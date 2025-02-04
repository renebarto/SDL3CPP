#pragma once 

#include "tracing/ConsoleTraceLineWriter.h"
#include "tracing/TraceWriter.h"
#include "tracing/Tracing.h"
#include "Controller/Controller.h"
#include "Model/Model.h"
#include "View/MainView.h"

class Application
{
private:
    tracing::CategorySet<tracing::TraceCategory> m_savedTraceFilter;

    Model m_model;
    MainView m_view;
    Controller m_controller;

public:
    Application();
    virtual ~Application();

    // Starts up SDL and creates window
    bool Init(tracing::TraceWriter* traceWriter);

    void SetDebug(bool on);

    bool Run();

    // Frees media and shuts down SDL
    void Close();
};

