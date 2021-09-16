#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#define VERY_LONG_STRING 300
#define SHORT_STRING  20
#define MEDIUM_SHORT_STRING 15
#define VERY_SHORT_STRING 10
#define USER_FILE_NAME  "users.txt"
#define GROUP_FILE_NAME  "groups.txt"
#define MEMBER_FILE_NAME  "group_members.txt"
#define MEMBER_TASK_FILE_NAME  "group_members_task.txt"

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


// struct for Group Member Create
struct Members{
    int gorup_id;
    int member_id;
    char mobile_number[SHORT_STRING], email[MEDIUM_SHORT_STRING],
    user_name[VERY_SHORT_STRING];

};

// struct for Group Member Task Assign
struct MembersTask{
    int group_id;
    int group_member_id;
    char member_user_name[VERY_SHORT_STRING];
    char task_description[VERY_LONG_STRING];
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

    FILE *log;
    struct Users user;
    log = fopen(USER_FILE_NAME, "r");
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

     FILE *log = fopen(USER_FILE_NAME, "a+");
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
    printf("\t\t\t\t\t\t<<<<Please Enter 'G' for Create New Group.>>>>\n\n");
    printf("\t\t\t\t\t\t<<<<Please Enter 'M' for New Member Add in Group.>>>>\n\n");
     printf("\t\t\t\t\t\t<<<<Please Enter 'T' for Group Members Task Assign.>>>>\n\n");
     printf("\t\t\t\t\t\t<<<<Please Enter 'D' for  Members Task Show.>>>>\n\n");
         printf("\t\t\t\t\t\t<<<<Please Enter 'U' for  All User Information.>>>>\n\n");
    printf("\t\t\t\t\t\t<<<<Enter 'E' for stop this application.>>>>\n\n");
    count_all_group();
    display_groups();
    initial_command_input();
dashboard_all_command_for_admin_user();

        return;
}

/*Function for dashboard command */
void dashboard_all_command_for_admin_user(){

 if(initial_command == 'G'){
        create_group();
    }
   else if(initial_command == 'M'){

        add_gorup_member();
    }
   else if( initial_command == 'T' ){

        group_member_task_assign();
    }
   else if(initial_command== 'D')
   {
        display_members_task();
   }
   else if(initial_command== 'U')
   {
        display_all_user();
   }
   else{
            initial_command_input();
                  printf("\n\n");
                dashboard_all_command_for_admin_user();
   }
    return;
}

/*Function to Group Create*/
void create_group()
{
  FILE *log = fopen(GROUP_FILE_NAME, "a+");
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
    int total_group=0;
  FILE *infile;
    struct  Groups group;

    // Open person.dat for reading
    infile = fopen (GROUP_FILE_NAME, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&group, sizeof(struct Groups), 1, infile)){
        printf ("\t\t\t\t\t\t<<<<ID = %d NAME = %s.>>>>\n\n", group.id,group.name);
    }
    // close file
    fclose (infile);

}

/*Function to Count All Groups*/
void count_all_group(){

 int total_group=0;
  FILE *infile;
    struct  Groups group;

    // Open person.dat for reading
    infile = fopen (GROUP_FILE_NAME, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&group, sizeof(struct Groups), 1, infile)){
       total_group+=1;
    }
    printf("\t\t\t\t\t\t<<<<Total Groups:%d!!>>>>\n",total_group);
    // close file
    fclose (infile);
}

/*Function for create group members*/
void add_gorup_member(){
struct Members member;
  printf("\tPlease enter Group Id:");
    scanf("%d", &member.gorup_id);
      printf("\tPlease enter Member Id:");
    scanf("%d", &member.member_id);
     printf("\tPlease enter your User name. User Name length must be between 1 to 10 characters:");
    scanf("%s", &member.user_name);
      printf("\tPlease enter your email address. Email length must be between 1 to 15 characters:");
    scanf("%s", &member.email);
      printf("\tPlease enter your mobile number. Mobile number length must be between 1 to 11 characters:");
    scanf("%s", &member.mobile_number);
    bool account_create = true;

     FILE *log = fopen(MEMBER_FILE_NAME, "a+");
     fwrite(&member, sizeof(struct  Members), 1, log);
     fclose(log);
     getchar();

    if(account_create == true){
             printf("\t\t<<<You are successfully add member in Group=> %d.>>>\n\n", member.gorup_id);
             display_group_members(member.gorup_id);
             printf("\n\n");
                initial_command_input();
                  printf("\n\n");
                dashboard_all_command_for_admin_user();
         }
         else{
                printf("\t\tYou are Account is not created successfully!!\n\n");
         }

    return 0;
}

