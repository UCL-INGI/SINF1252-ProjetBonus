/*Vous développez un gestionnaire de logs (historique d'événements).
Pour cela, vous voulez coder une fonction void writeToLogs(char *dir, char *msg) qui va 
ajouter une ligne à tous les fichiers finissant par l'extension ".log" du dossier associé au 
chemin dir. Cette ligne contiendra msg et finira par un retour à la ligne. 
Il n'y a pas de sous-dossiers.*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h> /*strrchr*/
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "student_code.h"

void writeToLogs(char *dir, char *msg)
{
  DIR *dirp;
  struct dirent *dp;

  //file descriptor
  int fd;

  dirp = opendir(dir);
  if(dirp==NULL)
  {
    perror("error opening the directory\n");
    exit(EXIT_FAILURE);
  }

  char *extension = "";
  char *log_extension = "";

  while((dp = readdir(dirp)) != NULL)
  {
    if(dp->d_type==DT_REG)
    {

      // looking for the files with extensions
      extension = strrchr(dp->d_name, '.'); //find the last dot 
      if (!extension) 
	{
	  printf("This file has no extension\n");
	} 
      
      else // files with extension .log
	{
	 // printf("extension is %s\n", extension + 1);
	  log_extension = extension + 1;
	  // among the files with extensions, find the ones with '.log' extension
	  if(strcmp(log_extension,"log") == 0)
	    {
	      printf("the log file is: %s\n", dp->d_name); 
	      fd = open(dp->d_name, O_WRONLY|O_APPEND); // the file is open to write in 
	      if(fd == -1)
	       {
		 perror("error opening the file\n");
		 exit(EXIT_FAILURE);
	       }
	      
	      if(write(fd, (void*) msg, strlen(msg)) == -1) 
	      {
		perror("error writing in the file\n");
		exit(EXIT_FAILURE);
	      }

	      if(write(fd, (void*) "\n", sizeof(char)) == -1) 
	      {
		perror("error writing in the file\n");
		exit(EXIT_FAILURE);
	       }

	      if(close(fd)==-1)
	      {
		perror("error closing file\n");
		exit(EXIT_FAILURE);
	      } 
	    }
	} 
    }  
  }
   

  // closing the directory
  int err = closedir(dirp);
  if(err<0)
    {
      perror("error writing in the file\n");
      exit(EXIT_FAILURE);
    }
}

/*

int main(int argc, char* argv[])
{
  char name[] = "../Test1";
  writeToLogs(name, "hello");
  return(EXIT_SUCCESS);
}
*/
