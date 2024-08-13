#include <stdio.h>

void main(int argc, char * argv[])
{

    int num1, num2,result;
    num1= atoi(argv[1]);
    num2= atoi(argv[2]);

    result= num1 + num2;

    printf("The Sum is %d\n", result);

}