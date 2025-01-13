cmake_minimum_required(VERSION 3.15)
project(hierarchical_compressed_sets)
include(ExternalProject)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/sdsl-lite
  ${PROJECT_BINARY_DIR}/external/sdsl-lite/build)

add_executable(benchmark benchmark.cpp)
target_compile_features(benchmark PRIVATE cxx_std_20)
target_compile_options(benchmark PRIVATE -O3)
target_link_libraries(benchmark PRIVATE sdsl)

add_executable(top_down top_down.cpp)
target_compile_features(top_down PRIVATE cxx_std_20)
target_compile_options(top_down PRIVATE -O3)
target_link_libraries(top_down PRIVATE sdsl)

add_executable(bottom_up bottom_up.cpp)
target_compile_features(bottom_up PRIVATE cxx_std_20)
target_compile_options(bottom_up PRIVATE -O3)
target_link_libraries(bottom_up PRIVATE sdsl)

add_executable(find_parents find_parents.cpp)
target_compile_features(find_parents PRIVATE cxx_std_20)
target_compile_options(find_parents PRIVATE -O3)

add_executable(sort_asc sort_sets_asc.cpp)
target_compile_features(sort_asc PRIVATE cxx_std_20)
target_compile_options(sort_asc PRIVATE -O3)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
  target_link_libraries(find_parents PRIVATE OpenMP::OpenMP_CXX)
endif()
