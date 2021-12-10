#include <cstring>
#include <iostream>

template<typename NodeValueType>
class BinaryTreeNode {
    public:
        BinaryTreeNode():leftChild(nullptr), rightChild(nullptr), value('\0') {}
        void setLeftChild(BinaryTreeNode<NodeValueType>* leftChild) {
            this->leftChild = leftChild;
        }
        void setRightChild(BinaryTreeNode<NodeValueType>* rightChild) {
            this->rightChild = rightChild;
        }
        void setValue(NodeValueType value) {
            this->value = value;
        }
        BinaryTreeNode<NodeValueType>* getLeftChild() {
            return this->leftChild;
        }
        BinaryTreeNode<NodeValueType>* getRightChild() {
            return this->rightChild;
        }
        NodeValueType getValue() {
            return this->value;
        }
    private:
        BinaryTreeNode<NodeValueType>* leftChild;
        BinaryTreeNode<NodeValueType>* rightChild;
        NodeValueType value;  
};

template <typename NodeValueType>
BinaryTreeNode<NodeValueType>* nodeFromArray(NodeValueType* arr, int size, int nodeNo) {
    if(nodeNo <= size) {
        BinaryTreeNode<NodeValueType> *node = new BinaryTreeNode<NodeValueType>();
        node->setValue(arr[nodeNo - 1]);
        node->setLeftChild(nodeFromArray(arr, size, nodeNo*2));
        node->setRightChild(nodeFromArray(arr, size, nodeNo*2 + 1));
        return node;
    } else {
        return nullptr;
    }    
}

template<typename NodeValueType>
class BinaryTree {
    public:
        BinaryTree(NodeValueType* arr, int size): root(nodeFromArray(arr, size, 1)), size(size) {}
        ~BinaryTree() {
            this->destroyNode(this->root);
            this->root = nullptr;
        }
        BinaryTreeNode<NodeValueType>* getRoot() {
            return this->root;
        }
    protected:
        BinaryTree(BinaryTreeNode<NodeValueType>* root, int size): root(root), size(size) {}
        void destroyNode(BinaryTreeNode<NodeValueType>* node) {
            if(node != nullptr) {
                this->destroyNode(node->getLeftChild());
                this->destroyNode(node->getRightChild());
                delete node;
            }        
        }
    private:
        BinaryTreeNode<NodeValueType>* root;
        int size;
};

class PreOrderTraverse
{
    protected:
        template<typename HoldedValues>
        void printNode(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {
                std::cout << node->getValue();
                this->printNode(node->getLeftChild());
                this->printNode(node->getRightChild());
            }           
        }
};

class InOrderTraverse
{
    protected:
        template<typename HoldedValues>
        void printNode(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {                
                this->printNode(node->getLeftChild());
                std::cout << node->getValue();
                this->printNode(node->getRightChild());
            }           
        }
        template<typename HoldedValues>
        void printWithParenthesis(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {             
                std::cout << "(";   
                this->printWithParenthesis(node->getLeftChild());
                std::cout << node->getValue();
                this->printWithParenthesis(node->getRightChild());
                std::cout << ")";
            }     
        }
};

class PostOrderTraverse
{
    protected:
        template<typename HoldedValues>
        void printNode(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {                
                this->printNode(node->getLeftChild());
                this->printNode(node->getRightChild());
                std::cout << node->getValue();
            }           
        }
        template<typename HoldedValues>
        void printWithParenthesis(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {             
                std::cout << "(";   
                this->printWithParenthesis(node->getLeftChild());
                this->printWithParenthesis(node->getRightChild());
                std::cout << node->getValue();
                std::cout << ")";
            }     
        }
};

template<class TraversePolicy> 
class BinaryTreeTraverser: public TraversePolicy {
    public: 
        template<typename HoldedValues>
        void print(BinaryTree<HoldedValues>& tree) {
            this->printNode(tree.getRoot());
            std::cout << std::endl;
        }
        template<typename HoldedValues>
        void parenthesize(BinaryTree<HoldedValues>& tree) {
            this->printWithParenthesis(tree.getRoot());
            std::cout << std::endl;
        }    
};

