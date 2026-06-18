#include <iostream>
#include <concepts>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <Eigen/Dense>
#include <string>

#include "DFS_DePina.hpp"
#include "grafo.hpp"
#include "codastack.hpp"
#include "graph_visit.hpp"
#include "verso_maglie.hpp"

using namespace std;

//creiamo uno struct resistore e uno generatore per distinguere le componenti ai fini della matrice B
struct Resistore{
	string nome;
	int u;
	int v;
	double valore;
};

struct Generatore{
	string nome;
	int u;
	int v;
	double valore;
};


int main(int argc, const char *argv[]){

	//se è stato lasciato vuoto l'input errore
	if (argc < 2) {
		cerr << "nessun file è stato inserito" << endl;
		return -1;
	}

	//il file di input corrisponde all'argomento in posizione 1
	string filename = argv[1];
    ifstream ifs(filename);

	//il codice di progetto richiede di implementare ambe le alternative (dfs e de pina)
	//usiamo come default il de pina, nonostante ciò abbiamo messo la possibilità di specificare in input "dfs" nel caso si volesse usare quello.
	
	bool dfs_search = false; 
    if (argc >= 3) {
        string metodo = argv[2];
        if (metodo == "dfs") {
            dfs_search = true;
        } else {
            cerr << "Argomento non riconosciuto" << endl;
			return -1;
        }
    } 
	
	unidirected_graph<int> G;
	vector<Generatore> generatori;
	vector<Resistore> resistenze;
		
	//scorriamo l'input.txt
	if(ifs.is_open()){
        cout << "File aperto correttamente!" << endl;
		
			string componente;
			double peso;
			int u; 
			int v;
	
			while (ifs >> componente >> peso >> u >> v) {
				G.add_edge(u, v);
				
				//dividiamo tra generatori e resistenze le componenti
				if (componente[0] == 'V') {
					generatori.push_back({componente, u, v, peso});
				}
				else {
					resistenze.push_back({componente, u, v, peso});
				}
			}
		ifs.close();
	}
    else{
		//se c'è stato qualche problema nella lettura del file di input - errore
        cerr<<"c'è stato un errore ad aprire il file di input";
		return -1;
    }
	
	int sorgente = 1;
	
	//ci calcoliamo il coalbero utilizzando la dfs
	stack<int> tipo;
	unidirected_graph<int> T = graph_visit(G, sorgente, tipo);
	unidirected_graph<int> C = G - T;
	
	std::vector<std::vector<int>> maglie_dfs;
	std::vector<std::vector<bool>> maglie_depina;

	if(dfs_search){ //implementiamo dfs
		for (const auto& archi : C.all_edges()){
		
			int u=archi.from();
			int v=archi.to();
		
			std::vector<int> ciclo = DFS_cycle(T, u, v);
		
			if (!ciclo.empty()) {
				maglie_dfs.push_back(ciclo);
			}
		}
	}
	else{ //implementiamo de pina
	
		//iniziamo dal vettore di booleani S - Si inizializzano k vettori booleani Si di lunghezza m.
		size_t m_archi = G.all_edges().size();
		size_t k_archi = C.all_edges().size();

		std::vector<std::vector<bool>> S(k_archi, std::vector<bool>(m_archi, false));

		int iter = 0;
		
		//inizializziamo S_i ad 1 se l'arco in num sta sia in G che in C, se no 0
		for (const auto& arco_coalbero : C.all_edges()) {
			int num = G.edge_number(arco_coalbero);
		
			if (num != -1) {
				S[iter][num] = true; 
			}
			iter++;
		}
		
		//troviamo i cicli
	    maglie_depina= De_Pina(G, S, k_archi);
	}
	
	
	//creo la matrice delle resistenze
    int m = resistenze.size();
	int n;
	
	//n è il numero di maglie
    if (dfs_search == true) {
		n = maglie_dfs.size();  
	} else {
		n = maglie_depina.size();   
	}
	
	//matrice diagonale delle resistenze
    Eigen::MatrixXd R=Eigen::MatrixXd::Zero(m, m);
	for (int i=0; i<m; i++){
		R(i,i)=resistenze[i].valore;
	}
	
	//matrice di incidenza 
	Eigen::MatrixXd B=Eigen::MatrixXd::Zero(m, n);
	
	//vettore dei termini noti
	Eigen::VectorXd V=Eigen::VectorXd::Zero(n); 
	
	for (int j=0; j<n; j++){ //ciclo sulle maglie generate da De Pina
		
		//definiamo il vettore con i nodi del ciclo (ad esempio del tipo 1 - 2 - 4 - 1)
		vector<int> nodi_ciclo;
		
		if (dfs_search) {
            nodi_ciclo = maglie_dfs[j]; 
        } else { 
			//per trasformare C_i da vettore di booleani nella forma desiderata chiamiamo verso_maglia
            nodi_ciclo = verso_maglia(maglie_depina[j], G);
        }
		
		for (size_t k = 0; k < nodi_ciclo.size()-1; k++){
			int nodo_A = nodi_ciclo[k];
			int nodo_B = nodi_ciclo[k+1];

			//assegno a B i valori +1 o -1 in base a se il verso di percorrenza è uguale a quello del resistore
			for (int i = 0; i < m; i++){
				int r_min = min(resistenze[i].u, resistenze[i].v);
				int r_max = max(resistenze[i].u, resistenze[i].v);
					
				if (nodo_A == r_min && nodo_B == r_max){
					B(i,j) = 1;
					break;
			    }
				else if(nodo_A == r_max && nodo_B == r_min){
					B(i,j) = -1;
					break;
				}
			}
			
			//assegno a v i valori di tensione con segni positivi o negativi sempre in base al verso di percorrenza
			for (const auto& gen: generatori){
				if (nodo_A == gen.u && nodo_B == gen.v){
					V(j) -= gen.valore;
					break;
				}
				else if (nodo_A == gen.v && nodo_B == gen.u){
					V(j) += gen.valore;
					break;
				}
			}
	    }
	}
	
	Eigen::MatrixXd A=B.transpose()*R*B; 
	
	//vettore delle correnti - usiamo cholesky
	Eigen::VectorXd I = A.llt().solve(V); 
	Eigen::VectorXd Tensioni_R=R*B*I;
	
	
	for (size_t i = 0; i < resistenze.size(); i++) {
		cout << resistenze[i].nome << ": V = " << Tensioni_R(i) << " volts, I = " << Tensioni_R(i)/resistenze[i].valore << " amps." << endl;
	}
	
    return 0;
}
