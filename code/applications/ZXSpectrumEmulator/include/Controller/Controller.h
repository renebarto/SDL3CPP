#pragma once

#include "Model/ISystem.h"

class Model;
class MainView;

class Controller
{
private:
    Model &m_model;
    MainView &m_mainView;
    std::shared_ptr<ISystem> m_system;
    bool m_debug;

public:
    Controller(Model &model, MainView &view);
    Controller(const Controller &) = delete;

    Controller& operator =(const Controller &) = delete;
    Controller& operator =(Controller &&) = delete;

    bool Init();
    void SetDebug(bool on);

    bool Run();
    bool Thread();
    bool DoDebug();
    bool DoRun();

    void WaitForInput();
    void Stop();
};