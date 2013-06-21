/* to compile:  gcc -o pthread_demo pthread_demo.c -l pthread
 *
 */ 


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define THREADS 10

char	mybuf[25];

int thread_count=0;
int global_counter=0;

pthread_mutex_t lock;


void ten_count(void *arg);

main() {
	int	retvalue, i;
	pthread_t tid_val[THREADS];
	void	*arg;
    
    pthread_mutex_init(&lock, NULL);  
    
	fprintf(stderr,"0Main Program executing\n");
    
    for (i=0; i<10 ; i++) //creating 10 threads each executing the void ten_count() function call
    {       
        //passing an element of an array of type pthread_t by reference to store the ID for joining them later
        retvalue=pthread_create(&tid_val[i],NULL, (void *)ten_count, i+1); //A thread is born!!!
        if(retvalue < 0)
        {        
            perror("Can't create first thread");
            exit(-1);
        }
        
	}
    
    
	for (i=0; i<10; i++) 
    {
        //housekeeping
        //fprintf(stderr,"0Waiting for thread %d to exit\n", i+1);
        pthread_join(tid_val[i],NULL);//<---------------------
        fprintf(stderr, "0Thread # %d exited\n", i+1);
        
    }
    
    fprintf(stderr,"LocalCount: %d\n", global_counter);
    
    pthread_mutex_destroy(&lock); 
    
    return 0;
}


void ten_count(void *arg){
    
    pthread_mutex_lock(&lock); //locks in the critical section for the current thread
    
    pthread_t tid= pthread_self();
    int birth_order= arg;
    thread_count++;
    int self_thread= thread_count;
    int local_counter;
    
    fprintf(stderr,"I'm Thread # %d, my TID is: %d \n", birth_order, tid);
    
    local_counter= global_counter;
    fprintf(stderr,"Thread # %d, TID #: %d LocalCount: %d\n", birth_order, tid, local_counter);
    local_counter+= 10;
    fprintf(stderr,"Thread # %d, TID #: %d FinalLocalCount: %d\n", birth_order, tid, local_counter); 
    sleep(1);
    global_counter= local_counter;    
    
    pthread_mutex_unlock(&lock);
    //pthread_mutex_lock(&lock);
    /*by commenting out the unlock, the first thread is creating a dog in the manger aka deadlock situation
     for the rest of the threads, denying them access to the critical section*/
}


