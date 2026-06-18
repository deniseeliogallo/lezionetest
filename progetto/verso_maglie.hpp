#pragma once

#include "grafo.hpp"
#include <vector>
#include <set>
#include <concepts>

using namespace std;

template <typename I> requires std::integral<I>
vector<I> verso_maglia(const vector<bool>& maglia, const unidirected_graph<I>& grafo){
    
    unidirected_graph<I> grafo_maglia; // costruiamo un grafo con gli archi del ciclo
    
    for (size_t i = 0; i < maglia.size(); i++){
        if (maglia[i]){
            unidirected_edge<I> arco = grafo.edge_at(i); //risaliamo all'arco nel grafo iniziale
            grafo_maglia.add_edge(arco.from(), arco.to());
        }
    }
    
	//ora dobbiamo dare un verso al nostro ciclo
    set<I> nodi_maglia = grafo_maglia.all_nodes();
    if (nodi_maglia.empty()) return {};

    I partenza = *nodi_maglia.begin(); //scegliamo il nodo di partenza
    vector<I> percorso;
    percorso.push_back(partenza);

    set<I> vicini_partenza = grafo_maglia.neighbors(partenza); 

	//usiamo l'operatore di deference per trovare il "primo" vicino
    I corrente = *vicini_partenza.begin();
    I precedente = partenza;
    percorso.push_back(corrente);

    bool trovato = true; //inizializzo una flag per verificare se ho trovato il vicino corretto nel ciclo

    while (corrente != partenza && trovato){ //il ciclo va avanti solo se non siamo arrivati al nodo iniziale e se non abbiamo trovato una strada
        I prossimo;
        trovato = false; 
        
        for (const I& v : grafo_maglia.neighbors(corrente)){ 
            if (v != precedente){
                prossimo = v;
                trovato = true;
                break;
            }
        }
        
        if (trovato){
            percorso.push_back(prossimo);
            precedente = corrente;
            corrente = prossimo;
        }
    }
    
    return percorso;
}