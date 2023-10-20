#include <iostream>

#include "utils.hpp"

int main(int argc, char** argv) {
   if (argc < 3) {
       std::cout << "Not enough arguments"; 
       return 1;
   } 
   const auto dir_1 = ParseInputToPath(argv[1]);
   const auto dir_2 = ParseInputToPath(argv[2]);

   std::cout << dir_1 << ' ' << dir_2;
}
