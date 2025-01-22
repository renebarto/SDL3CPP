#include "Model/Z80Disassembler.h"

#include <map>

#include "tracing/Tracing.h"
#include "Model/Memory.h"
#include "Utility/Serialization.h"

enum class InstructionName
{
    ADC,
    ADD,
    AND,
    BIT,
    CALL,
    CCF,
    CP,
    CPD,
    CPDR,
    CPI,
    CPIR,
    CPL,
    DAA,
    DEC,
    DI,
    DJNZ,
    EI,
    EX,
    EXX,
    HALT,
    IM,
    IN,
    INC,
    IND,
    INDR,
    INI,
    INIR,
    JP,
    JR,
    LD,
    LDD,
    LDDR,
    LDI,
    LDIR,
    NEG,
    NOP,
    OR,
    OUT,
    OUTD,
    OTDR,
    OUTI,
    OTIR,
    POP,
    PUSH,
    RES,
    RET,
    RETI,
    RETN,
    RLA,
    RL,
    RLCA,
    RLC,
    RLD,
    RRA,
    RR,
    RRCA,
    RRC,
    RRD,
    RST,
    SBC,
    SCF,
    SET,
    SLA,
    SRA,
    SLL,
    SRL,
    SUB,
    XOR,
    INV,
};
enum class OperandName
{
    None,
    A,
    B,
    c,
    D,
    E,
    H,
    L,
    I,
    R,
    $,
    Ind$,
    AF,
    BC,
    DE,
    HL,
    IX,
    IY,
    IndIX,
    IndIY,
    C,
    NC,
    M,
    P,
    Z,
    NZ,
    PE,
    PO,
    IndBC,
    IndDE,
    IndHL,
    IndSP,
    IndC,
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    SP,
    AF_,
};

