#pragma once

#include <string>
#include <vector>

using ByteVector = std::vector<uint8_t>;

class ICPU
{
public:
    virtual ~ICPU() = default;

    virtual bool Init() = 0;
    virtual void Reset() = 0;
    virtual bool IsHalted() = 0;
    virtual std::string DumpRegisters() = 0;

    virtual bool LoadROM(const ByteVector &romContents) = 0;
    virtual bool ExecuteInstruction() = 0;

    virtual uint64_t GetCPUClock() = 0;
    virtual uint64_t GetCPUClockFreq() = 0;
};
