#include <iostream>
#include <math.h>

using namespace std;

int main(){
static const int N=10;
double arr[N]={1.6,2.0,3.3,4.1,5.1,2.3,4.1,9.9,-2.3,8.0};

double minimo=10000;
double massimo=-10000;
double somma=0;

for(int i=0;i<N; i++){
somma=somma+arr[i];
minimo=min(minimo,arr[i]);
massimo=max(massimo,arr[i]);
}

double media=somma/N;

somma=0;
for(int i=0;i<N; i++){
somma=somma+(arr[i]-media)*(arr[i]-media);
}

double devstand=sqrt(somma/N);

cout << "il valore massimo e' " << massimo <<endl;
cout << "il valore minimo e' " << minimo <<endl;
cout << "la media e' " << media <<endl;
cout << "la deviazione standard e' " << devstand <<endl;

return 0;
}