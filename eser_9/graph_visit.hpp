#include <iostream>
#include <list>
#include <concepts>
#include <set>
#include <map>
#include <vector>
#include "codastack.hpp"
#include "grafo.hpp"

template <typename T, typename tipo> requires std::integral<T> 

unidirected_graph<T> graph_visit(const unidirected_graph<T>& grafo, T sorgente, tipo& contenitore ){
	
	// se tipo = lifo -> dfs
	// se tipo = fifo -> bfs
	// fa da solo quando chiamo.	
	
	unidirected_graph<T> albero;
	std::set<T> reached;
	std::map<T, T> padre;
	
	//inizializzo
	reached.insert(sorgente);
	contenitore.put(sorgente);
	
	// ciclo finche il contenitore non è vuoto
	while (!contenitore.empty()){
		T u = contenitore.get();
		
		if (u != sorgente) {
            albero.add_edge(padre.at(u), u);
        }
		
		std::set<T> vicini = grafo.neighbors(u);
		
		for (const T& v: vicini){
			if ( reached.count(v) == 0 ){
				reached.insert(v);
				contenitore.put(v);
				padre[v]=u;
			}
		}
	}
	return albero;
}


template <typename T> requires std::integral<T>
void dfs_visita(const unidirected_graph<T>& grafo, T u, std::set<T>& reached, unidirected_graph<T>& albero) {
    
	//il while lo prendiamo sottoforma di funzione ricorsiva
    std::set<T> vicini = grafo.neighbors(u);
    
    for (const T& v : vicini) {
        if (reached.count(v) == 0) {
            reached.insert(v);       
            albero.add_edge(u, v);  
            dfs_visita(grafo, v, reached, albero);
        }
    }
}


template <typename T> requires std::integral<T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& grafo, T sorgente) {
    
    unidirected_graph<T> albero;
    std::set<T> reached; 
    reached.insert(sorgente);
    
	
    //fino a qua segue gli stessi passaggi della dfs standard, poi lo mandiamo alla funzione di visita
    dfs_visita(grafo, sorgente, reached, albero);
    
    return albero;
}