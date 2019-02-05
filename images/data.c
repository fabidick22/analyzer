#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#include <assert.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//DELIMITADORES
char *variable_deli_keywords="<>=+-*/;( =):,\"";
char *operator_logicos_keywords="<>=";
char *operator_aritmetica_keywords="+-*/";
char keywordsRevers[13][12] = {"RETORNO", "INICIO", "FIN", "FUNCION", "IMPRIMIR", "RECOGER",
                               "BOOLEAN", "CADENA", "SINO", "HASTA", "SI", "ENTERO",
                               "PARA"};
//DELIMITADORES

int keyword_library(char temp[]);
int keyword_deli(char temp);
int variable_deli(char temp);
int automataIdenReser(char *temp);
int idenAritmetic(char temp[]); // para la identificación aritmetica
int idenOperator(char temp[]); //identifica cada operador logico
int operator_aritmetica(char temp);
int operator_logicos(char temp);
int operador_deli(char temp);
int operador_deliLogico(char temp);
int operador_deli_openClose(char temp, char  automa);
char bufferW[100];
int numWorldRes=0;
int numWorldOperL=0;
int numWorldOperA=0;
int identificadores=0;
int numerTotal=0;
int numError=0;
char charError[1000];
int lineError=1;

int banner(){
    printf("\n");
    printf("\n");
    printf(ANSI_COLOR_GREEN "\t █████╗ ███╗   ██╗ █████╗ ██╗  ██╗   ██╗███████╗███████╗██████╗ \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "\t██╔══██╗████╗  ██║██╔══██╗██║  ╚██╗ ██╔╝╚══███╔╝██╔════╝██╔══██╗\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "\t███████║██╔██╗ ██║███████║██║   ╚████╔╝   ███╔╝ █████╗  ██████╔╝\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "\t██╔══██║██║╚██╗██║██╔══██║██║    ╚██╔╝   ███╔╝  ██╔══╝  ██╔══██╗\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "\t██║  ██║██║ ╚████║██║  ██║███████╗██║   ███████╗███████╗██║  ██║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "\t╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝   ╚══════╝╚══════╝╚═╝  ╚═╝\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RED "\t\t\tby: Michael & Dickson"ANSI_COLOR_RESET "\n\n\n");
}

int analizerFile(char *dirFile){
    FILE *file_pointer;

    file_pointer = fopen(dirFile,"r");
    if(file_pointer == NULL) {
        printf("El archivo no pudo ser abierto.\n");
        exit(0);
    } else{
        automataIdenReser(dirFile);
    }
    //getch();
    return 0;
}

char * quitDeli(char temp[]){
    int s, i, con=0;
    s=strlen(temp);
    char copyTemp[s];
    for(i=0; i<s; i++){
        copyTemp[i]=*temp;
        if(isalpha(*temp)){
            temp++;
        } else{
            con++;
        }
    }
    s=s-con;
    //char a[s];
    //int* a = malloc(sizeof(int) * s);
    char* a = (char *) malloc(sizeof(int) * s);
    strncpy(a, copyTemp, s);
    return a;
}

int fun(){
    FILE* archivo = fopen("/home/exploit/Documentos/archivo.txt","r");
    char * buffer = NULL;
    int i, c;
    c = fgetc(archivo);
    while(!feof(archivo))
    {
        buffer = (char*)realloc(NULL, sizeof(char));
        i = 0;
        while( c != '\n') {
            char a=c;
            buffer[i] = c;
            i++;
            buffer = (char*)realloc(buffer, (i+1)*sizeof(char));
            c = fgetc(archivo);
        }
        /*Agrego el \n al buffer*/
        buffer = (char*)realloc(buffer, (i+2)*sizeof(char));
        buffer[i] = c;
        buffer[i+1] = 0;
        /*Trabajar con el buffer*/
        printf("%s", buffer);
        free(buffer);
        c = fgetc(archivo);
    }
    fclose(archivo);
}

