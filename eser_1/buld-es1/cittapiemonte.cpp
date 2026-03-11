#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[]){
    if (argc < 2) {
       cerr << "nessun file è stato inserito" << endl;
    }

    string filename = argv[1];
    ifstream ifs(filename);
	
    if(ifs.is_open()){
        cout << "File aperto correttamente!" << endl;
		 
		while ( !ifs.eof() ){
			
				string citta;
				double temp1;
				double temp2;
				double temp3;
				double temp4;
		
				ifs >> citta >> temp1 >> temp2 >> temp3 >> temp4;
				if (ifs.fail()){
					cerr << "c'è un errore nella scrittura del file";
					break;
				}
				else{
				double media=(temp1+temp2+temp3+temp4)/4;
				cout << "la media delle temperature a " << citta << " é " << media << endl;
				}
				
		}

        ifs.close();
    }
    else{
        cerr<<"c'è stato un errore ad aprire il file di input";
    }
    return 0;
}