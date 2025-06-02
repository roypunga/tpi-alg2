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

typedef struct encuestas{
    int encuesta_id;
    char denominacion[50];
    int encuesta_mes;
    int encuesta_anio;
    int preocesada; // 0 : no, 1: si
    struct encuestas *sgte;
}encuestas;

typedef struct preguntas{
    struct encuestas *encuesta_id;
    int pregunta_id;
    char pregunta[100];
    float ponderacion;
    struct preguntas *sgte;
}preguntas;

typedef struct respuestas{
    struct preguntas *pregunta_id;
    int respuesta_id;
    int respuesta_nro;
    char respuesta[100];
    float ponderacion;
    struct respuestas *sgte;
}respuestas;

typedef struct sEncuestador{
    int encuestador_id;
    char nombre[30], pass[15];
    struct sEncuestador* sgte;
}sEncuestador;

typedef struct encuestaRespondidas{
    struct encuestas *encuesta_id;
    struct preguntas *pregunta_id;
    struct respuestas *respuesta_id;
    int fecha_realizacion;
    struct encuestador *encuestador_id;
    int encuestarResondida_id;
    struct encuestaRespondidas *sgte;
}encuestaRespondidas;

void menu_encuestas();
void menu_preguntas();
void menu_respuestas();
void menu_administrador();
void menu_encuestador();
void menu_AdmEncuestadores();
void crear_encuesta();
int login(struct sEncuestador* lista);

void apilar(encuestas **tope, encuestas **nv){
    (*nv)->sgte = (*tope);
    (*tope) = (*nv);
    (*nv) = NULL;
}

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
                crear_encuesta();
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

encuestas *tope = NULL; // de momento el tope esta de manera global.
void crear_encuesta() {
    int opcion;

    do{
        printf("=================================\n");
        printf("          CREAR ENCUESTA         \n");
        printf("=================================\n");
        printf("\n");
        
        // faltaria la comprobacion de que se asigne correctamente el espacio en momoria "ELIJO CREER"
        encuestas* nueva = (encuestas*)malloc(sizeof(encuestas));
        printf("Ingrese ID de la encuesta: ");
        scanf("%d", &(nueva->encuesta_id));
        while(getchar() != '\n'); // Limpiar buffer
        
        printf("Ingrese denominacion: ");
        fgets(nueva->denominacion, 50, stdin);
        nueva->denominacion[strcspn(nueva->denominacion, "\n")] = '\0';
        
        printf("Ingrese mes (1-12): ");
        scanf("%d", &(nueva->encuesta_mes));
        
        printf("Ingrese anio: ");
        scanf("%d", &(nueva->encuesta_anio));
        
        nueva->preocesada = 0; // Por defecto no procesada
        nueva->sgte = NULL;
        
        // Apilar la nueva encuesta
        apilar(&tope, &nueva);
        printf("\nEncuesta creada y apilada con exito!\n");

        // Menú de opciones después de crear
        printf("\n¿Que desea hacer ahora?\n");
        printf("1. Crear otra encuesta\n");
        printf("2. Volver al menu principal\n");
        printf("0. Salir del programa\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n');

        switch (opcion)
        {
        case 1:
            //Continua creando encuestas
            break;
        case 2:
            clear_screen();
            return;
        case 0:
            printf("\nSaliendo del programa...\n");
            exit(0);
        default:
            printf("\nOpcion no valida. Volviendo al menu principal.\n");
            break;
        }


    }while (opcion == 1);
    
}

// --------------------------------------------------------- 

/* CRUD ENCUESTADORES*/

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Descarta todos los caracteres restantes en el buffer de entrada
        // hasta encontrar un salto de línea o fin de archivo
    }
}


void agregarEncuestador(sEncuestador** lista) {
    // Crear nuevo nodo
    sEncuestador* nuevo = (sEncuestador*)malloc(sizeof(sEncuestador));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }

    // Calcular el nuevo ID (máximo ID existente + 1)
    int max_id = 0;
    sEncuestador* actual = *lista;
    
    while (actual != NULL) {
        if (actual->encuestador_id > max_id) {
            max_id = actual->encuestador_id;
        }
        actual = actual->sgte;
    }
    

    char nombre[30], pass[15];
    int lectura_correcta;

    do {
        printf("Ingrese el nombre del encuestador (sin espacios, max 29 chars): ");
        lectura_correcta = scanf("%29s", nombre);  // %29s para dejar espacio para el '\0'
        limpiarBuffer();
        if (lectura_correcta != 1) {
            printf("Error en la lectura. ");
        }
    } while (lectura_correcta != 1);
    
    // Lectura del password con validación
    do {
        printf("Ingrese la pass del encuestador (sin espacios, max 14 chars): ");
        lectura_correcta = scanf("%14s", pass);  // %14s para dejar espacio para el '\0'
        limpiarBuffer();
        if (lectura_correcta != 1) {
            printf("Error en la lectura. ");
        }
    } while (lectura_correcta != 1);

    // Configurar el nuevo nodo
    nuevo->encuestador_id = max_id + 1;
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->pass, pass);

    // Insertar al inicio de la lista
    nuevo->sgte = *lista;
    *lista = nuevo;
}


//sin modificaion de preguntas ni de respuestas!!!!
//validador de respuestas -> es recorrido -> controla que todas las encuestas esten completas

//controles: Sumatoria de ponderacion de preguntas == 1 && almenos 1 respuesta tiene ponderacion == 1

//si hay una encuestaRespondida cargada no se puede borrar la encuesta

//prioridades:
// AB enc
// AB preg -> sumen 1
// AB resp -> haya un 1
// CSV de quique -> este bien cargada
// CSV sea procesado correctamente