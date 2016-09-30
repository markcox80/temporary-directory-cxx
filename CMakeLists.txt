project(temporary-directory)
cmake_minimum_required(VERSION 3.4.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catch REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(tags
                  COMMAND sh scripts/generate-tags.sh
                  DEPENDS temporary-directory
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

install(EXPORT temporary-directory
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/temporary-directory/)

configure_file(temporary-directory-config.cmake.in temporary-directory-config.cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/temporary-directory-config.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/temporary-directory/)
