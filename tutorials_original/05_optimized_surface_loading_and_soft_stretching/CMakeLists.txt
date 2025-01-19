cmake_minimum_required(VERSION 3.5)
project(05_optimized_surface_loading_and_soft_stretching)

# Create an option to switch between a system sdl library and a vendored SDL library
option(MAIN_VENDORED "Use vendored libraries" OFF)

if(MAIN_VENDORED)
    # This assumes you have added SDL as a submodule in vendored/SDL
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL3 package,
    # 2. look for the SDL3-shared component, and
    # 3. fail if the shared component cannot be found.
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

# Create your game executable target as usual
file(GLOB sources *.cpp)
add_executable(05_optimized_surface_loading_and_soft_stretching ${sources})

# Link to the actual SDL3 library.
target_link_libraries(05_optimized_surface_loading_and_soft_stretching PRIVATE SDL3::SDL3)

# Add resource files
file(GLOB RESOURCE_FILES *.bmp)
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
add_custom_target(05_optimized_surface_loading_and_soft_stretching_resources DEPENDS "${RESOURCE_FILES_BINDIR}")
add_dependencies(05_optimized_surface_loading_and_soft_stretching 05_optimized_surface_loading_and_soft_stretching_resources)
