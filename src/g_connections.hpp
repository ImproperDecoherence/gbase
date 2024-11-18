#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>

namespace gbase {

class GConnectable {
  public:
    virtual ~GConnectable() = default;
};

template <typename CallbackType> using CallbackParam = const CallbackType &;

template <typename Subject, typename CallbackType>
using CallbackSignature = void(Subject *, CallbackParam<CallbackType>);

template <typename Subject, typename CallbackType>
using Callback = std::function<CallbackSignature<Subject, CallbackType>>;

template <typename Subject, typename CallbackType> class GConnector {
  public:
    GConnector() = default;
    ~GConnector() = default;

    void connect(GConnectable *instance, Callback<Subject, CallbackType> callback) {
        callbacks_[instance] = std::move(callback);
    }

    void disconnect(GConnectable *instance) { callbacks_.erase(instance); }

    void emit(Subject *subject, GConnectable *instance, CallbackParam<CallbackType> callbackParam) const {
        auto it = callbacks_.find(instance);
        if (it != callbacks_.end() && it->second) {
            it->second(subject, callbackParam);
        }
    }

    void emit(Subject *subject, CallbackParam<CallbackType> callbackParam) const {
        for (const auto &entry : callbacks_) {
            if (entry.second) {
                entry.second(subject, callbackParam);
            }
        }
    }

    Size connectionCount() const { return callbacks_.size(); }

    bool isConnected(GConnectable *instance) const { return callbacks_.find(instance) != callbacks_.end(); }

  private:
    std::unordered_map<GConnectable *, Callback<Subject, CallbackType>> callbacks_;
};

template <typename Subject, typename CallbackType> class GAutoConnection {
  public:
    GAutoConnection() : connector_{nullptr}, instance_{nullptr} {}

    // Constructor for lambdas or general callable objects
    template <typename Callable>
    GAutoConnection(GConnector<Subject, CallbackType> &connector, GConnectable *instance, Callable &&callback)
        : connector_{&connector}, instance_{instance} {
        connector_->connect(instance, std::function<CallbackSignature<Subject, CallbackType>>(
                                          std::forward<Callable>(callback)));
    }

    // Constructor for member function pointers
    template <typename InstanceType>
    GAutoConnection(GConnector<Subject, CallbackType> &connector, GConnectable *instance,
                    void (InstanceType::*memberFunc)(Subject *, CallbackParam<CallbackType>))
        : connector_{&connector}, instance_{instance} {

        connect(connector, instance, memberFunc);
    }

    ~GAutoConnection() noexcept { disconnect(); }

    GAutoConnection(GAutoConnection &&other) noexcept
        : connector_(other.connector_), instance_(other.instance_) {
        other.connector_ = nullptr;
        other.instance_ = nullptr;
    }

    GAutoConnection &operator=(GAutoConnection &&other) noexcept {
        if (this != &other) {
            disconnect();
            connector_ = other.connector_;
            instance_ = other.instance_;
            other.connector_ = nullptr;
            other.instance_ = nullptr;
        }
        return *this;
    }

    void disconnect() {
        if (connector_ && instance_) {
            connector_->disconnect(instance_);
        }
        connector_ = nullptr;
        instance_ = nullptr;
    }

    template <typename InstanceType>
    void connect(GConnector<Subject, CallbackType> &connector, GConnectable *instance,
                 void (InstanceType::*memberFunc)(Subject *, CallbackParam<CallbackType>)) {

        connector_ = &connector;
        instance_ = instance;

        connector_->connect(instance, [instance = static_cast<InstanceType *>(instance),
                                       memberFunc](Subject *subject, CallbackParam<CallbackType> param) {
            (instance->*memberFunc)(subject, param);
        });
    }

  private:
    GConnector<Subject, CallbackType> *connector_{nullptr};
    GConnectable *instance_{nullptr};
};

} // namespace gbase