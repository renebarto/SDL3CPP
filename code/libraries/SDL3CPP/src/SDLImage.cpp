#include "SDL3CPP/SDLImage.h"

#include <sstream>
#include <stdexcept>

#include <SDL3_Image/SDL_image.h>

#include "SDL3CPP/Surface.h"

namespace SDL3CPP {

SDLImage::SDLImage()
{
}

SDLImage::~SDLImage()
{
}

int SDLImage::GetInitFlags()
{
    return 0;//IMG_Init(0);
}

Surface SDLImage::Load(const std::filesystem::path &path)
{
    Surface surface(IMG_Load(path.string().c_str()));
    return surface;
}

SDLImage &GetSDLImage()
{
    static SDLImage instance;
    return instance;
}

} // namespace SDL3CPP
