//------------------------------------------------------------------------------
// Copyright   : Copyright(c) 2024 Rene Barto
//
// File        : TraceCategory.h
//
// Namespace   : tracing
//
// Class       : TraceCategory
//
// Description :
//
//------------------------------------------------------------------------------

#pragma once

#include <functional>
#include <string>
#include <vector>

namespace tracing {

enum class TraceCategory : uint32_t
{
    Cat80000000          = 0x80000000u,
    Cat40000000          = 0x40000000u,
    Cat20000000          = 0x20000000u,
    Cat10000000          = 0x10000000u,
    Cat08000000          = 0x08000000u,
    Cat04000000          = 0x04000000u,
    Cat02000000          = 0x02000000u,
    Cat01000000          = 0x01000000u,
    Cat00800000          = 0x00800000u,
    Cat00400000          = 0x00400000u,
    Cat00200000          = 0x00200000u,
    Cat00100000          = 0x00100000u,
    Cat00080000          = 0x00080000u,
    Cat00040000          = 0x00040000u,
    Cat00020000          = 0x00020000u,
    Cat00010000          = 0x00010000u,
    Cat00008000          = 0x00008000u,
    Cat00004000          = 0x00004000u,
    Cat00002000          = 0x00002000u,
    Cat00001000          = 0x00001000u,
    Cat00000800          = 0x00000800u,
    Cat00000400          = 0x00000400u,
    Cat00000200          = 0x00000200u,
    Cat00000100          = 0x00000100u,
    Cat00000080          = 0x00000080u,
    FunctionEnter        = 0x00000040u,
    FunctionLeave        = 0x00000020u,
    Debug                = 0x00000010u,
    Information          = 0x00000008u,
    Warning              = 0x00000004u,
    Error                = 0x00000002u,
    Fatal                = 0x00000001u,
    None                 = 0x00000000u,
    All                  = 0xFFFFFFFFu,
};

std::ostream& operator << (std::ostream& stream, const TraceCategory& value);

std::vector<TraceCategory> EnumTraceCategories();

} // namespace tracing
