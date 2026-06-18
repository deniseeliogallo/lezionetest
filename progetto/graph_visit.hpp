#pragma once

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


