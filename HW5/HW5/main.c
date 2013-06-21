//
//  main.c
//  HW5
//
//  Created by Stephen Senatori on 4/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
/*
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int ADDRESS_SIZE=63; //includes zero
//int N= 15;
//int M= 63-15;
int N;
int M;

unsigned long long int getPage_num(unsigned long long int);
unsigned long long int getOffset(unsigned long long int);
int dec_to_oct(int);

//takes an int representing pagesize in kilobytes
void switchPageSizeTo(int page_sizeKB) { 
    int page_size_in_bytes;
    page_size_in_bytes = page_sizeKB * 1024;
    N = roundl(log2(page_size_in_bytes));

    M = ADDRESS_SIZE - N;
}

int main (int argc, const char * argv[])
{
    
    //Finished homework is better then perfect homework...
    
    int octal_address, octal_page_num, octal_offset;
    unsigned long long int address, page_num, offset;
    
    address= atoll(argv[1]);
    octal_address= dec_to_oct(address);
    
    
    switchPageSizeTo(32);

    
    page_num= getPage_num(address);
    offset= getOffset(address);
    
    octal_page_num= dec_to_oct(page_num);
    octal_offset= dec_to_oct(offset);
        
    
    printf("Address in Decimal: %lld Octal %d \n", address, octal_address);
    printf("Page # in Decimal: %lld Octal: %d \n", page_num, octal_page_num);
    printf("Offset in Decimal %lld Octal: %d \n\n\n", offset, octal_offset); 
    
    switchPageSizeTo(16);
    
    page_num= getPage_num(address);
    offset= getOffset(address);
    
    octal_page_num= dec_to_oct(page_num);
    octal_offset= dec_to_oct(offset);
    
    
    printf("Address in Decimal: %lld Octal %d \n", address, octal_address);
    printf("Page # in Decimal: %lld Octal: %d \n", page_num, octal_page_num);
    printf("Offset in Decimal %lld Octal: %d \n", offset, octal_offset);
    
    return 0;
}

unsigned long long int getPage_num(unsigned long long int address)
{
    //since Page num is represented by the 64-N bits, we want all but the N bits, so we shift N out
    unsigned long long int page_num;
    page_num= address >> N;
    
    return page_num;
}


unsigned long long int getOffset(unsigned long long address)
{
    unsigned long long int offset;
    //since we just want the N bits to be kept, we first shift M bits off so that we have the important offset bits
    offset= address << M;
    
    //we then shift the N bits back into their rightful place
    offset= offset >> M;
    
    return offset;
}

int dec_to_oct(int decimal) {
    

    int factor=1;
    int octal_digit=0;
    int octal=0;
    
    
    // converts decimal to octal
    while (decimal > 0) {
        octal_digit = decimal % 8;
        octal += (factor * octal_digit);  //multiply by a factor of ten each iteration so I don't have to deal with arrays
        factor = factor * 10;  
        
        decimal /= 8;
    }
    
    return octal; 
}


*/


