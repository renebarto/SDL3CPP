#include "Application.h"

#include <ostream>
#include "tracing/ScopedTracing.h"

using namespace tracing;

Application::Application()
    : m_savedTraceFilter{}
    , m_model{}
    , m_view{ m_model }
    , m_controller{ m_model, m_view }
{
    m_savedTraceFilter = Tracing::GetDefaultTraceFilter();
    Tracing::SetDefaultTraceFilter(TraceCategory::All);
    TRACE_DEBUG("Construct");
}

Application::~Application()
{
    TRACE_DEBUG("Destruct");
}

bool Application::Init(tracing::TraceWriter* traceWriter)
{
    if (traceWriter)
    {
        Tracing::SetTraceWriter(traceWriter);
    }
    SCOPEDTRACE(nullptr, nullptr);
    // Initialization flag
    return m_controller.Init();
}

void Application::SetDebug(bool on)
{
    m_controller.SetDebug(on);
}

bool Application::Run()
{
    SCOPEDTRACE(nullptr, nullptr);

    m_controller.SetDebug(true);
    return m_controller.Run();
}

void Application::Close()
{
}

