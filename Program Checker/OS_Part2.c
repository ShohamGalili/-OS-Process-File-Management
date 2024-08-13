/*##################################
EX1 part 2
NAME: Shoham Galili
ID: 208010785
DESCRIPTION: The code simulating and run students codes --> Compare their outputs to the expected output --> Give the grades
##################################*/
#include <sys/stat.h>          
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>   
#include <fcntl.h> 
#include <string.h>         
#include <stdlib.h>
#include <sys/wait.h>

//****************************************************************************
//READING FROM FILE FUNCTION
void Read_From_File (int fd, char* fileName, char* Buffer_Config)
{
//char* Buffer_File;
struct stat Stat_config;
int sizeOfFile;

    if ( stat(fileName,&Stat_config) == -1 )//Check if the stat return an unvalid value
    {
        write(2, "Error with stat syscall\n", sizeof("Error with stat syscall\n" -1)); //if syscall STAT has failed return error
        exit (-1);
        close(fd);
    }

    sizeOfFile= Stat_config.st_size; //if Stat has success --> Get the size of the ConfigFile

    if(sizeOfFile < 0)
        {
            write(2, "Error reading config file:\n", sizeof("Error reading config file:\n" -1)); //if file not found return error
            exit(-1);
        }

    if (read(fd, Buffer_Config, sizeOfFile ) == -1)
    {
    exit (-1);
        close(fd);
    }

}
//****************************************************************************
//The func return the length of the line
int Get_Line_Size (char* Buffer_Text, int counter)
{
    int sizeOfPrevLine= counter;  // Initialize

    while ( Buffer_Text[counter] != '\n' ){
        counter++; //While this is not the end of the row --> keep countering
    }

    return counter - sizeOfPrevLine + 1;
}
//****************************************************************************
//The func copy the value of the line from Buffer to string
void Copy_Line (char* line, char* Buffer_Text, int bytesToCopy, int offserFromBegin)
{
int i=0;
    for( i; i<bytesToCopy; i++){
        line[i] = Buffer_Text[i + offserFromBegin];  //Copy the value of the line from Buffer to line
    }

}
//****************************************************************************
//The func clear the string and set all chars to ' '.
void Clear_String(char* string)
{
    int j=0;
    int len = strlen(string);
    for( j; j<len; j++){
        string[j] = ' ';

    }

}


