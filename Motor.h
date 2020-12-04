//
//  Motor.h
//  
//
//  Created by Castro Bouquet Ildefonso on 27/11/2020.
//
#ifndef Motor_h
#define Motor_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#ifdef Motor_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/**
*This function validates file by opening and closing, if file can open it exist.If not exit program.
*
*@param
*   (char *)fileName: array with the name file to open.
*
*@returns
*
*/
EXTERN void valFile(char *fileName);

/**
*This function takes a 0x0 ptr and creates random values from (0-.999) and allocates them in the ptr.
*
*@param
*   (float **)ptr: array with trash values.
*   (int *)users: rows for ptr.
*   (int *)stats: columns for ptr.
*
*@returns
*
*/
EXTERN void randomUserNumbers(float **ptr,int *users,int *stats);

/**
*This function reads file and saves every char in char ptr. NO MATTER SIZE OF FILE.
*Saves how many rows and columns.
*
*@param
*   (char *)fileName: name of file to read.
*   (char ***)ptr: ptr where to save chars. Triple pointer to modify main.c values, not only local.
*   (int *)row: Enter without value, exit with number of rows in file.
*   (int *)column: Enter without value, exit with number of columns in file.
*
*@returns
*
*/
EXTERN void readFile(char fileName[],char ***ptr,int *row,int *column);

/**
*This function takes to vectors and calculate Dot Product.
*
*@param
*   (float *)vector_2: ptr of vector 1.
*   (float *)vector_2: ptr of vector 2.
*   (int)v_size: How many values of ptr to do.
*
*@returns
*   (float)dot_prod: result of dot Product.
*/
/*  THIS FUNCTION WAS GIVEN BY PROFESOR ANGELES RUIZ CESAR ARTURO  */
/*  ALL CREDITS ARE FOR HIM   */
EXTERN float my_dot_product(float * vector_1, float * vector_2, int v_size);

/**
*This function trains the system and modifies values for users and movies stats. This is done by using formulas and some Lineal Algebra
*
*@param
*   (float ***)ptr: ptr of users information.
*   (float ***)ptr2: ptr2 of movies information.
*   (float ***)ptr3: ptr3 of ratings information.
*   (int *)users: How many users.
*   (int *)stats: How many stats.
*   (int *)movies: How many movies.
*
*@returns
*
*/
EXTERN void training(float ***ptr,float ***ptr2,float ***ptr3,int *users,int *stats,int *movies);

/**
*This function ask for User ID and finds 3 movies that havent been seen and that maybe the user will Like. Done with Dot Product.
*
*@param
*   (float ***)ptr: ptr of users information.
*   (float ***)ptr2: ptr2 of movies information.
*   (float ***)ptr3: ptr3 of ratings information.
*   (int *)users: How many users.
*   (int *)stats: How many stats.
*   (int *)movies: How many movies.
*
*@returns
*
*/
EXTERN void newReco(float ***ptr,float ***ptr2,float ***ptr3,int *users,int *stats,int *movies);

/**
*This function ask for User ID and search for similar users with similar tastes. Done with Dot Product.
*
*@param
*   (float ***)ptr: ptr of users information.
*   (int *)users: How many users.
*   (int *)stats: How many stats.
*
*@returns
*
*/
EXTERN void simFriends(float ***ptr,int *users, int *stats);

/**
*This function ask for Movie ID and search for similar movies with similar genres. Done with Dot Product
*
*@param
*   (float ***)ptr: ptr of users information.
*   (int *)movies: How many movies.
*   (int *)stats: How many stats.
*
*@returns
*
*/
EXTERN void simMovie(float ***ptr,int *movies,int *stats);

/**
*This function saves ptr to a file given by param.
*
*@param
*   (float *)fileName: Name of file to write.
*   (float ***)ptr: ptr with information.
*   (int *)row: How many rows.
*   (int *)column: How many columns.
*
*@returns
*
*/
EXTERN void save(char *fileName,float ***ptr,int *row, int *column);

/**
*This function takes the char ptr info and gives a float format, creates space and save it on a float ptr.
*
*@param
*   (char **)ptr: information in string.
*   (float ***)ptr2: new ptr2 type float with the same ptr char values.
*   (int *)row: How many rows.
*   (int *)column: How many columns.
*
*@returns
*
*/
EXTERN void format(char **ptr,float ***ptr2,int *row,int *movies);

/**
*This function free pointer.
*
*@param
*   (float ***)ptr: ptr with information.
*   (int *)row: How many rows.
*   (int *)column: How many columns.
*
*@returns
*
*/
EXTERN void liberar();

/**
*This function will append to a file the errorEpoch.
*
*@param
*   (float)e: value of error.
*   (int)n: number of actual epoch.
*
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void appendError(float e, int n);

/**
*This function will call gnuplot, and open file with values.
*
*@param
*   
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void openGnu();

#undef Motor_IMPORT
#undef EXTERN

#endif /* Motor_h */
