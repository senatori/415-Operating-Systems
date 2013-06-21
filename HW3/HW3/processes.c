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




main() {
    
    char	mybuf[250];
    pid_t pid, childPID;
    //pid_t processes[10];
    
    int loopcount=0;
    
    pid= getpid();
    
    while (pid !=0) 
    {
        
        pid=fork();//<-------BEEF
        
        if (pid <0) {
            perror("Fork failed");
            exit(-1);
        }
        if(pid >0) //I just want parent to have access to this part of loop
        { 
            loopcount++;
            if(loopcount==10)
                break;
            
            
        }
    }
    
    if (pid==0)  //if in child processess
    {
        childPID= getpid();
        int num=1;
        while(num<11)
        {
            fprintf(stderr,"PID %d: %d \n", childPID, num);
            num++;
            sleep(1);
            
        }
        
//        fprintf(stderr,"PID %d: 1\nPID %d: 2\nPID %d: 3\nPID %d: 4\nPID %d: 5\nPID %d: 6\nPID %d: 7\nPID %d: 8\nPID %d: 9\nPID %d: 10\n\n", 
//                childPID,childPID,childPID,childPID,childPID,childPID,childPID,childPID,childPID,childPID);
        
//        memset(mybuf, '\0', 250);
//        sprintf(&mybuf[0],"PID %d: 1\nPID %d: 2\nPID %d: 3\nPID %d: 4\nPID %d: 5\nPID %d: 6\nPID %d: 7\nPID %d: 8\nPID %d: 9\nPID %d: 10\n\n", 
//                childPID,childPID,childPID,childPID,childPID,childPID,childPID,childPID,childPID,childPID);
//        
//        int retval;    
//        if ((retval= write(0, mybuf, 132)) < 0) { 
//            perror("Bad file write");
//            exit(-1);
//        }
        
        //exit(0);
        
    }
    
    
}
*/