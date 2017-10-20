cmake_minimum_required(VERSION 2.8)
project(fits)

enable_language(C)
add_subdirectory(code)

include_directories(code)
add_executable(test_fits test_fits.c)
target_link_libraries(test_fits fits)

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

