#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

//DEFINICION DE FUNCIONES

//Defino funci�n para desplegar el men� principal
void desplegarMenu()
{


    cout << "       +----------------------------------------------------------------------------------------------------------+" << endl;
    cout << "       |         \\             CCCCCC    LL         UU   UU    TTTTTTTT    CCCCCC     HH   HH           //        |" <<endl;
    cout << "       |        (o>           CCCCCCC    LL         UU   UU    TTTTTTTT   CCCCCCC     HH   HH          <o)        |"<<endl;
    cout << "       |      \\_//)           CC         LL         UU   UU       TT      CC          HHHHHHH          (\\_/       |" << endl;
    cout << "       |       \\/_)           CC         LL         UU   UU       TT      CC          HHHHHHH          (_\\/       |"<<endl;
    cout << "       |       _|_            CCCCCCC    LLLLLLL    UU   UU       TT      CCCCCCC     HH   HH           _|_       |"<<endl;
    cout << "       |                       CCCCCC    LLLLLLL     UUUUU        TT       CCCCCC     HH   HH                     |" << endl;
    cout << "       |----------------------------------------------------------------------------------------------------------|"<<endl;
    cout << "       |                                                                                                          |"<<endl;
    cout << "       |                                                                                                          |"<<endl;
    cout << "       |                                             1 - JUGAR                                                    |" << endl;
    cout << "       |                                                                                                          |"<<endl;
    cout << "       |                                             2 - ESTAD�STICAS                                             |" << endl;
    cout << "       |                                                                                                          |"<<endl;
    cout << "       |                                             3 - CR�DITOS                                                 |" << endl;
    cout << "       |                                                                                                          |"<<endl;
    cout << "       |----------------------------------------------------------------------------------------------------------|" << endl;
    cout << "       |                                                                                                          |"<<endl;
    cout << "       |                                             0 - SALIR                                                    |" << endl;
    cout << "       |                                                                                                          |"<<endl;
    cout << "       +----------------------------------------------------------------------------------------------------------+" << endl;


}
//Defino funci�n para ingresar nombres de los jugadores
string asignarNombres()
{
    string jugador;
    cout << " +-----------------------+" <<endl;
    cout << " |        CLUTCH         |" << endl;
    cout << " +-----------------------+" << endl;
    cout << " Antes de comenzar deben registrar sus nombres: " << endl << endl;
    cout << " �Nombre? "<<endl<<endl;

    getline(cin, jugador);


    return jugador;

}
// Defino funci�n para confirmar nombres de los jugadores

char confirmarNombresJugadores()
{
    char confirmar;

    cout << " �Confirmar nombres? (S/N)" << endl;
    cin >> confirmar;
    while(confirmar != 'S' && confirmar != 's' && confirmar != 'N' && confirmar != 'n')
    {
        cout << " -------------------------" << endl;
        cout << "Escriba un caracter valido (S/N)" << endl;
        cin >> confirmar;
    }

    return confirmar;

}
//Defino funci�n para crear la matriz cartas y la matriz sin mezclar
void crearMatricesCartasYSinMezclar(string matrizCartas[][4], string matrizSinMezclar[][4], string carta[], string palo[])
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrizCartas[i][j] = carta[i] + palo[j];
            matrizSinMezclar[i][j] = carta[i] + palo[j];
        }
    }
}

void repartirCartasAJugadores(int matrizElementos[][4], string matrizCartas[][4], string manoJugador[], int fila, int columna)
{

    srand(time(0));

    for (int x = 1; x <= 5; x++)
    {
        do
        {
            fila = (rand() % 5);             // Genera un n�mero aleatorio entre 0 y 4
            columna = (rand() % 4);             // Genera un n�mero aleatorio entre 0 y 3
        }
        while (matrizElementos[fila][columna] != 0);   // Asegura que la carta no se haya tomado antes

        matrizElementos[fila][columna]++;// Registra que esta carta ha sido tomada

        manoJugador[x - 1] = matrizCartas[fila][columna];
    }
}

