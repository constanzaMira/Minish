#include "builtin.h"

int pathname_is_regular(char *);
int pathname_is_dir(char *);
int copy_file(char *, char *);

int builtin_copiar(int argc, char **argv)
{
    char *origin_file = argv[1];

    char *last_file = argv[argc-1];

    if(argc == 1){
        fprintf(stderr, "copiar: invalid number of arguments\n");
        return EXIT_FAILURE;
    }

    if (!pathname_is_regular(origin_file)){
        fprintf(stderr, "copiar: origen is not a regular file\n");
        return EXIT_FAILURE;
    }

    if (!pathname_is_dir(last_file)) { // si el segundo argumento no es un directorio
        FILE *origin,*destiny;
        int c;

        if ((origin = fopen(origin_file, "r")) == NULL) {

            fprintf(stderr, "copiar: Error opening file for reading\n");
            return EXIT_FAILURE;
        }
        if ((destiny = fopen(last_file, "w")) == NULL) {
            
            fprintf(stderr, "copiar: Error opening file for writing\n");
            fclose(origin);

            return EXIT_FAILURE;
        }
        while ((c = fgetc(origin)) != EOF) {
            fputc(c, destiny);
        }

        fclose(destiny);
        fclose(origin);
        return EXIT_SUCCESS;

    }
    if(pathname_is_dir(last_file)){ // si el ultimo argumento es un directorio

        for(int i=1;i<argc-1;i++){ // argc -1 o arg c?
            if(pathname_is_regular(argv[i])){
                copy_file(argv[i],last_file);
            }
        }
    }
    return EXIT_SUCCESS;
    
}

int pathname_is_regular(char *pathname)
{
    struct stat buf;
    if (stat(pathname, &buf) == -1)
        return 0;
    return S_ISREG(buf.st_mode);// se usa s_isreg para saber si es un archivo regular
}

int pathname_is_dir(char *pathname)
{
    struct stat buf;
    if (stat(pathname, &buf) == -1) 
        return 0;
    return S_ISDIR(buf.st_mode);// Devuelve 0 si no es un directorio.
}

int copy_file(char *origin_file, char *destiny_dir){

    int ch;
    FILE *origin, *destiny;
    char *destino = malloc(strlen(destiny_dir) + strlen(basename(origin_file)) + 2);

    if ((origin = fopen(origin_file, "r")) == NULL) {
        fprintf(stderr, "copiar: Error opening file for reading\n");
        free(destino);
        return EXIT_FAILURE;
    }

    sprintf(destino, "%s/%s", destiny_dir, basename(origin_file));

    if ((destiny = fopen(destino, "w")) == NULL) {
        fprintf(stderr, "copiar: Error opening file for writing\n");
        fclose(origin);
        free(destino);
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(origin)) != EOF) {
        fputc(ch, destiny);
    }

    fclose(origin);
    fclose(destiny);
    free(destino);

    return EXIT_SUCCESS;

}


