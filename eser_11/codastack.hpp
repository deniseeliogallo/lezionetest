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
