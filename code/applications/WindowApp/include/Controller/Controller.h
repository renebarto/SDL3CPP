#pragma once

#include "osal/synchronization/ManualEvent.h"
#include "SDL3CPP/Events.h"
#include "View/UIElement.h"

class Model;
class MainView;

class Controller
{
private:
    Model &m_model;
    MainView &m_mainView;
    bool m_quit;
    SDL3CPP::Event m_keyDownEvent;
    osal::ManualEvent m_keyDownEventTrigger;

public:
    Controller(Model &model, MainView &view);
    Controller(const Controller &) = delete;
    virtual ~Controller();

    Controller& operator =(const Controller &) = delete;
    Controller& operator =(Controller &&) = delete;

    bool Init();

    bool Run();
    bool Thread();
    bool DoRun();

    void HandleEvent(const SDL3CPP::Event &e);

    void OnMouseMove(GUI::UIElement &element, SDL3CPP::MouseMotionEvent &event);

    void WaitForInput();

    void Stop();
    bool Quit() const;
};