int automataIdenReser(char *dirFile){
    FILE* archivo = fopen(dirFile,"r");
    char * buffer = NULL;
    int i, c;
    char temporalChar;
    c = fgetc(archivo);



    char puntero;
    int estado = 0, bandera;
    char token = 0;
    while(!feof(archivo)) {
        buffer = (char*)realloc(NULL, sizeof(char));
        i = 0;
        while( c != '\n') {
            puntero=c;
            if(bandera==1){
                free(buffer);
                i=0;
                buffer = (char*)realloc(NULL, sizeof(char));
                bandera=0;
            }
            switch (estado) {
                case 0:
                    if (isalpha(puntero) && islower(puntero)) {
                        estado = 1;
                        token = 1;
                        //c = fgetc(archivo);
                    } else if (isalpha(puntero) && isupper(puntero)) {
                        estado = 4;

                    } else if(isalnum(puntero)){
                        temporalChar=puntero;
                        estado=8;
                        c = fgetc(archivo);

                    }else if(operator_aritmetica(puntero)){
                        temporalChar=puntero;
                        estado=6;
                        c = fgetc(archivo);

                    } else if(puntero=='\t'){
                        estado=0;
                        c = fgetc(archivo);

                    }else if(operator_logicos(puntero)){
                        temporalChar=puntero;
                        estado=7;
                        c = fgetc(archivo);

                    }else if(puntero=='('){
                        temporalChar=puntero;
                        estado=9;
                        c = fgetc(archivo);

                    }else if(puntero==')'){
                        temporalChar=puntero;
                        estado=10;
                        c = fgetc(archivo);

                    } else if(puntero==';'){
                        estado=0;
                        c = fgetc(archivo);

                    }else {
                        estado = 0;
                        token = 0;
                        c = fgetc(archivo);
                    }

                    break;

                case 1: //del 1 al 2 para delimitadores
                    if (isalpha(puntero) || isdigit(puntero)) {
                        buffer[i] = c;
                        i++;
                        buffer = (char*)realloc(buffer, (i+1)*sizeof(char));

                        estado = 1;
                        token = 1;
                        c = fgetc(archivo);
                    } else {
                        estado = 2;
                        token = 0;
                    }
                    break;

                case 2:
                    //este if es para cuando dos variables estan unidas, si no esta este if se salta los delimitadores
                    if (isalpha(puntero) || isdigit(puntero)) {
                        c = fgetc(archivo);
                    }
                    if (variable_deli(puntero)) {
                        printf(buffer);

                        printf("\nToken: 3\n");
                        token = 3;
                        identificadores++;

                        buffer = (char*)realloc(buffer, (i+2)*sizeof(char));
                        buffer[i] = c;
                        buffer[i+1] = 0;
                        //free(buffer);
                        bandera=1;
                        estado=0;
                    } else {
                        estado = 0;
                        token = -1;
                        printf(ANSI_COLOR_RED "Error en la línea %d: %s se he encontrado un error.\n" ANSI_COLOR_RESET, lineError, buffer);
                        numError=numError+1;
                        c = fgetc(archivo);

                    }

                    break;

                case 3:
                    if (isalpha(puntero) || isdigit(puntero)) {
                        estado = 3;
                        token = 1;
                    } else {
                        estado = 100;
                        token = 0;
                    }
                    c = fgetc(archivo);
                    break;
                case 4: // desde el 4 al 5 para palabras reservadas
                    if (isupper(puntero)) {
                        estado = 4;
                        if(isupper(puntero)){
                            buffer[i] = c;
                            i++;
                            buffer = (char*)realloc(buffer, (i+1)*sizeof(char));
//                            bufferW[conForBuff++];
                        }
                        c = fgetc(archivo);
//                }else if(puntero==';'){
                    } else {
                        estado = 5;
                    }
                    break;
                case 5:
                    if (keyword_deli(puntero)) {
                        if (keyword_library(buffer)){
                            printf(buffer);
                            printf("\nToken: 1\n\n");
                            //free(buffer);
                            token = 1;


                            buffer = (char*)realloc(buffer, (i+2)*sizeof(char));
                            buffer[i] = c;
                            buffer[i+1] = 0;
                            bandera=1;
                            //free(buffer);
                            estado=0;
                        }else{
                            token=-1;
                            printf(ANSI_COLOR_RED "Error en la línea %d: %s No es palabra reservada.\n" ANSI_COLOR_RESET, lineError, buffer);
                            numError=numError+1;
                            estado=0;

                        }
                        //c = fgetc(archivo);
                    } else {
                        token = -1;

                        c = fgetc(archivo);
                    }
                    break;
                case 6: //automara para aritmeticos
                    if (operador_deli(puntero)) {
                        printf("%c",temporalChar);
                        printf("\nToken: 10\n\n");
                        token=10;
                        estado=0;
                        //c = fgetc(archivo);
                    } else {
                        token = -1;
                        c = fgetc(archivo);
                        printf(ANSI_COLOR_RED "Error en la línea %d : %s verifique su operador aritmetico.\n" ANSI_COLOR_RESET,lineError, buffer);
                        numError=numError+1;
                    }
                    break;
                case 7: //automata para logicos
                    if (operador_deliLogico(puntero)) {
                        printf("%c",temporalChar);
                        printf("\nToken: 11\n\n");
                        token=11;
                        estado=0;
                        //c = fgetc(archivo);
                    } else {
                        token = -1;
                        c = fgetc(archivo);
                        printf(ANSI_COLOR_RED "Error en la linea %d: mal escrito en el operador logico %s.\n" ANSI_COLOR_RESET, lineError, buffer);
                        numError=numError+1;
                    }
                    break;
                case 8: //automata para numeros
                    if (isdigit(puntero)){
                        estado=8;
                    }
                    else if (variable_deli(puntero)) {
                        printf("%c",temporalChar);
                        printf("\nToken: 4\n\n");
                        token=4;
                        estado=0;
                        numerTotal++;
                        //c = fgetc(archivo);
                    } else {
                        token = -1;
                        printf(ANSI_COLOR_RED "Error linea %d: en la declaracion, verifique la expresion %s.\n" ANSI_COLOR_RESET, lineError, buffer);
                        numError=numError+1;
                        c = fgetc(archivo);
                    }
                    break;
                case 9: //automata para abrir "("
                    if (operador_deli_openClose(puntero, '(')) {
                        printf("%c",temporalChar);
                        printf("\nToken: 14\n\n");
                        token=14;
                        estado=0;
                        //c = fgetc(archivo);
                    } else {
                        token = -1;
                        printf(ANSI_COLOR_RED "Error linea %d verifique la expresión.\n" ANSI_COLOR_RESET, lineError,buffer);
                        numError=numError+1;
                        c = fgetc(archivo);
                    }
                    break;
                case 10: //automata para abrir ")"
                    if (operador_deli_openClose(puntero, ')')) {
                        printf("%c",temporalChar);
                        printf("\nToken: 15\n\n");
                        token=11;
                        estado=0;
                        //c = fgetc(archivo);
                    } else {
                        token = -1;
                        c = fgetc(archivo);
                    }
                    break;
                default:
                    token = 0;
                    c = fgetc(archivo);
                    break;

            }

        }
        lineError=lineError+1;
        c = fgetc(archivo);
//        switch (token) {
//            case 0:
//                printf("No es identificador\n");
//                c = fgetc(archivo);
//                break;
//            case 1:
//                printf("Es Palabra Reservada\n\n");
//                c = fgetc(archivo);
//                break;
//            case 2:
//                printf("Es Palabra Reservada\n");
//                c = fgetc(archivo);
//                break;
//            case 4:
//                printf("Es Numero\n");
//                c = fgetc(archivo);
//                break;
//            case 96:
//                printf("Reservad\n");
//                c = fgetc(archivo);
//                break;
//            default:
//                printf("Error:\n");
//                break;
//        }

    }

}

