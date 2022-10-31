#ifndef HUFFMAN_COMPRESSION_H
#define HUFFMAN_COMPRESSION_H

#include <filesystem>

const int file_signature = 0xABA00488;

enum class compression_mode : int8_t
{
    single_symbol,
    multiple_symbol
};

void compress(const std::filesystem::path &input_path, const std::filesystem::path &output_path);
void decompress(const std::filesystem::path &input_path, const std::filesystem::path &output_path);

#endif
