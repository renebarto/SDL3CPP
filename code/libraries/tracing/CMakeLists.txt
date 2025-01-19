project(tracing
    VERSION ${MSI_NUMBER}
    DESCRIPTION "Tracing functionality"
    LANGUAGES CXX)

message(STATUS "\n**********************************************************************************\n")
message(STATUS "\n## In directory: ${CMAKE_CURRENT_SOURCE_DIR}")

message("\n** Setting up ${PROJECT_NAME} **\n")

set(PROJECT_TARGET_NAME ${PROJECT_NAME})

set(PROJECT_BUILD_REFERENCE "\"${PROJECT_VERSION}\"")

set(PROJECT_COMPILE_DEFINITIONS_CXX_PRIVATE
    "PACKAGE_NAME=\"${PROJECT_NAME}\""
    "ROOT_PATH=\"${CMAKE_SOURCE_DIR}\""
    ${COMPILE_DEFINITIONS_C}
    )

set(PROJECT_COMPILE_DEFINITIONS_CXX_PUBLIC
    )

set(PROJECT_COMPILE_OPTIONS_CXX_PRIVATE
    ${COMPILE_OPTIONS_CXX}
    )

set(PROJECT_COMPILE_OPTIONS_CXX_PUBLIC
    )

set(PROJECT_INCLUDE_DIRS_PRIVATE
    )

set(PROJECT_INCLUDE_DIRS_PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    )

set(PROJECT_LINK_OPTIONS
    ${LINKER_OPTIONS}
    )

set(PROJECT_DEPENDENCIES
    filesystem
    )

set(PROJECT_LIBS
    ${LINKER_LIBRARIES}
    ${PROJECT_DEPENDENCIES}
    )

set(PROJECT_SOURCES 
    src/ConsoleLogLineWriter.cpp
    src/ConsoleTraceLineWriter.cpp
    src/FatalHandler.cpp
    src/Logging.cpp
    src/LogWriter.cpp
    src/StringLogLineWriter.cpp
    src/StringTraceLineWriter.cpp
    src/TraceCategory.cpp
    src/TraceChannel.cpp
    src/TraceHelpers.cpp
    src/TraceRegistry.cpp
    src/TraceRegistryItem.cpp
    src/TraceWriter.cpp
    src/Tracing.cpp
    )
set(PROJECT_INCLUDES_PRIVATE
    )
set(PROJECT_INCLUDES_PUBLIC
    include/tracing/CategorySet.h
    include/tracing/ConsoleLogLineWriter.h
    include/tracing/ConsoleTraceLineWriter.h
    include/tracing/FatalHandler.h
    include/tracing/ILogLineWriter.h
    include/tracing/ITraceLineWriter.h
    include/tracing/ITraceRegistryUpdateListener.h
    include/tracing/LogEntry.h
    include/tracing/Logging.h
    include/tracing/LogWriter.h
    include/tracing/ScopedTracing.h
    include/tracing/StringLogLineWriter.h
    include/tracing/StringTraceLineWriter.h
    include/tracing/TraceCategory.h
    include/tracing/TraceChannel.h
    include/tracing/TraceHelpers.h
    include/tracing/TraceRegistry.h
    include/tracing/TraceRegistryItem.h
    include/tracing/TraceWriter.h
    include/tracing/Tracing.h
    )

if (CMAKE_VERBOSE_MAKEFILE)
    display_list("Package                           : " ${PROJECT_NAME} )
    display_list("Package description               : " ${PROJECT_DESCRIPTION} )
    display_list("Package version major             : " ${PROJECT_VERSION_MAJOR} )
    display_list("Package version minor             : " ${PROJECT_VERSION_MINOR} )
    display_list("Package version level             : " ${PROJECT_VERSION_PATCH} )
    display_list("Package version build             : " ${PROJECT_VERSION_TWEAK} )
    display_list("Package version                   : " ${PROJECT_VERSION} )
    display_list("Build reference                   : " ${PROJECT_BUILD_REFERENCE} )
    display_list("Defines - public                  : " ${PROJECT_COMPILE_DEFINITIONS_PUBLIC} )
    display_list("Defines - private                 : " ${PROJECT_COMPILE_DEFINITIONS_PRIVATE} )
    display_list("Compiler options - public         : " ${PROJECT_COMPILE_OPTIONS_CXX_PUBLIC} )
    display_list("Compiler options - private        : " ${PROJECT_COMPILE_OPTIONS_CXX_PRIVATE} )
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
#    EXPORT_MACRO_NAME SHARED_EXPORT
#    EXPORT_FILE_NAME ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}_export.h
#    STATIC_DEFINE ${PROJECT_NAME}_BUILD_STATIC
#)
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
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

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD ${SUPPORTED_CPP_STANDARD})

list_to_string(PROJECT_LINK_OPTIONS PROJECT_LINK_OPTIONS_STRING)
if (NOT "${PROJECT_LINK_OPTIONS_STRING}" STREQUAL "")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${PROJECT_LINK_OPTIONS_STRING}")
endif()

link_directories(${LINK_DIRECTORIES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_TARGET_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

show_target_properties(${PROJECT_NAME})

if (BUILD_CLASS_TESTS)
    add_subdirectory(test)
endif()
