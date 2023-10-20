#include "file_diff.hpp"
#include "levenshtein.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <iterator>
#include <vector>

namespace {

using Byte = unsigned char;

struct FileBufWithName {
    std::filesystem::path name;
    std::vector<Byte> buffer;
};

std::vector<FileBufWithName> ExtractFilesAsBuffers(
        const std::filesystem::path& dir) {
    std::vector<std::filesystem::path> files;
    for (const auto& file : std::filesystem::directory_iterator(dir)) {
        files.push_back(file);
    }
    std::sort(files.rbegin(), files.rend(), [](const auto& lhs, const auto& rhs){
        return std::filesystem::file_size(lhs) < std::filesystem::file_size(rhs);            
    });

    std::vector<FileBufWithName> buffers;
    buffers.reserve(files.size());
    for (const auto& file : files) {
        std::ifstream stream(file, std::ios::binary);
        std::vector<Byte> buffer{
                std::istreambuf_iterator<char>(stream),
                std::istreambuf_iterator<char>()};
        buffers.push_back({.name = file, .buffer = std::move(buffer)});
    }
    return buffers;
}

void LogResult(const std::filesystem::path& file_1,
        const std::filesystem::path& file_2, int dist,
        int max_file_size, int similarity_percent) {
    if (dist == 0) {
        std::cout << "Files " << file_1 << " and " << file_2 << " are identical\n"; 
    } else if (dist < max_file_size * similarity_percent / 100) {
        std::cout << "Files " << file_1 << " and " << file_2 << " are similar\n"; 
    } else {
        std::cout << "File " << file_1 << " is only present in one directory\n";
        std::cout << "File " << file_2 << " is only present in one directory\n";
    }
}
};

void DirectoryFilesDiff(const std::filesystem::path& dir_1, 
                        const std::filesystem::path& dir_2,
                        int similarite_percent) {
    if (!std::filesystem::is_directory(dir_1) || 
            !std::filesystem::is_directory(dir_2)) {
        throw std::logic_error("One of given directories is not a directory");
    }

    const auto buffers_1 = ExtractFilesAsBuffers(dir_1);
    const auto buffers_2 = ExtractFilesAsBuffers(dir_2);
    if (buffers_1.empty() || buffers_2.empty()) {
        std::cout << "One of given directories is empty"; 
        return;
    }
    const auto max_file_size = std::max(
            std::filesystem::file_size(buffers_1.front().name),
            std::filesystem::file_size(buffers_2.front().name)); 

    for (const auto& buffer_1 : buffers_1) {
        for (const auto& buffer_2 : buffers_2) {
            const auto dist = LevenshteinDistance(buffer_1.buffer, buffer_2.buffer);
            LogResult(buffer_1.name, buffer_2.name, dist, max_file_size, similarite_percent);
        }
    }

}

