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
    int pregunta_id;
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
    int encuesta_id;
    struct preguntas *pregunta_id;
    struct respuestas *respuesta_id;
    int fecha_realizacion;
    sEncuestador *encuestador_id;
    int encuestarResondida_id;
    struct encuestaRespondidas *sgte;
}encuestaRespondidas;

typedef struct nodoABB {
    int idEncuesta;
	int idEncustaRespondida;
	struct nodoABB* izq;
	struct nodoABB* der;
}nodoABB;

//Funciones de menu y login
void menu_encuestas(encuestas **tope, encuestaRespondidas** listaEncuestasResp); //Roy Ruiz
void menu_preguntas(encuestas* tope); //Roy Ruiz
void menu_respuestas(encuestaRespondidas** listaRespondidas, sEncuestador* listaEncuestadores, encuestas** tope); //Roy Ruiz
void menu_administrador(encuestas **tope, sEncuestador** listaEncuestadores, encuestaRespondidas** listaEncuestasResp); //Roy Ruiz
void menu_encuestador(encuestas** tope, sEncuestador* listaEncuestadores, encuestaRespondidas** listaRespondidas); //Roy Ruiz
void menu_AdmEncuestadores(sEncuestador** listaEncuestadores); //Roy Ruiz
int login(sEncuestador* lista); // Roy Ruiz
// Funciones de manejo de encuestas
void mostrar_encuesta(encuestas **tope,int interactivo); // Pitter Dos Santos
void crear_encuesta(encuestas **tope); // Pitter Dos Santos
void eliminar_encuesta(encuestas **tope); // Pitter Dos Santos
void apilar(encuestas **tope, encuestas **nv); // Pitter Dos Santos
void desapilar(encuestas **tope, encuestas **nodo_desapilado); // Pitter Dos Santos
int vacia(encuestas **tope); // Pitter Dos Santos
bool idExiste(encuestas *tope, int id); // Pitter Dos Santos
int leerNumeroValidado(const char *mensaje, const char *mensajeError, int min, int max, bool validarUnico, encuestas **tope); // Pitter Dos Santos
void agregarEncuestador(sEncuestador** lista); // Roy Ruiz
void limpiarBuffer(); // Roy Ruiz
void mostrarEncuestasRespondidasPorID(encuestaRespondidas* listaRespondidas, encuestas** topeEncuestas); // Pitter Dos Santos

int encuestaCompleta(int encuesta_id); // Roy Ruiz

// Funciones de csv
encuestaRespondidas* cargarEncuestasRespondidas(
    encuestaRespondidas* lista, 
    sEncuestador* listaEncuestadores,
    encuestas** topePila
); //Roy Ruiz

encuestaRespondidas* cargarManualEncuestaRespondida(
    encuestaRespondidas* lista, 
    sEncuestador* listaEncuestadores,
    encuestas *tope
); //Roy Ruiz

preguntas* buscarPregunta(int id_pregunta); //Roy Ruiz
respuestas* buscarRespuesta(int id_respuesta); //Roy Ruiz
sEncuestador* buscarEncuestador(sEncuestador* lista, int id); //Roy Ruiz
void mostrarEncuestasRespondidas(encuestaRespondidas* lista); //Roy Ruiz
int esEncuestaRespondidaDuplicada(encuestaRespondidas* lista, encuestaRespondidas* nodo); //Roy Ruiz

//Funciones del plantin
void buscarIdsParaABB(encuestaRespondidas* inicio, encuestas* tope); // Santiago Halberstadt
bool verificarSiExisteNodo(nodoABB* raiz, int id); // Santiago Halberstadt
void crecer(nodoABB** raiz, nodoABB** aux); // Santiago Halberstadt
void PrintearInOrder(nodoABB* raiz); // Santiago Halberstadt
void borrarArbol(nodoABB** raiz); // Santiago Halberstadt

// Funciones para cargar datos de ejemplo
void agregarPregunta(int encuesta_id, int pregunta_id, const char* pregunta, float ponderacion); // Roy Ruiz
void agregarRespuesta(int pregunta_id, int respuesta_id, int respuesta_nro, const char* respuesta, float ponderacion); // Roy Ruiz
void cargarDatosEjemplo(encuestas** topeEncuestas); // Roy Ruiz


// Funciones para CRUD de preguntas
void insertarInicio(preguntas** Ini, preguntas*nodo); //Santiago Halberstadt
int obtenerIdPregunta(preguntas* InicioLista); //Santiago Halberstadt
void crearPreguntas(encuestas* tope); //Santiago Halberstadt
void mostrarPreguntas(int idEncuesta, encuestas* tope, preguntas* inicioListaPreguntas); //Santiago Halberstadt
void eliminarPregunta(preguntas** Ini, int idEncuesta); //Santiago Halberstadt
bool validarIdEncuesta(encuestas** tope, int id); //Santiago Halberstadt
bool verificarProcesado(encuestas** tope, int id); //Santiago Halberstadt
bool verificarPreguntas(preguntas* inicioListaPreguntas, int id); //Santiago Halberstadt

// Funciones para CRUD de respuestas
void crearRespuesta(encuestas** tope); // Martin Kalesplaner
void mostrarRespuestas(); // Martin Kalesplaner
void eliminarRespuestas(int); // Martin Kalesplaner
void buscarBorrar(int num, respuestas **, respuestas **, int *); // Martin Kalesplaner
void mostrarEncuestadores(sEncuestador* actual);  // Martin Kalesplaner
int verificarIdPregunta(int num, preguntas **); // Martin Kalesplaner
int num_pregunta(int num); // Martin Kalesplaner
bool idSinProcesar(encuestas *tope, int num); // Martin Kalesplaner

// Funciones ponderar encuestas
void ponderarEncuesta(encuestaRespondidas *lista, encuestas **topePila); //Martin Kalesplaner
void ponderarEncuestaId(encuestaRespondidas *lista); //Martin Kalesplaner

