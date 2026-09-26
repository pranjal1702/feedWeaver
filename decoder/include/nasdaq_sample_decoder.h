#pragma once
#include<filesystem>
#include "file_frame_reader.h"
#include "nasdaq_sample_parser.h"
// this decoder reads raw sample data file provided by nasdaq and forwards one raw exchange message to parser

namespace itch50{


class NasdaqSampleDecoder{
public:
    NasdaqSampleDecoder(const std::filesystem::path& filepath);
    void start();
private:
    void on_msg();
    FileFrameReader file_reader_;
    itch50::NasdaqSampleParser parser_;
};




} // namespace ends