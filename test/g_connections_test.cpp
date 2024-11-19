#include <iostream>

#include "g_basic_types.hpp"
#include "g_connections.hpp"
#include "g_test_framework.hpp"
#include "g_vector.hpp"

using namespace std;

namespace gbase::test {

class TestSubjectI {
  public:
    virtual ~TestSubjectI() = default;
    virtual G0PConnector<TestSubjectI> &notifyConnector() = 0;
    virtual G1PConnector<TestSubjectI, String> &messageConnector() = 0;
    virtual G1PConnector<TestSubjectI, Integer> &countConnector() = 0;
    virtual const String &name() const = 0;
};

class TestObserver : public GConnectable {
  public:
    explicit TestObserver(TestSubjectI *subject) : GConnectable(), subject_{subject} { reconnect(); }

    virtual ~TestObserver() = default;

    TestObserver(TestObserver &&other)
        : messageConnection{std::move(other.messageConnection)},
          countConnection{std::move(other.countConnection)}, messages{std::move(other.messages)},
          counts{std::move(other.counts)}, subject_{other.subject_} {

        reconnect();
    }

    void reconnect() {
        notifyConnection.disconnect();
        notifyConnection.connect(subject_->notifyConnector(), this, TestObserver::subjectChanged);

        messageConnection.disconnect();
        messageConnection.connect(subject_->messageConnector(), this, TestObserver::messageChanged);

        countConnection.disconnect();
        countConnection.connect(subject_->countConnector(), this, TestObserver::countChanged);
    }

    TestObserver &operator=(TestObserver &&) = default;

    void subjectChanged(TestSubjectI *subject) { notifications.push_back(subject->name()); }

    void messageChanged(TestSubjectI *subject, const String &message) {
        messages.push_back(subject->name() + ":" + message);
    }

    void countChanged(TestSubjectI *subject, const Integer &count) {
        counts.push_back(subject->name() + ":" + std::to_string(count));
    }

    G0PAutoConnection<TestSubjectI> notifyConnection;
    G1PAutoConnection<TestSubjectI, String> messageConnection;
    G1PAutoConnection<TestSubjectI, Integer> countConnection;

    std::vector<String> notifications;
    std::vector<String> messages;
    std::vector<String> counts;

    TestSubjectI *subject_{nullptr};
};

class TestSubject : public TestSubjectI {
  public:
    explicit TestSubject(const String &name) : name_{name} {}
    virtual ~TestSubject() = default;

    G0PConnector<TestSubjectI> &notifyConnector() override { return theNotifyConnector; }
    G1PConnector<TestSubjectI, String> &messageConnector() override { return theMessageConnector; }
    G1PConnector<TestSubjectI, Integer> &countConnector() override { return theCountConnector; }
    const String &name() const override { return name_; };

    G0PConnector<TestSubjectI> theNotifyConnector;
    G1PConnector<TestSubjectI, String> theMessageConnector;
    G1PConnector<TestSubjectI, Integer> theCountConnector;

  private:
    String name_;
};

GTEST(GConnectionsTest) {
    TestSubject subject{"Subject"};
    std::vector<TestObserver> observers;
    observers.emplace_back(TestObserver{&subject});
    observers.emplace_back(TestObserver{&subject});
    observers.emplace_back(TestObserver{&subject});

    GCHECK("number message observers", subject.theMessageConnector.connectionCount(), observers.size());
    GCHECK("number count observers", subject.theCountConnector.connectionCount(), observers.size());

    subject.theNotifyConnector.notify(&subject);
    subject.theNotifyConnector.notify(&subject);
    subject.theNotifyConnector.notify(&subject);

    const String hello{"Hello!"};
    subject.theMessageConnector.notify(&subject, hello);

    subject.theCountConnector.notify(&subject, 7);
    subject.theCountConnector.notify(&subject, 9);

    for (auto &observer : observers) {
        GCHECK("", observer.notifications.size(), Size{3});
        GCHECK("", observer.notifications[0], String{"Subject"});
        GCHECK("", observer.notifications[1], String{"Subject"});
        GCHECK("", observer.notifications[2], String{"Subject"});

        GCHECK("", observer.messages.size(), Size{1});
        GCHECK("", observer.counts.size(), Size{2});

        GCHECK("", observer.messages[0], String{"Subject:Hello!"});
        GCHECK("", observer.counts[0], String{"Subject:7"});
        GCHECK("", observer.counts[1], String{"Subject:9"});
    }

    observers.clear();
    GCHECK("number message observers", subject.theMessageConnector.connectionCount(), Size{0});
    GCHECK("number count observers", subject.theCountConnector.connectionCount(), Size{0});

    subject.theMessageConnector.notify(&subject, hello);
}

} // namespace gbase::test
