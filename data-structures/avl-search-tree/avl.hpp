/**
 * @file avl.hpp
 * @brief AVL tree (Header file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 08, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Atílio Gomes Luiz
 * @author Adapted by: Gustavo Gurgel Medeiros
 */

#ifndef _AVL_H_
#define _AVL_H_
#include "node.hpp"
#include "person.hpp"
#include <string>

/**
 * @brief Template class for an AVL Tree.
 *
 * @tparam T The data type of the key stored in the tree.
 */
template <typename T>
class avl_tree {
public:

  /**
   * @brief Default constructor.
   */
  avl_tree() = default;

  /**
   * @brief Class destructor. Clears the tree memory.
   */
  ~avl_tree();

  /**
   * @brief Public method to add a node. Calls the private recursive add method.
   *
   * @param key The key to add.
   * @param per Pointer to the Person associated with the key.
   */
  void add(T key, Person* per = nullptr);

  /**
   * @brief Prints a visual representation of the tree in the console.
   */
  void bshow() const;

  /**
   * @brief Clears the tree by calling the private recursive clear method.
   */
  void clear();

  /**
   * @brief Public method that prints the tree in in-order traversal.
   */
  void inorderPrint();

  /**
   * @brief Searches for a node with a specific key.
   *
   * @param key The key to search for.
   * @return Node<T>* Pointer to the found node, or nullptr if not found.
   */
  Node<T>* searchNodeByKey(T key);

  /**
   * @brief Searches for nodes that fall within a specific interval [keyMin, keyMax].
   *
   * @param keyMin The minimum boundary of the interval.
   * @param keyMax The maximum boundary of the interval.
   * @return std::vector<Node<T>*> A vector containing pointers to the nodes within the interval.
   */
  std::vector<Node<T>*> searchNodeByInterval(T keyMin, T keyMax);

  /**
   * @brief Searches for nodes that match a specific prefix.
   *
   * Since this cannot be implemented solely with standard comparators,
   * it requires a function pointer to compare if two values of type T are prefixes.
   *
   * @param prefix The prefix to search for.
   * @param isPrefix A function pointer that checks if a key matches the prefix.
   * @return std::vector<Node<T>*> A vector containing pointers to the matching nodes.
   */
  std::vector<Node<T>*> searchNodeByPrefix(T prefix, bool (*isPrefix) (const T&, const T&));

private:

  Node<T> *root{nullptr};

  /**
   * @brief Gets the height of a node.
   *
   * @param node Pointer to the node.
   * @return int The height of the node (0 if the node is nullptr).
   */
  int height(Node<T> *node);

  /**
   * @brief Gets the balance factor of a node.
   *
   * @param node Pointer to the node.
   * @return int The balance factor (right height - left height).
   */
  int balance(Node<T> *node);

  /**
   * @brief Performs a right rotation on the given node.
   *
   * @param p Pointer to the node to rotate.
   * @return Node<T>* The new root of the rotated subtree.
   */
  Node<T> *rightRotation(Node<T> *p);

  /**
   * @brief Performs a left rotation on the given node.
   *
   * @param p Pointer to the node to rotate.
   * @return Node<T>* The new root of the rotated subtree.
   */
  Node<T> *leftRotation(Node<T> *p);

  /**
   * @brief Recursive method that receives a key and adds it to the tree.
   *
   * @param p The root of the current subtree.
   * @param key The key to add.
   * @param per Pointer to the Person associated with the key.
   * @return Node<T>* The updated root of the subtree.
   */
  Node<T> *add(Node<T> *p, T key, Person* per = nullptr);

  /**
   * @brief Calculates height and balance, and fixes any balancing issues for node p.
   *
   * @param p The node to fix.
   * @param key The key that was recently added.
   * @return Node<T>* The updated and balanced node.
   */
  Node<T> *fixup_node(Node<T> *p, T key);

  /**
   * @brief Recursive method to print the tree visually.
   *
   * @param node The current node.
   * @param heranca The string representing the branch prefixes for formatting.
   */
  void bshow(Node<T> *node, std::string heranca) const;

  /**
   * @brief Recursive method that clears the tree.
   *
   * @param node The root of the subtree to clear.
   * @return Node<T>* nullptr after clearing.
   */
  Node<T> *clear(Node<T> *node);

  /**
   * @brief Private recursive method that prints the tree in in-order traversal.
   *
   * @param node The root of the subtree.
   */
  void inorderPrint(Node<T>* node);
};

#endif
