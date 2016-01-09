#vcbuild.bat debug x64 nosign
#set %NODE_PATH%=.../node

project(fwBinding-javascript)

find_path(NODE_ROOT_DIR "node/node.h" "src/node.h"
    PATHS /usr/include/nodejs /usr/local/include/nodejs)
find_library(NODE_LIBRARY node ${NODE_ROOT_DIR} ${NODE_ROOT_DIR}/Debug ${NODE_ROOT_DIR}/Release)

set(CMAKE_SWIG_OUTDIR ${PROJECT_BINARY_DIR})

get_target_property(PROJECT_INCLUDE_DIRECTORIES ${FWPROJECT_NAME} INTERFACE_INCLUDE_DIRECTORIES)
include_directories("${PROJECT_INCLUDE_DIRECTORIES}"
    ${NODE_ROOT_DIR}/src 
    ${NODE_ROOT_DIR}/deps/v8/include
    ${NODE_ROOT_DIR}/deps/uv/include
)
set_source_files_properties(fw4spl.i PROPERTIES CPLUSPLUS ON)

set(SWIG_MODULE_fw4spl_EXTRA_FLAGS -node -DV8_VERSION=0x045103)

swig_add_module(fw4spl javascript fw4spl.i)
set_source_files_properties(${swig_generated_file_fullname} PROPERTIES COMPILE_FLAGS "-DBUILDING_NODE_EXTENSION")

swig_link_libraries(fw4spl ${FWPROJECT_NAME} ${NODE_LIBRARY})

set_target_properties(${SWIG_MODULE_fw4spl_REAL_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
set_target_properties(${SWIG_MODULE_fw4spl_REAL_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

#install module and test
add_custom_command(TARGET ${SWIG_MODULE_fw4spl_REAL_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${SWIG_MODULE_fw4spl_REAL_NAME}.node
                                     ${CMAKE_BINARY_DIR}/node/${SWIG_MODULE_fw4spl_REAL_NAME}.node
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test.js
                                     ${CMAKE_BINARY_DIR}/node/test.js
)