preguntas* inicioPreguntas = NULL; //puntero de manera global para la lista enlazada simple 
int main() {
    sEncuestador* listaEncuestadores = NULL;
    encuestas *tope = NULL;
    encuestaRespondidas* listaRespondidas = NULL;

    int control;

    //carga de un encuestador para prueba
    struct sEncuestador* nodo = NULL;
    nodo = malloc(sizeof(struct sEncuestador));
    nodo->encuestador_id = 9999;
    strcpy(nodo->nombre, "Garrafa Sanchez");
    strcpy(nodo->pass, "taladro10");
    nodo->sgte = NULL;
    listaEncuestadores = nodo;
    nodo = NULL;


    //carga de datos de ejemplo
    //cargarDatosEjemplo(&tope);
    
    do{
        control = login(listaEncuestadores);

        if(control == 2){
            clear_screen();
            menu_administrador(&tope, &listaEncuestadores, &listaRespondidas);
        }
        if(control == 1){
            clear_screen();
            menu_encuestador(&tope, listaEncuestadores, &listaRespondidas);
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

void menu_administrador(encuestas **tope, sEncuestador** listaEncuestadores, encuestaRespondidas** listaEncuestasResp){
       int opcion;
    
    do {
        printf("=================================\n");
        printf("        MENU ADMINISTRADOR       \n");
        printf("=================================\n");
        printf("1. Encuestas\n");
        printf("2. Preguntas\n");
        printf("3. Respuestas\n");
        printf("4. Encuestadores\n");
        printf("5. Crear arbol binario\n");
        printf("0. Salir\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                clear_screen();
                menu_encuestas(tope, listaEncuestasResp);
                break;
            case 2:
                clear_screen();
                menu_preguntas(*tope);
                break;
            case 3:
                clear_screen();
                menu_respuestas(listaEncuestasResp, *listaEncuestadores, tope);
                break;
            case 4:
                clear_screen();
                menu_AdmEncuestadores(listaEncuestadores);
                break;
            case 5:
                clear_screen();
                buscarIdsParaABB(*listaEncuestasResp, *tope);
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

void menu_AdmEncuestadores(sEncuestador** listaEncuestadores){
int opcion;
    
    do {
        printf("=================================\n");
        printf("        MENU ENCUESTADORES       \n");
        printf("=================================\n");
        printf("1. Agregar encuestador\n");
        printf("2. Mostrar encuestadores\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                agregarEncuestador(listaEncuestadores);
                clear_screen();
                break;
            case 2:
                clear_screen();
                mostrarEncuestadores((*listaEncuestadores));
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

void menu_encuestador(encuestas** tope, sEncuestador* listaEncuestadores, encuestaRespondidas** listaRespondidas) {
    int opcion;
    
    do {
        printf("\n=================================\n");
        printf("        MENU ENCUESTADOR         \n");
        printf("=================================\n");
        printf("1. Cargar respuestas desde archivo CSV\n");
        printf("2. Ingresar respuestas manualmente\n");
        printf("3. Mostrar todos los registros de encuestas respondidas\n");
        printf("4. Calcular ponderaciones\n");
        printf("5. Calcular ponderacion especifica (por ID)\n");
        printf("6. Crear arbol binario de una determinada encuesta\n");
        printf("7. Mostrar encuesta especifica (por ID)\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                clear_screen();
                printf("\n--- Cargar desde CSV ---\n");
                *listaRespondidas = cargarEncuestasRespondidas(*listaRespondidas, listaEncuestadores, tope);
                break;
            case 2:
                clear_screen();
                printf("\n--- Ingreso manual ---\n");
                *listaRespondidas = cargarManualEncuestaRespondida(*listaRespondidas, listaEncuestadores, *tope);
                break;
            case 3:
                clear_screen();
                printf("\n--- Todas las encuestas ---\n");
                mostrarEncuestasRespondidas(*listaRespondidas);
                break;
            case 4:
                clear_screen();
                printf("\n--- Ponderaciones ---\n");
                ponderarEncuesta(*listaRespondidas, tope);
                break;
            case 5:
                clear_screen();
                printf("\n--- Ponderacion por ID ---\n");
                ponderarEncuestaId(*listaRespondidas);
                break;
            case 6:
                clear_screen();
                buscarIdsParaABB(*listaRespondidas, *tope);
                break;
            case 7:
                printf("\n--- Buscar por ID ---\n");
                mostrarEncuestasRespondidasPorID(*listaRespondidas,tope);
                clear_screen();
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

void menu_encuestas(encuestas **tope, encuestaRespondidas** listaEncuestasResp) {
    int opcion;
    char buffer[16];
    int encuesta_id;
    do {
        printf("=================================\n");
        printf("          MENU ENCUESTAS         \n");
        printf("=================================\n");
        printf("1. Crear encuesta\n");
        printf("2. Mostrar encuestas\n");
        printf("3. Verificar que las encuestas esten completas.\n");
        printf("4. Eliminar encuesta\n");
        printf("5. Calcular ponderacion\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
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
                mostrar_encuesta(tope, 0);
                printf("\nQue encuesta quiere verificar si esta completa?: ");
                scanf("%d", &encuesta_id);
                if(idExiste(*tope, encuesta_id)){
                    //clear_screen();
                    encuestaCompleta(encuesta_id);
                }
                else{
                    //clear_screen();
                    printf("Esa encuesta no existe.\n");
                }
                break;
            case 4:
                //eliminar encuesta
                eliminar_encuesta(tope);
                clear_screen();
                break;
            case 5:
                clear_screen();
                ponderarEncuesta(*listaEncuestasResp, tope);
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

void menu_preguntas(encuestas* tope) {
    int opcion, idMostrar;
    
    do {
        printf("\n=================================\n");
        printf("          MENU PREGUNTAS         \n");
        printf("=================================\n");
        printf("1. Crear pregunta\n");
        printf("2. Mostrar preguntas\n");
        printf("3. Eliminar pregunta\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                crearPreguntas(tope);
                //clear_screen();
                break;
            case 2:
                mostrar_encuesta(&tope, 0);
				printf("Ingrese el ID de la encuesta para mostrar sus preguntas: ");
				scanf("%d", &idMostrar);
                clear_screen();
				mostrarPreguntas(idMostrar, tope, inicioPreguntas);
                //clear_screen();
                break;
            case 3:
                mostrar_encuesta(&tope, 0);
				printf("Ingrese el ID de la encuesta para eliminar sus preguntas: ");
				scanf("%d", &idMostrar);
                eliminarPregunta(&inicioPreguntas, idMostrar);
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

void menu_respuestas(encuestaRespondidas** listaRespondidas, sEncuestador* listaEncuestadores, encuestas** tope) {
    int opcion;
    int num;
    do {
        printf("=================================\n");
        printf("         MENU RESPUESTAS         \n");
        printf("=================================\n");
        printf("1. Crear respuesta\n");
        printf("2. Mostrar respuestas\n");
        printf("3. Eliminar respuesta\n");
        printf("4. Cargar respuestas desde .CSV\n");
        printf("5. Cargar encuestas respondidas manualmente\n");
        printf("6. Mostrar encuestas respondidas\n");
        printf("0. Volver al menu principal\n");
        printf("=================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n'); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                clear_screen();
                crearRespuesta(tope);
                break;
            case 2:
                clear_screen();
                mostrarRespuestas();
                break;
            case 3:
                printf("Ingrese el id de la pregunta a la que le desea borrar las respuestas\n");
	            scanf("%d", &num);
                eliminarRespuestas(num);
                clear_screen();
                break;
            case 4:
                clear_screen();
                *listaRespondidas = cargarEncuestasRespondidas(*listaRespondidas, listaEncuestadores, tope);
                break;
            case 5:
                clear_screen();
                *listaRespondidas = cargarManualEncuestaRespondida(*listaRespondidas, listaEncuestadores, *tope);
                break;
            case 6:
                clear_screen();
                mostrarEncuestasRespondidas(*listaRespondidas);
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
            printf("\nPresione dos veces ENTER para volver al menu...");
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
            printf("Opcion (debe tocar enter 2 veces): ");

            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                opcion = 1;
            } else {
                opcion = atoi(buffer);
            }

            // no entiendo por que aca hay que poner enter 2 veces!!!!!!!!!!!!!!!!!!!
            // esto con python no pasaba....

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
        printf("0. Volver al menu encuestas\n");
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
            case 0:
                clear_screen();
                return;
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
                    eliminarPregunta(&inicioPreguntas, nodo_eliminar->encuesta_id);
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

bool idSinProcesar(encuestas *tope, int id) {
    encuestas *temp = NULL;
    encuestas *nodo = NULL;
    bool existe = false;
    
    // Desapilar y verificar, apilando en temporal
    while (!vacia(&tope)) {
        desapilar(&tope, &nodo);
        if (nodo->encuesta_id == id && nodo->procesada == 0) {
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

void mostrarEncuestadores(sEncuestador* actual) {
    
    printf("Lista de encuestadores:\n");
    printf("-----------------------\n");
    
    
    if (actual == NULL) {
        printf("La lista está vacía.\n");
    }
    while (actual != NULL) {
        printf("ID: %d\n", actual->encuestador_id);
        printf("Nombre: %s\n", actual->nombre);
        printf("Password: %s\n", actual->pass);
        printf("-----------------------\n");
        
        actual = actual->sgte;  // Avanzar al siguiente nodo
    }
}

void agregarEncuestador(sEncuestador** lista) {
    // Crear nuevo nodo
    sEncuestador* nuevo = (sEncuestador*)malloc(sizeof(sEncuestador));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }

    char nombre[30], pass[15];
    int lectura_correcta, id;

    do {
        printf("Ingrese el nombre del encuestador (sin espacios, max 29 chars): ");
        lectura_correcta = scanf("%29s", nombre);  // %29s para dejar espacio para el '\0'
        limpiarBuffer();
        if (lectura_correcta != 1) {
            printf("Error en la lectura. ");
        }
    } while (lectura_correcta != 1);


    // Lectura de id
    do {
        printf("Ingrese el id del encuestador: ");
        lectura_correcta = scanf("%d", &id);  // %14s para dejar espacio para el '\0'
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
    nuevo->encuestador_id = id;
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->pass, pass);

    // Insertar al inicio de la lista
    nuevo->sgte = *lista;
    *lista = nuevo;
}


//CRUD RESPUESTAS --------------->
respuestas *inicioRespuestas = NULL; //puntero de manera global para la lista enlazada circular
void crearRespuesta(encuestas** tope){

	int parar = 1, num = 0, verificar = 0, contador = 0, control = 0, numEncuesta = 0;
	respuestas *ini = NULL, *iniListaAux = NULL, *iniListaAuxAux = NULL;
	ini = inicioRespuestas;
	printf("=================================\n");
	printf("          CREAR RESPUESTA        \n");
	printf("=================================\n");
	printf("\n");


    mostrar_encuesta(tope, 0);
    printf("Ingrese el id de encuesta al que desea agregar respuestas.\n");
	scanf("%d",&numEncuesta);
    
    if(!idSinProcesar(*tope, numEncuesta)){
        printf("Error, no existe ese id de encuesta o la encuesta ya fue procesada.\n");
        return;
    } 

    printf("Preguntas disponibles: \n");
    preguntas* auxLista = inicioPreguntas, *auxLista1 = NULL;
    while(auxLista!= NULL){
        if(auxLista->encuesta_id == numEncuesta){
            control = 1;
            printf("\n'%s'\nID: %d\n", auxLista->pregunta, auxLista->pregunta_id);
        }
        auxLista = auxLista->sgte;
    }

    if(control == 0){
        printf("No hay preguntas disponibles en la encuesta para crear respuestas.\n");
    } else {
        printf("Ingrese el id de pregunta al que desea crearle la respuesta\n");
	    scanf("%d",&num);
	    verificar = verificarIdPregunta(num, &inicioPreguntas);
        auxLista1 = buscarPregunta(num);

	if(verificar != 1){
		printf("El id de la respuesta ingresada no existe\n");
	} else if(auxLista1->encuesta_id != numEncuesta){
        printf("El id de respuesta no es de esta encuesta\n");
    }
		else { 
            printf("ENTRE ACA Y DIO QUILOMBO");
            contador = num_pregunta(num);
            if(contador != 0){
                verificar = 1;
            } else verificar = 0;

			do {
				respuestas *aux = (respuestas*)malloc(sizeof(respuestas));
				aux->pregunta_id = num;
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
			
                contador = contador + 1;
				aux->respuesta_nro = contador;
				
                while(getchar() != '\n'); //limpiar el buffer porque da quilombo aca
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

			} while(parar != 0);	

        //verificamos si hay alguna respuesta que valga 1
	    iniListaAuxAux = iniListaAux;
	    if(iniListaAuxAux->sgte == NULL){
		    if(iniListaAuxAux->ponderacion == 1){
			    verificar = 1;
		    } 
        }
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
	    if(verificar == 1 && inicioRespuestas == NULL && contador >= 2){
		    inicioRespuestas = iniListaAux;
		    iniListaAux = NULL;
		    iniListaAuxAux->sgte = inicioRespuestas;
		    iniListaAuxAux = NULL;
		    printf("Respuestas cargadas con exito\n");
	    }
		else if(verificar == 1 && inicioRespuestas != NULL && contador >= 2){
			ini->sgte = iniListaAux;
			iniListaAux = NULL;
			iniListaAuxAux->sgte = inicioRespuestas;
			iniListaAuxAux = NULL;
			printf("Respuestas cargadas con exito\n");
		} else{
			printf("Error, no se pudieron cargar las respuestas al sistema.\n No hay ninguna respuesta que valga 1 en la ponderacion o solo cargo 1 respuesta. \n");
			//borramos la lista auxiliar
			iniListaAuxAux = iniListaAux;
			while(iniListaAux != NULL){
				iniListaAux = iniListaAux->sgte;
				free(iniListaAuxAux);
				iniListaAuxAux = iniListaAux;
			}
		} 		
	}  
    }
}

int verificarIdPregunta(int num, preguntas **inicioPreguntas){
    preguntas *aux = NULL;
    int verificar = 0;
    aux = (*inicioPreguntas);
    while ((aux != NULL) && (verificar != 1))
    {
        if(aux->pregunta_id == num){
            verificar = 1;
        } else aux = aux->sgte;
    }
    return verificar;
}

int num_pregunta(int num){
    int wep = 0;
    if(inicioRespuestas == NULL){
        wep = 0;
    } else{
            respuestas *aux = inicioRespuestas;
        do
        {
            if(aux->pregunta_id == num){
                wep = aux->respuesta_nro;
            }
            aux = aux->sgte;
    } while(aux != inicioRespuestas);
    }
    return wep;
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

void eliminarRespuestas(int num){
	respuestas *bor = NULL, *ant = NULL, *ultimo = NULL;
	int borrar, borrado=0;

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

//CRUD PREGUNTAS --------------->

void insertarInicio(preguntas** Ini, preguntas* nodo) {
    nodo->sgte = *Ini;
	*Ini = nodo;
}

int obtenerIdPregunta(preguntas* inicio) {
    int Id = 0;
    while (inicio != NULL) {
        if (inicio->pregunta_id > Id) {
            Id = inicio->pregunta_id;
        }
        inicio = inicio->sgte;
    }
    return Id + 1;
}

void crearPreguntas(encuestas* tope) {
#define EPSILON 0.001
    char pregunta[100];
    int idEncuesta;
    float ponderacionPregunta, ponderacionDisponible = 0, suma=0;

    do {
        mostrar_encuesta(&tope, 0);
        printf("\nIngrese el id de la encuesta a la que le desea cargar preguntas (-1 salir): ");
        scanf("%d", &idEncuesta);

        if (idEncuesta != -1) {

            if (validarIdEncuesta(&tope, idEncuesta) == true) { //validar q no sea un id q no existe

                if (verificarProcesado(&tope, idEncuesta) == true) { //validar q no este procesada ya

                    if (verificarPreguntas(inicioPreguntas, idEncuesta) == true) { //validar q no tenga preguntas, dar opcion de borrar

                        ponderacionDisponible = 1; //reiniciamos la ponderacion disponible y cuanto suma cada pregunta por cada encuesta con la q trabajamos
                        suma = 0;

                        do {

                            preguntas* nv_nodo = (preguntas*)malloc(sizeof(preguntas));

                            if (nv_nodo != NULL) { //validar q se pueda crear el nodo

                               (nv_nodo->pregunta_id = obtenerIdPregunta(inicioPreguntas)); //id automatico

                                printf("\nIngrese la pregunta id:%d: ", nv_nodo->pregunta_id);
                                scanf(" %[^\n]s", pregunta); //formato para permitir carga de espacion junto con la pregunta

                                strcpy(nv_nodo->pregunta, pregunta);

                                printf("\nIngrese la ponderacion debe estar entre %.2f y %.2f\n-------->", 0.01, (ponderacionDisponible));
                                scanf("%f", &ponderacionPregunta);
                                limpiarBuffer();

                                if ((ponderacionPregunta > (ponderacionDisponible + EPSILON)) || (ponderacionPregunta < 0.01 - EPSILON)) {

                                    do {

                                        printf("\nError, la ponderacion debe estar entre %.2f y %.2f\n-------->", 0.01, (ponderacionDisponible + EPSILON));
                                        scanf("%f", &ponderacionPregunta);

                                    } while ((ponderacionPregunta > (ponderacionDisponible + EPSILON)) || (ponderacionPregunta < 0.01));

                                }

                                nv_nodo->encuesta_id = idEncuesta;

                                nv_nodo->ponderacion = ponderacionPregunta;

                                nv_nodo->sgte = NULL;

                                ponderacionDisponible -= ponderacionPregunta;

                                suma = (suma + ponderacionPregunta);

                                insertarInicio(&inicioPreguntas, nv_nodo);

                            }
                            else {
                                printf("\nERROR AL CREAR PREGUNTA");
                            }

                        } while (suma < 1.0f - EPSILON);
                    }
                    else {
                        printf("\nEncuesta ya cargada con preguntas, imposible crearle mas");
                    }

                }
                else {
                    printf("\nEncuesta ya procesada, imposible crearle mas preguntas");
                }

            }
            else {
                printf("\nNo existe ese id de encuesta");
            }

        }
        else {
            printf("\nSaliendo...");
        }

    } while (idEncuesta != -1);
}

bool validarIdEncuesta(encuestas** tope, int id) {

    encuestas* topePilaAux = NULL, * nodoAux = NULL;
    bool res = false;

    while (!vacia(tope)) {
        desapilar(tope, &nodoAux);
        if (nodoAux->encuesta_id == id) {
            res = true;
        }
        apilar(&topePilaAux, &nodoAux);
    }

    while (!vacia(&topePilaAux)) {
        desapilar(&topePilaAux, &nodoAux);
        apilar(tope, &nodoAux);
    }

    return res;

}

bool verificarProcesado(encuestas** tope, int id) {
    encuestas* nodoAux = NULL, * topePilaAux = NULL;
    bool res = false;

    while (!vacia(tope)) {
        desapilar(tope, &nodoAux);
        if (nodoAux->encuesta_id == id && nodoAux->procesada == 0) {
            res = true;
        }
        else {
            if (nodoAux->encuesta_id == id && nodoAux->procesada == 1) {
                res = false;
            }
        }
        apilar(&topePilaAux, &nodoAux);
    }

    while (!vacia(&topePilaAux)) {
        desapilar(&topePilaAux, &nodoAux);
        apilar(tope, &nodoAux);
    }

    return res;
}

bool verificarPreguntas(preguntas* inicioListaPreguntas, int id) {
    bool res = true;

    while (inicioListaPreguntas != NULL) {
        if (inicioListaPreguntas->encuesta_id == id) {
            res = false;
        }
        inicioListaPreguntas = inicioListaPreguntas->sgte;
    }

    return res;

}

void mostrarPreguntas(int idEncuesta, encuestas* tope, preguntas* inicioListaPreguntas) {
    encuestas* topeAuxEncuestas = NULL, * nodoAuxEncuestas = NULL;
    int encon = 1;

    if (validarIdEncuesta(&tope, idEncuesta) == true) {

        while ((!vacia(&tope)) && (encon == 1)) {

            desapilar(&tope, &nodoAuxEncuestas);

            if (nodoAuxEncuestas->encuesta_id == idEncuesta) {

                encon = 0;

                printf("\n=================================\n");
                printf("Encuesta: %s", nodoAuxEncuestas->denominacion);
                printf("\n=================================\n");
                while (inicioListaPreguntas != NULL) {

                    if (inicioListaPreguntas->encuesta_id == idEncuesta) {
                        printf("\n\t%d. %s\n\t\tVale: %.2f puntos del total\n", inicioListaPreguntas->pregunta_id, inicioListaPreguntas->pregunta, (inicioListaPreguntas->ponderacion * 100));
                    }
                    inicioListaPreguntas = inicioListaPreguntas->sgte;
                }
            }

            apilar(&topeAuxEncuestas, &nodoAuxEncuestas);

        }

        while (!vacia(&topeAuxEncuestas)) {
            desapilar(&topeAuxEncuestas, &nodoAuxEncuestas);
            apilar(&tope, &nodoAuxEncuestas);
        }

    }
    else {
        printf("\nEse id no existe ;p");
    }

}

void eliminarPregunta(preguntas** Ini, int idEncuesta) {
    preguntas* actual = *Ini;
    preguntas* anterior = NULL;

    

    while (actual != NULL) {
        if (actual->encuesta_id == idEncuesta) {
            
            eliminarRespuestas(actual->pregunta_id);

            preguntas* aBorrar = actual;

            if (anterior == NULL) {
                // el nodo es el primero de la lista
                *Ini = actual->sgte;
            }
            else {
                // el medio o el final
                anterior->sgte = actual->sgte;
            }

            actual = actual->sgte;
            free(aBorrar);
        }
        else {
            anterior = actual;
            actual = actual->sgte;
        }
    }
}


//------------------------------------------------------------------------------------------------
//----------------------------------Encuestas Respondida------------------------------------------
//------------------------------------------------------------------------------------------------

// Funciones auxiliares
preguntas* buscarPregunta(int id_pregunta) {
    preguntas* actual = inicioPreguntas;
    while (actual != NULL) {
        if (actual->pregunta_id == id_pregunta) {
            return actual;
        }
        actual = actual->sgte;
    }
    return NULL;
}

respuestas* buscarRespuesta(int id_respuesta) {
    if (inicioRespuestas == NULL) return NULL;
    
    respuestas* actual = inicioRespuestas;
    do {
        if (actual->respuesta_id == id_respuesta) {
            return actual;
        }
        actual = actual->sgte;
    } while (actual != inicioRespuestas && actual != NULL);
    
    return NULL;
}

sEncuestador* buscarEncuestador(sEncuestador* lista, int id) {
    sEncuestador* actual = lista;
    while (actual != NULL) {
        if (actual->encuestador_id == id) {
            return actual;
        }
        actual = actual->sgte;
    }
    return NULL;
}

// Función principal
encuestaRespondidas* cargarEncuestasRespondidas(
    encuestaRespondidas* lista, 
    sEncuestador* listaEncuestadores,
    encuestas **tope
) {

    FILE *archivo = fopen("resultados.csv", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        return lista;
    }

    char linea[51]; // 50 caracteres + null terminator
    int contadorLinea = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        contadorLinea++;
        size_t len = strlen(linea);
        
        // elimina el salto de linea del final
        //lo de \r no estoy seguro q es me lo tiro la IA dice que podia ser lo q me estaba dando un error, lo dejo por las dudas....
        while (len > 0 && (linea[len-1] == '\n' || linea[len-1] == '\r')) {
            linea[len-1] = '\0';
            len--;
        }

        // si la lina esta vacia saltea la iteracion del loop
        if (len == 0) {
            continue; 
        }

        // validar longitud
        if (len != 50) {
            printf("Error línea %d: Longitud incorrecta (%zu caracteres): '%.20s%s'\n", 
                    contadorLinea, len, 
                    linea,
                    (len > 20) ? "..." : "");
            continue;
        }

        // extraer los datos
        char str_encuesta_id[7] = {0};
        char str_pregunta_id[9] = {0};
        char str_respuesta_id[13] = {0};
        char str_fecha[9] = {0};
        char str_encuestador[5] = {0};
        char str_encuestaRes_id[13] = {0};

        strncpy(str_encuesta_id, linea, 6);
        strncpy(str_pregunta_id, linea + 6, 8);
        strncpy(str_respuesta_id, linea + 14, 12); // 6+8=14
        strncpy(str_fecha, linea + 26, 8);        // 6+8+12=26
        strncpy(str_encuestador, linea + 34, 4);  // 26+8=34
        strncpy(str_encuestaRes_id, linea + 38, 12); // 34+4=38

        // convertir a int
        int encuesta_id = atoi(str_encuesta_id);
        int pregunta_id = atoi(str_pregunta_id);
        int respuesta_id = atoi(str_respuesta_id);
        int fecha = atoi(str_fecha);
        int encuestador_id = atoi(str_encuestador);
        int encuestaRes_id = atoi(str_encuestaRes_id);

        //comprobar si existe id
        if(!idExiste((*tope), encuesta_id)){
            printf("Error: Encuesta ID %d no existe\n", encuesta_id);
            continue;
        }


        // buscar en las estructuras para conectar el puntero
        preguntas* pregunta_ptr = buscarPregunta(pregunta_id);
        if (pregunta_ptr == NULL) {
            printf("Error: Pregunta ID %d no existe\n", pregunta_id);
            continue;
        }

        respuestas* respuesta_ptr = buscarRespuesta(respuesta_id);
        if (respuesta_ptr == NULL) {
            printf("Error: Respuesta ID %d no existe\n", respuesta_id);
            continue;
        }

        sEncuestador* encuestador_ptr = buscarEncuestador(listaEncuestadores, encuestador_id);
        if (encuestador_ptr == NULL) {
            printf("Error: Encuestador ID %d no existe\n", encuestador_id);
            continue;
            continue;
        }

        // Crear nuevo nodo
        encuestaRespondidas* nuevo = (encuestaRespondidas*)malloc(sizeof(encuestaRespondidas));
        if (nuevo == NULL) {
            printf("Error de memoria\n");
            fclose(archivo);
            return lista;
        }

        // Asignar valores
        nuevo->encuesta_id = encuesta_id;
        nuevo->pregunta_id = pregunta_ptr;
        nuevo->respuesta_id = respuesta_ptr;
        nuevo->fecha_realizacion = fecha;
        nuevo->encuestador_id = encuestador_ptr;
        nuevo->encuestarResondida_id = encuestaRes_id;
        nuevo->sgte = NULL;

        if(!esEncuestaRespondidaDuplicada(lista, nuevo)){
            if (lista == NULL) {
                lista = nuevo;
            } else {
                encuestaRespondidas* actual = lista;
                while (actual->sgte != NULL) {
                    actual = actual->sgte;
                }
                actual->sgte = nuevo;
            }

            printf("¡Registro agregado exitosamente!\n");
        }
        else {
            printf("Error, se intento cargar una respuesta ya cargada.\n");
            free(nuevo);
        }
    }

    fclose(archivo);
    return lista;
}

void mostrarEncuestasRespondidas(encuestaRespondidas* lista) {
    if (lista == NULL) {
        printf("La lista de encuestas respondidas está vacía.\n");
        return;
    }
    
    printf("================================================================================\n");
    printf("                    LISTADO DE ENCUESTAS RESPONDIDAS\n");
    printf("================================================================================\n");
    
    encuestaRespondidas* actual = lista;
    int contador = 0;
    
    while (actual != NULL) {
        contador++;
        printf("\n--- Registro #%d ---\n", contador);
        printf("ID Encuesta Respondida: %d\n", actual->encuestarResondida_id);
        printf("ID Encuesta: %d\n", actual->encuesta_id);
        
        if (actual->pregunta_id != NULL) {
            printf("Pregunta [%d]: %s\n", 
                   actual->pregunta_id->pregunta_id,
                   actual->pregunta_id->pregunta);
        } else {
            printf("Pregunta: [NO ENCONTRADA]\n");
        }
        
        if (actual->respuesta_id != NULL) {
            printf("Respuesta [%d]: %s\n", 
                   actual->respuesta_id->respuesta_id,
                   actual->respuesta_id->respuesta);
        } else {
            printf("Respuesta: [NO ENCONTRADA]\n");
        }
        
        // Formatear fecha como AAAAMMDD
        char fechaStr[9];
        snprintf(fechaStr, sizeof(fechaStr), "%d", actual->fecha_realizacion);
        
        if (strlen(fechaStr) == 8) {
            printf("Fecha: %.4s/%.2s/%.2s (AAAAMMDD)\n", 
                   fechaStr, fechaStr + 4, fechaStr + 6);
        } else {
            printf("Fecha: %d (Formato inválido)\n", actual->fecha_realizacion);
        }
        
        if (actual->encuestador_id != NULL) {
            printf("Encuestador [%d]: %s\n", 
                   actual->encuestador_id->encuestador_id,
                   actual->encuestador_id->nombre);
        } else {
            printf("Encuestador: [NO ENCONTRADO]\n");
        }
        
        actual = actual->sgte;
    }
    
    printf("\n================================================================================\n");
    printf("Total de registros: %d\n", contador);
    printf("================================================================================\n");
}
encuestaRespondidas* cargarManualEncuestaRespondida(
    encuestaRespondidas* lista, 
    sEncuestador* listaEncuestadores,
    encuestas *tope
) {
    printf("\n--- Carga manual de encuesta respondida ---\n");
    
    int check = 1, checkExiste = 1;

    // variables temporales
    int encuesta_id, pregunta_id, respuesta_id, fecha, encuestador_id, encuestaRes_id;
    char input[100];
    
    // Validación de encuesta_id
    printf("Encuestas disponibles: \n");
    mostrar_encuesta(&tope, 0);

    do {
        if(check != 1){
            printf("Error en la lectura, unicamente valores enteros.\n");
        }
        else if(!checkExiste){
            printf("Error ese id de encuesta no existe, pruebe nuevamente.\n");
        }

        printf("ID de Encuesta (ej. 15): ");
        check = scanf("%d", &encuesta_id);
        limpiarBuffer();
        checkExiste = idExiste(tope, encuesta_id);

    } while (check != 1 || !checkExiste);

    check = 1;
    // Validación de pregunta_id
    preguntas* pregunta_ptr = NULL;

    printf("Preguntas disponibles: \n");
    preguntas* auxLista = inicioPreguntas;
    while(auxLista != NULL){
        if(auxLista->encuesta_id == encuesta_id){
            printf("ID: %d\n'%s'\n\n", auxLista->pregunta_id, auxLista->pregunta);
        }
        auxLista = auxLista->sgte;
    }

    do {
        if(check != 1){
            printf("Error de lectura, unicamente valores enteros.\n");
        }

        printf("ID de Pregunta (ej. 325): ");
        check = scanf("%d", &pregunta_id);
        limpiarBuffer();
        if (check == 1) {
            pregunta_ptr = buscarPregunta(pregunta_id);
            if (pregunta_ptr == NULL) {
                printf("Error: Pregunta ID %d no existe. Preguntas validas: ", pregunta_id);
            }
            else if(pregunta_ptr->encuesta_id != encuesta_id){
                printf("Error, eligio una pregunta de una encuesta distinta a la seleccionada.\n");
                pregunta_ptr = NULL;
            }
        }
    } while (pregunta_ptr == NULL);

    check = 1;
    // Validación de respuesta
    respuestas* respuesta_ptr = NULL;

    printf("Respuestas disponibles: \n");
    respuestas* auxListaRes = inicioRespuestas->sgte;
    if(inicioRespuestas->pregunta_id == pregunta_id){
        printf("ID: %d\n'%s'\n\n", inicioRespuestas->respuesta_id, inicioRespuestas->respuesta);
    }
    while(auxListaRes != inicioRespuestas){
        if(auxListaRes->pregunta_id == pregunta_id){
            printf("ID: %d\n'%s'\n\n", auxListaRes->respuesta_id, auxListaRes->respuesta);
        }
        auxListaRes = auxListaRes->sgte;
    }

    do {
        if(check != 1){
            printf("Error de lectura, unicamente valores enteros.\n");
        }
        printf("ID de Pregunta (ej. 666): ");
        check = scanf("%d", &respuesta_id);
        limpiarBuffer();
        if (check == 1) {
            respuesta_ptr = buscarRespuesta(respuesta_id);
            if (respuesta_ptr == NULL) {
                printf("Error: Pregunta ID %d no existe. Preguntas validas: ", pregunta_id);
            }
            else if(respuesta_ptr->pregunta_id != pregunta_id){
                printf("Error, eligio la respuesta de una pregunta distinta a la seleccionada.\n");
                respuesta_ptr = NULL;
            }
        }
    } while (respuesta_ptr == NULL);

    check = 1;
    // Validación de fecha (AAAAMMDD)
    do {
        if(check != 1){
            printf("Error, use el formato AAAAMMDD.\n");
        }
        printf("Fecha de realizacion (AAAAMMDD ej. 20250520): ");
        check = scanf("%d", &fecha);
        limpiarBuffer();
    } while (check != 1 || fecha < 20000101 || fecha > 21001231);


    check = 1;
    // Validación de encuestador

    printf("Encuestadores disponibles: \n");
    mostrarEncuestadores(listaEncuestadores);

    sEncuestador* encuestador_ptr = NULL;
    do {
        printf("ID de Encuestador (ej. 2): ");
        check = scanf("%d", &encuestador_id);
        if (check == 1) {
            encuestador_ptr = buscarEncuestador(listaEncuestadores, encuestador_id);
            if (encuestador_ptr == NULL) {
                printf("Error, ese encuestador no existe.\n");
            }
        }
    } while (!encuestador_ptr);

    // Validación de ID de encuesta respondida
    do {
        printf("ID de Encuesta Respondida (12 digitos ej. 000000000095): ");
        check = scanf("%d", &encuestaRes_id);
    } while (check != 1 || encuestaRes_id < 0);

    // Crear nuevo nodo
    encuestaRespondidas* nuevo = (encuestaRespondidas*)malloc(sizeof(encuestaRespondidas));
    nuevo->encuesta_id = encuesta_id;
    nuevo->pregunta_id = pregunta_ptr;
    nuevo->respuesta_id = respuesta_ptr;
    nuevo->fecha_realizacion = fecha;
    nuevo->encuestador_id = encuestador_ptr;
    nuevo->encuestarResondida_id = encuestaRes_id;
    nuevo->sgte = NULL;

    // Insertar en lista
    if(!esEncuestaRespondidaDuplicada(lista, nuevo)){
        if (lista == NULL) {
            lista = nuevo;
        } else {
            encuestaRespondidas* actual = lista;
            while (actual->sgte != NULL) {
                actual = actual->sgte;
            }
            actual->sgte = nuevo;
        }

        printf("¡Registro agregado exitosamente!\n");
    }
    else {
        printf("Error, ya se registro esa respuesta.\n");
        free(nuevo);
    }
    return lista;
}


int esEncuestaRespondidaDuplicada(encuestaRespondidas* lista, encuestaRespondidas* nodo) {
    /*
    verifica si un nodo de encuesta respondida esta duplicado en la lista
    se considera que un nodo esta duplicado si:
        - tiene el mismo ID de encuesta respondida
        - y la misma pregunta
    */
    int retorno = 0;

    if (nodo != NULL) {
    encuestaRespondidas* actual = lista;
    while (actual != NULL) {

        int mismoId = (actual->encuestarResondida_id == nodo->encuestarResondida_id);
        int mismaPregunta = (actual->pregunta_id == nodo->pregunta_id);

        if (mismoId && mismaPregunta) {
            retorno = 1;
        }
        
        actual = actual->sgte;
    }
    }
    
    return retorno; 
}


//------------------------------------------------------------------------------------------------


//----------------------------Arbolito de navidad--------------------------------------------------------

void buscarIdsParaABB(encuestaRespondidas* inicio, encuestas* tope) {
    int id, usrChoice=1, mostrar = 0, hayAlguno = 0;
    nodoABB* Raiz = NULL;
    
    if (inicio != NULL) {

        printf("Encuestas disponibles:\n");
        mostrar_encuesta(&tope, 0);

        printf("\nBienvenido al asistente de creacion de arbol binario de busqueda de encuestas respondidas, por favor ingrese el id de ecnuesta sobre el que desea trabajar, -1 para salir: ");
        scanf("%d", &id);

        if (validarIdEncuesta(&tope, id) == false && id != -1) {
            do {
                printf("\nError: Id no encontrado, ingrese otro o -1 para salir");
                scanf("%d", &id);

            } while (validarIdEncuesta(&tope, id) == false && id != -1);
        }

        if(id != -1) {

            while (inicio != NULL) {

                if ((inicio->encuesta_id == id) && (verificarSiExisteNodo(Raiz, inicio->encuestarResondida_id) == false)) { //si coincide el idEncuesta de encuestaRespondida y no esta cargado ya en el arbol;

                    nodoABB* nv_nodo = (nodoABB*)malloc(sizeof(nodoABB)); //crear nuevo nodo del arbol
                    hayAlguno = 1;
                    if (nv_nodo != NULL) {

                        nv_nodo->idEncuesta = id;
                        nv_nodo->idEncustaRespondida = inicio->encuestarResondida_id;
                        nv_nodo->der = NULL;
                        nv_nodo->izq = NULL;

                        crecer(&Raiz, &nv_nodo);

                    }
                    else {
                        printf("\nError: no fue posible crear nodo");
                    }

                }

                inicio = inicio->sgte;

            }
            if(hayAlguno == 0){
                printf("No hay ninguna respuesta cargada a la encuesta de id %d", id);
            }

            printf("\nDesea mostrar el arbol generado? (1=Si, 0=No): ");
            scanf("%d", &mostrar);
            if (mostrar == 1) {
                printf("IDs de encuestaRespondida correspondientes a la encuesta de id %d:", id);
                PrintearInOrder(Raiz);
                printf("\n");
            }

            borrarArbol(&Raiz);

        }
        else if(id == -1){
            printf("\nSaliendo...");
        }

    }
    else {
        printf("\nLista de encuestas respondidas vacia");
    }

}

bool verificarSiExisteNodo(nodoABB* raiz, int id) {
    bool res = false;

    if (raiz == NULL) {

        return res;

    }
    else {
        if (raiz->idEncustaRespondida == id) {
            res = true;
        }
        else {
            if (raiz->idEncustaRespondida > id) {
                return verificarSiExisteNodo(raiz->izq, id);
            }
            else {
                if (raiz->idEncustaRespondida < id) {
                    return verificarSiExisteNodo(raiz->der, id);
                }
            }
        }
    }
}

void crecer(nodoABB** raiz, nodoABB** aux){
	if (*raiz == NULL) {
		*raiz = *aux;
        (*raiz)->izq = NULL;
        (*raiz)->der = NULL;
	}
	else {
        if ((*raiz)->idEncustaRespondida > (*aux)->idEncustaRespondida) {
            crecer(&(*raiz)->izq , aux);
        }
        else {
            if ((*raiz)->idEncustaRespondida < (*aux)->idEncustaRespondida) {
                crecer(&(*raiz)->der, aux);
            }
        }
	}
}

void PrintearInOrder(nodoABB* raiz) {
    if (raiz != NULL) {
        PrintearInOrder(raiz->izq);
        printf("\n\t%d", raiz->idEncustaRespondida);
        PrintearInOrder(raiz->der);
    }
}

void borrarArbol(nodoABB** raiz) {
    if (*raiz != NULL) {
        borrarArbol(&((*raiz)->izq));
        borrarArbol(&((*raiz)->der));
        free(*raiz);
        *raiz = NULL;
    }
}


//-------------------------------------------------------------------------------------------------------- 


//--------------------------ponderar las locuritas estas--------------------------------------
void ponderarEncuesta(encuestaRespondidas *lista, encuestas **topePila){

    int  encontrado = 0, id = 0;
    float cont = 0, ponderacion = 0, acumulador = 0;
    encuestas *auxPila = NULL, *tpAux = NULL;
    encuestaRespondidas *auxLista = lista;

    desapilar(topePila, &auxPila);
    while(auxPila != NULL){
        while(auxLista != NULL){
            if(auxPila->encuesta_id == auxLista->encuesta_id){
                acumulador = acumulador + ((auxLista->pregunta_id->ponderacion) * (auxLista->respuesta_id->ponderacion));
                if(encontrado == 0){
                    id = auxLista->pregunta_id->pregunta_id;
                    encontrado = 1;
                    cont = 1;
                } else 
                    if(encontrado == 1 && auxLista->pregunta_id->pregunta_id == id){
                        cont = cont + 1;
                    } 
            }
            auxLista = auxLista->sgte;
        }
            auxLista = lista;
            ponderacion = 100 * (acumulador / cont);
            if(cont != 0){
                printf("La encuesta %d, llamada: %s, tiene %.0f respuestas y una ponderacion total de: %.2f\n", auxPila->encuesta_id, auxPila->denominacion, cont, ponderacion);
                auxPila->procesada = 1;
            }
            if(cont == 0) printf("La encuesta %d, llamada: %s, no tiene respuestas.\n", auxPila->encuesta_id, auxPila->denominacion);
            apilar(&tpAux, &auxPila);
            desapilar(topePila, &auxPila);
            encontrado = 0;
            id = 0;
            acumulador = 0;
            cont = 0;     
    }

    desapilar(&tpAux, &auxPila);

    while(auxPila != NULL){
        apilar(topePila, &auxPila);
        desapilar(&tpAux, &auxPila);
    }   

}

void ponderarEncuestaId(encuestaRespondidas *lista){

    int  encontrado = 0, num = 0, idEncuesta = 0;
    float ponderacion = 0;
    encuestaRespondidas *auxLista = lista;

    mostrarEncuestasRespondidas(lista);
    printf("Ingrese el id de la respuesta que desea ponderar (Id de encuesta respondida)\n");
    scanf("%d", &num);

    while(auxLista != NULL){
            if(auxLista->encuestarResondida_id == num){
                idEncuesta = auxLista->encuesta_id;
                    ponderacion = ponderacion + ((auxLista->pregunta_id->ponderacion) * (auxLista->respuesta_id->ponderacion));
                    encontrado = 1;
            }
            auxLista = auxLista->sgte;
        }

        if(encontrado == 1){
            printf("La respuesta %d (de la encuesta %d), tiene una ponderacion total de: %.2f\n", num, idEncuesta, (ponderacion*100));
        }else printf("La respuesta %d, no existe.\n", num);  
}


//-------------------------------------------------------------------------------------------------------- 

//--------------------------Funcion magica para cargar datos a las estructuras----------------------------


void agregarPregunta(int encuesta_id, int pregunta_id, const char* pregunta, float ponderacion) {
    preguntas* nueva = (preguntas*)malloc(sizeof(preguntas));
    nueva->encuesta_id = encuesta_id;
    nueva->pregunta_id = pregunta_id;
    strcpy(nueva->pregunta, pregunta);
    nueva->ponderacion = ponderacion;
    nueva->sgte = NULL;

    if (inicioPreguntas == NULL) {
        inicioPreguntas = nueva;
    } else {
        preguntas* actual = inicioPreguntas;
        while (actual->sgte != NULL) {
            actual = actual->sgte;
        }
        actual->sgte = nueva;
    }
}

// Función para agregar una respuesta a la lista global
void agregarRespuesta(int pregunta_id, int respuesta_id, int respuesta_nro, const char* respuesta, float ponderacion) {
    respuestas* nueva = (respuestas*)malloc(sizeof(respuestas));
    nueva->pregunta_id = pregunta_id;
    nueva->respuesta_id = respuesta_id;
    nueva->respuesta_nro = respuesta_nro;
    strcpy(nueva->respuesta, respuesta);
    nueva->ponderacion = ponderacion;
    nueva->sgte = NULL;

    if (inicioRespuestas == NULL) {
        inicioRespuestas = nueva;
        nueva->sgte = nueva;  // Lista circular: apunta a sí misma
    } else {
        respuestas* actual = inicioRespuestas;
        while (actual->sgte != inicioRespuestas) {
            actual = actual->sgte;
        }
        actual->sgte = nueva;
        nueva->sgte = inicioRespuestas;  // Cierra el círculo
    }
}

// Función principal para cargar todos los datos
void cargarDatosEjemplo(encuestas** topeEncuestas) {
    // Crear y cargar encuesta
    encuestas* nuevaEncuesta = (encuestas*)malloc(sizeof(encuestas));
    nuevaEncuesta->encuesta_id = 15;
    strcpy(nuevaEncuesta->denominacion, "Servicio urbano de Pasajeros");
    nuevaEncuesta->encuesta_mes = 6;
    nuevaEncuesta->encuesta_anio = 25;
    nuevaEncuesta->procesada = 0;
    
    // Apilar encuesta
    nuevaEncuesta->sgte = *topeEncuestas;
    *topeEncuestas = nuevaEncuesta;

    // Cargar preguntas
    agregarPregunta(15, 325, "Como considera la puntualidad del servicio", 0.35);
    agregarPregunta(15, 327, "Que tan limpia esta la unidad", 0.3);
    agregarPregunta(15, 328, "que tan bueno es el trato del chofer", 0.2);
    agregarPregunta(15, 330, "Que tan satisfecho esta con los recorridos", 0.15);

    // Cargar respuestas
    // Pregunta 325
    agregarRespuesta(325, 1500, 1, "Muy Puntual", 1.0);
    agregarRespuesta(325, 1501, 2, "Puntual", 0.5);
    agregarRespuesta(325, 1503, 3, "Impuntual", 0.1);
    
    // Pregunta 327
    agregarRespuesta(327, 1505, 1, "Impecable", 1.0);
    agregarRespuesta(327, 1506, 2, "Limpio", 0.6);
    agregarRespuesta(327, 1508, 3, "Regular", 0.3);
    agregarRespuesta(327, 1510, 4, "Sucio", 0.0);
    
    // Pregunta 328
    agregarRespuesta(328, 1511, 1, "Muy buen trato", 1.0);
    agregarRespuesta(328, 1513, 2, "Aceptable", 0.5);
    agregarRespuesta(328, 1518, 3, "Muy mal trato", 0.0);
    
    // Pregunta 330
    agregarRespuesta(330, 1519, 1, "Totalmente satisfecho", 1.0);
    agregarRespuesta(330, 1520, 2, "Satisfecho", 0.6);
    agregarRespuesta(330, 1521, 3, "Insatisfecho", 0.1);
}


//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

// Función mejorada para mostrar encuestas respondidas por ID

void mostrarEncuestasRespondidasPorID(encuestaRespondidas* listaRespondidas, encuestas** topeEncuestas) {
    if (listaRespondidas == NULL) {
        printf("No hay encuestas respondidas cargadas.\n");
        printf("Presione ENTER para continuar...");
        getchar();
        clear_screen();
        return;
    }

    int opcionSalir = 0;
    
    do {
        // Mostrar lista de encuestas respondidas disponibles
        printf("==================================================\n");
        printf("       ENCUESTAS RESPONDIDAS DISPONIBLES\n");
        printf("==================================================\n");
        
        encuestaRespondidas* actual = listaRespondidas;
        int ids[100], totalIds = 0;
        int fechas[100];
        char denominaciones[100][50];
        char encuestadores[100][30];
        int encuestaIds[100];
        
        // Recolectar encuestas respondidas únicas
        while (actual != NULL && totalIds < 100) {
            int encontrado = 0;
            
            for (int i = 0; i < totalIds; i++) {
                if (ids[i] == actual->encuestarResondida_id) {
                    encontrado = 1;
                    break;
                }
            }
            
            if (!encontrado && idExiste(*topeEncuestas, actual->encuesta_id)) {
                ids[totalIds] = actual->encuestarResondida_id;
                fechas[totalIds] = actual->fecha_realizacion;
                strncpy(encuestadores[totalIds], actual->encuestador_id->nombre, 29);
                encuestaIds[totalIds] = actual->encuesta_id;
                
                // Obtener denominación de la encuesta
                encuestas* pilaTemp = NULL;
                encuestas* nodoEncuesta = NULL;
                encuestas* copiaTope = *topeEncuestas;
                bool encontrada = false;
                
                while (!vacia(&copiaTope) && !encontrada) {
                    desapilar(&copiaTope, &nodoEncuesta);
                    
                    if (nodoEncuesta->encuesta_id == actual->encuesta_id) {
                        encontrada = true;
                        strncpy(denominaciones[totalIds], nodoEncuesta->denominacion, 49);
                    }
                    
                    apilar(&pilaTemp, &nodoEncuesta);
                }
                
                // Restaurar pila
                while (!vacia(&pilaTemp)) {
                    desapilar(&pilaTemp, &nodoEncuesta);
                    apilar(&copiaTope, &nodoEncuesta);
                }
                
                // Formatear fecha
                char fechaStr[9];
                snprintf(fechaStr, sizeof(fechaStr), "%d", fechas[totalIds]);
                char fechaFormateada[11] = "?";
                
                if (strlen(fechaStr) == 8) {
                    snprintf(fechaFormateada, sizeof(fechaFormateada), "%.4s/%.2s/%.2s", fechaStr, fechaStr+4, fechaStr+6);
                }
                
                printf("[%d] ID: %d - Encuesta: %d (%s) - Fecha: %s - Por: %s\n", 
                       totalIds + 1, 
                       actual->encuestarResondida_id,
                       encuestaIds[totalIds],
                       denominaciones[totalIds],
                       fechaFormateada,
                       encuestadores[totalIds]);
                totalIds++;
            }
            
            actual = actual->sgte;
        }
        
        if (totalIds == 0) {
            printf("No hay encuestas respondidas validas para mostrar.\n");
            printf("Presione ENTER para continuar...");
            getchar();
            return;
        }
        
        // Opción para salir
        printf("\n[%d] Volver al menu anterior\n", totalIds + 1);
        
        // Seleccionar encuesta respondida específica
        int opcion;
        int intentos = 0;
        const int MAX_INTENTOS = 3;
        bool entradaValida = false;
        
        do {
            printf("\nSeleccione una opcion (1-%d): ", totalIds + 1);
            
            if (scanf("%d", &opcion) != 1) {
                // Entrada no numérica
                limpiarBuffer();
                printf("Error: Debe ingresar un número. Intente nuevamente.\n");
                intentos++;
            } else if (opcion < 1 || opcion > totalIds + 1) {
                // Fuera de rango
                printf("Error: Opcion fuera de rango. Intente nuevamente.\n");
                intentos++;
            } else {
                entradaValida = true;
            }
            
            if (intentos >= MAX_INTENTOS) {
                printf("Demasiados intentos fallidos. Volviendo al menu...\n");
                clear_screen();
                return;
            }
        } while (!entradaValida);
        
        if (opcion == totalIds + 1) {
            // Salir seleccionado
            clear_screen();
            return;
        }
        
        int idRespondida = ids[opcion - 1];
        int encuestaId = encuestaIds[opcion - 1];
        
        // Mostrar la encuesta respondida seleccionada
        clear_screen();
        printf("\n==================================================\n");
        printf("     RESPUESTAS PARA ENCUESTA RESPONDIDA ID: %d\n", idRespondida);
        printf("     Encuesta ID: %d\n", encuestaId);
        printf("==================================================\n");
        
        printf("Titulo: %s\n\n", denominaciones[opcion-1]);
        
        // Recorrer preguntas de esta encuesta
        preguntas* pregActual = inicioPreguntas;
        
        while (pregActual != NULL) {
            if (pregActual->encuesta_id == encuestaId) {
                printf("Pregunta %d: %s\n", pregActual->pregunta_id, pregActual->pregunta);
                
                // Buscar la respuesta seleccionada para esta pregunta en ESTA encuesta respondida
                int respuestaSeleccionadaId = -1;
                encuestaRespondidas* resp = listaRespondidas;
                
                while (resp != NULL) {
                    if (resp->encuestarResondida_id == idRespondida && 
                        resp->pregunta_id->pregunta_id == pregActual->pregunta_id) {
                        respuestaSeleccionadaId = resp->respuesta_id->respuesta_id;
                        break;
                    }
                    resp = resp->sgte;
                }
                
                // Mostrar todas las respuestas posibles para esta pregunta
                respuestas* respActual = inicioRespuestas;
                if (respActual != NULL) {
                    do {
                        if (respActual->pregunta_id == pregActual->pregunta_id) {
                            // Marcar solo la respuesta realmente seleccionada
                            if (respActual->respuesta_id == respuestaSeleccionadaId) {
                                printf("    -> %s <-\n", respActual->respuesta);
                            } else {
                                printf("      %s\n", respActual->respuesta);
                            }
                        }
                        respActual = respActual->sgte;
                    } while (respActual != inicioRespuestas);
                }
                printf("\n");
            }
            pregActual = pregActual->sgte;
        }
        
        printf("==================================================\n");
        
        // Control de errores en el menu
        int verOtra;
        intentos = 0;
        entradaValida = false;
        
        do {
            printf("\nDesea ver otra encuesta respondida? (1: Si, 0: Volver al menu): ");
            
            if (scanf("%d", &verOtra) != 1) {
                limpiarBuffer();
                printf("Error: Entrada invalida. ");
                intentos++;
            } else if (verOtra != 0 && verOtra != 1) {
                printf("Error: Debe ser 1 o 0. ");
                intentos++;
            } else {
                entradaValida = true;
            }
            
            if (intentos >= 3) {
                printf("Demasiados intentos fallidos. Volviendo al menu...\n");
                verOtra = 0;
                break;
            }
        } while (!entradaValida);
        
        if (verOtra == 0) {
            opcionSalir = 1;
        }
        clear_screen();
        
    } while (opcionSalir == 0);
}

//--------------------------------------------------------------------------------------------------------------

int encuestaCompleta(int encuesta_id) {
    /*
    verifica si una encuesta esta cargada en su totalidad comprobando lo siguiente:
    1. Tiene al menos una pregunta cargada (el control de que las ponderaciones sumen 1 ya se hace al cargar)
    2. Cada pregunta cargada tiene al menos una respuesta asociada (el control de que almenos una respuesta sea de ponderacion 1 ya se hace al cargar)
    
    Retorna:
    1: Encuesta completa
    0: Le faltan respuesta/s
    -1: Encuesta sin preguntas
    */
    int retorno = 1;
    respuestas* respActual;
    preguntas* pregActual = inicioPreguntas;
    int tienePreguntas = 0;
    int tieneRespuestas;
    
    while (pregActual != NULL) {
        if (pregActual->encuesta_id == encuesta_id) {
            tienePreguntas = 1;
            break;
        }
        pregActual = pregActual->sgte;
    }
    
    if (tienePreguntas == 1) {     
        // Verificar que cada pregunta tenga al menos una respuesta
        pregActual = inicioPreguntas;
        while (pregActual != NULL) {
            if (pregActual->encuesta_id == encuesta_id) {
                tieneRespuestas = 0;
                respActual = inicioRespuestas;
                
                if (respActual != NULL) {
                    do {
                        if (respActual->pregunta_id == pregActual->pregunta_id) {
                            tieneRespuestas = 1;
                            break;
                        }
                        respActual = respActual->sgte;
                    } while (respActual != inicioRespuestas);
                }
                
                if (tieneRespuestas == 0) {
                    printf("Pregunta ID %d '%s' no tiene respuestas asociadas\n", pregActual->pregunta_id, pregActual->pregunta);
                    retorno = 0;  // Pregunta sin respuestas
                }
            }
            pregActual = pregActual->sgte;
        }
    }
    else{
        retorno = -1;
    }
    
    if(retorno == 1){
        printf("La encuesta esta completa.\n");
    }
    else if(retorno == 0){
        printf("A la encuesta le faltan respuestas.\n");
    }
    else if(retorno == -1){
        printf("La encuesta no tiene preguntas.\n");
    }


    return retorno; 
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


//TODO: 
// -Agregar controles a todos las lecturas de teclado
// -Funcion mostrar encuesta especifica (la verdad ni de que tiene que hacer, me parece que era la de 
//  mostrar una encuesta con su formato todo lindo, tipo encuesta, preguntas y respuestas, pero no estoy seguro)
// -Testear todo a fondo