#pragma once 

#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Window.h"

// Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

class App
{
private:
    // The window we'll be rendering to
    SDL3CPP::Window window;

    // The surface contained by the window
    SDL3CPP::Surface screenSurface;

    // The images that correspond to a keypress
    SDL3CPP::Surface keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

    // Current displayed image
    SDL3CPP::Surface *currentSurface = nullptr;

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

    void SelectCurrentImage(KeyPressSurfaces index);
    void BlitCurrentImageToScreen();
    void UpdateWindowSurface();
};

