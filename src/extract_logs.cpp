#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

void extract_logs(const std::string& input_date) {
    std::string input_filename = "logs_2024.log";  // The log file
    std::string output_filename = "output/output_" + input_date + ".txt";
    
    // Open the log file for reading
    int fd = open(input_filename.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error: Could not open file '" << input_filename << "'." << std::endl;
        return;
    }

    // Get the file size
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        std::cerr << "Error: Could not determine file size." << std::endl;
        close(fd);
        return;
    }

    // Memory-map the file for faster access
    char* mapped_file = (char*)mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped_file == MAP_FAILED) {
        std::cerr << "Error: Could not map file into memory." << std::endl;
        close(fd);
        return;
    }

    // Open the output file for writing
    std::ofstream outfile(output_filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open output file '" << output_filename << "'." << std::endl;
        munmap(mapped_file, file_size);
        close(fd);
        return;
    }

    std::string line;
    char* line_start = mapped_file;
    char* current = mapped_file;

    // Iterate through the memory-mapped file
    while (current < mapped_file + file_size) {
        // If we find a newline, process the current line
        if (*current == '\n' || current == mapped_file + file_size - 1) {
            size_t line_length = current - line_start + (current == mapped_file + file_size - 1 ? 1 : 0);
            line.assign(line_start, line_length);
            
            // Check if the line starts with the input date
            if (line.substr(0, 10) == input_date) {
                outfile << line << std::endl;
            }

            // Move to the next line
            line_start = current + 1;
        }
        current++;
    }

    std::cout << "Logs for " << input_date << " extracted successfully to " << output_filename << std::endl;

    // Clean up resources
    munmap(mapped_file, file_size);
    close(fd);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./extract_logs <YYYY-MM-DD>" << std::endl;
        return 1;
    }

    std::string input_date = argv[1];
    extract_logs(input_date);  // Call the function to extract logs
    return 0;
}