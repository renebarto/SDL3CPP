//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : IObservableSingular.h
//
// Namespace   : utility
//
// Class       : IObservableSingular
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

namespace utility
{

template <class T>
class IObservableSingular
{
public:
    virtual ~IObservableSingular() = default;

    virtual void Subscribe(T* observer) = 0;
    virtual void Unsubscribe(T* observer) = 0;
};

} // namespace utility
