project(fwBinding-python)

find_package(PythonLibs 2.7 REQUIRED )

set(CMAKE_SWIG_OUTDIR ${PROJECT_BINARY_DIR})

get_target_property(PROJECT_INCLUDE_DIRECTORIES ${FWPROJECT_NAME} INTERFACE_INCLUDE_DIRECTORIES)
include_directories("${PROJECT_INCLUDE_DIRECTORIES}" ${PYTHON_INCLUDE_DIRS})
set_source_files_properties(fw4spl.i PROPERTIES CPLUSPLUS ON)


swig_add_module(fw4spl python fw4spl.i)
swig_link_libraries(fw4spl ${FWPROJECT_NAME} ${PYTHON_LIBRARIES})
set_target_properties(${SWIG_MODULE_fw4spl_REAL_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${SWIG_MODULE_fw4spl_REAL_NAME} PROPERTIES SUFFIX _d.pyd)
endif()

#install module and test
get_target_property(PYTHON_MODULE_SUFFIX ${SWIG_MODULE_fw4spl_REAL_NAME} SUFFIX)
set(PYTHON_MODULE_NAME ${SWIG_MODULE_fw4spl_REAL_NAME}${PYTHON_MODULE_SUFFIX})

add_custom_command(TARGET ${SWIG_MODULE_fw4spl_REAL_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${PYTHON_MODULE_NAME}
                                     ${CMAKE_BINARY_DIR}/python/${PYTHON_MODULE_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/fw4spl.py
                                     ${CMAKE_BINARY_DIR}/python/fw4spl.py
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test.py
                                     ${CMAKE_BINARY_DIR}/python/test.py
)
