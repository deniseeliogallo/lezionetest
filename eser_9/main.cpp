#include <iostream>
#include "grafo.hpp"
#include "codastack.hpp"
#include "graph_visit.hpp"

int main() {
    //grafi test dati a lezione
    unidirected_graph<int> g;
	unidirected_graph<int> g1;
	unidirected_graph<int> g2;
	
	std::vector<int> nodi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	
    g.add_edge(1, 2);
    g.add_edge(1, 4);
    g.add_edge(1, 3);
    g.add_edge(1, 6);
	g.add_edge(2, 5);
	g.add_edge(2, 4);
	g.add_edge(2, 7);
	g.add_edge(3, 6);
	g.add_edge(4, 6);
	g.add_edge(4, 7);
	g.add_edge(5, 7);
	g.add_edge(6, 8);
	g.add_edge(7, 9);
	g.add_edge(8, 9);
	
	
	g1.add_edge(1, 2);
	g1.add_edge(1, 3);
	g1.add_edge(1, 4);
	g1.add_edge(1, 6);
	g1.add_edge(2, 5);
	g1.add_edge(2, 7);
	g1.add_edge(6, 8);
	g1.add_edge(7, 9);
	
	
	g2.add_edge(1, 2);
	g2.add_edge(1, 3);
	g2.add_edge(1, 4);
	g2.add_edge(1, 6);
	g2.add_edge(6, 7);
	g2.add_edge(7, 5);
	g2.add_edge(6, 8);
	g2.add_edge(8, 9);
	
	
  
    int sorgente = 1;

    //BFS 
    coda<int> coda_fifo; 
    unidirected_graph<int> albero_bfs_g = graph_visit(g, sorgente, coda_fifo);
    unidirected_graph<int> albero_bfs_g1 = graph_visit(g1, sorgente, coda_fifo);
	unidirected_graph<int> albero_bfs_g2  = graph_visit(g2, sorgente, coda_fifo);
	
	
    //DFS 
    stack<int> stack_lifo; 

    unidirected_graph<int> albero_dfs_g = graph_visit(g, sorgente, stack_lifo);
    unidirected_graph<int> albero_dfs_g1 = graph_visit(g1, sorgente, stack_lifo);
	unidirected_graph<int> albero_dfs_g2 = graph_visit(g2, sorgente, stack_lifo);
	 
	 
    //DFS Ricorsiva
    unidirected_graph<int> albero_dfs_ricorsiva_g = recursive_dfs(g, sorgente);
    unidirected_graph<int> albero_dfs_ricorsiva_g1 = recursive_dfs(g1, sorgente);
	unidirected_graph<int> albero_dfs_ricorsiva_g2 = recursive_dfs(g2, sorgente);
	
	
	
	
	// inizio a stampare g
	std::cout << "Albero BFS del primo grafo: ";
	for (const auto& arco : albero_bfs_g.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	std::cout << "Albero DFS del primo grafo: ";
	for (const auto& arco : albero_dfs_g.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	std::cout << "Albero DFS ricorsivo del primo grafo: ";
	for (const auto& arco : albero_dfs_ricorsiva_g.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	
	
		
	// stampo g1
	std::cout << "Albero BFS del secondo grafo: ";
	for (const auto& arco : albero_bfs_g1.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	std::cout << "Albero DFS del secondo grafo: ";
	for (const auto& arco : albero_dfs_g1.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	std::cout << "Albero DFS ricorsivo del secondo grafo: ";
	for (const auto& arco : albero_dfs_ricorsiva_g1.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	
		
	// stampo g2
	std::cout << "Albero BFS del terzo grafo: ";
	for (const auto& arco : albero_bfs_g2.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	std::cout << "Albero DFS del terzo grafo: ";
	for (const auto& arco : albero_dfs_g2.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	std::cout << "Albero DFS ricorsivo del terzo grafo: ";
	for (const auto& arco : albero_dfs_ricorsiva_g2.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	
    return 0;
}