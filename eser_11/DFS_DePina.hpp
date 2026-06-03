#pragma once
#include <iostream>
#include <concepts>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include "grafo.hpp"
#include "Dijkstra.hpp"

//implemento il codice del file "cicli fondamentali di un grafo"
template <typename T> requires std::integral<T>   
bool findpath(const unidirected_graph<T>& Tree, T u, T v, std::set<T>& visited, std::vector<T>& path) {
    visited.insert(u);
    path.push_back(u);
    
    if (u == v) return true;
    
    for (const auto& n : Tree.neighbors(u)) { 
	// uso il metodo find(n) che cerca un elemento con chiave uguale ad n, se nessun elemento è trovato, restituisce l'iteratore past-the-end (end())
        if (visited.find(n) == visited.end()) {
            if (findpath(Tree, n, v, visited, path)) { 
                return true;
            }
        }
    }
    
    path.pop_back();
    return false;
}

// DFS
template <typename T> requires std::integral<T> 
std::vector<T> DFS_cycle(const unidirected_graph<T>& Tree, T nodoA, T nodoB){
    std::vector<T> path; //potevo usare anche una lista, però ho usato un vettore perchè occupa meno memoria ed è piu facilmente accessibile
    std::set<T> visited;

    if (findpath(Tree, nodoA, nodoB, visited, path)) {
        path.push_back(nodoA);
    }
    
    return path;    
}

// Algoritmo di De Pina 
template <typename T> requires std::integral<T>
std::vector<std::vector<bool>> De_Pina (const unidirected_graph<T>& G, std::vector<std::vector<bool>> S, size_t k, const std::map<unidirected_edge<T>, int>& pesi_G){
    
    size_t m = G.all_edges().size();
    std::vector<std::vector<bool>> C(k, std::vector<bool>(m, false));
    
    for (size_t i = 0; i < k; i++){
        unidirected_graph<T> G_primo;
        std::map<unidirected_edge<T>, int> pesi_G_primo;
    
        for(const auto& arco : G.all_edges()){
            T u = arco.from();
            T v = arco.to();
			
            //per vedere una distinzione tra i nodi di G e i nodi di G', ho pensato di dividere i nodi tra pari in G e dispari in G'
			T u_piu  = 2 * u;
            T u_piu  = 2 * u;
            T u_meno = 2 * u + 1;
            T v_piu  = 2 * v;
            T v_meno = 2 * v + 1;
            
            int num = G.edge_number(arco);
            int peso_arco = pesi_G.at(arco);
            
            if (S[i][num] == true) {
                // Se è attivo: aggiungo a G' (u+, v-) e (u-, v+)
                G_primo.add_edge(u_piu, v_meno);
                G_primo.add_edge(u_meno, v_piu);
            
                pesi_G_primo[{u_piu, v_meno}] = peso_arco;
                pesi_G_primo[{u_meno, v_piu}] = peso_arco;
            } 
            else {
                // Se no aggiungo (u+, v+) e (u-, v-)
                G_primo.add_edge(u_piu, v_piu);
                G_primo.add_edge(u_meno, v_meno);
                
                pesi_G_primo[{u_piu, v_piu}] = peso_arco;
                pesi_G_primo[{u_meno, v_meno}] = peso_arco;
            }
        }
            
        std::vector<T> cammino_minimo_scelto;
        int min_peso_assoluto = std::numeric_limits<int>::max();
        
        for(const auto& nodi : G.all_nodes()){
            T v_piu  = 2 * nodi;
            T v_meno = 2 * nodi + 1;
            
            unidirected_graph<T> albero = dijkstra(G_primo, v_meno, pesi_G_primo);
            
            std::vector<T> cammino_minimo;
            std::set<T> visitati;
            bool percorso = findpath(albero, v_meno, v_piu, visitati, cammino_minimo);
            
            // faccio un controllo per evitare crash del programma in caso percorso è false
            if (percorso && cammino_minimo.size() > 1) {
                int peso_cammino_corrente = 0;
                for (size_t p = 0; p < cammino_minimo.size() - 1; ++p) {
                    unidirected_edge<T> arco_path(cammino_minimo[p], cammino_minimo[p+1]);
                    peso_cammino_corrente += pesi_G_primo.at(arco_path);
                }
                
                if (peso_cammino_corrente < min_peso_assoluto) {
                    min_peso_assoluto = peso_cammino_corrente;
                    cammino_minimo_scelto = cammino_minimo;
                }
            }
        }
        
        
        if (!cammino_minimo_scelto.empty()) {
            for (size_t j = 0; j < cammino_minimo_scelto.size() - 1; ++j) {
                T nodo1_primo = cammino_minimo_scelto[j];
                T nodo2_primo = cammino_minimo_scelto[j+1];
                
                T u_orig = nodo1_primo / 2;
                T v_orig = nodo2_primo / 2;
                
                unidirected_edge<T> arco_originale(u_orig, v_orig);
                int num = G.edge_number(arco_originale);
                
				// Incrementiamo modulo 2
                C[i][num] = !C[i][num]; 
      
            }
        }
        
        for (size_t j = i + 1; j < k; ++j) {
            // Calcolo il prodotto scalare <C_i, S_j> modificato modulo 2
            size_t prodscalare = 0;
            for (size_t id = 0; id < m; id++) {
                if (C[i][id] && S[j][id]) {
                    prodscalare++;
                }
            }
            
            // Se il prodotto scalare è pari a 1 
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