template<typename HoldedValues>
void heapifyAt(HoldedValues* values, int len, int no) {
    int largest = no;    
    int leftChildNo = 2*no;
    int rightChildNo = leftChildNo + 1;
    int currentElementIndex = no - 1;
    int largestValueIndex = largest - 1;
    int leftChildIndex = leftChildNo - 1;
    int rightChildIndex = rightChildNo - 1;
    if(leftChildNo <= len && (values[leftChildIndex] > values[largestValueIndex])) {        
        largest = leftChildNo;
        largestValueIndex = leftChildIndex;
    }
    if(rightChildNo <= len &&  (values[rightChildIndex] > values[largestValueIndex])) {
        largest = rightChildNo;
        largestValueIndex = rightChildIndex;
    }
    if(largest != no) {        
        HoldedValues largestValue = values[largestValueIndex];
        values[largestValueIndex] = values[currentElementIndex];
        values[currentElementIndex] = largestValue;
        heapifyAt(values, len, largest);
    }   
}

template<typename HoldedValues>
HoldedValues* heapify(HoldedValues* values, int len) {
    HoldedValues* heapifiedValues = new HoldedValues[len];
    for(int i = 0; i < len; i++) {
        heapifiedValues[i] = values[i];
    }
    for(int no = len; no >= 1; no--) {
        heapifyAt(heapifiedValues, len, no);
    }
    return heapifiedValues;
}

template<typename HoldedValues>
class BinaryHeap {
    public:
        BinaryHeap(HoldedValues *valuesToHeapify, int numberOfElements): originalValues(new HoldedValues[numberOfElements]), numberOfElements(numberOfElements) {
            for(int i = 0; i <this->numberOfElements; i++) {
                this->originalValues[i] = valuesToHeapify[i];
            }
            this.heapifyValues();            
        }
        ~BinaryHeap() {
            delete[] this->originalValues;
            this->destroyBinaryTree();            
        }
        HoldedValues* getValues() {
            return this->originalValues;
        }
        int getSize() {
            return this->numberOfElements;
        }
        
    protected:    
        void heapifyValues() {
            for(int i = this->numberOfElements; i >= 1; i--) {
                this->heapifyAt(i);
            }
            this->buildTree();
        }     
        void heapifyAt(int index) {
            int largest = index;
            int leftChildIndex = 2*index;
            int rightChildIndex = leftChildIndex + 1;
            if(leftChildIndex <= this->numberOfElements && this->originalValues[leftChildIndex - 1] > this->originalValues[largest - 1]) {
                largest = leftChildIndex;
            }
            if(rightChildIndex <= this->numberOfElements && this->originalValues[rightChildIndex - 1] > this->originalValues[largest - 1]) {
                largest = rightChildIndex;
            }
            if(largest != index) {
                HoldedValues tmp = this->originalValues[largest - 1];
                this->originalValues[largest - 1] = this->originalValues[index - 1];
                this->originalValues[index -1] = tmp;
                this->heapifyAt(largest);
            }
        }
    private:
        HoldedValues* originalValues;
        int numberOfElements;
};

#include "graphviz-tree.hpp"

int main() {
    const char* kopce= "WandaKrakKosciuszkoPilsudski";
    int kopceLen = strlen(kopce);
    //printArrayAsGraphvizBinaryTree(kopce, kopceLen);
    char* heapifiedKopce = heapify(const_cast<char*>(kopce), kopceLen);
    //printArrayAsGraphvizBinaryTree(heapifiedKopce, kopceLen);
    BinaryTreeTraverser<PreOrderTraverse> preOrderTraverser;
    BinaryTreeTraverser<InOrderTraverse> InOrderTraverser;
    BinaryTreeTraverser<PostOrderTraverse> postOrderTraverser;
    BinaryTree<char> kopceTree(const_cast<char*>(kopce), kopceLen);
    BinaryTree<char> kopceHeap(const_cast<char*>(heapifiedKopce), kopceLen);
   
    std::cout << "PREORDER" << std::endl;
    preOrderTraverser.print(kopceTree);
    std::cout << "heapified" << std::endl;
    preOrderTraverser.print(kopceHeap);
    std::cout << "POSTORDER" << std::endl;
    postOrderTraverser.print(kopceTree);
    postOrderTraverser.parenthesize(kopceTree);
    std::cout << "heapified" << std::endl;
    postOrderTraverser.print(kopceHeap);
    std::cout << "INORDER" << std::endl;
    InOrderTraverser.print(kopceTree);
    InOrderTraverser.parenthesize(kopceTree);
    std::cout << "heapified" << std::endl;
    InOrderTraverser.print(kopceHeap);
    InOrderTraverser.parenthesize(kopceHeap);
    delete[] heapifiedKopce;
    heapifiedKopce = nullptr;
    return 0;
}