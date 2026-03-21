#include <iostream>
#include <math.h>

using namespace std;

int main(){
static const int N=10;
double arr[N]={1.6,2.0,3.3,4.1,5.1,2.3,4.1,9.9,-2.3,8.0};
bool flag=0;
double scambio;

while (!flag){
	flag=1;
	for(int i=1;i<N; i++){
	if(arr[i-1]>arr[i])
	{
	scambio=arr[i];
	arr[i]=arr[i-1];
	arr[i-1]=scambio;
	
		flag=0;
	}
	}
}

for(int i = 0; i < N; i++){
    cout << arr[i] << " ";
}
return 0;
}