#include <iostream>
#include <utility>
#include <vector>
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