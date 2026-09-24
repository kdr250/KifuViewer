project(testmain VERSION 1.0)

find_package(GTest CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(GoogleTest)

file(GLOB_RECURSE TESTS "src/*.cpp")
file(GLOB_RECURSE SOURCES "../src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "Main.cpp")

add_executable(testmain ${TESTS} ${SOURCES})

target_include_directories(testmain PRIVATE ../src)

if (EMSCRIPTEN)

    file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/test)

    target_link_libraries(
        testmain
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        SDL3::SDL3
    )

else()

    target_link_libraries(
        testmain
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        SDL3::SDL3
    )

    add_custom_command(
        TARGET testmain POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:testmain>/resources
    )

endif()

gtest_discover_tests(testmain)
