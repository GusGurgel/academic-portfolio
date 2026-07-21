/**
 * @file avl.cpp
 * @brief AVL tree (Implementation file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 08, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Atílio Gomes Luiz
 * @author Adapted by: Gustavo Gurgel Medeiros
 */

#include "avl.hpp"
#include "node.hpp"
#include <iostream>
#include <vector>
using namespace std;


//------------------------------------
//   { Destructors and Constructors }
//------------------------------------

template <typename T> avl_tree<T>::~avl_tree() {
  clear();
}

//----------------------------
//   { Public Methods }
//----------------------------

template <typename T> void avl_tree<T>::add(T key, Person* per) {
  // std::cout << "Adding: " << key << " person: " << (*per);
  root = add(root, key, per);
}

template <typename T> void avl_tree<T>::bshow() const {
  bshow(root, "");
}

template <typename T> void avl_tree<T>::clear() {
  root = clear(root);
}

template <typename T>
void avl_tree<T>::inorderPrint(){
	inorderPrint(this->root);
}

template <typename T>
Node<T>* avl_tree<T>::searchNodeByKey(T key){
  // Current node
	Node<T>* current = this->root;

  // Search for the node with the requested key
	while(current != nullptr && key != current->key){
		if(key > current->key){
			current = current->right;
		}else if(key < current->key){
			current = current->left;
		}
	}

  // Returns the found node or nullptr if not found
	return current;
}

template <typename T>
std::vector<Node<T>*> avl_tree<T>::searchNodeByInterval(T keyMin, T keyMax){
  std::vector<Node<T>*> ret; // Return vector
  std::stack<Node<T>*> st;   // Stack to simulate recursion

  // Push root to stack
  st.push(root);

  // If min key is greater than max key, return empty vector
  if(keyMin > keyMax){
    return ret;
  }

  // Simulate recursion
  while(!st.empty()){
    Node<T>* current = st.top();
    st.pop();

    if(current != nullptr){
      // Greater than max (can only be on the left)
      if(current->key > keyMax){
        st.push(current->left);
      // Less than min (can only be on the right)
      }else if(current->key < keyMin){
        st.push(current->right);
      // Within limits
      }else{
        // Exactly equal to max
        if(current->key == keyMax){
          ret.push_back(current);
          st.push(current->left);
        // Exactly equal to min
        }else if(current->key == keyMin){
          ret.push_back(current);
          st.push(current->right);
        // Between min and max
        }else{
          ret.push_back(current);
          st.push(current->right);
          st.push(current->left);
        }
      }
    }
  }

  return ret;
}

template <typename T>
std::vector<Node<T>*> avl_tree<T>::searchNodeByPrefix(T prefix, bool (*isPrefix) (const T&, const T&)){
  std::vector<Node<T>*> ret; // Return vector
  std::stack<Node<T>*> st;   // Stack to simulate recursion

  // Push root to stack
  st.push(root);

  // Simulate recursion
  while(!st.empty()){
    Node<T>* current = st.top();
    st.pop();

    if(current != nullptr){
      // If it matches the prefix, search both sides
      if(isPrefix(prefix, current->key)){
        ret.push_back(current);
        st.push(current->left);
        st.push(current->right);
      // Value is greater than the prefix
      }else if(current->key > prefix){
        // Check if the value contains the prefix
        if(isPrefix(prefix, current->key)){
          ret.push_back(current);
        }
        // Push the left node to the stack
        st.push(current->left);
      // Value is less than the prefix
      }else if(current->key < prefix){
        // Check if the value contains the prefix
        if(isPrefix(prefix, current->key)){
          ret.push_back(current);
        }
        // Push the right node to the stack
        st.push(current->right);
      }
    }
  }

  return ret;
}

//----------------------------
//   { Private Methods }
//----------------------------

template <typename T>
void avl_tree<T>::inorderPrint(Node<T>* node){
	if(node == nullptr){
		return;
	}
	inorderPrint(node->left);
	std::cout << node->key << std::endl;
	inorderPrint(node->right);
}

template <typename T> int avl_tree<T>::height(Node<T> *node) {
  return (node == nullptr) ? 0 : node->height;
}

template <typename T> int avl_tree<T>::balance(Node<T> *node) {
  return height(node->right) - height(node->left);
}

template <typename T> Node<T> *avl_tree<T>::rightRotation(Node<T> *p) {
  Node<T> *u = p->left;
  p->left = u->right;
  u->right = p;
  // Recalculate heights for p and u
  p->height = 1 + max(height(p->left), height(p->right));
  u->height = 1 + max(height(u->left), height(u->right));
  return u;
}

template <typename T> Node<T> *avl_tree<T>::leftRotation(Node<T> *p) {
  Node<T> *u = p->right;
  p->right = u->left;
  u->left = p;
  // Recalculate heights for p and u
  p->height = 1 + max(height(p->right), height(p->left));
  u->height = 1 + max(height(u->left), height(u->right));
  return u;
}

template <typename T> Node<T> *avl_tree<T>::add(Node<T> *p, T key, Person* per) {
	// Allocation spot found
  if (p == nullptr){
		return new Node<T>(key, per);
	}
  // Duplicated value
	if (key == p->key){
		p->addDupe(new Node<T>(key, per));
		return p;
	}
  // Allocation spot is on the left
	if (key < p->key){
		p->left = add(p->left, key, per);
	}
  // Allocation spot is on the right
	else{
		p->right = add(p->right, key, per);
	}

  // Fix node balance
	p = fixup_node(p, key);

	return p;
}

template <typename T> Node<T> *avl_tree<T>::fixup_node(Node<T> *p, T key) {
  // Recalculate height of p
  p->height = 1 + max(height(p->left), height(p->right));

  // Calculate balance of p
  int bal = balance(p);

  if (bal >= -1 && bal <= 1) {
    return p;
  }

  if (bal < -1 && key < p->left->key) {
    p = rightRotation(p);
  } else if (bal < -1 && key > p->left->key) {
    p->left = leftRotation(p->left);
    p = rightRotation(p);
  } else if (bal > 1 && key > p->right->key) {
    p = leftRotation(p);
  } else if (bal > 1 && key < p->right->key) {
    p->right = rightRotation(p->right);
    p = leftRotation(p);
  }
  return p;
}

template <typename T> Node<T> *avl_tree<T>::clear(Node<T> *node) {
  if (node != nullptr) {
    node->left = clear(node->left);
    node->right = clear(node->right);
    delete node;
  }
  return nullptr;
}

template <typename T>
void avl_tree<T>::bshow(Node<T> *node, std::string heranca) const {
  if (node != nullptr && (node->left != nullptr || node->right != nullptr))
    bshow(node->right, heranca + "r");
  for (int i = 0; i < (int)heranca.size() - 1; i++)
    std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
  if (heranca != "")
    std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
  if (node == nullptr) {
    std::cout << "#" << std::endl;
    return;
  }
  std::cout << node->toString() << std::endl;
  if (node != nullptr && (node->left != nullptr || node->right != nullptr))
    bshow(node->left, heranca + "l");
}

// ----------------------------
// Template instantiations
// used by the main program.
// ----------------------------
template class avl_tree<llint>;
template class avl_tree<string>;
template class avl_tree<GDate>;
