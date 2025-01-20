#include "App.h"

#include "SDL3CPP/Rect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"
#include <iostream>

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

    // Load default surface
    stretchedSurface = LoadSurface(std::filesystem::path(IMAGE_DIR) / "stretch.bmp");
    if (stretchedSurface.IsEmpty())
    {
        std::cout << "Failed to load image!\n";
        success = false;
    }

    return success;
}

Surface App::LoadSurface(const std::filesystem::path &path)
{
    try
    {
        // Load image at specified path
        Surface loadedSurface = GetSDLImage().Load(path);

        // Convert surface to screen format
        Surface optimizedSurface = loadedSurface.Convert(screenSurface.GetFormatCode());
        return optimizedSurface;
    }
    catch (std::exception &e)
    {
        std::cout << "Cannot load image " << path << ":" << e.what() << std::endl;
    }

    return Surface();
}

void App::Close()
{
}

void App::BlitImageToScreen()
{
	//Apply the image stretched
	Rect stretchRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	stretchedSurface.BlitScaled(NullOpt, screenSurface, stretchRect, SDL_ScaleMode::SDL_SCALEMODE_LINEAR);
}

void App::UpdateWindowSurface()
{
    window.UpdateSurface();
}
