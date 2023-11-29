#ifndef MOVIEMAPREDUCER_H
#define MOVIEMAPREDUCER_H

#include <map>
#include <string>
#include <vector>

#include "movieMap.h"

// Forward declaration of MovieList
struct MovieList;

class MovieMapReducer {
   public:
    std::map<std::string, int> mapFunction(
        const std::map<std::string, MovieList>& data);
    int reduceFunction(
        const std::string& word,
        const std::vector<std::map<std::string, int>>& mappedData);
};

#endif  // MOVIEMAPREDUCER_H
