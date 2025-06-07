#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

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
    int procesada; // 0 : no, 1: si
    struct encuestas *sgte;
}encuestas;

typedef struct preguntas{
    int encuesta_id;
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

void menu_encuestas(encuestas **tope);
void menu_preguntas();
void menu_respuestas();
void menu_administrador(encuestas **tope);
void menu_encuestador();
void menu_AdmEncuestadores();
void mostrar_encuesta(encuestas **tope,int interactivo);
void crear_encuesta(encuestas **tope);
void eliminar_encuesta(encuestas **tope);
int login(sEncuestador* lista);
void apilar(encuestas **tope, encuestas **nv);
void desapilar(encuestas **tope, encuestas **nodo_desapilado);
int vacia(encuestas **tope);
bool idExiste(encuestas *tope, int id);
int leerNumeroValidado(const char *mensaje, const char *mensajeError, int min, int max, bool validarUnico, encuestas **tope);
void agregarEncuestador(sEncuestador** lista);
void limpiarBuffer();
void crearRespuesta();
void mostrarRespuestas();
void eliminarRespuestas();
void buscarBorrar(int num, respuestas **, respuestas **, int *);

//Prueba de pasar el tope desde main hasta crear_encuesta 
int main() {
    sEncuestador* listaEncuestadores = NULL;
    encuestas *tope = NULL;

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
            menu_administrador(&tope);
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

void desapilar(encuestas **tope, encuestas **nodo_desapilado){
    if((*tope) != NULL){
        (*nodo_desapilado) = (*tope);
        (*tope) = (*tope)->sgte;
        (*nodo_desapilado)->sgte = NULL;
    }
}

void apilar(encuestas **tope, encuestas **nv){
    (*nv)->sgte = (*tope);
    (*tope) = (*nv);
    (*nv) = NULL;
}

int vacia(encuestas **tope){
    return(*tope == NULL);
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

void menu_administrador(encuestas **tope){
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
                menu_encuestas(tope);
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

void menu_encuestas(encuestas **tope) {
    int opcion;
    char buffer[16];
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
       //scanf("%d", &opcion);
       // while(getchar() != '\n'); // Limpiar buffer
        if (fgets(buffer,sizeof(buffer),stdin) != NULL)
            opcion = atoi(buffer);
        else
            opcion = 0;
        
        switch(opcion) {
            case 1:
                crear_encuesta(tope);
                clear_screen();
                break;
            case 2:
                //mostrar_encuesta(tope);
                //clear_screen();
                mostrar_encuesta(tope,1);
                fgets(buffer, sizeof(buffer), stdin);
                clear_screen();
                break;
            case 3:
                //actualizar encuesta
                clear_screen();
                break;
            case 4:
                //eliminar encuesta
                eliminar_encuesta(tope);
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

//Muestra solamente las encuestas, sin las preguntas de dicha encuesta.
void mostrar_encuesta(encuestas **tope, int interactivo) {
    encuestas *nodo_desapilado = NULL;
    encuestas *aux = NULL;
    int opcion;

    clear_screen();
    printf("=================================\n");
    printf("       LISTA DE ENCUESTAS        \n");
    printf("=================================\n\n");

    if (vacia(tope)) {
        printf("No hay encuestas cargadas.\n");

        if (interactivo) {
            printf("\nPresione ENTER para volver al menu...");
            getchar(); // Espera ENTER
        }

        return;
    }

    // Mostrar encuestas
    while (!vacia(tope)) {
        desapilar(tope, &nodo_desapilado);
        printf("ID encuesta: %d\n", nodo_desapilado->encuesta_id);
        printf("Denominacion: %s\n", nodo_desapilado->denominacion);
        printf("Fecha: %d/%d\n", nodo_desapilado->encuesta_mes, nodo_desapilado->encuesta_anio);
        printf("Procesada: %d\n", nodo_desapilado->procesada);
        printf("-----------------------------\n");
        apilar(&aux, &nodo_desapilado);
    }

    // Restaurar la pila original
    while (!vacia(&aux)) {
        desapilar(&aux, &nodo_desapilado);
        apilar(tope, &nodo_desapilado);
    }

    // Menú interactivo solo si se indica
    if (interactivo) {
        char buffer[16];
        do {
            printf("\nQue desea hacer?\n");
            printf("1. Volver al menu principal\n");
            printf("2. Volver a mostrar encuestas\n");
            printf("Opcion: ");

            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                opcion = 1;
            } else {
                opcion = atoi(buffer);
            }

            switch (opcion) {
                case 1:
                    return;
                case 2:
                    // Evita recursión profunda: hacer bucle
                    clear_screen();
                    mostrar_encuesta(tope, 1);
                    return;
                default:
                    printf("Opcion no valida. Intente nuevamente.\n");
            }

        } while (opcion != 1 && opcion != 2);
    }
}

void crear_encuesta(encuestas **tope) {
    int opcion;
    char buffer[64]; 

    do {
        printf("=================================\n");
        printf("          CREAR ENCUESTA         \n");
        printf("=================================\n\n");

        encuestas* nueva = (encuestas*)malloc(sizeof(encuestas));
        if (nueva == NULL) {
            printf("No hay espacio en memoria\n");
            return;
        }

        // Validar ID único
        nueva->encuesta_id = leerNumeroValidado(
            "Ingrese ID de la encuesta: ",
            "ID no valido",
            1, INT_MAX,  // Rango para ID (1 a máximo entero)
            true,        // Validar que sea único
            tope
        );

        // Leer denominación
        printf("Ingrese denominacion: ");
        if (fgets(nueva->denominacion, sizeof(nueva->denominacion), stdin) != NULL) {
            nueva->denominacion[strcspn(nueva->denominacion, "\n")] = '\0';
        }

        // Validar mes (1-12)
        nueva->encuesta_mes = leerNumeroValidado(
            "Ingrese mes (1-12): ",
            "Mes no valido",
            1, 12,
            false,  // No validar unicidad para el mes
            NULL
        );

        // Validar año (asumimos años entre 2000-2100)
        nueva->encuesta_anio = leerNumeroValidado(
            "Ingrese anio (2000-2100): ",
            "Anio no valido",
            2000, 2100,
            false,  // No validar unicidad para el año
            NULL
        );

        nueva->procesada = 0;
        nueva->sgte = NULL;

        apilar(tope, &nueva);
        printf("\nEncuesta creada y apilada con exito!\n");

        // Menú de opciones después de crear
        printf("\nQue desea hacer ahora?\n");
        printf("1. Crear otra encuesta\n");
        printf("2. Volver al menu encuestas\n");
        printf("0. Salir del programa\n");
        printf("Seleccione una opcion: ");

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            opcion = atoi(buffer);
        } else {
            opcion = 2;  // Opción por defecto si hay error
        }

        switch (opcion) {
            case 1:
                clear_screen();
                break;
            case 2:
                clear_screen();
                return;
            case 0:
                printf("\nSaliendo del programa...\n");
                exit(0);
            default:
                printf("\nOpcion no valida. Volviendo al menu principal.\n");
                clear_screen();
                return;
        }
    } while (opcion == 1);
}

void eliminar_encuesta(encuestas **tope) {
    int opcion;
    char buffer[64];

    do {
        clear_screen();
        printf("=================================\n");
        printf("       ELIMINAR ENCUESTA         \n");
        printf("=================================\n\n");

        // Verificar si hay encuestas primero
        if (vacia(tope)) {
            printf("No hay encuestas para eliminar.\n");
            
            // Menú interactivo incluso cuando no hay encuestas
            printf("\nQue desea hacer ahora?\n");
            printf("1. Volver al menu de encuestas\n");
            printf("0. Salir del programa\n");
            printf("Seleccione una opcion: ");
            
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                opcion = 1; // Valor por defecto si hay error
            } else {
                opcion = atoi(buffer);
            }

            switch (opcion) {
                case 1:
                    clear_screen();
                    return;
                case 0:
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                default:
                    printf("\nOpcion no valida. Volviendo al menu de encuestas.\n");
                    clear_screen();
                    return;
            }
        }

        // Mostrar todas las encuestas
        mostrar_encuesta(tope,0);
        
        // Resto del código de eliminación
        int id_a_eliminar;
        char confirmacion;
        bool encontrada = false;
        
        encuestas *temp = NULL;
        encuestas *nodo = NULL;
        encuestas *nodo_eliminar = NULL;
        
        printf("\nIngrese el ID de la encuesta a eliminar (0 para cancelar): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error al leer la entrada.\n");
            continue;
        }
        id_a_eliminar = atoi(buffer);
        
        if (id_a_eliminar == 0) {
            clear_screen();
            return;
        }

        encontrada = false;
        while (!vacia(tope)) {
            desapilar(tope, &nodo);
            
            if (nodo->encuesta_id == id_a_eliminar) {
                encontrada = true;
                
                // Verificar si la encuesta ya fue procesada
                if (nodo->procesada == 1) {
                    printf("\nNo se puede eliminar la encuesta porque ya ha sido procesada.\n");
                    apilar(&temp, &nodo);
                    break;
                }
                
                nodo_eliminar = nodo;
                
                printf("\nEncuesta seleccionada para eliminar:\n");
                printf("ID: %d\n", nodo->encuesta_id);
                printf("Denominacion: %s\n", nodo->denominacion);
                printf("Fecha: %d/%d\n", nodo->encuesta_mes, nodo->encuesta_anio);
                
                printf("\nEsta seguro que desea eliminar esta encuesta? (s/n): ");
                if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                    printf("Error al leer la entrada.\n");
                    apilar(&temp, &nodo);
                    continue;
                }
                confirmacion = buffer[0];
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    free(nodo_eliminar);
                    printf("\nEncuesta eliminada con exito.\n");
                } else {
                    apilar(&temp, &nodo);
                    printf("\nEliminacion cancelada.\n");
                }
            } else {
                apilar(&temp, &nodo);
            }
        }
        
        while (!vacia(&temp)) {
            desapilar(&temp, &nodo);
            apilar(tope, &nodo);
        }
        
        if (!encontrada && id_a_eliminar != 0) {
            printf("\nNo se encontro una encuesta con el ID %d.\n", id_a_eliminar);
        }

        // Menú interactivo después de cualquier operación
        printf("\nQue desea hacer ahora?\n");
        printf("1. Eliminar otra encuesta\n");
        printf("2. Volver al menu de encuestas\n");
        printf("0. Salir del programa\n");
        printf("Seleccione una opcion: ");
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            opcion = 2;
        } else {
            opcion = atoi(buffer);
        }

        switch (opcion) {
            case 1:
                break; // Continuará en el bucle
            case 2:
                clear_screen();
                return;
            case 0:
                printf("\nSaliendo del programa...\n");
                exit(0);
            default:
                printf("\nOpcion no valida. Volviendo al menu de encuestas.\n");
                clear_screen();
                return;
        }
        
    } while (1); // Bucle infinito (se controla con las opciones)
}

