#pragma once

#include <filesystem>
#include <sstream>

std::filesystem::path ParseInputToPath(const char* path); 

int ParseInputToSimilarityPercent(const char* str);