void repartirCartasAlMazo(int matrizElementos[][4], string matrizCartas[][4], string cartasDelMazo[], int filaMazo, int columnaMazo)
{

    for (int x = 1; x <= 10; x++)
    {
        do
        {
            filaMazo = (rand() % 5);             // Genera un n�mero aleatorio entre 0 y 4
            columnaMazo = (rand() % 4);           //Genera n�mero aleatorio entre 0 y 3
        }
        while (matrizElementos[filaMazo][columnaMazo] != 0);   // Asegura que la carta no se haya tomado antes

        matrizElementos[filaMazo][columnaMazo]++; // Registra que esta carta ha sido asignada al mazo

        cartasDelMazo[x - 1] = matrizCartas[filaMazo][columnaMazo];
    }
}

// Defino funci�n mezclar cartas tipo matriz
void mezclar(string matrizCartas[][4])
{
    srand(time(0));

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int m = rand() % 5;
            int n = rand() % 4;
            swap(matrizCartas[i][j], matrizCartas[m][n]);
        }
        cout << endl;
    }

}

void mezclarMazo(string cartasDelMazo[], int tam)
{

    srand(time(0));
    int m;
    for(int x = 0; x < tam; x++)
    {
        m = rand() % 10;
        swap(cartasDelMazo[x], cartasDelMazo[m]);
    }
}

int determinarQuienEmpieza(string manoJugador[], string matrizSinMezclar[][4])
{

    /*SE UTILIZARON POTENCIAS DE 5 EN LOS ACUMULADORES
    PARA QUE EN LAS MANOS EXTREMAS GANE EL JUGADOR QUE CORRESPONDE
    EJ:
    JUGADOR 1: A,10,10,10,10 Y JUGADOR 2: K,K,K,K,Q

    10 = 1 , J = 5, Q = 25, K = 125, A = 625.
    VALOR ACUMULADOR JUGADOR 1 SER�A: 629
    VALOR ACUMULADOR JUGADOR 2 SER�A: 525

    EMPIEZA EL JUGADOR 1.


    SI FUERA CON POTENCIAS DE 4
    10 = 1 , J = 4, Q = 16, K = 64, A = 256.
    VALOR ACUMULADOR JUGADOR 1 SER�A: 260
    VALOR ACUMULADOR JUGADOR 2 SER�A: 272

    ESTO NO ES CORRECTO YA QUE EL JUGADOR QUE EMPIEZA DEBER�A SER EL JUGADOR 1 POR TENER MAYOR CANTIDAD
    DE ASES EN ESTE EJEMPLO.

    */

    int acumulador_jugador = 0;

    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (manoJugador[x] == matrizSinMezclar[4][y])
            {
                acumulador_jugador += 625;
            }
            else if (manoJugador[x] == matrizSinMezclar[3][y])
            {
                acumulador_jugador += 125;
            }
            else if (manoJugador[x] == matrizSinMezclar[2][y])
            {
                acumulador_jugador += 25;
            }
            else if(manoJugador[x] == matrizSinMezclar[1][y])
            {
                acumulador_jugador += 5;
            }
            else if(manoJugador[x] == matrizSinMezclar[0][y])
            {
                acumulador_jugador += 1;
            }
        }
    }

    return acumulador_jugador;
}

