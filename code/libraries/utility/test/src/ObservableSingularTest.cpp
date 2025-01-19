//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ObservableSingularTest.cpp
//
// Namespace   : utility
//
// Class       : ObservableTest
//
// Description :
//
//------------------------------------------------------------------------------

#include "test-platform/GoogleTest.h"

#include "utility/ObservableSingular.h"

namespace utility {

using Value = int;

TEST(ObservableSingularTest, Construction)
{
    ObservableSingular<Value> target;
    EXPECT_NULL(target.GetObserver());
}

TEST(ObservableSingularTest, Subscribe)
{
    int value1 = 123;
    int value2 = 234;
    ObservableSingular<Value> target;

    target.Subscribe(&value1);
    EXPECT_EQ(&value1, target.GetObserver());
    target.Subscribe(&value2);
    EXPECT_EQ(&value2, target.GetObserver());
}

TEST(ObservableSingularTest, Unsubscribe)
{
    int value1 = 123;
    int value2 = 456;
    ObservableSingular<Value> target;

    target.Subscribe(&value1);
    EXPECT_EQ(&value1, target.GetObserver());
    target.Subscribe(&value2);
    EXPECT_EQ(&value2, target.GetObserver());
    target.Unsubscribe(&value1);
    EXPECT_EQ(&value2, target.GetObserver());
    target.Unsubscribe(&value2);
    EXPECT_NULL(target.GetObserver());
}

namespace {

class Observer
{
private:
    int count;

public:
    Observer()
        : count{}
    {}
    void Call(int increment) { count += increment; }
    int Get() const { return count; }
};

} // namespace

using namespace std::placeholders;

TEST(ObservableSingularTest, Invoke)
{
    Observer observer;
    ObservableSingular<Observer> target;

    target.Invoke(std::bind(&Observer::Call, _1, 1));
    EXPECT_EQ(0, observer.Get());
    target.Subscribe(&observer);
    EXPECT_EQ(0, observer.Get());
    target.Invoke(std::bind(&Observer::Call, _1, 2));
    EXPECT_EQ(2, observer.Get());
}

} // namespace utility
