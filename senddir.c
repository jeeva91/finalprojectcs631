/*final project sws 
 *program name: senddir.c
 *program to send the directory details given in the path to the given fd
 *author:jeeva
 *date: 11/28/2017
 */

#include"final.h"
int comparator(const void* first, const void* second);

int
senddir(int to_fd, char* path){
  DIR* dp;
  struct dirent *dirp;
  char* current_fileptr;
  char* fileptr;
  size_t fileptr_size;
  size_t nw;
  size_t fptr_cnt;
  char* buff;
  size_t i;
 
  fptr_cnt =0;
  fileptr_size =5;
   
  if((fileptr = (char*)malloc(fileptr_size*MAXFILENAME))==NULL){

    //senderror()internal server error;
    perror("malloc failed");
    exit(-1);
  }
  current_fileptr = fileptr;
  if((dp = opendir(path))==NULL){

    /* send the internal server error */
    perror("unable to opent the dir");
    exit(-1);
  }
  while((dirp = readdir(dp)) != NULL){
    if(dirp->d_name[0]=='.'){
      continue;
    }
    else{
    
    if(fileptr_size <= fptr_cnt){
      fileptr_size = fileptr_size*2;
      if((fileptr = (char*) realloc((void *)fileptr,
				    fileptr_size*MAXFILENAME))==NULL){
	//senderror()internal server error;
	perror("malloc failed");
	exit(-1);
      }
    }
    current_fileptr = fileptr +fptr_cnt*MAXFILENAME;
    strcat(current_fileptr, dirp->d_name);
    current_fileptr+=MAXFILENAME;
    fptr_cnt +=1;
    }

    
    
  }

  /* 
   *call the logger
   */

  qsort((void*)fileptr, fptr_cnt, MAXFILENAME, comparator);

  if((buff = malloc(fptr_cnt*MAXFILENAME))==NULL){
    //senderror()internal server error;
    perror("malloc failed");
    exit(-1);
  }
  current_fileptr = fileptr;
  for(i=0;i<=fptr_cnt;i++){
    strcat(buff, current_fileptr);
    strcat(buff, "\n");
    current_fileptr+=MAXFILENAME;
  }
  send_response(to_fd, 0, buff, "Text", 200);
  /*
    if((nw=write(to_fd, fileptr, strlen(fileptr)))<strlen(fileptr)){
    //senderror()internal server error;
    perror("write failed");
    exit(-1);
    
    }*/
  nw = strlen(buff);
  free(fileptr);
  free(buff);

  return nw;
}

int comparator(const void* first, const void* second){
  //char* f = (char*) first;
  //char* s = (char*) second;
  return strcmp((char*)first,(char*)second);
}
  
