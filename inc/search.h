/*
Written by Musa Azeem
Search class header
*/

#ifndef SEARCH_H
#define SEACH_H
#include <string>
#include <vector>

class Search{
    public:
      Search(char *path, char *search_str);
      void setPath(char *path);
      void setSearchStr(char *search_str);
    //   bool isValidFile() const;
    //   std::vector<std::string> search();
    int search();
    const std::vector<std::string> &get_found_lines() const;
    private:
      std::string path;
      std::string search_str;
      std::vector<std::string> found_lines;   //vector of null terminated char[]
      bool validFile;
      void checkValidFile();
};

#endif