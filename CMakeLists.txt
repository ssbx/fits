cmake_minimum_required(VERSION 2.8)
project(fits)

enable_language(C)
add_subdirectory(code)

set (FITS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/code CACHE STRING "fits includes")

find_package (Doxygen)
if (DOXYGEN_FOUND)
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
            ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile @ONLY)
    add_custom_target (cglm_doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif (DOXYGEN_FOUND)

