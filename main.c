#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
    char * f_name;
    char * l_name;
    unsigned int length_f_name;
    unsigned int length_l_name;
};

struct personRead{
    char * rf_name;
    char * rl_name;
    unsigned int length_rf_name;
    unsigned int length_rl_name;
};

int main()
{
    char temp[128];
    struct person one;

    printf("Please provide your first name\n");
    scanf("%s",temp);
    one.length_f_name = strlen(temp) + 1;
    one.f_name = (char*)malloc(sizeof(char)*one.length_f_name);
    strcpy(one.f_name , temp);

    printf("Please provide your last name\n");
    scanf("%s",temp);
    one.length_l_name = strlen(temp) + 1;
    one.l_name = (char*)malloc(sizeof(char)*one.length_l_name);
    strcpy(one.l_name , temp);

    char * buffer = (char*) malloc( 2*sizeof(int) + one.length_l_name + one.length_f_name );
    char * backup = buffer;

    memcpy(buffer , &one.length_f_name , sizeof(int) );
    buffer+=sizeof(int);

    memcpy(buffer , &one.length_l_name , sizeof(int));
    buffer+=sizeof(int);

    memcpy(buffer , one.f_name , one.length_f_name );
    buffer+=one.length_f_name ;

    memcpy(buffer , one.l_name , one.length_l_name );
    buffer+=one.length_l_name ;

    buffer = backup;

    FILE * MyFile = fopen("test.txt","w");
    if(!MyFile){
        printf("Error\n");
        return 0;
    }
    fwrite( buffer, 2*sizeof(int)+one.length_f_name+one.length_l_name  ,  1  , MyFile);

    if(one.l_name) free(one.l_name);
    if(one.f_name) free(one.f_name);
    if(MyFile) fclose(MyFile);

    //----------- Read from file

    FILE * readFile = fopen("test.txt","r");
    if(!readFile){
        printf("Error\n");
        return 0;
    }
    struct personRead two;

    fread( &two.length_rf_name , sizeof(int)  ,  1 , readFile );
    fread( &two.length_rl_name , sizeof(int)  ,  1 , readFile );

    two.rf_name = (char*)malloc(sizeof(char) * one.length_f_name);
    fread( two.rf_name , one.length_f_name , 1 , readFile );

    two.rl_name = (char*)malloc(sizeof(char) * one.length_l_name);
    fread( two.rl_name , one.length_l_name , 1 , readFile );

    printf("\n\ntwo.rf_name is %s\n" , two.rf_name);
    printf("two.rl_name is %s\n" , two.rl_name);
    printf("two.length_rf_name is %d\n" , two.length_rf_name);
    printf("two.length_rl_name is %d\n" , two.length_rl_name);

    if(readFile) close(readFile);
    if(two.rf_name) free (two.rf_name);
    if(two.rl_name) free (two.rl_name);

    return 0;
}
