#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "curl.h"

#define oops(msg) { perror(msg); exit(-1); }

struct sockaddr_in bba;
struct hostent *hp;
FILE *rf; int s, rfd, ch;

char * hostname;
int portnum;

char * curl(h,b,o)
struct headers h;
char * b;
struct options o;
{
  char message[1024];
  bzero(message,1024);
  if (strlen(h.host) == 0) {
    printf("No host given!\n");
    return "";
  }

  hostname = "htpc.elliot.lan";
  

  bzero(&bba, sizeof(bba));
  bba.sin_family = AF_INET;

  hostname = h.host;
  portnum = o.port;

  hp = gethostbyname(hostname);
  if (hp == NULL) oops("no such computer");
  bcopy(hp->h_addr, &bba.sin_addr, hp->h_length);
  bba.sin_port = htons(portnum);

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1) oops("socket");
  if (connect(s, &bba, sizeof(bba)) != 0)
    oops("connect");

  /*message = "GET / HTTP/1.1\r\n\r\n";*/
  
  switch (h.method) {
    case POST:
      strcpy(message,"POST");
      break;
    case HEAD:
      strcpy(message,"HEAD");
      break;
    case GET:
    default:
      strcpy(message,"GET");
      break;
    }

  strcat(message," ");
  strcat(message,h.path);
  strcat(message," HTTP/1.1\r\nHost: ");
  strcat(message,h.host);
  strcat(message,"\r\n\r\n");
  if (h.method == POST) {
    strcat(message,b);
    strcat(message,"\r\n\r\n");
  }

  printf("Request:\n%s\n",message);


  rf = fdopen(s, "rw");
  if (rf == NULL) oops("fdopen");

  send(s,message,strlen(message),0);

  while ((ch = getc(rf)) != EOF)
    putchar(ch);
  fclose(rf);
  printf("\n");
  return "";
}
