#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HEIGHT 100
#define TREE_LEFT 1
#define TREE_RIGHT 2
 
/* �񕪒T���؂̃m�[�h��\���\���� */
struct node_t {
    int number;
    struct node_t *left;
    struct node_t *right;
};
 
/* getHeight:�񕪒T���؂̃m�[�h�S�Ă��폜����
   �����P node : ���m�[�h�̃A�h���X
   �ԋp�l : node�����Ƃ����؂̍��� */
int getHeight(struct node_t *node) {
    int left_height;
    int right_height;
    int tree_height;
 
    if (node == NULL) {
        /* node�������Ȃ獂����0 */
        return 0;
    }
 
    /* ���E�̎q�����Ƃ����؂̍������擾 */
    left_height = getHeight(node->left);
    right_height = getHeight(node->right);
 
    /* �傫������+1�������̂�؂̍����Ƃ��ĕԋp */
    if (left_height > right_height) {
        tree_height = left_height;
    }
    else {
        tree_height = right_height;
    }
 
    return tree_height + 1;
}
 
/* leftRotate:node�����Ƃ��镔���؂���]�i���j
   �����P root : ���̃m�[�h���w���A�h���X
   �����Q node : ��]���镔���؂̍��m�[�h���w���A�h���X
   �����R parent : node�̐e�m�[�h���w���A�h���X
   �����S direction : parent���猩��node�̂������
   �ԋp�l : ���̃m�[�h���w���A�h���X */
struct node_t *leftRotate(struct node_t *root, struct node_t *node, struct node_t *parent, int direction) {
    /* node�����Ƃ��č���]���s�� */
 
    struct node_t *pivot;
    struct node_t *new_root;
 
    /* �V�������Ƃ���m�[�h��pivot�Ƃ��Đݒ� */
    pivot = node->right;
 
    /* ����] */
    if (pivot != NULL) {
        node->right = pivot->left;
        pivot->left = node;
    }
 
    /* parent��������root�ɐV�������m�[�h���Q�Ƃ����� */
    if (parent == NULL) {
        new_root = pivot;
        return new_root;
    }
 
    /* �ǂ���̎q�ɐݒ肷�邩��direction���画�f */
    if (direction == TREE_LEFT) {
        parent->left = pivot;
    }
    else {
        parent->right = pivot;
    }
    return root;
}
 
/* rightRotate:node�����Ƃ��镔���؂���]�i�E�j
    �����P root : ���̃m�[�h���w���A�h���X
    �����Q node : ��]���镔���؂̍��m�[�h���w���A�h���X
    �����R parent : node�̐e�m�[�h���w���A�h���X
    �����S direction : parent���猩��node�̂������
    �ԋp�l : ���̃m�[�h���w���A�h���X */
struct node_t * rightRotate(struct node_t *root, struct node_t *node, struct node_t *parent, int direction) {
 
    struct node_t *pivot;
    struct node_t *new_root;
 
    /* �V�������Ƃ���m�[�h��pivot�Ƃ��Đݒ� */
    pivot = node->left;
 
    /* �E��] */
    if (pivot != NULL) {
        node->left = pivot->right;
        pivot->right = node;
    }
 
    /* parent��������root�ɐV�������m�[�h���Q�Ƃ����� */
    if (parent == NULL) {
        new_root = pivot;
        return new_root;
    }
 
    /* �ǂ���̎q�ɐݒ肷�邩��direction���画�f */
    if (direction == TREE_LEFT) {
        parent->left = pivot;
    }
    else {
        parent->right = pivot;
    }
 
    return root;
}
 
/*  leftRightRotate:node�����Ƃ��镔���؂��d��]�i�E->���j
    �����P root : ���̃m�[�h���w���A�h���X
    �����Q node : ��]���镔���؂̍��m�[�h���w���A�h���X
    �����R parent : node�̐e�m�[�h���w���A�h���X
    �����S direction : parent���猩��node�̂������
    �ԋp�l : ���̃m�[�h���w���A�h���X */
