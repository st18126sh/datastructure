#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_tag {
    int data;
    int diff;
    struct node_tag *child[2];
} node_t;

void rotate(node_t **node, int is_right) {
    int l = is_right ? 0 : 1; /* 「左の子」の添字 */
    int r = is_right ? 1 : 0; /* 「右の子」の添字 */
    int sign = is_right ? 1 : -1; /* 左回転の時はdiffの意味が反転する */
    assert((*node)->child[l] != NULL); /* 回転に必要な子が無かったら死亡 */
    if ((*node)->child[l] != NULL) {
        node_t* left = (*node)->child[l];
        int a = (*node)->diff * sign, b = left->diff * sign, na, nb;
        /* 高さの差の更新 */
        if (b >= 0) {
            if (a - 1 - b >= 0) {
                nb = b - 1;
            } else {
                nb = a - 2;
            }
            na = a - 1 - b;
        } else {
            if (a - 1 >= 0) {
                nb = b - 1;
            } else {
                nb = a + b - 2;
            }
            na = a - 1;
        }
        (*node)->diff = na * sign;
        left->diff = nb * sign;
        /* 回転操作 */
        (*node)->child[l] = (*node)->child[l]->child[r];
        left->child[r] = *node;
        *node = left;
    }
}

/* 戻り値 = 高さの変化 */
int modify_tree(node_t **node, int data, int add) {
    if (*node == NULL) {
        if (add) {
            /* 新しい子を追加する */
            *node = malloc(sizeof(node_t));
            assert(*node != NULL);
            if (*node != NULL) {
                /* 作成したノードを初期化する */
                (*node)->data = data;
                (*node)->diff = 0; /* 子は両方無い */
                (*node)->child[0] = NULL;
                (*node)->child[1] = NULL;
            }
            /* 何もない所に子を作ったので、高さが増える */
            return *node != NULL;
        } else {
            /* 削除対象が見つからなかった */
            return 0;
        }
    } else {
        int l, delta, delta_sign;
        node_t *next_node;
        if (data == (*node)->data) {
            /* このノードのデータと同じ */
            if (add) {
                /* 重複したデータの挿入クエリなので、無視する */
                return 0;
            } else {
                /* このノードを削除する */
                if ((*node)->child[1] == NULL) {
                    /* 右の子が無いので、左の子をこのノードの位置に持ってくる */
                    next_node = (*node)->child[0];
                    free(*node);
                    *node = next_node;
                    /* 高さが1減る */
                    return -1;
                } else if ((*node)->child[0] == NULL) {
                    /* 左の子が無いので、右の子をこのノードの位置に持ってくる */
                    next_node = (*node)->child[1];
                    free(*node);
                    *node = next_node;
                    /* 高さが1減る */
                    return -1;
                } else {
                    /* 両方に子がある */
                    /* 左にある一番右のノードを探す */
                    for (next_node = (*node)->child[0]; next_node->child[1] != NULL; next_node = next_node->child[1]);
                    /* そのノードの値をこのノードに持ってくる */
                    (*node)->data = next_node->data;
                    /* そのノードを削除する (左に行く) */
                    l = 0;
                    delta_sign = 1;
                    delta = modify_tree(&(*node)->child[l], next_node->data, add);
                }
            }
        } else {
            /* このノードは対象では無いので、子を処理する */
            if (data < (*node)->data) {
                /* このノードのデータより小さいので、左に行く */
                l = 0; /* 「左の子」の添字 */
                delta_sign = 1; /* diffの変化の方向 */
            } else {
                /* このノードのデータより大きいので、右に行く */
                l = 1;
                delta_sign = -1;
            }
            delta = modify_tree(&(*node)->child[l], data, add);
        }
        if (delta != 0) {
            /* 子の高さに変化があった */
            int orig_diff = (*node)->diff; /* 子の高さが変わる前の高さの差 */
            int do_rotate = 0, rotate_l, diff_sign, rotate_right; /* 回転操作の情報 */
            (*node)->diff += delta * delta_sign; /* 差を更新する */
            if ((*node)->diff > 1) {
                /* 左が高すぎるので、右回転する */
                do_rotate = 1; /* 回転をする */
                rotate_l = 0; /* 「左の子」の添字 */
                diff_sign = 1; /* diffの意味 */
                rotate_right = 1; /* この回転は右回転か */
            } else if ((*node)->diff < -1) {
                /* 右が高すぎるので、左回転する */
                do_rotate = 1;
                rotate_l = 1;
                diff_sign = -1;
                rotate_right = 0;
            }
            if (do_rotate) {
                int child_diff = (*node)->child[rotate_l]->diff;
                /* 回転操作 */
                if ((*node)->child[rotate_l]->diff * diff_sign < 0) {
                    /* 左 -> 右 みたいな感じになっているので、まず子を回転する */
                    /* メインの回転の逆方向 */
                    rotate(&(*node)->child[rotate_l], !rotate_right);
                }
                /* このノードを回転する */
                rotate(node, rotate_right);
                /* 子が高くなって回転をした場合は、高くなった分がその方向から減らされるから変わらない */
                /* 子が低くなって回転をした場合は、低くなった分が反対方向から減らされるから減る */
                /* ただし、高い方の子の高さの差が0の場合は、回転によって高さが減らない */
                /* 挿入後の回転では、「高い方の子の高さの差が0、かつ高い方の子が高くなった」という場合は発生しない */
                return delta < 0 && child_diff != 0 ? -1 : 0;
            }
            /* 高さの変化を返す */
            if (delta > 0 && orig_diff == 0) {
                /* 左右の高さが同じ状態で子の高さが増えたら、高さが増える */
                /* 左右の高さが違う場合は、平らになるだけで高さは変わらないか、回転が行われここでは扱わない */
                return 1;
            } else if (delta < 0 && orig_diff != 0) {
                /* 左右の高さが違い、高い方の子の高さが減ったら、高さが減る */
                /* 低い方の高さが減る場合は、回転操作が行われるのでここでは扱わない */
                return -1;
            } else {
                /* それ以外では、高さは変わらない */
                return 0;
            }
        } else {
            /* 子の高さが変わっていないので、高さは変わらない */
            return 0;
        }
    }
}

void print_tree(const node_t *node, int depth) {
    int i;
    if (node != NULL) {
        /* 右の子を出力 (右から出力すると、90度右回転した時にいい感じになる) */
        print_tree(node->child[1], depth + 1);
        /* このノードを出力 */
        for (i = 0; i < depth; i++) printf("  ");
        printf("%d (%d)\n", node->data, node->diff);
        /* 左の子を出力 */
        print_tree(node->child[0], depth + 1);
    }
}

void free_tree(node_t *node) {
    if (node != NULL) {
        free_tree(node->child[0]);
        free_tree(node->child[1]);
        free(node);
    }
}

int main(void) {
    node_t *root = NULL;
    int command, input;
    while (scanf("%d", &command) == 1) {
        switch (command) {
        case 0: /* 追加 */
        case 3: /* 追加して木を出力 */
            if (scanf("%d", &input) != 1) break;
            printf("add %d\n", input);
            modify_tree(&root, input, 1);
            if (command == 3) print_tree(root, 0);
            break;
        case 1: /* 削除 */
        case 4: /* 削除して木を出力 */
            if (scanf("%d", &input) != 1) break;
            printf("delete %d\n", input);
            modify_tree(&root, input, 0);
            if (command == 4) print_tree(root, 0);
            break;
        case 2: /* 木を出力 */
            printf("print\n");
            print_tree(root, 0);
            break;
        }
    }
    free_tree(root);
    return 0;
}