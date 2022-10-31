#include <iostream>
#include "compression.h"

static const std::string compressed_extension = "hufc";
static const std::string decompressed_extension = "hufd";

void compress(const std::filesystem::path &input_path, const std::filesystem::path &ouput_path)
{
    std::cout << "Compressing." << std::endl;
    // Be kell olvasni a fájl tartalmát egy bufferbe.

}

void decompress(const std::filesystem::path &input_path, const std::filesystem::path &output_path)
{
    std::cout << "Decompressing." << std::endl;
}
