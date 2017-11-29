/* Program reads and copies the file to fd
 *input: source and fd for the socket or pipe. fd of the log file
 *output: the file will be sent to the given fd
 *log file will be updated
 *author: jeeva
 *date: 11/26/2017
 */

#include"final.h"

int sendfile(int to_fd, int log_fd, char* path){
  size_t buffsize;
  char* buff;
  //  char* currentbuffptr;
  struct stat sb;
  int source;
  int nr;
  int nw;
  
  //find the size of the file

  if(stat(path, &sb)!=0){
    //senderror(to_fd, FILENOTFOUND);
    fprintf(stderr, "'stat' failed for '%s': %s.\n",
	    path, strerror (errno));
    return FAIL;
  }
  buffsize = sb.st_size + 20;

  if((buff = malloc(buffsize))==NULL){
    //senderror(to_fd, SERVERERROR);
    fprintf(stderr, "Unable to allocate memory: for file:%s error: %s\n",
	    path, strerror(errno));
    return FAIL;
  }
  // currentbuffptr = buff;
  
  //open the file
  if((source = open(path, O_RDONLY))<0){
    // senderror(to_fd, FILENOTFOUND);
    fprintf(stderr, "'stat' failed for '%s': %s.\n",
	    path, strerror (errno));
    return FAIL;
  }

  while((nr = read(source, buff, 8)) !=-1 && nr!=0){
   
    	if((nw = write(to_fd, buff, nr)) != -1 && nw !=0)
	  ;
	else {
	  fprintf(stderr, "%s\n", strerror(errno));
	  return FAIL;
	}
    
  }
  
  
  
  
  return 0;
  
}




  
