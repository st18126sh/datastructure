#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "redblack.h"
#include "fatal.h"


struct RedBlackNode;
typedef struct RedBlackNode *Position;
typedef struct RedBlackNode *RedBlackTree;
typedef int ElementType;
typedef enum ColorType {Red,Black} ColorType;
struct RedBlackNode{
  ElementType Element;
  ColorType Collar;
  RedBlackTree Left;
  RedBlackTree Right;
  int Height;
};

//ŠÖ”
RedBlackTree MakeEmpty(RedBlackTree T);
Position Find(ElementType X, RedBlackTree T);
Position FindMin(RedBlackTree T);
Position FindMax(RedBlackTree T);
RedBlackTree Insert(ElementType X, RedBlackTree T);
RedBlackTree Delete(ElementType X, RedBlackTree T);

//Max
static int Max(ElementType X, ElementType Y){
  return (X)>(Y)?(X):(Y);
}

//Height
static int Height( Position P ){
  if (P == NULL){
    return -1;
  }
  else{
    return P->Height;
  }
}

//SingleRotateWithRight
static Position SingleRotateWithRight (Position K1){
  Position K2;
  K2 = K1->Right;
  K1->Right = K2->Left;
  K2->Left= K1;

  /*Recalculate Height of tree*/
  K1->Height = Max( Height(K1->Right), Height(K1->Left)) + 1;
  K2->Height = Max( Height(K2->Right), K1->Height) + 1;

  return K2;

}
static Position SingleRotateWithLeft (Position K2){
  /*
   *            K2                         K2        (K2's left Point to K1->Right)       (K1->Right Point to K2)
   *           /                          /                                                  K1->(K1)'                
   *         (K1)'       ====>      K1->(K1)'    ====>    K1->(K1)'   K2            ====>     /    \
   *        /   \                       /  \                  /  \   /                       A      K2
   *       A     B                     A    B                A     B                                 /
   *                                                                                                 B
   *
   * /              
  /*This K1 isn't (K1)'. This K1 will be a new root after rotate*/

  Position K1;
  K1 = K2->Left;
  K2->Left = K1->Right;
  K1->Right = K2;

  /*Recalculate Height of tree*/
  K2->Height = Max( Height(K2->Left), Height(K2->Right)) + 1;
  K1->Height = Max( Height(K1->Left), K2->Height) + 1;

  return K1;

}

static Position DoubleRotateWithLeft(Position K3){
  /*K3 is root of tree*/
  /*
   * DoubleRotate is component of two single rotates
   *               K3                  K3                 K2
   *              /  \                /  \               /  \
   *            K1    D             K2    D             K1   K3   
   *           /  \       ===>     /  \       ===>     /  \ /  \
   *          A    K2             K1   C              A   B C   D
   *              /  \           /  \
   *             B    C         A    B 
   *
   */
  /*Rotate between K1 and K2*/

  K3->Left = SingleRotateWithRight(K3->Left);

  return SingleRotateWithLeft(K3);
}
static Position DoubleRotateWithRight(Position K3){
  /*K3 is root of tree*/
  /*
   * DoubleRotate is component of two single rotates
   *
   */
  /*Rotate between K1 and K2*/

  K3->Right = SingleRotateWithLeft(K3->Right);

  return SingleRotateWithRight(K3);
}

//Insert
RedBlackTree Insert(ElementType X, RedBlackTree T){
  if (T == NULL){
    T = (struct RedBlackNode*)malloc(sizeof (struct RedBlackNode));
    if (T == NULL) {
      perror("malloc");
      exit(1);
    }else{
      T->Element = X; T->Height = 0;
      T->Left = T->Right = NULL;
    }
  }
  else if (X < T->Element){
    T->Left = Insert(X, T->Left);
    if (Height(T->Left) - Height(T->Right) == 2){
      if (X < T->Left->Element){
         T = SingleRotateWithLeft(T);
      }else{
         T = DoubleRotateWithLeft(T); 
      }
    }
  }
  else if (X > T->Element){
    T->Right = Insert(X, T->Right);
    if (Height(T->Right) - Height(T->Left) == 2){
      if (X > T->Right->Element){
        T=SingleRotateWithRight(T);
      }else{
        T=DoubleRotateWithRight(T);
      }
    }
  }
  T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
  return T;
}
//show
void show(RedBlackTree T){
  if (T == NULL){
    return;
  }else{
    printf("James:%d Collar:%d\n", T->Element,T->Collar);
    show(T->Left);
    show(T->Right);
  }
}
//main
int main(int argc, char **argv){
  int max = 16;
  int i;
  RedBlackTree T=NULL;
  while(max--){
    scanf("%d\n", &i);
    T=Insert(i, T);
  }
  show(T);
	return 0;
}
