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

template<typename HoldedValues>
class PreOrderTraverse
{
    protected:
        void printNode(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {
                std::cout << node->getValue();
                this->printNode(node->getLeftChild());
                this->printNode(node->getRightChild());
            }           
        }
};

template<typename HoldedValues>
class InOrderTraverse
{
    protected:
        void printNode(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {                
                this->printNode(node->getLeftChild());
                std::cout << node->getValue();
                this->printNode(node->getRightChild());
            }           
        }
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

template<typename HoldedValues>
class PostOrderTraverse
{
    protected:
        void printNode(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {                
                this->printNode(node->getLeftChild());
                this->printNode(node->getRightChild());
                std::cout << node->getValue();
            }           
        }
};

template<typename HoldedValues, template<typename> class TraversePolicy>
class BinaryHeap: public TraversePolicy<HoldedValues> {
    public:
        BinaryHeap(HoldedValues *valuesToHeapify, int numberOfElements): originalValues(new HoldedValues[numberOfElements]), numberOfElements(numberOfElements) {
            for(int i = 0; i <this->numberOfElements; i++) {
                this->originalValues[i] = valuesToHeapify[i];
            }            
            this->heapifyValues();
            this->buildTree();
        }
        ~BinaryHeap() {
            delete[] this->originalValues;
            this->destroyBinaryTree();            
        }
        void print() {            
            this->printNode(this->root);
            std::cout << std::endl;
        }
        void parenthesize() {
            this->printWithParenthesis(this->root);
            std::cout << std::endl;
        }    
    private:
        void heapifyValues() {
            for(int i = this->numberOfElements; i >= 1; i--) {
                this->heapifyAt(i);
            }
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
        void buildTree() {
            this->root = this->buildTreeNode(1);
        }
        BinaryTreeNode<HoldedValues>* buildTreeNode(int index) {
            if(index <= this->numberOfElements) {
                BinaryTreeNode<HoldedValues> *node = new BinaryTreeNode<HoldedValues>();
                node->setValue(this->originalValues[index - 1]);
                node->setLeftChild(this->buildTreeNode(2*index));
                node->setRightChild(this->buildTreeNode(2*index + 1));
                return node;
            } else {
                return nullptr;
            }
        }
        void destroyBinaryTree() {
            this->destroyNode(this->root);
            this->root = nullptr;
        }
        void destroyNode(BinaryTreeNode<HoldedValues>* node) {
            if(node != nullptr) {
                this->destroyNode(node->getLeftChild());
                this->destroyNode(node->getRightChild());
                delete node;
            }        
        }

        HoldedValues* originalValues;
        int numberOfElements;
        BinaryTreeNode<HoldedValues> *root;
};

int main() {
    const char* kopce= "WandaKrakKosciuszkiPilsudski";
    BinaryHeap<char, PreOrderTraverse> kopcePreOrderedHeap(const_cast<char*>(kopce), strlen(kopce));
    kopcePreOrderedHeap.print();
    BinaryHeap<char, PostOrderTraverse> kopcePostOrder(const_cast<char*>(kopce), strlen(kopce));
    kopcePostOrder.print();
    BinaryHeap<char, InOrderTraverse> kopceInOrder(const_cast<char*>(kopce), strlen(kopce));
    kopceInOrder.print();
    kopceInOrder.parenthesize();
}