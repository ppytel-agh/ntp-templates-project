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
BinaryTreeNode<NodeValueType> nodeFromArray(NodeValueType* arr, int size, int nodeNo) {
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
        BinaryTree<NodeValueType> fromArray(NodeValueType* arr, int size) {
            return BinaryTree<NodeValueType>(nodeFromArray(arr, size, 1), size);
        }
        ~BinaryTree() {
            this->destroyNode(this->root);
            this->root = nullptr;
        }
        BinaryTreeNode<NodeValueType> getRoot() {
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
        BinaryTree<NodeValueType>* root;
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

template<typename HoldedValues, template<typename> class TraversePolicy>
class BinaryHeap: public TraversePolicy<HoldedValues> {
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

// template<typename HoldedValue>
// printArrayAsBinaryTree(HoldedValue* arr, int size) {
//     int rows = ceil(log2(size));
//     int nextRowSize = 1;
//     int rowSizesSum = 1;
//     for(int i = 0; i < size; i++) {

//         if(i+1 == rowSizesSum) {
//             nextRowSize *= 2;
//             rowSizesSum += nextRowSize;
//         }
//     }
// }

int main() {
    const char* kopce= "WandaKrakKosciuszkoPilsudski";
    // BinaryHeap<char, PreOrderTraverse> kopcePreOrderedHeap(const_cast<char*>(kopce), strlen(kopce));
    // std::cout << "PREORDER" << std::endl;
    // kopcePreOrderedHeap.print();
    // std::cout << "heapified" << std::endl;
    // kopcePreOrderedHeap.heapifyValues();
    // kopcePreOrderedHeap.print();
    // BinaryHeap<char, PostOrderTraverse> kopcePostOrder(const_cast<char*>(kopce), strlen(kopce));
    // std::cout << "POSTORDER" << std::endl;
    // kopcePostOrder.print();
    // kopcePostOrder.parenthesize();
    // std::cout << "heapified" << std::endl;
    // kopcePostOrder.heapifyValues();
    // kopcePostOrder.print();
    // BinaryHeap<char, InOrderTraverse> kopceInOrder(const_cast<char*>(kopce), strlen(kopce));
    // std::cout << "INORDER" << std::endl;
    // kopceInOrder.print();
    // kopceInOrder.parenthesize();
    // std::cout << "heapified" << std::endl;
    // kopceInOrder.heapifyValues();
    // kopceInOrder.print();
    // kopceInOrder.parenthesize();
}