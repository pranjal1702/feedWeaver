#include "nasdaq_sample_decoder.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: ./feedWeaver <nasdaq_sample_file>\n";
        return 1;
    }

    itch50::NasdaqSampleDecoder decoder{argv[1]};

    decoder.start();

    return 0;
}