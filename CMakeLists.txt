cmake_minimum_required(VERSION 3.20)

message(STATUS "CMake Version: ${CMAKE_VERSION}")

message(STATUS "\n## In directory: ${CMAKE_CURRENT_SOURCE_DIR}")

option(VERBOSE_BUILD "Verbose build" ON)
set(SCRIPTS_DIR "" CACHE STRING "CMake scripts path")

if ("${SCRIPTS_DIR}" STREQUAL "")
    set(SCRIPTS_DIR "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_PREFIX_PATH}/cmake)
endif()
message(STATUS "SCRIPTS_DIR      : ${SCRIPTS_DIR}")

list(APPEND CMAKE_MODULE_PATH ${SCRIPTS_DIR})

include(functions)
include(macros)

message(STATUS "\n** Setting up project **\n--")

parse_msi(MSI_NUMBER MSI_VERSION_MAJOR MSI_VERSION_MINOR MSI_VERSION_LEVEL MSI_VERSION_BUILD)
message(STATUS "MSI version: ${MSI_VERSION_MAJOR}.${MSI_VERSION_MINOR}.${MSI_VERSION_LEVEL}.${MSI_VERSION_BUILD}")

message(STATUS "\n** Setting up toolchain **\n--")

project(SDL3Tutorial
    VERSION ${MSI_NUMBER}
    DESCRIPTION "This is the main project for SDL3 tutorials"
)

message(STATUS "")

if(WIN32 AND MSVC)
    set(PLATFORM_WINDOWS TRUE)
    message(STATUS "Building for Windows with MSVC")
    set(PLATFORM_NAME windows)
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_LINUX TRUE)
    message(STATUS "Building for Linux")
    set(PLATFORM_NAME linux)
else()
    message(ERROR "Unsupported platform " ${CMAKE_HOST_SYSTEM} "?")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_MAKEFILE   OFF)

set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

set(DEPLOYMENT_DIR "${CMAKE_SOURCE_DIR}/deploy" CACHE STRING "Deployment directory")
set(CMAKE_INSTALL_PREFIX ${DEPLOYMENT_DIR} CACHE STRING "" FORCE)
set(CMAKE_STAGING_PREFIX ${DEPLOYMENT_DIR})

set(CMAKE_PROGRAM_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_LIBRARY_PATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INCLUDE_PATH ${CMAKE_INSTALL_PREFIX}/include)

option(BUILD_CLASS_TESTS "Build class tests" ON)

