#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct Need {
    char name[50];
    int id;
    int amount_needed;
    int amount_available;
    int material_needed;
    int material_received;
} Need_t;

typedef struct Donation {
    char cedulaDonante[30];
    char fecha[20];
    int tipo;
    char descripcion[300];
    int valor; 
    int amount;
    int need;
    char material[50];
    struct Donation* next;
} Donation_t;

typedef struct User {
    char nombre[40];
    char cedula[30];
    char telefono[30];
    char direccion[50];
    struct User* next;
} User_t;

Need_t needs[] = {
    {"Alimento", 1, 500, 500, 0, 0},
    {"Medicinas", 2, 300, 300, 0, 0},
    {"Mantenimiento", 3, 200, 200, 0, 0},
    {"Reparaciones", 4, 400, 400, 0, 0}
};

void inicializar_necesidades() {
    for (int i = 0; i < sizeof(needs) / sizeof(Need_t); i++) {
        needs[i].amount_available = needs[i].amount_needed;
    }
}

void printNeeds() {
     printf("\n--- Necesidades del refugio ---\n");
    for (int i = 0; i < sizeof(needs) / sizeof(Need_t); i++) {
        printf("%d. %s\n", needs[i].id, needs[i].name);
    }
}
void obtenerFechaActual(char* fecha) {
    time_t tiempo;
    struct tm* fechaActual;

    tiempo = time(NULL);
    fechaActual = localtime(&tiempo);
    strftime(fecha, 20, "%d/%m/%Y", fechaActual);
}

void addNodeUser(User_t** head, User_t* user) {
    if (*head == NULL) {
        *head = user;
    } else {
        User_t* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = user;
    }
}

void addNodeDonation(Donation_t** head, Donation_t* donation) {
    if (*head == NULL) {
        *head = donation;
    } else {
        Donation_t* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = donation;
    }
}

User_t* crear_Usuario() {
    User_t* user = malloc(sizeof(User_t));
    printf("\t\t\tIngrese el nombre: ");
    fgets(user->nombre, sizeof(user->nombre), stdin);
    user->nombre[strcspn(user->nombre, "\n")] = '\0';

    printf("\t\t\tIngrese la cédula: ");
    fgets(user->cedula, sizeof(user->cedula), stdin);
    user->cedula[strcspn(user->cedula, "\n")] = '\0';

    printf("\t\t\tIngrese el teléfono: ");
    fgets(user->telefono, sizeof(user->telefono), stdin);
    user->telefono[strcspn(user->telefono, "\n")] = '\0';

    printf("\t\t\tIngrese la dirección: ");
    fgets(user->direccion, sizeof(user->direccion), stdin);
    user->direccion[strcspn(user->direccion, "\n")] = '\0';

    user->next = NULL;

    return user;
}

Donation_t* crear_Donacion(char* cedulaDonante) {
    Donation_t* donacion = malloc(sizeof(Donation_t));
    char aux[20];
    printf("Tipo de donación (1 para monetaria, 2 para material): \n");
    printf("1.Monetaria\n");
    printf("2.Material\n");
    fgets(aux, sizeof(aux), stdin);
    if(aux[0]>='0' || aux[0]<='9'){ 
    donacion->tipo = aux[0]-'0';}
    if (donacion->tipo == 1) {
        printf("Ingrese la cantidad de dinero donada: ");
        fgets(aux, sizeof(aux), stdin);
        donacion->valor = atoi(aux);
    } else if (donacion->tipo == 2) {
        printf("Ingrese la cantidad de material donada: ");
        fgets(aux, sizeof(aux), stdin);
        donacion->amount = atoi(aux);
        
        printf("Ingrese el tipo de material donado: ");
        fgets(donacion->material, sizeof(donacion->material), stdin);
        donacion->material[strcspn(donacion->material, "\n")] = '\0';
    }
    
    printNeeds();

    printf("Seleccione la necesidad a la que se destina la donación: ");
    fgets(aux, sizeof(aux), stdin);
    donacion->need = atoi(aux);


    strncpy(donacion->cedulaDonante, cedulaDonante, sizeof(donacion->cedulaDonante));

    obtenerFechaActual(donacion->fecha);

    printf("\t\t\tIngrese el tipo: ");
    char tipoStr[10];
    fgets(tipoStr, sizeof(tipoStr), stdin);
    donacion->tipo = atoi(tipoStr);

    printf("\t\t\tIngrese la descripción: ");
    fgets(donacion->descripcion, sizeof(donacion->descripcion), stdin);
    donacion->descripcion[strcspn(donacion->descripcion, "\n")] = '\0';

    printf("\t\t\tIngrese el valor: ");
    char valorStr[10];
    fgets(valorStr, sizeof(valorStr), stdin);
    donacion->valor = atoi(valorStr);

    donacion->next = NULL;

    return donacion;
}

