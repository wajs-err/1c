#include "levenshtein.hpp"

int LevenshteinDistance(const std::vector<unsigned char>& lhs,
                        const std::vector<unsigned char>& rhs) {
   if (lhs.size() > rhs.size()) {
        return LevenshteinDistance(rhs, lhs);
    }

    const size_t min_size = lhs.size();
    const size_t max_size = rhs.size();
    std::vector<size_t> dist(min_size + 1);

    for (size_t i = 0; i <= min_size; ++i) {
        dist[i] = i;
    }

    for (size_t j = 1; j <= max_size; ++j) {
        size_t prev_diagonal = dist[0];
        size_t prev_diagonal_save;
        ++dist[0];
        for (size_t i = 1; i <= min_size; ++i) {
            prev_diagonal_save = dist[i];
            if (lhs[i - 1] == rhs[j - 1]) {
                dist[i] = prev_diagonal;
            } else {
                dist[i] = std::min(std::min(dist[i - 1], dist[i]), prev_diagonal) + 1;
            }
            prev_diagonal = prev_diagonal_save;
        }
    }

    return dist.back(); 
}
