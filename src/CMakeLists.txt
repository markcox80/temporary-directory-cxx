add_library(temporary-directory temporary-directory.cpp)
target_include_directories(temporary-directory PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                      $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

install(TARGETS temporary-directory
        EXPORT temporary-directory
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES temporary-directory.hpp
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
