cmake_minimum_required(VERSION "3.16")

project(shamir_secret_sharing C)
set(CMAKE_C_COMPILER "gcc")


include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

add_executable(shamir_secret_sharing src/shamir_secret_sharing.c)
set_target_properties(shamir_secret_sharing PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")