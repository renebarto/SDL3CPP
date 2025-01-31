#pragma once

#include "SDL3CPP/Config.h"

#include "SDL3CPP/SDL.h"
#include "SDL3CPP/Optional.h"

////////////////////////////////////////////////////////////
/// \defgroup audio Audio
///
/// \brief Audio device management and audio playback
///
////////////////////////////////////////////////////////////
//#include "SDL3CPP/AudioDevice.h"
//#include "SDL3CPP/AudioSpec.h"
//#include "SDL3CPP/Wav.h"

////////////////////////////////////////////////////////////
/// \defgroup graphics Graphics
///
/// \brief Graphics output
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \defgroup windows Window management
///
/// \brief Display and window management
///
/// \ingroup graphics
///
////////////////////////////////////////////////////////////
#include "SDL3CPP/Window.h"

////////////////////////////////////////////////////////////
/// \defgroup rendering 2D rendering
///
/// \brief 2D accelerated rendering
///
/// \ingroup graphics
///
////////////////////////////////////////////////////////////
//#include "SDL3CPP/Renderer.h"
#include "SDL3CPP/Surface.h"
//#include "SDL3CPP/Texture.h"
//#include "SDL3CPP/Color.h"

////////////////////////////////////////////////////////////
/// \defgroup geometry 2D geometry
///
/// \brief 2D rectangle and point functions
///
/// \ingroup graphics
///
////////////////////////////////////////////////////////////
#include "SDL3CPP/Rect.h"
#include "SDL3CPP/Point.h"

////////////////////////////////////////////////////////////
/// \defgroup io I/O abstraction
///
/// \brief Functions that extend file-like operations onto arbitrary
///        objects such as memory, streams, STL containers etc.
///
////////////////////////////////////////////////////////////
//#include "SDL3CPP/RWops.h"
//#include "SDL3CPP/ContainerRWops.h"
//#include "SDL3CPP/StreamRWops.h"

#ifdef SDL2_WITH_TTF

////////////////////////////////////////////////////////////
/// \defgroup ttf SDL_ttf
///
/// \brief Text rendering through SDL_ttf library
///
////////////////////////////////////////////////////////////
//#include "SDL3CPP/SDLTTF.h"
//#include "SDL3CPP/Font.h"

#endif

#ifdef SDL2_WITH_IMAGE

////////////////////////////////////////////////////////////
/// \defgroup image SDL_image
///
/// \brief Functions that are specific to SDL_image library
///
////////////////////////////////////////////////////////////

//#include "SDL3CPP/SDLImage.h"

#endif

#ifdef SDL2_WITH_MIXER
////////////////////////////////////////////////////////////
/// \defgroup mixer SDL_mixer
///
/// \brief Functions that are specific to SDL_mixer library
///
////////////////////////////////////////////////////////////
#include "SDL3CPP/Chunk.h"
#include "SDL3CPP/Mixer.h"
#include "SDL3CPP/Music.h"
#include "SDL3CPP/SDLMixer.h"

#endif
