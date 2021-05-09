#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

void func(int sockfd)
{
 char buff[80];
 int a;
  for(;;)
{
  bzero(buff, 80);
  read(sockfd,buff,sizeof(buff));
  
  printf("From Server : %s\t to Client : ", buff);
  bzero(buff,80);
  a=0;
  while((buff[a++] = getchar()) != '\n');
  
write (sockfd,buff,sizeof(buff));
if (strncmp("exit",buff,4) == 0)
{
   printf("Server Exit...\n");
   printf("   WELCOME TO WHATSAPP   ");
   break;
}
}
}
int main()
{
  int sockfd,connfd,len;
  struct sockaddr_in servaddr,client;
  

//Create socket
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd ==-1)
{
 printf("Creating Socket Failed.\n");
 exit(0);
}
else
printf("Creating Socket Was Succesful.\n");
bzero(&servaddr,sizeof(servaddr));
//asign
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(8888);
//Bind
if((bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))) !=0)
{
printf("Binding failed\n");
exit(0);
}
else
printf("Binding done\n");
//Listen
if((listen(sockfd,3)) !=0)
{
printf("Listen failed..\n"); 
exit(0);
}
else
  printf("Server listening..\n");
len=sizeof(client);
//Accept data
connfd =accept(sockfd,(struct sockaddr*)&client,&len);
if(connfd<0)
{
printf("Accepting server failed\n");
exit(0);
}
else
{
printf("Accepting server success/n");
printf("You can start send a message now\n");
printf("If want to end the chat, please press [ctrl+c].\n\n");
printf("          WHATSAPP CHAT ROOM          \n\n ");
}
//function for chat
func(connfd);
//close the socket
close(sockfd);
}
