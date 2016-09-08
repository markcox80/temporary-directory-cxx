
add_library(temporary-directory temporary-directory.cpp)

install(TARGETS temporary-directory
        EXPORT temporary-directory
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES temporary-directory.hpp
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
