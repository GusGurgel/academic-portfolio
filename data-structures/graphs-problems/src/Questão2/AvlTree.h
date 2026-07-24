/**************************************************
//
// Projeto 1 - Estrutura de Dados Avançada UFC
//
// AVL tree (Header file)
//
// Criação:     08 Mai 2023
// Atualização: 08 Mai 2023
//
// Criado Por:
// Nome: Atílio Gomes Luiz
//
// Arquivo Adaptado por:
// Gustavo Gurgel Medeiros
// Número de Matrícula [UFC]: 539226
************************************************/

#ifndef _AVL_H_
#define _AVL_H_
#include <string>
#include <algorithm>
#include <vector>
#include <string>

using std::max;
using std::vector;
using std::stack;
using std::string;

//Estrutura de nó
template <typename T> struct Node {
  // atributos
  T key;
  int height;
  Node<T> *left;
  Node<T> *right;

  // Construtor
  Node(T key, Node *left = nullptr, Node *right = nullptr, int height = 1)
      : key(key), height(height), left(left), right(right) {}
};

template <typename T> class AvlTree {
public:
  AvlTree() = default;

  /*--------------{add}----------------
   > Chamada recursiva do método pri-
   > vado recursivo add.
  -----------------------------------*/
  void add(T key){
    root = add(root, key);
  }
  
  void bshow() const{
    bshow(root, ""); 
  }
  
  void clear(){
    root = clear(root); 
  }
  
  ~AvlTree(){
    clear();
  }

  void inoderVec(vector<T>& vec){
    vec.clear();

    stack<Node<T>*> st;
    Node<T>* curr = root;

    while (!st.empty() || curr != nullptr)
    {
        if (curr != nullptr)
        {
            st.push(curr);
            curr = curr->left;
        }
        else {
            curr = st.top();
            st.pop();
            
            vec.push_back(curr->key);
 
            curr = curr->right;
        }
    }
  }

private:
  Node<T> *root{nullptr};

  /*-------{heigth}---------
   > retorna a alura do nó.
   > se é vazio, então a
   > altura é zero
  ------------------------*/
  int height(Node<T> *node){
    return (node == nullptr) ? 0 : node->height;
  }

  /*--------{balance}----------
   > retorna o balanço do nó
   > baseado nas alturas direta
   > e esquerda.
  ----------------------------*/
  int balance(Node<T> *node){
    return height(node->right) - height(node->left);
  }

  /*-------{rightRotation}---------
   > efetura rotação a direita no
   > nó p.
  --------------------------------*/
  Node<T> *rightRotation(Node<T> *p){
    Node<T> *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left), height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));
    return u;
  }

  /*-------{leftRotation}---------
   > efetura rotação a esquerda no
   > nó p.
  --------------------------------*/
  Node<T> *leftRotation(Node<T> *p){
    Node<T> *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right), height(p->left));
    u->height = 1 + max(height(u->left), height(u->right));
    return u;
  }

  /*--------------{add}----------------
   > método que recebe uma chave (key)
   > e adiciona (de forma recursiva)
   > na árvore. Se a chave já estiver,
   > então não faz nada.
  -----------------------------------*/
  Node<T> *add(Node<T> *p, T key){
    if (p == nullptr)
      return new Node<T>(key);
    if (key == p->key)
      return p;
    if (key < p->key)
      p->left = add(p->left, key);
    else
      p->right = add(p->right, key);

    p = fixup_node(p, key);

    return p;
  }
  
  /*---------{fixup_node}-----------
   > Calcula altura e balanço e re-
   > solve problemas de balancea-
   > mento do nó p.
  ---------------------------------*/
  Node<T> *fixup_node(Node<T> *p, T key){
    // recalcula a altura de p
    p->height = 1 + max(height(p->left), height(p->right));

    // calcula o balanço do p
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

  /*---------{clear}-----------
   > método recursivo que limpa
   > a árvore.
  ----------------------------*/  
  Node<T> *clear(Node<T> *node){
    if (node != nullptr) {
      node->left = clear(node->left);
      node->right = clear(node->right);
      delete node;
    }
    return nullptr;
  }

  void bshow(Node<T> *node, std::string heranca) const{
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
    std::cout << node->key << std::endl;
    if (node != nullptr && (node->left != nullptr || node->right != nullptr))
      bshow(node->left, heranca + "l");
  }
};

#endif