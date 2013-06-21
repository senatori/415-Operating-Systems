//
//  main.c
//  PRELIM
//
//  Created by Stephen Senatori on 4/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>



int N, P, C, X, Dequeue, Ptime, Ctime;

int bbq_counter = 0; //keeps a tally of the values to be consumned

pthread_mutex_t mylock;

void check(int expression, char *message) {
    if (!expression) {
        perror(message);
        exit(-1);
    }
}

void producer() {
    fprintf(stderr, "**Producer started**\n");
    do {
        pthread_mutex_lock(&mylock);
        
        bbq_counter += X;
        fprintf(stderr, "[PRODUCER] Buffer count increased \t Count: %d\n", bbq_counter);
        
        pthread_mutex_unlock(&mylock);
        sleep(Ptime);
        
    } while (bbq_counter < N);
}

void consumer() {
    fprintf(stderr, "**Consumer started**\n");
    do {
        pthread_mutex_lock(&mylock);
        
        bbq_counter -= Dequeue;
        fprintf(stderr, "[CONSUMER] Buffer count decreased \t Count: %d\n", bbq_counter);
        
        pthread_mutex_unlock(&mylock);
        sleep(Ctime);
        
    } while (bbq_counter > 0);
}


int main(int argc, char *argv[]) {
    
    time_t start_time, end_time;
    struct tm *ptr;
    int i, retvalue;
    
    pthread_mutex_init(&mylock, NULL);
    
    
    
    if (argc< 7) 
    {
        perror("Requires following arguments: N, P, C, X, Ptime, Ctime \n");
        exit(-1);
    }    
    
    N  = atoi(argv[1]);
    P = atoi(argv[2]);
    C = atoi(argv[3]);
    X = atoi(argv[4]);   //this is the rate/quantity that the PRODUCER will add to the counter
    Ptime = atoi(argv[5]);
    Ctime = atoi(argv[6]);
    Dequeue = P * X / C; //this is the rate/quantity that the CONSUMER will decrement from the counter

    pthread_t producer_TID[P], consumer_TID[C];
        
    
    start_time = time(NULL);
    ptr=localtime(&start_time);
    printf("Start: ");
    printf(asctime(ptr));
    
    printf("\n\n\n");
    
    
    for (i = 0; i < P; i++)
    {
        pthread_create(&producer_TID[i], NULL, (void *) producer, NULL);
    }
    
    for (i = 0; i < C; i++)
        pthread_create(&consumer_TID[i], NULL, (void *) consumer, NULL);
    
    
    for (i = 0; i < P; i++) {
        pthread_join(producer_TID[i], NULL);
    }
    
    for (i = 0; i < C; i++) {
        pthread_join(consumer_TID[i], NULL);
    }
    
    end_time = time(NULL);
    printf("====================\n");
    printf("End time: %s", ctime(&end_time));
    printf("Duration: %ld seconds\n", end_time - start_time);
    
    pthread_mutex_destroy(&mylock);
    return 0;
}
*/