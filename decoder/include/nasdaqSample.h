#pragma once
#include<filesystem>
// this decoder reads raw sample data file provided by nasdaq and forwards one raw exchange message to parser

namespace itch50{


class NasdaqSampleDecoder{
public:
    NasdaqSampleDecoder(const std::filesystem::path& filepath){
        // open the file and 
    }

private:
    void on_msg(){
        // reads the raw data in memory and pass it to the parser

    }
};




} // namespace ends