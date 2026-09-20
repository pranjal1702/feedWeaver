#pragma once
#include<filesystem>
// this decoder reads raw sample data file provided by nasdaq and forwards one raw exchange message to parser

namespace itch50{


class NasdaqSampleParser{
public:
    NasdaqSampleParser();

private:
    void parse(){
        // reads the raw data in memory and pass it to the parser
        
    }
};




} // namespace ends