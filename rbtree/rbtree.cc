#include <iostream>
#include <queue>
using namespace std;

/* 红黑树四个规则
 * (1) 每个结点要么是黑要么是红
 * (2) 根结点为黑
 * (3) 结点为红，子结点必须为黑
 * (4) 从根结点到null结点之间的黑结点数量相同 => 所以新增结点为红
 * */

class rbtree {
    public:
        enum {RED, BLACK};
        struct node {
            int val;
            int color;
            node* left;
            node* right;
            node(int v, int c = RED):val(v), color(c), 
            left(nullptr), right(nullptr) { }
        };
        rbtree():root(nullptr) {}
        void insert(int val) {
            /*
            if(root == nullptr) {
                root = new node(val, BLACK);
                return;
            }*/
            root = insert(root, val);
            root->color = BLACK;
        }

        void order() {
            queue<node*> que;
            que.push(root);
            int cnt = 1;
            while(que.size()) {
                for(int i = 0; i < cnt; ++i) {
                    node* p = que.front();
                    que.pop();
                    print(p);
                    if(p != nullptr) {
                        que.push(p->left);
                        que.push(p->right);
                    }
                }
                cout << endl;
                cnt = que.size();
            }
        }

        void print(node *p) {
            if(p == nullptr) {
                cout << "null ";
                return;
            }
            cout << "{ ";
            cout << ((p->color == RED)?"RED ":"BLACK ");
            cout << p->val << " } ";
        }
    private:
        node* root;
        node* insert(node* root, int val) {
            if(root == nullptr)
                return new node(val);
            
            if(root->color == BLACK 
                    && root->left && root->left->color == RED 
                    && root->right && root->right->color == RED) {
                root->color = RED;
                root->left->color  = BLACK;
                root->right->color = BLACK;
            }

            if(root->val < val) {
                root-> right = insert(root->right, val);
                if(root->right->color == RED
                        && root->right->val < val
                        && root->right->right->color == RED) {
                    // 左旋
                    root = rotateLeft(root);
                }
                if(root->right->color == RED
                        && root->right->val > val
                        && root->right->left->color == RED) {
                    // 先右再左
                    root->right = rotateRight(root->right);
                    root = rotateLeft(root);
                }
            }
            if(root->val > val) {
                root->left   = insert(root->left, val);
                if(root->left->color == RED 
                        && root->left->val > val
                        && root->left->left->color == RED) {
                    // 右旋
                    root = rotateRight(root);
                }
                if(root->left->color == RED
                        && root->left->val < val
                        && root->left->right->color == RED) {
                    // 先左再右
                    root->left = rotateLeft(root->left);
                    root = rotateRight(root);
                }
            }
            return root;
        }

        node* rotateLeft(node* root) {
            int color = root->color;
            root->color = root->right->color;
            root->right->color = color;
            node *p = root->right;
            root->right = p->left;
            p->left = root;
            return p;
        }

        node* rotateRight(node* root) {
            int color = root->color;
            root->color = root->left->color;
            root->left->color = color;
            node* p = root->left;
            root->left = p->right;
            p->right = root;
            return p;
        }
};

int main() 
{
    int val;
    rbtree rbt;
    while(cin >> val) {
        rbt.insert(val);
        rbt.order();
    }
}
