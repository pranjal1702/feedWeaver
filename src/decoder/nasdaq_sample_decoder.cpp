#include "nasdaq_sample_decoder.h"
#include<iostream>
#include<unordered_map>
namespace itch50{

NasdaqSampleDecoder::NasdaqSampleDecoder(const std::filesystem::path& filepath):file_reader_(filepath),parser_() {

}

void NasdaqSampleDecoder::start(){
    // start getting the message frames
    std::span<const std::byte> frame;
    uint64_t count = 0;
    std::unordered_map<char,uint64_t> ct;

    while(file_reader_.next(frame)){
        // call the parser on this frame
        parser_.parse(frame,ct);
        count++;
    }
    std::cout<<" Total messages: "<< count<<"\n";
    std::cout<<" Total add order: "<< ct['A']<<"\n";
    std::cout<<" Total executed order: "<< ct['E']<<"\n";
}


} // namespace ends