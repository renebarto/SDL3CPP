#pragma once 

#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Window.h"

class App
{
private:
    // The window we'll be rendering to
    SDL3CPP::Window window;

    // The surface contained by the window
    SDL3CPP::Surface screenSurface;

    // The image we will load and show on the screen
    SDL3CPP::Surface helloWorld;

public:
    App();
    virtual ~App();

    // Starts up SDL and creates window
    bool Init();

    // Loads media
    bool LoadMedia();

    // Frees media and shuts down SDL
    void Close();

    void BlitImageToScreen();
    void UpdateWindowSurface();
};

