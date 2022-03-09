/*
Written by Musa Azeem
Search class source code
This file defines the functions of Searh class
Functions:
    defuault constructor:   sets path and search_str to "", isValid to false, and found_lines to default
    alternate constructor:  takes a single string and splits it by the tab character into path and search strings
        calls checkValidFile to set validFile
    copy constructor: initializes object by copying another instance
    assignment operator: copies another instance of object
    get_found_lines:  returns found_lines
    get_path:   returns path
    get_search_str: returns search_str
    checkValidFile: checks if path is a file in directory, sets value of validFile accordingly
    Search: if validFile is true, searches for search_str in file specified by path
        loops through every line of file
        if search_str is a substring of line, that line is added to found_lines vector
        returns 1 if successful
        if not valid file or if error occurs, returns 0
*/

#include "../inc/search.h"
#include <string>
#include <vector>
#include <filesystem>   //using exists
#include <fstream>      //using istream
#include <sstream>      //using stringstream

Search::Search() 
    : path(""), search_str(""), validFile(false)
    {}
Search::Search(char *str){
    std::stringstream ss(str);
    std::getline(ss, path, '\t');
    std::getline(ss, search_str, '\t');
    checkValidFile();
}
Search::Search(Search &s){
    validFile = s.validFile;
    path = s.get_path();
    search_str = s.get_search_str();
    found_lines = s.get_found_lines();
}
const Search &Search::operator=(const Search &rhs){
    validFile = rhs.validFile;
    path = rhs.get_path();
    search_str = rhs.get_search_str();
    found_lines = rhs.get_found_lines();
    return rhs;
}
const std::vector<std::string> &Search::get_found_lines() const{
    return found_lines;
}
const std::string &Search::get_path() const{
    return path;
}
const std::string &Search::get_search_str() const{
    return search_str;
}
void Search::checkValidFile(){
    if(std::filesystem::exists(path)){
        validFile = true;
    }
    else{
        validFile = false;
    }
}
int Search::search(){
    if(!validFile){
        return 0;
    }

    std::ifstream in_file;
    try{
        in_file.open(path);
        std::string line;
        while(getline(in_file, line)){
            if(line.find(search_str) != std::string::npos){
                found_lines.push_back(line);
            }
        }
        in_file.close();
        return 1;
    }
    catch(std::string e){
        return(0);
    }    
}