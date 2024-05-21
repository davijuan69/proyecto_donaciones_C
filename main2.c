#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
typedef struct Donation{
    char cedula[30];
    char fecha[20];
    char tipo[20];
    char descriccion[100];
    char valor[20]; 
}Donation_t;

typedef struct User
{
    char nombre[20];
    char cedula[30];
    char telefono[30];
    char direccion[30];
}User_t;

typedef struct nodeDonation
{
    Donation_t donation;
    struct nodeDonation* next;
}nodeDonation_t;

void addNodeDonationStart(nodeDonation_t* head, Donation_t donation){
    nodeDonation_t* newNode = malloc(sizeof(nodeDonation_t));
    newNode->donation = donation;

    newNode->next = head->next;

    head->next = newNode;
}

void addNodeDonationEnd(nodeDonation_t* head, Donation_t donation){
    nodeDonation_t* newNode = malloc(sizeof(nodeDonation_t));
    newNode->donation = donation;
    newNode->next = NULL;

    while (head->next != NULL){
        head = head->next;
    }
    head->next = newNode;
}

void printNodesDonations(nodeDonation_t* head){
    while (head!= NULL){
        printf("%s-\n", head->donation.cedula);
        head = head->next;
    }
}

void freeLinkedDonations(nodeDonation_t** head){
    nodeDonation_t* temp;
    while (*head != NULL){
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}






int main(){
    return 0;
}