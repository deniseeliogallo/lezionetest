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
unidirected_graph<T> dijkstra( const unidirected_graph<T>& grafo, T sorgente, const std::map<unidirected_edge<T>, int>& pesi) 
{
    std::map<T, int> distanze;
	unidirected_graph<T> albero_cammini_minimi;

    std::map<T, T> padre;
   

    //Inizializziamo le distanze a infinito (di meno)
    for (const T& nodo : grafo.all_nodes()) {
        distanze[nodo] = std::numeric_limits<int>::max();
    }
    distanze[sorgente] = 0;

	
	// coppia {distanza, nodo}
    std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> pq;

    pq.push({distanze[sorgente], sorgente});

    while (!pq.empty()) {
		
        std::pair<int, T> dequeue = pq.top();
		pq.pop();
		
        int d = dequeue.first;
        T u = dequeue.second;

        if (d > distanze[u]) continue;

        std::set<T> vicini = grafo.neighbors(u);
        for (const T& v : vicini) {
            unidirected_edge<T> arco(u, v);
            int peso_arco = pesi.at(arco); 

            if (distanze[u] + peso_arco < distanze[v]) {
                distanze[v] = distanze[u] + peso_arco;
                padre[v] = u;
                pq.push({distanze[v], v}); 
            }
        }
    }

    for (const auto& [figlio, genitore] : padre) {
        albero_cammini_minimi.add_edge(genitore, figlio);
    }

    return albero_cammini_minimi;
}

