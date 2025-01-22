#pragma once

#include <memory>
#include <ostream>
#include "tracing/TraceCategory.h"
#include "Model/ISystem.h"

class Model;

class MainView
{
private:
    Model &m_model;
    std::shared_ptr<ISystem> m_system;

public:
    MainView(Model &model);
    MainView(const MainView &) = delete;

    MainView& operator =(const MainView &) = delete;
    MainView& operator =(MainView &&) = delete;

    void Init(std::shared_ptr<ISystem> system);

    void ShowInstruction(const std::string& mnemonic);
    void ShowRegisters();
    void ShowCPUClock();
};