/*Function To Display  Group Members By Group Id*/
void display_group_members(int gorup_id){
  FILE *infile;
    struct  Members member;
    // Open person.dat for reading
    infile = fopen (MEMBER_FILE_NAME, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    // read file contents till end of file
    while(fread(&member, sizeof(struct Members), 1, infile)){
            if(gorup_id==member.gorup_id){
        printf ("\t\t\t<<<<GroupID = %d MemberID = %d User Name = %s Email = %s Mobile = %s.>>>>\n\n", member.gorup_id,member.member_id, member.user_name, member.email, member.email);
            }
    }
    // close file
    fclose (infile);

}

/*Function for task assign in group members*/
void group_member_task_assign(){
   struct MembersTask member_task;
  printf("\tPlease enter GroupId:");
    scanf("%d", &member_task.group_id);
    display_group_members(member_task.group_id);

    printf("\tPlease enter Group MemberId:");
    scanf("%d", &member_task.group_member_id);

      printf("\tPlease enter your Member User name. Member User Name length must be between 1 to 10 characters:");
    scanf("%s", &member_task.member_user_name);

      printf("\tEnter Member Task. Task Description length must be between 1 to 300 characters:");
    scanf("%[^.]", &member_task.task_description);

    bool account_create = true;

     FILE *log = fopen(MEMBER_TASK_FILE_NAME, "a+");
     fwrite(&member_task, sizeof(struct  MembersTask), 1, log);
     fclose(log);
     getchar();

    if(account_create == true){
             printf("\t\t<<<Member %d Task Assign is successfully!!>>>\n\n", member_task.group_member_id);
             display_group_members_task(member_task.group_id);
             printf("\n\n");
                initial_command_input();
                  printf("\n\n");
                dashboard_all_command_for_admin_user();
         }
         else{
                printf("\t\tYou are Account is not created successfully!!\n\n");
         }

    return 0;


}

/*Function To Display  Group Members Task By Group Id*/
void display_group_members_task(int gorup_id){
  FILE *infile;
    struct  MembersTask member_task;

    // Open person.dat for reading
    infile = fopen (MEMBER_TASK_FILE_NAME, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&member_task, sizeof(struct MembersTask), 1, infile)){
            if(gorup_id==member_task.group_id){
        printf ("\t<<<<GroupID = %d MemberID = %d User Name = %s Description = %s.>>>>\n\n", member_task.group_id,member_task.group_member_id, member_task.member_user_name ,  member_task.task_description );
            }
    }
    // close file
    fclose (infile);

}

/*Function to seen personal Task*/
void display_members_task(){
    int member_id;
    printf("\n\n\t\t\t<<<Please Enter your Member Id to see your Task>>>> :");
    scanf("%d", &member_id);
  FILE *infile;
    struct  MembersTask member_task;

    // Open person.dat for reading
    infile = fopen (MEMBER_TASK_FILE_NAME, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&member_task, sizeof(struct MembersTask), 1, infile)){
            if(member_id==member_task.group_member_id){
        printf ("\tGroupID = %d || MemberID = %d || User Name = %s  ||Description = %s.\n\n", member_task.group_id,member_task.group_member_id, member_task.member_user_name ,  member_task.task_description );
            }
            else{
               initial_command_input();
                  printf("\n\n");
                dashboard_all_command_for_admin_user();
            }
    }
    // close file
    fclose (infile);

}

/*Function to seen all User*/
void display_all_user(){


  FILE *infile;
    struct  Users user;

    // Open person.dat for reading
    infile = fopen (USER_FILE_NAME, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&user, sizeof(struct Users), 1, infile)){

        printf ("\tFull Name = %s || Email = %s || Mobile = %s  || User Name = %s .\n\n", user.full_name,user.email, user.mobile_number, user.user_name );


               initial_command_input();
                  printf("\n\n");
                dashboard_all_command_for_admin_user();

    }
    // close file
    fclose (infile);

}































































































































