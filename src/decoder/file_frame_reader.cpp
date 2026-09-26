#include "file_frame_reader.h"
#include<cstddef>
FileFrameReader::FileFrameReader(const std::filesystem::path& path): file_(path,std::ios::binary) {
    if (!file_) {
        throw std::runtime_error("Failed to open file");
    }
}

bool FileFrameReader::next(std::span<const std::byte>& frame){
    std::array<std::byte, 2> length_bytes;

    file_.read(
        reinterpret_cast<char*>(length_bytes.data()),
        length_bytes.size()
    );

    if(!file_){
        return false;
    }
    std::uint16_t length =
    (static_cast<std::uint16_t>(length_bytes[0]) << 8) |
     static_cast<std::uint16_t>(length_bytes[1]);

    buffer_.resize(length);

    file_.read(reinterpret_cast<char*>(buffer_.data()),length);

    frame = std::span<const std::byte>(
        buffer_.data(),
        buffer_.size()
    );

    return true;
}