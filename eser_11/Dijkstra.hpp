#pragma once

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <limits>
#include <queue>
#include <concepts>

#include "grafo.hpp"
#include "codastack.hpp"


template <typename T> requires std::integral<T>
void dijkstra( size_t n, const unidirected_graph<T>& grafo, T sorgente, const std::map<unidirected_edge<T>, double>& pesi, std::vector<double>& distanze, std::vector<T>& pred) 
{
	distanze.assign(n,std::numeric_limits<double>::infinity());
	pred.assign(n, T(-1));
	
	pred[sorgente]=sorgente;
    distanze[sorgente]=0.0;
	
	
	// coppia {distanza, nodo} - coda con priorità dove gli elementi sono i vertici e le proprità sono le distanze tra nodi
    std::priority_queue<std::pair<double, T>, std::vector<std::pair<double, T>>, std::greater<std::pair<double, T>>> pq;

    pq.push({distanze[sorgente], sorgente});

    while (!pq.empty()) {
		
        std::pair<double, T> dequeue = pq.top();
		pq.pop();
		
		//distanza dalla sorgente di u
        double d = dequeue.first;
        T u = dequeue.second;

        if (d > distanze[u]) continue;

        std::set<T> vicini = grafo.neighbors(u);
        for (const T& v : vicini) {
            unidirected_edge<T> arco(u, v);
            double peso_arco = pesi.at(arco); 
			
			//se la distanza di u dalla sorgente + il peso (u,v) è minore della distanza di v dalla sorgente aggiorno pred e distanze
            if (distanze[u] + peso_arco < distanze[v]) {
                distanze[v] = distanze[u] + peso_arco;
                pred[v] = u;
                pq.push({distanze[v], v}); 
            }
        }
	}
}

