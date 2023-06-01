#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//puto el q borra
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
        case 1:
            system("cls");
            leerArchivo(listado, listadoFile);
            system("PAUSE");
            system("cls");
            break;

        case 2:
            break;

        case 3:
            system("cls");
            cargarProducto(listado, listadoFile);
            system("cls");
            break;

        case 4:
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
    int size;
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
    listadoFile = fopen(listado, "rb");
    if (listadoFile!= NULL)
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
