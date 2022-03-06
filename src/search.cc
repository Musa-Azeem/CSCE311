/*
Written by Musa Azeem
Search class source code
*/

#include "../inc/search.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#include <iostream>

Search::Search(char *path, char *search_str){
    this->path = std::string(path);
    this->search_str = std::string(search_str);
    checkValidFile();
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
void Search::checkValidFile(){
    if(std::filesystem::exists(path)){
        validFile = true;
    }
    else{
        validFile = false;
    }
}
// bool Search::isValidFile() const{
//     return this->validFile;
// }
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
        return 1;
    }
    catch(std::string e){
        return(0);
    }    
}