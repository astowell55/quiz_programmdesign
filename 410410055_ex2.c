#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 200
#define ARTICLE_MAX 5000
#ifndef DEBUG
#define DEBUG 1
#endif
#define info_islegal(info) \
    if(strcmp(info,"-i") != 0){ \
        printf("The input format: string1 string2 [parameter]\n");\
        exit(0);\
        }
#define num_islegal(n) \
    if(n != 2 && n != 3){ \
        printf("The input format: string1 string2 [parameter]\n"); \
        exit(0); \
    }
#define strlower(str, i)          \
    for (; i < strlen(str);i++) { \
        str[i] = tolower(str[i]); \
    } \
    
    
//the function to check the if parameter is "-i"
/*
void islegal(char *info){
    if(strcmp(info,"-i")){
        printf("The input format: string1 string2 [parameter]\n");
        exit(0);
    }
    return;
}
*/
//the fuctoin to read line, return false when entering EOF
bool readline(char *str){
    char c;
    int i = 0;
    while((c = getchar())!='\n'&&c!=EOF){
        str[i] = c;
        i++;
    }
    if(c == EOF){
        return false;
    }
    str[i] = '\0';
    return true;
}
//the fuctoin to replace tab
/*
void replacespace(char *str){
    for (int i = 0; i < strlen(str) ;i++){
        if (str[i] == '\t'){
            str[i] = ' ';
        }
    }
    return;
}
*/
//the functoin use to read first line of formate
void readinfo(char str1[MAX],char str2[MAX],char info[MAX]){
    char line[MAX*3];
    char *temp[3];
    temp[0] = NULL;
    char *token;
    char *delim = " \t\v\b\r\n~`!@#$%%^&*()_=+{}[]<>,.?/:;\"\'|\\";
    int i = 0;
    fgets(line,ARTICLE_MAX, stdin);
    //replacespace(line);
    token = strtok(line, delim);
    while(token != NULL){
        //store every token in temp array
        temp[i] = token;
        token = strtok(NULL, delim);
        //count the token number
        i++;
    }
    if(temp[0] != NULL){
        strcpy(str1, temp[0]);
    }
    //token number wrong
    num_islegal(i);
    if(i == 3){
        strcpy(str2, temp[1]);
        strcpy(info, temp[2]);
        info_islegal(info);
    #if DEBUG
        printf("this is case 1\n");
    #endif
        return;
    }else if(i == 2){
        strcpy(str2, temp[1]);
    #if DEBUG
        printf("this is case 0\n");
    #endif
    }
    return;
}
//change a string into lowercase
/*
void strtolower(char *str){
    int i = 0;
    while(str[i]!='\0'){
        str[i] = tolower(str[i]);
        i++;
    }
    return;
}
*/

//replace punctuation
/*
void replacepunc(char *str){
    for (int i = 0; i < strlen(str) ;i++){
        if (str[i] == ',' || str[i] == '.' || str[i] == '!' || str[i] == '?' || str[i] == '\"' || str[i] == '\'' || str[i] == ':' || str[i] == '@' || str[i] == '#' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '&' || str[i] == '*' || str[i] == '(' || str[i] == ')' || str[i] == '_' || str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == ';' || str[i] == '<'||str[i] == '>'||str[i] == '{'||str[i] =='}'||str[i] == '['||str[i] ==']'||str[i] == '~'||str[i] == '`')
        {
            str[i] = ' ';
        }
    }
    return;
}
*/
//replace the original char into target and print out
void replacechar(char front[MAX],char ostr[MAX],char rstr[MAX],char info[MAX]){
    char casetest[MAX];
    char lowerostr[MAX];
    int t = 0;
    strcpy(lowerostr, ostr);
    strcpy(casetest, front);
    if(strcmp(info,"-i")==0){ 
        //turn to lowercase first to compare
        strlower(casetest,t);
        t = 0;
        strlower(lowerostr,t);
        t = 0;
    }
    char *ptest = strstr(casetest, lowerostr);
    //count the distant between casetest[0] with target string
    int locat = ptest - casetest;
    if(ptest != NULL){
        front[locat] = '\0';
        //print the front(the rear part), rstr(the middle),front + locate + strlen(ostr)(the rear)
        printf("%s%s%s\n", front, rstr, front + locat + strlen(ostr));
    }
    return;
}
//read the article
void readArticle(char ostr[MAX],char rstr[MAX],char info[MAX]){
    char first[ARTICLE_MAX];
    char *token;
    char *delim = " \t\v\b\r\n~`!@#$%%^&*()_=+{}[]<>,.?/:;\"\'|\\";
    //end when read EOF
    while(readline(first)){
        //replacepunc(first);
        //replacespace(first);
        token = strtok(first, delim);
        while(token != NULL){
        #if DEBUG
            printf("the word is: %s\n", token);
        #endif
            replacechar(token, ostr, rstr, info);
            token = strtok(NULL, delim);
        }
    }
    return;
}
int main(){
    char ostr[MAX];//the string 1
    char rstr[MAX];//the string 2
    char info[MAX];//the parameter
    readinfo(ostr, rstr, info);//process the formate
    readArticle(ostr, rstr,info);//process th article
    return 0;
}
