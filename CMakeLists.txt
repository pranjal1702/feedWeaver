cmake_minimum_required(VERSION 3.20)

project(feedWeaver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(feedWeaver
    src/main.cpp

    src/decoder/file_frame_reader.cpp
    src/decoder/nasdaq_sample_decoder.cpp

    src/parser/nasdaq_sample_parser.cpp
)

target_include_directories(feedWeaver PRIVATE
    decoder/include
    parser/include
)