// donaciones.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct destino {
    char Nombre_destino;
    int Max_Donaciones;
} Destino;

typedef struct Donation {
    char cedula[30];
    char fecha[20];
    int tipo;
    char descriccion[300];
    int valor;
    struct Donation *next;
} Donation_t;

typedef struct User {
    char nombre[40];
    char cedula[30];
    char telefono[30];
    char direccion[50];
    int cantidad;
    int destino;
    struct User *next;
} User_t;

void obtenerFechaActual(char* fecha) {
    time_t tiempo;
    struct tm *fechaActual;

    tiempo = time(NULL);
    fechaActual = localtime(&tiempo);
    strftime(fecha, 20, "%d/%m/%Y", fechaActual);
}

void addNodeuser(User_t** head, User_t *user) {
    if (*head == NULL) {
        *head = user;
        user->next = NULL;
    } else {
        User_t* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = user;
        user->next = NULL;
    }
}

User_t* crearUsuario() {
    User_t* usuario = malloc(sizeof(User_t));

    printf("\t\t\tIngrese el nombre: ");
    fgets(usuario->nombre, sizeof(usuario->nombre), stdin);
    usuario->nombre[strcspn(usuario->nombre, "\n")] = '\0';

    printf("\t\t\tIngrese la cédula: ");
    fgets(usuario->cedula, sizeof(usuario->cedula), stdin);
    usuario->cedula[strcspn(usuario->cedula, "\n")] = '\0';

    printf("\t\t\tIngrese el teléfono: ");
    fgets(usuario->telefono, sizeof(usuario->telefono), stdin);
    usuario->telefono[strcspn(usuario->telefono, "\n")] = '\0';

    printf("\t\t\tIngrese la dirección: ");
    fgets(usuario->direccion, sizeof(usuario->direccion), stdin);
    usuario->direccion[strcspn(usuario->direccion, "\n")] = '\0';

    printf("\t\t\tIngrese el destino: ");
    char destinoStr[10];
    fgets(destinoStr, sizeof(destinoStr), stdin);
    usuario->destino = atoi(destinoStr);

    usuario->next = NULL;

    return usuario;
}

void addNodeDonation(Donation_t** head, Donation_t* donation) {
    if (*head == NULL) {
        *head = donation;
        donation->next = NULL;
    } else {
        Donation_t* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = donation;
        donation->next = NULL;
    }
}

Donation_t* crearDonacion() {
    Donation_t* donacion = malloc(sizeof(Donation_t));

    printf("\t\t\tIngrese la cédula: ");
    fgets(donacion->cedula, sizeof(donacion->cedula), stdin);
    donacion->cedula[strcspn(donacion->cedula, "\n")] = '\0';

    obtenerFechaActual(donacion->fecha);

    printf("\t\t\tIngrese el tipo: ");
    char tipoStr[10];
    fgets(tipoStr, sizeof(tipoStr), stdin);
    donacion->tipo = atoi(tipoStr);

    printf("\t\t\tIngrese la descripción: ");
    fgets(donacion->descriccion, sizeof(donacion->descriccion), stdin);
    donacion->descriccion[strcspn(donacion->descriccion, "\n")] = '\0';

    printf("\t\t\tIngrese el valor: ");
    char valorStr[10];
    fgets(valorStr, sizeof(valorStr), stdin);
    donacion->valor = atoi(valorStr);

    donacion->next = NULL;

    return donacion;
}

void printNodesUsuarios(User_t* head) {
    while (head != NULL) {
        printf("%s-\n", head->cedula);
        head = head->next;
    }
}

void freeLinkedUsers(User_t* head) {
    User_t* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printNodesDonations(Donation_t* head) {
    printf("\n--- Lista de Donaciones ---\n");
    while (head != NULL) {
        printf("Cédula: %s\n",




Ask a follow-up...