namespace serialization {

template<>
const BidirectionalMap<InstructionName, std::string> EnumSerializationMap<InstructionName>::ConversionMap = 
{
    { InstructionName::ADC, "ADC" },
    { InstructionName::ADD, "ADD" },
    { InstructionName::AND, "AND" },
    { InstructionName::BIT, "BIT" },
    { InstructionName::CALL, "CALL" },
    { InstructionName::CCF, "CCF" },
    { InstructionName::CP, "CP" },
    { InstructionName::CPD, "CPD" },
    { InstructionName::CPDR, "CPDR" },
    { InstructionName::CPI, "CPI" },
    { InstructionName::CPIR, "CPIR" },
    { InstructionName::CPL, "CPL" },
    { InstructionName::DAA, "DAA" },
    { InstructionName::DEC, "DEC" },
    { InstructionName::DI, "DI" },
    { InstructionName::DJNZ, "DJNZ" },
    { InstructionName::EI, "EI" },
    { InstructionName::EX, "EX" },
    { InstructionName::EXX, "EXX" },
    { InstructionName::HALT, "HALT" },
    { InstructionName::IM, "IM" },
    { InstructionName::IN, "IN" },
    { InstructionName::INC, "INC" },
    { InstructionName::IND, "IND" },
    { InstructionName::INDR, "INDR" },
    { InstructionName::INI, "INI" },
    { InstructionName::INIR, "INIR" },
    { InstructionName::JP, "JP" },
    { InstructionName::JR, "JR" },
    { InstructionName::LD, "LD" },
    { InstructionName::LDD, "LDD" },
    { InstructionName::LDDR, "LDDR" },
    { InstructionName::LDI, "LDI" },
    { InstructionName::LDIR, "LDIR" },
    { InstructionName::NEG, "NEG" },
    { InstructionName::NOP, "NOP" },
    { InstructionName::OR, "OR" },
    { InstructionName::OUT, "OUT" },
    { InstructionName::OUTD, "OUTD" },
    { InstructionName::OTDR, "OTDR" },
    { InstructionName::OUTI, "OUTI" },
    { InstructionName::OTIR, "OTIR" },
    { InstructionName::POP, "POP" },
    { InstructionName::PUSH, "PUSH" },
    { InstructionName::RES, "RES" },
    { InstructionName::RET, "RET" },
    { InstructionName::RETI, "RETI" },
    { InstructionName::RETN, "RETN" },
    { InstructionName::RLA, "RLA" },
    { InstructionName::RL, "RL" },
    { InstructionName::RLCA, "RLCA" },
    { InstructionName::RLC, "RLC" },
    { InstructionName::RLD, "RLD" },
    { InstructionName::RRA, "RRA" },
    { InstructionName::RR, "RR" },
    { InstructionName::RRCA, "RRCA" },
    { InstructionName::RRC, "RRC" },
    { InstructionName::RRD, "RRD" },
    { InstructionName::RST, "RST" },
    { InstructionName::SBC, "SBC" },
    { InstructionName::SCF, "SCF" },
    { InstructionName::SET, "SET" },
    { InstructionName::SLA, "SLA" },
    { InstructionName::SRA, "SRA" },
    { InstructionName::SLL, "SLL" },
    { InstructionName::SRL, "SRL" },
    { InstructionName::SUB, "SUB" },
    { InstructionName::XOR, "XOR" },
    { InstructionName::INV, "INV" },
};

template<>
const BidirectionalMap<OperandName, std::string> EnumSerializationMap<OperandName>::ConversionMap = 
{
    { OperandName::None, "None" },
    { OperandName::A, "A" },
    { OperandName::B, "B" },
    { OperandName::c, "c" },
    { OperandName::D, "D" },
    { OperandName::E, "E" },
    { OperandName::H, "H" },
    { OperandName::L, "L" },
    { OperandName::I, "I" },
    { OperandName::R, "R" },
    { OperandName::$, "$" },
    { OperandName::Ind$, "($)" },
    { OperandName::AF, "AF" },
    { OperandName::BC, "BC" },
    { OperandName::DE, "DE" },
    { OperandName::HL, "HL" },
    { OperandName::IX, "IX" },
    { OperandName::IY, "IY" },
    { OperandName::IndIX, "(IX)" },
    { OperandName::IndIY, "(IY)" },
    { OperandName::C, "C" },
    { OperandName::NC, "NC" },
    { OperandName::M, "M" },
    { OperandName::P, "P" },
    { OperandName::Z, "Z" },
    { OperandName::NZ, "NZ" },
    { OperandName::PE, "PE" },
    { OperandName::PO, "PO" },
    { OperandName::IndBC, "(BC)" },
    { OperandName::IndDE, "(DE)" },
    { OperandName::IndHL, "(HL)" },
    { OperandName::IndSP, "(SP)" },
    { OperandName::IndC, "(C)"},
    { OperandName::_0, "0" },
    { OperandName::_1, "1" },
    { OperandName::_2, "2" },
    { OperandName::_3, "3" },
    { OperandName::_4, "4" },
    { OperandName::_5, "5" },
    { OperandName::_6, "6" },
    { OperandName::_7, "7" },
    { OperandName::SP, "SP" },
    { OperandName::AF_, "AF" },
};

} // namespace serialization

enum class OperatorType
{
    Trivial,
    Direct8Bit,
    Direct16Bit,
    Address,
    Indirect,
    PCRelativeAddress,
    RestartAddress,
    Indirect8BitDisplacement,
    PrefixedIndirect,
};

enum class InstructionPrefixDDFD
{
    None,
    DD,
    FD,
};

enum class InstructionPrefixEDCB
{
    None,
    ED,
    CB,
};

using OperandFunction = std::function<std::string ()>;
using OperatorTypeLookup = std::map<OperatorType, OperandFunction>;

struct InstructionDefinition
{
    InstructionName name;
    OperatorType    operatorType;
    OperandName     operand1;
    OperandName     operand2;
};

using InstructionTable = std::vector<InstructionDefinition>;
using LookupTable2 = std::map<InstructionPrefixEDCB, const InstructionTable>;
using LookupTable = std::map<InstructionPrefixDDFD, LookupTable2>;


std::string HandleOperatorTypeTrivial()
{
    return {};
}

std::string HandleOperatorTypeDirect8Bit()
{
    auto instance = Z80Disassembler::GetInstance();
    uint8_t byte = instance->GetInstructionByte();
    return serialization::Serialize(byte, 2, 16);
}

std::string HandleOperatorTypeDirect16Bit()
{
    auto instance = Z80Disassembler::GetInstance();
    uint8_t lowByte = instance->GetInstructionByte();
    uint8_t highByte = instance->GetInstructionByte();
    uint16_t word = static_cast<uint16_t>(lowByte | (highByte << 8));
    return serialization::Serialize(word, 4, 16);
}

