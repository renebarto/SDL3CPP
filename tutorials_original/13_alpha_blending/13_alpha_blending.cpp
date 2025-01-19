/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// Using SDL, SDL_image, and strings
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Texture wrapper class
class LTexture
{
public:
    // Initializes variables
    LTexture();

    // Deallocates memory
    ~LTexture();

    // Loads image at specified path
    bool loadFromFile(std::string path);

    // Deallocates texture
    void free();

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Renders texture at given point
    void render(int x, int y, SDL_FRect *clip = NULL);

    // Gets image dimensions
    int getWidth();
    int getHeight();

private:
    // The actual hardware texture
    SDL_Texture *mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Scene textures
LTexture gModulatedTexture;
LTexture gBackgroundTexture;

LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    // Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        // Color key image
        SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    // Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    // Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    // Modulate texture rgb
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    // Set blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_FRect *clip)
{
    // Set rendering space and render to screen
    SDL_FRect renderQuad = {(float)x, (float)y, (float)mWidth, (float)mHeight};

    // Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderTexture(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window and renderer
        if (!SDL_CreateWindowAndRenderer("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gWindow, &gRenderer))
        {
            SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load front alpha texture
    if (!gModulatedTexture.loadFromFile("fadeout.png"))
    {
        SDL_Log("Failed to load front texture!\n");
        success = false;
    }
    else
    {
        // Set standard alpha blending
        gModulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }

    // Load background texture
    if (!gBackgroundTexture.loadFromFile("fadein.png"))
    {
        SDL_Log("Failed to load background texture!\n");
        success = false;
    }

    return success;
}

void close()
{
    // Free loaded images
    gModulatedTexture.free();
    gBackgroundTexture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *args[])
{
    // Start up SDL and create window
    if (!init())
    {
        SDL_Log("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            SDL_Log("Failed to load media!\n");
        }
        else
        {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Modulation component
            Uint8 a = 255;

            // While application is running
            while (!quit)
            {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_EVENT_QUIT)
                    {
                        quit = true;
                    }
                    // Handle key presses
                    else if (e.type == SDL_EVENT_KEY_DOWN)
                    {
                        // Increase alpha on w
                        if (e.key.key == SDLK_W)
                        {
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
                        }
                        // Decrease alpha on s
                        else if (e.key.key == SDLK_S)
                        {
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
                        }
                    }
                }

                // Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // Render background
                gBackgroundTexture.render(0, 0);

                // Render front blended
                gModulatedTexture.setAlpha(a);
                gModulatedTexture.render(0, 0);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}
