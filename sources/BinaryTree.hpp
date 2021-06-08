#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <queue>

using namespace std;
namespace ariel
{
    template <typename T>
    class BinaryTree
    {
        class Node
        {
        public:
            T data;
            Node *right;
            Node *left;

            Node(T data) : data(data), right(nullptr), left(nullptr) {} // def const with data
        };

    public:
        Node *root;

        BinaryTree() : root(nullptr) {} // def const

        ~BinaryTree() {} // destructor

        BinaryTree(BinaryTree &&tree) noexcept // shallow copy root
        {
            root = tree.root;
            tree.root = nullptr;
        }

        BinaryTree(BinaryTree &tree) // deep copy all nodes
        {
            if (tree.root != nullptr)
            {
                copy(root, tree.root);
            }
            else
            {
                root = nullptr;
            }
        }

        void copy(Node *&root, Node *&copyNode)
        {
            if (copyNode == nullptr)
            {
                root = nullptr;
            }
            else
            {
                root = new Node(copyNode->data); // copy preorder
                copy(root->left, copyNode->left);
                copy(root->right, copyNode->right);
            }
        }

        BinaryTree &add_root(T data)
        {
            if (root == nullptr) // add new root
            {
                root = new Node(data);
            }
            else
            {
                root->data = data; // change root data
            }
            return *this;
        }
        BinaryTree &add_left(const T &parent, const T &left)
        {
            Node *runner = findTreeNode(root, parent);
            if (runner == nullptr)
            {
                throw invalid_argument{"parent is null"};
            }
            if (runner->left == nullptr)
            {
                runner->left = new Node(left); // left node is empty add it
            }
            else
            {
                runner->left->data = left; // change left node to new data
            }
            return *this;
        }
        BinaryTree &add_right(const T &parent, const T &right)
        {
            Node *runner = findTreeNode(root, parent);
            if (runner == nullptr)
            {
                throw invalid_argument{"parent is null"};
            }
            if (runner->right == nullptr) // right node is empty add it
            {
                runner->right = new Node(right);
            }
            else
            {
                runner->right->data = right; // change right node to new data
            }
            return *this;
        }
        Node *findTreeNode(Node *node, const T findData) // private func for adding left/right nodes
        {
            if (node == nullptr)
            {
                return nullptr;
            }
            if (node->data == findData) // data in this node
            {
                return node;
            }

            Node *runner = findTreeNode(node->right, findData); // find node right
            if (runner == nullptr)                              // not found on right
            {
                return findTreeNode(node->left, findData); // find node left
            }
            return runner;
        }

        friend ostream &operator<<(ostream &out, const BinaryTree &tree)
        {
            out << "binary tree is:" << endl;
            //add print
            return out;
        }
        BinaryTree &operator=(BinaryTree &&tree) noexcept
        {
            root = tree.root;
            tree.root = nullptr;
        }

        BinaryTree &operator=(BinaryTree tree)
        {
            if (this == &tree)
            {
                return *this;
            }
            root = new Node(tree.root->data);
            copy(root, tree.root);
            return *this;
        }

        class iterator
        {
        private:
            Node *currNode;
            queue<Node *> queue;

        public:
            iterator()
            {
                currNode = nullptr;
            }
            iterator(Node *node)
            {
                this->currNode = node;
            }

            T &operator*()
            {
                return currNode->data;
            }

            T *operator->()
            {
                return &(currNode->data);
            }

            iterator &operator++()
            {
                if (queue.size() > 1)
                {
                    queue.pop();                    // pop first
                    this->currNode = queue.front(); // put this node first
                }
                else
                {
                    this->currNode = nullptr;
                }
                return *this;
            }

            iterator operator++(int)
            {
                iterator iter = *this; // keep before ++
                ++*this;               // ++this node
                return iter;
            }

            bool operator==(const iterator &iter)
            {
                return currNode == iter.currNode;
            }

            bool operator!=(const iterator &iter)
            {
                return currNode != iter.currNode;
            }

            iterator(Node *root, const int &order)
            {
                if (root != nullptr)
                {
                    if (order == 1)
                    {
                        preorder(root);
                        this->currNode = queue.front(); // get the last node
                    }
                    if (order == 2)
                    {
                        inorder(root);
                        this->currNode = queue.front();
                    }
                    if (order == 3)
                    {
                        postorder(root);
                        this->currNode = queue.front();
                    }
                }
                else
                {
                    this->currNode = nullptr;
                }
            }

            void preorder(Node *node)
            { // P L R

                if (node == nullptr)
                {
                    return;
                }
                queue.push(node);
                preorder(node->left);
                preorder(node->right);
            }

            void inorder(Node *node)
            { // L P R
                if (node == nullptr)
                {
                    return;
                }
                inorder(node->left);
                queue.push(node);
                inorder(node->right);
            }

            void postorder(Node *node)
            { // L R P

                if (node == nullptr)
                {
                    return;
                }
                postorder(node->left);
                postorder(node->right);
                queue.push(node);
            }
        };

        iterator begin()
        {
            return iterator(root, 2);
        }
        iterator end()
        {
            return iterator();
        }
        iterator begin_preorder()
        {
            return iterator(root, 1);
        }
        iterator end_preorder()
        {
            return iterator();
        }
        iterator begin_inorder()
        {
            return iterator(root, 2);
        }
        iterator end_inorder()
        {
            return iterator();
        }
        iterator begin_postorder()
        {
            return iterator(root, 3);
        }
        iterator end_postorder()
        {
            return iterator();
        }
    };
}