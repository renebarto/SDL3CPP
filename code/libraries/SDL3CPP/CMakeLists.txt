project(SDL3CPP
    DESCRIPTION "SDL3 C++ wrapper library"
    LANGUAGES CXX)

message(STATUS "\n**********************************************************************************\n")
message(STATUS "\n## In directory: ${CMAKE_CURRENT_SOURCE_DIR}")

message("\n** Setting up ${PROJECT_NAME} **\n")

include(functions)

set(PROJECT_TARGET_NAME ${PROJECT_NAME})

set(PROJECT_COMPILE_DEFINITIONS_CXX_PRIVATE ${COMPILE_DEFINITIONS_C})
set(PROJECT_COMPILE_DEFINITIONS_CXX_PUBLIC )
set(PROJECT_COMPILE_DEFINITIONS_ASM_PRIVATE ${COMPILE_DEFINITIONS_ASM})
set(PROJECT_COMPILE_OPTIONS_CXX_PRIVATE ${COMPILE_OPTIONS_CXX})
set(PROJECT_COMPILE_OPTIONS_CXX_PUBLIC )
set(PROJECT_COMPILE_OPTIONS_ASM_PRIVATE ${COMPILE_OPTIONS_ASM})
set(PROJECT_INCLUDE_DIRS_PRIVATE
    )
set(PROJECT_INCLUDE_DIRS_PUBLIC
    include
    ${SDL2_INCLUDE_DIRS}
    )

set(PROJECT_LINK_OPTIONS ${LINKER_OPTIONS})

set(PROJECT_DEPENDENCIES
    )

set(PROJECT_LIBS
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
    utility
    ${LINKER_LIBRARIES}
    ${PROJECT_DEPENDENCIES}
    )

set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AudioConfiguration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DisplayConfiguration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Events.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Font.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FPoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FRect.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Hints.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Rect.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SDL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SDLImage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SDLTTF.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Surface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Window.cpp
    )

set(PROJECT_INCLUDES_PUBLIC )
set(PROJECT_INCLUDES_PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/AudioConfiguration.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/DisplayConfiguration.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Events.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/FPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/FRect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Hints.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Lib.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Optional.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/PixelFormat.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Point.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Rect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/SDL.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/SDLImage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/SDLTTF.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Surface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Texture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL3CPP/Window.h
    )

if (CMAKE_VERBOSE_MAKEFILE)
    display_list("Package                           : " ${PROJECT_NAME} )
    display_list("Package description               : " ${PROJECT_DESCRIPTION} )
    display_list("Defines C - public                : " ${PROJECT_COMPILE_DEFINITIONS_C_PUBLIC} )
    display_list("Defines C - private               : " ${PROJECT_COMPILE_DEFINITIONS_C_PRIVATE} )
    display_list("Defines C++ - public              : " ${PROJECT_COMPILE_DEFINITIONS_CXX_PUBLIC} )
    display_list("Defines C++ - private             : " ${PROJECT_COMPILE_DEFINITIONS_CXX_PRIVATE} )
    display_list("Defines ASM - private             : " ${PROJECT_COMPILE_DEFINITIONS_ASM_PRIVATE} )
    display_list("Compiler options C - public       : " ${PROJECT_COMPILE_OPTIONS_C_PUBLIC} )
    display_list("Compiler options C - private      : " ${PROJECT_COMPILE_OPTIONS_C_PRIVATE} )
    display_list("Compiler options C++ - public     : " ${PROJECT_COMPILE_OPTIONS_CXX_PUBLIC} )
    display_list("Compiler options C++ - private    : " ${PROJECT_COMPILE_OPTIONS_CXX_PRIVATE} )
    display_list("Compiler options ASM - private    : " ${PROJECT_COMPILE_OPTIONS_ASM_PRIVATE} )
    display_list("Include dirs - public             : " ${PROJECT_INCLUDE_DIRS_PUBLIC} )
    display_list("Include dirs - private            : " ${PROJECT_INCLUDE_DIRS_PRIVATE} )
    display_list("Linker options                    : " ${PROJECT_LINK_OPTIONS} )
    display_list("Dependencies                      : " ${PROJECT_DEPENDENCIES} )
    display_list("Link libs                         : " ${PROJECT_LIBS} )
    display_list("Source files                      : " ${PROJECT_SOURCES} )
    display_list("Include files - public            : " ${PROJECT_INCLUDES_PUBLIC} )
    display_list("Include files - private           : " ${PROJECT_INCLUDES_PRIVATE} )