// Función para verificar si un ID ya existe en la pila
bool idExiste(encuestas *tope, int id) {
    encuestas *temp = NULL;
    encuestas *nodo = NULL;
    bool existe = false;
    
    // Desapilar y verificar, apilando en temporal
    while (!vacia(&tope)) {
        desapilar(&tope, &nodo);
        if (nodo->encuesta_id == id) {
            existe = true;
        }
        apilar(&temp, &nodo);
    }
    
    // Restaurar la pila original
    while (!vacia(&temp)) {
        desapilar(&temp, &nodo);
        apilar(&tope, &nodo);
    }
    
    return existe;
}

int leerNumeroValidado(const char *mensaje, const char *mensajeError, int min, int max, bool validarUnico, encuestas **tope) {
    char buffer[64];
    int numero;
    bool entradaValida = false;
    
    do {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error al leer la entrada.\n");
            continue;
        }
        
        // Verificar si la entrada es numérica
        char *endptr;
        numero = strtol(buffer, &endptr, 10);
        
        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
            printf("Error: Debe ingresar un numero valido.\n");
            continue;
        }
        
        // Validar rango
        if (numero < min || numero > max) {
            printf("%s (Debe estar entre %d y %d)\n", mensajeError, min, max);
            continue;
        }
        
        // Validar ID único si es necesario
        if (validarUnico && idExiste(*tope, numero)) {
            printf("Error: El ID %d ya existe. Ingrese un ID unico.\n", numero);
            continue;
        }
        
        entradaValida = true;
    } while (!entradaValida);
     
    return numero;
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


