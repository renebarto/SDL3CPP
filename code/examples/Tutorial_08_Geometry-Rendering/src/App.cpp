#include "App.h"

#include "SDL3CPP/FRect.h"
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/SDLImage.h"
#include <iostream>
#include <ostream>

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
        // Create renderer for window
        renderer = Renderer(window);
        if (renderer.IsEmpty())
        {
            std::cout << "Renderer could not be created!: " << SDL_GetError() << std::endl;
            success = false;
        }
        // Initialize renderer color
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

Texture App::LoadTexture(const std::filesystem::path &path)
{
    try
    {
        // Load image at specified path
        Surface loadedSurface = GetSDLImage().Load(path);

        // Create texture from surface pixels
        Texture loadedTexture(renderer, loadedSurface);
        if (loadedTexture.IsEmpty())
        {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        return loadedTexture;
    }
    catch (std::exception &e)
    {
        std::cout << "Cannot load image " << path << ":" << e.what() << std::endl;
    }

    return Texture();
}

void App::Close()
{
}

void App::Render()
{
    // Clear screen
    renderer.SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.Clear();
    
    // Render red filled quad
    FRect fillRect{SCREEN_WIDTH / 4.0F, SCREEN_HEIGHT / 4.0F, SCREEN_WIDTH / 2.0F, SCREEN_HEIGHT / 2.0F};
    renderer.SetDrawColor(0xFF, 0x00, 0x00, 0xFF);
    renderer.FillRect(fillRect);

    // Render green outlined quad
    FRect outlineRect{SCREEN_WIDTH / 6.0F, SCREEN_HEIGHT / 6.0F, SCREEN_WIDTH * 2 / 3.0F, SCREEN_HEIGHT * 2 / 3.0F};
    renderer.SetDrawColor(0x00, 0xFF, 0x00, 0xFF);
    renderer.DrawRect(outlineRect);

    // Draw blue horizontal line
    renderer.SetDrawColor(0x00, 0x00, 0xFF, 0xFF);
    renderer.DrawLine(0, SCREEN_HEIGHT / 2.0F, SCREEN_WIDTH, SCREEN_HEIGHT / 2.0F);

    // Draw vertical line of yellow dots
    renderer.SetDrawColor(0xFF, 0xFF, 0x00, 0xFF);
    for (int i = 0; i < SCREEN_HEIGHT; i += 4)
    {
        renderer.DrawPoint(SCREEN_WIDTH / 2.0F, static_cast<float>(i));
    }

    // Update screen
    renderer.Present();
}
