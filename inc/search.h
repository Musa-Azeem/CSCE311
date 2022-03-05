/*
Written by Musa Azeem
Search class header
*/

#ifndef SEARCH_H
#define SEACH_H
#include <string>
#include <vector>

class String{
    public:
      String(char *path, char *search_str);
      void setPath(char *path);
      void setSearchStr(char *search_str);
      bool isValidFile() const;
      std::vector<std::string> search() const;
    private:
      std::string path;
      std::string search_str;
      std::vector<std::string> found;   //vector of null terminated char[]
};

#endif