//CRUD RESPUESTAS --------------->
respuestas *inicioRespuestas = NULL; //puntero de manera global para la lista enlazada circular
void crearRespuesta(){

	int parar = 1, num = 0, verificar = 0;
	respuestas *ini = NULL, *iniListaAux = NULL, *iniListaAuxAux = NULL;
	ini = inicioRespuestas;
	printf("=================================\n");
	printf("          CREAR RESPUESTA        \n");
	printf("=================================\n");
	printf("\n");

	printf("Ingrese el id de pregunta al que desea crearle la respuesta\n");
	scanf("%d",&num);
	printf("num leido: %d\n", num);

	//verificar = verificarPregunta(num /*puntero al incio de la lista enlazada simple*/);
	if(verificar == 1){
		printf("El id de la respuesta ingresada no existe\n");
	}
		else { 
			do {
				respuestas *aux = (respuestas*)malloc(sizeof(respuestas));
				aux->pregunta_id = num;
				printf("pregunta_id guardada: %d\n", aux->pregunta_id);
				//buscamos el ultimo id de respuesta creado y le sumamos 1
				if(inicioRespuestas == NULL && iniListaAux == NULL){
					aux->respuesta_id = 1;
				} 
				else {
					if(iniListaAux == NULL){
						do {  
							ini = ini->sgte;
						} while (ini->sgte != inicioRespuestas);
						aux->respuesta_id = ini->respuesta_id + 1;
					}	 
					else {
						aux->respuesta_id = iniListaAuxAux->respuesta_id + 1;
					}
				}
			
			
				printf("Ingrese el numero de respuesta\n");
				scanf("%d",&(aux->respuesta_nro));
				while(getchar() != '\n'); // Limpiar buffer

				printf("Ingrese la respuesta deseada\n");
				fgets(aux->respuesta, 100, stdin);
				aux->respuesta[strcspn(aux->respuesta, "\n")] = '\0';

				
				do {
        			printf("Ingrese la ponderacion de la respuesta (recuerde que al menos una respuesta debe valer 1)\n");
        			scanf("%f",&(aux->ponderacion));
					while(getchar() != '\n'); // Limpiar buffer

					if(aux->ponderacion < 0 || aux->ponderacion > 1){
						printf("por favor ingrese un numero entre 0 y 1");
					}

    			} while (aux->ponderacion < 0 || aux->ponderacion > 1);
				
		
				//agregamos el nodo a la estructura auxiliar para que despues de que se termine de cargar las respuestas verificar si da 1 la ponderacion
				if(iniListaAux == NULL){
				iniListaAux = aux;
				iniListaAux->sgte = NULL;
				iniListaAuxAux = iniListaAux;
				aux = NULL;
				} else {
				iniListaAuxAux->sgte = aux;
				aux = NULL;
				iniListaAuxAux = iniListaAuxAux->sgte;
				iniListaAuxAux->sgte = NULL;
				}	
			
				printf("Desea cargar otra respuesta? 1 (si) / 0 (no)\n");
				scanf("%i",&parar);
				while(getchar() != '\n'); // Limpiar buffer

			} while(parar != 0);	
		}   
	
	//verificamos si hay alguna respuesta que valga 1
	verificar = 0;
	iniListaAuxAux = iniListaAux;
	if(iniListaAuxAux->sgte == NULL){
		if(iniListaAuxAux->ponderacion == 1){
			verificar = 1;
		} }
		else {
			while(iniListaAuxAux->sgte != NULL){
			if(iniListaAuxAux->ponderacion == 1){
				verificar = 1;
			} 
				iniListaAuxAux = iniListaAuxAux->sgte;
			}
			if(iniListaAuxAux->ponderacion == 1){
				verificar = 1;
			} 
		}
	
	//enlazamos la lista simple auxiliar a la lista circular principal
	if(verificar == 1 && inicioRespuestas == NULL){
		inicioRespuestas = iniListaAux;
		iniListaAux = NULL;
		iniListaAuxAux->sgte = inicioRespuestas;
		iniListaAuxAux = NULL;
		printf("Respuestas cargadas con exito\n");
	}
		else if(verificar == 1 && inicioRespuestas != NULL){
			ini->sgte = iniListaAux;
			iniListaAux = NULL;
			iniListaAuxAux->sgte = inicioRespuestas;
			iniListaAuxAux = NULL;
			printf("Respuestas cargadas con exito\n");
		} else{
			printf("No hay ninguna respuesta que valga 1. No se pudieron cargar las respuestas al sistema\n");
			//borramos la lista auxiliar
			iniListaAuxAux = iniListaAux;
			while(iniListaAux != NULL){
				iniListaAux = iniListaAux->sgte;
				free(iniListaAuxAux);
				iniListaAuxAux = iniListaAux;
			}
		} 		
}