if (VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
else()
    set(CMAKE_VERBOSE_MAKEFILE OFF)
endif()

set(IMAGE_DIR "${CMAKE_SOURCE_DIR}/images")
set(FONT_DIR "${CMAKE_SOURCE_DIR}/fonts")
set(STOCK_FONT_DIR "C:/Windows/fonts")
set(SOUND_DIR "${CMAKE_SOURCE_DIR}/sound")
set(ROM_DIR "${CMAKE_SOURCE_DIR}/rom")

message(STATUS "Platform:            ${PLATFORM_NAME}")
message(STATUS "Platform Windows:    ${PLATFORM_WINDOWS}")
message(STATUS "")
message(STATUS "Verbose build:       ${CMAKE_VERBOSE_MAKEFILE}")

get_git_commit(GIT_COMMIT)
get_git_tag(GIT_TAG)

message(STATUS "Git commit:          ${GIT_COMMIT}")
message(STATUS "Git tag:             ${GIT_TAG}")

macro(setup_default_options)
    if(PLATFORM_WINDOWS)
        # Important!! Since CMake 3.15 the variable CMAKE_MSVC_RUNTIME_LIBRARY and the target property MSVC_RUNTIME_LIBRARY were introduced.
        # This means that replacing compiler flags no longer works, and the variable CMAKE_MSVC_RUNTIME_LIBRARY needs to be set to either:
        #   set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") for non-DLL linkage, or
        #   set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL") for DLL linkage
        # This also changes the way Google Test / Mock compile and link
        # If you do not set this correctly, you will get errors such as this:
        #   error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MDd_DynamicDebug' doesn't match value 'MTd_StaticDebug' in xxx.cpp.obj

        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

        # Important! do not keep warning 4251 4275 ignored!
        # Possibly switch warning 4505 back on
        # /wd4251 /wd4275 
        set(FLAGS_CXX
            /Wall /wd4061 /wd4355 /wd4371 /wd4435 /wd4505 /wd4514 /wd4548 /wd4571 /wd4592 /wd4625 /wd4626 /wd4628 /wd4668 /wd4710 /wd4711 /wd4774 /wd4868 /wd5039 /wd5045
            /wd4820 /wd5026 /wd5027 /wd26495 /wd26812 /WX- /EHsc /Gd /GR /sdl- /Zc:wchar_t /Zc:inline /fp:precise /bigobj)
        set(FLAGS_CXX_DEBUG /Od /Gm- /Zi /RTC1 /MTd)
        set(FLAGS_CXX_RELEASE /Ox /GL /GS /Gy /Oi /MT)
        set(FLAGS_CXX_MINSIZEREL /O1 /GL /GS /Gy /Oi /MT)
        set(FLAGS_CXX_RELWITHDEBINFO /O2 /GL /GS /Gy /Oi /Zi /MT)

        set(FLAGS_C
            /Wall /wd4061 /wd4251 /wd4275 /wd4505 /wd4514 /wd4548 /wd4571 /wd4625 /wd4626 /wd4710 /wd4774
            /wd4820 /wd5026 /wd5027 /WX- /EHsc /Gd /GR /sdl- /Zc:wchar_t /Zc:inline /fp:precise)

        set(FLAGS_C_DEBUG /Od /Gm- /ZI /RTC1 /MTd)
        set(FLAGS_C_RELEASE /Ox /GL /GS /Gy /Oi /MT)
        set(FLAGS_C_MINSIZEREL /O1 /GL /GS /Gy /Oi /MT)
        set(FLAGS_C_RELWITHDEBINFO /O2 /GL /GS /Gy /Oi /Zi /MT)

        set(DEFINES_C _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS WINVER=0x0A00 _WIN32_WINNT=0x0A00 PLATFORM_WINDOWS
            IMAGE_DIR="${IMAGE_DIR}"
            FONT_DIR="${FONT_DIR}"
            STOCK_FONT_DIR="${STOCK_FONT_DIR}"
            SOUND_DIR="${SOUND_DIR}"
            ROM_DIR="${ROM_DIR}"
            )
        if (USE_SDL2_IMAGE)
            list(APPEND DEFINES_C SDL2_WITH_IMAGE)
        endif()
        if (USE_SDL2_TTF)
            list(APPEND DEFINES_C SDL2_WITH_TTF)
        endif()
        if (USE_SDL2_MIXER)
            list(APPEND DEFINES_C SDL2_WITH_MIXER)
        endif()
        set(DEFINES_C_DEBUG _DEBUG)
        set(DEFINES_C_RELEASE NDEBUG)
        set(DEFINES_C_MINSIZEREL NDEBUG)
        set(DEFINES_C_RELWITHDEBINFO NDEBUG)

        set(LINK_FLAGS /ignore:4217)
        list(APPEND LINK_LIBRARIES )
        list(APPEND LINK_DIRECTORIES )

        # Hack to force linker to target X64 machine when needed.
        if (${CMAKE_SIZEOF_VOID_P} EQUAL "8")
            list(APPEND DEFINES_C _AMD64_)
        else ()
            list(APPEND DEFINES_C _X86_)
        endif ()
        set(SUPPORTED_CPP_STANDARD 17)
    elseif(PLATFORM_LINUX)
        set(FLAGS_CXX -Wall -Wextra -fPIC -fexceptions -fmessage-length=0
             -Wno-deprecated-copy -Wno-packed-bitfield-compat)
        set(FLAGS_CXX_DEBUG -O0 -g)
        set(FLAGS_CXX_RELEASE -O3)
        set(FLAGS_CXX_MINSIZEREL -O3)
        set(FLAGS_CXX_RELWITHDEBINFO -O2 -g)

        set(FLAGS_C -Wall -Wextra -fPIC -fmessage-length=0)
        set(FLAGS_C_DEBUG -O0 -g)
        set(FLAGS_C_RELEASE -O3)
        set(FLAGS_C_MINSIZEREL -O3)
        set(FLAGS_C_RELWITHDEBINFO -O2 -g)

        set(DEFINES PLATFORM_LINUX)
        set(DEFINES_DEBUG _DEBUG)
        set(DEFINES_RELEASE NDEBUG)
        set(DEFINES_MINSIZEREL NDEBUG)
        set(DEFINES_RELWITHDEBINFO NDEBUG)

        set(LINK_FLAGS )
        list(APPEND LINK_LIBRARIES )
        list(APPEND LINK_DIRECTORIES )

        set(SUPPORTED_CPP_STANDARD 17)
    else()
        display_list("Unsupported platform " ${CMAKE_HOST_SYSTEM})
        return()
    endif()

    if("${GIT_TAG}" STREQUAL "")
        list(APPEND DEFINES BUILD_VERSION="${GIT_COMMIT}")
    else()
        list(APPEND DEFINES BUILD_VERSION="${GIT_TAG}")
    endif()
endmacro()

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set_config_dir()

set(OUTPUT_BASE_DIR ${CMAKE_SOURCE_DIR}/output/${PLATFORM_NAME})
set(OUTPUT_BIN_DIR "${OUTPUT_BASE_DIR}/${CONFIG_DIR}/bin")
set(OUTPUT_LIB_DIR "${OUTPUT_BASE_DIR}/${CONFIG_DIR}/lib")

message(STATUS "\n-- Find threading library\n--")
if (PLATFORM_WINDOWS)
    set(CMAKE_USE_WIN32_THREADS_INIT TRUE)
else()
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message(STATUS "CMAKE_THREAD_LIBS_INIT             = ${CMAKE_THREAD_LIBS_INIT}")
    message(STATUS "CMAKE_USE_WIN32_THREADS_INIT       = ${CMAKE_USE_WIN32_THREADS_INIT}")
    message(STATUS "CMAKE_USE_PTHREADS_INIT            = ${CMAKE_USE_PTHREADS_INIT}")
endif()

find_package(SDL3 REQUIRED)
message(    STATUS "SDL3_FOUND                         = ${SDL3_FOUND}")
if (SDL3_FOUND)
    message(STATUS "SDL3_Headers_FOUND                 = ${SDL3_Headers_FOUND}")
    message(STATUS "SDL3_SDL3-shared_FOUND             = ${SDL3_SDL3-shared_FOUND}")
    message(STATUS "SDL3_SDL3-static_FOUND             = ${SDL3_SDL3-static_FOUND}")
    include(SDL3ConfigVersion)
    set(SDL3_Version ${PACKAGE_VERSION})
    message(STATUS "SDL3_Version                       = ${SDL3_Version}")
endif()

find_package(SDL3_image QUIET)
message(    STATUS "SDL3_image_FOUND                   = ${SDL3_image_FOUND}")
if (SDL3_image_FOUND)
    message(STATUS "SDL3_image_SDL3_image-shared_FOUND = ${SDL3_image_SDL3_image-shared_FOUND}")
    message(STATUS "SDL3_image_SDL3_image-static_FOUND = ${SDL3_image_SDL3_image-static_FOUND}")
    include(SDL3_imageConfigVersion)
    set(SDL3_Image_Version ${PACKAGE_VERSION})
    message(STATUS "SDL3_Image_Version                 = ${SDL3_Image_Version}")
endif()

find_package(SDL3_net QUIET)
message(    STATUS "SDL3_net_FOUND                     = ${SDL3_net_FOUND}")
if (SDL3_net_FOUND)
    if(TARGET SDL3_net::SDL3_net-shared)
    message(STATUS "SDL3_net                           = SHARED")
    else()
    message(STATUS "SDL3_net                           = STATIC")
    endif()
    include(SDL3_netConfigVersion)
    set(SDL3_Net_Version ${PACKAGE_VERSION})
    message(STATUS "SDL3_Net_Version                   = ${SDL3_Net_Version}")
endif()

find_package(SDL3_mixer QUIET)
message(    STATUS "SDL3_mixer_FOUND                   = ${SDL3_mixer_FOUND}")
if (SDL3_mixer_FOUND)
    if(TARGET SDL3_mixer::SDL3_mixer-shared)
    message(STATUS "SDL3_mixer                         = SHARED")
    else()
    message(STATUS "SDL3_mixer                         = STATIC")
    endif()
    include(SDL3_mixerConfigVersion)
    set(SDL3_Mixer_Version ${PACKAGE_VERSION})
    message(STATUS "SDL3_Mixer_Version                 = ${SDL3_Mixer_Version}")
endif()

find_package(SDL3_rtf QUIET)
message(    STATUS "SDL3_rtf_FOUND                     = ${SDL3_rtf_FOUND}")
if (SDL3_rtf_FOUND)
    if(TARGET SDL3_rtf::SDL3_rtf-shared)
    message(STATUS "SDL3_rtf                           = SHARED")
    else()
    message(STATUS "SDL3_rtf                           = STATIC")
    endif()
    include(SDL3_rtfConfigVersion)
    set(SDL3_RTF_Version ${PACKAGE_VERSION})
    message(STATUS "SDL3_RTF_Version                   = ${SDL3_RTF_Version}")
endif()

find_package(SDL3_ttf QUIET)
message(    STATUS "SDL3_ttf_FOUND                     = ${SDL3_ttf_FOUND}")
if (SDL3_ttf_FOUND)
    if(TARGET SDL3_ttf::SDL3_ttf-shared)
    message(STATUS "SDL3_ttf                           = SHARED")
    else()
    message(STATUS "SDL3_ttf                           = STATIC")
    endif()
    include(SDL3_ttfConfigVersion)
    set(SDL3_TTF_Version ${PACKAGE_VERSION})
    message(STATUS "SDL3_TTF_Version                   = ${SDL3_TTF_Version}")
endif()

message(STATUS "C++ compiler version:    ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C compiler version:      ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "C++ supported standard:  ${SUPPORTED_CPP_STANDARD}")

setup_default_options()
convert_default_options()

if (NOT PLATFORM_WINDOWS)
    add_custom_target(install-components)
    add_custom_target(uninstall-components)
endif()

set(THIS_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

function(add_uninstall_target TARGET MAIN_TARGET)
    if (NOT PLATFORM_WINDOWS)
        configure_file(
            ${THIS_LIST_DIR}/uninstall.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
            IMMEDIATE @ONLY)
        add_custom_target(uninstall_${TARGET}
            COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${TARGET} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
            DEPENDS ${TARGET}
            COMMENT "Uninstalling ${TARGET}")
        add_dependencies(${MAIN_TARGET} uninstall_${TARGET})
    endif()
endfunction()

function(add_install_target TARGET MAIN_TARGET)
    add_custom_target(install_${TARGET}
        COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${TARGET} -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
        DEPENDS ${TARGET}
        COMMENT "Installing ${TARGET}")
    add_dependencies(${MAIN_TARGET} install_${TARGET})
endfunction()

message(STATUS "\n** Setup google test **")
# to prevent a warning with google test, set the default value for policy CMP0048
message(STATUS "\n## In directory: ${CMAKE_SOURCE_DIR}/externals/googletest/googletest-release-1.10.0")
set( CMAKE_POLICY_DEFAULT_CMP0048 NEW )
if (CMAKE_COMPILER_IS_GNUCXX) # Ignore warnings on ABI change in GCC7.1
    set(CMAKE_CXX_FLAGS_DEBUG -Wno-psabi)
    set(CMAKE_CXX_FLAGS_RELEASE -Wno-psabi)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO -Wno-psabi)
    set(CMAKE_CXX_FLAGS_MINSIZEREL -Wno-psabi)
endif()
add_subdirectory(${CMAKE_SOURCE_DIR}/externals/googletest/googletest-release-1.10.0 gtest_binary_dir)

add_subdirectory(code)
#add_subdirectory(tutorials_original)
