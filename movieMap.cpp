// MovieMap.cpp

#include "movieMap.h"

#include <fstream>
#include <iostream>
#include <sstream>

// ListNode constructor
ListNode::ListNode(std::string g, float r)
    : genre(g), rating(r), next(nullptr) {}

// MovieList constructor
MovieList::MovieList() : head(nullptr), count(0) {}

// MovieList destructor
MovieList::~MovieList() {
  ListNode* current = head;
  while (current != nullptr) {
    ListNode* nextNode = current->next;
    delete current;
    current = nextNode;
  }
}

// Add node to MovieList
void MovieList::addNode(const std::string& genre, float rating) {
  ListNode* newNode = new ListNode(genre, rating);
  newNode->next = head;
  head = newNode;
  count++;
}

// MovieMap constructor
MovieMap::MovieMap() {}

// MovieMap destructor
MovieMap::~MovieMap() {
  // No dynamic memory allocation directly within MovieMap,
  // so no additional actions needed in the destructor
}

// TODO: FIX THIS PARSING, DOESNT HANDLE QUOTES
bool MovieMap::parseCSV(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file '" << filename << "'."
              << std::endl;
    return false;
  }

  std::string line, movieName, genre, ratingStr;
  float rating;

  // Read and discard the header
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    if (line.front() == '\"') {
      // Handle quoted movie name
      std::getline(ss, movieName, '\"');  // Extract up to the closing quote
      ss.get();                           // Skip the following comma
      movieName.erase(0, 1);              // Remove the leading quote
      std::getline(ss, movieName, '\"');  // Extract the rest of the movie name
      ss.get();                           // Skip the following comma
    } else {
      std::getline(ss, movieName, ',');  // Handle unquoted movie name
    }

    std::getline(ss, genre, ',');
    std::getline(ss, ratingStr);

    // Trim whitespace from ratingStr
    ratingStr.erase(0, ratingStr.find_first_not_of(" \n\r\t"));
    ratingStr.erase(ratingStr.find_last_not_of(" \n\r\t") + 1);

    try {
      rating = std::stof(ratingStr);
    } catch (const std::invalid_argument& ia) {
      std::cerr << "Extracted rating string: '" << ratingStr << "'"
                << std::endl;
      std::cerr << "Error: Invalid rating encountered in line: " << line
                << std::endl;
      continue;  // Optionally skip this line and continue parsing
    }
    movieMap[movieName].addNode(genre, rating);
  }

  return true;
}

void MovieMap::printMovieMap() const {
  for (const auto& pair : movieMap) {
    std::cout << "Movie: " << pair.first
              << " (Total Entries: " << pair.second.count << ")" << std::endl;
    ListNode* current = pair.second.head;
    while (current != nullptr) {
      std::cout << "  Genre: " << current->genre
                << ", Rating: " << current->rating << std::endl;
      current = current->next;
    }
  }
}

const std::map<std::string, MovieList>& MovieMap::getData() const {
  return movieMap;
}