struct node_t *rightLeftRotate(struct node_t *root, struct node_t *node, struct node_t *parent, int direction) {
    /* �Q�d��]�iRight Left Case�j���s�� */
 
    struct node_t *new_root;
 
    /* node�̉E�̎q�m�[�h�����Ƃ��ĉE��] */
    new_root = rightRotate(root, node->right, node, TREE_RIGHT);
 
    /* node�����Ƃ��č���] */
    return leftRotate(new_root, node, parent, direction);
}
 
/*  leftRightRotate:node�������镔���؂��d��]�i��->�E�j
    �����P root : ���̃m�[�h���w���A�h���X
    �����Q node : ��]���镔���؂̍��m�[�h���w���A�h���X
    �����R parent : node�̐e�m�[�h���w���A�h���X
    �����S direction : parent���猩��node�̂������
    �ԋp�l : ���̃m�[�h���w���A�h���X */
struct node_t * leftRightRotate(struct node_t *root, struct node_t *node, struct node_t *parent, int direction) {
    /* �Q�d��]�iLeft Right Case�j���s�� */
 
    struct node_t *new_root;
 
    /* node�̍��̎q�m�[�h�����Ƃ��č���] */
    new_root = leftRotate(root, node->left, node, TREE_LEFT);
 
    /* node�����Ƃ��ĉE��] */
    return rightRotate(new_root, node, parent, direction);
}
 
/*  balancing:node����branch�ŒH�����m�[�h�𕽍t�ɂ���
    �����P root : ���̃m�[�h���w���A�h���X
    �����Q node : ���t�ɂ���m�[�h���w���A�h���X
    �����R parent : node�̐e�m�[�h���w���A�h���X
    �����S direction : parent���猩��node�̂������
    �����T branch : ���t�����s���m�[�h�ւ̌o�H
    �����U num_branch : branch�Ɋi�[���ꂽ�o�H�̐�
    �ԋp�l : ���̃m�[�h���w���A�h���X */
struct node_t * balancing(struct node_t *root, struct node_t *node, struct node_t *parent, int direction, int *branch, int num_branch) {
 
    struct node_t *next;
    struct node_t *new_root;
    int left_height, right_height;
    int balance;
 
    if (node == NULL || root == NULL) {
        return root;
    }
 
    if (num_branch > 0) {
        /* �H���ꍇ�͂܂��ړI�̃m�[�h�܂ŒH�� */
 
        /* �H��q�m�[�h��ݒ� */
        if (branch[0] == TREE_LEFT) {
        next = node->left;
        }
        else {
        next = node->right;
        }
 
        /* �q�m�[�h��H�� */
        new_root = balancing(root, next, node, branch[0], &branch[1], num_branch - 1);
    }
    
    /* ���t�W�����v�Z */
    left_height = getHeight(node->left);
    right_height = getHeight(node->right);
    balance = right_height - left_height;
  
    if (balance > 1) {
        /* �E�̕����؂������ĕ��s��ԂłȂ��ꍇ */
 
        /* �Q�d��]���K�v���ǂ����𔻒f */
        if (getHeight(node->right->left) > getHeight(node->right->right)) {
        /* �Q�d��]�iRight Left Case�j*/
        return rightLeftRotate(new_root, node, parent, direction);
        }
        else {
        /*�P�d��]�i����]�j*/
        return leftRotate(new_root, node, parent, direction);
        }
    }
    else if (balance < -1) {
        /* ���̕����؂������ĕ��s��ԂłȂ��ꍇ */
 
        /* �Q�d��]���K�v���ǂ����𔻒f */
        if (getHeight(node->left->right) > getHeight(node->left->left)) {
        /* �Q�d��]�iLeft Right Case�j*/
        return leftRightRotate(new_root, node, parent, direction);
        }
        else {
        /* �P�d��]�i�E��]�j*/
        return rightRotate(new_root, node, parent, direction);
        }
    }
 
    return root;
}
 
/*  deleteTree:�񕪒T���؂̃m�[�h�S�Ă��폜����
    �����P root : ���m�[�h�̃A�h���X
    �ԋp�l : �Ȃ� */
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
 
