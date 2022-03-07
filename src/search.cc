/*
Written by Musa Azeem
Search class source code
*/

#include "../inc/search.h"
#include <string>
#include <vector>
#include <filesystem>   //using exists
#include <fstream>      //using istream
#include <sstream>

#include <iostream>

Search::Search() 
    : path(""), search_str(""), validFile(false)
    {}
Search::Search(char *str){
    std::stringstream ss(str);
    std::getline(ss, path, '\t');
    std::getline(ss, search_str, '\t');
    checkValidFile();
}
Search::Search(char *path, char *search_str){
    this->path = std::string(path);
    this->search_str = std::string(search_str);
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
void Search::setPath(char *path){
    this->path = std::string(path);
    checkValidFile();
}
void Search::setSearchStr(char *search_str){
    this->search_str = std::string(search_str);
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