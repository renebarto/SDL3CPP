#pragma once 

#include "utility/EnumBitSet.h"
#include "tracing/TraceCategory.h"
#include "tracing/TraceWriter.h"
#include "Controller/Controller.h"
#include "Model/Model.h"
#include "View/MainView.h"

class Application
{
private:
    utility::EnumBitSet<tracing::TraceCategory> m_savedTraceFilter;

    Model m_model;
    MainView m_view;
    Controller m_controller;

public:
    Application(tracing::TraceWriter* traceWriter);
    virtual ~Application();

    bool Init();

    bool Run();

    void Quit();
};

