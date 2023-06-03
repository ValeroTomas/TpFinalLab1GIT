#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

/** COLORES PARA LA TERMINAL DE WINDOWS*/
#define ROJO     12
#define VERDE   10
#define AMARILLO  14
#define MAGENTA 13
#define CYAN    11
#define BLANCO   15

/** ESTRUCTURA DE PRODUCTO*/
typedef struct
{
    int id;
    char nombre [50];
    int existencias;
    int precio;
} stProducto;

/** FUNCIONES*/
stProducto nuevoProducto(int i);
void color(int color);
void menu();
void verificarArchivo(char archivo[]);
void cargarProducto(FILE *listadoFile, char listado[]);
void leerArchivo(FILE *listadoFile, char listado[]);
void cuponDeDescuento(Pila *pila1);

/** NOMBRE Y VERSIÓN DEL PROGRAMA*/
const char tpFinal[] = "Gestor de Stock V0.03.0";


/** FUNCIÓN PRINCIPAL*/
int main()
{
    int opc;
    int loop = 1;
    int flag;
    char listadoFile[] = "listado.bin";
    FILE *listado;

    verificarArchivo(listadoFile);



    while(loop == 1)
    {
        menu();
        fflush(stdin);
        scanf("%d", &opc);
        switch(opc)
        {
        case 1: //LISTADO ORDENADO POR ID
            system("cls");
            leerArchivo(listado, listadoFile);
            system("PAUSE");
            system("cls");
            break;

        case 2: //LISTADO ORDENADO POR NOMBRE
            system("cls");
            leerArchivo (listado,listadoFile);
            system("PAUSE");
            system("cls");
            break;

        case 3: //CARGA PRODUCTOS
            system("cls");
            cargarProducto(listado, listadoFile);
            system("cls");
            break;

        case 4: //CARGA EXISTENCIAS
            break;

        case 5:
            break;

        case 6:
            system("cls");
            color(VERDE);
            printf("\n\nHasta luego!\n\n");
            color(BLANCO);
            system("pause");
            system("cls");
            exit(0);
            break;

        default:
            system("cls");
            color(ROJO);
            printf("\n\nOpcion invalida!\n");
            printf("intente nuevamente...\n\n");
            color(BLANCO);
            system("pause");
            system("cls");
            loop = 1;
            break;
        }
    }

    return 0;
}

/** FUNCIÓN BASE DE CARGA DE PRODUCTO*/
stProducto nuevoProducto(int i)
{
    stProducto producto;
    int id = i + 1;

    producto.id = id;
    color(CYAN);
    printf("\nIngrese el nombre.\n");
    color(BLANCO);
    fflush(stdin);
    gets(producto.nombre);
    color(CYAN);
    printf("\nIngrese numero de existencias:\n");
    color(BLANCO);
    fflush(stdin);
    scanf("%d", &producto.existencias);
    color(CYAN);
    printf("\nIngrese precio (SIN SIGNO '$'):\n");
    color(BLANCO);
    fflush(stdin);
    scanf("%d", &producto.precio);
    return producto;
}

/** FUNCIÓN PARA CARGAR EL PRODUCTO AL ARCHIVO*/
void cargarProducto(FILE *listadoFile, char listado[])
{
    stProducto producto;
    stProducto cache;
    listadoFile = fopen(listado, "rb");
    int i = 0;
    long int size;
    if(listadoFile != NULL)
    {
        fseek(listadoFile, 0, SEEK_END);
        size = ftell(listadoFile);
        if(size > 0)
        {
            fseek(listadoFile, -sizeof(stProducto), SEEK_END);
            fread(&cache, sizeof(stProducto),1, listadoFile);
            i = cache.id;
            printf("%d", i);
        }
        fclose(listadoFile);
        listadoFile = fopen(listado, "ab");
        producto = nuevoProducto(i);
        fwrite(&producto, sizeof(stProducto), 1, listadoFile);
        fclose(listadoFile);
    }
}

void leerArchivo(FILE *listadoFile, char listado[])
{

    stProducto producto;
    long int size;
    listadoFile = fopen(listado, "rb");

    if (listadoFile!= NULL)
    {
        fseek(listadoFile, 0, SEEK_END);
        size = ftell(listadoFile);
        fclose(listadoFile);
        listadoFile = fopen(listado, "rb");
        if (size == 0)
        {
            printf ("EL ARCHIVO NO ESTA CARGADO \n");

        }
        else
        {
            while(!feof(listadoFile))
            {
                fread(&producto, sizeof(stProducto),1, listadoFile);
                if(!feof(listadoFile))
                {
                    color(AMARILLO);
                    printf("\n______________________________________\n\n");
                    color(CYAN);
                    printf ("ID: ");
                    color(BLANCO);
                    printf ("%i\n", producto.id);
                    color(CYAN);
                    printf ("NOMBRE: ");
                    color(BLANCO);
                    printf ("%s\n", producto.nombre);
                    color(CYAN);
                    printf ("EXISTENCIAS: ");
                    color(BLANCO);
                    printf ("%i\n", producto.existencias);
                    color(CYAN);
                    printf ("PRECIO: ", producto.precio);
                    color(BLANCO);
                    printf ("$%i\n", producto.precio);
                    color(AMARILLO);
                    printf("______________________________________\n");
                    color(BLANCO);
                }
                printf("\n");
            }
            fclose(listadoFile);


        }
    }
    else
    {
        printf ("EL ARCHIVO NO EXISTE\n");
    }


}

