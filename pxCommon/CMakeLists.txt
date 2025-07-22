project(pxtone-common)

add_library(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/pxStdDef.h")

# Consumers do not have to manually include
set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}")

if(NOT "${BUNDLE_BUILD_DIR}" STREQUAL "")
    file(COPY "${CMAKE_SOURCE_DIR}/data/" DESTINATION "${CMAKE_SOURCE_DIR}/${BUNDLE_BUILD_DIR}")
endif()

# Create shorthand for subproject boilerplate
# ---------------

# Common behavior for any binary in our build
macro(target_binary PROJECT)

    # Multi-config generators are too unpredictable to test & maintain code for; use CMAKE_BUILD_TYPE to make a release
    get_cmake_property(MULTI_CONFIG_BUILD GENERATOR_IS_MULTI_CONFIG)
    if(NOT MULTI_CONFIG_BUILD AND NOT "${BUNDLE_BUILD_DIR}" STREQUAL "")
        set(OUT_DIR "${CMAKE_SOURCE_DIR}/${BUNDLE_BUILD_DIR}")
        message("${OUT_DIR}")
        set_target_properties(${PROJECT} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUT_DIR}"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUT_DIR}"
            OPTIMIZE_DEPENDENCIES true
            PCH_WARN_INVALID true
        )
    endif()
endmacro()

# Create a target with all requirements for internal subprojects
macro(add_pxtone_subproject PROJECT)
    target_link_libraries(${PROJECT} PRIVATE
    pxtone::common
    ${ARGN}
  )
    target_binary(${PROJECT})
    set(STDAFX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/StdAfx/StdAfx.h")
    if(EXISTS "${STDAFX_HEADER}")
        target_include_directories(${PROJECT} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/StdAfx")
        target_precompile_headers(${PROJECT} PRIVATE ${STDAFX_HEADER})
    endif()
endmacro()

# Create a target with all requirements for an executable
macro(add_pxtone_executable PROJECT SOURCES)
    if(USE_UNICODE)
        list(APPEND SOURCES "${UTF8_MANIFEST_RC}")
    endif()
    add_executable(${PROJECT} WIN32 ${SOURCES})
    add_pxtone_subproject(${PROJECT} ${ARGN})
endmacro()

# Create a target with all requirements for an internal library
macro(add_pxtone_library PROJECT SCOPE SOURCES)
    add_library(${PROJECT} ${SCOPE} ${SOURCES})
    set_target_properties(${PROJECT} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})
    if(NOT ${SCOPE} STREQUAL "INTERFACE")
        # Consumers do not have to manually include this target's path
        target_include_directories(${PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
        add_pxtone_subproject(${PROJECT} ${ARGN})
    endif()
endmacro()

# Create a target with all requirements for an internally-managed external dependency
macro(add_bundled_library PROJECT SCOPE SOURCES INCLUDE_DIRS)
    add_library(${PROJECT} ${SCOPE} ${SOURCES})
    target_include_directories(${PROJECT} PUBLIC "${INCLUDE_DIRS}")
    target_link_libraries(${PROJECT} PRIVATE ${ARGN})
    if (MSVC)
        target_compile_options(${PROJECT} PRIVATE "/W0")
    else()
        target_compile_options(${PROJECT} PRIVATE "-w")
    endif()
    target_binary(${PROJECT})
endmacro()

# Export
# ---------------

add_library(pxtone::common ALIAS ${PROJECT_NAME})