int keyword_library(char temp[]) {
    char *quitTemp;
    quitTemp=quitDeli(temp);
    int count = 0, flag = 0;
    char keywords[13][12] = {"RETORNO", "INICIO", "FIN", "FUNCION", "IMPRIMIR", "RECOGER",
                             "BOOLEAN", "CADENA", "SINO", "HASTA", "SI", "ENTERO",
                             "PARA"};

    while(count <= 12) {
        if(strcmp(keywords[count], quitTemp) == 0) {
            flag = 1;// entra es palabra reservada
            numWorldRes++;
            break;
        }
        count = count + 1;
    }
    return (flag);
}



int keyword_deli(char temp) {
    char a[1];
    a[1]=temp;
    int count = 0, flag = 0;
    if(isalpha(temp) && isupper(temp)){
        flag=1;
    }else{
        //char keywords[3][1] = {";","("," "};
        char *keywords=";( {}";

        for (int i = 0; i < 5; ++i) {
            if(*keywords== temp) {
                flag = 1;
                //numWorldOperA++;
                break;
            }
            keywords++;
        }
    }
    return (flag);
}

int operador_deli(char temp) {
    char a[1];
    a[1]=temp;
    int count = 0, flag = 0;
    if(isalpha(temp) || isdigit(temp)){
        flag=1;
    }else{
        char keywords[1][1] = {" "};

        while(count <= 1) {
            if(strcmp(keywords[count], a) == 0) {
                flag = 1;
                break;
            }
            count = count + 1;
        }
    }
    return (flag);
}
int operador_deli_openClose(char temp, char automa) {
    char a[1];
    a[1]=temp;
    int count = 0, flag = 0;
    char *keywords="";
    if(automa=='('){
        if(isalpha(temp) || isalnum(temp)){
            flag=1;
        }
        keywords="\" ";
    }else if(automa==')'){
        if(isalpha(temp) || isalnum(temp)){
            flag=0;
        }
        keywords="{ ;";
    }

    for (int i = 0; i < 2; ++i) {
        if(*keywords== temp) {
            flag = 1;
            //numWorldOperA++;
            break;
        }
        keywords++;
    }
    return (flag);
}