/*  mallocNode:�m�[�h�̍\���̂̃��������m�ۂ��A�f�[�^��ݒ�
    �����P number : �ǉ��������ԍ�
    �����Q name : �ǉ��������̖��O
    �ԋp�l : �ǉ������m�[�h�̃A�h���X */
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
 
/*  addNode:�w�肳�ꂽnumber��name���m�[�h��ǉ�����
    �����P root : ���m�[�h�̃A�h���X
    �����Q number : �ǉ��������ԍ�
    �����R name : �ǉ��������̖��O
    �ԋp�l : �����[�g�̃A�h���X */
struct node_t *addNode(struct node_t *root, int number){
    struct node_t *node;
    int branch[MAX_HEIGHT] = {0};
    int num_branch = 0;
 
    /* �܂��m�[�h������Ȃ��ꍇ */
    if(root == NULL){
        /* ���m�[�h�Ƃ��ăm�[�h��ǉ� */
        root = mallocNode(number);
        if(root == NULL){
        printf("malloc error\n");
        return NULL;
        }
        return root;
    }
 
    /* ���m�[�h���珇�ɒǉ�����ꏊ��T�� */
    node = root;
    while(1) {
        if(number < node->number){
        /* �ǉ�����l���m�[�h�̒l�����������ꍇ */
 
        if(node->left == NULL){
            /* ���̃m�[�h�̍��̎q�������ꍇ�i�����H��ׂ��m�[�h�������ꍇ�j*/
 
            /* ���̍��̎q�̈ʒu�Ƀm�[�h��ǉ� */
            node->left = mallocNode(number);
 
            /* �ǉ����������̂ŏ����I�� */
            break;
        }
 
        /* ���m�[�h��H�������Ƃ��o���Ă��� */
        branch[num_branch] = TREE_LEFT;
        num_branch++;
        
        /* ���̎q������ꍇ�͍��̎q��V���Ȓ��ڃm�[�h�ɐݒ� */
        node = node->left;
 
        }
        else if(number > node->number){
        /* �ǉ�����l���m�[�h�̒l�����傫���ꍇ */
 
        if(node->right == NULL){
            /* ���̃m�[�h�̉E�̎q�������ꍇ�i�����H��ׂ��m�[�h�������ꍇ�j*/
 
            /* ���̉E�̎q�̈ʒu�Ƀm�[�h��ǉ� */
            node->right = mallocNode(number);
 
            /* �ǉ����������̂ŏ����I�� */
            break;
        }
 
        /* �E�m�[�h��H�������Ƃ��o���Ă��� */
        branch[num_branch] = TREE_RIGHT;
        num_branch++;
 
        /* �E�̎q������ꍇ�͉E�̎q��V���Ȓ��ڃm�[�h�ɐݒ� */
        node = node->right;
        }
        else {
            /* �ǉ�����l�ƃm�[�h�̒l�������ꍇ */
            printf("%d already exist\n", number);
            break;
        }
    }
    
    return balancing(root, root, NULL, 0, branch, num_branch);
}
 
/*  searchNode:�w�肳�ꂽnumber�����m�[�h��T������
    �����P root : �T�����J�n����m�[�h�̃A�h���X
    �����Q number : �T���������ԍ�
    �ԋp�l : number �����m�[�h�̃A�h���X�i���݂��Ȃ��ꍇ�� NULL�j*/
struct node_t *searchNode(struct node_t *root, int number){
    struct node_t *node;
  
    node = root;
 
    /* �T�����s�����[�v�i���ڃm�[�h��NULL�ɂȂ�����I�� */
    while(node){
        if(number < node->number){
            /* �T���l���m�[�h�̒l�����������ꍇ */
 
            /* ���ڃm�[�h�����̎q�m�[�h�ɐݒ� */
            node = node->left;
        }
        else if(number > node->number){
            /* �T���l���m�[�h�̒l�����傫���ꍇ */
 
            /* ���ڃm�[�h���E�̎q�m�[�h�ɐݒ� */
            node = node->right;
        }
        else {
            /* �T���l = �m�[�h�̒l�̏ꍇ */
            return node;
        }
    }
    
