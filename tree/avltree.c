#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HEIGHT 100
#define TREE_LEFT 1
#define TREE_RIGHT 2
 
/* 二分探索木のノードを表す構造体 */
struct node_t {
    int number;
    struct node_t *left;
    struct node_t *right;
};
 
/* getHeight:二分探索木のノード全てを削除する
   引数１ node : 根ノードのアドレス
   返却値 : nodeを根とした木の高さ */
int getHeight(struct node_t *node) {
    int left_height;
    int right_height;
    int tree_height;
 
    if (node == NULL) {
        /* nodeが無いなら高さは0 */
        return 0;
    }
 
    /* 左右の子を根とした木の高さを取得 */
    left_height = getHeight(node->left);
    right_height = getHeight(node->right);
 
    /* 大きい方に+1したものを木の高さとして返却 */
    if (left_height > right_height) {
        tree_height = left_height;
    }
    else {
        tree_height = right_height;
    }
 
    return tree_height + 1;
}
 
/* leftRotate:nodeを根とする部分木を回転（左）
   引数１ root : 根のノードを指すアドレス
   引数２ node : 回転する部分木の根ノードを指すアドレス
   引数３ parent : nodeの親ノードを指すアドレス
   引数４ direction : parentから見たnodeのある方向
   返却値 : 根のノードを指すアドレス */
struct node_t *leftRotate(struct node_t *root, struct node_t *node, struct node_t *parent, int direction) {
    /* nodeを根として左回転を行う */
 
    struct node_t *pivot;
    struct node_t *new_root;
 
    /* 新しい根とするノードをpivotとして設定 */
    pivot = node->right;
 
    /* 左回転 */
    if (pivot != NULL) {
        node->right = pivot->left;
        pivot->left = node;
    }
 
    /* parentもしくはrootに新しい根ノードを参照させる */
    if (parent == NULL) {
        new_root = pivot;
        return new_root;
    }
 
    /* どちらの子に設定するかはdirectionから判断 */
    if (direction == TREE_LEFT) {
        parent->left = pivot;
    }
    else {
        parent->right = pivot;
    }
    return root;
}
 
/* rightRotate:nodeを根とする部分木を回転（右）
    引数１ root : 根のノードを指すアドレス
    引数２ node : 回転する部分木の根ノードを指すアドレス
    引数３ parent : nodeの親ノードを指すアドレス
    引数４ direction : parentから見たnodeのある方向
    返却値 : 根のノードを指すアドレス */
struct node_t * rightRotate(struct node_t *root, struct node_t *node, struct node_t *parent, int direction) {
 
    struct node_t *pivot;
    struct node_t *new_root;
 
    /* 新しい根とするノードをpivotとして設定 */
    pivot = node->left;
 
    /* 右回転 */
    if (pivot != NULL) {
        node->left = pivot->right;
        pivot->right = node;
    }
 
    /* parentもしくはrootに新しい根ノードを参照させる */
    if (parent == NULL) {
        new_root = pivot;
        return new_root;
    }
 
    /* どちらの子に設定するかはdirectionから判断 */
    if (direction == TREE_LEFT) {
        parent->left = pivot;
    }
    else {
        parent->right = pivot;
    }
 
    return root;
}
 
/*  leftRightRotate:nodeを根とする部分木を二重回転（右->左）
    引数１ root : 根のノードを指すアドレス
    引数２ node : 回転する部分木の根ノードを指すアドレス
    引数３ parent : nodeの親ノードを指すアドレス
    引数４ direction : parentから見たnodeのある方向
    返却値 : 根のノードを指すアドレス */
struct node_t *rightLeftRotate(struct node_t *root, struct node_t *node, struct node_t *parent, int direction) {
    /* ２重回転（Right Left Case）を行う */
 
    struct node_t *new_root;
 
    /* nodeの右の子ノードを根として右回転 */
    new_root = rightRotate(root, node->right, node, TREE_RIGHT);
 
    /* nodeを根として左回転 */
    return leftRotate(new_root, node, parent, direction);
}
 
/*  leftRightRotate:nodeを根する部分木を二重回転（左->右）
    引数１ root : 根のノードを指すアドレス
    引数２ node : 回転する部分木の根ノードを指すアドレス
    引数３ parent : nodeの親ノードを指すアドレス
    引数４ direction : parentから見たnodeのある方向
    返却値 : 根のノードを指すアドレス */
struct node_t * leftRightRotate(struct node_t *root, struct node_t *node, struct node_t *parent, int direction) {
    /* ２重回転（Left Right Case）を行う */
 
