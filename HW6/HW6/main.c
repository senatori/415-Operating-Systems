//
//  main.c
//  HW6
//
//  Created by Stephen Senatori on 4/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <pthread.h>


void printArray_All(int size);
void search(void *TID);
void fill_array();

long size;
long *array;

long partition_size;

long search_key;
signed long *search_results;

//struct thread_args {  //can only pass one argument via pthread_create, so I package a bunch in a struct.
//    int TID;
//    int ;
//};

int main (int argc, const char * argv[])
{

    // insert code here...
    int P, N, number_of_partitions;
    
    int i;
    //int *TIDptr;
    
    time_t start_time, end_time;
    
    pthread_t *scout_TID;  //will be an array of thread handles
    pthread_attr_t attr; //set of thread attributes, BOILERPLATE code
    
    
    P= atoi(argv[1]);
    N= atoi(argv[2]);
    
    search_key= 63;
    
    
    size= pow(2, P); //2**P
    number_of_partitions= pow(2, N); //  <------------------------------- 2**N
    
    array= (long *) malloc(size * sizeof(long));
    
    scout_TID= (pthread_t *) malloc(number_of_partitions * sizeof(pthread_t)); //dynamically alocating elements in array of thread handles
    search_results = (signed long *) malloc(number_of_partitions * sizeof(long));
    
    partition_size= size / number_of_partitions;  //<-------------------------
    
    
    fill_array();
    
    pthread_attr_init(&attr); //gets default attributes BOILER PLATE Code
    
    start_time = clock() / (CLOCKS_PER_SEC / 1000);
        
    //create threads
    for (i = 0; i < number_of_partitions; i++)
    {
        pthread_create(&scout_TID[i], &attr, (void*) search, (void*) i); //i is threadID
    }
    
    //join threads
    for (i = 0; i < number_of_partitions; i++)
    {
        pthread_join(scout_TID[i], NULL);
    }
    
    end_time = clock() / (CLOCKS_PER_SEC / 1000);
    printf("====================\n");
//    printf("Start Time: %s", ctime(&start_time));
//    printf("End time: %s", ctime(&end_time));
    printf("Duration: %ld miliseconds\n", end_time - start_time);
    
    printf("====================\n");




    
   
    
        
    //###############################################
    //printf("Hello, World! %lu \n", x );
    
    printArray_All(number_of_partitions);
    //###############################################
    
    return 0;
}

void fill_array()
{
    long  i;
    long temp;
    long *dup;
    
//    long long raz;
//    raz= RAND_MAX;
    
    dup= (long*) malloc(size * sizeof(long)); //this array is to make sure that there are no duplicates in main array
    
    //fill dup array with zeros
    for (i=0; i< size; i++) 
    {
        dup[i]=0;
    }
    
    srand((unsigned)time(NULL));
    
    for (i=0; i< size; i++) {
        temp= rand() % size;  
        
        if (dup[temp]==0) //if & only if value hasn't been used before
        {
            array[i]= temp;
            dup[temp]=1;
        }
        else
        {
            while(dup[temp]==1)
            {
                temp= rand() % size;
            }
            
            array[i]= temp;
            dup[temp]=1;
            
        }
    }
    
    
    
    free(dup);  //since my array is initialized to hold RAND_MAX number of elements...this is REALLY necessary :(
    
   
    
}

void printArray_All(int size)
{
    long i; 
    
    for (i=0; i < size; i++)
    {
        if (search_results[i] > -1)
        {
            printf("The value %ld found at index %ld \n", search_key, search_results[i]);  //CAUTION %l %lu
            break;
        }
    }
    
}

//each thread will be running an instance of this funciton
void search(void *TID) {
    
    int iTID;
    iTID= (int) TID;
    
    long start, end;
    
    start= iTID * partition_size;
    end=  (1 + iTID) * partition_size;
    
    search_results[iTID]= -1; //setting it to NOT found by default
    
    for (; start < end; start++) {
        if (array[start]== search_key) {
            
            search_results[iTID]= start;
        }
    }
    
    printf("THREAD No. %d \n", iTID);
    
    
    
}














