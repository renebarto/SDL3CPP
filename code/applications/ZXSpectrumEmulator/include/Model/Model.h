#pragma once

#include "Model/Z80.h"

class Model
{
private:
    Z80Registers m_registers;

public:
    Model();

    const Z80Registers &GetRegisters() const;

    bool IsHalted() const;
    void DumpRegisters() const;
    void PrintClockInfo() const;
};

