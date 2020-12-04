//
//  Netflix.c
//  
//
//  Created by Castro Bouquet Ildefonso on 21/11/2020.
//

/* Libraries */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* Custom Libraries */

#include"Motor.h"
#include"Vista.h"

/* Main Function */
int main (int argc, char *argv[])
{   
    system("clear");
   
    /*Variables*/

    char fileName[40];   
    int opcion=1,i,x;
    float **user,**object,**rank;
    int stats, movies, users;
    char **file1,**file2,**file3;

    /*Process*/

    if(argc<=2||argc>=5)
    {
        printf("Incorrect Format\n");
        printf("For First Time use:\n./Netflix \"MoviesFileName\" \"UserRankingMoviesFileName\"\n");
        printf("If not First Time use:\n./Netflix \"MoviesFileName\" \"UserRankingMoviesFileName\" \"User.dat\"\n");
        exit(0);
    }
    //Validate if files open
    valFile(argv[1]);
    valFile(argv[2]);
    if(argc==4)
    {
        valFile(argv[3]);
    }
    //Validate if files open, before doing any proccess

    //readFiles, saves info in char ptr
    readFile(argv[1],&file1,&stats,&movies);
    readFile(argv[2],&file2,&users,&movies);
    if(argc==4)
    {
        readFile(argv[3],&file3,&users,&stats);
    }

    //change format from char ptr to float ptr
    format(file1,&object,&stats,&movies);
    format(file2,&rank,&users,&movies);
    if(argc==4)
    {
        format(file3,&user,&users,&stats);
    }

    if(argc==3)
    {
        //Malloc on User ptr, asign random values from 0 to 1.
        user=malloc((users)*(sizeof(float*)));
        for(i=0;i<users;i++)
        {
            user[i]=malloc((stats)*sizeof(float));
        }
        randomUserNumbers(user,&users,&stats);
    }
    
    //User Interactive
    do
    {   
        //system("clear");
        opcion=menu();//Returns input of one of many options to do.
        switch(opcion)
        {
            case 1://Consult User or Movie
                system("clear");
                do
                {
                    x=printConsultas();//Print consults of User or Movie
                    switch(x)
                    {
                        case 1:
                            consultUser(user,&users,&stats);//print consult of User
                        break;
                        case 2:
                            consultMovies(object,&stats,&movies);//Print consult of Movie
                        break;
                        case 3:
                        //cancel option
                        break;
                    }
                }while(x!=3);
                system("clear");
            break;
            case 2://Ratings of movies
                system("clear");
                printRating(rank, &users, &movies);

                //Imprime ratings de peliculas por usuario o usuarios por pelicula
                system("clear");
            break;
            case 3://Train system
                system("clear");
                training(&user,&object,&rank,&users,&stats,&movies);//Train the recommendation system
            break;
            case 4://Recommend movie
                system("clear");
                newReco(&user,&object,&rank,&users,&stats,&movies);//Print 3 Recommendations of movies
                system("clear");
            break;
            case 5://Similar Friends
                system("clear");
                simFriends(&user,&users,&stats);//Print 3 friends with similar likes than ID User
                system("clear");
            break;
            case 6://Similar Movies
                system("clear");
                simMovie(&object,&stats,&movies);//Print 3 Similar Movies to the one ask on input
                system("clear");
            break;
            case 7://Save
                system("clear");
                //Overwrites inicial file data with the new Data, third file created with users Data
                save(argv[1],&object,&stats,&movies);//Guarda las tablas en el archivo CSV
                save(argv[2],&rank,&users,&movies);
                strcpy(fileName,"User.dat");
                save(fileName,&user,&users,&stats);
                printf("Files had been saved correctly!\n");
            break;
            case 0://Quit
                do
                {
                    printf("Do you want to save before exit?\n1)yes\n2)no\n3)Cancel\n");
                    printf("Option: ");
                    scanf("%d",&x);
                }while(x<1 && x>3);
                if(x==3)
                {
                    opcion=1;
                    system("clear");
                }
                else
                {
                    if(x==1)
                    {
                        save(argv[1],&object,&stats,&movies);//Guarda las tablas en el archivo CSV
                        save(argv[2],&rank,&users,&movies);
                        strcpy(fileName,"User.dat");
                        save(fileName,&user,&users,&stats); 
                    }
                    printf("Thanks for beeing here.\n");
                    liberar(&user,&users,&stats);
                    liberar(&object,&stats,&movies);
                    liberar(&rank,&users,&movies);
                    openGnu();
                    exit(0);    
                }
            break;
        }
    }while(opcion!=0);
}
/*End Main*/