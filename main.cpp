#include <iostream>

#include "movieMap.h"
#include "movieMapReducer.h"

int main() {
    // Create instances of MovieMap for each data file
    MovieMap movieMapData1, movieMapData2, movieMapData3, movieMapData4;

    // Parse each CSV file
    if (!movieMapData1.parseCSV("data1.csv")) {
        std::cerr << "Failed to parse data1.csv" << std::endl;
        return 1;
    }

    if (!movieMapData2.parseCSV("data2.csv")) {
        std::cerr << "Failed to parse data2.csv" << std::endl;
        return 1;
    }

    if (!movieMapData3.parseCSV("data3.csv")) {
        std::cerr << "Failed to parse data3.csv" << std::endl;
        return 1;
    }

    if (!movieMapData4.parseCSV("data4.csv")) {
        std::cerr << "Failed to parse data4.csv" << std::endl;
        return 1;
    }

    MovieMapReducer reducer;

    // Map phase for each data file
    auto mapResult1 = reducer.mapFunction(movieMapData1.getData());
    auto mapResult2 = reducer.mapFunction(movieMapData2.getData());
    auto mapResult3 = reducer.mapFunction(movieMapData3.getData());
    auto mapResult4 = reducer.mapFunction(movieMapData4.getData());

    // Combine the map results
    std::vector<std::map<std::string, int>> combinedMapResults = {
        mapResult1, mapResult2, mapResult3, mapResult4};

    // Reduce phase for a specific movie name
    std::string movieName = "Chan Is Missing";
    int totalMovieCount = reducer.reduceFunction(movieName, combinedMapResults);

    // Display the results
    std::cout << "Total count for \"" << movieName << "\": " << totalMovieCount
              << std::endl;
    return 0;
}
