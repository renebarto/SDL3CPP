#pragma once

namespace SDL3CPP {

enum class PixelFormat
{
    Unknown       = 0,
    Index1LSB     = 0x11100100u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_Index1, SDL_BITMAPORDER_4321, 0, 1, 0),
    Index1MSB     = 0x11200100u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_Index1, SDL_BITMAPORDER_1234, 0, 1, 0),
    Index2LSB     = 0x1c100200u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_Index2, SDL_BITMAPORDER_4321, 0, 2, 0),
    Index2MSB     = 0x1c200200u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_Index2, SDL_BITMAPORDER_1234, 0, 2, 0),
    Index4LSB     = 0x12100400u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_Index4, SDL_BITMAPORDER_4321, 0, 4, 0),
    Index4MSB     = 0x12200400u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_Index4, SDL_BITMAPORDER_1234, 0, 4, 0),
    Index8        = 0x13000801u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_Index8, 0, 0, 8, 1),
    RGB332        = 0x14110801u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED8, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_332, 8, 1),
    XRGB4444      = 0x15120c02u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_4444, 12, 2),
    XBGR4444      = 0x15520c02u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_4444, 12, 2),
    XRGB1555      = 0x15130f02u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_1555, 15, 2),
    XBGR1555      = 0x15530f02u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_1555, 15, 2),
    ARGB4444      = 0x15321002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ARGB, SDL_PACKEDLAYOUT_4444, 16, 2),
    RGBA4444      = 0x15421002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_RGBA, SDL_PACKEDLAYOUT_4444, 16, 2),
    ABGR4444      = 0x15721002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ABGR, SDL_PACKEDLAYOUT_4444, 16, 2),
    BGRA4444      = 0x15821002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_BGRA, SDL_PACKEDLAYOUT_4444, 16, 2),
    ARGB1555      = 0x15331002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ARGB, SDL_PACKEDLAYOUT_1555, 16, 2),
    RGBA5551      = 0x15441002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_RGBA, SDL_PACKEDLAYOUT_5551, 16, 2),
    ABGR1555      = 0x15731002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ABGR, SDL_PACKEDLAYOUT_1555, 16, 2),
    BGRA5551      = 0x15841002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_BGRA, SDL_PACKEDLAYOUT_5551, 16, 2),
    RGB565        = 0x15151002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_565, 16, 2),
    BGR565        = 0x15551002u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_565, 16, 2),
    RGB24         = 0x17101803u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU8, SDL_ARRAYORDER_RGB, 0, 24, 3),
    BGR24         = 0x17401803u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU8, SDL_ARRAYORDER_BGR, 0, 24, 3),
    XRGB8888      = 0x16161804u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_8888, 24, 4),
    RGBX8888      = 0x16261804u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_RGBX, SDL_PACKEDLAYOUT_8888, 24, 4),
    XBGR8888      = 0x16561804u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_8888, 24, 4),
    BGRX8888      = 0x16661804u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_BGRX, SDL_PACKEDLAYOUT_8888, 24, 4),
    ARGB8888      = 0x16362004u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ARGB, SDL_PACKEDLAYOUT_8888, 32, 4),
    RGBA8888      = 0x16462004u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_RGBA, SDL_PACKEDLAYOUT_8888, 32, 4),
    ABGR8888      = 0x16762004u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ABGR, SDL_PACKEDLAYOUT_8888, 32, 4),
    BGRA8888      = 0x16862004u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_BGRA, SDL_PACKEDLAYOUT_8888, 32, 4),
    XRGB2101010   = 0x16172004u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_2101010, 32, 4),
    XBGR2101010   = 0x16572004u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_2101010, 32, 4),
    ARGB2101010   = 0x16372004u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ARGB, SDL_PACKEDLAYOUT_2101010, 32, 4),
    ABGR2101010   = 0x16772004u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ABGR, SDL_PACKEDLAYOUT_2101010, 32, 4),
    RGB48         = 0x18103006u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_RGB, 0, 48, 6),
    BGR48         = 0x18403006u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_BGR, 0, 48, 6),
    RGBA64        = 0x18204008u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_RGBA, 0, 64, 8),
    ARGB64        = 0x18304008u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_ARGB, 0, 64, 8),
    BGRA64        = 0x18504008u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_BGRA, 0, 64, 8),
    ABGR64        = 0x18604008u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_ABGR, 0, 64, 8),
    RGB48_FLOAT   = 0x1a103006u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_RGB, 0, 48, 6),
    BGR48_FLOAT   = 0x1a403006u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_BGR, 0, 48, 6),
    RGBA64_FLOAT  = 0x1a204008u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_RGBA, 0, 64, 8),
    ARGB64_FLOAT  = 0x1a304008u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_ARGB, 0, 64, 8),
    BGRA64_FLOAT  = 0x1a504008u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_BGRA, 0, 64, 8),
    ABGR64_FLOAT  = 0x1a604008u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_ABGR, 0, 64, 8),
    RGB96_FLOAT   = 0x1b10600cu, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_RGB, 0, 96, 12),
    BGR96_FLOAT   = 0x1b40600cu, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_BGR, 0, 96, 12),
    RGBA128_FLOAT = 0x1b208010u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_RGBA, 0, 128, 16),
    ARGB128_FLOAT = 0x1b308010u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_ARGB, 0, 128, 16),
    BGRA128_FLOAT = 0x1b508010u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_BGRA, 0, 128, 16),
    ABGR128_FLOAT = 0x1b608010u, // SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_ABGR, 0, 128, 16),

    YV12          = 0x32315659u, // Planar mode: Y + V + U  (3 planes) SDL_DEFINE_PIXELFOURCC('Y', 'V', '1', '2'),
    IYUV          = 0x56555949u, // Planar mode: Y + U + V  (3 planes) SDL_DEFINE_PIXELFOURCC('I', 'Y', 'U', 'V'), 
    YUY2          = 0x32595559u, // Packed mode: Y0+U0+Y1+V0 (1 plane) SDL_DEFINE_PIXELFOURCC('Y', 'U', 'Y', '2'),
    UYVY          = 0x59565955u, // Packed mode: U0+Y0+V0+Y1 (1 plane) SDL_DEFINE_PIXELFOURCC('U', 'Y', 'V', 'Y'),
    YVYU          = 0x55595659u, // Packed mode: Y0+V0+Y1+U0 (1 plane) SDL_DEFINE_PIXELFOURCC('Y', 'V', 'Y', 'U'),
    NV12          = 0x3231564eu, // Planar mode: Y + U/V interleaved  (2 planes) SDL_DEFINE_PIXELFOURCC('N', 'V', '1', '2'),
    NV21          = 0x3132564eu, // Planar mode: Y + V/U interleaved  (2 planes) SDL_DEFINE_PIXELFOURCC('N', 'V', '2', '1'),
    P010          = 0x30313050u, // Planar mode: Y + U/V interleaved  (2 planes) SDL_DEFINE_PIXELFOURCC('P', '0', '1', '0'),
    EXTERNAL_OES  = 0x2053454fu, // Android video texture format SDL_DEFINE_PIXELFOURCC('O', 'E', 'S', ' ')
};

} // namespace SDL3CPP