    /* �T���l�����m�[�h��������Ȃ������ꍇ */
    return NULL;
}
 
/*  deleteNoChildeNode:�w�肳�ꂽ�q�̖����m�[�h���폜����
    �����P root : �؂̍��m�[�h�̃A�h���X
    �����Q node : �폜����m�[�h�̃A�h���X
    �����R parent�F�폜����m�[�h�̐e�m�[�h�̃A�h���X
    �ԋp�l : ���m�[�h�̃A�h���X */
struct node_t *deleteNoChildNode(struct node_t *root, struct node_t *node, struct node_t *parent){
 
    if(parent != NULL){
        /* �e������ꍇ�i���m�[�h�ȊO�̏ꍇ�j��
     �폜�Ώۃm�[�h���w���|�C���^��NULL�ɐݒ� */
        if(parent->left ==  node){
            /* �폜�Ώۃm�[�h���e�m�[�h���猩�č��̎q�̏ꍇ */
            parent->left = NULL;
        }
        else {
            /* �폜�Ώۃm�[�h���e�m�[�h���猩�ĉE�̎q�̏ꍇ */
            parent->right = NULL;
        }
        free(node);
    }
    else {
        /* �폜�Ώۃm�[�h�����m�[�h�̏ꍇ */
        free(node);
      
        /* ���m�[�h���w���|�C���^��NULL�ɐݒ� */
        root = NULL;
    }
    
    return root;
}
 
/*  deleteOneChildeNode:�w�肳�ꂽ�q����̃m�[�h���폜����
    �����P root : �؂̍��m�[�h�̃A�h���X
    �����Q node : �폜����m�[�h�̃A�h���X
    �����R child : �폜����m�[�h�̎q�m�[�h�̃A�h���X
    �ԋp�l : ���m�[�h�̃A�h���X */
struct node_t *deleteOneChildNode(struct node_t *root, struct node_t *node, struct node_t * child){
   
    /* �폜�Ώۃm�[�h�ɂ��̎q�m�[�h�̃f�[�^�ƃ|�C���^���R�s�[ */
    node->number = child->number;
    node->left = child->left;
    node->right = child->right;
    
    /* �R�s�[���̃m�[�h���폜 */
    free(child);
  
    return root;
}
 
/*  deleteTwoChildeNode:�w�肳�ꂽ�q����̃m�[�h���폜����
    �����P root : �؂̍��m�[�h�̃A�h���X
    �����Q node : �폜����m�[�h�̃A�h���X
    �ԋp�l : ���m�[�h�̃A�h���X */
struct node_t *deleteTwoChildNode(struct node_t *root, struct node_t *node, int *branch, int *num_branch){
 
    struct node_t *max;
    struct node_t *maxParent;
  
    /* ���̎q�����ԑ傫���l�����m�[�h��T�� */
    max = node->left;
    maxParent = node;
 
    /* ���̎q�m�[�h��H�������Ƃ��o���Ă��� */
    branch[*num_branch] = TREE_LEFT;
    (*num_branch)++;
    
    while(max->right != NULL){
        maxParent = max;
        max = max->right;
 
        /* �E�̎q�m�[�h��H�������Ƃ��o���Ă��� */
        branch[*num_branch] = TREE_RIGHT;
        (*num_branch)++;
    }
    
    /* �ő�m�[�h�̃f�[�^�̂ݍ폜�Ώۃm�[�h�ɃR�s�[ */
    node->number = max->number;
    
    /* �ő�m�[�h���폜 */
  
    /* max�͍ő�m�[�h�Ȃ̂ŕK��max->right��NULL�ɂȂ� */
    if(max->left == NULL){
        /* �ő�m�[�h�Ɏq�����Ȃ��ꍇ */
        root = deleteNoChildNode(root, max, maxParent);      
    }
    else {
        /* �ő�m�[�h�Ɏq���������ꍇ */
        root = deleteOneChildNode(root, max, max->left);
    }
 
    return root;
}
 
