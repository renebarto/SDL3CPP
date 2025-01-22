#pragma once

#include "Model/ICPU.h"

#include <ostream>

class ISystem
{
public:
    virtual ~ISystem() = default;

    virtual bool Init() = 0;

    virtual void Reset() = 0;

    virtual bool IsHalted() = 0;

    virtual bool LoadROM(const ByteVector &romContents) = 0;

    virtual bool Disassemble(std::string &mnemonic) = 0;
    virtual bool ProcessInstruction() = 0;

    virtual std::string DumpRegisters() = 0;

    virtual uint64_t GetCPUClock() = 0;
    virtual uint64_t GetCPUClockFreq() = 0;
};
