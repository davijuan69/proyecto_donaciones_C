#include <stdio.h>
#include <stdbool.h>

bool buscarDatosEnArchivo(char dato1, char dato2) {
    FILE* archivo = fopen("hola.txt", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return false;
    }

    char caracter;
    bool encontrado1 = false;
    bool encontrado2 = false;

    while ((caracter = fgetc(archivo)) != EOF) {
        if (caracter == dato1) {
            encontrado1 = true;
        }
        if (caracter == dato2) {
            encontrado2 = true;
        }
    }

    fclose(archivo);

    if (encontrado1 && encontrado2) {
        return true;
    } else {
        return false;
    }
}

int main() {
    FILE* archivo = fopen("hola.txt", "r+");
    char dato1, dato2;
    printf("Ingrese el primer dato: ");
    scanf("%c", &dato1);
    printf("\nIngrese el segundo dato: \n");
    scanf(" %c", &dato2);

    bool encontrado = buscarDatosEnArchivo(dato1, dato2);

    if (encontrado) {
        printf("Los datos fueron encontrados en el archivo.\n");
    } else {
        printf("Los datos no fueron encontrados en el archivo.\n");
    }

    return 0;
}
