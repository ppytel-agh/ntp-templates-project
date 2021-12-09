
template<typename TraversePolicy>
class BinaryHeap: public TraversePolicy {
    public:
        BinaryHeap(char *stringToHeapify) {
            this->heapifyString();
        }
        void print() {
            
        }
        void parenthesize();
    private:
        char* heapifiedString;
};



int main {
    const char* = "WandaKrakKosciuszkiPilsudski";

}