int operador_deliLogico(char temp) {
    char a[1];     a[1]=temp;
    int count = 0, flag = 0;
    if(isalpha(temp) || isalnum(temp)){
        flag=1;
    }else{
        //char keywords[1][1] = {" ","="};
        char *keywords=" =";
        for (int i = 0; i < 2; ++i) {
            if(*keywords== temp) {
                flag = 1;
                //numWorldOperA++;
                break;
            }             keywords++;
        }
    }
    return (flag);
}

int operator_aritmetica(char temp) {
    int  flag = 0;
    char *keywords=operator_aritmetica_keywords;

    for (int i = 0; i < 4; ++i) {
        if(*keywords== temp) {
            flag = 1;
            numWorldOperA++;
            break;
        }
        keywords++;
    }

    return (flag);
}

int operator_logicos(char temp) {
    char a[1];
    a[1]=temp;
    int count = 0, flag = 0;
    if(isalpha(temp) && isupper(temp)){
        flag=1;
    }else{
        char *keywords=operator_logicos_keywords;

        for (int i = 0; i < 3; ++i) {
            if(*keywords== temp) {
                flag = 1;
                numWorldOperL++;
                break;
            }
            keywords++;
        }
    }
    return (flag);
}

int variable_deli(char temp) {
    char a[1];
    a[1]=temp;
    int count = 0, flag = 0;

    //char keywords[12][1] = {"<", ">", "=","+", "-", "*", "/", ";", "(", " ", "=", ")", ":" };
    char *keywords=variable_deli_keywords;

    for (int i = 0; i < 15; ++i) {
        if(*keywords== temp) {
            flag = 1;
            //numWorldOperA++;
            break;
        }
        keywords++;
    }

    return (flag);
}

int isWorldR(int numero) {
    int count = 0, flag = 0;

    return (flag);
}

int resultadosFinales(){
    printf(ANSI_COLOR_BLUE "\n\n##################################\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\nTotal Palabras R.: %d\t" ANSI_COLOR_RESET,numWorldRes);
    printf(ANSI_COLOR_YELLOW "\nTotal Operadores A.: %d\t" ANSI_COLOR_RESET,numWorldOperA);
    printf(ANSI_COLOR_YELLOW "\nTotal Operadores L.: %d\t" ANSI_COLOR_RESET,numWorldOperL);
    printf(ANSI_COLOR_YELLOW "\nTotal Identificadores: %d\t" ANSI_COLOR_RESET,identificadores);
    printf(ANSI_COLOR_YELLOW "\nTotal Numeros: %d\t" ANSI_COLOR_RESET,numerTotal);
    printf(ANSI_COLOR_RED "\nTotal Errores: %d\t" ANSI_COLOR_RESET,numError);
    //printf(ANSI_COLOR_RED "\nUltma línea con error: %d\t" ANSI_COLOR_RESET,lineError);

    printf(ANSI_COLOR_BLUE "\n\n##################################" ANSI_COLOR_RESET);
}

int presentarDatos(){
    printf(ANSI_COLOR_YELLOW "\n\n\n\nDelimitadores para Identificadores.\n " ANSI_COLOR_RESET);
    printf("%s", variable_deli_keywords);
    printf(ANSI_COLOR_YELLOW "\n\nOperadores Logicos.\n %s" ANSI_COLOR_RESET);
    printf("%s", operator_logicos_keywords);
    printf(ANSI_COLOR_YELLOW "\n\nDelimitadores Aritmeticos.\n %s" ANSI_COLOR_RESET);
    printf("%s", operator_aritmetica_keywords);
    printf(ANSI_COLOR_YELLOW "\n\nPalabras Rervadas. "ANSI_COLOR_RESET);
    int count = 0, flag = 0;
    char keywords[13][12] = {"RETORNO", "INICIO", "FIN", "FUNCION", "IMPRIMIR", "RECOGER",
                             "BOOLEAN", "CADENA", "SINO", "HASTA", "SI", "ENTERO",
                             "PARA"};

    while(count <= 12) {
        printf("\n%s\n",keywords[count]);
        count = count + 1;
    }
}

