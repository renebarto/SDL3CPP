#include "Model/Model.h"

Model::Model()
{
}

const Z80Registers& Model::GetRegisters() const
{
    return m_registers;
}

bool Model::IsHalted() const
{
    return false;
}

void Model::DumpRegisters() const
{

}

void Model::PrintClockInfo() const
{

}
