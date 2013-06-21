/* A simple server in the internet domain using TCP
 The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

/*
struct sockaddr_in
{
    short   sin_family; // must be AF_INET
    u_short sin_port;
    struct  in_addr sin_addr;
    char    sin_zero[8]; //Not used, must be zero
};
*/

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    
    socklen_t clilen;
    char buffer[256];
    
    struct sockaddr_in serv_addr, cli_addr;
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    //AF_INET specifies internet domain(as opposed to UNIX) and SOCKS_STREAM specifies tcp/ip 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //creating socket. returns filedescriptor
    if (sockfd < 0) 
        error("ERROR opening socket"); 
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET; //again specifing internet domain
    
    //sin_addr is a structure that contains only one field, s_addr, which contains the host IP address
    //for server code, this will always be the IP of the machine in which the server is running.
    serv_addr.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY is a symbolic constant that gets the current IP.
    
    serv_addr.sin_port = htons(portno); //converts port number from host to network byte order which is Big Endian
    
    //bind system call binds a socket to an address/portnumber combo. Takes three args,
    //the socket file descriptor, the address to which is bound, and size of address. Second arg is a slightly diferent
    //type of struct, so we have to cast it.
    if ( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    
    listen(sockfd,5); //allos process to listen on the socket for connections. the 2nd arg is the size of the backlog queue
                      //(the num of connections that can be waiting while the process is handling
    
    clilen = sizeof(cli_addr);
    //accept blocks process till a client connects to server.
    //RETURNS: a new file descriptor that you use from here on. 
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, //2nd arg is a ref pointer to the address of the client on the other end of the connection
                       &clilen);
    if (newsockfd < 0) 
        error("ERROR on accept");
    
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
    
    close(newsockfd);
    close(sockfd);
    return 0; 
}
