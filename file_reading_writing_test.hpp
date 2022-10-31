#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

std::uintmax_t file_size(std::ifstream &input);

int main(int argc, char *argv[])
{
    std::cout << "Huffman" << std::endl;
    
    std::ifstream input("fontos.txt", std::ios_base::binary);

    if (!input.is_open())
    {
        std::cout << "Input opening failed." << std::endl;
        return 0;
    }

    std::ofstream output("output.dat", std::ios_base::binary);

    if (!output.is_open())
    {
        std::cout << "Output opening failed" << std::endl;
        return 0;
    }

    std::uintmax_t input_size = file_size(input);
    std::cout << "File size " << input_size << " bytes." << std::endl;
    char buffer[512];
    std::cout << "Size of buffer " << sizeof(buffer) << " bytes." << std::endl;

    for (std::uintmax_t read_byte_count = 0; read_byte_count < input_size;)
    {
        std::uintmax_t bytes_to_read = std::min(sizeof(buffer), input_size - read_byte_count);
        input.read(buffer, bytes_to_read);
        output.write(buffer, bytes_to_read);
        read_byte_count += bytes_to_read;
    }

    std::string result_message = !input.bad() && !input.fail() 
        ? "Successfully processed input." 
        : "Failed to process input";

    std::cout << result_message << std::endl;

    return 0;
}

std::uintmax_t file_size(std::ifstream &input)
{
    input.seekg(0, std::ios_base::end);
    std::uintmax_t size = input.tellg();
    input.seekg(0, std::ios_base::beg);

    return size;
}