endif()

#include (GenerateExportHeader)
#if (BUILD_STATIC_LIBS)
add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES} ${PROJECT_INCLUDES_PUBLIC} ${PROJECT_INCLUDES_PRIVATE})
#else()
#add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${PROJECT_INCLUDES_PUBLIC} ${PROJECT_INCLUDES_PRIVATE})
#endif()

#generate_export_header(${PROJECT_NAME}
#    BASE_NAME ${PROJECT_NAME}
#    EXPORT_MACRO_NAME SDL3CPP_EXPORT
#    EXPORT_FILE_NAME ${PROJECT_SOURCE_DIR}/include/SDL3CPP/${PROJECT_NAME}_export.h
#    STATIC_DEFINE ${PROJECT_NAME}_BUILD_STATIC
#)

target_link_libraries(${PROJECT_NAME} ${START_GROUP} ${PROJECT_LIBS} ${END_GROUP})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIRS_PRIVATE})
target_include_directories(${PROJECT_NAME} PUBLIC  ${PROJECT_INCLUDE_DIRS_PUBLIC})
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    $<$<COMPILE_LANGUAGE:C>:${PROJECT_COMPILE_DEFINITIONS_C_PRIVATE}>
    $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_COMPILE_DEFINITIONS_CXX_PRIVATE}>
    $<$<COMPILE_LANGUAGE:ASM>:${PROJECT_COMPILE_DEFINITIONS_ASM_PRIVATE}>
    )
target_compile_definitions(${PROJECT_NAME} PUBLIC 
    $<$<COMPILE_LANGUAGE:C>:${PROJECT_COMPILE_DEFINITIONS_C_PUBLIC}>
    $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_COMPILE_DEFINITIONS_CXX_PUBLIC}>
    $<$<COMPILE_LANGUAGE:ASM>:${PROJECT_COMPILE_DEFINITIONS_ASM_PUBLIC}>
    )
target_compile_options(${PROJECT_NAME} PRIVATE 
    $<$<COMPILE_LANGUAGE:C>:${PROJECT_COMPILE_OPTIONS_C_PRIVATE}>
    $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_COMPILE_OPTIONS_CXX_PRIVATE}>
    $<$<COMPILE_LANGUAGE:ASM>:${PROJECT_COMPILE_OPTIONS_ASM_PRIVATE}>
    )
target_compile_options(${PROJECT_NAME} PUBLIC 
    $<$<COMPILE_LANGUAGE:C>:${PROJECT_COMPILE_OPTIONS_C_PUBLIC}>
    $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_COMPILE_OPTIONS_CXX_PUBLIC}>
    $<$<COMPILE_LANGUAGE:ASM>:${PROJECT_COMPILE_OPTIONS_ASM_PUBLIC}>
    )

message(STATUS "Standard ${SUPPORTED_CPP_STANDARD}")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD ${SUPPORTED_CPP_STANDARD})

list_to_string(PROJECT_LINK_OPTIONS PROJECT_LINK_OPTIONS_STRING)
if (NOT "${PROJECT_LINK_OPTIONS_STRING}" STREQUAL "")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${PROJECT_LINK_OPTIONS_STRING}")
endif()

link_directories(${LINK_DIRECTORIES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_TARGET_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

show_target_properties(${PROJECT_NAME})

if (BUILD_CLASS_TESTS)
    add_subdirectory(test)
endif()
