#include <future>
#include <iostream>
#include <map>

#include "movieMap.h"
#include "movieMapReducer.h"

std::map<std::string, int> parseAndMap(const std::string& filename,
                                       MovieMapReducer& reducer) {
  MovieMap movieMap;
  if (!movieMap.parseCSV(filename)) {
    std::cerr << "Failed to parse " << filename << std::endl;
    return {};  // Return an empty map in case of failure
  }
  return reducer.mapFunction(movieMap.getData());
}

int serializedMain() {
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();
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
  std::string movieName = "Arthur Newman";
  int totalMovieCount = reducer.reduceFunction(movieName, combinedMapResults);

  // Stop timer
  auto end = std::chrono::high_resolution_clock::now();

  // Display the time in milliseconds
  std::cout << "Time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms" << std::endl;

  // Display the results
  std::cout << "Total count for \"" << movieName << "\": " << totalMovieCount
            << std::endl;
}

int parallelizedMain() {
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  MovieMapReducer reducer;

  // Use std::async to run parsing and mapping in parallel
  std::future<std::map<std::string, int>> future1 =
      std::async(parseAndMap, "data1.csv", std::ref(reducer));
  std::future<std::map<std::string, int>> future2 =
      std::async(parseAndMap, "data2.csv", std::ref(reducer));
  std::future<std::map<std::string, int>> future3 =
      std::async(parseAndMap, "data3.csv", std::ref(reducer));
  std::future<std::map<std::string, int>> future4 =
      std::async(parseAndMap, "data4.csv", std::ref(reducer));

  // Retrieve the results
  auto mapResult1 = future1.get();
  auto mapResult2 = future2.get();
  auto mapResult3 = future3.get();
  auto mapResult4 = future4.get();

  // Combine the map results
  std::vector<std::map<std::string, int>> combinedMapResults = {
      mapResult1, mapResult2, mapResult3, mapResult4};

  // Reduce phase for a specific movie name
  std::string movieName = "Arthur Newman";
  int totalMovieCount = reducer.reduceFunction(movieName, combinedMapResults);

  // Stop timer
  auto end = std::chrono::high_resolution_clock::now();

  // Display the time in milliseconds
  std::cout << "Time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms" << std::endl;

  // Display the results
  std::cout << "Total count for \"" << movieName << "\": " << totalMovieCount
            << std::endl;
}

int main() {
  serializedMain();
  parallelizedMain();
  return 0;
}
