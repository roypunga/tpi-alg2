#include <stdio.h>
#include <stdlib.h>

// Función portable para limpiar pantalla
void clear_screen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}


void menu_encuestas();
void menu_preguntas();
void menu_respuestas();

int main() {
    int opcion;
    
    do {
        printf("=================================\n");
        printf("          MENU PRINCIPAL         \n");
        printf("=================================\n");
        printf("1. Encuestas\n");
        printf("2. Preguntas\n");
        printf("3. Respuestas\n");
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
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                clear_screen();
                printf("Opcion no valida. Intente de nuevo.\n");
                
        }
        
    } while (opcion != 0);
    
    return 0;
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
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                printf("\nCreando nueva encuesta...\n");
                //crear encuesta
                clear_screen();
                break;
            case 2:
                printf("\nListado de encuestas:\n");
                //mostrar encuestas
                clear_screen();
                break;
            case 3:
                printf("\nActualizando encuesta...\n");
                //actualizar encuesta
                clear_screen();
                break;
            case 4:
                printf("\nEliminando encuesta...\n");
                //eliminar encuesta
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
                printf("\nCreando nueva pregunta...\n");
                //crear pregunta
                clear_screen();
                break;
            case 2:
                printf("\nListado de preguntas:\n");
                //mostrar preguntas
                clear_screen();
                break;
            case 3:
                printf("\nActualizando pregunta...\n");
                //actualizar pregunta
                clear_screen();
                break;
            case 4:
                printf("\nEliminando pregunta...\n");
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
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                printf("\nCreando nueva respuesta...\n");
                //crear respuesta
                clear_screen();
                break;
            case 2:
                printf("\nListado de respuestas:\n");
                //mostrar respuestas
                clear_screen();
                break;
            case 3:
                printf("\nActualizando respuesta...\n");
                //actualizar respuesta
                clear_screen();
                break;
            case 4:
                printf("\nEliminando respuesta...\n");
                //eliminar respuesta
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