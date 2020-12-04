//
//  Vista.c
//  
//
//  Created by Castro Bouquet Ildefonso on 02/11/2020.
//

/* Libraries */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* Custom Libraries */

/* Vista.c -- Functions */

/**
*This function generates a menu for the program, asking what action does the user want to do.
*Shows 8 paths were each one have a different function, and diferent purpose.
*
*@param
*
*@returns
*   input of user based on 8 posible answers.(0-7)
*
*/
/*------------------------------------------------------------------------------------------*/
int menu()
{   
    int x;
    do
    {
        printf("===========================================================\n");
        printf("=                          MENU                           =\n");
        printf("=                                                         =\n");
        printf("=1) Print user and movie consults                         =\n");
        printf("=2) Print movie ratings per user or users per movie       =\n");
        printf("=3) System Training                                       =\n");
        printf("=4) Recommend movie                                       =\n");
        printf("=5) Posibles Friends                                      =\n");
        printf("=6) Similar movies                                        =\n");
        printf("=7) Save files                                            =\n");
        printf("=0) Exit Programm                                         =\n");
        printf("=                                                         =\n");
        printf("===========================================================\n");
        printf("Input an option: ");
    }while((scanf("%d",&x)!=1)||((x<0)||(x>7)));
    return x;
}

/**
*This function prints 3 options. If want to see User, Movie or come back to the Main Menu.
*
*@param
*
*@returns
*   input of user based on 3 posible answers.(1-3)
*
*/
/*------------------------------------------------------------------------------------------*/
int printConsultas()
{
    int x;
    do
    {
        printf("=======================================\n");
        printf("=  What Menu do you want to Consult:\n= 1)Users\n= 2)Movies\n= 3)Main Menu\n");
        printf("=======================================\n");
        printf("Option: ");
        scanf("%d",&x);
    }while(x<1||x>3);
    return x;
}

/**
*This function ask for ID depending if we want MovieID or UserID, give format to char string, and validates if ID isnt out of range via (int)max.
*
*@param
*   (int)num: (1||2) just to show different message.
*   (int)max: number of values in the ptr.
*@returns
*   (int)ID: the UserID or MovieID already validated.
*
*/
/*------------------------------------------------------------------------------------------*/
int askID(int num, int max)
{
    char id[3];
    int ID;
    do{
        switch(num)
        {
            case 1:
            printf("Introduce User ID: ");
            break;
            case 2:
            printf("Introduce Movie ID: ");
            break;
        }
        __fpurge(stdin);
        gets(id);
        ID=atoi(id);
        if((ID<0)||(ID>=max))
        {
            printf("ID %d doesnt exist.\n",ID);
        }
    }while((ID<0)||(ID>=max));
    return ID;
}

/**
*This function prints all genre statistics for ID User
*
*@param
*   (float **)ptr: ptr with all the users info.
*   (int *)users: rows of ptr.
*   (int *)stats: columns of ptr.
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void consultUser(float **ptr,int *users,int *stats)
{
    int i,ID,x=1;
    while(x==1)
    {
        printf("=======================================\n");
        printf("=            Consult Users            =\n");
        ID=askID(1,(*users));
        printf("Genre statistics for ID User are:\n");
        for(i=0;i<(*stats);i++)
        {
            printf("%d) %f\n",i+1,ptr[ID][i]);
        }
        do
        {
            printf("Want to look for another user?\n1)Yes 2)No\n");
            printf("Option: ");
            scanf("%d",&x);
        }while(x!=1 && x!=2);
    }
}

/**
*This function prints all genre statistics for ID Movie
*
*@param
*   (float **)ptr: ptr with all the movies info.
*   (int *)stats: rows of ptr.
*   (int *)movies: columns of ptr.
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void consultMovies(float **ptr,int *stats,int *movies)
{
    int i,ID,x;
    do
    {   
        printf("========================================\n");
        printf("=            Consult Movies            =\n");
        ID=askID(2,(*movies));
        if((ID<0)||(ID>(*movies)))
        printf("Genre statistics for ID Movie are:\n");
        for(i=0;i<(*stats);i++)
        {
            printf("%d) %f\n",i+1,ptr[i][ID]);
        }
        do
        {
            printf("Want to look for another Movie?\n1)Yes 2)No\n");
            printf("Option: ");
            scanf("%d",&x);
        }while(x!=1 && x!=2);
    }while(x==1);
}

/**
*This function prints 3 options. If want to see User, Movie or come back to the Main Menu.
*
*@param
*
*@returns
*   input of user based on 3 posible answers.(1-3)
*
*/
/*------------------------------------------------------------------------------------------*/
int printRating_UM()
{
    int x;
    do
    {
        printf("========================================\n");
        printf("= How do you want to print ratings by? =\n");
        printf("= 1) User\n= 2) Movie\n= 3) Cancel\n");
        printf("========================================\n");
        printf("Option: ");
        scanf("%d",&x);
    }while(x<1||x>3);
    return x;
}

/**
*This function prints the rating the movies by ID User.
*
*@param
*   (float **)rank: ptr with all the users info.
*   (int *)users: rows of ptr.
*   (int *)movies: columns of ptr.
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void printRating(float **rank,int *users,int *movies)
{
    int i,ID,x,y;
    do
    {
        printf("========================================\n");
        printf("=            Movie Ratings             =\n");
        y=printRating_UM();
        if(y==3)
        {
            return;
        } 
        if(y==1)
        {
            ID=askID(1,(*users));
            printf("Movie Ratings of User %d:\n",ID);
            for(i=0;i<(*movies);i++)
            {
                printf("Movie %d: %f \n",i+1,rank[ID][i]);
            }
        }
        if(y==2)
        {
            ID=askID(2,(*movies));
            printf("User Ratings of Movie %d:\n",ID);
            for(i=0;i<(*users);i++)
            {
                printf("User %d: %f \n",i+1,rank[i][ID]);
            }
        }
        do
        {
            printf("Want to look for another User/Movies rankings?\n1)Yes 2)No\n");
            printf("Option: ");
            scanf("%d",&x);
        }while(x!=1 && x!=2);
    }while(x==1);
}

/**
*This function ask how many cycles to do for the training.
*
*@param
*
*@returns
*   (int)cant: Quantity of cycles to do.
*
*/
/*------------------------------------------------------------------------------------------*/
int askEpocs()
{
    int cant;
    printf("=============================================\n");
    printf("How many Epocs (cycles) do you want to train?\n");
    printf("Quantity: ");
    scanf("%d",&cant);
    return cant;
}

/**
*This function prints the 3 number string. With some text for easy reading.
*
*@param
*   (int *)moviesID: 3 number array of recommended movies.
*
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void p_Movies(int *moviesID)
{
    int i;
    printf("We recommend for you to see:\n");
    for(i=0;i<3;i++)
    {
        printf("%d) Movie with ID: %d\n",i+1,moviesID[i]);
    }
}

/**
*This function prints the 3 number string. With some text for easy reading.
*
*@param
*   (int *)usersID: 3 number array of recommended friends.
*
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void p_Friends(int *usersID)
{
    int i;
    printf("We found these similar people: \n");
    for(i=0;i<3;i++)
    {
        printf("%d) User with ID: %d\n",i+1,usersID[i]);
    }
}