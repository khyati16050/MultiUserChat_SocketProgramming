//khyati seth 2016050
//ahilya sinha 2016009
//group id - 7
	

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<pthread.h>
pthread_t thread;
void print_format()
{
 printf("ERROR - formatting incorrect");
}
void* receive(void* d)
{
    int sockfd=*((int *)d);
    int a;
    char buf[256];
    while(1)
    {
    memset(buf,0,256);
    a=recv(sockfd,buf,255,0);
    if(a>0)
      {
        printf("\n %s\n ",buf);
      }
    else
      {
        print_format();
        exit(0);
      }
    }
    close(sockfd);
    pthread_exit(NULL);
}
void print_exit()
{
 printf("ERROR - restart socket\n");
 //printf("%d\n",sockfd);
}

int main (int argc, char *argv[]) 
{
  int sockfd;
  int port;
  int n;
  int new_socket;
  char user[100];
  char pass[100];
  struct sockaddr_in addr_in, serv_addr;
  struct hostent *server;
  char buf_msg[256];
  FILE *file;
  port=atoi(argv[2]);
  server=gethostbyname(argv[1]);
  sockfd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if ((sockfd<0)||(server==NULL) )
     {
      print_exit();
      exit(0);
     }
      memset((char*)&serv_addr,0,sizeof(serv_addr));
      serv_addr.sin_family=AF_INET;
    bcopy(((char*)server->h_addr), ((char*)&serv_addr.sin_addr.s_addr), (server->h_length));
    serv_addr.sin_port=htons(port);
    new_socket = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
    if (new_socket >= 0)
    {
     
      memset(user,0,100);
      printf("\nuserid of the user -: ");
        fgets(user,100,stdin);
        n=send(sockfd, user, strlen(user), 0);
      printf("\npassword of the user -: ");
      fgets(pass,100,stdin);
      n=send(sockfd, pass, strlen(pass), 0);
      memset(buf_msg,0,256);
      n=recv(sockfd,buf_msg,255,0);
      if(n > 0)
      printf("%s\n",buf_msg);
    }
    else
    {
      print_exit();
      exit(0);
    }
file=fopen("sock_info.txt","a+");
char message[100];
memset(message,0,100);
if(strcmp(buf_msg,"reg")==0)
{
fprintf(file,"%s",user);
fprintf(file,"\n%s\n",pass);
}
fclose(file);
pthread_create(&thread,NULL,receive,(void*)&sockfd);
while(1)
{
  printf("\nMessage:- ");
  memset(buf_msg,0,256);
  fgets(buf_msg, 255, stdin);
  {   
      if((strncmp(buf_msg,"To user-",8)==0))
      {
        sprintf(buf_msg,"%s|%s",buf_msg,user);
        if(send(sockfd, buf_msg, strlen(buf_msg), 0) < 0)
        {
          print_exit();
          print_format();
          exit(0);
        }
      }
            
    }
  }
    close(sockfd); 
    
   return 0;
    
}

void* server(void* sock)
{
int new_socket=*((int*)sock);
int j=0;
int m;
char buf_msg[1000];
int new_socket1;
char reciever[100];
char sender[100];
strcpy(buf_msg,"From ");
strcat(buf_msg,sender); 
if(send(new_socket1,buf_msg,sizeof buf_msg,0)<0)
  send(new_socket, "FAIL",4,0); 
else
{
   if (send(new_socket, "SUCCESS", 18, 0)<0)
    {
      print_exit();
      exit(0);
    }
}

close(new_socket);
pthread_exit(NULL);
}
