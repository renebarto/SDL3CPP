#pragma once

#include <string>

class MemorySpace;
struct InstructionDefinition;

class Z80Disassembler
{
private:
    MemorySpace& m_memory;
    uint16_t m_instructionOrigin;
    uint16_t m_currentLocation;
    static Z80Disassembler *m_instance;

public:
    Z80Disassembler(MemorySpace& memory);
    Z80Disassembler(const Z80Disassembler &) = delete;
    Z80Disassembler(Z80Disassembler &&) = delete;

    Z80Disassembler &operator = (const Z80Disassembler &) = delete;
    Z80Disassembler &operator = (Z80Disassembler &&) = delete;

    static Z80Disassembler *GetInstance();
    bool DisassembleInstruction(uint16_t address, uint8_t instructionSize, std::string &mnemonic);

    uint8_t GetInstructionByte();

private:
    bool DecodeInstruction(std::string &mnemonic);
    std::string SerializeOperand(const InstructionDefinition &def, int operandIndex);
    void BuildMnemonic(const InstructionDefinition &def, std::string &mnemonic);
};
