/* Program designed to perform a security authorisation based on numeric codes.
The user will enter a four digit code 0000 - 9999 inclusive or opt to generate a random code.
The code will be encrypted using an encryption algorithm and be compared to a fixed correct code.
The code will also be able to be decrypted using an decryption algorithm.
Designed by Jonathan Hew
Date : 21/04/2020
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
//structure templates
struct code_counter
{
    int correct_code;
    int wrong_code;
};//end struct code_counter

//function signatures
void code_entry(int*);
void code_encrypt(int*);
void code_decrypt(int*);
void code_comparison(int*, int*, int*);
void code_counter(int*, int*);

int main()
{
    int input;
    int user_code[SIZE];
    int opt1_count = 0;
    int opt3_count = 0;
    int encrypt_status = 0;
    int check_status = 0;
    
    struct code_counter result = {0, 0};
    
    //do while loop to displaymenu until option 6 ("EXIT") is clicked after a function is completed the program will return to this main menu
    do 
    {
        printf("\n\n------------------------------------------------------------------------------------------------------------------------");
        printf("\n**********MAIN MENU********** \n\n");
        printf("1. Enter your code or generate a random code. \n");
        printf("2. Encrypt code. \n");
        printf("3. Compare code with authorised access code. \n");
        printf("4. Decrypt code. \n");
        printf("5. Display the frequency of encrypted code is correct / incorrect . \n");
        printf("6. EXIT \n\n");
        printf("------------------------------------------------------------------------------------------------------------------------ \n\n");
        
        scanf("%d", &input);
        flushall();
        
        //switch statement to read the input from the user and to carry out the relevant case and to call the relevant function
        switch (input)
        {
            case 1:
            {
                //call function code_entry to promt user to input code or generate a random code.
                code_entry(user_code);
                encrypt_status = 0;
                check_status = 0;
                opt1_count = opt1_count + 1;
            }//end case
            break;
            case 2:
            {
                //check to see if numebers have been inputted yet
                if (opt1_count < 1)
                {
                    printf("\n Please enter your 4 digit code first. (Option 1) ");
                }//end if
                //check to see if current code has already been encrypted
                else if (encrypt_status == 1)
                {
                    printf("\n Your code has already been encrypted.");
                }//end else if
                else
                {
                    //call function code_encrypt to encrypt already entered code
                    code_encrypt(user_code);
                    encrypt_status = 1;
                }//end else
            }//end case
            break;
            case 3:
            {
                //check to see if numbers have been inputted yet
                if (opt1_count < 1)
                {
                    printf("\n Please enter your 4 digit code first. (Option 1) ");
                }//end if
                //checking to see if current code has been enrypted yet
                else if (encrypt_status == 0)
                {
                    printf("\n Please encrypt your code first. (Option 2) ");
                }//end else if
                //checking to see if code has already been checked
                else if (check_status == 1)
                {
                    printf("\n You have already checked this code. Please submit another and check again. (Option1)");
                }//end else if
                else 
                {
                    //call function code_comparison() to compare users encrytped code with the given access code
                    code_comparison(user_code, &result.correct_code, &result.wrong_code);
                    opt3_count = opt3_count + 1;
                    check_status = 1;
                }//end else
            }//end case
            break;
            case 4:
            {
                //check to see if numbers have been inputted yet
                if (opt1_count < 1)
                {
                    printf("\n Please enter your 4 digit code first. (Option 1) ");
                }//end if
                //checking to see ifthe code has already been decrypted 
                else if (encrypt_status == 0)
                {
                    printf("\n The code is currently already decrypted.");
                }//end if 
                else
                {
                    //call function code_decrypt decrypt an encrypted code
                    code_decrypt(user_code);
                    encrypt_status = 0;
                }//end else
            }//end case
            break;
            case 5:
            {
                //check to see if codes have been compared yet
                if (opt3_count < 1)
                {
                    printf("\n You have not compared any codes yet. Please compare a code first. (Option 3) ");
                }//end if
                else 
                {
                    //call function code_counter() to display the amount of times correct or wrong codes have been entered
                    code_counter(&result.correct_code, &result.wrong_code);
                }//end else
            }//end case
            break;
            case 6:
            {
                //exit the program when option 6 is selected
                return 0;
            }//end case
            default: 
                //displaying error message if an invalid inout is entered
                printf("\n Please enter a valid option. \n");
        }//end switch
    }//end do 
    while (!(input == 6)); 
        
    getchar();
}//end main

/* Implement code_entry()
Function to ask the user to either input a code or generate a random code into the array.
Necessary validation and error checking is carried out to prevent letters, numbers out of the range and repeated numbers frombeing inputted.
Code will be between 0000 - 9999 inclusive.
*/
void code_entry(int *code)
{
    int input;
    int i;
    int valid=0;
    int errors;
    int num;
    
    //display options to user 1. enter your own code OR 2. generate random code
    do 
    {
        printf("\nPlease choose an option. \n");
        printf("Option 1: Enter your code manually. \n");
        printf("Option 2: Let the computer select a random code. \n");
        
        scanf("%d", &input);
        //switch case to carry out function inputted by user
        switch(input)
        {
            case 1:
            {
                printf("\n Please enter 4 single digits between 0-9 inclusive. \n");
                //entering a number for each element in the array
                for (i=0;i<SIZE;i++)
                {
                    //loop until input is valid
                    while (1)
                    {
                        errors = 0;
                        scanf("%d", &num);
                        
                        //error check to see if number lies between 0-9 inclusive
                        if (num < 0 || num > 9)
                        {
                            //displaying error message as number does notlie within the range of 1-42
                            printf("\n The number is invalid as it does not lie within the range of 1-42. Please select another number. \n");
                            //incrementing error counter 
                            errors = errors + 1;
                        }//end if
                        //break out of while loop if no errors
                        if (errors == 0)
                        {
                            break;
                        }//end if
                    }//end while
                    
                    //assign chosen number into the code array
                    *(code+i) = num;
                }//end for
                printf("\n You chose the numbers ");
                //displaying numbers
                for (i=0;i<SIZE;i++)
                {
                    printf("%d", *(code+i));
                }//end for
                printf("\n Your code has been entered into the array. \n");
                valid = 1;
            }//end case
            break;
            case 2:
            {
                //selecting a random numbe rfor each element of the array 
                for (i=0;i<SIZE;i++)
                {
                    *(code+i) = rand() % 9+1;
                }//end for
                
                printf("\n A random code has been generated. \n");
                printf(" The random code generated is ");
                //displaying random generated code.
                for (i=0;i<SIZE;i++)
                {
                    printf("%d", *(code+i));
                }//end for
                printf("\n These numbers have been entered into the array.");
                valid = 1;
            }//end case
            break;
            default: 
                //displaying error message if an invalid inout is entered
                printf("\n Please enter a valid option. \n");
        }//end switch 
    }//end do 
    while (valid == 0);
}//end code_entry()

