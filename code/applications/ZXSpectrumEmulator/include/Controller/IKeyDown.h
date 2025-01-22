#pragma once

#include "SDL3CPP/Events.h"

class IKeyDown
{
public:
    virtual ~IKeyDown() = default;

    virtual void OnKeyDown(const SDL3CPP::Event &key) = 0;
};