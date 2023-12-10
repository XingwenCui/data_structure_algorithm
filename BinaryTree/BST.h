#ifndef BST_H
#define BST_H

#include<iostream>
#include<queue>
#include<cassert>

template<typename Key, typename Value>
class BST{

private:
    // Node以struct实现
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = nullptr;     // nullptr比NULL更安全，因为NULL本质是0     
        }

        Node(Node *node) {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };
    Node *root;     // root节点
    int count;      // 记录节点个数，便于维护
private:
    // 增：以node为root，递归插入节点，返回插入node后的新树的root
    Node* insert(Node *node, Key key, Value value) {
        // 递归终止条件，直接创建node当做root
        if (node == nullptr) {
            // 计数+1
            count++;
            return new Node(key, value);
        }
        if (key == node->key)
            node->value = value;        // 我们假设所有值是唯一的
        else if (key < node->key)      // 如果插入值小于当前节点，就往该结点的左侧插入
            node->left = insert(node->left, key, value);
        else
            node->right = insert(node->right, key, value);
        
        return node; 
    }

    // 查：查看以node为root的BST是否包含某个键值的节点
    bool contain(Node* node, Key key) {
        // 递归终止条件
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        else if (key < node->key)   // 如果要查的值小于当前node，就查左子树
            return contain(node->left, key);
        else    //反之查右侧
            return contain(node->right, key);
    }

    // 查：查具体值
    Value* search(Node* node, Key key) {
        if (node == nullptr)
            return nullptr;
        if (key == node->key)
            return &(node->value);
        else if (key < node->key)
            return search(node->left, key);
        else    
            return search(node->right, key);
    }

    /*遍历*/
    // preorder 前序遍历：root->left->right
    void preOrder(Node* node) {
        if (node != nullptr){
            std::cout<<node->key<<' '<<std::endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }
    
    // inorder中序遍历：left->root->right
    void inOrder(Node* node) {
        if (node!=nullptr) {
            inOrder(node->left);
            std::cout<<node->key<<' '<<std::endl;
            inOrder(node->right);
        }
    }

    // postorder后序遍历：left->right->root
    void postOrder(Node* node) {
        if (node!=nullptr) {
            postOrder(node->left);
            postOrder(node->right);
            std::cout<<node->key<<' '<<std::endl;
        }
    }

    // 释放node为root的BST所有节点, post顺序递归
    void destroy(Node* node) {
        if (node!=nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            count--;
        }
    }

    // 查找以node为根的BST的最小key所在节点
    Node* minimum(Node* node) {
        if (node->left == nullptr)
            return node;
        return minimum(node->left);     // 最左的节点
    }

    Node* maximum(Node* node) {
        if (node->right == nullptr)
            return node;
        return maximum(node->right);   // 最右的节点
    }

    Node* removeMin(Node* node) {
        if (node->left == nullptr){
            Node* rightNode = node->right;
            delete node;
            count--;
            return rightNode;
        }
        // 删除了left后将right连接到父节点
        node->left = removeMin(node->left);
        return node;
    }

    Node* removeMax(Node* node) {
        if (node->right == nullptr) {
            Node* leftNode = node->left;
            delete node;
            count--;
            return leftNode;
        }
        node->right = removeMax(node->right);
        return node;
    }

    // 删：删除某个key的节点，使用Hubbard Deletion
    Node* remove(Node* node, Key key) {
        if (node == nullptr)
            return node;
        if (node->key < key) {
            node->left = remove(node->left, key);
            return node;
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
        }
        else {  // key == node->key
            // 如果该节点是最小或最大的
            if( node->left == nullptr ){
                Node *rightNode = node->right;
                delete node;
                count --;
                return rightNode;
            }
            if( node->right == nullptr ){
                Node *leftNode = node->left;
                delete node;
                count--;
                return leftNode;
            }
            // 理解为删除节点，链接他的左右子树
            Node *successor = new Node(minimum(node->right));
            count++;
            successor->right = removeMin(node->right);
            successor->left = node->left;
            delete node;
            count--;

            return successor;
        }
    }


public:
    BST(): root(nullptr), count(0) {}
    ~BST() {
        destroy(root);
    }

    // 返回BST中节点个数
    int size() {return count;}

    // 判断BST是否为空
    bool isEmpty() {return count==0;}

    // 向二分搜索树中插入一个新的(key, value)数据对
    void insert(Key key, Value value){
        root = insert(root, key, value);
    }

    // 查看二分搜索树中是否存在键key
    bool contain(Key key){
        return contain(root, key);
    }

    // 在二分搜索树中搜索键key所对应的值。如果这个值不存在, 则返回NULL
    Value* search(Key key){
        return search( root , key );
    }

    // 二分搜索树的前序遍历
    void preOrder(){
        preOrder(root);
    }

    // 二分搜索树的中序遍历
    void inOrder(){
        inOrder(root);
    }

    // 二分搜索树的后序遍历
    void postOrder(){
        postOrder(root);
    }

    // 二分搜索树的层序遍历, 需要借助queue
    void levelOrder(){

        if (root == NULL) return;
        
        std::queue<Node*> q;
        q.push(root);
        while( !q.empty() ){

            Node *node = q.front();
            q.pop();

            std::cout<<node->key<<std::endl;

            if( node->left )
                q.push( node->left );
            if( node->right )
                q.push( node->right );
        }
    }

    // 寻找二分搜索树的最小的键值
    Key minimum(){
        assert( count != 0 );
        Node* minNode = minimum( root );
        return minNode->key;
    }

    // 寻找二分搜索树的最大的键值
    Key maximum(){
        assert( count != 0 );
        Node* maxNode = maximum(root);
        return maxNode->key;
    }

    // 从二分搜索树中删除最小值所在节点
    void removeMin(){
        if( root )
            root = removeMin( root );
    }

    // 从二分搜索树中删除最大值所在节点
    void removeMax(){
        if( root )
            root = removeMax( root );
    }

    // 从二分搜索树中删除键值为key的节点
    void remove(Key key){
        root = remove(root, key);
    }

    
};


#endif //BST_H
