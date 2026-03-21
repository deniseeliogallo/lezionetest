#include <iostream>

int main()
{

double ad[4] = {0.0, 1.1, 2.2, 3.3};
float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
int ai[3] = {0, 1, 2};
int x = 1;
float y = 1.1;

(&y)[1] = 0;
// y è una variabile di tipo float - non è un array quindi provare a prendere l'indirizzo del secondo elemento produce un errore
// in particolare vedo qua ad esempio che in memoria la x è stata messa in posizione 0xffffc0b1d1ec e la y in posizione 0xffffc0b1d1e8
// dunque andare a modificare la posizione 1 di y va in realtà a modificare la posizione dove si trova la x - infatti la x mi stampa 0



std::cout << &ad[0] <<"\n";
std::cout << &ad[1] <<"\n";
std::cout << &ad[2] <<"\n";
std::cout << &ad[3] <<"\n";
// le variabili di tipo double occupano 64 bit di memoria - dunque occupano 8 spazi (Byte) 
// ad[0] sta nella posizione 0, 1 nella 8, 2 di nuovo in 0 (aumentando la posizione della cella a sinistra), la 3 in 8

std::cout << &af[0] <<"\n";
std::cout << &af[1] <<"\n";
std::cout << &af[2] <<"\n";
std::cout << &af[3] <<"\n";
std::cout << &af[4] <<"\n";
std::cout << &af[5] <<"\n";
std::cout << &af[6] <<"\n";
std::cout << &af[7] <<"\n";

std::cout << &ai[0] <<"\n";
std::cout << &ai[1] <<"\n";
std::cout << &ai[2] <<"\n";
//sia float che int occupano 32 bit - occupano 4 spazi
// 0 , 4 , 8 , c, e poi cambia la cella subito a sinistra e di nuovo 0, 4, 8, c
//Vedi scan per visualizzazione grafica

std::cout << x << "\n";
std::cout << &x <<"\n";

std::cout << y << "\n";
std::cout << &y <<"\n";

return 0;
}