/*Implement code_encrypt 
Function to encrypt users selected code using a given encryption algorithm.
*/
void code_encrypt(int *code)
{
    int temp;
    int i;
    
    //swapping first and third number
    temp = *(code+0);
    *(code+0) = *(code+2);
    *(code+2) = temp;
    //swapping the second and fourth number
    temp = *(code+1);
    *(code+1) = *(code+3);
    *(code+3) = temp;
    //adding 1 to each number
    for (i=0;i<SIZE;i++)
    {
        *(code+i) = *(code+i) + 1;
        //if number is 10 after addition it is changed back to 0
        if (*(code+i) == 10)
        {
            *(code+i) = 0;
        }//end if
    }//end for
    
    printf("\n The code has now been encrypted.\n");
    printf(" Your encrypted code is ");
    //displaying encrypted code
    for (i=0;i<SIZE;i++)
    {
        printf("%d", *(code+i));
    }//end for
    
}//end code_encrypt()

/* Implement code_decrypt 
Function to decrypt users encrypted code using a given decryption algorithm
*/
void code_decrypt (int *code)
{
    int temp;
    int i;
    
    //subtracting one from each number
    for (i=0;i<SIZE;i++)
    {
        *(code+i) = *(code+i) - 1;
        //if number is now -1 after subtraction it will now be a 9
        if (*(code+i) == -1)
        {
            *(code+i) = 9;
        }//end if
    }//end for
    
    //swapping first and third number
    temp = *(code+0);
    *(code+0) = *(code+2);
    *(code+2) = temp;
    //swapping the second and fourth number
    temp = *(code+1);
    *(code+1) = *(code+3);
    *(code+3) = temp;
    
    printf("\n The code has now been decrypted.\n");
    printf(" Your decrypted code is ");
    //displaying encrypted code
    for (i=0;i<SIZE;i++)
    {
        printf("%d", *(code+i));
    }//end for
}//end code_decrypt

/*Implement code_comparison() 
Function to compare the users encrypted code with the given access code (4523)
Function will also count how many times the users code is correct or wrong.
*/
void code_comparison (int *code ,int *correct_count, int *wrong_count)
{
    const int access_code[SIZE] = {4,5,2,3};
    int i;
    int errors = 0;
    
    printf("\n Your code is ");
    //displaying code
    for (i=0;i<SIZE;i++)
    {
        printf("%d", *(code+i));
    }//end for
    
    //comparing user code with access code
    for (i=0;i<SIZE;i++)
    {
        //incrementing error checker if numbers arent the same 
        if ( !(*(access_code+i) == *(code+i)))
        {
            errors = errors + 1;
        }//end if
    }//end for
    
    //checking to see how many errors are in users code if 0 errors then code is correct
    if (errors == 0)
    {
        printf("\n Code is Correct! Access Granted.");
        *correct_count = *correct_count + 1;
    }//end if
    else
    {
        printf("\n Code is Wrong ! Access Denied.");
        *wrong_count = *wrong_count + 1;
    }//end else
    
}//end code comparison

/* Implement code_counter() 
Function to display the amount of times the code has been correct or wrong whilst the program has been running
*/
void code_counter(int *correct_count, int *wrong_count)
{
    int input;
    
    printf("\n Please choose an option. \n");
    printf(" Option 1: Display the amount of times the code has been correct. \n");
    printf(" Option 2: Display the amount of times the code has been wrong. \n");
    
    scanf("%d", &input);
    
    //switch menu to only show the option entered 
    switch(input)
    {
        case 1:
        {
            printf("\n Correct code has been entered %d times whilst the program has been running. \n", *correct_count);
        }//end case
        break;
        case 2:
        {
            printf("\n Wrong code has been entered %d times whilst the program has been running. \n", *wrong_count);
        }//end case
        break;
        default: 
            //displaying error message if an invalid inout is entered
            printf("\n Please enter a valid option. \n");
    }//end switch 
}//end code_counter()