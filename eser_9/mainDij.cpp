#include <iostream>
#include "grafo.hpp"
#include "codastack.hpp"
#include "Dijkstra.hpp"



int main() {
    unidirected_graph<int> grafo;
   
    grafo.add_edge(1, 2);
    grafo.add_edge(1, 3);
    grafo.add_edge(2, 3);
    grafo.add_edge(2, 4);
    grafo.add_edge(3, 4);
    grafo.add_edge(3, 5);
    grafo.add_edge(4, 5);

  
    std::map<unidirected_edge<int>, int> pesi;
    pesi[unidirected_edge<int>(1, 2)] = 10;
    pesi[unidirected_edge<int>(1, 3)] = 3;
    pesi[unidirected_edge<int>(2, 3)] = 1;
    pesi[unidirected_edge<int>(2, 4)] = 2;
    pesi[unidirected_edge<int>(3, 4)] = 8;
    pesi[unidirected_edge<int>(3, 5)] = 2;
    pesi[unidirected_edge<int>(4, 5)] = 7;

    int sorgente = 1;
   
   
    unidirected_graph<int> albero_minimo = dijkstra(grafo, sorgente, pesi);

   
    std::cout << "Albero Dijkstra: ";
    for (const auto& arco : albero_minimo.all_edges()) {
        std::cout << arco << " ";
    }
    std::cout << std::endl;
	
    return 0;
}