int reglaCount(char numRegla){
    int tamanio=0;
    int altura=10;
    int anchura=10;
    const char *options[anchura][altura];
    options[0][0] = "1", options[0][1] = "E", options[0][2] = "E+T";
    options[1][0] = "2", options[1][1] = "E", options[1][2] = "T";
    options[2][0] = "3", options[2][1] = "T", options[2][2] = "T*F";
    options[3][0] = "4", options[3][1] = "T", options[3][2] = "F";
    options[4][0] = "5", options[4][1] = "F", options[4][2] = "(E)";
    options[5][0] = "6", options[5][1] = "F", options[5][2] = "i";

    for (int j = 0; j < altura; ++j) {
        char *columna=options[j][0];
        char valorN=*columna;
        if(valorN==numRegla){
            char *regla=options[j][2];
            tamanio= strlen(regla);
            break;
        }
    }

    if (tamanio==0){
        printf(ANSI_COLOR_YELLOW "\nRegla no encontrada" ANSI_COLOR_RESET);
        return tamanio;
    }else{
        return tamanio;
    }
}
char *getRulerA(char numRegla){
    char *A;
    int altura=10;
    int anchura=10;
    const char *options[anchura][altura];
    options[0][0] = "1", options[0][1] = "E", options[0][2] = "E+T";
    options[1][0] = "2", options[1][1] = "E", options[1][2] = "T";
    options[2][0] = "3", options[2][1] = "T", options[2][2] = "T*F";
    options[3][0] = "4", options[3][1] = "T", options[3][2] = "F";
    options[4][0] = "5", options[4][1] = "F", options[4][2] = "(E)";
    options[5][0] = "6", options[5][1] = "F", options[5][2] = "i";

    for (int j = 0; j < altura; ++j) {
        char *columna=options[j][0];
        char valorN=*columna;
        if(valorN==numRegla){
            A=options[j][1];
            break;
        }
    }

    if (A==' '){
        printf(ANSI_COLOR_YELLOW "\nRegla no encontrada" ANSI_COLOR_RESET);
        return NULL;
    }else{
        return *A;
    }
}

//a son simbolos
//s numero de fila
char *accion(char ss, char aa){
    int columanSimbolo=0;
    int filaNumero=0;
    int altura=22;
    int anchura=14;
    const char *options[anchura][altura];
    options[0][0] = "state", options[0][1] = "i", options[0][2] = "+", options[0][3] = "*",options[0][4] = "(",options[0][5] = ")",options[0][6] = "$";
    options[1][0] = "0", options[1][1] = "d5", options[1][2] = "", options[1][3] = "",options[1][4] = "d4",options[1][5] = "",options[1][6] = "";
    options[2][0] = "1", options[2][1] = "", options[2][2] = "d6", options[2][3] = "",options[2][4] = "",options[2][5] = "",options[2][6] = "acc";
    options[3][0] = "2", options[3][1] = "", options[3][2] = "r2", options[3][3] = "d7",options[3][4] = "",options[3][5] = "r2",options[3][6] = "r2";
    options[4][0] = "3", options[4][1] = "", options[4][2] = "r4", options[4][3] = "r4",options[4][4] = "",options[4][5] = "r4",options[4][6] = "r4";
    options[5][0] = "4", options[5][1] = "d5", options[5][2] = "", options[5][3] = "",options[5][4] = "d4",options[5][5] = "",options[5][6] = "";
    options[6][0] = "5", options[6][1] = "", options[6][2] = "r6", options[6][3] = "r6",options[6][4] = "",options[6][5] = "r6",options[6][6] = "r6";
    options[7][0] = "6", options[7][1] = "d5", options[7][2] = "", options[7][3] = "",options[7][4] = "d4",options[7][5] = "",options[7][6] = "";
    options[8][0] = "7", options[8][1] = "d5", options[8][2] = "", options[8][3] = "",options[8][4] = "d4",options[8][5] = "",options[8][6] = "";
    options[9][0] = "8", options[9][1] = "", options[9][2] = "d6", options[9][3] = "",options[9][4] = "",options[9][5] = "d11",options[9][6] = "";
    options[10][0] = "9", options[10][1] = "", options[10][2] = "r1", options[10][3] = "d7",options[10][4] = "",options[10][5] = "r1",options[10][6] = "r1";
    options[11][0] = "10", options[11][1] = "", options[11][2] = "r3", options[11][3] = "r3",options[11][4] = "",options[11][5] = "r3",options[11][6] = "r3";
    options[12][0] = "11", options[12][1] = "", options[12][2] = "r5", options[12][3] = "r5",options[12][4] = "",options[12][5] = "r5",options[12][6] = "r5";

    for (int i = 0; i < anchura; ++i) {
        char *columna=options[0][i];
        char valorM=*columna;
        if(valorM==aa){
            columanSimbolo=i;
            break;
        }
        if(i>=anchura){
            columanSimbolo=0;
            break;
        }
    }
    for (int j = 0; j < altura; ++j) {
        char *columna=options[j][0];
        char valorN=*columna;
        if(valorN==ss){
            filaNumero=j;
            break;
        }
        if(j>=altura){
            columanSimbolo=0;
            break;
        }
    }
    if (columanSimbolo==0 || filaNumero==0){
        printf(ANSI_COLOR_YELLOW "\nError accion no encontrada" ANSI_COLOR_RESET);
        return 0;
    } else{
        char *resp=options[filaNumero][columanSimbolo];
        return resp;
    }

}

