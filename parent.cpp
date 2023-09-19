#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <fcntl.h>

using namespace std;

int main (int argc, char *argv[]){

    string file_name;
    cin >> file_name;

    int file = open(file_name.c_str(), O_RDONLY | O_CREAT, 0777);
    if (file == -1){
		cerr << "Error of opening file!\n";
		return -1;
	}


    int fd[2]; // fd[0] - read; fd[1] - write
    // Creating pipe and checking that it was created
    if (pipe(fd) == -1)
    {
        cerr << "Pipe creation failed\n";
        return 1;
    }


    // Forking the process
    int id = fork();
    if (id == -1) // fork error
    {
        cerr << "Could not fork a process";
        return 2;
    }
    if (id == 0) { //child process

        dup2(file, 0);
        if (dup2(fd[1], 1) == -1){
			cerr << "dup2 err\n";
			return 5;
		}
        close(fd[0]);
        close(file);
        execlp("./child", "./child", NULL);

        cerr << "Couldn't start child process\n";
        return 3;

    } else { //parent process

        close(fd[1]);
        dup2(fd[0], 0);
        int answer;
        cin >> answer;
        cout << answer << endl;
        close(fd[0]);
        close(file);
    }

    cout << "Processes ended succesfully\n";

    return 0;
}