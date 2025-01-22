#include "Model/Z80.h"

#include <algorithm>
#include "tracing/Tracing.h"

static void HandlOpcodeNOP()
{
    Z80 *instance = Z80::GetInstance();
    instance->IncrementCPUClock(4);
}

static void HandleOpcodeLD_B_NN()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint8_t operand = instance->ReadByte();
    regs.Reg[RegisterIndex::B] = operand;
    instance->IncrementCPUClock(7);
}

static void HandleOpcodeLD_C_NN()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint8_t operand = instance->ReadByte();
    regs.Reg[RegisterIndex::C] = operand;
    instance->IncrementCPUClock(7);
}

static void HandleOpcodeLD_DE_nn()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint16_t operand = instance->ReadWord();
    regs.SetDE(operand);
    instance->IncrementCPUClock(10);
}

static void HandleOpcodeLD_D_NN()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint8_t operand = instance->ReadByte();
    regs.Reg[RegisterIndex::D] = operand;
    instance->IncrementCPUClock(7);
}

static void HandleOpcodeLD_E_NN()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint8_t operand = instance->ReadByte();
    regs.Reg[RegisterIndex::E] = operand;
    instance->IncrementCPUClock(7);
}

static void HandleOpcodeLD_H_NN()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint8_t operand = instance->ReadByte();
    regs.Reg[RegisterIndex::H] = operand;
    instance->IncrementCPUClock(7);
}

static void HandleOpcodeLD_L_NN()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint8_t operand = instance->ReadByte();
    regs.Reg[RegisterIndex::L] = operand;
    instance->IncrementCPUClock(7);
}

static void HandleOpcodeLD_A_NN()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint8_t operand = instance->ReadByte();
    regs.Reg[RegisterIndex::A] = operand;
    instance->IncrementCPUClock(7);
}

static void HandleOpcodeLD_B_r()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.Reg[RegisterIndex::B] = regs.Reg[instance->GetOpcode() & 0x07];
    instance->IncrementCPUClock(4);
}

static void HandleOpcodeLD_C_r()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.Reg[RegisterIndex::C] = regs.Reg[instance->GetOpcode() & 0x07];
    instance->IncrementCPUClock(4);
}

static void HandleOpcodeLD_D_r()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.Reg[RegisterIndex::D] = regs.Reg[instance->GetOpcode() & 0x07];
    instance->IncrementCPUClock(4);
}

static void HandleOpcodeLD_E_r()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.Reg[RegisterIndex::E] = regs.Reg[instance->GetOpcode() & 0x07];
    instance->IncrementCPUClock(4);
}

static void HandleOpcodeLD_H_r()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.Reg[RegisterIndex::H] = regs.Reg[instance->GetOpcode() & 0x07];
    instance->IncrementCPUClock(4);
}

static void HandleOpcodeLD_L_r()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.Reg[RegisterIndex::L] = regs.Reg[instance->GetOpcode() & 0x07];
    instance->IncrementCPUClock(4);
}

static void HandleOpcodeLD_A_r()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.Reg[RegisterIndex::A] = regs.Reg[instance->GetOpcode() & 0x07];
    instance->IncrementCPUClock(4);
}

static void HandleOpcodeXOR_r()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.XOR(RegisterIndex::A, static_cast<RegisterIndex>(instance->GetOpcode() & 0x07), RegisterIndex::A);

    instance->IncrementCPUClock(4);
}

static void HandleOpcodeJP_NNNN()
{
    Z80 *instance = Z80::GetInstance();
    uint16_t address = instance->ReadWord();
    auto &regs = instance->GetRegisters();
    regs.SetPC(address);
    instance->IncrementCPUClock(10);
}

static void HandleOpcodeOUT_IndNN_A()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    uint8_t operand = instance->ReadByte();
    instance->Out(operand, regs.Reg[RegisterIndex::A]);
}

static void HandlOpcodeDI()
{
    Z80 *instance = Z80::GetInstance();
    auto &regs = instance->GetRegisters();
    regs.IFF1 = regs.IFF2 = false;
    regs.IntLock = true;
    instance->IncrementCPUClock(4);
}