//a son simbolos
//s numero de fila
char ir_a(char sP, char A){
    int columanSimbolo=0;
    int filaNumero=0;
    int altura=18;
    int anchura=7;
    const char *options[anchura][altura];
    options[0][0] = "state", options[0][1] = "E", options[0][2] = "T", options[0][3] = "F";
    options[1][0] = "0", options[1][1] = "1", options[1][2] = "2", options[1][3] = "3";
    options[2][0] = "1", options[2][1] = "", options[2][2] = "", options[2][3] = "";
    options[3][0] = "2", options[3][1] = "", options[3][2] = "", options[3][3] = "";
    options[4][0] = "3", options[4][1] = "", options[4][2] = "", options[4][3] = "";
    options[5][0] = "4", options[5][1] = "8", options[5][2] = "2", options[5][3] = "3";
    options[6][0] = "5", options[6][1] = "", options[6][2] = "", options[6][3] = "";
    options[7][0] = "6", options[7][1] = "", options[7][2] = "9", options[7][3] = "3";
    options[8][0] = "7", options[8][1] = "", options[8][2] = "", options[8][3] = "10";
    options[9][0] = "8", options[9][1] = "", options[9][2] = "", options[9][3] = "";
    options[10][0] = "9", options[10][1] = "", options[10][2] = "", options[10][3] = "";
    options[11][0] = "10", options[11][1] = "", options[11][2] = "", options[11][3] = "";
    options[12][0] = "11", options[12][1] = "", options[12][2] = "", options[12][3] = "";

    for (int i = 0; i < anchura; ++i) {
        char *columna=options[0][i];
        char valorM=*columna;
        if(valorM==A){
            columanSimbolo=i;
            break;
        }
        if(i>=anchura){
            columanSimbolo=0;
            break;
        }
    }
    for (int j = 0; j < altura; ++j) {
        char *columna=options[j][0];
        char valorN=*columna;
        if(valorN==sP){
            filaNumero=j;
            break;
        }
        if(j>=altura){
            columanSimbolo=0;
            break;
        }
    }
    if (columanSimbolo==0 || filaNumero==0){
        printf(ANSI_COLOR_YELLOW "\nError accion no encontrada" ANSI_COLOR_RESET);
        return 0;
    } else{
        char *resp=options[filaNumero][columanSimbolo];
        return *resp;
    }

}



struct node
{
    char info;
    struct node *ptr;
}*top,*top1,*temp;

char topelement();
void push(char data);
void pop();
void empty();
void display();
void destroy();
void stack_count();
void create();

int count = 0;

/* Create empty stack */
void create()
{
    top = NULL;
}

/* Count stack elements */
void stack_count()
{
    printf("\n No. of elements in stack : %c", count);
}

