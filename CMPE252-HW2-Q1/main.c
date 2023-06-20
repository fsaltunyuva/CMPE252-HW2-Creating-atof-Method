#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define SIZE 250

float myAtof(char *string, char *error);

int main()
{
    char string[SIZE];            // Array declaration.
    float fnum1;
    char errorState=0;

    printf("Enter a number:\n");
    //gets(string);
    scanf("%s", string);

    fnum1=myAtof(string,&errorState);

    if (errorState==0){
        printf("Your number is: %.2f \n", fnum1);
    }else if (errorState==1){
        printf("Error has been occurred due to inappropriate input!\n");
    }

    return 0;
}

float myAtof(char* string, char* error){          // Function to convert string into float.
    for(int i = 0; i < SIZE; i++) { //Checking the error condition
        if(string[i] == '\0'){
            break;
        }
        if(string[i] == '-' || string[i] == '.'){
            continue;
        }
        if(isdigit(string[i]) == 0){
            error[0] = 1;
            return 0;
        }
    }

    float result = 0;
    int length_until_point = 0;

    int is_number_negative = 0;

    if(string[0] == '-'){
        is_number_negative = 1;
    }

    for(int i = 0; i < SIZE; i++){ //Calculating the position of the "point"
        if(string[i] == '.' ||string[i] == '\0'){
            break;
        }
        else if(string[i] == '-'){
            continue;
        }
        else{
            length_until_point++;
        }
    }
    int power = length_until_point; //Powers of 10

    if(is_number_negative == 1){ //If number is negative, go 1 more character to reach the point (.)
        for(int i = 0; i < length_until_point+1; i++){
            if(string[i] == '-'){
                continue;
            }
            double temp = (double)(string[i] - '0'); //ASCII Value Subtraction

            result += temp * pow(10, power - 1);
            power--;
        }
        //Power exits as 0 always
    }
    else{
        for(int i = 0; i < length_until_point; i++){
            if(string[i] == '-'){
                continue;
            }
            double temp = (double)(string[i] - '0'); //ASCII Value Subtraction

            result += temp * pow(10, power - 1);
            power--;
        }
        //Power exits as 0 always
    }

    char string_after_point[SIZE];
    int index = 0;

    for(int i = length_until_point + 1; i < SIZE; i++){ //Placing the numbers after the point to a char array
        if(string[i] == '\0'){
            break;
        }
        else if(string[i] == '-'){
            continue;
        }
        else{
            string_after_point[index] = string[i];
            index++;
        }
    }

    for(int i = 0; i < index + 1; i++){ //Doing the same process but this time with negative power values
        if(string[i] == '-'){
            continue;
        }
        if(string_after_point[i] == '\0') {
            break;
        }
        double temp = (double)(string_after_point[i] - '0'); //ASCII Value Subtraction

        result += temp * pow(10, power - 1);

        power--;
    }

    if(is_number_negative == 1){ //Multiplying the result with -1 if the number is negative
        return -1 * result;
    }
    else{
        return result;
    }

}
