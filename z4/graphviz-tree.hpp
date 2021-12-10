#include <iostream>

template<typename HoldedValue>
void printGraphvizConnectionsRecursively(HoldedValue* arr, int size, int no) {
    if(no <= size) {
        int leftNodeNo = 2*no;
        if(leftNodeNo <= size) {
            std::cout << "\t" << no << " -> " << leftNodeNo << ";" << std::endl;            
        }
        int rightNodeNo = leftNodeNo + 1;
        if(rightNodeNo <= size) {
            std::cout << "\t" << no << " -> " << rightNodeNo << ";" << std::endl;            
        }        
        printGraphvizConnectionsRecursively(arr, size, leftNodeNo);
        printGraphvizConnectionsRecursively(arr, size, rightNodeNo);
    }
}

template<typename HoldedValue>
void printArrayAsGraphvizBinaryTree(HoldedValue* arr, int size) {
    std::cout << "digraph btree {" << std::endl;
    for(int i = 0; i < size; i++) {
        std::cout << "\t" << (i+1) << " [label=\"";
        //std::cout << (i+1) << ": ";
        std::cout << arr[i] << "\"];" << std::endl;
    }
    printGraphvizConnectionsRecursively(arr, size, 1);
    std::cout << "}" << std::endl << std::endl;
}