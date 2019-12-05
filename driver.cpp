/**
* Author: Christopher Mannes
* Student ID: 20743505
*
* ECE 650 - Methods and Tools for Software Engineering
* Assignment 3 - Driver code for concurrent programs.
*/

/**
 * Import header files.
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>

/**
 * Import libraries.
 */
#include <iostream>
#include <vector> 

using namespace std;

/**
 * Function for sending an error message to stderr.
 */ 
void error(string str)
{
    // Output error message.
    cerr << str << endl;
}

/**
 * Enter main driver program.
 */
int main(int argc, char * argv[]) {

    vector<pid_t> childrenPIDs;

    // Create pipes.
    int pipeDBToBFS[2];
    int pipeRgenToDB[2];
    int pipeParentToRgen[2];

    pipe(pipeDBToBFS);
    pipe(pipeRgenToDB);
    pipe(pipeParentToRgen);

    // Fork main process.
    pid_t pid, wpid;
    int status;
    pid = fork();

    if (pid < 0)
    {
        error("Error: Child 1 process generation failed.");

        return 1;
    }
    else if (pid == 0)
    {
        dup2(pipeDBToBFS[0], 0);
        close(pipeDBToBFS[0]);
        close(pipeDBToBFS[1]);

        char * argv[2];
        argv[0] = (char *)"./bfs";
        argv[1] = nullptr;

        execvp(argv[0], argv);
    }
    
    childrenPIDs.push_back(pid);

    pid_t pid2, wpid2;
    int status2;
    pid2 = fork();

    if (pid2 < 0)
    {
        error("Error: Child 2 process generation failed.");

        return 1;
    }
    else if (pid2 == 0)
    {
        dup2(pipeRgenToDB[0], 0);
        close(pipeRgenToDB[0]);
        close(pipeRgenToDB[1]);

        dup2(pipeDBToBFS[1], 1);
        close(pipeDBToBFS[0]);
        close(pipeDBToBFS[1]);

        char * argv[2];
        argv[0] = (char *)"./graphDB.py";
        argv[1] = nullptr;

        execvp(argv[0], argv);
    }

    childrenPIDs.push_back(pid2);

    pid_t pid3, wpid3;
    int status3;
    pid3 = fork();

    if (pid3 < 0)
    {
        error("Error: Child 3 process generation failed.");

        return 1;
    }
    else if (pid3 == 0)
    {
        dup2(pipeParentToRgen[0], 0);
        close(pipeParentToRgen[0]);
        close(pipeParentToRgen[1]);

        dup2(pipeRgenToDB[1], 1);
        close(pipeRgenToDB[0]);
        close(pipeRgenToDB[1]);

        char * argv[2];
        argv[0] = (char *)"./rgen";
        argv[1] = nullptr;

        execvp(argv[0], argv);
    }
    else if (pid3 > 0)
    {
        childrenPIDs.push_back(pid3);

        dup2(pipeParentToRgen[1], 1);
        close(pipeParentToRgen[0]);
        close(pipeParentToRgen[1]);

        string args;
        args = argv[0];

        if (argc > 1)
        {
            for (int i = 1; i < argc; i++)
            {
                args.append(argv[i]);
            }
            cout << args << endl;
        }
        else
        {
            cout << args << endl;
        }

        dup2(pipeDBToBFS[1], 1);
        close(pipeDBToBFS[0]);
        close(pipeDBToBFS[1]);

        string driverInput;

        while (!cin.eof())
        {
            getline(cin, driverInput);

            cout << driverInput << endl;
        }

        // Send kill signal to all children.
        vector<pid_t>::iterator it;
        for (it = childrenPIDs.begin(); it != childrenPIDs.end(); it++)
        {
            int status;
            kill(*it, SIGTERM);
            waitpid(*it, &status, 0);
        }
    }

    return 0;
}