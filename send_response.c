/* project sws group3
 * send_response 
 * input: socket, time_modified, buff, repsoncetype, content_type
 * output: put all the above details together, and send to the socket
 * author:jeeva
 * date: 11/28/2017
 */

#include"final.h"
#include<time.h>
#include<stdbool.h>

int send_response(int socket_fd, time_t modified_time, char* content, char* content_type, int status_code){
  char* buff;
  size_t buff_size;
  struct tm tm;
  char date_buff[50];
  time_t now;
  char content_size[10];
  size_t nw;
  
  buff_size = strlen(content) + 300;
  if((buff = (char*) malloc(buff_size))==NULL){
    send_response(socket_fd, 0, "", "", 300);
    perror("malloc failed");
    return -1;
  }
  strcat(buff, "HTTP/1.0 ");
  switch(status_code){
  case 200:
    strcat(buff, "200 OK\n");
    break;
  case 201:
    strcat(buff, "201 Created\n");
    break;
  case 202:
    strcat(buff, "202 Accepted\n");
    break;
  case 204:
    strcat(buff, "204 No Content\n");
    break;
  case 301:
    strcat(buff, "301 Moved Permanently\n");
    break;
  case 304:
    strcat(buff, "304 Not Modified\n");
    break;
  case 400:
    strcat(buff, "400 Bad Request\n");
    break;
  case 401:
    strcat(buff, "401 Unauthorized\n");
    break;
  case 403:
    strcat(buff, "401 Forbidden\n");
    break;
  case 404:
    strcat(buff, "404 Not Found\n");
    break;
  case 500:
    strcat(buff, "500 Internal SErver Error\n");
    break;
  case 501:
    strcat(buff, "501 Not Implemented\n");
    break;
  case 502:
    strcat(buff, "502 Bad Gateway\n");
    break;
  case 503:
    strcat(buff, "503 Service Unavailable\n");
    break;
  }

  now = time(0);
  tm = *gmtime(&now);
  strftime(date_buff, sizeof(date_buff), "%a, %d %b %Y %H:%M:%S %Z", &tm);
  strcat(buff, "Date: ");
  strcat(buff, date_buff);
  strcat(buff, "\n");
  
  strcat(buff, "Server: ");
  strcat(buff, NAME);
  strcat(buff, "\n");
      
  if(modified_time>0){
    tm = *gmtime(&modified_time);
    strftime(date_buff, sizeof(date_buff), "%a, %d %b %Y %H:%M:%S %Z", &tm);
    strcat(buff, "Last-Modified: ");
    strcat(buff, date_buff);
  }

  strcat(buff, "Content-Type: ");
  strcat(buff, content_type);
  strcat(buff, "\n");
  
  strcat(buff, "Content-Length: ");
  strcat(buff, itoa(strlen(content), content_size, 10));
  strcat(buff, "\n\n");
  strcat(buff, content);
  if((nw = write(socket_fd, buff, strlen(buff)+1))!=(strlen(buff)+1)){
    perror("unable to write to the socket");
  }
  
  
  return 0;
}

