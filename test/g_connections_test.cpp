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
    virtual GConnector<TestSubjectI, String> &messageConnector() = 0;
    virtual GConnector<TestSubjectI, Integer> &countConnector() = 0;
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
        messageConnection.disconnect();
        messageConnection.connect(subject_->messageConnector(), this, TestObserver::messageChanged);

        countConnection.disconnect();
        countConnection.connect(subject_->countConnector(), this, TestObserver::countChanged);
    }

    TestObserver &operator=(TestObserver &&) = default;

    void messageChanged(TestSubjectI *subject, const String &message) {
        messages.push_back(subject->name() + ":" + message);
    }

    void countChanged(TestSubjectI *subject, const Integer &count) {
        counts.push_back(subject->name() + ":" + std::to_string(count));
    }

    GAutoConnection<TestSubjectI, String> messageConnection;
    GAutoConnection<TestSubjectI, Integer> countConnection;

    std::vector<String> messages;
    std::vector<String> counts;

    TestSubjectI *subject_{nullptr};
};

class TestSubject : public TestSubjectI {
  public:
    explicit TestSubject(const String &name) : name_{name} {}
    virtual ~TestSubject() = default;

    GConnector<TestSubjectI, String> &messageConnector() override { return messageConnections; }
    GConnector<TestSubjectI, Integer> &countConnector() override { return countConnections; }
    const String &name() const override { return name_; };

    GConnector<TestSubjectI, String> messageConnections;
    GConnector<TestSubjectI, Integer> countConnections;

  private:
    String name_;
};

GTEST(GConnectionsTest) {
    TestSubject subject{"Subject"};
    std::vector<TestObserver> observers;
    observers.emplace_back(TestObserver{&subject});
    observers.emplace_back(TestObserver{&subject});
    observers.emplace_back(TestObserver{&subject});

    GCHECK("number message observers", subject.messageConnections.connectionCount(), observers.size());
    GCHECK("number count observers", subject.countConnections.connectionCount(), observers.size());

    const String hello{"Hello!"};
    subject.messageConnections.emit(&subject, hello);

    subject.countConnections.emit(&subject, 7);
    subject.countConnections.emit(&subject, 9);

    for (auto &observer : observers) {

        GCHECK("", observer.messages.size(), Size{1});
        GCHECK("", observer.counts.size(), Size{2});

        GCHECK("", observer.messages[0], String{"Subject:Hello!"});
        GCHECK("", observer.counts[0], String{"Subject:7"});
        GCHECK("", observer.counts[1], String{"Subject:9"});
    }

    observers.clear();
    GCHECK("number message observers", subject.messageConnections.connectionCount(), Size{0});
    GCHECK("number count observers", subject.countConnections.connectionCount(), Size{0});

    subject.messageConnections.emit(&subject, hello);
}

} // namespace gbase::test
