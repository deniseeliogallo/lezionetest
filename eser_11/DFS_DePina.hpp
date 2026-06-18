#pragma once

#include <iostream>
#include <concepts>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <algorithm>

#include "grafo.hpp"
#include "Dijkstra.hpp"


template <typename T> requires std::integral<T>   
bool findpath(const unidirected_graph<T>& Tree, T u, T v, std::set<T>& visited, std::vector<T>& path) {
    //segno come visitato e inserisco nel cammino u
	visited.insert(u);
    path.push_back(u);
    
    if (u == v) return true;
    
    for (const auto& n : Tree.neighbors(u)) { 
	// uso il metodo find(n) che cerca un elemento con chiave uguale ad n, se nessun elemento è trovato, restituisce l'iteratore past-the-end (end())
        if (visited.find(n) == visited.end()) {
            if (findpath(Tree, n, v, visited, path)) {  //verifico che il nodo vicino n arrivi a v tramite la chiamata ricorsiva
                return true;
            }
        }
    }  
    path.pop_back(); //se invece non trova il cammino rimuove u da path 
    return false;
}

// DFS
template <typename T> requires std::integral<T> 
std::vector<T> DFS_cycle(const unidirected_graph<T>& Tree, T nodoA, T nodoB){
    std::vector<T> path; 
    std::set<T> visited;

    if (findpath(Tree, nodoA, nodoB, visited, path)) {
        path.push_back(nodoA); //chiudiamo il ciclo
    }
    
    return path;    
}



// Algoritmo di De Pina 
template <typename T> requires std::integral<T>
std::vector<std::vector<bool>> De_Pina (const unidirected_graph<T>& G, std::vector<std::vector<bool>> S, size_t k){
    
    size_t m = G.all_edges().size();
	size_t cost = G.all_nodes().size();
	
	//C_i vettori booleani che rappresentano gli archi dei cicli: i=1  se l'arco fa parte del ciclo se no è zero
    std::vector<std::vector<bool>> C(k, std::vector<bool>(m, false));
    
    for (size_t i = 0; i < k; i++){
		
		unidirected_graph<T> G_primo;
		std::map<unidirected_edge<T>, double> pesi_G_primo;
    
        for(const auto& arco : G.all_edges()){
            T u = arco.from();
            T v = arco.to();
		
			// divido i nodi in positivi e negativi aggiungendo a u e v il fattore costante
            T u_piu  = u;
            T u_meno = u + cost;
            T v_piu  = v;
            T v_meno = v + cost;
            
            int num = G.edge_number(arco);
            
            if (S[i][num] == true) {
                // Se è attivo: aggiungo a G' (u+, v-) e (u-, v+)
                G_primo.add_edge(u_piu, v_meno);
                G_primo.add_edge(u_meno, v_piu);
            
                pesi_G_primo[{u_piu, v_meno}] = 1;
                pesi_G_primo[{u_meno, v_piu}] = 1;
            } 
            else {
                // Se no aggiungo (u+, v+) e (u-, v-)
                G_primo.add_edge(u_piu, v_piu);
                G_primo.add_edge(u_meno, v_meno);
                
                pesi_G_primo[{u_piu, v_piu}] = 1;
                pesi_G_primo[{u_meno, v_meno}] = 1;
            }
        }
        
		//inizializzo C_i e min_elementi al massimo intero di macchina
		std::vector<bool> C_i(m, false);		
        int min_elementi = std::numeric_limits<int>::max();
		
        for(const auto& nodi : G.all_nodes()){
			//chiamiamo dijkstra per trovare i cammini minimi
			
            T v_piu  = nodi;
            T v_meno = nodi + cost;
            
			std::vector<double> distanze;
			std::vector<T> pred;
			
			dijkstra(2 * cost + 1, G_primo, v_piu, pesi_G_primo, distanze, pred);
            
			//le distanze sono inizializzate a infinito - dunque controllo se è stato trovato un percorso oppure no
            if (distanze[v_meno] != std::numeric_limits<double>::infinity()) {
				
				//Questo vettore rappresenterà il cammino corrente
				std::vector<bool> C_mu(m, false);
				
				// partiamo dal nodo di arrivo e si risale all'indietro.
				T nodo_corrente = v_meno;
				
				while (nodo_corrente != v_piu) {
					T padre = pred[nodo_corrente];
				
					//ritroviamo i nodi originali del grafo G
					T u_orig;
					if (padre > (T)cost) {
						u_orig = padre - cost;
					} else {
						u_orig = padre;
					}

					T v_orig;
					if (nodo_corrente > (T)cost) {
						v_orig = nodo_corrente - cost;
					} else {
						v_orig = nodo_corrente;
					}
					
					//troviamo la posizione dell'arco originale
					unidirected_edge<T> arco_originale(u_orig, v_orig);
					int num = G.edge_number(arco_originale);
				
					//se esiste incrementiamo modulo 2 l'elemento di C_mu relativo all'arco
					if(num != -1){
						C_mu[num] = !C_mu[num];
					}
				
					nodo_corrente = padre;
				}
				
				//contiamo quanti archi sono attivati ('true') e se ha meno elementi di C_i aggiorniamo C_i
				int count = std::count(C_mu.begin(), C_mu.end(), true);
				
				if (count < min_elementi) {
					min_elementi = count;
					C_i = C_mu;
				}
				
			}
		}
		
		// salviamo il ciclo minimo C_i
        C[i] = C_i;
       
        
        for (size_t j = i + 1; j < k; ++j) {
            // Calcolo il prodotto scalare <C_i, S_j> 
            size_t prodscalare = 0;
            for (size_t id = 0; id < m; id++) {
                if (C[i][id] && S[j][id]) {
                    prodscalare++;
                }
            }
            
            // Se il prodotto scalare modulo 2 è pari a 1 
            if (prodscalare % 2 == 1) {
                // S_j = S_j XOR S_i 
                for (size_t id = 0; id < m; ++id) {
                    S[j][id] = S[j][id] ^ S[i][id];
                }
            }
        }
    }  
        
    return C;
}