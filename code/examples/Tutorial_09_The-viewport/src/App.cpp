#include "App.h"

#include "SDL3CPP/Hints.h"
#include "SDL3CPP/Rect.h"
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
        GetSDL(SDLInitFlags::Video);
        // Create window
        if (!window.Create("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0))
        {
            std::cout << "Window could not be created!: " << SDL_GetError() << std::endl;
            success = false;
        }
        // Create renderer for window
        renderer = Renderer(window, nullptr);
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

    // Load default surface
    texture = LoadTexture(std::filesystem::path(IMAGE_DIR) / "viewport.png");
    if (texture.IsEmpty())
    {
        std::cout << "Failed to load texture image!\n";
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

    // Top left corner viewport
    Rect topLeftViewport{0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    renderer.SetViewport(topLeftViewport);

    // Render texture to screen
    renderer.Copy(texture, NullOpt, NullOpt);

    // Top right viewport
    Rect topRightViewport{SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    renderer.SetViewport(topRightViewport);

    // Render texture to screen
    renderer.Copy(texture, NullOpt, NullOpt);

    // Bottom viewport
    Rect bottomViewport{ 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
    renderer.SetViewport(bottomViewport);

    // Render texture to screen
    renderer.Copy(texture, NullOpt, NullOpt);

    // Update screen
    renderer.Present();
}
