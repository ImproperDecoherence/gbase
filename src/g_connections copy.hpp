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

template <typename CallbackType> using CallbackSignature = void(CallbackParam<CallbackType>);

template <typename CallbackType> using Callback = std::function<CallbackSignature<CallbackType>>;

template <typename CallbackType> class GConnector {
  public:
    GConnector() = default;
    ~GConnector() = default;

    void connect(GConnectable *instance, Callback<CallbackType> callback) {
        callbacks_[instance] = std::move(callback);
    }

    void disconnect(GConnectable *instance) { callbacks_.erase(instance); }

    void emit(GConnectable *instance, CallbackParam<CallbackType> callbackParam) const {
        auto it = callbacks_.find(instance);
        if (it != callbacks_.end() && it->second) {
            it->second(callbackParam);
        }
    }

    void emit(CallbackParam<CallbackType> callbackParam) const {
        for (const auto &entry : callbacks_) {
            if (entry.second) {
                entry.second(callbackParam);
            }
        }
    }

    Size connectionCount() const { return callbacks_.size(); }

    bool isConnected(GConnectable *instance) const { return callbacks_.find(instance) != callbacks_.end(); }

  private:
    std::unordered_map<GConnectable *, Callback<CallbackType>> callbacks_;
};

template <typename CallbackType> class GAutoConnection {
  public:
    // Constructor for lambdas or general callable objects
    template <typename Callable>
    GAutoConnection(GConnector<CallbackType> &connector, GConnectable *instance, Callable &&callback)
        : connector_{&connector}, instance_{instance} {
        connector_->connect(instance,
                            std::function<CallbackSignature<CallbackType>>(std::forward<Callable>(callback)));
    }

    // Constructor for member function pointers
    template <typename InstanceType>
    GAutoConnection(GConnector<CallbackType> &connector, InstanceType *instance,
                    void (InstanceType::*memberFunc)(CallbackParam<CallbackType>))
        : connector_{&connector}, instance_{instance} {
        connector_->connect(instance, [instance, memberFunc](CallbackParam<CallbackType> param) {
            (instance->*memberFunc)(param);
        });
    }

    ~GAutoConnection() noexcept {
        if (connector_ && instance_) {
            connector_->disconnect(instance_);
        }
    }

    GAutoConnection(GAutoConnection &&other) noexcept
        : connector_(other.connector_), instance_(other.instance_) {
        other.connector_ = nullptr;
        other.instance_ = nullptr;
    }

    GAutoConnection &operator=(GAutoConnection &&other) noexcept {
        if (this != &other) {
            if (connector_ && instance_) {
                connector_->disconnect(instance_);
            }
            connector_ = other.connector_;
            instance_ = other.instance_;
            other.connector_ = nullptr;
            other.instance_ = nullptr;
        }
        return *this;
    }

  private:
    GConnector<CallbackType> *connector_{nullptr};
    GConnectable *instance_{nullptr};
};

} // namespace gbase