/** MENÚ PRINCIPAL DEL PROGRAMA*/
void menu()
{
    color(CYAN);
    printf("  _______________________________________________________________  \n");
    printf(" |                                                               |\n");
    printf(" |                                                               |\n");
    printf(" |");
    color(BLANCO);
    printf("                    %s                    ", tpFinal);
    color(CYAN);
    printf("|\n");
    printf(" |                                                               |\n");
    printf(" |_______________________________________________________________|\n");
    printf(" |                                                               |\n");
    printf(" |                                                               |\n");
    printf(" |");
    color(BLANCO);
    printf(" 1. MOSTRAR PRODUCTOS ORDENADOS POR ID                         ");
    color(CYAN);
    printf("|\n");
    printf(" |                                                               |\n");
    printf(" |");
    color(BLANCO);
    printf(" 2. MOSTRAR PRODUCTOS ORDENADOS POR NOMBRE                     ");
    color(CYAN);
    printf("|\n");
    printf(" |                                                               |\n");
    printf(" |");
    color(BLANCO);
    printf(" 3. AGREGAR NUEVO PRODUCTO                                     ");
    color(CYAN);
    printf("|\n");
    printf(" |                                                               |\n");
    printf(" |");
    color(BLANCO);
    printf(" 4. AGREGAR EXISTENCIAS DE PRODUCTO (ID)                       ");
    color(CYAN);
    printf("|\n");
    printf(" |                                                               |\n");
    printf(" |");
    color(BLANCO);
    printf(" 5. CREAR CARRITO DE SALIDA DE PRODUCTOS                       ");
    color(CYAN);
    printf("|\n");
    printf(" |                                                               |\n");
    printf(" |");
    color(ROJO);
    printf(" 6. SALIR                                                      ");
    color(CYAN);
    printf("|\n"); /**AGREGAR MAS OPCIONES ACÁ */
    printf(" |                                                               |\n");
    printf(" |_______________________________________________________________|");
    printf("\n\n  Ingrese su opcion: ");
    color(BLANCO);
}

/** FUNCIÓN DE COLORES EN TERMINAL DE WINDOWS*/
void color(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

/** VERIFICACIÓN DE EXISTENCIA DE ARCHIVO*/
void verificarArchivo(char archivo[])
{
    FILE *arch;
    arch = fopen(archivo, "rb");
    color(AMARILLO);
    printf("  %s\n",tpFinal);
    color(BLANCO);
    printf("\n  Verificando la existencia del listado...");
    Sleep(1500);
    if(arch != NULL)
    {
        system("cls");
        color(AMARILLO);
        printf("  %s\n",tpFinal);
        color(VERDE);
        printf("\n  El archivo existe!\n\n  Entrando al menu...");
        fclose(arch);
        Sleep(1250);
        system("cls");
    }
    else
    {
        system("cls");
        color(AMARILLO);
        printf("  %s\n",tpFinal);
        color(ROJO);
        printf("\n  El archivo NO existe!");
        color(BLANCO);
        printf("\n\n  Creando el arhivo...");
        Sleep(2000);
        arch = fopen(archivo, "ab");
        if(arch != NULL)
        {
            system("cls");
            color(AMARILLO);
            printf("  %s\n",tpFinal);
            color(VERDE);
            printf("\n  Archivo creado exitosamente!\n\n  Entrando al menu...");
            Sleep(1250);
            fclose(arch);
            system("cls");
        }
        else
        {
            system("cls");
            color(AMARILLO);
            printf("  %s\n",tpFinal);
            color(ROJO);
            printf("\n  Error inesperado al crear el archivo!\n\n  Cerrando el programa...");
            color(BLANCO);
            exit(1);
        }
    }
}


/** FUNCION 'CALCULO DEL DESCUENTO' **/
void cuponDeDescuento(Pila *pila1)
{


    Pila aux;
    inicpila (&aux);
    int suma = 0;
    int aux2;
    float descuento;
    int op;

    while(!pilavacia(pila1))
    {
        aux2 = tope(pila1);
        suma = suma + aux2;
        apilar(&aux, desapilar(pila1));
    }

    while(!pilavacia(&aux)){

        apilar(pila1, desapilar(&aux));

    }

    printf("**  Selecciona tu cupon de descuento  ** \n\n");
    printf("  (1) Prog4 (20% de descuento en la totalidad de la compra)\n");
    printf("  (2) JJT10 (35% de descuento en la totalidad de la compra)");
    printf("\n  -Insertar cupon aqui: ");

    scanf("%i", &op);

    switch(op)
    {

    case 1:

        descuento = suma * 0.20; //DESCUENTO QUE LUEGO RESTO CON EL PRECIO TOTAL

        suma = suma - descuento;

        printf("\n * El total de la compra es de: %i", suma);
        break;


    case 2:

        descuento = suma * 0.35; //DESCUENTO QUE LUEGO RESTO CON EL PRECIO TOTAL
        suma = suma - descuento;

        printf("El total de la compra es de: %i", suma);
        break;

    }
}
