add_executable(temporary-directory-test tests.cpp)
target_include_directories(temporary-directory-test
                           PRIVATE ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries(temporary-directory-test temporary-directory catch)

add_custom_target(tests
                  COMMAND temporary-directory-test
                  DEPENDS temporary-directory-test
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
