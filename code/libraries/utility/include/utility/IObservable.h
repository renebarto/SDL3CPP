//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : IObservable.h
//
// Namespace   : utility
//
// Class       : IObservable
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

namespace utility
{

template <class T>
class IObservable
{
public:
    virtual ~IObservable() = default;

    virtual void Subscribe(T* observer) = 0;
    virtual void Unsubscribe(T* observer) = 0;
};

} // namespace utility
