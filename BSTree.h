#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:



	int nelem;

	BSNode<T> *root;


    	BSNode<T>* search(BSNode<T>* n, T e) const{
	
	
		if (n == nullptr){
        
			throw std::runtime_error("arbol vacio");
        
	
		}else if (n->elem < e){
        
			return search(n->right, e);
	
		}else if (n->elem > e){
	
			return search(n->left, e);
	
		}else{
	
			return n;
	
		}
	}


	BSNode<T>* insert(BSNode<T>* n, T e){
		
		if (n == nullptr){
			return new BSNode<T>(e, nullptr, nullptr);			
		
		}else if(n->elem < e){
			n->right = insert(n->right, e);
		
		} else if(n->elem > e){
			n->left = insert(n->left, e);
		
		}else{
			throw std::runtime_error("el elemento ya está en el arbol");
		
		}
		return n;
	}


	void print_inorder(std::ostream &out, BSNode<T>* n) const{
		if( n != nullptr){
			print_inorder(out, n->left);
			out << n->elem << " ";
			print_inorder(out, n->right);
		}else{
			
		}
	}


	T max(BSNode<T>* n) const{
		if (n == nullptr){
			throw std::runtime_error("arbol vacio");
		}else if(n->right != nullptr){
			return max(n->right);
	        }else{
	 		return n->elem;
		}		
		return n->elem;
        }



	BSNode<T>* remove_max(BSNode<T>* n){
	
		if(n->right == nullptr){
			return n->left;
	
		}else{
			n->right = remove_max(n->right);
	
			return n;
		}
        }


	BSNode<T>* remove(BSNode<T>* n, T e){
	
		if( n == nullptr){
			throw std::runtime_error("Arbol vacio!! (remove)");
	
		}else if (n->elem < e){
			n->right = remove(n->right, e);
	
		}else if(n->elem > e){
			n->left = remove(n->left, e);
	
		}else{
	
			if(n->right != nullptr && n->left != nullptr){
				n->elem = max(n->left);
				n->left = remove_max(n->left);
	
			}else if(n->right != nullptr && n->left == nullptr){
	
				BSNode<T>* backup = n->right;
				delete n;
				return backup;	
	
	
			}else if(n->right == nullptr && n->left != nullptr){
        
				BSNode<T>* backup = n->left;
                                delete n;
                                return backup;
	
	
			}else if(n->right == nullptr && n->left == nullptr){
				delete n;
				return nullptr;
			}
		}
		return n;
	}


	void delete_cascade(BSNode<T>* n){
		if(n != nullptr){
			delete_cascade(n->right);
			delete_cascade(n->left);
			delete n;
		}
	}



	

    public:

        BSTree(){
		root = nullptr;
		nelem = 0;
	}


	int size() const{
		return nelem;
	}


	T search(T e) const{
		return search(root, e)->elem;
	}


	T operator[](T e) const{
		return search(e)->elem;
	}


	void insert(T e){
		root = insert(root, e); 
		nelem++;
	}


	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		bst.print_inorder(out, bst.root);
		return out;
	}


	void remove(T e){
		remove(root, e);
		nelem--;
	}


	~BSTree(){
		delete_cascade(root);
	}
    
};

#endif