void printNodesUsers(User_t* head) {
    while (head != NULL) {
        printf("Cédula: %s\n", head->cedula);
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

void freeLinkeddonaciones(Donation_t* head) {
    Donation_t* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printNodesdonaciones(Donation_t* head) {
    printf("\n--- Lista de Donaciones ---\n");
    while (head != NULL) {
        printf("Cédula del donante: %s\n", head->cedulaDonante);
        printf("Fecha: %s\n", head->fecha);
        printf("Tipo: %d\n", head->tipo);
        printf("Descripción: %s\n", head->descripcion);
        printf("Valor: %d\n", head->valor);
        printf("--------------------------\n");
        head = head->next;
    }
}

void Tracking_Donaciones(Donation_t* head, char* cedulaABuscar) {
    printf("\n--- Donaciones para la cédula %s ---\n", cedulaABuscar);
    Donation_t* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->cedulaDonante, cedulaABuscar) == 0) {
            found = 1;
            printf("Fecha: %s\n", temp->fecha);
            printf("Tipo: %d\n", temp->tipo);
            printf("Descripción: %s\n", temp->descripcion);
            printf("Valor: %d\n", temp->valor);
            printf("--------------------------\n");
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No se encontraron donaciones para la cédula %s.\n", cedulaABuscar);
    }
}

Donation_t* donar(Donation_t* donaciones, char* cedulaDonante) {
    Donation_t* donacion = crear_Donacion(cedulaDonante);
    addNodeDonation(&donaciones, donacion);
    printf("Donación de %d para la necesidad %d\n", donacion->amount, donacion->need);
    printNodesdonaciones(donaciones);

    char buffer[10];
    int respuesta = 1;
    printf("¿Desea realizar otra donación?(Si/No): \n");
    printf("1. Si\n");
    printf("2. No\n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    respuesta = atoi(buffer);
   if (respuesta != 1) {
            return donaciones;
    } else {
        if (donacion->tipo == 1) {
            needs[donacion->need - 1].amount_available -= donacion->amount;
            printf("Monto disponible para la necesidad %d: %d\n", donacion->need, needs[donacion->need - 1].amount_available);
        }
        return donar(donaciones,cedulaDonante);
    }
}
void imprimir_easter_egg(){
    char line[2000]; // Utilizamos un búfer más grande
    FILE* archivo = fopen("gojo.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    } else {
        while (fgets(line, sizeof(line), archivo) != NULL) {
            printf("%s", line);
        }
        fclose(archivo);
    }
}


void realizar_Donaciones() {
    User_t* Users = NULL;
    Donation_t* donations = NULL;
    char buffer[10];
    int respuesta = 1;
    char cedula[30];

    while (respuesta == 1) {
        User_t* user = crear_Usuario();
        addNodeUser(&Users, user);

        printf("\nDatos del usuario:\n");
        printf("Nombre: %s\n", user->nombre);
        printf("Cédula: %s\n", user->cedula);
        printf("Teléfono: %s\n", user->telefono);
        printf("Dirección: %s\n", user->direccion);

        printf("¿Desea hacer una donación?(Si/No): \n");
        printf("1. Si\n");
        printf("2. No\n");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        respuesta = atoi(buffer);

        if (respuesta == 1) {
            donations = donar(donations, user->cedula);
        } 
    }

    printf("¿Desea buscar las donaciones que un usuario ha hecho? (Si/No): \n");
    printf("1. Si\n");
    printf("2. No\n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    respuesta = atoi(buffer);

    if (respuesta == 1) {
        printf("Ingrese la cédula a buscar: ");
        fgets(cedula, sizeof(cedula), stdin);
        cedula[strcspn(cedula, "\n")] = '\0';
        Tracking_Donaciones(donations, cedula);
    }

    printf("Terminando programa...\n");
    freeLinkedUsers(Users);
    freeLinkeddonaciones(donations);
}
int main() {
    int opcion;
    inicializar_necesidades();
    realizar_Donaciones();
    printf("");
    getchar();
    imprimir_easter_egg();
    return 0;
}
