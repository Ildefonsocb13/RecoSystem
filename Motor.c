//
//  Motor.c
//  
//
//  Created by Castro Bouquet Ildefonso on 25/11/2020.
//

/* Libraries */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* Custom Libraries */

#include"Motor.h"
#include"Vista.h"

/* Motor.c -- Functions */

/**
*This function validates file by opening and closing, if file can open it exist.If not exit program.
*
*@param
*   (char *)fileName: array with the name file to open.
*
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void valFile(char *fileName)
{
    FILE *fp;
    fp=fopen(fileName,"r");
    if(fp==NULL)
    {
        printf("File \"%s\" doesnt exist.",fileName);
        exit(1);
    }
    fclose(fp);
}

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
/*------------------------------------------------------------------------------------------*/
/*Based on GeekForGeeks updated on 04/06/2020 by Avinashavi0941
https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
#:~:text=rand()%20function%20is%20used,again%20every%20time%20program%20runs.
*/
void randomUserNumbers(float **ptr,int *users,int *stats)
{
    int i,j,numi;
    float numf;
    srand(time(0));
    for(i=0;i<(*users);i++)
    {
        for(j=0;j<(*stats);j++)
        {
            numi=rand()%999;
            numf=numi/1000.0;
            ptr[i][j]=numf;
        }
    }
}

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
/*------------------------------------------------------------------------------------------*/
void readFile(char fileName[],char ***ptr,int *row,int *column)
{
    /*Variables*/

    char c;
    int i=0,j=0,size=0;
    FILE *file;
    (*row)=0;
    
    /*Procces*/

    file=fopen(fileName,"r");
    if(file==NULL)
    {
        printf("File couldnt be opened.\n");
        exit(0);
    }
    while((c = getc(file)) != EOF)
    {
        if(c=='\n')
        {
            (*row)++;    
        } 
    }
    if((*row)==0)
    {
        printf("Rows = cero");
        fclose(file);
        exit(0);
    }
    (*ptr)=malloc((*row)*(sizeof(char *)));
    rewind(file);
    for(i=0;i<(*row);i++)
    {  
        (*column)=1;
        while((c = getc(file)) != '\n')
        {
            if(c==',')
            {
                (*column)++;
            }
            size++;
        }
        (*ptr)[i]=malloc(size+2);
        rewind(file);
        for(j=0;j<=i;j++)
        {
            __fpurge(stdin);
            fgets((*ptr)[i],size,file);
        }
        
    }
    strcat((*ptr)[0],"\n");
    if((*row)>1)
    {
        rewind(file);
        fgets((*ptr)[1],size,file);
        fgets((*ptr)[1],size,file); 
    }
    /*for(i=0;i<(*row);i++)
    {
        printf("%s",(*ptr)[i]);
    }*/ //just for visualization purpose
    fclose(file);
}

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
/*------------------------------------------------------------------------------------------*/
float my_dot_product(float * vector_1, float * vector_2, int v_size)
{ 
    float dot_prod=0;
    int n;
    for (n = 0 ; n<v_size; n++)
    {
        dot_prod += vector_1[n] * vector_2[n];
    }
    return dot_prod;
}

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
/*------------------------------------------------------------------------------------------*/
void training(float ***ptr,float ***ptr2,float ***ptr3,int *users,int *stats,int *movies)
{
    int cant,ciclo,u,m,s;
    float multi,cont=0,x,y,rui,e,cantError=0;
    double errorEpoc=0,error;
    float nVar=0.0005;//Modify
    cant=askEpocs();
    for(ciclo=0;ciclo<cant;ciclo++)//Cycle to repeat training, depends on input.
    {
        for(u=0;u<(*users);u++)//goes from user 0 to max user
        {
            for(m=0;m<(*movies);m++)//for every user goes to each movie
            {
                if((*ptr3)[u][m]!=0)//validate if movie has been seen
                {
                    
                    /*for(s=0;s<(*stats);s++)//for each movie does dot product.
                    {
                        x=(*ptr)[u][s];
                        y=(*ptr2)[s][m];
                        multi=x*y;
                        cont+=multi;
                    }*/
                    cont= my_dot_product((*ptr)[u],(*ptr2)[m],(*stats));//Dot Product
                    rui=(*ptr3)[u][m];
                    error=rui-cont;
                    //printf("error: %f\n",error);
                    for(s=0;s<(*stats);s++)
                    {
                        (*ptr)[u][s]=((*ptr)[u][s])+(nVar*error*((*ptr2)[s][m]));
                        (*ptr2)[s][m]=((*ptr2)[s][m])+(nVar/10.0)*error*((*ptr)[u][s]);
                    }
                    cantError++;
                    errorEpoc+=error;  
                    cont=0;
                }  
            }
        }
        //printf("Error Epoc %d: %f\n",ciclo+1,errorEpoc/cantError);
        e=errorEpoc/cantError;

        /*  Filling file with values for later Graphic  */
        appendError(e,ciclo);

        errorEpoc=0;
        cantError=0;
    }
}

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
/*------------------------------------------------------------------------------------------*/
void newReco(float ***ptr,float ***ptr2,float ***ptr3,int *users,int *stats,int *movies)
{   
    int moviesID[3];
    int ID,i,j,x;
    float z,y,multi,cont,temp;
    for(i=0;i<3;i++)
    {
        moviesID[i]=-1;
    }
    do
    {
        printf("=======================================\n");
        printf("=        Movies Recomendations        =\n");
        ID=askID(1,(*users));
        for(j=0;j<(*movies);j++)
        {
            if((*ptr3)[ID][j]==0)//Validate if movie hasnt been seen
            {
                cont=my_dot_product((*ptr)[ID],(*ptr2)[j],(*stats));//Dot Product
                if(cont>8)
                {
                    for(i=0;i<3;i++)//List of 3 movies to recommend
                    {
                        if(cont>moviesID[i])
                        {
                            temp=moviesID[i];
                            moviesID[i]=cont;
                            if(j==0)
                            {
                                cont=temp;
                                temp=moviesID[j+1];
                                moviesID[j+1]=cont;
                                cont=temp;
                                temp=moviesID[j+2];
                                moviesID[j+2]=cont;
                            }
                            if(j==1)
                            {
                                cont=temp;
                                temp=moviesID[j+1];
                                moviesID[j+1]=cont;
                            }
                        }
                    }
                }
            }
            
        }
        p_Movies(moviesID);
        do
        {
            printf("Want to look for another User Recommendations?\n1)Yes 2)No\n");
            printf("Option: ");
            scanf("%d",&x);
        }while(x!=1 && x!=2);
    }while(x==1);
}

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
/*------------------------------------------------------------------------------------------*/
void simFriends(float ***ptr,int *users, int *stats)
{
    int usersID[3];
    int ID,i,j,x;
    float cont,temp;
    for(i=0;i<3;i++)
    {
        usersID[i]=-1;
    }
    do
    {
        printf("========================================\n");
        printf("=        Friends Recomendations        =\n");
        ID=askID(1,(*users));

        for(i=0;i<(*users);i++)
        {
            if(i!=ID)
            {
                cont=my_dot_product((*ptr)[ID],(*ptr)[i],(*stats));//Dot Product
                if(cont>8)
                {
                    for(j=0;j<3;j++)//List of 3 movies to recommend
                    {
                        if(cont>usersID[j])
                        {
                            temp=usersID[j];
                            usersID[j]=cont;
                            if(j==0)
                            {
                                cont=temp;
                                temp=usersID[j+1];
                                usersID[j+1]=cont;
                                cont=temp;
                                temp=usersID[j+2];
                                usersID[j+2]=cont;
                            }
                            if(j==1)
                            {
                                cont=temp;
                                temp=usersID[j+1];
                                usersID[j+1]=cont;
                            }
                        }
                    }  
                } 
            }  
        }
        p_Friends(usersID);
        do
        {
            printf("Want to look for another Friends Recommendations?\n1)Yes 2)No\n");
            printf("Option: ");
            scanf("%d",&x);
        }while(x!=1 && x!=2);
    }while(x==1);
}

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
/*------------------------------------------------------------------------------------------*/
void simMovie(float ***ptr,int *movies,int *stats)
{
    int moviesID[3];
    int ID,i,x,j,temp;
    float cont;
    for(i=0;i<3;i++)
    {
        moviesID[i]=-1;
    }
    do
    {
        printf("========================================\n");
        printf("=            Similar Movies            =\n");
        ID=askID(2,(*movies));
        
        for(i=0;i<(*movies);i++)
        {
            if(i!=ID)
            {
                cont=my_dot_product((*ptr)[ID],(*ptr)[i],(*stats));//Dot Product
                if(cont>8)
                {
                    for(j=0;j<3;j++)//List of 3 movies to recommend
                    {
                        if(cont>moviesID[j])
                        {
                            temp=moviesID[j];
                            moviesID[j]=cont;
                            if(j==0)
                            {
                                cont=temp;
                                temp=moviesID[j+1];
                                moviesID[j+1]=cont;
                                cont=temp;
                                temp=moviesID[j+2];
                                moviesID[j+2]=cont;
                            }
                            if(j==1)
                            {
                                cont=temp;
                                temp=moviesID[j+1];
                                moviesID[j+1]=cont;
                            }
                        }
                    }  
                } 
            }  
        }
        p_Movies(moviesID);
        do
        {
            printf("Want to look for more Similar Movies Recommendations?\n1)Yes 2)No\n");
            printf("Option: ");
            scanf("%d",&x);
        }while(x!=1 && x!=2);
    }while(x==1);
}

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
/*------------------------------------------------------------------------------------------*/
void save(char *fileName,float ***ptr,int *row, int *column)
{
    int i,j;
    FILE *fp;
    fp=fopen(fileName,"w");
    if(fp==NULL)
    {
        printf("File couldnt be created.\n");
        return;
    }
    for(i=0;i<(*row);i++)
    {
        for(j=0;j<(*column);j++)
        {
            if(j>0)
            {
                fprintf(fp,",");
            }
            fprintf(fp,"%f",(*ptr)[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

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
/*------------------------------------------------------------------------------------------*/
void format(char **ptr,float ***ptr2,int *row,int *column)
{
    int i=0,j=0;
    float a;
    char s[2]=",";
    char *token, *temp;
    (*ptr2)=malloc((*row)*sizeof(float *));
    for(i=0;i<(*row);i++)
    {
        (*ptr2)[i]=malloc((*column)*sizeof(float));
    }
    i=0;
    for(j=0;j<(*row);j++)
    {
        for(token=strtok_r(ptr[j],s,&temp);token;token=strtok_r(NULL,s,&temp))
        {
            a=atof(token);
            //printf("Valor de token: %s\n",token);//visualizar valores
            //printf("Valor de a: %f\n\n",a);
            (*ptr2)[j][i]=a;
            i++;
        }
        i=0;
    }
    /*
    printf("-------------------\n");
    for(i=0;i<(*row);i++)
    {
        for(j=0;j<(*column);j++)
        {
            printf("%f",(*ptr2)[i][j]);
        } 
        printf("\n");
    }
    printf("-------------------\n");*/ //just for visualization purpose
}

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
/*------------------------------------------------------------------------------------------*/
void liberar(float ***ptr,int *row, int *column)
{
    int j,i;
    for(j=(*row);j>=0;--j)
    {
        //free((*ptr)[j]);
        /*for(i=(*column);i>=0;--i)
        {
            free(ptr[j][i]);
        }*/
    }
    free((*ptr));
}

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
void appendError(float e, int n)
{
    FILE *fp;
    if(n==0)
    {
       fp=fopen("Graphic.dat","w"); 
    }
    else
    {
        fp=fopen("Graphic.dat","a");
    }
    fprintf(fp,"%d, %f\n",n,e);
    fclose(fp);
}

/**
*This function will call gnuplot, and open file with values.
*
*@param
*   
*@returns
*
*/
/*------------------------------------------------------------------------------------------*/
void openGnu()
{
    FILE *gnu_socket;
    char *nombre="Graphic.dat";
    gnu_socket=popen("gnuplot -persist","w");
    fprintf(gnu_socket,"plot \"%s\" using 1:2 with lines\n",nombre);/*Command for calling gnuplot internally*/
    pclose(gnu_socket);
}