#pragma once 

#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Texture.h"
#include "SDL3CPP/Window.h"

class App
{
private:
    // The window we'll be rendering to
    SDL3CPP::Window window;

    //The window renderer
    SDL3CPP::Renderer renderer;

    // The surface contained by the window
    SDL3CPP::Surface screenSurface;

    //Current displayed image
    SDL3CPP::Texture texture;

public:
    App();
    virtual ~App();

    // Starts up SDL and creates window
    bool Init();

    // Loads media
    bool LoadMedia();
    SDL3CPP::Surface LoadSurface(const std::filesystem::path &path);
    SDL3CPP::Texture LoadTexture(const std::filesystem::path &path);

    // Frees media and shuts down SDL
    void Close();

    void Render();
};

