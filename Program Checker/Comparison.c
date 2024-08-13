/*##################################
EX1 part 1
NAME: Shoham Galili
ID: 208010785
DESCRIPTION: The code compare two files. If Equal--> Return 2. If not Equal --> Return 1
##################################*/
#include <stdio.h>
#include <string.h>
#include<fcntl.h> 
#include<stdlib.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char * argv[]){
//Initialize Variables:
int fd1, fd2;
int x1, x2;
char ch1, ch2;

//Get File Descriptors:
fd1= open(argv[1],O_RDONLY); // Get the file descriptor of the first argument with open sycall
fd2= open(argv[2],O_RDONLY); // Get the file descriptor of the second argument with open sycall

while (1){ // While we dont get to the end of the files
    x1= read(fd1, &ch1, 1); //Read 1 char from the first file to ch1
    x2= read(fd2, &ch2, 1);  // Read 1 char from the second file to ch2

        if ( x1 < 0){             //If read syscall get failed --> return Error
            write(2,"Error", 5);
        }
        if( x2< 0){               //If read syscall get failed --> return Error
            write(2,"Error", 5);
        }
        if( x1==0 && x2==0 ){    //If this is the end of both files --> return 2 (Equal Files)
            exit(2);
        }
        if( ch1 != ch2 ){       // If the chars are not equal --> return 1 (Not Equal Files)
            exit(1);
        }
    }
    // Close the file after use them
    close(fd1);
    close(fd2);
}