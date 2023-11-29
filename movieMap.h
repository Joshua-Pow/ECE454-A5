#ifndef MOVIEMAP_H
#define MOVIEMAP_H

#include <map>
#include <string>

// Forward declaration
struct ListNode;

struct MovieList {
    ListNode* head;
    int count;

    MovieList();
    ~MovieList();
    void addNode(const std::string& genre, float rating);
};

// Node structure for the linked list
struct ListNode {
    std::string genre;
    float rating;
    ListNode* next;
    ListNode(std::string g, float r);
};

class MovieMap {
   private:
    std::map<std::string, MovieList> movieMap;

   public:
    MovieMap();
    ~MovieMap();
    bool parseCSV(const std::string& filename);
    void printMovieMap() const;
    const std::map<std::string, MovieList>& getData() const;
};

#endif  // MOVIEMAP_H
