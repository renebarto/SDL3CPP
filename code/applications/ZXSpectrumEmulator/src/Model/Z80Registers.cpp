#include "Model/Z80Registers.h"

#include <iomanip>
#include <sstream>
#include "Utility/Serialization.h"

// Fast flag computation lookup table
static uint8_t FlagsLookupTable[256]; // OR,XOR and more

// Flags
#define flagS  0x80
#define flagZ  0x40
#define flagHC 0x10
#define flagPV 0x04
#define flagN  0x02
#define flagC  0x01

// Undocumented flags
#define flagU1 0x08
#define flagU2 0x20

/* calculates an even parity for the given 8-bit number */
static bool OddParity8(uint8_t x)
{
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    x ^= 1;

    return (x & 1) != 0;
}

static void InitializeFlagsTable()
{
    for (unsigned i = 0; i < 256; ++i)
    {
        FlagsLookupTable[i] = static_cast<uint8_t>(i & (flagS | flagU1 | flagU2));
        if (OddParity8(static_cast<uint8_t>(i)))
            FlagsLookupTable[i] |= flagPV;
    }
    FlagsLookupTable[0] |= flagZ;
}

void Z80Registers::Reset()
{
    std::memset(Reg, 0, sizeof(Reg));
    F = {};
    std::memset(Reg_, 0, sizeof(Reg_));
    F_ = {};
    I = {};
    IX = {};
    IY = {};
    PC = {};
    R = {};
    SP = {};

    IFF1 = {};
    IFF2 = {};
    IntMode = {};
    IntLock = {};
    IntPending = {};
    NMIPending = {};
    Modifier    = {};
    Halted = {};
    InitializeFlagsTable();
}

std::string LogValue(bool value)
{
    std::ostringstream stream;
    stream << (value ? "1" : "0");
    return stream.str();
}

std::string LogValue(uint8_t value)
{
    return serialization::Serialize(value, 2, 16);
}

std::string LogValue(uint16_t value)
{
    return serialization::Serialize(value, 4, 16);
}

std::string LogFlags(uint8_t value)
{
    std::ostringstream stream;
    stream << "S=" << LogValue(static_cast<bool>(value & 0x80)) << " ";
    stream << "Z=" << LogValue(static_cast<bool>(value & 0x40)) << " ";
    stream << "N=" << LogValue(static_cast<bool>(value & 0x20)) << " ";
    stream << "P/V=" << LogValue(static_cast<bool>(value & 0x04)) << " ";
    stream << "N=" << LogValue(static_cast<bool>(value & 0x02)) << " ";
    stream << "C=" << LogValue(static_cast<bool>(value & 0x01)) << " ";
    return stream.str();
}

std::string Z80Registers::Dump()
{
    std::ostringstream stream;
    stream << "A  = " << LogValue(Reg[7]) << "\n";
    stream << "B  = " << LogValue(Reg[0]) << "\n";
    stream << "C  = " << LogValue(Reg[1]) << "\n";
    stream << "D  = " << LogValue(Reg[2]) << "\n";
    stream << "E  = " << LogValue(Reg[3]) << "\n";
    stream << "H  = " << LogValue(Reg[4]) << "\n";
    stream << "L  = " << LogValue(Reg[5]) << "\n";
    stream << "F  = " << LogFlags(F) << "\n";

    stream << "A' = " << LogValue(Reg_[7]) << "\n";
    stream << "B' = " << LogValue(Reg_[0]) << "\n";
    stream << "C' = " << LogValue(Reg_[1]) << "\n";
    stream << "D' = " << LogValue(Reg_[2]) << "\n";
    stream << "E' = " << LogValue(Reg_[3]) << "\n";
    stream << "H' = " << LogValue(Reg_[4]) << "\n";
    stream << "L' = " << LogValue(Reg_[5]) << "\n";
    stream << "F' = " << LogFlags(F_) << "\n";

    stream << "I  = " << LogValue(I) << "\n";
    stream << "R  = " << LogValue(R) << "\n";
    stream << "IX = " << LogValue(IX) << "\n";
    stream << "IY = " << LogValue(IY) << "\n";
    stream << "PC = " << LogValue(PC) << "\n";
    stream << "SP = " << LogValue(SP) << "\n";

    stream << "IFF1 = " << LogValue(IFF1) << "\n";
    stream << "IFF2 = " << LogValue(IFF2) << "\n";
    stream << "INTM = " << LogValue(IntMode) << "\n";
    stream << "INTL = " << LogValue(IntLock) << "\n";
    stream << "INTP = " << LogValue(IntPending) << "\n";
    stream << "NMIP = " << LogValue(NMIPending) << "\n";
    stream << "MOD  = " << LogValue(Modifier) << "\n";
    stream << "HLT  = " << LogValue(Halted) << "\n";
    return stream.str();
}

void Z80Registers::SetAF(uint16_t val)
{
    Reg[RegisterIndex::A] = static_cast<uint8_t>(val >> 8);
    F = static_cast<uint8_t>(val & 0xFF);
}

void Z80Registers::SetBC(uint16_t val)
{
    Reg[RegisterIndex::B] = static_cast<uint8_t>(val >> 8);
    Reg[RegisterIndex::C] = static_cast<uint8_t>(val & 0xFF);
}

void Z80Registers::SetDE(uint16_t val)
{
    Reg[RegisterIndex::D] = static_cast<uint8_t>(val >> 8);
    Reg[RegisterIndex::E] = static_cast<uint8_t>(val & 0xFF);
}

void Z80Registers::SetHL(uint16_t val)
{
    Reg[RegisterIndex::H] = static_cast<uint8_t>(val >> 8);
    Reg[RegisterIndex::L] = static_cast<uint8_t>(val & 0xFF);
}

void Z80Registers::SetPC(uint16_t val)
{
    PC = val;
}

static uint8_t xor8(uint8_t a, uint8_t b)
{
    return static_cast<uint8_t>(a ^ b);
}

void Z80Registers::XOR(RegisterIndex op1, RegisterIndex op2, RegisterIndex result)
{
    uint8_t res = xor8(Reg[op1], Reg[op2]);
    Reg[result] = res;
    F = FlagsLookupTable[res];
}
