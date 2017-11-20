#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
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

int coprobarDir(){

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
    FILE* archivo = fopen("/home/by-default/Documents/gitProyects/automatasApp/archivo.txt","r");
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
                            printf(ANSI_COLOR_RED "Error: %s no es una palabra reservada.\n" ANSI_COLOR_RESET, buffer);
                            estado=0;
                        }
                        c = fgetc(archivo);
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
                    }
                    break;
                case 8: //automata para numeros
                    if (isalnum(puntero)){
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
    if(isalpha(temp) || isalnum(temp)){
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
        keywords=" ";
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
    char *keywords="+-*/";

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
        char *keywords="<>=";

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
    if(isalpha(temp) && isupper(temp)){
        flag=1;
    }else{
        //char keywords[12][1] = {"<", ">", "=","+", "-", "*", "/", ";", "(", " ", "=", ")", ":" };
        char *keywords="<>=+-*/;( =):,\"";

        for (int i = 0; i < 15; ++i) {
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
    printf(ANSI_COLOR_BLUE "\n\n##################################" ANSI_COLOR_RESET);
}

// FIN EDICION Michael
int main( int argc, char *argv[] )  {
    banner();
    int p=0;
    int op;
    char directorio[256];
    char* texto;
    while(op!=4) {
        printf(ANSI_COLOR_CYAN "\n\n1.- Analizar Archivo\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "2.- Analizar Texto\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "3.- Datos de Analizador\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "4.- Salir\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_YELLOW "Indica la opcion: " ANSI_COLOR_RESET);
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("Ingrese directorio completo del archivo: \n");
                scanf("%s", &directorio);
//                analizerFile(directorio);
                analizerFile("/home/by-default/Documents/gitProyects/automatasApp/archivo.txt");
                resultadosFinales();
                break;
            case 2:
                printf("Ingrese directorio del archivo: \n");
                scanf("%d", &texto);
                printf(texto);
                break;
            case 3:
                printf("Datos: asdsa, \nasdsa, asdsa\n");
                break;
            case 4:
                break;
        }
    }
    return 0;
}
//autores: dickson y michaelju
