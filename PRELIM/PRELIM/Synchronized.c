//
//  Synchronized.c
//  PRELIM
//
//  Created by Stephen Senatori on 4/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//
//  main.c
//  PRELIM
//
//  Created by Stephen Senatori on 4/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>


struct bbq_node //definition of my bounded buffer queue
{
    struct bbq_node *next;

    int value;
    
};

//void 
struct bbq_node *head=NULL;
struct bbq_node *tail=NULL;
struct bbq_node *p_ptr=NULL; //points to where the producer is inserting values in que
struct bbq_node *c_ptr=NULL;

unsigned int N, P, C, X, Dequeue, Ptime, con_time;

sem_t emptyCount;
sem_t fullCount;



int bbq_counter = 0; //keeps a tally of the values to be consumned
int buffer_count=0;


pthread_mutex_t sharedLock; //lock that will be shared between producer & consumer

void init_bbq(unsigned int N)
{
    int i;
    //lnode = (struct dllist *)malloc(sizeof(struct dllist));
    struct bbq_node *tmp;
    struct bbq_node *node= (struct bbq_node *)malloc(sizeof(struct bbq_node));
    //if(head==NULL){
        head= node;
        tmp=head;
        
        head->next= NULL;
        //head->value= bbq_counter;
        
    //}
    //building the rest of the linked list
    
    for (i=1 ; i< N; i++) //already initialized the first node(head), so we'll start iterating from 1
    {
        node= (struct bbq_node *)malloc(sizeof(struct bbq_node));
        
        tmp->next= node;
        tmp= node;
        
    }
    
    tmp->next= head; //our list is circular now.
}


void producer(int start, int end) {
    int i, semValue;
    
    for (i=0; i< X; i++)
    {
        sem_wait(&emptyCount); //wait(empty) aka P(empty)
        pthread_mutex_lock(&sharedLock);  //wait(mutex) aka P(mutex)
        
        bbq_counter++;
        p_ptr->value= bbq_counter; //store a unique value in the node
        p_ptr= p_ptr->next; //move pointer to next item in queue
        
//        sem_getvalue(&emptyCount, &semValue);
//        semValue= N - semValue;
        buffer_count++;
        semValue= buffer_count;
        
        fprintf(stderr, "[PRODUCER] Buffer count increased to %d Value: %d\n", semValue, bbq_counter);
        
        
        pthread_mutex_unlock(&sharedLock); //signal(mutex) aka V(mutex)
        sem_post(&fullCount);              //signal(full) aka V(full)
        sleep(Ptime);
      }  
    
}

void consumer() 
{
    int i, qValue, semValue;
    for (i=0; i < Dequeue; i++) 
    {
        sem_wait(&fullCount); //wait(full) aka P(full)
        pthread_mutex_lock(&sharedLock); //wait(mutex) aka P(mutex)
        
        qValue= c_ptr->value;
        c_ptr= c_ptr->next; //move pointer to next item in queue
        
        //sem_getvalue(&fullCount, &semValue);
        buffer_count--;
        semValue= buffer_count;
        
        fprintf(stderr, "[CONSUMER] Buffer count decreased to %d Value: %d\n", semValue, qValue);
        
        pthread_mutex_unlock(&sharedLock); //signal(mutex)
        sem_post(&emptyCount);             //signal(empty)
        sleep(con_time);
        
    }
    
}


int main(int argc, char *argv[]) {
    
    time_t start_time, end_time;
    struct tm *ptr; //for displaying time
    int i, retvalue;
    int debuga=0;
    
    pthread_mutex_init(&sharedLock, NULL);
    
    
    
    
    if (argc< 7) 
    {
        perror("Requires following arguments: N, P, C, X, Ptime, Ctime \n");
        exit(-1);
    }    
    
    N  = atoi(argv[1]);
    P = atoi(argv[2]);
    C = atoi(argv[3]);
    X = atoi(argv[4]);   //this is the rate/quantity of nodes that each PRODUCER thread will  will add to the counter
    Ptime = atoi(argv[5]);
    con_time = atoi(argv[6]);
    Dequeue = P * X / C; //this is the rate/quantity of nodes that each CONSUMER thread will dequeue from the BBQ
    
    //INITIALIZING QUEUE and P & C trackers
    init_bbq(N);
    p_ptr= head;
    c_ptr= head;
    
    
    sem_init(&emptyCount, 0, N); //keeps track of how many empty slots we have in buffer
    sem_init(&fullCount, 0, 0);  //keeps track of how many full slots we have in buffer
    
    sem_getvalue(&emptyCount, &debuga);
    fprintf(stderr,"counter %d", debuga);
    
    pthread_t producer_TID[P], consumer_TID[C];
    
    
    start_time = time(NULL);
    ptr=localtime(&start_time);
    printf("Start: ");
    printf(asctime(ptr));
    
    
    printf("\n\n\n");
    
    //spin off P amount of producer threads
    for (i = 0; i < P; i++)
    {
        pthread_create(&producer_TID[i], NULL, (void *) producer, NULL);
    }
    //spin off C amount of consumer threads
    for (i = 0; i < C; i++)
        pthread_create(&consumer_TID[i], NULL, (void *) consumer, NULL);
    
    //wait for producer threads to finish
    for (i = 0; i < P; i++) {
        pthread_join(producer_TID[i], NULL);
    }
    //wait for consumer threads to finish
    for (i = 0; i < C; i++) {
        pthread_join(consumer_TID[i], NULL);
    }
    
    end_time = time(NULL);
    printf("====================\n");
    printf("End time: %s", ctime(&end_time));
    printf("Duration: %ld seconds\n", end_time - start_time);
    
    //pthread_mutex_destroy(&mylock);
    pthread_mutex_destroy(&sharedLock);
    sem_destroy(&emptyCount);
    sem_destroy(&fullCount);
    
    return 0;
}