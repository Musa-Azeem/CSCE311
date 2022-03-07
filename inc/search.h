/*
Written by Musa Azeem
Search Class header
This file defines the Search Class, which recieves a file path and searches for a given search string in the file
Class Variables:
  path:       file path string
  search_str: string to search for in file
  found_lines:  vector of lines in the file that contain search string
  validFile:  is true if given path is a valid file, false if not
Class Functions:
  defualt Constructor:  sets isValid to false and all else to null
  alternate constructor:  splits given string into path and search strings
  copy constructor: initializes object by copying another instance
  assignment operator: copies another instance of object
  search:   searches for search_str in path file
  get_found_lines:  returns found_lines
  get_path:   returns path
  get_search_str: returns search_str
  checkValidFile: checks if path is a file in directory, sets value of validFile accordingly
*/

#ifndef SEARCH_H
#define SEACH_H
#include <string>
#include <vector>

class Search{
    public:
      Search();
      Search(char *str);
      // Search(char *path, char *search_str);
      Search(Search &s);
      const Search &operator=(const Search &rhs);
      // void setPath(char *path);
      // void setSearchStr(char *search_str);
    //   bool isValidFile() const;
    //   std::vector<std::string> search();
      int search();
      const std::vector<std::string> &get_found_lines() const;
      const std::string &get_path() const;
      const std::string &get_search_str() const;
    private:
      std::string path;
      std::string search_str;
      std::vector<std::string> found_lines;   //vector of null terminated char[]
      bool validFile;
      void checkValidFile();
};

#endif