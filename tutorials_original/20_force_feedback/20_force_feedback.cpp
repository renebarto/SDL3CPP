/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, math, and strings
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path );
        
        #if defined(SDL_TTF_MAJOR_VERSION)
        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
        #endif

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void render( int x, int y, SDL_FRect* clip = NULL, double angle = 0.0, SDL_FPoint* center = NULL, SDL_FlipMode flip = SDL_FLIP_NONE );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene texture
LTexture gSplashTexture;

//Game controller handler with force feedback
SDL_Gamepad* gGameController = NULL;

//Joystick handler with haptic
SDL_Joystick* gJoystick = NULL;
SDL_Haptic* gJoyHaptic = NULL;

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetSurfaceColorKey( loadedSurface, true, SDL_MapSurfaceRGB( loadedSurface, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_DestroySurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            SDL_Log( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        SDL_Log( "Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError() );
    }

    
    //Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}
        
void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_FRect* clip, double angle, SDL_FPoint* center, SDL_FlipMode flip )
{
    //Set rendering space and render to screen
    SDL_FRect renderQuad = { (float)x, (float)y, (float)mWidth, (float)mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderTextureRotated( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
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
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( !SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMEPAD ) )
    {
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Check for joysticks
		SDL_JoystickID joystickID = 0;
		SDL_JoystickID *joysticks = SDL_GetJoysticks( NULL );
		if( joysticks )
		{
			joystickID = joysticks[ 0 ];
			SDL_free( joysticks );
		}
        if( joystickID == 0 )
        {
            SDL_Log( "Warning: No joysticks connected!\n" );
        }
        else
        {
            //Check if first joystick is game controller interface compatible
            if( !SDL_IsGamepad( joystickID ) )
            {
                SDL_Log( "Warning: Joystick is not game controller interface compatible! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Open game controller and check if it supports rumble
                gGameController = SDL_OpenGamepad( joystickID );
                if( !SDL_GetBooleanProperty( SDL_GetGamepadProperties( gGameController ), SDL_PROP_GAMEPAD_CAP_RUMBLE_BOOLEAN, false ) )
                {
                    SDL_Log( "Warning: Game controller does not have rumble! SDL Error: %s\n", SDL_GetError() );
                }
            }

            //Load joystick if game controller could not be loaded
            if( gGameController == NULL )
            {
                //Open first joystick
                gJoystick = SDL_OpenJoystick( joystickID );
                if( gJoystick == NULL )
                {
                    SDL_Log( "Warning: Unable to open joystick! SDL Error: %s\n", SDL_GetError() );
                }
                else
                {
                    //Check if joystick supports haptic
					if( !SDL_GetBooleanProperty( SDL_GetJoystickProperties( gJoystick ), SDL_PROP_JOYSTICK_CAP_RUMBLE_BOOLEAN, false ) )
                    if( !SDL_IsJoystickHaptic( gJoystick ) )
                    {
                        SDL_Log( "Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError() );
                    }
                    else
                    {
                        //Get joystick haptic device
                        gJoyHaptic = SDL_OpenHapticFromJoystick( gJoystick );
                        if( gJoyHaptic == NULL )
                        {
                            SDL_Log( "Warning: Unable to get joystick haptics! SDL Error: %s\n", SDL_GetError() );
                        }
                        else
                        {
                            //Initialize rumble
                            if( !SDL_InitHapticRumble( gJoyHaptic ) )
                            {
                                SDL_Log( "Warning: Unable to initialize haptic rumble! SDL Error: %s\n", SDL_GetError() );
                            }
                        }
                    }
                }
            }
        }

        //Create window and renderer
        if( !SDL_CreateWindowAndRenderer( "SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gWindow, &gRenderer ) )
		{
			SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Enable vsync
			SDL_SetRenderVSync( gRenderer, 1 );

			//Initialize renderer color
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		}
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load press texture
    if( !gSplashTexture.loadFromFile( "splash.png" ) )
    {
        SDL_Log( "Failed to load splash texture!\n" );
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded images
    gSplashTexture.free();

    //Close game controller or joystick with haptics
    if( gGameController != NULL )
    {
        SDL_CloseGamepad( gGameController );
    }
    if( gJoyHaptic != NULL )
    {
        SDL_CloseHaptic( gJoyHaptic );
    }
    if( gJoystick != NULL )
    {
        SDL_CloseJoystick( gJoystick );
    }
    gGameController = NULL;
    gJoystick = NULL;
    gJoyHaptic = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        SDL_Log( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            SDL_Log( "Failed to load media!\n" );
        }
        else
        {    
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_EVENT_QUIT )
                    {
                        quit = true;
                    }
                    //Joystick button press
                    else if( e.type == SDL_EVENT_JOYSTICK_BUTTON_DOWN )
                    {
                        //Use game controller
                        if( gGameController != NULL )
                        {
                            //Play rumble at 75% strength for 500 milliseconds
                            if( !SDL_RumbleGamepad( gGameController, 0xFFFF * 3 / 4, 0xFFFF * 3 / 4, 500 ) )
                            {
                                SDL_Log( "Warning: Unable to play game contoller rumble! %s\n", SDL_GetError() );
                            }
                        }
                        //Use haptics
                        else if( gJoyHaptic != NULL )
                        {
                            //Play rumble at 75% strength for 500 milliseconds
                            if( !SDL_PlayHapticRumble( gJoyHaptic, 0.75, 500 ) )
                            {
                                SDL_Log( "Warning: Unable to play haptic rumble! %s\n", SDL_GetError() );
                            }
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render splash image
                gSplashTexture.render( 0, 0 );

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
