#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int banner(){
printf("\n");
printf("\n");
printf(ANSI_COLOR_GREEN "\t █████╗ ███╗   ██╗ █████╗ ██╗  ██╗   ██╗███████╗███████╗██████╗ \n" ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "\t██╔══██╗████╗  ██║██╔══██╗██║  ╚██╗ ██╔╝╚══███╔╝██╔════╝██╔══██╗\n" ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "\t███████║██╔██╗ ██║███████║██║   ╚████╔╝   ███╔╝ █████╗  ██████╔╝\n" ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "\t██╔══██║██║╚██╗██║██╔══██║██║    ╚██╔╝   ███╔╝  ██╔══╝  ██╔══██╗\n" ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "\t██║  ██║██║ ╚████║██║  ██║███████╗██║   ███████╗███████╗██║  ██║\n" ANSI_COLOR_RESET);
printf(ANSI_COLOR_GREEN "\t╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝   ╚══════╝╚══════╝╚═╝  ╚═╝\n" ANSI_COLOR_RESET);
                                                                
printf(ANSI_COLOR_RED "\t\t\tby: Michael & Dickson"ANSI_COLOR_RESET "\n");
}


int main( int argc, char *argv[] )  {
	banner();
   if( argc == 2 ) {
      printf("El directorio del archivo es: %s\n", argv[1]);
	char c[1000];
    FILE *fptr;

    if ((fptr = fopen(argv[1], "r")) == NULL){
        printf(ANSI_COLOR_RED"\nError! No se puede abrir el archivo.\n"ANSI_COLOR_RESET);
        exit(1);         
    }

    // leer texto
    fscanf(fptr,"%[^\n]", c);

    printf(ANSI_COLOR_GREEN"Datos del archivo:\n%s"ANSI_COLOR_RESET, c);
    fclose(fptr);
	return 0;
   }
   else if( argc != 2 ) {
      printf(ANSI_COLOR_RED"\nError! Falta argumento de archivo a leer.\n"ANSI_COLOR_RESET);
   }
   else {
      printf("Error de argumentos.\n");
   }
return 0;
}
