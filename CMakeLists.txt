cmake_minimum_required(VERSION 3.17)
project("Secure Paper" VERSION 0.1 LANGUAGES CXX)

find_package(Boost COMPONENTS program_options REQUIRED)

file(GLOB source_files src/*)
file(GLOB header_files include/*)
file(GLOB doc_files docs/*)

add_executable(secure-paper ${source_files})
target_include_directories(secure-paper PRIVATE include)
target_link_libraries(secure-paper PRIVATE Boost::program_options)

install(TARGETS secure-paper)
