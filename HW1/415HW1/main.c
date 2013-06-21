#include <stdio.h>
#include <sys/types.h> //read
#include <sys/stat.h>
#include <fcntl.h>   //open
#include <unistd.h>  //read/write
#include <stdlib.h>

#define BUFSIZE 11


main() {
	char	rw_buff[BUFSIZE]/*= "\0"*/;
	int	readFile_id;
    int writeFile_id;
	int	retval;
	int	numread;
    int counter=1;
    
	printf("Welcome to the TEE Copy Program by Steven Senatori\n");
    printf("Enter the name of the file to copy from: \0");
	scanf("%s",&rw_buff[0]);
	printf("Filename is:  %s\n",&rw_buff[0]);
        
	if ((readFile_id = open(rw_buff,O_RDONLY)) < 0) {  //open returns the filedescriptorID
		perror("Read file failed to open");
		exit(-1);
	}
    
    printf("Enter the name of the file to copy to: ");
    scanf("%s", &rw_buff);
    printf("Filename is: %s\n", &rw_buff[0]);
    
    
    if ((writeFile_id = open(rw_buff, O_WRONLY)) < 0) { //open returns the filedescriptorID
        perror("Write file failed to open");
		exit(-1);
    }
    
	do {
        memset(rw_buff, '\0', BUFSIZE); //fills every character in the array with the end line
		/*------Reading From File-------*/
        if ((numread = read (readFile_id,rw_buff,BUFSIZE)) < 0) { //read populates the buffer & returns # read 
			perror("Bad file read"); 
			exit(-1);
		}
        //printf("\n-----------\n"); //this was
        //fflush(stdout);
        
        /*-----------Writing to screen-----------*/
		if ((retval = write (1, rw_buff, /*BUFSIZE*/numread)) < 0) { //write returns a status value
			perror("Bad stdout");//trippy
			exit(-1);
		}
        /*-----------Writing to File-----------*/
        if ((retval= write(writeFile_id, rw_buff, numread)) < 0) { 
            perror("Bad file write");
            exit(-1);
        }
        counter+= numread;
        
	} while (numread > 0);
    
	printf("\nFile Copy Successful, %i bytes copied\n", counter);
    
    
};
