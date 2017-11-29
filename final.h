#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<libgen.h>
#include<stdlib.h>
#include<dirent.h>
#include<stdbool.h>
#include<time.h>

#define SUCCESS 0
#define FAIL 2
#define MAXPATHSIZE 1024
#define READ 1
#define WRITE 2
#define FILENOTFOUND 404
#define SERVERERROR 500
#define MAXFILENAME 1024
#define NAME "SWS-GROUP3"

int sendfile(int to_fd, char* path);
int senddir(int to_fd,  char* path);

int senderror(int to_fd, int errorcode);
int send_response(int socket_fd, time_t modified_time, char* buff, char* content_type, int response_type);
int comparator(const void* first, const void* second);

