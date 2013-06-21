//
//  VirtualMemorySched.c
//  HW5
//
//  
//

#include <stdio.h>

#include <stdlib.h>

#define STRING_REF_SIZE 100
#define MAX_PAGE_FRAMES 13

int reference_string[STRING_REF_SIZE];
int number_of_frames=0;
int *page_frames;



void init_Ref_String() 
{
    int i, value;
    
    for (i = 0; i < STRING_REF_SIZE; i++) 
    {
        value = (random() % 13) + 1;
        
        while (i > 0 && value == reference_string[i-1])
            value = (random() % 13) + 1;
        
        reference_string[i] = value;
    }
}

void resetFrames() 
{
    int i;
    for (i = 0; i < number_of_frames; i++)
        page_frames[i] = -1;
}

//checks if page_number is already in the pageframes. Returns location of pageFrame if found, zero if false
int pageFrame_contains(int page_number) 
{
    int frame;
    for (frame = 0; frame < number_of_frames; frame++) 
    {
        // Return frame number for LRU reference counting purposes
        if (page_frames[frame] == page_number)
            return frame+1;
    }
    
    
    return 0;
}

//This function call will be used by OPTMIN to determine which page wont be showing up in the string for a while
int get_furthest_reference(int starting_index, int page_number)
{
    int i;
    for (i = starting_index; i < STRING_REF_SIZE; i++) {
        if (reference_string[i] == page_number)
            return i;
    }
    
    return STRING_REF_SIZE;
}




int FIFO() 
{
    int frame, reference_index, page_number, pageFaults;
    int page_stored = 0;
    
    frame = 0;
    pageFaults = 0;
    reference_index = 0;
    while (reference_index < STRING_REF_SIZE) {
        
        page_stored = 0;
        while (!page_stored && reference_index < STRING_REF_SIZE) {
            page_number = reference_string[reference_index];
            
            if (!pageFrame_contains(page_number)) {
                page_frames[frame] = page_number;
                pageFaults = pageFaults + 1;
                page_stored = 1;
            }
            
            reference_index += 1;
        }
        
        if (frame+1 < number_of_frames)
            frame += 1;
        else
            frame = 0;
    }
    
    return pageFaults;
}


int OPTMIN()
{
    int frame, reference_index, page_number, pageFaults;
    int furthest_indexed_frame, index, furthest_index;
    int empty_frames = number_of_frames;
    int page_stored = 0;
    
    pageFaults = 0;
    reference_index = 0;
    while (reference_index < STRING_REF_SIZE) {
        
        page_stored = 0;
        while (!page_stored && reference_index < STRING_REF_SIZE) 
        {
            page_number = reference_string[reference_index];
            
            if (empty_frames > 0) {
                frame = number_of_frames - empty_frames;
                
                page_frames[frame] = page_number;
                
                pageFaults += 1;
                empty_frames -= 1;
            }
            
            else {
                frame = pageFrame_contains(page_number);
                
                if (!frame)
                {
                    page_frames[furthest_indexed_frame] = page_number;
                    pageFaults += 1;
                    page_stored = 1;
                }
            }
            
            reference_index += 1;
            
            furthest_index = -1;
            for (frame = 0; frame < (number_of_frames - empty_frames); frame++) 
            {
                
                //to determine which indices will not be used for the longest period of time
                index = get_furthest_reference(reference_index, page_frames[frame]);
                
                if (index > furthest_index) 
                {
                    furthest_index = index;
                    furthest_indexed_frame = frame;
                }
            }
            
        }
    }
    
    return pageFaults;
}



int main() 
{
    
    init_Ref_String();
    
    
    page_frames = malloc(sizeof(int));
    
    for (number_of_frames = 1; number_of_frames <= MAX_PAGE_FRAMES; number_of_frames++) 
    {
        page_frames = realloc(page_frames, number_of_frames * sizeof(int));
        resetFrames();
        
        printf("#Of Page Frames %d \n", number_of_frames);
        printf("FIFO: %d page faults \n", FIFO());
        printf("OPTMIN:  %d page faults \n\n", OPTMIN());
    }
    
        
    return 0;
}