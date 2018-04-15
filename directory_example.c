#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(void)
{
  struct dirent *de;  // Pointer for directory entry

  // opendir() returns a pointer of DIR type.
  DIR *dr = opendir(".");

  if (dr == NULL)  // opendir returns NULL if couldn't open directory
  {
      printf("Could not open current directory" );
      return 0;
  }

  // for readdir()
  while ((de = readdir(dr)) != NULL)
          printf("%s\n", de->d_name);

  closedir(dr);
  system("ls");
  return 0;
}
