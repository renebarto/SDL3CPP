#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include "App.h"
#include "SDL3CPP/Events.h"

using namespace SDL3CPP;

// Screen dimension constants
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 800;

int main(int /*argc*/, char * /*args*/[])
{
    try
    {
        App app;
        // Start up SDL and create window
        if (!app.Init(SCREEN_WIDTH, SCREEN_HEIGHT))
        {
            std::cout << "Failed to initialize!" << std::endl;
            return 1;
        }
        // Load media
        if (!app.LoadMedia())
        {
            std::cout << "Failed to load media!" << std::endl;
            return 1;
        }

        // Modulation components
        uint8_t r = 255;
        uint8_t g = 255;
        uint8_t b = 255;
        uint8_t a = 255;

        Event e;
        bool quit = false;
        while (quit == false)
        {
            while (Events::Poll(e))
            {
                // User requests quit
                if (e.Type() == SDL_EVENT_QUIT)
                {
                    quit = true;
                }
                // User presses a key
                else if (e.Type() == SDL_EVENT_KEY_DOWN)
                {
                    // Select surfaces based on key press
                    switch (e.Key())
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    // Increase red
                    case SDLK_Q:
                        r += 32;
                        break;

                    // Increase green
                    case SDLK_W:
                        g += 32;
                        break;

                    // Increase blue
                    case SDLK_E:
                        b += 32;
                        break;

                    // Decrease red
                    case SDLK_A:
                        r -= 32;
                        break;

                    // Decrease green
                    case SDLK_S:
                        g -= 32;
                        break;

                    // Decrease blue
                    case SDLK_D:
                        b -= 32;
                        break;

                    // Increase alpha
                    case SDLK_R:
                        // Cap if over 255
                        if (a + 32 > 255)
                        {
                            a = 255;
                        }
                        // Increment otherwise
                        else
                        {
                            a += 32;
                        }
                        break;

                    // Decrease alpha
                    case SDLK_F:
                        // Cap if below 0
                        if (a - 32 < 0)
                        {
                            a = 0;
                        }
                        // Decrement otherwise
                        else
                        {
                            a -= 32;
                        }
                        break;

                    default:
                        break;
                    }
                }
            }

            // Modulate and render texture
            app.SetColorAndAlpha(r, g, b, a);
            // Render the texture
            app.Render();
        }

        // Free resources and close SDL
        app.Close();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
