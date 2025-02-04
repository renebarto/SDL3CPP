#include "Controller/Controller.h"

#include <filesystem>
#include <fstream>
#include <thread>
#include "core/threading/Thread.h"
#include <SDL3/SDL_keycode.h>
#include "Model/ZXSpectrum.h"
#include "View/MainView.h"

class ZXSpectrumEmulatorThread
    : public core::threading::TypedReturnThread<bool>
{
private:
    Controller &m_controller;
    
public:
    ZXSpectrumEmulatorThread(Controller &controller)
        : core::threading::TypedReturnThread<bool>(std::bind(&Controller::Thread, &controller))
        , m_controller{ controller }
    {
    }
    void Kill()
    {
        m_controller.Stop();
    }
};

Controller::Controller(Model& model, MainView& view)
    : m_model{model}
    , m_mainView{view}
    , m_system{}
    , m_debug{}
{
}

bool Controller::Init()
{
    m_system  = std::make_shared<ZXSpectrum>();

    std::filesystem::path romDir{ ROM_DIR };
    std::filesystem::path romFilePath{(romDir / "spec48.rom").generic_string() };
    auto fileSize = std::filesystem::file_size(romFilePath);
    std::ifstream romFile{ romFilePath, std::ios::binary };
    if (!romFile)
        TRACE_FATAL("Can't open ROM file");
    std::vector<uint8_t> romContents;
    romContents.reserve(fileSize);
    romContents.resize(fileSize);
    romFile.read(reinterpret_cast<char *>(romContents.data()), static_cast<std::streamsize>(fileSize));

    bool result = m_system->LoadROM(romContents);

    if (result)
    {
        result = m_system->Init();
    }
    if (result)
    {
        result = m_mainView.Init(m_system);
    }
    return result;
}

void Controller::SetDebug(bool on)
{
    m_debug = on;
}

bool Controller::Run()
{
    ZXSpectrumEmulatorThread thread(*this);

    bool result = m_mainView.Run();
    thread.Kill();
    thread.WaitForDeath();
    if (!result)
        return false;
    return thread.GetResult();
}

bool Controller::Thread()
{
    return m_debug ? DoDebug() : DoRun();
}

bool Controller::DoRun()
{
    while (!m_system->IsHalted() && !m_mainView.Quit())
    {
        bool ok = m_system->ProcessInstruction();
        if (!ok)
            TRACE_ERROR("Instruction execution failed!");
        if (m_debug)
        {
            m_mainView.ShowRegisters();
        }
        if (!ok)
            return false;
    }
    return true;
}

bool Controller::DoDebug()
{
    TRACE_INFO("Initial state");
    m_mainView.ShowCPUClock();
    m_mainView.ShowRegisters();
    while (!m_system->IsHalted() && !m_mainView.Quit())
    {
        std::string mnemonic;
        bool ok = m_system->Disassemble(mnemonic);
        if (!ok)
            TRACE_ERROR("Instruction disassembly failed!");
        else
        {
            m_mainView.ShowInstruction(mnemonic);
            ok = m_system->ProcessInstruction();
            if (!ok)
                TRACE_ERROR("Instruction execution failed!");
        }
        m_mainView.ShowCPUClock();
        m_mainView.ShowRegisters();
        if (!ok)
            return false;
        WaitForInput();
    }
    return true;
}

void Controller::WaitForInput()
{
    m_mainView.WaitForInput();
}

void Controller::Stop()
{
    m_mainView.Stop();
}