#pragma warning(disable: 4365)
#pragma warning(disable: 4242)
#pragma warning(disable: 4244)
const Z80::OpcodeFuncionLookup Z80::OpcodeLookup = {
    { 0x00, HandlOpcodeNOP},
    { 0x01, nullptr }, // ei_ld_BC_NN,
    { 0x02, nullptr }, // ei_ld_iBC_A,
    { 0x03, nullptr }, // ei_inc_BC,
    { 0x04, nullptr }, // ei_inc_B,
    { 0x05, nullptr }, // ei_dec_B,
    { 0x06, HandleOpcodeLD_B_NN },
    { 0x07, nullptr }, // ei_rlca,
    { 0x08, nullptr }, // ei_ex_AF_xAF,
    { 0x09, nullptr }, // ei_add_HL_BC,
    { 0x0A, nullptr }, // ei_ld_A_iBC,
    { 0x0B, nullptr }, // ei_dec_BC,
    { 0x0C, nullptr }, // ei_inc_C,
    { 0x0D, nullptr }, // ei_dec_C,
    { 0x0E, HandleOpcodeLD_C_NN },
    { 0x0F, nullptr }, // ei_rrca,
    { 0x10, nullptr }, // ei_djnz,
    { 0x11, HandleOpcodeLD_DE_nn},
    { 0x12, nullptr }, // ei_ld_iDE_A,
    { 0x13, nullptr }, // ei_inc_DE,
    { 0x14, nullptr }, // ei_inc_D,
    { 0x15, nullptr }, // ei_dec_D,
    { 0x16, HandleOpcodeLD_D_NN },
    { 0x17, nullptr }, // ei_rla,
    { 0x18, nullptr }, // ei_jr_N,
    { 0x19, nullptr }, // ei_add_HL_DE,
    { 0x1A, nullptr }, // ei_ld_A_iDE,
    { 0x1B, nullptr }, // ei_dec_DE,
    { 0x1C, nullptr }, // ei_inc_E,
    { 0x1D, nullptr }, // ei_dec_E,
    { 0x1E, HandleOpcodeLD_E_NN },
    { 0x1F, nullptr }, // ei_rra,
    { 0x20, nullptr }, // ei_jr_NZ_N,
    { 0x21, nullptr }, // ei_ld_HL_NN,
    { 0x22, nullptr }, // ei_ld_iNN_HL,
    { 0x23, nullptr }, // ei_inc_HL,
    { 0x24, nullptr }, // ei_inc_H,
    { 0x25, nullptr }, // ei_dec_H,
    { 0x26, HandleOpcodeLD_H_NN },
    { 0x27, nullptr }, // ei_daa,
    { 0x28, nullptr }, // ei_jr_Z_N, // 0x28
    { 0x29, nullptr }, // ei_add_HL_HL,
    { 0x2A, nullptr }, // ei_ld_HL_iNN,
    { 0x2B, nullptr }, // ei_dec_HL,
    { 0x2C, nullptr }, // ei_inc_L, // 0x2C
    { 0x2D, nullptr }, // ei_dec_L,
    { 0x2E, HandleOpcodeLD_L_NN },
    { 0x2F, nullptr }, // ei_cpl,
    { 0x30, nullptr }, // ei_jr_NC_N, // 0x30
    { 0x31, nullptr }, // ei_ld_SP_NN,
    { 0x32, nullptr }, // ei_ld_iNN_A,
    { 0x33, nullptr }, // ei_inc_SP,
    { 0x34, nullptr }, // ei_inc_iHL, // 0x34
    { 0x35, nullptr }, // ei_dec_iHL,
    { 0x36, nullptr }, // ei_ld_iHL_N,
    { 0x37, nullptr }, // ei_scf,
    { 0x38, nullptr }, // ei_jr_C_N, // 0x38
    { 0x39, nullptr }, // ei_add_HL_SP,
    { 0x3A, nullptr }, // ei_ld_A_iNN,
    { 0x3B, nullptr }, // ei_dec_SP,
    { 0x3C, nullptr }, // ei_inc_A, // 0x3C
    { 0x3D, nullptr }, // ei_dec_A,
    { 0x3E, HandleOpcodeLD_A_NN },
    { 0x3F, nullptr }, // ei_ccf,
    { 0x40, HandleOpcodeLD_B_r }, // 0x40
    { 0x41, HandleOpcodeLD_B_r }, // 0x41
    { 0x42, HandleOpcodeLD_B_r }, // 0x42
    { 0x43, HandleOpcodeLD_B_r }, // 0x43
    { 0x44, HandleOpcodeLD_B_r }, // 0x44
    { 0x45, HandleOpcodeLD_B_r }, // 0x45
    { 0x46, nullptr }, // ei_ld_B_iHL,
    { 0x47, HandleOpcodeLD_B_r }, // 0x47
    { 0x48, HandleOpcodeLD_C_r }, // 0x48
    { 0x49, HandleOpcodeLD_C_r }, // 0x49
    { 0x4A, HandleOpcodeLD_C_r }, // 0x4A
    { 0x4B, HandleOpcodeLD_C_r }, // 0x4B
    { 0x4C, HandleOpcodeLD_C_r }, // 0x4C
    { 0x4D, HandleOpcodeLD_C_r }, // 0x4D
    { 0x4E, nullptr }, // ei_ld_C_iHL,
    { 0x4F, HandleOpcodeLD_C_r }, // 0x4F
    { 0x50, HandleOpcodeLD_D_r }, // 0x50
    { 0x51, HandleOpcodeLD_D_r }, // 0x51
    { 0x52, HandleOpcodeLD_D_r }, // 0x52
    { 0x53, HandleOpcodeLD_D_r }, // 0x53
    { 0x54, HandleOpcodeLD_D_r }, // 0x54
    { 0x55, HandleOpcodeLD_D_r }, // 0x55
    { 0x56, nullptr }, // ei_ld_D_iHL,
    { 0x57, HandleOpcodeLD_D_r }, // 0x57
    { 0x58, HandleOpcodeLD_E_r }, // 0x58
    { 0x59, HandleOpcodeLD_E_r }, // 0x59
    { 0x5A, HandleOpcodeLD_E_r }, // 0x5A
    { 0x5B, HandleOpcodeLD_E_r }, // 0x5B
    { 0x5C, HandleOpcodeLD_E_r }, // 0x5C
    { 0x5D, HandleOpcodeLD_E_r }, // 0x5D
    { 0x5E, nullptr }, // ei_ld_E_iHL,
    { 0x5F, HandleOpcodeLD_E_r }, // 0x5F
    { 0x60, HandleOpcodeLD_H_r }, // 0x60
    { 0x61, HandleOpcodeLD_H_r }, // 0x61
    { 0x62, HandleOpcodeLD_H_r }, // 0x62
    { 0x63, HandleOpcodeLD_H_r }, // 0x63
    { 0x64, HandleOpcodeLD_H_r }, // 0x64
    { 0x65, HandleOpcodeLD_H_r }, // 0x65
    { 0x66, nullptr }, // ei_ld_H_iHL,
    { 0x67, HandleOpcodeLD_H_r }, // 0x67
    { 0x68, HandleOpcodeLD_L_r }, // 0x68
    { 0x69, HandleOpcodeLD_L_r }, // 0x69
    { 0x6A, HandleOpcodeLD_L_r }, // 0x6A
    { 0x6B, HandleOpcodeLD_L_r }, // 0x6B
    { 0x6C, HandleOpcodeLD_L_r }, // 0x6C
    { 0x6D, HandleOpcodeLD_L_r }, // 0x6D
    { 0x6E, nullptr }, // ei_ld_L_iHL,
    { 0x6F, HandleOpcodeLD_L_r }, // 0x6F
    { 0x70, nullptr }, // ei_ld_iHL_r, // 0x70
    { 0x71, nullptr }, // ei_ld_iHL_r,
    { 0x72, nullptr }, // ei_ld_iHL_r,
    { 0x73, nullptr }, // ei_ld_iHL_r,
    { 0x74, nullptr }, // ei_ld_iHL_r, // 0x74
    { 0x75, nullptr }, // ei_ld_iHL_r,
    { 0x76, nullptr }, // ei_halt,
    { 0x77, nullptr }, // ei_ld_iHL_r,
    { 0x78, HandleOpcodeLD_A_r }, // 0x78
    { 0x79, HandleOpcodeLD_A_r }, // 0x79
    { 0x7A, HandleOpcodeLD_A_r }, // 0x7A
    { 0x7B, HandleOpcodeLD_A_r }, // 0x7B
    { 0x7C, HandleOpcodeLD_A_r }, // 0x7C
    { 0x7D, HandleOpcodeLD_A_r }, // 0x7D
    { 0x7E, nullptr }, // ei_ld_A_iHL,
    { 0x7F, HandleOpcodeLD_A_r }, // 0x7F
    { 0x80, nullptr }, // ei_add_A_r, //0x80
    { 0x81, nullptr }, // ei_add_A_r,
    { 0x82, nullptr }, // ei_add_A_r,
    { 0x83, nullptr }, // ei_add_A_r,
    { 0x84, nullptr }, // ei_add_A_r, //0x84
    { 0x85, nullptr }, // ei_add_A_r,
    { 0x86, nullptr }, // ei_add_A_iHL,
    { 0x87, nullptr }, // ei_add_A_r,
    { 0x88, nullptr }, // ei_adc_A_r, // 0x88
    { 0x89, nullptr }, // ei_adc_A_r,
    { 0x8A, nullptr }, // ei_adc_A_r,
    { 0x8B, nullptr }, // ei_adc_A_r,
    { 0x8C, nullptr }, // ei_adc_A_r, // 0x8C
    { 0x8D, nullptr }, // ei_adc_A_r,
    { 0x8E, nullptr }, // ei_adc_A_iHL,
    { 0x8F, nullptr }, // ei_adc_A_r,
    { 0x90, nullptr }, // ei_sub_r, // 0x90
    { 0x91, nullptr }, // ei_sub_r,
    { 0x92, nullptr }, // ei_sub_r,
    { 0x93, nullptr }, // ei_sub_r,
    { 0x94, nullptr }, // ei_sub_r, // 0x94
    { 0x95, nullptr }, // ei_sub_r,
    { 0x96, nullptr }, // ei_sub_iHL,
    { 0x97, nullptr }, // ei_sub_r,
    { 0x98, nullptr }, // ei_sbc_A_r, // 0x98
    { 0x99, nullptr }, // ei_sbc_A_r,
    { 0x9A, nullptr }, // ei_sbc_A_r,
    { 0x9B, nullptr }, // ei_sbc_A_r,
    { 0x9C, nullptr }, // ei_sbc_A_r, // 0x9C
    { 0x9D, nullptr }, // ei_sbc_A_r,
    { 0x9E, nullptr }, // ei_sbc_A_iHL,
    { 0x9F, nullptr }, // ei_sbc_A_r,
    { 0xA0, nullptr }, // ei_and_r, // 0xA0
    { 0xA1, nullptr }, // ei_and_r,
    { 0xA2, nullptr }, // ei_and_r,
    { 0xA3, nullptr }, // ei_and_r,
    { 0xA4, nullptr }, // ei_and_r, // 0xA4
    { 0xA5, nullptr }, // ei_and_r,
    { 0xA6, nullptr }, // ei_and_iHL,
    { 0xA7, nullptr }, // ei_and_r,
    { 0xA8, HandleOpcodeXOR_r },
    { 0xA9, HandleOpcodeXOR_r },
    { 0xAA, HandleOpcodeXOR_r },
    { 0xAB, HandleOpcodeXOR_r },
    { 0xAC, HandleOpcodeXOR_r },
    { 0xAD, HandleOpcodeXOR_r },
    { 0xAE, nullptr }, // ei_xor_iHL,
    { 0xAF, HandleOpcodeXOR_r },
    { 0xB0, nullptr }, // ei_or_r, // 0xB0
    { 0xB1, nullptr }, // ei_or_r,
    { 0xB2, nullptr }, // ei_or_r,
    { 0xB3, nullptr }, // ei_or_r,
    { 0xB4, nullptr }, // ei_or_r, // 0xB4
    { 0xB5, nullptr }, // ei_or_r,
    { 0xB6, nullptr }, // ei_or_iHL,
    { 0xB7, nullptr }, // ei_or_r,
    { 0xB8, nullptr }, // ei_cp_r, // 0xB8
    { 0xB9, nullptr }, // ei_cp_r,
    { 0xBA, nullptr }, // ei_cp_r,
    { 0xBB, nullptr }, // ei_cp_r,
    { 0xBC, nullptr }, // ei_cp_r, // 0xBC
    { 0xBD, nullptr }, // ei_cp_r,
    { 0xBE, nullptr }, // ei_cp_iHL,
    { 0xBF, nullptr }, // ei_cp_r,
    { 0xC0, nullptr }, // ei_ret_NZ, // 0xC0
    { 0xC1, nullptr }, // ei_pop_BC,
    { 0xC2, nullptr }, // ei_jp_NZ_NN,
    { 0xC3, HandleOpcodeJP_NNNN },
    { 0xC4, nullptr }, // ei_call_NZ_NN, // 0xC4
    { 0xC5, nullptr }, // ei_push_BC,
    { 0xC6, nullptr }, // ei_add_A_N,
    { 0xC7, nullptr }, // ei_rst_0,
    { 0xC8, nullptr }, // ei_ret_Z, // 0xC8
    { 0xC9, nullptr }, // ei_ret,
    { 0xCA, nullptr }, // ei_jp_Z_NN,
    { 0xCB, nullptr }, // 0, // 0xCB
    { 0xCC, nullptr }, // ei_call_Z_NN, // 0xCC
    { 0xCD, nullptr }, // ei_call_NN,
    { 0xCE, nullptr }, // ei_adc_A_N,
    { 0xCF, nullptr }, // ei_rst_8,
    { 0xD0, nullptr }, // ei_ret_NC, // 0xD0
    { 0xD1, nullptr }, // ei_pop_DE,
    { 0xD2, nullptr }, // ei_jp_NC_NN,
    { 0xD3, HandleOpcodeOUT_IndNN_A },
    { 0xD4, nullptr }, // ei_call_NC_NN, // 0xD4
    { 0xD5, nullptr }, // ei_push_DE,
    { 0xD6, nullptr }, // ei_sub_N,
    { 0xD7, nullptr }, // ei_rst_10,
    { 0xD8, nullptr }, // ei_ret_C, // 0xD8
    { 0xD9, nullptr }, // ei_exx,
    { 0xDA, nullptr }, // ei_jp_C_NN,
    { 0xDB, nullptr }, // ei_in_A_iN,
    { 0xDC, nullptr }, // ei_call_C_NN, // 0xDC
    { 0xDD, nullptr }, // Mi_dd, // 0xDD
    { 0xDE, nullptr }, // ei_sbc_A_N,
    { 0xDF, nullptr }, // ei_rst_18,
    { 0xE0, nullptr }, // ei_ret_PO, // 0xE0
    { 0xE1, nullptr }, // ei_pop_HL,
    { 0xE2, nullptr }, // ei_jp_PO_NN,
    { 0xE3, nullptr }, // ei_ex_iSP_HL,
    { 0xE4, nullptr }, // ei_call_PO_NN, // 0xE4
    { 0xE5, nullptr }, // ei_push_HL,
    { 0xE6, nullptr }, // ei_and_N,
    { 0xE7, nullptr }, // ei_rst_20,
    { 0xE8, nullptr }, // ei_ret_PE, // 0xE8
    { 0xE9, nullptr }, // ei_jp_HL,
    { 0xEA, nullptr }, // ei_jp_PE_NN,
    { 0xEB, nullptr }, // ei_ex_DE_HL,
    { 0xEC, nullptr }, // ei_call_PE_NN,// 0xEC
    { 0xED, nullptr }, // 0, // 0xED
    { 0xEE, nullptr }, // ei_xor_N,
    { 0xEF, nullptr }, // ei_rst_28,
    { 0xF0, nullptr }, // ei_ret_P, // 0xF0
    { 0xF1, nullptr }, // ei_pop_AF,
    { 0xF2, nullptr }, // ei_jp_P_NN,
    { 0xF3, HandlOpcodeDI },
    { 0xF4, nullptr }, // ei_call_P_NN, // 0xF4
    { 0xF5, nullptr }, // ei_push_AF,
    { 0xF6, nullptr }, // ei_or_N,
    { 0xF7, nullptr }, // ei_rst_30,
    { 0xF8, nullptr }, // ei_ret_M, // 0xF8
    { 0xF9, nullptr }, // ei_ld_SP_HL,
    { 0xFA, nullptr }, // ei_jp_M_NN,
    { 0xFB, nullptr }, // ei_ei,
    { 0xFC, nullptr }, // ei_call_M_NN, // 0xFC
    { 0xFD, nullptr }, // Mi_fd, // 0xFD
    { 0xFE, nullptr }, // ei_cp_N,
    { 0xFF, nullptr }, // ei_rst_38
};
#pragma warning(default: 4365)
#pragma warning(default: 4242)
#pragma warning(default: 4244)

