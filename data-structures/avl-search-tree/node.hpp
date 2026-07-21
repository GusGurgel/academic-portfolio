/**
 * @file node.hpp
 * @brief Node (Header/Implementation file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 10, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Atílio Gomes Luiz
 * @author Adapted by: Gustavo Gurgel Medeiros
 */

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>    // Handle duplicate nodes
#include <string>    // toString method
#include <sstream>   // stringstream
#include "person.hpp"// Person node

/**
 * @brief Template structure representing a node in an AVL tree.
 *
 * @tparam T The data type of the key stored in the node.
 */
template <typename T>
struct Node {
	// ---{ Attributes }---

	T key;                  ///< The key value of the node
	int height{0};          ///< The height of the node in the tree

	Node<T> *left{nullptr}; ///< Pointer to the left child
	Node<T> *right{nullptr};///< Pointer to the right child

	Person* toPerson{nullptr}; ///< Pointer to the associated Person object

	/**
	 * @brief Vector that stores duplicate versions of this node.
	 *
	 * Used to handle cases where multiple entries have the same key.
	 */
	std::vector<Node<T>*>* dupes {nullptr};

	// ---{ Methods }---

	/**
	 * @brief Adds a duplicate node to this node's duplicate list.
	 *
	 * @param toAdd Pointer to the duplicate node to be added.
	 */
	void addDupe(Node<T>* toAdd){
		if(dupes == nullptr){
			dupes = new std::vector<Node<T>*>();
		}
		dupes->push_back(toAdd);
	}

	/**
	 * @brief Returns a string representation of the node.
	 *
	 * Includes the key and the number of duplicates if any exist.
	 *
	 * @return std::string The string representation of the node.
	 */
	std::string toString(){
		std::stringstream ret;

		// Adds the node's key
		ret << this->key;

		// Appends the duplicate count if there are any
		if(dupes != nullptr){
			ret << "(" << (dupes->size() + 1) << "x)";
		}

		return ret.str();
	}

	/**
	 * @brief Destructor. Cleans up memory allocated for duplicate nodes.
	 */
	~Node(){
		if(dupes != nullptr){
			for(Node<T>* node : *(dupes)){
				delete node;
			}
			dupes->clear();
			delete dupes;
		}
	}

	/**
	 * @brief Constructs a new Node object.
	 *
	 * @param key The key value for this node.
	 * @param toPerson Pointer to the associated Person (default is nullptr).
	 * @param left Pointer to the left child (default is nullptr).
	 * @param right Pointer to the right child (default is nullptr).
	 * @param height Initial height of the node (default is 1).
	 */
	Node(T key, Person* toPerson = nullptr, Node *left = nullptr, Node *right = nullptr, int height = 1)
	  : key(key), height(height) , left(left), right(right), toPerson(toPerson) {}
};

#endif
