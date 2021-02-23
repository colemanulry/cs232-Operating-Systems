/*
 * Author: Coleman Ulry
 * Date: 2/19/21
 * Written in C
 * Copies content from src file into dest file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

  FILE *src, *dest;
  // variable used to copy characters
  char content;

  // conditional if to ensure 3 inputs, copy and two files
  // reference on using stderr and fprintf: https://stackoverflow.com/questions/39002052/how-i-can-print-to-stderr-in-c
  if (argc != 3)
  {
    fprintf(stderr, "You need to pass in two files... (i.e ./copy src dest)  \n");
    return -1;
  }

  // condition if dest file already exists
  // if fopen can't find file to open, then it doesn't exist within the directory
  // reference to using fopen(): https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm
  if (fopen(argv[2], "r") != NULL)
  {
    // error message
    fprintf(stderr, "Destination file %s", argv[2]);
    fprintf(stderr, " already exists. \n");
    return -1;
  }

  // open source file - read from
  src = fopen(argv[1], "r");

  // condition if src file does not exist, return -1
  if (src == NULL)
  {
    // error message
    fprintf(stderr, "Source file %s does not exist... \n", argv[1]);
    fprintf(stderr, "Make sure file exists, and ensure correct spelling. \n");
    return -1;
  }

  // only do this if source file was successfully found
  // open destination file - write to
  dest = fopen(argv[2], "w");

  // read contents from src
  // reference to using fgetc and fputc: https://www.geeksforgeeks.org/fgetc-fputc-c/
  content = fgetc(src);

  // while pointer hasn't reached the end of the file, copy content from src to dest
  while (content != EOF)
  {
    // put content into dest
    fputc(content, dest);

    // next character
    content = fgetc(src);
  }

  // copying worked successfully
  return 0;

  // close files
  fclose(src);
  fclose(dest);
}