std::string HandleOperatorTypeAddress()
{
    auto instance = Z80Disassembler::GetInstance();
    uint8_t lowByte = instance->GetInstructionByte();
    uint8_t highByte = instance->GetInstructionByte();
    uint16_t word = static_cast<uint16_t>(lowByte | (highByte << 8));
    return serialization::Serialize(word, 4, 16);
}

std::string HandleOperatorTypeIndirect()
{
    return {};
}

std::string HandleOperatorTypePCRelativeAddress()
{
    return {};
}

std::string HandleOperatorTypeRestartAddress()
{
    return {};
}

std::string HandleOperatorTypeIndirect8BitDisplacement()
{
    return {};
}

std::string HandleOperatorTypePrefixedIndirect()
{
    return {};
}

static const OperatorTypeLookup OperatorTypeHandlerLookup = {
    { OperatorType::Trivial, HandleOperatorTypeTrivial },
    { OperatorType::Direct8Bit, HandleOperatorTypeDirect8Bit },
    { OperatorType::Direct16Bit, HandleOperatorTypeDirect16Bit },
    { OperatorType::Address, HandleOperatorTypeAddress },
    { OperatorType::Indirect, HandleOperatorTypeIndirect },
    { OperatorType::PCRelativeAddress, HandleOperatorTypePCRelativeAddress },
    { OperatorType::RestartAddress, HandleOperatorTypeRestartAddress },
    { OperatorType::Indirect8BitDisplacement, HandleOperatorTypeIndirect8BitDisplacement },
    { OperatorType::PrefixedIndirect, HandleOperatorTypePrefixedIndirect },
};

