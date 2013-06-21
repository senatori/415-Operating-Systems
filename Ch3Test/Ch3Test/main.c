//
//  main.c
//  Ch3Test
//
//  Created by Stephen Senatori on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int value=5;

int main (int argc, const char * argv[])
{
    //pid_t pid;
    int pid;
    
    pid= fork();
    
    if(pid == 0){ /* child process */
        value += 15;
        return 0;
    }
    else if(pid > 0) {/* parent process */
        wait(NULL);
        printf("Parent: value = %d", value);
        return 0;
    }
    
}

