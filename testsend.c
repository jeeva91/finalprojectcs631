#include"final.h"

int main(void){

  int fd[2];
  pid_t pid;
  char buff[8];
  char* path = "/cygdrive/c/users/jee11/onedrive/documents/fall 17/jramana1-hw1/final_project/hello";
  if(pipe(fd)<0){
    perror("pipe error");
    exit(-1);
  }

  if((pid = fork())<0){
    perror("fork error");
    exit(-1);
  }
  if(pid>0){ //parent

    close(fd[0]);
    if(sendfile(fd[1], 0, path)<0){
      perror("sendifle error");
      exit(-1);
    }
    
  }
  else{

    close(fd[1]);
    int n;
    n = read(fd[0], buff, 8);
    printf("read from the file:%s\n", buff);
  }

  return 0;
}
