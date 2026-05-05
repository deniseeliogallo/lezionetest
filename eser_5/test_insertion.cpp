#include <iostream>
#include <vector>
#include "randfiller.h"
#include "sorting.hpp"

using namespace std;

template<typename T>
void
print_vector(const std::vector<T>& v)
{
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

int main(void)
{
    randfiller rf; /* instantiate a randfiller */

    int successi = 0;
    const int num_test = 100;


	// ho fatto tutto usando un vettore di interi perchè non sapevo se 
	// si volessero misti o meno. Ho comunque fatto prove con vettori di float e double e la situazione è medesima
	// l'unico cambiamento da fare sarebbe definire vector<float> o vector<double>
	//	e poi specificare nel caso di float rf.fill(vec, 1.5f, 7.5f); 
   
    for (int i = 0; i < num_test; ++i) {
        
		/*prendiamo 100 vettori di dimensioni scelte a caso */
        std::vector<int> vect_size(1); // in particolare dato che fill prende in imput un vettore per avere come output un valore singolo vado a prendermi un vettore con un solo elemento
        rf.fill(vect_size, 10, 500);  //uso sempre il randfill per le dimensioni
        int size = vect_size[0];

        /*rempiamo il vettore sempre con randfill*/
        std::vector<int> vec(size);
        rf.fill(vec, -100, 100); 

        /* Eseguiamo il insertion sort */
        insertion_sort(vec); 

        /* Verifichiamo con is_sorted */
        if (is_sorted(vec)) {
            successi++;
        } 
    }

	std::vector<std::string> vec = {"ciao", "cosenza", "acqua", "tony2milli", "Denise", "Sofia", "Soia", "Palla", "Gatto", "Heinsenberg"};
    insertion_sort(vec);
	print_vector(vec);
    
  
   if (is_sorted(vec) && successi == num_test){
        cout << "test ha avuto successo" << endl; 
        return EXIT_SUCCESS;   
    }
    else {
        cout << "test NON ha avuto successo" << endl; 
        return EXIT_FAILURE;   
    }
}
