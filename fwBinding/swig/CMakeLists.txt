option(BUILD_PYTHON "Build Python wrapper." ON)
option(BUILD_NODE "Build NodeJS wrapper." ON)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

if(BUILD_PYTHON)
    add_subdirectory(python)
endif()
if(BUILD_NODE)
    add_subdirectory(node)
endif()