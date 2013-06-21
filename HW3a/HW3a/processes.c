//
//  processes.c
//  HW3
//
//  Created by Stephen Senatori on 3/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

/*

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>



void sigprocessFunction(int loopcount);

pid_t processes[10];

main() {
    
//    char	mybuf[250];
//    pid_t pid, childPID;
//    pid_t processes[10];

/*
    int loopcount=0;
    int i;
    
    processes[loopcount]= getpid();
    
    while (processes[loopcount] !=0) 
    {
        
        processes[loopcount]=fork();//<-------BEEF
        
        if (processes[loopcount] <0) {
            perror("Fork failed");
            exit(-1);
        }
        if(processes[loopcount]> 0) //I just want parent to have access to this part of loop
        { 
            loopcount++;
            if(loopcount==10)
                break;
            
            
        }
    }
    
    if (processes[loopcount]==0)  //if in child processess
    {
        
        if (loopcount<0) //stall all but the first child process
        {        
            signal(SIGHUP, sigprocessFunction); 
            
        }
        else
        {
            sigprocessFunction(loopcount);
        }
    }
    
    if(processes[0] > 0)
    {
        wait(NULL);
        
    }
    
    return 0;
}

void sigprocessFunction(int loopcount){
    
   pid_t childPID= getpid();
    int num=1;
    while(num<11)
    {
        fprintf(stderr,"PID %d: %d \n", childPID, num);
        num++;
        sleep(1);
        
    }
    
    if (loopcount < 9) //using nine so we don't send signal on last process
        kill(processes[loopcount+1], SIGHUP); //send signal to next process
    
    exit(0);
    
}
*/
