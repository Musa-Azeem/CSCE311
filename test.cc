#include <string>
#include <iostream>
using namespace std;

#include "inc/search.h"
#include <vector>

int main(){
    // Search s("data/dante.t", "bad");
    Search s("data/del\thello");
    if(s.search()){
        for(auto str : s.get_found_lines()){
            cout << str << endl;
        }
    }
    else{
        cout << "error" << endl;
    }
    cout << endl << endl;
    Search f;
    f = Search("data/del\thello");
    if(!f.search()){
        cout << "fail" << endl;
    }
    cout << f.get_path() << endl;
    cout << f.get_search_str() << endl;

    for(auto str : f.get_found_lines()){
            cout << str << endl;
    }

    Search z = f;
    f.setPath("none");
    cout << f.get_path() << endl;
    cout << z.get_path() << endl;

}