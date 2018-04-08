//khyati seth 2016050
//ahilya sinha 2016009
//group id - 7
  

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
 
FILE *fp;

void print_exit()
{
 printf("ERROR - restart socket");
}
 
struct connect_user
{
char id[100];
int socket;
}
u[1000];
pthread_t thread;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char buf_msg[256];
char user[100];
char message[100];
char pass[30];
struct sockaddr_in serv_addr, cli_addr;
int x;
int nu = 1;
int i;

void print_format()
{
 printf("ERROR - formatting incorrect");
 //printf("%d\n",socket);
}
void* server(void*);

int main (int argc, char *argv[]) 
{
 
      fp=fopen("sock_info.txt","w");
      fclose(fp);
      int i;
      int sockfd;
      int new_socket[1000];
      int port;
      int userstr;
      int no = 0;
      int x;  
       sockfd = socket(AF_INET, SOCK_STREAM, 0);
         
       if (sockfd < 0)
       {
          print_exit();
          exit(0);
       } 
      memset((char *) &serv_addr,0,sizeof(serv_addr));
         
       port = atoi(argv[1]);
       serv_addr.sin_family = AF_INET;
       serv_addr.sin_addr.s_addr = INADDR_ANY;
       serv_addr.sin_port = htons(port);
         
       if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
          print_exit();
          exit(0);
        } 
        listen(sockfd, 5);
        userstr = sizeof(cli_addr);
      while(1)
      {
           new_socket[no] = accept(sockfd, (struct sockaddr *)&cli_addr, &userstr);
            if (new_socket < 0)
            {
               print_exit();
              exit(0);
            }
           
          pthread_mutex_lock(&mutex);
          pthread_create(&thread,NULL,server,(void*)&new_socket[no]);
          no++;
       
      }
      close(new_socket[no]); 
      close(sockfd);
      return 0;
         
 }
 
void* server(void* sock)
{
int new_socket=*((int*)sock);
int j=0;
int m;
char to[100];
char from[100];
char name[100];
fp=fopen("sock_info.txt","r+");
checking:
    m=1;
    memset(user,0,100);
    memset(to,0,100);
    memset(from,0,100);
    memset(message,0,100);
    recv(new_socket,user,100,0);
    recv(new_socket,pass,30,0);
    while(fscanf(fp,"%s",message)!=EOF)
    {
        
        if(strncmp(user,message,strlen(message))==0)
        {
          m=2;
          fscanf(fp,"%s",message);
        }
 
    }
if(m==1)
{
    fclose(fp);
    send(new_socket,"reg",3,0);
    bzero(u[nu].id,100);
    u[nu].socket=new_socket;
    strncpy(u[nu].id,user,strlen(user));
    nu++;
}
if(m==2)
{
    fclose(fp);
    send(new_socket,"log",3,0);
    for(i=1;i<nu;i++)
    if(strcmp(user,u[i].id)==0)
    break;
    u[i].socket=new_socket;
}
pthread_mutex_unlock(&mutex);
 
bzero(buf_msg, 256);
int newsockfd1;
while(1)
{ 
 
  if(recv(new_socket, buf_msg, 255, 0) < 0)
  {
     print_exit();
     print_format();
    exit(0);
  }
i=3;
strcpy(name,buf_msg);
while(name[i]!=':')
{
  to[i-3]=name[i];
  i++;
}
to[i]='\0';
j=0;
memset(buf_msg,0,256);
while(name[i]!='|')
{
  buf_msg[j]=name[i];
  i++;
  j++;
}
buf_msg[j]='\0';
j=0;
for(i+=1;name[i]!='\0';i++)
{
  from[j]=name[i];
  j++;
}
from[j-1]='\0';
printf("Receiver is %s and Sender is %s Message is :- %s",to,from,buf_msg);
j=1; 
while(j<nu)
{
    if((strncmp(u[j].id,to,strlen(to)))==0)
    {
    newsockfd1=u[j].socket;
    break;
    }
j++;
}
strcat(from,buf_msg);
memset(buf_msg,0,256);
strcpy(buf_msg,"From ");
strcat(buf_msg,from); 
if(send(newsockfd1,buf_msg,sizeof buf_msg,0)<0)
  {
    send(new_socket, "FAIL",4,0); 
  }
  else
  {
   if (send(new_socket, "SUCCESS", 18, 0)<0)
    {
      print_exit();
      exit(0);
    }
  }
}
close(new_socket);
pthread_exit(NULL);
}