/* deleteNode:�w�肳�ꂽnumber�����m�[�h���폜����
   �����P root : �؂̍��m�[�h�̃A�h���X
   �����Q number : �폜�������ԍ�
   �ԋp�l : ���m�[�h�̃A�h���X */
struct node_t *deleteNode(struct node_t *root, int number){
    struct node_t *node;
    struct node_t *parent;
    int branch[MAX_HEIGHT] = {0};
    int num_branch = 0;
 
    if(root == NULL){
        return NULL;
    }
 
    /* �폜�Ώۃm�[�h���w���m�[�h��T�� */
    node = root;
    parent = NULL;
  
    while(node !=  NULL){
        if(number < node->number){
            parent = node;
            node = node->left;
 
            /* ���̎q�m�[�h��H�������Ƃ��o���Ă��� */
            branch[num_branch] = TREE_LEFT;
            num_branch++;
        }
        else if(number > node->number){
            parent = node;
            node = node->right;
 
            /* �E�̎q�m�[�h��H�������Ƃ��o���Ă��� */
            branch[num_branch] = TREE_RIGHT;
            num_branch++;
        }
        else {
            break;
        }
    }
  
    /* �w�肳�ꂽnumber��l�Ƃ��Ď��m�[�h�����݂��Ȃ��ꍇ�͉��������I�� */
    if(node == NULL){
        printf("%d �����m�[�h�����݂��܂���B\n", number);
        return root;
    }
 
    printf("Delete %d node\n", node->number);
 
    if(node->left == NULL && node->right == NULL){    
        /* �q�����Ȃ��m�[�h�̍폜 */
        root = deleteNoChildNode(root, node, parent);
    }
    else if((node->left != NULL && node->right == NULL) ||(node->right != NULL && node->left == NULL)){
        /* �q��������Ȃ��ꍇ */
        
        if(node->left != NULL){
        root = deleteOneChildNode(root, node, node->left);
        }
        else {
        root = deleteOneChildNode(root, node, node->right);
        }
    }
    else {
        /* ���̎q�ƉE�̎q����������m�[�h�̍폜 */
        root = deleteTwoChildNode(root, node, branch, &num_branch);
    }
    
    return balancing(root, root, NULL, 0, branch, num_branch);
}
 
/*  printTree:root�����m�[�h�Ƃ���񕪒T���؂��̑S�m�[�h��\������
    �����P root : �؂̍��m�[�h�̃A�h���X
    �����Q depth: �֐��Ăяo���̐[��
    �ԋp�l : �Ȃ� */
void printTree(struct node_t *root, int depth){
    int i;
 
    if(root == NULL){
    return ;
    }
 
    /* �E�̎q���m�[�h��\�� */
    printTree(root->right, depth+1);
 
    /* �[�����X�y�[�X�ŕ\�� */ 
    for(i = 0; i < depth; i++){
        printf("    ");
    }
 
    /* �m�[�h�̃f�[�^��\�� */
    printf("+%3d\n", root->number);
 
    /* ���̎q���m�[�h��\�� */
    printTree(root->left, depth+1);
 
    depth++;
}
 
int main(void){
    struct node_t *root, *node;
    int input;
    int number;
    int loop;
 
    /* �܂��؂��Ȃ��̂�root��NULL�ɃZ�b�g */
    root = NULL;
 
    loop = 1;
    while(loop){
        printf("������I��(1:�ǉ�, 2:�폜, 3:����, 4:�I��) : ");
        scanf("%d", &input);
 
        switch(input){
        case 1:
            printf("number(1 - 999):");
            scanf("%d", &number);
            if(number < 1 || number > 999){
                printf("�l���͈͊O�ł�\n");
                continue;
            }
            root = addNode(root, number);
            break;
        case 2:
            printf("number(1 - 999):");
            scanf("%d", &number);
            if(number < 1 || number > 999){
                printf("�l���͈͊O�ł�\n");
                continue;
            }
 
            root = deleteNode(root, number);
            break;
        case 3:
            printf("number(1 - 999):");
            scanf("%d", &number);
            if(number < 1 || number > 999){
                printf("�l���͈͊O�ł�\n");
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