Z80 *Z80::m_instance{};

Z80::Z80(uint64_t clockFreq)
    : m_cpuFreq{ clockFreq }
    , m_registers{}
    , m_memory{ 65535u }
    , m_rom{ m_memory, 0, 16384 }
    , m_ram{ m_memory, 16384, 49152 }
    , m_memoryMap{ 
        MemoryMappingSet<uint16_t>{ 
                { m_memory, m_rom.StartAddress(), m_rom.EndAddress() }, 
                { m_memory, m_ram.StartAddress(), m_ram.EndAddress()  }
            }
        }
    , m_videoBorder{}
    , m_ioMap{ 
        IOMappingSet<uint8_t>{ 
                { m_videoBorder, 0xFE, 0xFE }
            }
        }
    , m_opcode{}
    , m_disassembler{ m_memory }
    , m_cpuClock{}
{
    m_instance = this;
}

Z80 *Z80::GetInstance()
{
    return m_instance;
}

bool Z80::Init()
{
    return true;
}

void Z80::Reset()
{
    m_registers.Reset();
    m_cpuClock = {};
}

bool Z80::IsHalted()
{
    return false;
}

std::string Z80::DumpRegisters()
{
    return m_registers.Dump();
}

bool Z80::LoadROM(const ByteVector &romContents)
{
    if (romContents.size() > m_rom.Size())
        return false;
    m_memory.Load(m_rom.StartAddress(), std::min(m_rom.Size(), static_cast<uint16_t>(romContents.size())), romContents);
    return true;
}

