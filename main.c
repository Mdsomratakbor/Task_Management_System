#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>



int main()
{
    char initial_command;
    int authentication_token=0;
    first_window_messages();

    printf("\tEnter your command keyword:");
    scanf("%c", &initial_command);
    if(initial_command == 'L')
    {
     authentication_token =   login();
    }
    if (authentication_token==1){
        printf("\t\tYou are Successfully login\n\n");
    }
    else{
        printf("\t\tPlease Enter valid User Name and User Password!!\n\n");

    printf("\tEnter your command keyword:");
    scanf("%c\n\n", &initial_command);
    }

    return 0;
}
/*Function to show the initial information in first window*/
void first_window_messages(){
  printf("\t\t\t\t\t\tWelcome to Task Management System!\n\n\n");
    printf("\t\t\t\t\t\tPlease Enter 'L' for Sign-in.\n\n");
    printf("\t\t\t\t\t\tPlease Enter 'A' for New Account.\n\n");
    printf("\t\t\t\t\t\tEnter 'E' for stop this application.\n\n");
    return;
}

/*Function to User Authorization Checking*/
int login(){
    char user_name[12]; char password[10];
      printf("\tPlease Enter your User Name:");
    scanf("%c\n\n", &user_name);
      printf("\tPlease Enter your Password:");
    scanf("%c\n\n", &password);

    if(user_name == "somrat" && password == "123"){
        return 1;
    }


return 0;
}
