#include <iostream>
#include "Numbers.h"
#include "BinaryTree.h"

int main() {
  int  count;
  printf("count: \n");
  scanf("%d", &count);
  if(count > 0) {
    Numbers num(count);
    num.read();
    num.output();
    BinaryTree<int> bt((int*)num, count);
    bt.build();
    bt.load();
  }
  
}

