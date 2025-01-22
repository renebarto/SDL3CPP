#pragma once

#include <cstdint>
#include <string>

#include "tracing/Tracing.h"

enum RegisterIndex
{
    A = 0x7,
    B = 0x0,
    C = 0x1,
    D = 0x2,
    E = 0x3,
    H = 0x4,
    L = 0x5,
};

__pragma(pack(push, 1))
class Z80Registers
{
public:
    // General-purpose register set (except Flags (= 6))
    uint8_t Reg[8];
    // Flags register
    uint8_t F;

    // Alternate register set (except F')
    uint8_t Reg_[8];
    // Alternate Flags register
    uint8_t F_;

    // Interrupt page address register
    uint8_t I;
    // Index registers
    uint16_t IX, IY;
    // Program counter
    uint16_t PC;
    // Memory refresh register
    uint8_t R;
    // Stack pointer
    uint16_t SP;

    // Interrupt flip-flops
    bool IFF1;
    bool IFF2;
    // Interrupt mode
    uint8_t IntMode;
    // Blocks INT & NMI (after EI/DI/DD/FD)
    bool IntLock;
    // An interrupt is pending
    bool IntPending;
    // A NMI is pending
    bool NMIPending;
    // 0 / 0xDD / 0xFD
    uint8_t Modifier;
    // Halted by the HALT instruction?
    bool Halted;

    void Reset();
    std::string Dump();
    void SetAF(uint16_t val);
    void SetBC(uint16_t val);
    void SetDE(uint16_t val);
    void SetHL(uint16_t val);
    void SetPC(uint16_t val);
    void XOR(RegisterIndex op1, RegisterIndex op2, RegisterIndex result);
};
__pragma(pack(pop))
