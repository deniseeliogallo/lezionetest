#include <iostream>
#include <vector>
#include <set>
#include "randfiller.h" 
#include "grafo.hpp"

using namespace std;

int main(void) {
    cout << "--Test sulla classe degli archi--" << "\n";
    
    unidirected_edge<int> arco1(10, 5);  
    unidirected_edge<int> arco2(3, 1);
    unidirected_edge<int> arco3(5, 10);
    
    cout << boolalpha; 
    
    cout << "Verifica stampa arco: " << arco1 << "\n";
    cout << "L'arco (5-10) è minore dell'arco (1-3)? " << (arco1 < arco2) << "\n";
    cout << "L'arco (10-5) è uguale all'arco (5-10)? " << (arco1 == arco3) << "\n\n";
    
    
	
    cout << "--Test sulla classe dei grafi--" << "\n";
    
    randfiller rf;

    unidirected_graph<int> G1;
    vector<int> nodi_g1(10); 
    rf.fill(nodi_g1, 1, 10);
    
    // Aggiungo gli archi prendendo i nodi a coppie dal vettore
    for (size_t i = 0; i < nodi_g1.size(); i += 2) {
        G1.add_edge(nodi_g1[i], nodi_g1[i+1]);
    }

    
    unidirected_graph<int> G2;
    vector<int> nodi_g2(6);
    rf.fill(nodi_g2, 1, 10);
    
    for (size_t i = 0; i < nodi_g2.size(); i += 2) {
        G2.add_edge(nodi_g2[i], nodi_g2[i+1]);
    }
    
	cout << "Grafo G1:" << "\n";
    for (const auto& arco : G1.all_edges()) {
        cout << "Arco: " << arco << endl;
    }
    
	cout << "\nGrafo G2:" << "\n";
    for (const auto& arco : G2.all_edges()) {
        cout << "Arco: " << arco << endl;
    }
	
    cout << "\nVerifica sottrazioni G1-G2:" << "\n";
    cout << "Grafo differenza:" << "\n";
	
    unidirected_graph<int> G_diff = G1 - G2;
    for (const auto& arco : G_diff.all_edges()) {
        cout << "Arco: " << arco << endl;
    }

  
    int nodo_test = nodi_g1[0]; 
    cout << "\nVerifica vicini del nodo " << nodo_test << " in G1:" << "\n";
    set<int> vicini = G1.neighbors(nodo_test); 
    cout << "I vicini di " << nodo_test << " sono: ";
    for (int n : vicini) {
        cout << n << " ";  
    }
    cout << "\n";

    cout << "\nAggiungiamo archi manuali a G1:" << "\n";
    // Verifico che se aggiungo un arco già presente, non cambia nulla
    G1.add_edge(nodi_g1[0], nodi_g1[1]); 
    // Aggiungo un arco nuovo
    G1.add_edge(100, 200); 
    
	cout << "Grafo G1 aggiornato:" << "\n";
    for (const auto& arco : G1.all_edges()) {
        cout << "Arco: " << arco << endl;
    }
	

   
    set<unidirected_edge<int>> set_archi = G1.all_edges();
    cout << "\nNumero totale di archi in G1: " << set_archi.size() << "\n"; 

    set<int> set_nodi = G1.all_nodes();
    cout << "Numero totale di nodi in G1: " << set_nodi.size() << "\n";


    cout << "\nVerifica posizione archi:" << "\n"
	
	;
    // Cerco un arco che so per certo di aver inserito
    unidirected_edge<int> arco_ricerca(nodi_g1[0], nodi_g1[1]); 
    int pos = G1.edge_number(arco_ricerca);
	
    cout << "L'arco " << arco_ricerca << " si trova alla posizione: " << pos << "\n";
    
    if (pos != -1) {
        cout << "Verifico che con edge_at mi restituisca lo stesso arco: \n";
        cout << "L'arco alla posizione " << pos << " e': " << G1.edge_at(pos) << "\n";
    }

    return 0;
}