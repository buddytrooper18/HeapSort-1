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
      Node<T>* pn = nullptr;
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

    Node<T>* moveLeftRight(T data) {
      if(left == nullptr || right == nullptr) return addNode(data);
	    	if(this->left->data > data) {
	    		return getRoot()->place(left->swapData(data));
	    	}
	    	if(this->right->data > data) {
	    		return getRoot()->place(right->swapData(data));
	    	}
      return nullptr;
    }

    Node<T>* moveDown(T data) {
      Node<T>* pn = nullptr;
      if(left != nullptr) {
        pn = left->place(data);
        if(pn != nullptr) return pn;
      }
      if(right != nullptr) {
        pn = right->place(data);
        if(pn != nullptr) return pn;
      }
      return addNode(data);
    }

    void swapLeftRight() {
      Node<T>* temp = left;
      left = right;
      right = temp;
    }

    Node<T>* addNode(T data) {
      Node<T>* node = new Node<T>(data);
      if(left != nullptr && right != nullptr){
        node->parent = left;
        return node;
      }
      if(left != nullptr){
        right = node;
        swapLeftRight();
        node->parent = left->parent;
        return node;
      }
      if(right != nullptr && data > right->data){
        left = right;
        right = node;
        node->parent = this;
        return node;
      }
      node->parent = this;
      left = node;
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
      int i = 0;
      while(i < List<T>::count) {
        node->getData(i, *this);
      }
    }
};
#endif //binary_tree_h