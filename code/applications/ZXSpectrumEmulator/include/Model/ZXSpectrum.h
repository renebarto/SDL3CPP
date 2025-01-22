#pragma once

#include <cstdint>
#include <string>

#include "tracing/Tracing.h"
#include "Model/ISystem.h"
#include "Model/Z80.h"


class ZXSpectrum
    : public ISystem
{
private:
    Z80 m_cpu;

public:
    ZXSpectrum();
    ZXSpectrum(const ZXSpectrum &) = delete;
    ZXSpectrum(ZXSpectrum &&) = delete;

    ZXSpectrum &operator = (ZXSpectrum &) = delete;
    ZXSpectrum &operator = (ZXSpectrum &&) = delete;

    bool Init() override;

    void Reset() override;

    bool IsHalted() override;

    bool LoadROM(const ByteVector &romContents) override;

    bool Disassemble(std::string &mnemonic) override;
    bool ProcessInstruction() override;

    std::string DumpRegisters() override;

    uint64_t GetCPUClock() override;
    uint64_t GetCPUClockFreq() override;
};
