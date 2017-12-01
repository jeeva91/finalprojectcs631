/* Program reads and copies the file to fd
 *input: source and fd for the socket or pipe. fd of the log file
 *output: the file will be sent to the given fd
 *log file will be updated
 *author: jeeva
 *date: 11/26/2017
 */

#include"final.h"
#include<magic.h>

int sendfile(int to_fd, time_t ltime, char* path){
  size_t buffsize;
  char* buff;
  char* filetype;
  magic_t magic_cookie;
  //  char* currentbuffptr;
  struct stat sb;
  int source;
  int nr;
  int nw;
  FILE* f;
  size_t content_size;
  
  
  
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

  if((magic_cookie = magic_open(MAGIC_NONE)==NULL){
      if((filetype = (char*)malloc(10))==NULL){
	perror("malloc failed");
      }
      strcat(filetype, "unknown");
    }
  if (magic_load(magic_cookie, NULL) != 0) {
	        printf("cannot load magic database - %s\n", magic_error(magic_cookie));
	        magic_close(magic_cookie);
	        //return 1;
	    }
    file_type = magic_file(magic_cookie, path);
    //printf("%s\n", magic_full);
    magic_close(magic_cookie);


    f=fopen(path, "rb");
    fread(buff, sb.st_size, 1, f);
    fclose(f);

    content_size = strlen(buff)

    send_response(to_fd, sb.st_mtime, buff, file_type, 200);
    free(buff);
      
  // currentbuffptr = buff;
  /*
  //open the file
  if((source = open(path, O_RDONLY))<0){
    // senderror(to_fd, FILENOTFOUND);
    fprintf(stderr, "'stat' failed for '%s': %s.\n",
	    path, strerror (errno));
    
    return FAIL;
  }

  while((nr = read(source, buff, sb.st_size)) !=-1 && nr!=0){
   
    	if((nw = write(to_fd, buff, nr)) != -1 && nw !=0)
	  ;
	else {
	  fprintf(stderr, "%s\n", strerror(errno));
	  return FAIL;
	}
    
  }
  */
  
  
  
  return strlen;
  
}




  
