#include "Model/ZXSpectrum.h"

#include <Windows.h>

void WaitForInput()
{
    while ((GetKeyState(VK_RETURN) & 0x8000) == 0);
    while ((GetKeyState(VK_RETURN) & 0x8000) != 0);
}

ZXSpectrum::ZXSpectrum()
    : m_cpu{ 3500000 }
{
}

bool ZXSpectrum::Init()
{
    Reset();
    m_cpu.Init();
    return true;
}

void ZXSpectrum::Reset()
{
    m_cpu.Reset();
}

bool ZXSpectrum::LoadROM(const ByteVector &romContents)
{
    return m_cpu.LoadROM(romContents);
}

bool ZXSpectrum::IsHalted()
{
    return m_cpu.IsHalted();
}

bool ZXSpectrum::Disassemble(std::string &mnemonic)
{
    return m_cpu.Disassemble(mnemonic);
}

bool ZXSpectrum::ProcessInstruction()
{
    return m_cpu.ExecuteInstruction();
}

std::string ZXSpectrum::DumpRegisters()
{
    return m_cpu.DumpRegisters();
}

uint64_t ZXSpectrum::GetCPUClock()
{
    return m_cpu.GetCPUClock();
}

uint64_t ZXSpectrum::GetCPUClockFreq()
{
    return m_cpu.GetCPUClockFreq();
}
