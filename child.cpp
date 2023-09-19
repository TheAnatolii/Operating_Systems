#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace std;

int main (int argc, char *argv[]){
    int count = 0, l;
    while (cin >> l){
        count += l;
    }
    cout << count;

    return 0;
}