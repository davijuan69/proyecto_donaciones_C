#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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

typedef struct Need {
    char name[50];
    int id;
} Need_t;

typedef struct Donation{
    char cedula[30];
    char fecha[20];
    int tipo;
    char descriccion[300];
    int valor;
     struct Donation *next;
     int amount;
     int need;
}Donation_t;

typedef struct User{
    char nombre[40];
    char cedula[30];
    char telefono[30];
    char direccion[50];
    int cantidad;
    int destino;
    struct User *next;
}User_t;

Need_t needs[] = {
    {"Alimento", 1},
    {"Medicinas", 2},
    {"Mantenimiento", 3},
    {"Reparaciones", 4}
};

void printNeeds() {
    printf("\n--- Necesidades del refugio ---\n");
    for (int i = 0; i < sizeof(needs)/sizeof(Need_t); i++) {
        printf("%d. %s\n", needs[i].id, needs[i].name);
    }
}

void obtenerFechaActual(char* fecha) {
    time_t tiempo;
    struct tm *fechaActual;

    tiempo = time(NULL);
    fechaActual = localtime(&tiempo);
    strftime(fecha, 20, "%d/%m/%Y", fechaActual);
}

void addNodeuser(User_t* head, User_t *user){
    if(!head){
        head=(User_t*)malloc(sizeof(User_t));
        head->next = user;
        user->next=NULL;
    }   
    while (head->next != NULL){

        head = head->next;

    }
    head->next = user;

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


Donation_t* crearDonacion() {
    Donation_t* donacion = malloc(sizeof(Donation_t));

    printf("Ingrese la cantidad de la donación: ");
    char amountStr[10];
    fgets(amountStr, sizeof(amountStr), stdin);
    donacion->amount = atoi(amountStr);

    printNeeds();
    printf("Seleccione la necesidad a la que se destina la donación: ");
    char needStr[10];
    fgets(needStr, sizeof(needStr), stdin);
    donacion->need = atoi(needStr);

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

void addNodeDonation(Donation_t** head, Donation_t* donation) {
    if (*head == NULL) {
        *head = donation;
    } else {
        Donation_t* actual = *head;
        while (actual->next != NULL) {
            actual = actual->next;
        }
        actual->next = donation;
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

void printNodesDonations(Donation_t* head) {
    printf("\n--- Lista de Donaciones ---\n");
    while (head != NULL) {
        printf("Cédula: %s\n", head->cedula);
        printf("Fecha: %s\n", head->fecha);
        printf("Tipo: %d\n", head->tipo);
        printf("Descripción: %s\n", head->descriccion);
        printf("Valor: %d\n", head->valor);
        printf("--------------------------\n");
        head = head->next;
    }
}

void buscarDonacionesPorCedula(Donation_t* head, char* cedulaABuscar) {
    printf("\n--- Donaciones para la cédula %s ---\n", cedulaABuscar);
    while (head != NULL) {
        if (strcmp(head->cedula, cedulaABuscar) == 0) {
            printf("Cédula: %s\n", head->cedula);
            printf("Fecha: %s\n", head->fecha);
            printf("Tipo: %d\n", head->tipo);
            printf("Descripción: %s\n", head->descriccion);
            printf("Valor: %d\n", head->valor);
            printf("--------------------------\n");
        }
        head = head->next;
    }
}



void realizarDonaciones() {
    User_t* usuarios = NULL;
    Donation_t* donaciones = NULL;
    char respuesta[10] = "Si";
    char aux[20];
    char cedula[30];
    while (strcmp(respuesta, "Si") == 0 || strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0 || strcmp(respuesta, "sI") == 0) {
        User_t* usuario = crearUsuario();
        addNodeuser(usuarios, usuario);

        printf("\nDatos del usuario:\n");
        printf("Nombre: %s\n", usuario->nombre);
        printf("Cédula: %s\n", usuario->cedula);
        printf("Teléfono: %s\n", usuario->telefono);
        printf("Dirección: %s\n", usuario->direccion);
        printf("Destino: %d\n", usuario->destino);

        printf("¿Desea hacer una donación? (Si/No): ");
        fgets(aux, sizeof(aux), stdin);
        aux[strcspn(aux, "\n")] = '\0';

        if (strcmp(aux, "Si") == 0 || strcmp(aux, "si") == 0 || strcmp(aux, "SI") == 0 || strcmp(aux, "sI") == 0) {
            Donation_t* donacion = crearDonacion();
            addNodeDonation(&donaciones, donacion);
            printNodesDonations(donaciones);
            printf("¿Desea realizar otra donación? (Si/No): ");
            fgets(respuesta, sizeof(respuesta), stdin);
            respuesta[strcspn(respuesta, "\n")] = '\0';
        } else {
             printf("¿Desea buscar las donaciones que un usuario ha hecho? (Si/No): ");
                fgets(aux, sizeof(aux), stdin);
                aux[strcspn(aux, "\n")] = '\0';

                if (strcmp(aux, "Si") == 0 || strcmp(aux, "si") == 0 || strcmp(aux, "SI") == 0 || strcmp(aux, "sI") == 0) {
                    printf("ingrese la cedula a buscar: ");
                    fgets(cedula,sizeof(cedula),stdin);
                    buscarDonacionesPorCedula(donaciones,cedula);
            printf("¿Desea realizar una donación? (Si/No): ");
            fgets(respuesta, sizeof(respuesta), stdin);
            respuesta[strcspn(respuesta, "\n")] = '\0';

            strcpy(respuesta, "No");
        }
        else{
            strcpy(respuesta, "No");
            }
        }
    }

    printf("Terminando programa...\n");

    freeLinkedUsers(usuarios);
    freeLinkedDonations(donaciones);
}



void main(){
    Donation_t* donacion = crearDonacion();
    printf("Donación de %d para la necesidad %d\n", donacion->amount, donacion->need);
    free(donacion);
    realizarDonaciones();

}