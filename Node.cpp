

class Node {
    private:
        wchar_t word;
        int frequency;    
        Node *left, *right;

    public:
        Node() : frequency(), word(), right(nullptr), left(nullptr) {}
        Node(wchar_t w, int freq) : word(w), frequency(freq), right(nullptr), left(nullptr) {}
        Node(wchar_t w, int freq, Node *l, Node *r) : frequency(freq), word(w), left(r), right(l) {}

        bool isLeaf() {
            return (!left && !right);
        }

        void setChildren(Node* left, Node* right) {
            this->left = left;
            this->right = right;
        }

        void createSubTree(wchar_t c, int fr, Node* l, Node* r) {
            setWord(c);
            setFrequency(fr);
            setChildren(l, r);
        }

        int getFrequency() {
            return frequency;
        }

        void setFrequency(int fr) {
            frequency = fr;
        }

        wchar_t getWord() {
            return word;
        }

        void setWord(wchar_t wr) {
            word = wr;
        }

        Node* getLeftChield() {
            return left;
        }

        Node* getRightChield() {
            return right;
        }
};