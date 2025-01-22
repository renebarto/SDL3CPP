#pragma once

template<class AddressType>
class IDebugger
{
public:
    virtual ~IDebugger() = default;

    virtual void Run() = 0;
};
