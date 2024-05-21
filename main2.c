#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Desarrollar un sistema de gestión de donaciones para un refugio de animales en el lenguaje
de programación C, que permita:
• Registro de donantes: Nombre, cédula, teléfono, dirección.
• Registro de donaciones: Fecha, tipo de donación (monetaria, material, voluntariado),
descripción (opcional), valor monetario (si aplica), donante (debe estar registrado).
• Asignar donaciones monetarias y de materiales a necesidades específicas del
refugio (alimento, medicinas, mantenimiento, reparaciones, etc.).
• Gestionar el estado de las donaciones (disponible/no disponible).
• Listado de cómo se han utilizado las donaciones monetarias y de materiales.
• Listado de artículos donados, cantidad, fecha de recepción.
• Listar el detalle de donaciones junto con el donante que la ha realizado.
• Listar cantidad de donaciones realizadas por donante.*/

typedef struct destino{
    char Nombre_destino;
    int Max_Donaciones;
}Destino;

typedef struct Donation{
    char cedula[30];
    char fecha[20];
    int tipo;
    char descriccion[300];
    int valor;
     struct Donation *next;
}Donation_t;

typedef struct User{
    char nombre[25];
    char cedula[30];
    char telefono[30];
    char direccion[30];
    int cantidad;
    int destino;
    struct User *next;
}User_t;

void obtenerFechaActual(char* fecha) {
    time_t tiempo;
    struct tm *fechaActual;

    tiempo = time(NULL);
    fechaActual = localtime(&tiempo);
    strftime(fecha, 20, "%d/%m/%Y", fechaActual);
}

void addNodeuser(User_t* head, User_t *user){

    while (head->next != NULL){

        head = head->next;

    }
    head->next = user;

}

void printNodesUsuarios(User_t* head){
    while (head!= NULL){
        printf("%s-\n", head->cedula);
        head = head->next;
    }
}

void freeLinkedUsers(User_t* head){
    User_t* temp;
    while (head){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void addNodeDonation(Donation_t* head, Donation_t* donation){
    Donation_t* newNode = malloc(sizeof(Donation_t));
    newNode->next = NULL;
    while (head->next != NULL){
        head = head->next;
    }
    head->next = newNode;
}

void printNodesDonations(Donation_t* head){
    while (head!= NULL){
        printf("%s-\n", head->cedula);
        head = head->next;
    }
}

void freeLinkedDonations(Donation_t* head){
    Donation_t* temp;
    while (head){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void main(){
    User_t* usuario=(User_t*)malloc(sizeof(User_t*));
    if(!usuario){
        printf("Error!!!");
        exit(0);
        }
    printf("ingrese nombre(pinche usuario todo gay): ");
    scanf("%s",usuario->nombre);
    printf("ingrese cedula (usuario burda gay de pana): ",usuario->cedula);
    scanf("%s",usuario->cedula);
    printf("factous %s es gay",usuario->nombre);
    printf("Doxeado tu cedula es %s\n",usuario->cedula);
}