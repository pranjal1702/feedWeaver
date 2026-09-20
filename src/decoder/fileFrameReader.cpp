#include "fileFrameReader.h"

FileFrameReader::FileFrameReader(const std::filesystem::path& path): file_(path,std::ios::binary) {
    if (!file_) {
        throw std::runtime_error("Failed to open file");
    }
}

bool FileFrameReader::next(std::span<const std::byte>& frame){
    std::uint16_t length;

    file_.read(reinterpret_cast<char*>(&length),sizeof(length));
    if(!file_){
        return false;
    }

    buffer_.resize(length);

    file_.read(reinterpret_cast<char*>(buffer_.data()),length);

    frame = std::span<const std::byte>(
        buffer_.data();
        buffer_.size();
    );

    return true;
}