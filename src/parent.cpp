#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[])
{

    string file_name;
    char symbol;
    if (read(STDIN_FILENO, &symbol, sizeof(char)) == -1)
    {
        return 7;
    }

    while (symbol != '\n')
    {
        file_name += symbol;
        if (read(STDIN_FILENO, &symbol, sizeof(char)) == -1)
        {
            return 7;
        }
    }
    int file = open(file_name.c_str(), O_RDONLY | O_CREAT, 0777);
    if (file == -1)
    {
        return -1;
    }

    int fd[2]; // fd[0] - read; fd[1] - write
    // Creating pipe and checking that it was created
    if (pipe(fd) == -1)
    {
        return 1;
    }

    // Forking the process
    int id = fork();
    if (id == -1) // fork error
    {
        return 2;
    }
    if (id == 0)
    { // child process

        dup2(file, 0);
        if (dup2(fd[1], 1) == -1)
        {
            return 5;
        }
        close(fd[0]);
        execlp("./child", "./child", NULL);

        return 3;
    }
    else
    { // parent process

        close(fd[1]);
        int answer = 0;
        string final = "";
        if (read(fd[0], &answer, sizeof(int)) == -1)
        {
            return 7;
        }
        final = to_string(answer) + "\n";

        write(STDOUT_FILENO, &final, final.length());
        close(fd[0]);
        close(file);
    }

    return 0;
}