static const InstructionTable OperatorsStandard = {
    { InstructionName::NOP, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x00 NOP
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x01
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x02
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x03
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x04
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x05
    { InstructionName::LD,  OperatorType::Direct8Bit,  OperandName::B,     OperandName::$     }, // 0x06 LD B,nn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x07
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x08
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x09
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x0A
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x0B
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x0C
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x0D
    { InstructionName::LD,  OperatorType::Direct8Bit,  OperandName::C,     OperandName::$     }, // 0x0E LD C,nn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x0F
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x10
    { InstructionName::LD,  OperatorType::Direct16Bit, OperandName::DE,    OperandName::$     }, // 0x11 LD DE,nnnn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x12
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x13
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x14
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x15
    { InstructionName::LD,  OperatorType::Direct8Bit,  OperandName::D,     OperandName::$     }, // 0x16 LD D,nn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x17
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x18
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x19
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x1A
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x1B
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x1C
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x1D
    { InstructionName::LD,  OperatorType::Direct8Bit,  OperandName::E,     OperandName::$     }, // 0x1E LD E,nn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x1F
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x20
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x21
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x22
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x23
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x24
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x25
    { InstructionName::LD,  OperatorType::Direct8Bit,  OperandName::H,     OperandName::$     }, // 0x26 LD H,nn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x27
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x28
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x29
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x2A
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x2B
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x2C
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x2D
    { InstructionName::LD,  OperatorType::Direct8Bit,  OperandName::L,     OperandName::$     }, // 0x2E LD L,nn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x2F
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x30
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x31
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x32
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x33
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x34
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x35
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x36
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x37
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x38
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x39
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x3A
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x3B
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x3C
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x3D
    { InstructionName::LD,  OperatorType::Direct8Bit,  OperandName::A,     OperandName::$     }, // 0x3E LD A,nn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x3F
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::B,     OperandName::B     }, // 0x40 LD B,B
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::B,     OperandName::C     }, // 0x41 LD B,C
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::B,     OperandName::D     }, // 0x42 LD B,D
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::B,     OperandName::E     }, // 0x43 LD B,E
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::B,     OperandName::H     }, // 0x44 LD B,H
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::B,     OperandName::L     }, // 0x45 LD B,L
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::B,     OperandName::IndHL }, // 0x46 LD B,(HL)
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::B,     OperandName::A     }, // 0x47 LD B,A
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::C,     OperandName::B     }, // 0x48 LD C,B
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::C,     OperandName::C     }, // 0x49 LD C,C
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::C,     OperandName::D     }, // 0x4A LD C,D
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::C,     OperandName::E     }, // 0x4B LD C,E
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::C,     OperandName::H     }, // 0x4C LD C,H
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::C,     OperandName::L     }, // 0x4D LD C,L
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::C,     OperandName::IndHL }, // 0x4E LD C,(HL)
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::C,     OperandName::A     }, // 0x4F LD C,A
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::D,     OperandName::B     }, // 0x50 LD D,B
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::D,     OperandName::C     }, // 0x51 LD D,C
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::D,     OperandName::D     }, // 0x52 LD D,D
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::D,     OperandName::E     }, // 0x53 LD D,E
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::D,     OperandName::H     }, // 0x54 LD D,H
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::D,     OperandName::L     }, // 0x55 LD D,L
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::D,     OperandName::IndHL }, // 0x56 LD D,(HL)
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::D,     OperandName::A     }, // 0x57 LD D,A
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::E,     OperandName::B     }, // 0x58 LD E,B
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::E,     OperandName::C     }, // 0x59 LD E,C
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::E,     OperandName::D     }, // 0x5A LD E,D
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::E,     OperandName::E     }, // 0x5B LD E,E
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::E,     OperandName::H     }, // 0x5C LD E,H
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::E,     OperandName::L     }, // 0x5D LD E,L
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::E,     OperandName::IndHL }, // 0x5E LD E,(HL)
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::E,     OperandName::A     }, // 0x5F LD E,A
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::H,     OperandName::B     }, // 0x60 LD H,B
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::H,     OperandName::C     }, // 0x61 LD H,C
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::H,     OperandName::D     }, // 0x62 LD H,D
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::H,     OperandName::E     }, // 0x63 LD H,E
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::H,     OperandName::H     }, // 0x64 LD H,H
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::H,     OperandName::L     }, // 0x65 LD H,L
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::H,     OperandName::IndHL }, // 0x66 LD H,(HL)
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::H,     OperandName::A     }, // 0x67 LD H,A
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::L,     OperandName::B     }, // 0x68 LD L,B
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::L,     OperandName::C     }, // 0x69 LD L,C
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::L,     OperandName::D     }, // 0x6A LD L,D
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::L,     OperandName::E     }, // 0x6B LD L,E
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::L,     OperandName::H     }, // 0x6C LD L,H
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::L,     OperandName::L     }, // 0x6D LD L,L
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::L,     OperandName::IndHL }, // 0x6E LD L,(HL)
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::L,     OperandName::A     }, // 0x6F LD L,A
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x70
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::A,     OperandName::B     }, // 0x78 LD A,B
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::A,     OperandName::C     }, // 0x79 LD A,C
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::A,     OperandName::D     }, // 0x7A LD A,D
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::A,     OperandName::E     }, // 0x7B LD A,E
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::A,     OperandName::H     }, // 0x7C LD A,H
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::A,     OperandName::L     }, // 0x7D LD A,L
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::A,     OperandName::IndHL }, // 0x7E LD A,(HL)
    { InstructionName::LD,  OperatorType::Trivial,     OperandName::A,     OperandName::A     }, // 0x7F LD A,A
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x80
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0x90
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0xA0
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::XOR, OperatorType::Trivial,     OperandName::A,     OperandName::None  }, // 0xAF XOR A
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // B0
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // C0
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::JP,  OperatorType::Address,     OperandName::$,     OperandName::None  }, // 0xC3 JP nnnn
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0xD0
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::OUT, OperatorType::Direct8Bit,  OperandName::Ind$,  OperandName::A     }, // 0xD3
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // E0
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // F0
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::DI,  OperatorType::Trivial,     OperandName::None,  OperandName::None  }, // 0xF3 DI
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
    { InstructionName::INV, OperatorType::Trivial,     OperandName::None,  OperandName::None  },
};

static const InstructionTable OperatorsPrefixED = {
};
static const InstructionTable OperatorsPrefixDD = {
};
static const InstructionTable OperatorsPrefixFD = {
};
static const InstructionTable OperatorsPrefixCB = {
};
static const InstructionTable OperatorsPrefixDDCB = {
};
static const InstructionTable OperatorsPrefixFDCB = {
};

