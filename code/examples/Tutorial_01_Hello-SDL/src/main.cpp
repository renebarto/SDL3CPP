#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL3/SDL.h>
#include "SDL3CPP/SDL.h"
#include "SDL3CPP/Rect.h"
#include "SDL3CPP/Surface.h"
#include "SDL3CPP/Window.h"

using namespace SDL3CPP;

// You must include the command line parameters for your main function to be recognized by SDL
int main(int /*argc*/, char* /*argv*/[])
{
    try
    {
        SDL sdl;

        Window window;

        // Create our window
        if (!window.Create("Example", 1280, 720, 0))
        {
            std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
            // End the program
            return 1;
        }
        Surface winSurface(window);

        // Fill the window with a white rectangle
        winSurface.FillRect(NullOpt, SDL_MapSurfaceRGB(winSurface.Get(), 255, 255, 255));

        // Update the window display
        window.UpdateSurface();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    
    // End the program
    return 0;
}
