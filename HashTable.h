#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include <iostream>



#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V>{


    	private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;

	int h(std::string key){
		int suma_Key = 0;
		for( size_t i=0; i<key.length(); i++){
			suma_Key += static_cast<int>(key.at(i)); //convierte en ASCII
		}
		return suma_Key % max;
	}


    public:
        


	HashTable(int size){
		table = new ListLinked<TableEntry<V>>[size];
		n = 0;
		max = size;
	}



	~HashTable(){
		delete[] table;
	}



	int capacity(){
		return max;
	}


	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		out << "=========" << std::endl;
		for (int i = 0; i < th.max; i++){
			out<< "cubeta " << i << th.table[i] << std::endl; 
		}
		out << "=========" << std::endl;
		return out;
	}

	


	V operator[](std::string key){
		int cubeta = h(key);
		int pos = table[cubeta].search(key);
		if(pos >= 0){
			return table[cubeta].get(pos).value;
		}else{
			throw std::runtime_error("no se ha podido encontrar la clave o clave no válida");
		}
	}


	void insert(std::string key, V value) override{
		int cubeta = h(key);
		int pos = table[cubeta].search(key);
		if(pos != -1){
			throw std::runtime_error("clave existente");
		}else{
			table[cubeta].insert(table[cubeta].size(), TableEntry(key, value));
			n++;
		}
	}

	
	V search(std::string key) override{
		int cubeta = h(key);
                int pos = table[cubeta].search(key);                        
                if (pos >= 0){
                return table[cubeta].get(pos).value;    
                }else{
			throw std::runtime_error("no se ha podido encontrar la clave");
                }
	}

	
	V remove(std::string key) override{
		int cubeta = h(key);
                int pos = table[cubeta].search(key);
                if (pos >= 0){
			
			V valor = table[cubeta].get(pos).value;
                        table[cubeta].remove(pos);
			
			n--;
			return valor;
                }else{

                        throw std::runtime_error("no se ha podido encontrar la clave");
                }

	}

	
	int entries() override{
		return n;
	}
       
};

#endif