static LookupTable DisassemblyTable = {
    { InstructionPrefixDDFD::None, {
        { InstructionPrefixEDCB::None, OperatorsStandard },
        { InstructionPrefixEDCB::ED, OperatorsPrefixED },
        { InstructionPrefixEDCB::CB, OperatorsPrefixCB },
    } },
    { InstructionPrefixDDFD::DD, {
        { InstructionPrefixEDCB::None, OperatorsPrefixDD },
        { InstructionPrefixEDCB::ED, OperatorsPrefixED },
        { InstructionPrefixEDCB::CB, OperatorsPrefixDDCB },
    } },
    { InstructionPrefixDDFD::FD, {
        { InstructionPrefixEDCB::None, OperatorsPrefixFD },
        { InstructionPrefixEDCB::ED, OperatorsPrefixED },
        { InstructionPrefixEDCB::CB, OperatorsPrefixFDCB },
    } },
};

Z80Disassembler *Z80Disassembler::m_instance{};

Z80Disassembler::Z80Disassembler(MemorySpace& memory)
    : m_memory{ memory }
    , m_instructionOrigin{}
    , m_currentLocation{}
{
    m_instance = this;
}

Z80Disassembler *Z80Disassembler::GetInstance()
{
    return m_instance;
}
    
bool Z80Disassembler::DisassembleInstruction(uint16_t address, uint8_t instructionSize, std::string &mnemonic)
{
    m_instructionOrigin = address;
    auto result = DecodeInstruction(mnemonic);
    if (!result)
        TRACE_ERROR("Cannot decode instruction");
    instructionSize = static_cast<uint8_t>(m_currentLocation - m_instructionOrigin);
    return result;
}

bool Z80Disassembler::DecodeInstruction(std::string &mnemonic)
{
    InstructionPrefixDDFD prefixDDFD = InstructionPrefixDDFD::None;
    InstructionPrefixEDCB prefixEDCB = InstructionPrefixEDCB::None;
    uint8_t displacement{};
    m_currentLocation = m_instructionOrigin;
    auto opcode = GetInstructionByte();
    if (opcode == 0xDD)
    {
        prefixDDFD = InstructionPrefixDDFD::DD;
        opcode = GetInstructionByte();
    }
    else if (opcode == 0xFD)
    {
        prefixDDFD = InstructionPrefixDDFD::FD;
        opcode = GetInstructionByte();
    }
    if (opcode == 0xED)
    {
        prefixEDCB = InstructionPrefixEDCB::ED;
        opcode = GetInstructionByte();
    }
    else if (opcode == 0xCB)
    {
        prefixEDCB = InstructionPrefixEDCB::CB;
        opcode = GetInstructionByte();
    }
    // For DDCB/FDCB that was actually the displacement, opcode is the following byte
    if ((prefixDDFD != InstructionPrefixDDFD::None) && (prefixEDCB == InstructionPrefixEDCB::CB))
    {
        displacement = opcode;
        opcode = GetInstructionByte();
    }
    auto instructionTable = DisassemblyTable[prefixDDFD][prefixEDCB];
    if (instructionTable.size() < opcode)
    {
        TRACE_ERROR("Cannot lookup opcode, table not complete");
        mnemonic = "???";
        return false;
    }
    auto instructionDefinition = instructionTable[opcode];

    BuildMnemonic(instructionDefinition, mnemonic);
    return true;
}

uint8_t Z80Disassembler::GetInstructionByte()
{
    uint8_t value{};
    m_memory.Read8(m_currentLocation++, value);
    return value;
}

std::string Z80Disassembler::SerializeOperand(const InstructionDefinition &def, int operandIndex)
{
    std::string str;
    auto operand = (operandIndex == 0) ? def.operand1 : def.operand2;
    if (operand != OperandName::None)
    {
        auto operandStr = serialization::Serialize(operand);
        const char *pattern = "$";
        if (operandStr.find(pattern) != std::string::npos)
        {
            operandStr.replace(operandStr.find(pattern) + 1, strlen(pattern) - 1, OperatorTypeHandlerLookup.at(def.operatorType)());
        }
        str = operandStr;
    }
    return str;
}

void Z80Disassembler::BuildMnemonic(const InstructionDefinition &def, std::string &mnemonic)
{
    mnemonic = serialization::Serialize(def.name);
    if (def.operand1 != OperandName::None)
    {
        mnemonic += " " + SerializeOperand(def, 0);
    }
    if (def.operand2 != OperandName::None)
    {
        mnemonic += "," + SerializeOperand(def, 1);
    }
}
