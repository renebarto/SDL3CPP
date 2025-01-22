#pragma once

#include "Controller/IKeyDown.h"
#include "Model/ISystem.h"

class Model;
class MainView;

class Controller
    : public IKeyDown
{
private:
    Model &m_model;
    MainView &m_mainView;
    std::shared_ptr<ISystem> m_system;
    bool m_debug;
    bool m_quit;
    SDL3CPP::Event m_keyDownEvent;
    bool m_keyDownEventTrigger;

public:
    Controller(Model &model, MainView &view);
    Controller(const Controller &) = delete;

    Controller& operator =(const Controller &) = delete;
    Controller& operator =(Controller &&) = delete;

    bool Init();
    void SetDebug(bool on);

    bool Run();
    bool DoDebug();
    bool DoRun();
    void Stop();

    void WaitForInput();
    void OnKeyDown(const SDL3CPP::Event &e) override;
};