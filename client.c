//include file here

#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv){
//declare variables here
int sockfd,n;
struct sockaddr_in servaddr;
char sendline[512],recvline[512];

if (argc != 2) printf("usage tcpcli <ipaddress>\n");
sockfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(6000);
servaddr.sin_addr.s_addr = inet_addr(argv[1]);
connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
fgets(sendline, 512, stdin);
n = strlen(sendline);
write(sockfd, sendline, n);
n = read(sockfd, recvline, 512);
if (n < 0) printf("error reading\n");
recvline[n] = 0;
fputs(recvline, stdout);
exit(0);
}