int tirardado()
{
    int dado;
    srand(time(0));
    dado = rand() % 6 + 1;
    switch (dado)
    {
    case 1:
        cout << " ----------------------- " << endl;
        cout << " * LANZAMIENTO DADO #1 *" << endl;
        cout << " -----------------------" << endl;

        cout << " Elegir una carta de su propio corral (1-5) y robar una carta del mazo. Se intercambian las dos."<<endl<<" La carta robada pasa a formar parte del corral y la carta seleccionada se incorpora al mazo." <<endl;
        cout << endl;
        break;
    case 2:
        cout << " ----------------------- " << endl;
        cout << " * LANZAMIENTO DADO #2 *" << endl;
        cout << " -----------------------" << endl;

        cout << " Elegir una carta del corral del contrario (1-5) y robar una carta del mazo. Se intercambian las dos."<<endl<<" La carta robada pasa a formar parte del corral del contrario y la carta seleccionada se incorpora al mazo."<<endl;
        break;
    case 3:
        cout << " ----------------------- " << endl;
        cout << " * LANZAMIENTO DADO #3 *" << endl;
        cout << "  ----------------------" << endl;

        cout << " Elegir una carta del corral propio (1-5) e intercambiarla por una carta del corral del contrario (1-5)."<<endl<<" Las cartas seleccionadas se intercambian."<<endl;
        break;
    case 4:
        cout << " ----------------------- " << endl;
        cout << " * LANZAMIENTO DADO #4 *" << endl;
        cout << " -----------------------" << endl;

        cout << " Intercambiar dos cartas del propio corral. Se eligen dos cartas del propio corral (1-5) y se intercambian entre s�"<<endl;
        break;
    case 5:
        cout << " ----------------------- " << endl;
        cout << " * LANZAMIENTO DADO #5 *" << endl;
        cout << " -----------------------" << endl;
        cout << " Bloquear una carta del corral."<<endl<<" La carta bloqueada no puede ser elegida por el contrario para intercambio (acciones 2 y 3) pero s� puede ser elegida por uno mismo."<<endl;
        break;
    case 6:
        cout << " ----------------------- " << endl;
        cout << " * LANZAMIENTO DADO #6 *" << endl;
        cout << " -----------------------" << endl;

        cout << "1) Intercambiar carta del corral propio con el mazo" << endl;
        cout << "2) Intercambiar carta del corral contrario con el mazo" << endl;
        cout << "3) Intercambiar carta del corral propio con la del contrario" << endl;
        cout << "4) Intercambiar dos cartas del corral propio" << endl;
        cout << "5) Bloquear una carta del corral propio" << endl;
        cout << endl;
        break;
    default:
        cout << " Opci�n no v�lida. Arroje nuevamente el dado." << endl;
        break;
    }
    return dado;
}

