#include <exception>
#include <iostream>

#include "file_diff.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
   if (argc < 4) {
       std::cout << "Not enough arguments"; 
       return 1;
   } 
   const auto dir_1 = ParseInputToPath(argv[1]);
   const auto dir_2 = ParseInputToPath(argv[2]);
   const auto similarity_percent = ParseInputToSimilarityPercent(argv[3]);

   try {
        DirectoryFilesDiff(dir_1, dir_2, similarity_percent);
   } catch (const std::exception& exc) {
        std::cerr << exc.what();
        return 1;
   } 
}
