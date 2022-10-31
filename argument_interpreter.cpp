#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>
#include <optional>
#include "compression.h"
#include "argument_interpreter.h"

extern const int file_signature;
extern const std::string compressed_extension;

static const std::string_view compression_argument = "-c";
static const std::string_view decompression_argument = "-d";
static const std::string_view output_file_path_argument = "-o";

static bool validate_input_file(std::filesystem::path path)
{    
    if (path.empty())
    {
        std::cout << "File path must not be empty.";
        return false;
    }

    if (!std::filesystem::exists(path))
    {
        std::cout << "File does not exist" << std::endl;
        return false;
    }

    if (std::filesystem::file_size(path) < sizeof(file_signature))
    {
        std::cout << "Invalid file signature. Can not use file for the given operation." << std::endl;
        return false;
    }
    
    std::ifstream input(path, std::ios_base::binary);

    if (!input.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return false;
    }
    
    int signature;
    input.read(reinterpret_cast<char *>(&signature), sizeof(signature));

    if (signature != file_signature)
    {
        std::cout << "Invalid file signature. Can not use file for the given operation." << std::endl;
        return false;
    }
   
    return true;
}

static bool validate_operation(std::string_view operation)
{
    if (operation != compression_argument && operation != decompression_argument)
    {
        std::cout << "Operation argument must be either" << std::endl;
        std::cout << compression_argument << ": for compression" << std::endl;
        std::cout << decompression_argument << ": for decompression" << std::endl;
        
        return false;
    }

    return true;
}

std::string find_operation_argument(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::string argument(argv[i]);

        if (argument == compression_argument || argument == decompression_argument)
        {
            return argument;
        }
    }

    return "";
}

std::optional<std::string> find_output_path_argument(int argc, char *argv[])
{
    typedef std::optional<std::string> result_type;

    for (int i = 1; i < argc; ++i)
    {
        if (std::string_view argument = argv[i]; argument == output_file_path_argument)
        {
            return i < argc - 1 ? result_type(argv[i + 1]) : result_type("");
        }
    }

    return result_type();
}

void execute_operation(std::string_view operation, const std::filesystem::path &input_path, const std::filesystem::path &output_path)
{
     if (operation == compression_argument)
    {
        compress(input_path, output_path);
    }
    else if (operation == decompression_argument)
    {
        decompress(input_path, output_path);
    }
}

void interpret_arguments(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Filename and operation arguments required." << std::endl;
        return;
    }

    std::filesystem::path input_path = argv[1];
    std::string operation = find_operation_argument(argc, argv);

    if (!validate_input_file(input_path) || !validate_operation(operation))
    {
        return;
    }

    std::optional<std::string> output_path_argument = find_output_path_argument(argc, argv);

    if (output_path_argument && output_path_argument->empty())
    {
        std::cout << "Output file path value is missing." << std::endl;
        return;
    }

    std::filesystem::path output_path = output_path_argument ? *output_path_argument : "";
    execute_operation(operation, input_path, output_path);
}
