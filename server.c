//include header files here

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERV_PORT 6000

int main(int argc, char **argv){
//declare variable here

int listenfd,connfd,clilen,childpid,n1;
struct sockaddr_in servaddr,cliaddr; 
char msg1[512];

listenfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);
bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
listen(listenfd, 5);
for(;;) {
 clilen = sizeof(cliaddr);
 connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
 if ((childpid = fork()) == 0) {
 close(listenfd);
 n1 = read(connfd, msg1, 512);
 printf("%s\n",msg1);
 write(connfd, msg1, 50);
 bzero(&msg1,sizeof(msg1));
 close(connfd);
 exit(0);
 }
 close(connfd);
}
}
