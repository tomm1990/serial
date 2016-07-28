#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
    char * f_name;
    char * l_name;
    unsigned int length_f_name;
    unsigned int length_l_name;
};

int main(){
    char temp[128];
    struct person one;

    // input first name
    printf("Please provide your first name\n");
    scanf("%s",temp);
    one.length_f_name = strlen(temp) + 1;
    one.f_name = (char*)malloc(sizeof(char)*one.length_f_name);
    strcpy(one.f_name , temp);

    // input last name
    printf("Please provide your last name\n");
    scanf("%s",temp);
    one.length_l_name = strlen(temp) + 1;
    one.l_name = (char*)malloc(sizeof(char)*one.length_l_name);
    strcpy(one.l_name , temp);

    char * buffer = (char*) malloc( 2*sizeof(int) + one.length_l_name + one.length_f_name );
    char * backup = buffer;

    memcpy( buffer , &one.length_f_name , sizeof(int) );
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



    //----------- Read from file ---------------///

    struct person two;

    FILE * readFile = fopen("test.txt","r");
    if(!readFile){
        printf("Error\n");
        return 0;
    }

    fread( &two.length_f_name , sizeof(int)  ,  1 , readFile );
    fread( &two.length_l_name , sizeof(int)  ,  1 , readFile );

    two.f_name = (char*)malloc(sizeof(char) * one.length_f_name);
    fread( two.f_name , one.length_f_name , 1 , readFile );

    two.l_name = (char*)malloc(sizeof(char) * one.length_l_name);
    fread( two.l_name , one.length_l_name , 1 , readFile );

    printf("\n\ntwo.f_name is %s\n" , two.f_name);
    printf("two.l_name is %s\n" , two.l_name);
    printf("two.length_f_name is %d\n" , two.length_f_name);
    printf("two.length_l_name is %d\n" , two.length_l_name);

    if(readFile) close(readFile);
    if(two.f_name) free (two.f_name);
    if(two.l_name) free (two.l_name);

    remove("test.txt");

    return 0;
}
