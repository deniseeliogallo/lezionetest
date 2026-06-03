#pragma once
#include <iostream>
#include <algorithm>
#include <concepts>
#include <set>
#include <map>


template<typename T> requires std::integral<T>
class unidirected_edge {
	
	T nodeA;
	T nodeB;
	
public:
	
	unidirected_edge() : nodeA(0), nodeB(0) {} 
	//costruttore user-defined - ho messo che il nodo A che è quello di partenza deve essere inferiore al nodo B di arrivo con min e max
	unidirected_edge(T u, T v) {
		nodeA= std::min(u,v);
		nodeB= std::max(u,v);
		
	}
	
	//return di nodoA e nodeB
	T from() const {
        return nodeA;
    }
	
	T to() const {
        return nodeB;
    }
	
	//metodi booleani che controllano uguaglianza e se uno è minore dell'altro
	bool operator==(const unidirected_edge<T>& other) const {
        return (nodeA == other.nodeA) && (nodeB == other.nodeB);
    }
	
	bool operator<(const unidirected_edge<T>& other) const{
		if (nodeA != other.nodeA) {
            return nodeA < other.nodeA;
        }
        return nodeB < other.nodeB;
	}

};

template<typename T>
std::ostream& 
operator<<(std::ostream& os, const unidirected_edge<T>& e) 
{
    os << "(" << e.from() << "," << e.to() << ")";
    return os;
}



template<typename T> requires std::integral<T>
class unidirected_graph{
	
	std::set<unidirected_edge<T>> archi;
	std::map<T, std::set<T>> lista_adj;
	
	public:
	
	//costruttore di default
	unidirected_graph() {};
	
	unidirected_graph(const unidirected_graph& other){
    archi=other.archi;
    lista_adj=other.lista_adj;
	}
	
	
	// inizio a definire i metodi
	// metodo neighbors() che restituisce i nodi confinanti -> uso la lista di adiacenza per trovare i vicini.
	std::set<T> neighbors(const T& nodo) const{
		if(lista_adj.count(nodo)>0){
			return lista_adj.at(nodo);
		}
		return std::set<T>();
	}

	// metodo add edge che permette di aggiungere un arco
    void add_edge(const T&u, const T&v) {
		
		unidirected_edge<T> arco_nuovo(u,v);
        archi.insert(arco_nuovo); 
		//insert controlla già se l'arco esiste gia!
        
        lista_adj[u].insert(v);
		lista_adj[v].insert(u);
    }

  

    // Restituisce tutti gli archi
    std::set<unidirected_edge<T>> all_edges() const {
        return archi;
    }

    // Restituisce tutti i nodi
    std::set<T> all_nodes() const {
        std::set<T> nodi;
		for (auto& [nodo, vicini]: lista_adj){
			nodi.insert(nodo);
		}	
		return nodi;
    }

    
	// edge number che dato un arco ne da la numerazione nel grafo
    int edge_number(const unidirected_edge<T>& arco_cercare) const {
		int count=0;
        for (const auto& arco: archi) {
            if (arco == arco_cercare){
				return count;
			}
			count++;
        }
        return -1; // dato che 0 mi restituisce l'arco in "Prima" posizione, uso -1 per indicare quando non è stato trovato 
    }

    // edge at dato un numero d'arco restituisce l'oggetto arco dato il suo numero (indice)
    unidirected_edge<T> edge_at(const int& i) const {
		int count=0;
		for (const auto& arco: archi){
			if (count == i){
				return arco;
			}
			count++;
		}
		return unidirected_edge<T>();     
    }

    // operatore differenza che da gli archi presenti in G e non in G'
    unidirected_graph<T> operator-(const unidirected_graph<T>& other) const {
        
		unidirected_graph<T> differenza;
		
		for (const auto& arco : archi) {
            if (other.archi.count(arco) == 0) {
                differenza.add_edge(arco.from(), arco.to());
            }
        }
        return differenza;
    }
};
	