void mostrarRespuestas(){
	respuestas *aux = NULL;
	if(inicioRespuestas != NULL){
			aux = inicioRespuestas;
		do
		{
			printf("Respuesta con el id: %d. '%s'. Numero de respuesta: %d, a la pregunta: %d. Pondera con: %.2f\n", aux->respuesta_id, aux->respuesta, aux->respuesta_nro, aux->pregunta_id, aux->ponderacion);
			aux = aux->sgte;
		} while (aux != inicioRespuestas);
	} else printf("No hay ninguna respuesta cargada en el sistema\n");	
	
}

void eliminarRespuestas(){
	respuestas *bor = NULL, *ant = NULL, *ultimo = NULL;
	int borrar, num, borrado=0;

	printf("Ingrese el id de la pregunta a la que le desea borrar las respuestas\n");
	scanf("%d", &num);

	if(inicioRespuestas != NULL){
		bor = inicioRespuestas;
		borrar = 0;
		buscarBorrar(num, &bor, &ant, &borrar);

		while(bor != inicioRespuestas){
			if(bor->pregunta_id == num){
				ant->sgte = bor->sgte;
				bor->sgte = NULL;
				free(bor);
				bor = ant->sgte;
				borrado = 1;
			} else bor = bor->sgte;
		}
		

		if(bor->pregunta_id == num){ //si necesitamos borrar el primero nodo que quedo solitario
			if(inicioRespuestas->sgte == inicioRespuestas){ //condicion que analiza si hay 1 solo nodo en la lista
				inicioRespuestas = NULL;
				ant = NULL;
				free(bor);
				bor = NULL;
				borrado = 1;
			}
			else{
				ultimo = inicioRespuestas;
				while(ultimo->sgte != inicioRespuestas){
					ultimo = ultimo->sgte; //busco el ultimo nodo para engancharlo al comienzo despues
				}
				inicioRespuestas = inicioRespuestas->sgte; //cambio el inicio de la lista para poder borrar el primer nodo
				ultimo->sgte = inicioRespuestas; //el ulitmo nodo apunta al inicio de vuelta
				bor->sgte = NULL;
				ant = NULL;
				free(bor); //libero el primer nodo
				bor = NULL;
				borrado = 1;
			}
		}
		if(borrado){
			printf("Se borraron las respuestas exitosamente\n");
		} else printf("El id a borrar no existe");
	} 	else printf("No hay nada para borrar la lista esta vacia\n");
} 

void buscarBorrar(int num, respuestas **rc, respuestas **ant, int *borrar){
	respuestas *aux;
	(*ant) = (*rc);
	aux = (*rc);
	(*rc) = (*rc)->sgte;
	while((*rc) != aux && *borrar != 1){
			if((*rc)->pregunta_id == num){
				*borrar = 1;
			} else{
				(*ant) = (*rc);
				(*rc) = (*rc)->sgte;
			}
	}
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
