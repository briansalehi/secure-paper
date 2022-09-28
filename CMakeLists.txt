cmake_minimum_required(VERSION 3.17)
project("Secure Paper" VERSION 0.1 LANGUAGES CXX)

find_package(Boost COMPONENTS program_options REQUIRED)

file(GLOB source_files src/*)
file(GLOB header_files include/*)
file(GLOB doc_files docs/*)
file(GLOB artifacts *.pdf *.log *.aux *.tex)

add_executable(secure-paper ${source_files})
target_include_directories(secure-paper PRIVATE include)
target_link_libraries(secure-paper PRIVATE Boost::program_options)
set_property(TARGET secure-paper APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${artifacts})

add_custom_target(docs doxygen WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} SOURCES Doxyfile ${doc_files} COMMENT "generating html documents")

install(TARGETS secure-paper)
