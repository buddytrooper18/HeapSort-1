#include <iostream>
#include "Numbers.h"
#include "BinaryTree.h"

int main() {
  int  count;
  /*printf("count: \n");
  scanf("%d", &count);
  if(count > 0) {
    Numbers num(count);
    num.read();
    num.output();*/
    int  fn[] = {13, 3, 7};
    count = sizeof(fn) / sizeof(int);
    Numbers num = Numbers(fn, count);
    BinaryTree<int> bt((int*)num, count);
    bt.build();
    bt.print();
    bt.load();
  //}
  
}

