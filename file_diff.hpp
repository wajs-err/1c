#pragma once

#include <filesystem>

void DirectoryFilesDiff(const std::filesystem::path& dir_1, 
                        const std::filesystem::path& dir_2,
                        int similarite_percent);
