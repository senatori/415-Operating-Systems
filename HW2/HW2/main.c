//
//  main.c
//  HW2
//
//  Created by Stephen Senatori on 2/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h> //read
#include <sys/uio.h>  //read
#include <sys/stat.h>
#include <fcntl.h>   //open
#include <unistd.h>  //read/write/fork
#include <stdlib.h>
#include <string.h> //strtok 

#define BUFSIZE 25


int main (int argc, const char * argv[])
{
      
    
    char usr_input[BUFSIZE];
    char delim[]= " \n";
    char *token= NULL;
    char *array[BUFSIZE];
    int counter, num_read, status;
    int backgroundFlag= 0;
    int TokenIsEmpty=0;  //if empty, it is set to 1, Set to zero if it is not... 
    
    
    
    pid_t pid;
    pid_t currentprocess;
    int fd[2];
    
    currentprocess= getpid();
    
    
    
    while (currentprocess != 0) {
        
        pid= currentprocess;
        
        
        
        // insert code here...
        memset(usr_input, '\0', BUFSIZE); //fills every character in the array with the end lin
        write(1, "MyShell>", 8);
        num_read = read(0 , usr_input, BUFSIZE);
        
        token= usr_input;
        
        if (token[num_read - 2] == '&') { //if the last char before '\0' is an '&'
            token[num_read - 2] = '\0' /*NULL*/;   //replace with
            backgroundFlag= 1;
        }
        
        
        
        
        counter=0;
        token = strtok(usr_input, delim); 
        array[counter]=token;
        
        if (token == NULL)  //checks if the user hit Enter without calling a program & sets flag
            TokenIsEmpty= 1;
        
        while (token != NULL) {
            counter++;
            token = strtok(NULL, delim); //NULL so we don't Re-Tokenize user_input
            array[counter]= token;
            
        }
        if (!TokenIsEmpty) //only create a new child process is the user input more then just a 
            pid= fork();   //cariage return.
        
        if (pid <0) {
            perror("Fork failed");
            exit(-1);
        }
        else if (pid == 0) { //if in child process
            
            
            execvp(array[0], array);             
        }
        else if ((!backgroundFlag) && (!TokenIsEmpty)) { //if not supposed to run in background
            
            waitpid(pid,0,0);
            printf("Child Completed in foreground\n");
            //TokenIsEmpty=0; //reset the TokenIsEmpty status
        }
        else if(!TokenIsEmpty){  //if child process was supposed to run in background
            backgroundFlag=0;// reset the backgroundflag
            
            printf("Child Process %i is in background \n", pid);
            //printf(")
        }
        TokenIsEmpty=0; //reset the TokenIsEmpty
        
    }
    
    //in windows, si.hStdOutput
    
    
    
    return 0;
}

