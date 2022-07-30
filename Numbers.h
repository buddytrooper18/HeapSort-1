#include <stdlib.h>
#include <stdio.h>
#ifndef numbers_h
#define numbers_h 1

const char* const ListEmptyException = "List Is Empty!";
const char* const IndexOutOfBounds = "Index out of Bounds";

template<typename T>
struct List {
  T*  items;
  int  count;
  bool copy;
  unsigned int size;

  bool checkIndex(int index) {
    return index >= 0 && index < size;
  }

  List() {
    items = NULL;
    count = 0;
    copy = false;
    size = 0;
  }

  List(T* i, int k) {
    if(k > 0 && i != NULL) {
      items = i;
      count = k;
      copy = true;
      size = count;
    }
  }

  List(int k) {
    if(k > 0) {
      count = k;
      items = new T[k]; 
      copy = false;
      size = 0;
    }
  }
  
  bool empty() const {
    return items == NULL && count == 0;
  }

  T& operator[] (const int i) {
    try {
      if(empty()) throw ListEmptyException;
      if(i < 0 || i > count) throw IndexOutOfBounds;
      return size++, items[i];
    }
    catch(const char* const e){
      printf("%s\t%d\n", e, i);
      printf("items: %u\ncount: %u\n", items, count);
      throw e;
    }
  }

  const T operator[](int i) const{
    if(!checkIndex(i)) throw IndexOutOfBounds; 
    if(empty()) throw ListEmptyException;
    return (*this)[i];
  }

  ~List() {
    if(items != NULL && count > 0) {
      if(!copy) delete items;
      items = NULL;
      count = 0;
    }
  }
};

typedef List<int> LIST_i;

class Numbers : List<int> {
  public:
    Numbers() : List<int>() {}
    Numbers(const int n) : List<int>(n) {}
    ~Numbers() {}
    int read() {
      if(!empty()) {
        int data = 0;
        bool quit = false;
        for(int i = 0; i < count; i++){
          printf("number: \n");
          scanf("%d", &data);
          ((*this)[i]) = data; //problem line
        }
      }
      return count;
    }
    void output(){
      printf("numbers: \n");
      for(int i = 0; i < count; i++)
        printf("%d\n", (*this)[i]);
    }
    operator int*() const {
      return items;
    }
};
#endif //numbers_h