bool determinarSiGanoElJugador(string manoJugador[], string matrizSinMezclar[][4], int tam)
{
    int contador = 0;

    for (int y = 0; y < 4; y++)
    {
        //ACA PREGUNTO POR LOS DIEZ
        if (manoJugador[0] == matrizSinMezclar[0][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS JOTAS
        if (manoJugador[1] == matrizSinMezclar[1][y])

        {
            contador++;
        }
        //ACA PREGUNTO POR LAS QUS
        if (manoJugador[2] == matrizSinMezclar[2][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS KAS
        if(manoJugador[3] == matrizSinMezclar[3][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS ASES
        if(manoJugador[4] == matrizSinMezclar[4][y])
        {
            contador++;
        }
    }


    if(contador == 5)
    {
        return true;
    }
    return false;
}

//FUNCIONES PARA LOS DADOS

//FUNCION DADO 1

void accionDado1(string manoJugador[], string cartasDelMazo[])
{
    int cartaCorral;
    string auxiliar;

    cout << "  Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
    cin >> cartaCorral;

    while(cartaCorral < 1 || cartaCorral > 5)
    {
        cout << "  No se ingres� un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
        cout << "  Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
        cin >> cartaCorral;
    }

    auxiliar = manoJugador[cartaCorral - 1];
    manoJugador[cartaCorral - 1] = cartasDelMazo [0];
    cartasDelMazo[0] = auxiliar;
}

//FUNCION DADO 2

void accionDado2(string manoJugador[],string cartasDelMazo[], int cartaCorral)
{
    string auxiliar;

    auxiliar = manoJugador[cartaCorral - 1];
    manoJugador[cartaCorral - 1] = cartasDelMazo[0];
    cartasDelMazo[0] = auxiliar;
}
//FUNCION DADO 3
void accionDado3(string manoJugadorQueNoEmpieza[], string manoJugadorQueEmpieza[], int cartaCorralPropio, int cartaCorralContrario, bool manoJugadorContrarioSinCartasBloqueadas[])
{

    string auxiliar;

    cout << "  Ingrese la carta del corral propio (1-5) para intercambiar por la del corral del contrario (1-5)" << endl;
    cout << "  Carta del corral propio: " << endl;
    cin >> cartaCorralPropio;

    while(cartaCorralPropio < 1 || cartaCorralPropio > 5)
    {
        cout << "  No se ingres� un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
        cout << "  Ingrese la carta del corral propio (1-5) para intercambiar por la del corral del contrario (1-5)" << endl;
        cout << "  Carta del corral propio: " << endl;
        cin >> cartaCorralPropio;
    }
    cout << endl;
    cout << "  Carta del corral contrario: " << endl;
    cin >> cartaCorralContrario;

    while(cartaCorralContrario < 1 || cartaCorralContrario > 5)
    {
        cout << "  No se ingres� un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
        cout << "  Ingrese la carta del corral contrario (1-5) para intercambiar por la del corral propio (1-5)" << endl;
        cout << "  Carta del corral contrario: " << endl;
        cin >> cartaCorralContrario;
    }

    while (manoJugadorContrarioSinCartasBloqueadas[cartaCorralContrario - 1] == true)
    {

        cout << "  No puedes elegir la carta porque est� bloqueada por el contrario" << endl;

        cout << "  Elije otra carta por favor: " << endl;

        cin >> cartaCorralContrario;

        while(cartaCorralContrario < 1 || cartaCorralContrario > 5)

        {
            cout << "  No se ingres� un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
            cout << "  Ingrese la carta del corral contrario (1-5) para intercambiar por la del corral propio (1-5)" << endl;
            cout << "  Carta del corral contrario: " << endl;
            cin >> cartaCorralContrario;
        }
    }

    auxiliar = manoJugadorQueNoEmpieza[cartaCorralPropio - 1];
    manoJugadorQueNoEmpieza[cartaCorralPropio - 1] = manoJugadorQueEmpieza[cartaCorralContrario - 1];
    manoJugadorQueEmpieza[cartaCorralContrario - 1] = auxiliar;
}
// FUNCION DADO 4
void accionDado4(string manoJugadorQueEmpieza[], bool manoJugadorSinCartasBloqueadas[])
{
    int cartaCorralPropio1, cartaCorralPropio2;
    string auxiliar;
    bool auxiliar2;



    cout << "  Ingrese primer carta del corral a intercambiar" << endl;
    cin >> cartaCorralPropio1;

    while(cartaCorralPropio1 < 1 || cartaCorralPropio1 > 5)
    {
        cout << "  No se ingres� un valor correcto de carta, recuerde que es un n�mero del 1 al 5" << endl;
        cout << "  Ingrese primer carta del corral a intercambiar" << endl;
        cin >> cartaCorralPropio1;
    }
    cout << "  Ingrese segunda carta del corral a intercambiar" << endl;
    cin >> cartaCorralPropio2;

    while(cartaCorralPropio2 < 1 || cartaCorralPropio2 > 5)
    {
        cout << "  No se ingres� un valor correcto de carta, recuerde que es un n�mero del 1 al 5" << endl;
        cout << "  Ingrese segunda carta del corral a intercambiar" << endl;
        cin >> cartaCorralPropio2;
    }

    while(cartaCorralPropio1 == cartaCorralPropio2)
    {
        cout << "  Esa carta ya fue seleccionada, elija una diferente para intercambiar" << endl;
        cout << "  Ingrese segunda carta del corral a intercambiar" << endl;
        cin >> cartaCorralPropio2;
        while(cartaCorralPropio2 < 1 || cartaCorralPropio2 > 5)
        {
        cout << "  No se ingres� un valor correcto de carta, recuerde que es un n�mero del 1 al 5" << endl;
        cout << "  Ingrese segunda carta del corral a intercambiar" << endl;
        cin >> cartaCorralPropio2;
        }

    }

    auxiliar2 = manoJugadorSinCartasBloqueadas[cartaCorralPropio1 - 1];
    manoJugadorSinCartasBloqueadas[cartaCorralPropio1 - 1] = manoJugadorSinCartasBloqueadas[cartaCorralPropio2 - 1];
    manoJugadorSinCartasBloqueadas[cartaCorralPropio2 - 1] = auxiliar2;


    auxiliar = manoJugadorQueEmpieza[cartaCorralPropio1 - 1];
    manoJugadorQueEmpieza[cartaCorralPropio1 - 1] = manoJugadorQueEmpieza[cartaCorralPropio2 - 1];
    manoJugadorQueEmpieza[cartaCorralPropio2 - 1] = auxiliar;
}
//FUNCION DADO 5
void accionDado5(bool manoJugadorSinCartasBloqueadas[])
{
    //SUPONIENDO QUE UNA PARTIDA NO VA A SER TAN LARGA PARA BLOQUEAR LAS 5 CARTAS YA QUE EL JUGADOR CONTRARIO
    //NO PODR�A EJECUTAR LA ACCI�N DADO 2 Y 3

    int cartaCorral, contador = 0;
    cout << "  Ingrese la carta del corral a bloquear (1-5): " << endl;
    cin >> cartaCorral;

    while(cartaCorral < 1 || cartaCorral > 5)
    {
        cout << "  No se ingres� un valor correcto de carta, recuerde que es un n�mero del 1 al 5" << endl;
        cout << "  Ingrese la carta del corral a bloquear (1-5): " << endl;
        cin >> cartaCorral;
    }

    for(int x = 0; x < 5; x++)
    {
        if(manoJugadorSinCartasBloqueadas[x] == true)
        {
            contador++;
        }
    }
    if(contador == 5)
    {
        cout << "  Todas las cartas estan bloqueadas por el jugador." << endl;
    }
    else
    {

        while(manoJugadorSinCartasBloqueadas[cartaCorral - 1] == true)
        {
            cout << "  Esta carta ya se encuentra bloqueada, elija otra por favor" << endl;
            cin >> cartaCorral;
        }

    }

    manoJugadorSinCartasBloqueadas[cartaCorral - 1] = true;

}

//FUNCION DADO 6

int accionDado6()
{

    int dado;

    cout << "  Elija la opcion que quiere realizar(1-5) o bien pasar de turno (Opci�n 6): " << endl;


    cin >> dado;
    while(dado < 1 || dado > 6)
    {
        cout << "  No se ingres� un valor correcto de opci�n, recuerde que es un n�mero del 1 al 6" << endl;
        cout << "  Ingrese opci�n del dado 6 nuevamente: " << endl;
        cin >> dado;
    }

    return dado;
}

int cuantasCartasMalUbicadas(string manoJugador[], string matrizSinMezclar[][4], int tam)
{
    int contador = 5;
    int resultado;

    for (int y = 0; y < 4; y++)
    {
        //ACA PREGUNTO POR LOS DIEZ
        if (manoJugador[0] == matrizSinMezclar[0][y])
        {
            contador--;
        }
        //ACA PREGUNTO POR LAS JOTAS
        if (manoJugador[1] == matrizSinMezclar[1][y])

        {
            contador--;
        }
        //ACA PREGUNTO POR LAS QUS
        if (manoJugador[2] == matrizSinMezclar[2][y])
        {
            contador--;
        }
        //ACA PREGUNTO POR LAS KAS
        if(manoJugador[3] == matrizSinMezclar[3][y])
        {
            contador--;
        }
        //ACA PREGUNTO POR LAS ASES
        if(manoJugador[4] == matrizSinMezclar[4][y])
        {
            contador--;
        }
    }
    resultado = contador * 5;

    return resultado;
}

int cuantasCartasBienUbicadas(string manoJugador[], string matrizSinMezclar[][4])
{
    int contador = 0;
    int resultado;

    for (int y = 0; y < 4; y++)
    {
        //ACA PREGUNTO POR LOS DIEZ
        if (manoJugador[0] == matrizSinMezclar[0][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS JOTAS
        if (manoJugador[1] == matrizSinMezclar[1][y])

        {
            contador++;
        }
        //ACA PREGUNTO POR LAS QUS
        if (manoJugador[2] == matrizSinMezclar[2][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS KAS
        if(manoJugador[3] == matrizSinMezclar[3][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS ASES
        if(manoJugador[4] == matrizSinMezclar[4][y])
        {
            contador++;
        }
    }
    resultado = contador * 5;

    return resultado;
}