/* Push data into stack */
void push(char data) {
    printf("\n Push value : %c", data);
    if (top == NULL)
    {
        top =(struct node *)malloc(1*sizeof(struct node));
        top->ptr = NULL;
        top->info = data;
    }
    else
    {
        temp =(struct node *)malloc(1*sizeof(struct node));
        temp->ptr = top;
        temp->info = data;
        top = temp;
    }
    count++;
}

/* Display stack elements */
void display()
{
    top1 = top;

    if (top1 == NULL)
    {
        printf("Stack is empty");
        return;
    }

    while (top1 != NULL)
    {
        printf("%c ", top1->info);
        top1 = top1->ptr;
    }
}

/* Pop Operation on stack */
void pop()
{
    top1 = top;

    if (top1 == NULL)
    {
        printf("\n Error : Trying to pop from empty stack");
        return;
    }
    else
        top1 = top1->ptr;
    printf("\n Popped value : %c", top->info);
    free(top);
    top = top1;
    count--;
}

/* Return top element */
char topelement()
{
    return(top->info);
}

/* Check if stack is empty or not */
void empty()
{
    if (top == NULL)
        printf("\n Stack is empty");
    else
        printf("\n Stack is not empty with %d elements", count);
}

/* Destroy entire stack */
void destroy()
{
    top1 = top;

    while (top1 != NULL)
    {
        top1 = top->ptr;
        free(top);
        top = top1;
        top1 = top1->ptr;
    }
    free(top1);
    top = NULL;

    printf("\n All stack elements destroyed");
    count = 0;
}




void analisiSintactico(char *w){
    int bandera=0;
    char temporal;
    int i;
    push('0');
    char * ae = NULL;
    ae = (char*)realloc(NULL, sizeof(char));
    int aei = 0;
    ae[aei]=*w;
    aei++;
    bandera=1;
    char s, sP;
    char a;
    while (*w != '\0') {
        s=topelement();
        if(*ae==NULL){a=temporal;}else{a=*ae;}
        if(bandera==1){
            free(ae);
            aei=0;
            ae = (char*)realloc(NULL, sizeof(char));
            bandera=0;
        }
        char *res=accion(s,a);
        if(res[0]=='d'){
            push(a);
            char atem=res[1];
            push(atem);
            w++;
            if(*w==' '){
                w++;
            }
            if(*w=='i'){
                temporal=*w;
                ae[aei]=*w;
                w++;
                aei++;
                ae[aei]+=*w;
                w++;
                bandera=1;
            }else{
                temporal=*w;
                ae[aei]=*w;
                w++;
                bandera=1;
            }

            display();
        } else if(res[0]=='r'){
            char aq=res[1];
            int res=2*reglaCount(aq);
            for (int j = 0; j < res; ++j) {
                pop();
            }
            sP=topelement();
            char A=getRulerA(aq);
            push(A);
            char ssP=ir_a(sP, A);
            push(ssP);
            //emitir la produccion
            printf(ANSI_COLOR_RED "\t ----------- "ANSI_COLOR_RESET "\n");
            display();
        } else if(res[0]=='acc'){
            printf(ANSI_COLOR_CYAN "\n\n Perfecto\n" ANSI_COLOR_RESET);
            return;
        } else{
            printf(ANSI_COLOR_RED "\t Error en la tabla "ANSI_COLOR_RESET "\n");
        }
    }
    ae = (char*)realloc(NULL, sizeof(char));
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

// FIN EDICION Michael
int main( int argc, char *argv[] )  {
    banner();
    int p=0;
    int op;
    char directorio[256];
    char* texto;
    char *igua;
    while(op!=4) {
        printf(ANSI_COLOR_CYAN "\n\n1.- Analizar Archivo\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "2.- Analizar Texto (No desarrollado)\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "3.- Datos de Analizador\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "4.- Salir\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_YELLOW "Indica la opcion: " ANSI_COLOR_RESET);



        scanf("%d", &op);





        switch(op) {
            case 1:
                printf("Ingrese directorio completo del archivo: \n");
                scanf("%s", &directorio);
                analizerFile(directorio);
                //analizerFile("/home/by-default/Documentos/gitProyect/automatasApp/archivo.txt");
                resultadosFinales();
                break;
            case 2:

                analisiSintactico("( id + id ) * id");
                //reglaCount('4');
                break;
            case 3:
                presentarDatos();
                break;
            case 4:
                break;
        }
    }


    return 0;
}
//autores: dickson y michael