bool Z80::ExecuteInstruction()
{
    m_opcode = ReadOpcodeByte();
    if (m_registers.Modifier == 0)
    {
        if (OpcodeLookup.at(m_opcode) != nullptr)
        {
            OpcodeLookup.at(m_opcode)();
            return true;
        }
        else
        {
            TRACE_FATAL("Cannot decode instruction");
        }
        return false;
    }
    return false;
}

bool Z80::Disassemble(std::string &mnemonic)
{
    uint8_t instructionSize{};
    bool result = m_disassembler.DisassembleInstruction(m_registers.PC, instructionSize, mnemonic);
    if (!result)
        TRACE_ERROR("Cannot disassemble instruction");
    return result;
}

void Z80::IncrementCPUClock(uint8_t increment)
{
    m_cpuClock += increment;
}

uint8_t Z80::ReadOpcodeByte()
{
    return ReadByte();
}

uint8_t Z80::ReadByte()
{
    uint8_t byte{};
    m_memoryMap.Read8(m_registers.PC, byte);
    m_registers.PC++;
    return byte;
}

uint16_t Z80::ReadWord()
{
    uint16_t word{};
    m_memoryMap.Read16(m_registers.PC, word);
    m_registers.PC += 2;
    return word;
}

void Z80::Out(uint8_t port, uint8_t value)
{
    m_ioMap.Write8(port, value);
}

uint64_t Z80::GetCPUClock()
{
    return m_cpuClock;
}

uint64_t Z80::GetCPUClockFreq()
{
    return m_cpuFreq;
}

uint8_t Z80::GetOpcode()
{
    return m_opcode;
}
