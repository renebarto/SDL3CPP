project(osal-test
    VERSION ${MSI_NUMBER}
    DESCRIPTION "OSAL Test"
    LANGUAGES CXX)

message(STATUS "\n**********************************************************************************\n")
message(STATUS "\n## In directory: ${CMAKE_CURRENT_SOURCE_DIR}")

message("\n** Setting up ${PROJECT_NAME} **\n")

if (PLATFORM_WINDOWS)
    set(PROJECT_TARGET_NAME ${PROJECT_NAME})
else()
    set(PROJECT_TARGET_NAME ${PROJECT_NAME}.out)
endif()

set(PROJECT_BUILD_REFERENCE "\"${PROJECT_VERSION}\"")

set(PROJECT_COMPILE_DEFINITIONS_CXX_PRIVATE
    "PACKAGE_NAME=\"${PROJECT_NAME}\""
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
    )

set(PROJECT_LINK_OPTIONS
    ${LINKER_OPTIONS}
    )

set(PROJECT_DEPENDENCIES
    osal
    test-platform
    gtest_main
    )

set(PROJECT_LIBS
    ${LINKER_LIBRARIES}
    ${PROJECT_DEPENDENCIES}
    )

set(PROJECT_SOURCES 
    ${PROJECT_SOURCE_DIR}/src/regex/RegexTest.cpp
    ${PROJECT_SOURCE_DIR}/src/synchronization/ManualEventTest.cpp
    ${PROJECT_SOURCE_DIR}/src/synchronization/SemaphoreTest.cpp
    ${PROJECT_SOURCE_DIR}/src/synchronization/SignalTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utilities/AssertTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utilities/ClockTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utilities/ConsoleTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utilities/EnvironmentTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utilities/ErrorCodeTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utilities/ThreadFunctionsTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utilities/TypeInfoTest.cpp
    )
set(PROJECT_SOURCES_${PROJECT_NAME}
    ${PROJECT_SOURCES}
    CACHE STRING "${PROJECT_NAME}" FORCE)

set(PROJECT_INCLUDES_PRIVATE
    )

set(PROJECT_INCLUDES_PUBLIC
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

link_directories(${LINK_DIRECTORIES})
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_INCLUDES_PUBLIC} ${PROJECT_INCLUDES_PRIVATE})
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

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_TARGET_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

show_target_properties(${PROJECT_NAME})

if (NOT PLATFORM_WINDOWS)
    add_install_target(${PROJECT_NAME} install-components)
    add_uninstall_target(${PROJECT_NAME} uninstall-components)

    message(STATUS "Deploy to ${DEPLOYMENT_DIR}/${PROJECT_NAME}/${CONFIG_DIR}")
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${DEPLOYMENT_DIR}/${PROJECT_NAME}/${CONFIG_DIR}
        COMPONENT ${PROJECT_NAME}
        )
endif()