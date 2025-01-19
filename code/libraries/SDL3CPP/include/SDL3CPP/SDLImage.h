#pragma once

#include <filesystem>
#include <SDL3_Image/SDL_image.h>

namespace SDL3CPP {

class Surface;

extern uint32_t IMG_INIT_DEFAULT;

class SDLImage
{
  private:
    friend SDLImage &GetSDLImage();
    explicit SDLImage();

  public:
    SDLImage(const SDLImage &other) = delete;
    SDLImage(SDLImage &&other) = delete;

    virtual ~SDLImage();

    SDLImage &operator=(const SDLImage &other) = delete;
    SDLImage &operator=(SDLImage &&other) = delete;

    int GetInitFlags();

    Surface Load(const std::filesystem::path &path);
};

SDLImage &GetSDLImage();

} // namespace SDL3CPP
