#include "App.h"

#include <iostream>
#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"

using namespace SDL3CPP;

// Screen dimension constants
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

App::App()
{
}

App::~App()
{
}

bool App::Init()
{
    // Initialization flag
    bool success = true;

    try
    {
        GetSDL(SDLInitFlags::Video);
        // Create window
        if (!window.Create("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0))
        {
            std::cout << "Window could not be created!: " << SDL_GetError() << std::endl;
            success = false;
        }
        screenSurface = std::move(Surface(window.GetSurface()));
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        success = false;
    }
    return success;
}

bool App::LoadMedia()
{
    // Loading success flag
    bool success = true;

    auto path = std::filesystem::path(IMAGE_DIR) / "x.bmp";
    try
    {
        // Load splash image
        xOut = GetSDLImage().Load(path);
    }
    catch (std::exception &e)
    {
        std::cout << "Cannot load image " << path << ":" << e.what() << std::endl;
        success = false;
    }

    return success;
}

void App::Close()
{
}

void App::BlitImageToScreen()
{
    xOut.Blit(NullOpt, screenSurface, NullOpt);
}

void App::UpdateWindowSurface()
{
    window.UpdateSurface();
}
