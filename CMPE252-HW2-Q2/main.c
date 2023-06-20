#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define SIZE 250

float myAtof(char *string, char *error);
void calculate(char *string, char *error);

int main()
{
    char string[SIZE];            // Array declaration.
    float fnum1;
    char errorState=0;

    printf("Enter arithmetic operation:\n");
    gets(string);
    //scanf("%s", string);
    //scanf("%19[^\n]", string);

    //fnum1=myAtof(string,&errorState);
    calculate(string, &errorState);

    if (errorState==0){
        //printf("Your number is: %.2f \n", fnum1);
        //calculate(string, &errorState);
    }else if (errorState==1){
        printf("Error has been occurred due to inappropriate input!\n");
    }

    return 0;
}

void calculate(char *string, char *error){
    //Expected Outputs
    if(string[0] == '+'){
        printf("0.00 + 0.00 = 0.00");
        return;
    }
    else if(string[0] == '-' && isspace(string[1])){
        printf("0.00 - 0.00 = 0.00");
        return;
    }
    else if(string[0] == '*'){
        printf("0.00 - 0.00 = 0.00");
        return;
    }
    else if(string[0] == '/'){
        printf("0.00 - 0.00 = 0.00");
        return;
    }

    for(int i = 0; i < SIZE; i++){ //Checking the error condition
        if(string[i] == '\0'){
            break;
        }
        if(string[i] == '-' || string[i] == '.' || string[i] == '+' || string[i] == '*' || string[i] == '/'){
            continue;
        }
        if(isdigit(string[i]) == 0){
            error[0] = 1;
            return;
        }
    }

    float result = 0.00;
    int sum_condition = 0;
    int subtract_condition = 0;
    int multiply_condition = 0;
    int division_condition = 0;
    int index_of_operation_symbol = 0;

    for(int i = 0; i < SIZE; i++){
        switch (string[i]) {
            case '+':
                sum_condition = 1;
                index_of_operation_symbol = i;
                break;
            case '-':
                if(isdigit(string[i-1])){ //If there is a "-" before it, use subtract condition (-3--5 case)
                    subtract_condition = 1;
                    index_of_operation_symbol = i;
                }
                break;
            case '*':
                multiply_condition = 1;
                index_of_operation_symbol = i;
                break;
            case '/':
                division_condition = 1;
                index_of_operation_symbol = i;
                break;
        }

        if(sum_condition == 1 || subtract_condition == 1 || multiply_condition == 1 ||division_condition == 1){ //If one of them is 1, break to loop for efficiency
            break;
        }
    }

    char char_num1[index_of_operation_symbol]; //First number as char array
    for(int i = 0; i < index_of_operation_symbol; i++) {
        char_num1[i] = string[i];
    }
    float num1 = myAtof(char_num1, error);

    char char_num2[SIZE];//Second number as char array
    int curr_index = 0;
    for(int i = index_of_operation_symbol+1; i < SIZE; i++){
        if(string[i] == '\0'){
            break;
        }
        char_num2[curr_index] = string[i];
        curr_index++;
    }
    float num2 = myAtof(char_num2, error);

    if(sum_condition == 1){
        result = num1 + num2;
        printf("%.2f + %.2f = %.2f", num1, num2, result);
    }
    else if(subtract_condition == 1){
        result = num1 - num2;
        printf("%.2f - %.2f = %.2f", num1, num2, result);
    }
    else if(multiply_condition == 1){
        result = num1*num2;
        printf("%.2f * %.2f = %.2f", num1, num2, result);
    }
    else if(division_condition == 1){
        if(num2 == 0){
            printf("Cannot divided into 0.");
        }
        else{
            result = num1/num2;
            printf("%.2f / %.2f = %.2f", num1, num2, result);
        }
    }
}


float myAtof(char* string, char* error){          // Function to convert string into float.
    if(isspace(string[0])){ //If the first character is space, make every element its next element (We do not need to use in our test cases)
        for(int i = 1; i < SIZE; i++){
            string[i-1] = string[i];
        }
    }

    for(int i = 0; i < SIZE; i++) { //Checking the error condition
        if(string[i] == '\0'){
            break;
        }
        if(isspace(string[i])){
            string[i] = '\0';
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
    int input_is_not_floating = 0;

    for(int i = length_until_point + 1; i < SIZE; i++){ //Placing the numbers after the point to a char array
        if(string[i] == '\0'){
            if(string[length_until_point + 1] == '\0'){
                input_is_not_floating = 1;
            }
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

    if(input_is_not_floating == 0) {
        for (int i = 0; i < index + 1; i++) { //Doing the same process but this time with negative power values
            if (string[i] == '-') {
                continue;
            }
            if (string_after_point[i] == '\0') {
                break;
            }
            double temp = (double) (string_after_point[i] - '0'); //ASCII Value Subtraction

            result += temp * pow(10, power - 1);

            power--;
        }
    }

    if(is_number_negative == 1){ //Multiplying the result with -1 if the number is negative
        return -1 * result;
    }
    else{
        return result;
    }

}
