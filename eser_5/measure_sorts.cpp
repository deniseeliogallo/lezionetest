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

	double m_merge, m_quick, m_bubble, m_insertion, m_selection, m_std;	
	cout << "Medie\n";
	cout << "Dimensione \tMerge Sort \tQuick Sort \tBubble Sort\tInsertion Sort\tSelection Sort\t std::sort\n";



    for (int size = 4; size <= 8192; size = size * 2) {
        
		std::vector<std::vector<int>> vec(100, std::vector<int>(size));
		for(int i=0; i<100; i++)
		{
			rf.fill(vec[i], -100, 100);
		}
		
   
		// faccio delle copie del vettore cosi evito di far si che una volta sortato col primo rimane sortato con gli altri
		vector<vector<int>> vec_merge = vec;
        vector<vector<int>> vec_quick = vec;
		vector<vector<int>> vec_bubble    = vec;
		vector<vector<int>> vec_insertion = vec;
		vector<vector<int>> vec_selection = vec;
        vector<vector<int>> vec_std       = vec;

        double time_merge, time_quick, time_bubble, time_insertion, time_selection, time_std;

		//Test merge Sort
		
		tc.tic();
		for(int i=0; i<100; i++)
		{
			merge_sort(vec_merge[i], 0, size-1); 
		} 
        time_merge = tc.toc();  
		
		//Test quick Sort
        tc.tic();
		for(int i=0; i<100; i++)
		{
			quicksort(vec_quick[i], 0, size-1); 
		} 
        time_quick = tc.toc();  
		
        //Test Bubble Sort
		tc.tic();
		for(int i=0; i<100; i++)
		{
			bubble_sort(vec_bubble[i]); 
		} 
        time_bubble = tc.toc(); 
		
        //Test Insertion Sort
        tc.tic();
		for(int i=0; i<100; i++)
		{
			insertion_sort(vec_insertion[i]); 
		} 
        time_insertion = tc.toc(); 

        //Test Selection Sort
        tc.tic();
		for(int i=0; i<100; i++)
		{
			selection_sort(vec_selection[i]); 
		} 
        time_selection = tc.toc(); 

        //Test std::sort 
        tc.tic();
		for(int i=0; i<100; i++)
		{
		std::sort(vec_std[i].begin(), vec_std[i].end()); 
		} 
        time_std = tc.toc(); 
		
		m_merge=time_merge/100;
		m_quick=time_quick/100;
		m_bubble=time_bubble/100;
		m_insertion =time_insertion/100;
		m_selection=time_selection/100;
		m_std=time_std/100;

       // uso la libreria iomanip per permettere di formattare meglio l'output. questa cosa la ho poi usata per aiutarmi per poi fare i grafici su matlab.
        cout << size << "\t\t" << fixed << setprecision(6) << m_merge << "s\t" << m_quick << "s\t" << m_bubble << "s\t" << m_insertion << "s\t" << m_selection << "s\t" << m_std << "s\n";
   }
	


    
    return 0;
}