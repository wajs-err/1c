#include "utils.hpp"

std::filesystem::path ParseInputToPath(const char* path) {
   return {path}; 
}

int ParseInputToSimilarityPercent(const char* str) {
    int result;
    std::stringstream stream(str);
    stream >> result;
    return result;
}
