//
//  shell.h
//  CS232 Command Shell
//
//  Author: Coleman Ulry
//  Date: 2/28/21
//  h class to run program
//
#ifndef SHELL_H
#define SHELL_H

#include "commandline.h"
#include "prompt.h"
#include "path.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Shell
{
public:
  Shell(){};
  void run();

private:
  Prompt prompt;
};

#endif /* defined(__CS232_Command_Shell__commandline__) */
