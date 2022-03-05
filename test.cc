#include <string>
#include <iostream>
#include "inc/text-client.h"
using namespace std;

int main(){
    TextClient cli("socket", "hello", "hell");
    cli.print();
}