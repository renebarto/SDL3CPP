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
        GetSDL(SDL_INIT_VIDEO);
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
    keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = LoadSurface(std::filesystem::path(IMAGE_DIR) / "press.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT].IsEmpty())
    {
        std::cout << "Failed to load default image!\n";
        success = false;
    }

    // Load up surface
    keyPressSurfaces[KEY_PRESS_SURFACE_UP] = LoadSurface(std::filesystem::path(IMAGE_DIR) / "up.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_UP].IsEmpty())
    {
        std::cout << "Failed to load up image!\n";
        success = false;
    }

    // Load down surface
    keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = LoadSurface(std::filesystem::path(IMAGE_DIR) / "down.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_DOWN].IsEmpty())
    {
        std::cout << "Failed to load down image!\n";
        success = false;
    }

    // Load left surface
    keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = LoadSurface(std::filesystem::path(IMAGE_DIR) / "left.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_LEFT].IsEmpty())
    {
        std::cout << "Failed to load left image!\n";
        success = false;
    }

    // Load right surface
    keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = LoadSurface(std::filesystem::path(IMAGE_DIR) / "right.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT].IsEmpty())
    {
        std::cout << "Failed to load right image!\n";
        success = false;
    }

    return success;
}

Surface App::LoadSurface(const std::filesystem::path &path)
{
    try
    {
        // Load splash image
        return GetSDLImage().Load(path);
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

void App::SelectCurrentImage(KeyPressSurfaces index)
{
    currentSurface = &keyPressSurfaces[index];
}

void App::BlitCurrentImageToScreen()
{
    // Apply the current image
    currentSurface->Blit(NullOpt, screenSurface, NullOpt);
}

void App::UpdateWindowSurface()
{
    window.UpdateSurface();
}
