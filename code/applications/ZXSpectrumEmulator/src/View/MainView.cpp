#include "View/MainView.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include "tracing/Tracing.h"
#include "Model/Model.h"

using namespace tracing;

MainView::MainView(Model& model)
    : m_model{model}
    , m_system{}
{
    
}

void MainView::Init(std::shared_ptr<ISystem> system)
{
    m_system = system;
}

void MainView::ShowInstruction(const std::string& mnemonic)
{
    TRACE_INFO(mnemonic);
}

void MainView::ShowRegisters()
{
    TRACE_INFO(m_system->DumpRegisters());
}

void MainView::ShowCPUClock()
{
    auto cpuClock = m_system->GetCPUClock();
    auto cpuClockFreq = m_system->GetCPUClockFreq();
    std::ostringstream stream;
    double timeSecs = static_cast<double>(cpuClock) / static_cast<double>(cpuClockFreq);
    stream << "Clock: " << cpuClock << " = " << std::fixed << std::setprecision(9) << timeSecs;
    TRACE_INFO(stream.str());
}
