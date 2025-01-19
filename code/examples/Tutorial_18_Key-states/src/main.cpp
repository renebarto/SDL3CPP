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

        // double angle{};
        // SDL_FlipMode flipMode{ SDL_FLIP_NONE };
        // FPoint centerPoint = { (SCREEN_WIDTH - app.GetTextureSize().x) / 2.0F, (SCREEN_HEIGHT -
        // app.GetTextureSize().y) / 2.0F }; app.SetCenter(centerPoint);

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

                    default:
                        break;
                    }
                }
            }
            app.HandleKeyboard();

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
