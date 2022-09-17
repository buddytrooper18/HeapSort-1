#include <stdlib.h>
#include "Numbers.h"
#ifndef binary_tree_h
#define binary_tree_h 1

template <typename T>
class Node {
  protected:
    Node* left;
    Node* right;
    Node* parent;
    T data;

    Node<T>* place(T data) {
      printf("place: data = %d\n", data);
      Node<T>* pn = nullptr;
      printNode();
      if(this->data != data){
        if(this->data > data){
          return this->getRoot()->place(swapData(data));
        }
        pn = moveLeftRight(data);
        return pn != nullptr ? pn : moveDown(data);
      }
      return this;
    }

    T swapData(T data) {
      T temp = this->data;
      this->data = data;
      return temp;
    }

    Node<T>* placeyThing(bool rootYN) {
      return rootYN ? getRoot() : this;
    }

    Node<T>* moveLeftRight(T data) {
      printf("moveLeftRight: ...\n");
      printNode();
      Node<T>* n = placeyThing(false);
      if(left != nullptr && left->data > data) return n->place(left->swapData(data));
      if(right != nullptr && right->data > data) return n->place(right->swapData(data));
      if(left != nullptr && right == nullptr)
        return addNode(data);
      return nullptr;
    }

    Node<T>* moveDown(T data) {
      printf("moveDown: ...\n");
      printNode();
      Node<T>* pn = nullptr;
      if(left != nullptr) {
        pn = left->place(data); //needs fixin
        if(pn != nullptr) return pn;
      }
      if(right != nullptr) {
        pn = right->place(data); //needz fixing as well
        if(pn != nullptr) return pn;
      }
      return addNode(data);
    }

    bool swapLeftRight() {
      if(left != nullptr && right != nullptr && left->data > right->data){
        Node<T>* temp = left;
        left = right;
        right = temp;
        return true;
      }
      return false;
    }

    Node<T>* addNode(T data) {
      printf("addNode: ...\n");
      printNode();
      Node<T>* node = new Node<T>(data);
      if(left != nullptr && right != nullptr){
        node->parent = left;
        printf("%d\n", __LINE__);
        return node;
      }
      if(left != nullptr){
        right = node;
        swapLeftRight();
        node->parent = left->parent;
        printf("%d\n", __LINE__);
        left->printNode();
        printNode();
        return node;
      }
      if(right != nullptr && data > right->data){
        left = right;
        right = node;
        node->parent = this;
        printf("%d\n", __LINE__);
        right->printNode();
        printNode();
        return node;
      }
      node->parent = this;
      left = node;
      printf("%d\n", __LINE__);
      node->printNode();
      return node;
    }
    
    Node<T>* getRoot() {
      Node<T>* root = this;
      while(root->parent != nullptr) root = root->parent;
      return root;
    }  

    Node<T>* switchNode(Node<T>* c, Node<T>* root) {
      if(left != nullptr) {
        switchData(c);
        return root->place(c, root);
      }
      if(right != nullptr) {
        switchData(c);
        return root->place(c, root);
      }
    }

    void switchData(Node<T>* node) {
      if(node != nullptr) {
        T temp = this->data;
        this->data = node->data;
        node->data = temp;
      }
    }

    void getData(int& i, List<T> dat) {
      dat[i] = this->data;
      if(left != nullptr) left->getData(i, dat);
      if(right != nullptr) right->getData(i, dat);
      i++;
    }

    T* load(T* pd) {
      if(pd != nullptr) {
        *pd = data;
        return pd + 1;
      }
      return pd;
    }

  public:
    Node() {
      left = right = parent = NULL;
      data = (T)0;
    }
    Node(T d, Node* l = NULL, Node* r = NULL, Node* p = NULL) {
      left = l;
      right = r;
      parent = p;
      data = d;
    }

    T* loadItems(T* pd) {
      T* pll = load(pd);
      if(left != nullptr) pll = left->loadItems(pll);
      if(right != nullptr) pll = right->loadItems(pll);
      return pll;
    }

    void printNode(){
      printf("parent = %x\tnode = %x\tleft = %x\tright = %x\tdata = %d\n", parent, this, left, right, data);
    }

    void print(int& i) {
      printf("%d. ", i++);
      printNode();
      if(left != nullptr) left->print(i);
      if(right != nullptr) right->print(i);
    }
};
typedef Node<double> NODE_d;
typedef Node<int> NODE_i;

template <typename T>
class BinaryTree : public Node<T>, List<T> {
  public: 
    BinaryTree() : Node<T>(), List<T>() {}
    BinaryTree(T* nums, int count) : Node<T>(), List<T>(nums, count) {}
    
    void build() {
      this->data = (*this)[0];
      for(int i = 1; i < List<T>::count; i++){
        this->place((*this)[i]);
      }
    }

    void load() {
      Node<T>* node = this->getRoot();
      T* pdata = List<T>::items;
      node->loadItems(pdata);
    }
    
    void print() {
      Node<T>* node = this->getRoot();
      int i = 0;
      node->print(i);
    }

    void output(){
      List<int>::output("numbers: \n", "%d\n");
    }
};
#endif //binary_tree_h