#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <optional>

template<typename T>
std::optional<std::vector<T>>
bubble_sort(std::vector<T>&vec)
{
	if (vec.size() == 0) {
		return {};
	}
	for( size_t i=0; i< (vec.size()-1); i++)
	{
		for ( size_t j= vec.size()-1; j>i; j--)
		{
		if (vec[j]<vec[j-1]){
			std::swap(vec[j],vec[j-1]);
		}
		}
	}
	return vec;
}

template<typename T>
std::optional<std::vector<T>>
insertion_sort(std::vector<T>&vec)
{
	if (vec.size() == 0) {
		return {};
	}
	for (size_t j = 1; j < vec.size(); j++) {
		T key = vec[j];
		size_t i = j;
		while (i > 0 && vec[i - 1] > key) {
        vec[i] = vec[i - 1];
        i--;
		}
		vec[i] = key;
	}
	return vec;
}


template<typename T>
std::optional<std::vector<T>>
selection_sort(std::vector<T>&vec)
{
	if (vec.size() == 0) {
		return {};
	}
	for( size_t i=0; i< (vec.size()-1); i++)
	{
		size_t min=i;
		for ( size_t j= i+1; j < vec.size(); j++ )
		{
		if (vec[j]<vec[min]){
			min=j;
		}
		}
		if(min !=i){
			std::swap(vec[i],vec[min]);
		}
	}
	return vec;
}


template<typename T>
std::optional<std::vector<T>>
merge(std::vector<T>&vec, int p, int q,  int r)
{
	int n1=q-p+1;
	int n2= r-q;
	std::vector<T> L(n1);
	std::vector<T> R(n2);
	
	for (int i=0; i<n1; i++){
	L[i]=vec[p+i];
	}
	
	for (int j=0; j<n2; j++){
	R[j]=vec[q+1+j];
	}

	
    int i = 0;
    int j = 0;
    for (int k = p; k <= r; k++) {
    // l'infinito mi dava problema con le stringhe quindi ho cambiato la condizione di if
    if (i < n1 && (j >= n2 || L[i] <= R[j])) {
        vec[k] = L[i];
        i++;
    } else {
        vec[k] = R[j];
        j++;
    }
}
	return vec;
}
template<typename T>
std::optional<std::vector<T>>
merge_sort(std::vector<T>&vec, int p,  int r)
{
	if (vec.size() == 0) {
		return {};
	}
	if (p < r)
	{
		int q = (p+r)/2;
		merge_sort(vec, p,q);
		merge_sort(vec, q+1, r);
		merge(vec, p, q, r);
	}
	return vec;
}



template<typename T>
int partition(std::vector<T>&vec, int p,  int r)
{
	T x= vec[r];
	int i= p-1;
	for( int j=p; j<=r-1; j++){
		if (vec[j]<=x){
			i++;
			std::swap(vec[i],vec[j]);
		}
	}
	std::swap(vec[i+1],vec[r]);
	
	return i+1;
}
template<typename T>
std::optional<std::vector<T>>
quicksort(std::vector<T>&vec, int p,  int r)
{
	if (vec.size() == 0) {
		return {};
	}
	if (p < r)
	{
		int q = partition(vec, p, r);
		quicksort(vec, p, q-1);
		quicksort(vec, q+1, r);
	}
	return vec;
}

template<typename T>
std::optional<std::vector<T>>
insertion_sort_quick(std::vector<T>& vec, int p, int r)
{
	if (vec.size() == 0) {
		return {};
	}
	for (int j = p + 1; j <= r; j++) 
    {
        T key = vec[j];
        int i = j - 1;
		while (i >= p && vec[i] > key) 
        {
            vec[i + 1] = vec[i];
            i--;
        }
        vec[i + 1] = key;

    }
return vec;
}

//creo un quicksort modificato che sotto la soglia 40 (dove nei mio esempio - vedi osservazioni - inizia a battere il bubble sort e il selection sort) usa l'insertion sort
template<typename T>
std::optional<std::vector<T>>
quicksort_ibrido(std::vector<T>& vec, int p, int r, int soglia = 40)
{
    if (vec.empty()) return {};

    if (p < r)
    {
        if ((r - p + 1) < soglia) {
            insertion_sort_quick(vec,p,r);
        } 
        else {
            int q = partition(vec, p, r);
            quicksort_ibrido(vec, p, q - 1, soglia);
            quicksort_ibrido(vec, q + 1, r, soglia);
        }
    }
    return vec;
}
template<typename T>
bool is_sorted(const std::vector<T>& vec){
	if (vec.size() < 2) {
        return true;
    }
	
	for(size_t i=0; i< (vec.size()-1); i++){
		if (vec[i]>vec[i+1]){
			return false;
		}
	}
	return true;
}