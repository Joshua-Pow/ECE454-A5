#include "movieMapReducer.h"

#include "movieMap.h"

// Map function implementation
std::map<std::string, int> MovieMapReducer::mapFunction(
    const std::map<std::string, MovieList>& data) {
    std::map<std::string, int> wordCounts;
    for (const auto& pair : data) {
        wordCounts[pair.first] = pair.second.count;
    }
    return wordCounts;
}

// Reduce function implementation
int MovieMapReducer::reduceFunction(
    const std::string& word,
    const std::vector<std::map<std::string, int>>& mappedData) {
    int totalCount = 0;
    for (const auto& dataFile : mappedData) {
        auto it = dataFile.find(word);
        if (it != dataFile.end()) {
            totalCount += it->second;
        }
    }
    return totalCount;
}