    struct node_t *new_root;
 
    /* nodeの左の子ノードを根として左回転 */
    new_root = leftRotate(root, node->left, node, TREE_LEFT);
 
    /* nodeを根として右回転 */
    return rightRotate(new_root, node, parent, direction);
}
 
/*  balancing:nodeからbranchで辿ったノードを平衡にする
    引数１ root : 根のノードを指すアドレス
    引数２ node : 平衡にするノードを指すアドレス
    引数３ parent : nodeの親ノードを指すアドレス
    引数４ direction : parentから見たnodeのある方向
    引数５ branch : 平衡化を行うノードへの経路
    引数６ num_branch : branchに格納された経路の数
    返却値 : 根のノードを指すアドレス */
struct node_t * balancing(struct node_t *root, struct node_t *node, struct node_t *parent, int direction, int *branch, int num_branch) {
 
    struct node_t *next;
    struct node_t *new_root;
    int left_height, right_height;
    int balance;
 
    if (node == NULL || root == NULL) {
        return root;
    }
 
    if (num_branch > 0) {
        /* 辿れる場合はまず目的のノードまで辿る */
 
        /* 辿る子ノードを設定 */
        if (branch[0] == TREE_LEFT) {
        next = node->left;
        }
        else {
        next = node->right;
        }
 
        /* 子ノードを辿る */
        new_root = balancing(root, next, node, branch[0], &branch[1], num_branch - 1);
    }
    
    /* 平衡係数を計算 */
    left_height = getHeight(node->left);
    right_height = getHeight(node->right);
    balance = right_height - left_height;
  
    if (balance > 1) {
        /* 右の部分木が高くて並行状態でない場合 */
 
        /* ２重回転が必要かどうかを判断 */
        if (getHeight(node->right->left) > getHeight(node->right->right)) {
        /* ２重回転（Right Left Case）*/
        return rightLeftRotate(new_root, node, parent, direction);
        }
        else {
        /*１重回転（左回転）*/
        return leftRotate(new_root, node, parent, direction);
        }
    }
    else if (balance < -1) {
        /* 左の部分木が高くて並行状態でない場合 */
 
        /* ２重回転が必要かどうかを判断 */
        if (getHeight(node->left->right) > getHeight(node->left->left)) {
        /* ２重回転（Left Right Case）*/
        return leftRightRotate(new_root, node, parent, direction);
        }
        else {
        /* １重回転（右回転）*/
        return rightRotate(new_root, node, parent, direction);
        }
    }
 
    return root;
}
 
/*  deleteTree:二分探索木のノード全てを削除する
    引数１ root : 根ノードのアドレス
    返却値 : なし */
void deleteTree(struct node_t *root){
    if(root == NULL){
        return;
    }
 
    if(root->left != NULL){
        deleteTree(root->left);
    }
    if(root->right != NULL){
        deleteTree(root->right);
    }
 
    free(root);
 
}
 
/*  mallocNode:ノードの構造体のメモリを確保し、データを設定
    引数１ number : 追加する会員番号
    引数２ name : 追加する会員の名前
    返却値 : 追加したノードのアドレス */
struct node_t *mallocNode(int number){
    struct node_t *add;
 
    add = (struct node_t*)malloc(sizeof(struct node_t));
    if(add == NULL){ 
        return NULL;
    }
 
    add->left = NULL;
    add->right = NULL;
    add->number = number;
    return add;
}
 
/*  addNode:指定されたnumberとname持つノードを追加する
    引数１ root : 根ノードのアドレス
    引数２ number : 追加する会員番号
    引数３ name : 追加する会員の名前
    返却値 : 根ルートのアドレス */
struct node_t *addNode(struct node_t *root, int number){
    struct node_t *node;
    int branch[MAX_HEIGHT] = {0};
    int num_branch = 0;
 
    /* まだノードが一つもない場合 */
    if(root == NULL){
        /* 根ノードとしてノードを追加 */
        root = mallocNode(number);
        if(root == NULL){
        printf("malloc error\n");
        return NULL;
        }
        return root;
    }
 
