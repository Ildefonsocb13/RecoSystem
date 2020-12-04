//
//  Vista.h
//  
//
//  Created by Castro Bouquet Ildefonso on 02/12/2020.
//
#ifndef Vista_h
#define Vista_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#ifdef Vista_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


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
EXTERN int menu();

/**
*This function prints 3 options. If want to see User, Movie or come back to the Main Menu.
*
*@param
*
*@returns
*   input of user based on 3 posible answers.(1-3)
*
*/
EXTERN int printConsultas();

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
EXTERN int askID(int num, int max);

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
EXTERN void consultUser(float **ptr,int *users,int *stats);

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
EXTERN void consultMovies(float **ptr,int *stats,int *movies);

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
EXTERN int printRating_UM();

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
EXTERN void printRating(float **rank,int *users,int *movies);

/**
*This function ask how many cycles to do for the training.
*
*@param
*
*@returns
*   (int)cant: Quantity of cycles to do.
*
*/
EXTERN int askEpocs();

/**
*This function prints the 3 number string. With some text for easy reading.
*
*@param
*   (int *)moviesID: 3 number array of recommended movies.
*
*@returns
*
*/
EXTERN void p_Movies(int *moviesID);

/**
*This function prints the 3 number string. With some text for easy reading.
*
*@param
*   (int *)usersID: 3 number array of recommended friends.
*
*@returns
*
*/
EXTERN void p_Friends(int *usersID);

#undef Vista_IMPORT
#undef EXTERN

#endif /* Vista_h */