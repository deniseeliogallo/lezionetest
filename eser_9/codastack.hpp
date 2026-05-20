#pragma once
#include <iostream>
#include <list>
#include <concepts>

template<typename T> requires std::integral<T>
class stack{
	std::list<T> contenitore;
	
public:
	stack() {}
	
	//PUSH - PUSH_BACK
	void put(T valore) {
		contenitore.push_back(valore);
	}
	
	//POP - POP_BACK
	T get(){
		if(!empty()){
			T valore = contenitore.back();
			contenitore.pop_back();
			return valore;
		}
		return T{};
	}
	
	//EMPTY - EMPTY
	bool empty() const{
		return contenitore.empty();
	}
};


template<typename T> requires std::integral<T>
class coda{
	std::list<T> contenitore;
	
public:
	coda() {}
	
	//PUSH - PUSH_BACK
	void put(T valore) {
		contenitore.push_back(valore);
	}
	
	//POP - POP_FRONT
	T get(){
		if(!empty()){
			T valore = contenitore.front();
			contenitore.pop_front();
			return valore;
		}
		return T{};
	}
	
	//EMPTY - EMPTY
	bool empty() const{
		return contenitore.empty();
	}
};


template<typename T>
requires std::totally_ordered<T> // dato che dopo gli vado a passare un insieme costituito da due cose e non una, al posto di richiedere che siano interi richiedo che siano ordinabili 
class priority_queue {
    std::set<T> contenitore; // uso un set al posto della list perche ordina automaticamente tutto dal minimo al massimo
    
public:
    priority_queue() {}
    
    // PUSH 
    void put(T valore) {
        contenitore.insert(valore);
    }
    
    // POP
    T get() {
        if (!empty()) {
            T valore = *contenitore.begin();
            contenitore.erase(contenitore.begin()); 
            return valore;
        }
        return T{};
    }
    
    // EMPTY
    bool empty() const {
        return contenitore.empty();
    }
};