// ################################################# MAIN ############################################################
 int main(int argc, char * argv[])
{
    if ( argc != 2){                //Check if we got 2 files on argc
        return (-1);
    }

    //------------------------Initializations:---------------------------
    // Initialize Pointers to the strings we will use
    char* Buffer_Config;
    int fd;
    //SPLIT
    int Length_count1= 0;  // Initialize
    int Length_count2= 0;
    int Length_count3= 0;   
    int i=0;
    char* dir;
    char* in;
    char* out; 
    int input_fd=0;
    char inputs_buffer[50] = {'\0'};

    //initialize output path:
    char* full_outPath = NULL;
    int len_dir;                    //the length of dir string


    //Open config File
    fd = open( argv[1], O_RDONLY); //Return the fd of config File
    if ( fd == (-1) ){             // Check if there was an error on the FD
	    exit(-1);
    }

    //CHECK READ:
     Buffer_Config = (char*) malloc(150); //allocate space for config buffer
     Read_From_File(fd, argv[1], Buffer_Config); //Read the Config file into Buffer_Config


    //****************************** SPLIT LINES OF CONFIG FILE ***************************************
    //SPLIT LINE 1 from config file --> DIR:
    //Get the size of first line:
    while ( Buffer_Config[Length_count1] != '\n'){ //While this is not the end of the row --> keep countering
        Length_count1++;
    }

    dir = (char*) malloc(Length_count1+1); //Dynamic allocate for the path of the dir

    for( i; i<Length_count1; i++){
        dir[i] = Buffer_Config[i];  //Copy the value of the first line from Buffer to dir
    }

    //SPLIT LINE 2 from config file --> IN;
    int j=0;
    //Get the size of second line:
    while ( Buffer_Config[Length_count2+Length_count1+1] != '\n'){ //While this is not the end of the row --> keep countering
        Length_count2++;
    }
    in = (char*) malloc(Length_count2+1);           //Dynamic allocate for the path of in
    for( j; j<Length_count2+1; j++){
        in[j] = Buffer_Config[ Length_count1+j ];  //Copy the value of the second line from Buffer_Config to in
    }

    //SPLIT LINE 3 from confog file --> OUT;
    j=0;
    //Get the size of third line:
    while ( Buffer_Config[Length_count3+Length_count2+Length_count1+2] != '\n'){ //While this is not the end of the row --> keep countering
        Length_count3++;
    }
    out = (char*) malloc(Length_count3+1);           //Dynamic allocate for out
    for( j; j<Length_count3+2; j++){
        out[j] = Buffer_Config[ Length_count1 +Length_count2+j +1 ];  //Copy the value of the third line from Buffer_Config to out
    }

    //End reading from ConfigFile --> close config file. If Faile-->Print ERROR
    if( close(fd) == -1){
         printf("Cannot close the config file\n");
         exit(-1);
    }

    //********************* CREATE grade.csv FILE ****************************
    int Grades_fd;
    Grades_fd= open("grades.csv",O_RDONLY|O_WRONLY|O_CREAT, 0666); //Open a csv file to Students's grades
    if ( Grades_fd < 0){
        printf("Error with open syscall\n");
        free(out);
        free(in);
        free(dir);
        exit(-1);
    }

    //***************************** READ STUDENTS NAME TO A FILE *****************************
    //CREATE a SON PROCESS
    int pid=0;
    pid= fork();
    if ( pid < 0){ //Check if fork has an error
        printf("Error with fork syscall\n");
        free(out);
        free(in);
        free(dir);       
        exit(-1);
    }

    //~~~~~~~~~~~~~SON~~~~~~~~~~~~~
    if ( pid == 0){      

        int Students_list_fd= open("StudentsList.txt", O_WRONLY|O_CREAT, 0666); //Open new Students List File
        if ( Students_list_fd < 0){        //Check if open syscall was sucess
            printf("Error with open syscall\n");
            free(out);
            free(in);
            free(dir); 
            exit(-1);
        }
        //The defualt output(screen) is closed
        if (close(1) == -1){ //Check if close syscall was success
            printf("Error with close syscall\n");
            free(out);
            free(in);
            free(dir); 
            exit(-1);
        } 
        // Route students list file to fd 1 (screen)               
        if (dup(Students_list_fd) == -1) {
            printf("Error with dup syscall\n");
            free(out);
            free(in);
            free(dir); 
            exit(-1);
        } 
        //Close the file Student List
        if(close(Students_list_fd) == -1){
            printf("Error with close syscall\n");
            free(out);
            free(in);
            free(dir); 
            exit(-1);
        }
        //Write the students names into StudentsList file
        if(execlp( "ls", "ls", dir, NULL) == -1){ //Check if execlp syscall was success
            printf("Error with execlp syscall\n");
            free(out);
            free(in);
            free(dir); 
            exit(-1);
        } 
    }

    //~~~~~~~~~~FATHER~~~~~~~~~~~~~
    else{
        //Wait for son to finish
        if (wait(NULL) == -1){
            printf("Error with wait syscall\n");
            free(out);
            free(in);
            free(dir); 
            exit(-1);
        } 
    }

    //Read the Students Names from Students List File to Buffer
    int Students_list_fd=0;
    Students_list_fd= open("StudentsList.txt", O_RDONLY, 0666); //Open Students List File
    if ( Students_list_fd < 0){        //Check if the FD is valid.
        printf("Error with open syscall\n");
        free(out);
        free(in);
        free(dir); 
        free(Buffer_Config);
        exit(-1);
    }
    
    //Initialize an Array for Students. Assume that the max length of name is 50
    char* Buffer_StudentsList = (char*) malloc(50);

    if (read(Students_list_fd, Buffer_StudentsList, 50) == -1){  //Check if yscall of read from file was success
        printf("Error with read syscall\n");
        free(out);
        free(in);
        free(dir); 
        free(Buffer_Config);
        free(Buffer_StudentsList);        
        exit(-1);
    }

    //************************Get Inputs from input file: ******************************
    input_fd = open("Input.txt",O_RDONLY, 0666); //Get FD of Input files  
     if ( input_fd < 0){                       //Check if the FD is valid.
        printf("Error with open syscall\n");
        free(out);
        free(in);
        free(dir); 
        free(Buffer_Config);
        exit(-1);
    }

    if (read(input_fd, inputs_buffer, 40) == (-1)) //Read the input file content to an inputs_buffer
    {
        printf("Error with read syscall\n");
        free(out);
        free(in);
        free(dir); 
        free(Buffer_Config);
        exit(-1);
    }
    //Split and set the arguments from input_buffer for 2 args:
    char* arg1 = strtok(inputs_buffer, " ");
    char* arg2 = strtok(NULL, " ");
    
    //********************** Create the full Path of Students **********************************
    //Initializations:
    i=0;
    int len=0;
    int offset=0;
    char* Student_Name = (char*) malloc(15);
    char* Students_Grades = (char*) calloc(50, sizeof(char));
    full_outPath = (char*)calloc(150, sizeof(char));
    int StudentNameSize=0;

    strcpy(full_outPath,dir);                //Copy the dir to the full outPath
    len_dir = strlen(dir);                   //check what is the length of dir string
    strncat(full_outPath, "/", strlen("/") )  ;          // Add / at the end of the path

    //Sweep files as long as we havent reached the end of the file, we check students program
    while( Buffer_StudentsList[i] != '\0')
    {
        //GET THE STUDENT NAME:
        len= Get_Line_Size(Buffer_StudentsList, offset); //Get the length of line
        Copy_Line(Student_Name,Buffer_StudentsList,len - 1,offset);  //Copy the name to Student Name Buffer
        offset = offset + len;
        strncat(full_outPath, Student_Name, len-1);                  //Add the student name to the path string
        strncat(full_outPath, "/./main.exe", strlen("/./main.exe")); //Add the name of the compiled file

       //Create a New Process for each Student
        pid= fork(); // *** FIRST FORK ***

        if(pid < 0){
            printf("Error with fork syscall\n");
            free(out);
            free(in);
            free(dir); 
            free(Buffer_Config);
            free(Student_Name);
            free(Students_Grades);
            exit(-1);
        }

        else if( pid == 0){ //SON
            //Give fot each student the permission to execute:
            if( execlp("chmod", "/bin/chmod", "0777", full_outPath, NULL)<0){
                 printf("Error with execlp syscall\n");
                free(out);
                free(in);
                free(dir);
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades); 
                exit(-1); 
            }
        }
        else{ //FATHER
            if(wait(NULL) == -1){
                printf("Error with wait syscall\n");
                free(out);
                free(in);
                free(dir);
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades); 
                exit(-1); 
            }
        }
        int pid= fork(); // *** SECOND FORK ***

        if(pid < 0){
            printf("Error with fork syscall\n");
            free(out);
            free(in);
            free(dir); 
            free(Buffer_Config);
            free(Student_Name);
            free(Students_Grades);
            exit(-1);
        }

        else if ( pid == 0)   { //SON
            //Create an Output file for each student
            int output_fd = open("output.txt", O_WRONLY|O_CREAT, 0666); //Open Outpput File
            //execlp(full_outPath, full_outPath, arg1, arg2, NULL);
            if(output_fd < 0){ //Check if Open syscall has success
                printf("Error with Open syscall\n");
                free(out);
                free(in);
                free(dir);
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades); 
                exit(-1);           
            }
            //The defualt output(screen) is closed
            if (close(1) == -1){
                printf("Error with close syscall\n");
                free(out);
                free(in);
                free(dir);
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades); 
                exit(-1); 
            } 
            // Route the outputs file to fd 1 (screen)               
            if (dup(output_fd)== -1){
                printf("Error with dup syscall\n");
                free(out);
                free(in);
                free(dir);
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades); 
                exit(-1);
            }          
            if (close(output_fd) == -1){
                printf("Error with close syscall\n");
                free(out);
                free(in);
                free(dir);
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades); 
                exit(-1);
            }
            //Writing to the file the students names:
            if (execlp(full_outPath, full_outPath, arg1, arg2, NULL) == -1){
                printf("Error with execlp syscall\n");
                free(out);
                free(in);
                free(dir);
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades); 
                exit(-1);
            }
        
        }
        else //FATHER 
        {
            if (wait(NULL) == -1 )
            {
                printf("Error with wait syscall\n");
                free(out);
                free(in);
                free(dir);
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades); 
                exit(-1);
            }
        }
        
        // *************SECOND FORK***************
        //Compare the Students outputs to the Expected output - with PART1 of EX1
        pid= fork(); 

        if(pid < 0){
            printf("Error with fork syscall\n");
            free(out);
            free(in);
            free(dir); 
            free(Buffer_Config);
            free(Student_Name);
            free(Students_Grades);
            exit(-1);
        }

        else if( pid == 0){ //SON
            if ( execlp("./comp.out","./comp.out", "ExpectedOutput.txt", "output.txt", NULL) < 0)
            {
                printf("Error with execlp \n");
                free(out);
                free(in);
                free(dir); 
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades);
                exit(-1);

            }
        }

        else { //FATHER
            int son_status;
            if( wait(&son_status) == -1){
                printf("Error with execlp \n");
                free(out);
                free(in);
                free(dir); 
                free(Buffer_Config);
                free(Student_Name);
                free(Students_Grades);
                exit(-1);
            }

            //Checking the return value of the comparation between the output VS Expected Output
            if( WEXITSTATUS(son_status) == 2){ //If there was a ssuccess
                if( write(Grades_fd, Student_Name, strlen(Student_Name)) == -1){
                    printf("Error with write to file \n");
                    free(out);
                    free(in);
                    free(dir); 
                    free(Buffer_Config);
                    free(Student_Name);
                    free(Students_Grades);
                    exit(-1);  
                }

                //The student's answer was CORRECT -->GRADE 100         
                if( write(Grades_fd, ",100\n", strlen(",100\n")) == -1){
                    printf("Error with write to file \n");
                    free(out);
                    free(in);
                    free(dir); 
                    free(Buffer_Config);
                    free(Student_Name);
                    free(Students_Grades);
                    exit(-1);               
                }  
            }

            else{ // Files are not Equal
                if( write(Grades_fd, Student_Name, strlen(Student_Name)) == -1){
                    printf("Error with write to file \n");
                    free(out);
                    free(in);
                    free(dir); 
                    free(Buffer_Config);
                    free(Student_Name);
                    free(Students_Grades);
                    exit(-1);  
                }

                //The student's answer was INCORRECT -->GRADE 0         
                if( write(Grades_fd, ",0\n", strlen(",0\n")) == -1){
                    printf("Error with write to file \n");
                    free(out);
                    free(in);
                    free(dir); 
                    free(Buffer_Config);
                    free(Student_Name);
                    free(Students_Grades);
                    exit(-1);               
                } 
            }
        }

       //Make path ready for the next Student:
       Clear_String(Student_Name); //Clear the path from student name
       strcpy(full_outPath,dir); 
       strncat(full_outPath, "/", strlen("/"));
       i=offset; //inc index
       
    }
    exit(0);
    free(out);
    free(in);
    free(dir); 
    free(Buffer_Config);
    free(Student_Name);
    free(Students_Grades);
}