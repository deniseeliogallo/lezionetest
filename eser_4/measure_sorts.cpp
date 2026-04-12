#include <iostream>
#include <vector>
#include <algorithm> 
#include <iomanip>
#include "randfiller.h"
#include "sorting.hpp"
#include "timecounter.h"

using namespace std;

int main() {
    timecounter tc;
	randfiller rf;

	cout << "Dimensione\tBubble Sort\tInsertion Sort\tSelection Sort\tstd::sort\n";
	
    for (int size = 4; size <= 8192; size = size * 2) {
        
        vector<int> vec(size);
        rf.fill(vec, -100, 100); 

		// faccio delle copie del vettore cosi evito di far si che una volta sortato col primo rimane sortato con gli altri
        vector<int> vec_bubble    = vec;
        vector<int> vec_insertion = vec;
        vector<int> vec_selection = vec;
        vector<int> vec_std       = vec;

        double time_bubble, time_insertion, time_selection, time_std;

        //Test Bubble Sort
        tc.tic();                   
        bubble_sort(vec_bubble);   
        time_bubble = tc.toc();     

        //Test Insertion Sort
        tc.tic();
        insertion_sort(vec_insertion);
        time_insertion = tc.toc();

        //Test Selection Sort
        tc.tic();
        selection_sort(vec_selection);
        time_selection = tc.toc();

        //Test std::sort 
        tc.tic();
        std::sort(vec_std.begin(), vec_std.end()); 
        time_std = tc.toc();

       // uso la libreria iomanip per permettere di formattare meglio l'output. questa cosa la ho poi usata per aiutarmi per poi fare i grafici su matlab.
        cout << size << "\t\t" << fixed << setprecision(6) << time_bubble << "s\t" << time_insertion << "s\t" << time_selection << "s\t" << time_std << "s\n";
    }

    return 0;
}