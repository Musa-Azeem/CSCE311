#include <string>
#include <iostream>
using namespace std;

#include "inc/search.h"
#include <vector>

int main(){
    Search s("data/dante.t", "bad");
    if(s.search()){
        for(auto str : s.get_found_lines()){
            cout << str << endl;
        }
    }
    else{
        cout << "error" << endl;
    }

}