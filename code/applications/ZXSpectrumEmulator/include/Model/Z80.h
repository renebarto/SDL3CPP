#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <string>

#include "Model/ICPU.h"
#include "Model/Memory.h"
#include "Model/IO.h"
#include "Model/Z80Disassembler.h"
#include "Model/Z80Registers.h"

class Z80
    : public ICPU
{
public:

private:
    using OpcodeFunction = std::function<void ()>;
    using OpcodeFuncionLookup = std::map<uint8_t, OpcodeFunction>;
    static const OpcodeFuncionLookup OpcodeLookup;

    static Z80 *m_instance;
    uint64_t m_cpuFreq;
    Z80Registers m_registers;
    MemorySpace m_memory;
    ROM m_rom;
    RAM m_ram;
    MemoryMap m_memoryMap;
    VideoBorder m_videoBorder;
    IOMap m_ioMap;
    uint8_t m_opcode;
    Z80Disassembler m_disassembler;
    uint64_t m_cpuClock;

public:
    Z80(uint64_t clockFreq);
    Z80(const Z80 &) = delete;

    Z80& operator =(const Z80 &) = delete;
    Z80& operator =(Z80 &&) = delete;

    static Z80 *GetInstance();
    Z80Registers &GetRegisters() { return m_registers; }
    const Z80Registers &GetRegisters() const { return m_registers; }

    bool Init() override;
    void Reset() override;
    bool IsHalted() override;
    std::string DumpRegisters() override;

    bool LoadROM(const ByteVector &romContents) override;

    bool ExecuteInstruction() override;
    bool Disassemble(std::string &mnemonic);
    void IncrementCPUClock(uint8_t increment);
    uint8_t ReadOpcodeByte();
    uint8_t ReadByte();
    uint16_t ReadWord();
    void Out(uint8_t port, uint8_t value);
    uint8_t GetOpcode();
    uint64_t GetCPUClock();
    uint64_t GetCPUClockFreq();

private:
};
