#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función portable para limpiar pantalla
void clear_screen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}


struct sEncuestador{
    int encuestador_id;
    char nombre[30], pass[15];
    struct sEncuestador* sgte;
};


void menu_encuestas();
void menu_preguntas();
void menu_respuestas();
void menu_administrador();
void menu_encuestador();
void menu_AdmEncuestadores();
int login(struct sEncuestador* lista);




int main() {
    struct sEncuestador* listaEncuestadores = NULL;

    int control;

    //carga de un encuestador para prueba
    struct sEncuestador* nodo = NULL;
    nodo = malloc(sizeof(struct sEncuestador));
    nodo->encuestador_id = 10;
    strcpy(nodo->nombre, "Garrafa Sanchez");
    strcpy(nodo->pass, "taladro10");
    nodo->sgte = NULL;
    listaEncuestadores = nodo;
    nodo = NULL;



    do{
        control = login(listaEncuestadores);

        if(control == 2){
            clear_screen();
            menu_administrador();
        }
        if(control == 1){
            clear_screen();
            menu_encuestador();
        }
        if(control == 0){
            clear_screen();
            printf("Usuario o pass incorrecta, intente de nuevo. \n");
        }

    }while(control != -1);


    return 0;
}

int login(struct sEncuestador* lista){
    int retorno = 0;

    int check;
    char pass[15];
    int id;
    
    printf("=================================\n");
    printf("       ENCUESTAS EL CURIOSO      \n");
    printf("=================================\n");
    printf("Para salir ingrese -1 en el ID. (Adm: 777)\n");
    printf("ID: \n");
    scanf("%d", &id);
    if(id == -1){
        retorno = -1;
    }
    else if(id == 777){
        printf("Pass de Administrador (es banfield): \n");
        scanf("%s", pass);
        if(!strcmp(pass, "banfield")){
            retorno = 2;
        }
    }
    else{
        printf("Pass: \n");
        scanf("%s", pass);

        while(lista != NULL){
                if(lista->encuestador_id == id && !strcmp(lista->pass, pass)){
                retorno = 1;
                }
            lista = lista->sgte;
        }
    }

    return retorno;
}

void menu_administrador(){
       int opcion;
    
    do {
        printf("=================================\n");
        printf("        MENU ADMINISTRADOR       \n");
        printf("=================================\n");
        printf("1. Encuestas\n");
        printf("2. Preguntas\n");
        printf("3. Respuestas\n");
        printf("4. Encuestadores\n");
        printf("0. Salir\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                clear_screen();
                menu_encuestas();
                break;
            case 2:
                clear_screen();
                menu_preguntas();
                break;
            case 3:
                clear_screen();
                menu_respuestas();
                break;
            case 4:
                clear_screen();
                menu_AdmEncuestadores();
                break;
            case 0:
                printf("Cerrando sesion...\n");
                clear_screen();
                break;
            default:
                clear_screen();
                printf("Opcion no valida. Intente de nuevo.\n");
                
        }
        
    } while (opcion != 0);
}

void menu_AdmEncuestadores(){
int opcion;
    
    do {
        printf("=================================\n");
        printf("        MENU ENCUESTADORES       \n");
        printf("=================================\n");
        printf("1. Agregar encuestador\n");
        printf("2. Mostrar encuestadores\n");
        printf("3. Actualizar encuestador\n");
        printf("4. Eliminar encuestador\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                //
                clear_screen();
                break;
            case 2:
                //
                clear_screen();
                break;
            case 3:
                //
                clear_screen();
                break;
            case 4:
                //
                clear_screen();
                break;
            case 0:
                clear_screen();
                break;
            default:
                clear_screen();
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}

void menu_encuestador() {
    int opcion;
    
    do {
        printf("=================================\n");
        printf("        MENU ENCUESTADOR         \n");
        printf("=================================\n");
        printf("1. Cargar respuestas desde archivo CSV\n");
        printf("2. Ingresar respuestas manualmente\n");
        printf("3. Mostrar todas las encuestas\n");
        printf("4. Mostrar ponderaciones\n");
        printf("5. Mostrar encuesta específica (por ID)\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                clear_screen();
                printf("\n--- Cargar desde CSV ---\n");
                // Función para cargar desde CSV iría aquí
                break;
            case 2:
                clear_screen();
                printf("\n--- Ingreso manual ---\n");
                // Función para ingreso manual iría aquí
                break;
            case 3:
                clear_screen();
                printf("\n--- Todas las encuestas ---\n");
                // Función para mostrar todas las encuestas iría aquí
                break;
            case 4:
                clear_screen();
                printf("\n--- Ponderaciones ---\n");
                // Función para mostrar ponderaciones iría aquí
                break;
            case 5:
                clear_screen();
                printf("\n--- Buscar por ID ---\n");
                // Función para mostrar encuesta por ID iría aquí
                break;
            case 0:
                clear_screen();
                break;
            default:
                clear_screen();
                printf("\n¡Opción no válida! Intente de nuevo.\n");
        }
    } while (opcion != 0);
}

void menu_encuestas() {
    int opcion;
    
    do {
        printf("=================================\n");
        printf("          MENU ENCUESTAS         \n");
        printf("=================================\n");
        printf("1. Crear encuesta\n");
        printf("2. Mostrar encuestas\n");
        printf("3. Actualizar encuesta\n");
        printf("4. Eliminar encuesta\n");
        printf("5. Calcular ponderacion\n");
        printf("6. Mostrar encuesta especifica\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                //crear encuesta
                clear_screen();
                break;
            case 2:
                //mostrar encuestas
                clear_screen();
                break;
            case 3:
                //actualizar encuesta
                clear_screen();
                break;
            case 4:
                //eliminar encuesta
                clear_screen();
                break;
            case 5:
                //calcular ponderacion
                clear_screen();
                break;
            case 6:
                //mostrar encuesta por id
                clear_screen();
                break;
            case 0:
                clear_screen();
                break;
            default:
                clear_screen();
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}

void menu_preguntas() {
    int opcion;
    
    do {
        printf("=================================\n");
        printf("          MENU PREGUNTAS         \n");
        printf("=================================\n");
        printf("1. Crear pregunta\n");
        printf("2. Mostrar preguntas\n");
        printf("3. Actualizar pregunta\n");
        printf("4. Eliminar pregunta\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                //crear pregunta
                clear_screen();
                break;
            case 2:
                //mostrar preguntas
                clear_screen();
                break;
            case 3:
                //actualizar pregunta
                clear_screen();
                break;
            case 4:
                //eliminar pregunta
                clear_screen();
                break;
            case 0:
                clear_screen();
                break;
            default:
                clear_screen();
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}

void menu_respuestas() {
    int opcion;
    
    do {
        printf("=================================\n");
        printf("         MENU RESPUESTAS         \n");
        printf("=================================\n");
        printf("1. Crear respuesta\n");
        printf("2. Mostrar respuestas\n");
        printf("3. Actualizar respuesta\n");
        printf("4. Eliminar respuesta\n");
        printf("5. Cargar respuestas desde .CSV\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                //crear respuesta
                clear_screen();
                break;
            case 2:
                //mostrar respuestas
                clear_screen();
                break;
            case 3:
                //actualizar respuesta
                clear_screen();
                break;
            case 4:
                //eliminar respuesta
                clear_screen();
                break;
            case 5:
                //cargar desde csv
                clear_screen();
                break;
            case 0:
                printf("\nVolviendo al menu principal...\n");
                clear_screen();
                break;
            default:
                clear_screen();
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}