//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : ObservableSingular.h
//
// Namespace   : utility
//
// Class       : ObservableSingular
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <algorithm>
#include <functional>
#include <list>
#include <mutex>
#include "utility/IObservableSingular.h"

namespace utility
{

template <class T>
class ObservableSingular
    : public IObservableSingular<T>
{
public:
    typedef std::recursive_mutex Mutex;
    typedef std::lock_guard<Mutex> Lock;

    ObservableSingular()
        : m_observer{}
    {}
    void Subscribe(T* observer) override;
    void Unsubscribe(T* observer) override;

    // Not thread safe
    T* GetObserver();
    // Thread safe
    void Invoke(std::function<void(T&)> action);

protected:
    T* m_observer;
    Mutex m_guard;
};

template <class T>
void ObservableSingular<T>::Subscribe(T* observer)
{
    Lock lock(m_guard);
    m_observer = observer;
}

template <class T>
void ObservableSingular<T>::Unsubscribe(T* observer)
{
    Lock lock(m_guard);
    if (m_observer == observer)
        m_observer = nullptr;
}

template<class T>
T* ObservableSingular<T>::GetObserver()
{
    return m_observer;
}

template<class T>
void ObservableSingular<T>::Invoke(std::function<void (T&)> action)
{
    Lock lock(m_guard);
    if (m_observer != nullptr)
    {
        action(*m_observer);
    }
}

} // namespace utility
