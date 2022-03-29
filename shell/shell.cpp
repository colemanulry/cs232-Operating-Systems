//
//  shell.cpp
//  CS232 Command Shell
//
//  Author: Coleman Ulry
//  Date: 2/28/21
//  cpp class that runs shell program
//

#include "shell.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void Shell::run()
{

  // infinite loop
  while (true)
  {

    //cout getter method from prompt class
    cout << prompt.get() << flush;

    // class objects
    Path myPath;
    CommandLine commandline(cin);
    string command = commandline.getCommand();

    if (commandline.getArgCount() != 0)
    {
      // handles exit command
      if (command == "exit")
      {
        cout << "See you soon!" << endl;
        exit(0);
      }

      // handles cd command
      if (command == "cd")
      {
        if (commandline.getArgCount() != 2)
        {
          cerr << "Wrong number of arguments..." << endl;
        }
        else
        {
          if (chdir(commandline.getArgVector(1)) == -1)
          {
            cerr << "cd not successful... " << endl;
          }
          else
          {
            prompt = Prompt();
          }
        }
      }

      // // handles pwd command
      if (command == "pwd")
      {
        if (commandline.getArgCount() != 1)
        {
          cerr << "Wrong number of arguments... " << endl;
        }
        else
        {
          string wd = prompt.getCwd();
          cout << wd << endl;
        }
      }

      else
      {
        // fork child process
        pid_t proc = fork();

        // check value of proc
        if (proc)
        {
          // check ampersand boolean variable
          if (commandline.noAmpersand())
          {
            // wait until the child terminates, https://linux.die.net/man/2/waitpid
            waitpid(proc, NULL, 0);
          }
        }
        else
        {

          // create path variable
          string path = myPath.getDirectory(myPath.find(commandline.getCommand())) + '/' + commandline.getCommand();

          // reference: https://man7.org/linux/man-pages/man2/execve.2.html
          execve(path.c_str(), commandline.getArgVector(), NULL);
        }
      }
    }
  }
}