    /* 根ノードから順に追加する場所を探索 */
    node = root;
    while(1) {
        if(number < node->number){
        /* 追加する値がノードの値よりも小さい場合 */
 
        if(node->left == NULL){
            /* そのノードの左の子が無い場合（もう辿るべきノードが無い場合）*/
 
            /* その左の子の位置にノードを追加 */
            node->left = mallocNode(number);
 
            /* 追加完了したので処理終了 */
            break;
        }
 
        /* 左ノードを辿ったことを覚えておく */
        branch[num_branch] = TREE_LEFT;
        num_branch++;
        
        /* 左の子がある場合は左の子を新たな注目ノードに設定 */
        node = node->left;
 
        }
        else if(number > node->number){
        /* 追加する値がノードの値よりも大きい場合 */
 
        if(node->right == NULL){
            /* そのノードの右の子が無い場合（もう辿るべきノードが無い場合）*/
 
            /* その右の子の位置にノードを追加 */
            node->right = mallocNode(number);
 
            /* 追加完了したので処理終了 */
            break;
        }
 
        /* 右ノードを辿ったことを覚えておく */
        branch[num_branch] = TREE_RIGHT;
        num_branch++;
 
        /* 右の子がある場合は右の子を新たな注目ノードに設定 */
        node = node->right;
        }
        else {
            /* 追加する値とノードの値が同じ場合 */
            printf("%d already exist\n", number);
            break;
        }
    }
    
    return balancing(root, root, NULL, 0, branch, num_branch);
}
 
/*  searchNode:指定されたnumberを持つノードを探索する
    引数１ root : 探索を開始するノードのアドレス
    引数２ number : 探索する会員番号
    返却値 : number を持つノードのアドレス（存在しない場合は NULL）*/
struct node_t *searchNode(struct node_t *root, int number){
    struct node_t *node;
  
    node = root;
 
    /* 探索を行うループ（注目ノードがNULLになったら終了 */
    while(node){
        if(number < node->number){
            /* 探索値がノードの値よりも小さい場合 */
 
            /* 注目ノードを左の子ノードに設定 */
            node = node->left;
        }
        else if(number > node->number){
            /* 探索値がノードの値よりも大きい場合 */
 
            /* 注目ノードを右の子ノードに設定 */
            node = node->right;
        }
        else {
            /* 探索値 = ノードの値の場合 */
            return node;
        }
    }
    
    /* 探索値を持つノードが見つからなかった場合 */
    return NULL;
}
 
/*  deleteNoChildeNode:指定された子の無いノードを削除する
    引数１ root : 木の根ノードのアドレス
    引数２ node : 削除するノードのアドレス
    引数３ parent：削除するノードの親ノードのアドレス
    返却値 : 根ノードのアドレス */
struct node_t *deleteNoChildNode(struct node_t *root, struct node_t *node, struct node_t *parent){
 
    if(parent != NULL){
        /* 親がいる場合（根ノード以外の場合）は
     削除対象ノードを指すポインタをNULLに設定 */
        if(parent->left ==  node){
            /* 削除対象ノードが親ノードから見て左の子の場合 */
            parent->left = NULL;
        }
        else {
            /* 削除対象ノードが親ノードから見て右の子の場合 */
            parent->right = NULL;
        }
        free(node);
    }
    else {
        /* 削除対象ノードが根ノードの場合 */
        free(node);
      
        /* 根ノードを指すポインタをNULLに設定 */
        root = NULL;
    }
    
    return root;
}
 
/*  deleteOneChildeNode:指定された子が一つのノードを削除する
    引数１ root : 木の根ノードのアドレス
    引数２ node : 削除するノードのアドレス
    引数３ child : 削除するノードの子ノードのアドレス
    返却値 : 根ノードのアドレス */
struct node_t *deleteOneChildNode(struct node_t *root, struct node_t *node, struct node_t * child){
   
    /* 削除対象ノードにその子ノードのデータとポインタをコピー */
    node->number = child->number;
    node->left = child->left;
    node->right = child->right;
    
    /* コピー元のノードを削除 */
    free(child);
  
    return root;
}
 
/*  deleteTwoChildeNode:指定された子が二つのノードを削除する
    引数１ root : 木の根ノードのアドレス
    引数２ node : 削除するノードのアドレス
    返却値 : 根ノードのアドレス */
struct node_t *deleteTwoChildNode(struct node_t *root, struct node_t *node, int *branch, int *num_branch){
 
    struct node_t *max;
    struct node_t *maxParent;
  
    /* 左の子から一番大きい値を持つノードを探索 */
    max = node->left;
    maxParent = node;
 
    /* 左の子ノードを辿ったことを覚えておく */
    branch[*num_branch] = TREE_LEFT;
    (*num_branch)++;
    
    while(max->right != NULL){
        maxParent = max;
        max = max->right;
 
        /* 右の子ノードを辿ったことを覚えておく */
        branch[*num_branch] = TREE_RIGHT;
        (*num_branch)++;
    }
    
