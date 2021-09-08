#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#define LONG_STRING 100
#define SHORT_STRING  20
#define MEDIUM_SHORT_STRING 15
#define VERY_SHORT_STRING 10
char initial_command;
int authentication_token=0;
// struct for Group
 struct Groups {
  int id;
  char name[SHORT_STRING];
};
// struct for User New Account
struct Users{
char full_name[SHORT_STRING], mobile_number[SHORT_STRING], email[MEDIUM_SHORT_STRING],
user_name[VERY_SHORT_STRING],  password[VERY_SHORT_STRING], confirm_password[VERY_SHORT_STRING];
};


int main()
{
    first_window_messages();
    initial_command_input();
    initial_command_logic();
    if (authentication_token==1){
        printf("\t\tYou are Successfully login\n\n");
        dashboard_data_show_admin_user();
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

    FILE *log;
  struct Users user;
  log = fopen("users.txt", "r");
  if (log == NULL)
  {
    printf("FILE NOT FOUND!!!\n");
    return 0; // login failed
  }

  while (fread(&user, sizeof(user), 1, log))
  {
    if (strcmp(user_name, user.user_name ) == 0 && strcmp(password, user.password)==0)
    {
      fclose(log);
      return 1; // login succeeded
    }
  }
  getchar();
  fclose(log);

return 0;
}
/*Function to Create New Account*/
int create_new_account(){
   struct Users user;
  printf("\tPlease enter your full name. Full name length must be between 1 to 20 characters:");
    scanf("%s", &user.full_name);
      printf("\tPlease enter your mobile number. Mobile number length must be between 1 to 11 characters:");
    scanf("%s", &user.mobile_number);
      printf("\tPlease enter your email address. Email length must be between 1 to 15 characters:");
    scanf("%s", &user.email);
      printf("\tPlease enter your User name. User Name length must be between 1 to 10 characters:");
    scanf("%s", &user.user_name);
      printf("\tPlease enter your password. Password length must be between 1 to 10 characters:");
    scanf("%s", &user.password);
      printf("\tPlease Enter your Confirm password:");
    scanf("%s", &user.confirm_password);
    bool account_create = true;

     FILE *log = fopen("users.txt", "a+");
     fwrite(&user, sizeof(struct  Users), 1, log);
     fclose(log);
     getchar();

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

/*Function for dashboard data showing administrator user*/
void dashboard_data_show_admin_user(){
    printf("\t\t\t\t\t\t<<<<Welcome to Task Management System Dashboard>>>>!\n\n\n");
    printf("\t\t\t\t\t\t<<<<Please Enter 'L' for Sign-in.>>>>\n\n");
    printf("\t\t\t\t\t\t<<<<Please Enter 'A' for New Account.>>>>\n\n");
    printf("\t\t\t\t\t\t<<<<Enter 'E' for stop this application.>>>>\n\n");
        create_group();
        display_groups();
}

/*Function to Group Create*/

void create_group()
{
  FILE *log = fopen("groups.txt", "a+");
 struct  Groups group;
   printf("\nEnter Group Id: ");
  scanf("%d", &group.id);
  printf("\nEnter Group name: ");
  scanf("%s", &group.name);
  fwrite(&group, sizeof(struct  Groups), 1, log);
  fclose(log);
  printf("\nYou are successfully create group!!");
  printf("\nYour GroupId is %d and your Group name is %s\n\n", group.id, group.name);
  getchar();
  return;
}

/*Function To Display Group Information*/
void display_groups(){

  FILE *infile;
    struct  Groups group;

    // Open person.dat for reading
    infile = fopen ("groups.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&group, sizeof(struct Groups), 1, infile))
        printf ("id = %d name = %s\n", group.id,group.name);

    // close file
    fclose (infile);

}












































































































































