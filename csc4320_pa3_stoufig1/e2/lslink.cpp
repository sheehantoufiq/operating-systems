#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <string>
#include <grp.h>
#include <pwd.h>
#include <time.h>

int main(int argc, char **argv)
{
  //check that we have a command line arg
  if (argc < 2){
    std::cout << "Usage is \'command\' <path to file>\n";
    std::cin.get();
    exit(0);
  }
  else{

    //set our file as the argument
    char* file;
    file = argv[1];

    long long size; //st_size can be a 64-bit int.
    struct stat *buf = new struct stat();
    errno = 0; //always set errno to zero first.

    //this is how you can tell if something is a symlink
    int pathBuffSize = 256;
    char *pathBuff = (char *)malloc(pathBuffSize);
    char target_path[256];
    int len = readlink(file, target_path, pathBuffSize);

    if (len >= 0){

      //if a non-negative number is returned we have a symlink
      std::cout << "\nSymbolic Link" << std::endl;

      //get a struct dealing with the group and password.
      //look at the man pages of these functions.
      //you will have to use the uit_t and gid_t returned from the stat functions
      struct passwd* pw = getpwuid(1);
      struct group* gr = getgrgid(1);
      target_path[len] = '\0';

      printf("\nFile Name: \"%s\"", file);
      printf (" -> %s\n\n", target_path);

    }
    else{
      std::cout << "\nNot Symbolic Link" << std::endl;
      printf("\nFile Name: \"%s\"\n\n", file);

    }

    //this gets you the stats of a file
    if (stat(file, buf) == 0)
    {
      long long ln = buf->st_nlink;
      struct passwd *uid = getpwuid(buf->st_uid);
      struct group *gid = getgrgid(buf->st_gid);
      size = buf->st_size;
      long long blocks = buf->st_blocks;

      struct stat results;  
      stat(file, &results);

      

      printf("File Permissions: ");
      printf( (S_ISDIR(results.st_mode)) ? "d" : "-");
      printf( (results.st_mode & S_IRUSR) ? "r" : "-");
      printf( (results.st_mode & S_IWUSR) ? "w" : "-");
      printf( (results.st_mode & S_IXUSR) ? "x" : "-");
      printf( (results.st_mode & S_IRGRP) ? "r" : "-");
      printf( (results.st_mode & S_IWGRP) ? "w" : "-");
      printf( (results.st_mode & S_IXGRP) ? "x" : "-");
      printf( (results.st_mode & S_IROTH) ? "r" : "-");
      printf( (results.st_mode & S_IWOTH) ? "w" : "-");
      printf( (results.st_mode & S_IXOTH) ? "x" : "-");
      printf("\n");

      printf("Links: %lld \n", ln);
      printf("Owner: %s \n", uid->pw_name);
      printf("Group: %s \n", gid->gr_name);

      struct tm *mod = localtime(&buf->st_mtime);
      char buffer [80];
      strftime(buffer,80,"Last modified: %a %h %d %I:%M%p %G.",mod);
      puts(buffer);

      printf("Size in bytes: %lld bytes.\n", size);
      printf("Size in blocks: %lld \n", blocks);
    }
    else
    {
      perror(file);    //if stat fails, print a diagnostic.
    }

    //this gets you the stats of a symbolic link
    if (lstat(file, buf) == 0)
    {
      size = buf->st_size;
      if (S_ISLNK(buf->st_mode)){
        std::cout << "This can be used to see if we have a symbolic link,\n there are more macros too, check stat 2 man page for more!" << std::endl;
        std::cout << "But be careful, the normal stat function follows the\n symbolic link to the actual file!!"<<std::endl;
      }
      printf("Size of symlink \"%s\" is %lld bytes.\n\n", file, size);
    }
    else
    {
      perror(file);    //if lstat fails, print a diagnostic.
    }

    delete buf;
    free(pathBuff);
    exit(errno);
  }
}