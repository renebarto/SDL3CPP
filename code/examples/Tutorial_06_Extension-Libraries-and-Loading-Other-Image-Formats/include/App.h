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

    //Current displayed image
    SDL3CPP::Surface stretchedSurface;

public:
    App();
    virtual ~App();

    // Starts up SDL and creates window
    bool Init();

    // Loads media
    bool LoadMedia();
    SDL3CPP::Surface LoadSurface(const std::filesystem::path &path);

    // Frees media and shuts down SDL
    void Close();

    void BlitImageToScreen();
    void UpdateWindowSurface();
};

