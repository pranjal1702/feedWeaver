#pragma once
#include<span>
#include<filesystem>
#include<cstddef>
#include<vector>
#include<fstream>


class FileFrameReader {
public:
    explicit FileFrameReader(const std::filesystem::path& path);

    bool next(std::span<const std::byte>& frame);

private:
    std::ifstream file_;
    std::vector<std::byte> buffer_;
};