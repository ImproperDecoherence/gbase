#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>

#include "g_basic_types.hpp"

namespace gbase {

/**
 * @brief
 *
 */
class GConnectable {
  public:
    virtual ~GConnectable() = default;
};

template <typename CallbackType> using CallbackParam = const CallbackType &;

template <typename SubjectType> using CallbackSigNoParameter = void(SubjectType *);

template <typename SubjectType, typename CallbackType>
using CallbackSigOneParameter = void(SubjectType *, CallbackParam<CallbackType>);

template <typename SubjectType>
using CallbackFuncNoParameter = std::function<CallbackSigNoParameter<SubjectType>>;

template <typename SubjectType, typename CallbackType>
using CallbackFuncOneParameter = std::function<CallbackSigOneParameter<SubjectType, CallbackType>>;

/**
 * @brief
 *
 */
template <typename SubjectType> class G0PConnector {
  public:
    G0PConnector() = default;
    ~G0PConnector() = default;

    void connect(GConnectable *instance, CallbackFuncNoParameter<SubjectType> callback) {
        callbacks_[instance] = std::move(callback);
    }

    void disconnect(GConnectable *instance) { callbacks_.erase(instance); }

    void notify(SubjectType *subject, GConnectable *instance) const {
        auto it = callbacks_.find(instance);
        if (it != callbacks_.end() && it->second) {
            it->second(subject);
        }
    }

    void notify(SubjectType *subject) const {
        for (const auto &entry : callbacks_) {
            if (entry.second) {
                entry.second(subject);
            }
        }
    }

    Size connectionCount() const { return callbacks_.size(); }

    bool isConnected(GConnectable *instance) const { return callbacks_.find(instance) != callbacks_.end(); }

  private:
    std::unordered_map<GConnectable *, CallbackFuncNoParameter<SubjectType>> callbacks_;
};

/**
 * @brief
 *
 */
template <typename SubjectType, typename CallbackType> class G1PConnector {
  public:
    G1PConnector() = default;
    ~G1PConnector() = default;

    void connect(GConnectable *instance, CallbackFuncOneParameter<SubjectType, CallbackType> callback) {
        callbacks_[instance] = std::move(callback);
    }

    void disconnect(GConnectable *instance) { callbacks_.erase(instance); }

    void notify(SubjectType *subject, GConnectable *instance,
                CallbackParam<CallbackType> callbackParam) const {
        auto it = callbacks_.find(instance);
        if (it != callbacks_.end() && it->second) {
            it->second(subject, callbackParam);
        }
    }

    void notify(SubjectType *subject, CallbackParam<CallbackType> callbackParam) const {
        for (const auto &entry : callbacks_) {
            if (entry.second) {
                entry.second(subject, callbackParam);
            }
        }
    }

    Size connectionCount() const { return callbacks_.size(); }

    bool isConnected(GConnectable *instance) const { return callbacks_.find(instance) != callbacks_.end(); }

  private:
    std::unordered_map<GConnectable *, CallbackFuncOneParameter<SubjectType, CallbackType>> callbacks_;
};

/**
 * @brief
 *
 */
template <typename SubjectType> class G0PAutoConnection {
  public:
    G0PAutoConnection() : connector_{nullptr}, instance_{nullptr} {}

    // Constructor for lambdas or general callable objects
    template <typename Callable>
    G0PAutoConnection(G0PConnector<SubjectType> &connector, GConnectable *instance, Callable &&callback)
        : connector_{&connector}, instance_{instance} {
        connector_->connect(
            instance, std::function<CallbackSigNoParameter<SubjectType>>(std::forward<Callable>(callback)));
    }

    // Constructor for member function pointers
    template <typename InstanceType>
    G0PAutoConnection(G0PConnector<SubjectType> &connector, GConnectable *instance,
                      void (InstanceType::*memberFunc)(SubjectType *))
        : connector_{&connector}, instance_{instance} {

        connect(connector, instance, memberFunc);
    }

    ~G0PAutoConnection() noexcept { disconnect(); }

    G0PAutoConnection(G0PAutoConnection &&other) noexcept
        : connector_(other.connector_), instance_(other.instance_) {
        other.connector_ = nullptr;
        other.instance_ = nullptr;
    }

    G0PAutoConnection &operator=(G0PAutoConnection &&other) noexcept {
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
    void connect(G0PConnector<SubjectType> &connector, GConnectable *instance,
                 void (InstanceType::*memberFunc)(SubjectType *)) {

        connector_ = &connector;
        instance_ = instance;

        connector_->connect(instance, [instance = static_cast<InstanceType *>(instance), memberFunc](
                                          SubjectType *subject) { (instance->*memberFunc)(subject); });
    }

  private:
    G0PConnector<SubjectType> *connector_{nullptr};
    GConnectable *instance_{nullptr};
};

/**
 * @brief
 *
 */
template <typename SubjectType, typename CallbackType> class G1PAutoConnection {
  public:
    G1PAutoConnection() : connector_{nullptr}, instance_{nullptr} {}

    // Constructor for lambdas or general callable objects
    template <typename Callable>
    G1PAutoConnection(G1PConnector<SubjectType, CallbackType> &connector, GConnectable *instance,
                      Callable &&callback)
        : connector_{&connector}, instance_{instance} {
        connector_->connect(instance, std::function<CallbackSigOneParameter<SubjectType, CallbackType>>(
                                          std::forward<Callable>(callback)));
    }

    // Constructor for member function pointers
    template <typename InstanceType>
    G1PAutoConnection(G1PConnector<SubjectType, CallbackType> &connector, GConnectable *instance,
                      void (InstanceType::*memberFunc)(SubjectType *, CallbackParam<CallbackType>))
        : connector_{&connector}, instance_{instance} {

        connect(connector, instance, memberFunc);
    }

    ~G1PAutoConnection() noexcept { disconnect(); }

    G1PAutoConnection(G1PAutoConnection &&other) noexcept
        : connector_(other.connector_), instance_(other.instance_) {
        other.connector_ = nullptr;
        other.instance_ = nullptr;
    }

    G1PAutoConnection &operator=(G1PAutoConnection &&other) noexcept {
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
    void connect(G1PConnector<SubjectType, CallbackType> &connector, GConnectable *instance,
                 void (InstanceType::*memberFunc)(SubjectType *, CallbackParam<CallbackType>)) {

        connector_ = &connector;
        instance_ = instance;

        connector_->connect(instance, [instance = static_cast<InstanceType *>(instance),
                                       memberFunc](SubjectType *subject, CallbackParam<CallbackType> param) {
            (instance->*memberFunc)(subject, param);
        });
    }

  private:
    G1PConnector<SubjectType, CallbackType> *connector_{nullptr};
    GConnectable *instance_{nullptr};
};

} // namespace gbase