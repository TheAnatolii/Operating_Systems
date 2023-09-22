#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    int count = 0;
    char symbol;
    string num;

    if (read(STDIN_FILENO, &symbol, sizeof(char)) == -1)
    {
        return -1;
    }

    while (symbol != '\n')
    {
        if (symbol != ' ')
        {
            num += symbol;
        }
        else
        {
            count += stoi(num);
            num = "";
        }
        read(STDIN_FILENO, &symbol, sizeof(char));
    }

    count += stoi(num);

    write(STDOUT_FILENO, &count, sizeof(int));

    return 0;
}