    /* 最大ノードのデータのみ削除対象ノードにコピー */
    node->number = max->number;
    
    /* 最大ノードを削除 */
  
    /* maxは最大ノードなので必ずmax->rightはNULLになる */
    if(max->left == NULL){
        /* 最大ノードに子がいない場合 */
        root = deleteNoChildNode(root, max, maxParent);      
    }
    else {
        /* 最大ノードに子供が一ついる場合 */
        root = deleteOneChildNode(root, max, max->left);
    }
 
    return root;
}
 
/* deleteNode:指定されたnumberを持つノードを削除する
   引数１ root : 木の根ノードのアドレス
   引数２ number : 削除する会員番号
   返却値 : 根ノードのアドレス */
struct node_t *deleteNode(struct node_t *root, int number){
    struct node_t *node;
    struct node_t *parent;
    int branch[MAX_HEIGHT] = {0};
    int num_branch = 0;
 
    if(root == NULL){
        return NULL;
    }
 
    /* 削除対象ノードを指すノードを探索 */
    node = root;
    parent = NULL;
  
    while(node !=  NULL){
        if(number < node->number){
            parent = node;
            node = node->left;
 
            /* 左の子ノードを辿ったことを覚えておく */
            branch[num_branch] = TREE_LEFT;
            num_branch++;
        }
        else if(number > node->number){
            parent = node;
            node = node->right;
 
            /* 右の子ノードを辿ったことを覚えておく */
            branch[num_branch] = TREE_RIGHT;
            num_branch++;
        }
        else {
            break;
        }
    }
  
    /* 指定されたnumberを値として持つノードが存在しない場合は何もせず終了 */
    if(node == NULL){
        printf("%d を持つノードが存在しません。\n", number);
        return root;
    }
 
    printf("Delete %d node\n", node->number);
 
    if(node->left == NULL && node->right == NULL){    
        /* 子がいないノードの削除 */
        root = deleteNoChildNode(root, node, parent);
    }
    else if((node->left != NULL && node->right == NULL) ||(node->right != NULL && node->left == NULL)){
        /* 子が一つしかない場合 */
        
        if(node->left != NULL){
        root = deleteOneChildNode(root, node, node->left);
        }
        else {
        root = deleteOneChildNode(root, node, node->right);
        }
    }
    else {
        /* 左の子と右の子両方がいるノードの削除 */
        root = deleteTwoChildNode(root, node, branch, &num_branch);
    }
    
    return balancing(root, root, NULL, 0, branch, num_branch);
}
 
/*  printTree:rootを根ノードとする二分探索木をの全ノードを表示する
    引数１ root : 木の根ノードのアドレス
    引数２ depth: 関数呼び出しの深さ
    返却値 : なし */
void printTree(struct node_t *root, int depth){
    int i;
 
    if(root == NULL){
    return ;
    }
 
    /* 右の子孫ノードを表示 */
    printTree(root->right, depth+1);
 
    /* 深さをスペースで表現 */ 
    for(i = 0; i < depth; i++){
        printf("    ");
    }
 
    /* ノードのデータを表示 */
    printf("+%3d\n", root->number);
 
    /* 左の子孫ノードを表示 */
    printTree(root->left, depth+1);
 
    depth++;
}
 
int main(void){
    struct node_t *root, *node;
    int input;
    int number;
    int loop;
 
    /* まだ木がないのでrootをNULLにセット */
    root = NULL;
 
    loop = 1;
    while(loop){
        printf("処理を選択(1:追加, 2:削除, 3:検索, 4:終了) : ");
        scanf("%d", &input);
 
        switch(input){
        case 1:
            printf("number(1 - 999):");
            scanf("%d", &number);
            if(number < 1 || number > 999){
                printf("値が範囲外です\n");
                continue;
            }
            root = addNode(root, number);
            break;
        case 2:
            printf("number(1 - 999):");
            scanf("%d", &number);
            if(number < 1 || number > 999){
                printf("値が範囲外です\n");
                continue;
            }
 
            root = deleteNode(root, number);
            break;
        case 3:
            printf("number(1 - 999):");
            scanf("%d", &number);
            if(number < 1 || number > 999){
                printf("値が範囲外です\n");
                continue;
            }
        
            node = searchNode(root, number);
            if(node == NULL){
                printf("number %d is not found\n", number);
            }
            else {
            printf("number %d\n", number);
            }
            break;
        default:
            loop = 0;
            break;
        }
        printTree(root, 0);
    }
 
    deleteTree(root);   
  
    return 0;
}

