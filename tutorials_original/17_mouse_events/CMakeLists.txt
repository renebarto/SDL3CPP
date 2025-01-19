cmake_minimum_required(VERSION 3.5)
project(17_mouse_events)

# Create an option to switch between a system sdl library and a vendored SDL library
option(MAIN_VENDORED "Use vendored libraries" OFF)

if(MAIN_VENDORED)
    # This assumes you have added SDL as a submodule in vendored/SDL
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
    add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL3 package,
    # 2. look for the SDL3-shared component, and
    # 3. fail if the shared component cannot be found.
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
    find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)
endif()

# Create your game executable target as usual
file(GLOB sources *.cpp)
add_executable(17_mouse_events ${sources})

# Link to the actual SDL3 library.
target_link_libraries(17_mouse_events PRIVATE SDL3::SDL3)
target_link_libraries(17_mouse_events PRIVATE SDL3_image::SDL3_image)

# Add resource files
file(GLOB RESOURCE_FILES *.bmp *.png)
set(RESOURCE_FILE_NAMES)
set(RESOURCE_FILES_BINDIR)
foreach(resource_file IN LISTS RESOURCE_FILES)
    get_filename_component(res_file_name ${resource_file} NAME)
    list(APPEND RESOURCE_FILE_NAMES "${res_file_name}")
    set(resource_file_bindir "${CMAKE_CURRENT_BINARY_DIR}/${res_file_name}")
    add_custom_command(OUTPUT "${resource_file_bindir}"
        COMMAND "${CMAKE_COMMAND}" -E copy "${resource_file}" "${resource_file_bindir}"
        DEPENDS "${resource_file}"
    )
    list(APPEND RESOURCE_FILES_BINDIR "${resource_file_bindir}")
endforeach()
add_custom_target(17_mouse_events_resources DEPENDS "${RESOURCE_FILES_BINDIR}")
add_dependencies(17_mouse_events 17_mouse_events_resources)
