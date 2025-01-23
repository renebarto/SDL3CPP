#include "Controller/Controller.h"

#include <filesystem>
#include <fstream>
#include <thread>

#include "Model/ZXSpectrum.h"
#include "View/MainView.h"

Controller::Controller(Model& model, MainView& view)
    : m_model{model}
    , m_mainView{view}
    , m_system{}
    , m_debug{}
    , m_quit{}
    , m_keyDownEvent{}
    , m_keyDownEventTrigger{}
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
        m_quit = false;
        result = m_system->Init();
    }
    if (result)
    {
        m_mainView.Init(m_system);
    }
    return result;
}

void Controller::SetDebug(bool on)
{
    m_debug = on;
}

bool Controller::Run()
{
    m_quit = false;
    return m_debug ? DoDebug() : DoRun();
}

void Controller::Stop()
{
    m_quit = true;
    m_keyDownEventTrigger.Set();
}

bool Controller::DoRun()
{
    while (!m_system->IsHalted() && !m_quit)
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
    while (!m_system->IsHalted() && !m_quit)
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
    m_keyDownEventTrigger.Wait();
    m_keyDownEventTrigger.Reset();
}

void Controller::OnKeyDown(const SDL3CPP::Event &e)
{
    if (e.Type() == SDL_EVENT_KEY_DOWN)
    {
        m_keyDownEvent = e;
        m_keyDownEventTrigger.Set();
    }
}