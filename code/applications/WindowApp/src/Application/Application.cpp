#include "Application/Application.h"

#include "tracing/ScopedTracing.h"

using namespace tracing;

Application::Application(tracing::TraceWriter* traceWriter)
    : m_savedTraceFilter{}
    , m_model{}
    , m_view{ m_model }
    , m_controller{ m_model, m_view }
{
    m_savedTraceFilter = Tracing::GetDefaultTraceFilter();
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    if (traceWriter)
    {
        Tracing::SetTraceWriter(traceWriter);
    }
    TRACE_DEBUG("Application::Application");
}

Application::~Application()
{
    TRACE_DEBUG("Application::~Application");
}

bool Application::Init()
{
    SCOPEDTRACE(nullptr, nullptr);
    return m_controller.Init();
}

bool Application::Run()
{
    SCOPEDTRACE(nullptr, nullptr);

    return m_controller.Run();
}

void Application::Quit()
{
    SCOPEDTRACE(nullptr, nullptr);
    m_controller.Stop();
}

