#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
char initial_command;
int authentication_token=0;
int main()
{
    first_window_messages();
    initial_command_input();
    initial_command_logic();
    if (authentication_token==1){
        printf("\t\tYou are Successfully login\n\n");
    }
    return 0;
}

/*Function for initial command*/
void initial_command_logic(){
   if(initial_command == 'L')
    {
    login_all_logic();
    }
    else if(initial_command =='A'){
        create_new_account();
    }
    else if(initial_command=='E'){
        return 0;
    }
    else {
         printf("\t<<<<Please Enter Valid Command.>>>>\n\n");
          initial_command_input();
            initial_command_logic();
    }
}

/*Initial command input code*/
void initial_command_input(){

 printf("\tEnter your command keyword:");
    scanf("%c", &initial_command);
    if(initial_command=='\n')
        scanf("%c", &initial_command);
    return;
}


/*Function for login logic*/
void login_all_logic(){
        authentication_token =   login();
        if (authentication_token==0){
        printf("\t\tPlease Enter valid User Name and User Password!!\n\n");
        initial_command_input();
            initial_command_logic();
        }
    return;
}

/*Function to show the initial information in first window*/
void first_window_messages(){
  printf("\t\t\t\t\t\t<<<<Welcome to Task Management System>>>>!\n\n\n");
    printf("\t\t\t\t\t\t<<<<Please Enter 'L' for Sign-in.>>>>\n\n");
    printf("\t\t\t\t\t\t<<<<Please Enter 'A' for New Account.>>>>\n\n");
    printf("\t\t\t\t\t\t<<<<Enter 'E' for stop this application.>>>>\n\n");
    return;
}

/*Function to User Authorization Checking*/
int login(){
    char user_name[12]; char password[10];
      printf("\tPlease Enter your User Name:");
    scanf("%s", &user_name);
      printf("\tPlease Enter your Password:");
    scanf("%s", &password);

    int user_name_correct, password_correct;
    user_name_correct=strcmp(user_name,"somrat");
    password_correct=strcmp(password,"123");

    if(user_name_correct == 0 && password_correct == 0){
        return 1;
    }

return 0;
}
/*Function to Create New Account*/
int create_new_account(){
char full_name[20], mobile_number[11], email[15], user_name[10],  password[10], confirm_password[10];
  printf("\tPlease enter your full name. Full name length must be between 1 to 20 characters:");
    scanf("%s", &full_name);
      printf("\tPlease enter your mobile number. Mobile number length must be between 1 to 11 characters:");
    scanf("%s", &mobile_number);
      printf("\tPlease enter your email address. Email length must be between 1 to 15 characters:");
    scanf("%s", &email);
      printf("\tPlease enter your User name. User Name length must be between 1 to 10 characters:");
    scanf("%s", &user_name);
      printf("\tPlease enter your password. Password length must be between 1 to 10 characters:");
    scanf("%s", &password);
      printf("\tPlease Enter your Confirm password:");
    scanf("%s", &confirm_password);
    bool account_create = true;
    if(account_create == true){
             printf("\t\t<<<You are Account is created successfully!!>>>\n\n");
             printf("\n\n");
                initial_command_input();
                  printf("\n\n");
                initial_command_logic();
         }
         else{
                printf("\t\tYou are Account is not created successfully!!\n\n");
         }

    return 0;
}
