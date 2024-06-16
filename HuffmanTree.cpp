#include "Node.cpp"
#include <unordered_map>
#include <queue>
#include <iostream>
#include <locale>
#include <codecvt>


class HuffmanTree {
    public:
        struct CompareNodes {
            bool operator()(Node* lhs, Node* rhs) const {
                if (lhs->getFrequency() == rhs->getFrequency()) {
                    return lhs->getWord() > rhs->getWord();
                }
                return lhs->getFrequency() > rhs->getFrequency();
            }
        };

    private:
        Node* root;
        std::unordered_map<wchar_t, int> frequencyMap;
        std::unordered_map<wchar_t, std::wstring> huffmanTable;
        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue;
    
    public:
        HuffmanTree() : root() {}

        Node* getRoot() {
            return root;
        }

        void createFrequencyMap (std::wstring strFile) { 
            for (wchar_t c : strFile) {
                frequencyMap[c]++;
            }
        } 

        void createPriorityQueue () {
            for (auto c : frequencyMap) {
                priorityQueue.push(new Node(c.first, c.second));
            }
        }  

        void createTree() { // mudar, criar uma copia da pq para adulterar dentro do methodo
            std::priority_queue<Node*, std::vector<Node*>, CompareNodes> copy = priorityQueue;
            while (copy.size() != 1) {
                Node* aux1 = copy.top(); copy.pop();
                Node* aux2 = copy.top(); copy.pop();

                int fr = aux1->getFrequency() + aux2->getFrequency();
                Node* subTree = new Node(L'+', fr);
                subTree->setChildren(aux1, aux2);
                copy.push(subTree);
            }

            root = copy.top();
            copy.pop();
        }

        void encode(Node *root, std::wstring str) 
        {
            if(root == nullptr) {
                return;
            }

            if(root->isLeaf()) {
                huffmanTable[root->getWord()] = str;
            }

            encode(root->getLeftChield(), str + L"0");
	        encode(root->getRightChield(), str + L"1");

        }

        void buildHuffmanTree(std::wstring strTxt) {
            createFrequencyMap(strTxt);
            createPriorityQueue();
            createTree();
            encode(root, L""); // mudar nome, createHuffmanTable
        }

        std::unordered_map<wchar_t, std::wstring> getHuffmanTable() {
            return huffmanTable;
        }

        std::string freqToString() {
            std::string str = "";
            for (const auto& pair : frequencyMap) {
                str += pair.first; // Adiciona o caractere chave
                str += ":";

                // Convertendo o número inteiro para uma string antes de adicionar a str
                std::string numS = std::to_string(pair.second);
                str += numS;

                str += " ";
            }
            return str;
        }

        std::string mapToString() {
            std::string str = "";
            for (const auto& pair : huffmanTable) {
                str += pair.first; // Adiciona o caractere chave
                str += ":";
                                // Converte de std::wstring para std::string utilizando o objeto converter
                std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
                str += converter.to_bytes(pair.second);
                str += " ";
            }
            return str;
        }

        // Function to export the Huffman tree to a DOT file
        void exportToDot(const std::string& filename) const {
            std::ofstream dot(filename);
            dot << "digraph HuffmanTree {\n";
            traverseAndGenerateDot(root, dot); 
            dot << "}\n";
            dot.close();
        }

        // Function to draw the Huffman tree using Graphviz (platform-independent)
        void drawTree(const std::string& dotFilename = "huffman_tree.dot",
                    const std::string& imageFilename = "../arquivos/huffman_tree.png") const {
            exportToDot(dotFilename);
            std::string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
            std::system(command.c_str());
        }

    private:

        // Helper function for traversing the tree and generating DOT code
        void traverseAndGenerateDot(Node *node, std::ofstream& dot) const {
            if (!node) {
                return;
            }

            dot << "\t\"" << node->getWord() << " (" << node->getFrequency() << ")\" -> \""
                << node->getLeftChield()->getWord() << " (" << node->getLeftChield()->getFrequency() << ")\";\n";
            traverseAndGenerateDot(node->getLeftChield(), dot);

            dot << "\t\"" << node->getWord() << " (" << node->getFrequency() << ")\" -> \""
                << node->getRightChield()->getWord() << " (" << node->getRightChield()->getFrequency() << ")\";\n";
            traverseAndGenerateDot(node->getRightChield(), dot);
        }

        void printHuffmanTree(Node* node) {
            if (node == nullptr) {
                return;
            }

            // Traverse the left subtree
            printHuffmanTree(node->getLeftChield());

            // Print the current node
            if (node->getWord() != L'+') {
                std::wcout << node->getWord() << L" -> " << node->getFrequency() << L"\n";
            } else {
                std::wcout << L"+ -> " << node->getFrequency() << L"\n";
            }

            // Traverse the right subtree
            printHuffmanTree(node->getRightChield());
        }

        //Funções utilizadas no teste e funções para mostrar no terminal
    public:
        void printFreqMap() {
            for (auto wc : frequencyMap) {
                if (std::iswspace(wc.first)) {
                    std::wcout << "' '" << L" -> " << wc.second << L"\n";

                } else { std::wcout << wc.first << L" -> " << wc.second << L"\n"; } 
                        
            }            
        }

        void printPriorityQueue () {
            std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq = priorityQueue;
            while (!pq.empty() ) {          
                Node aux = *pq.top();
                std::wcout << aux.getWord() << " " << aux.getFrequency() << "\n";
                pq.pop();
            }
        }   

        void printTree() {
            printHuffmanTree(root);
        }

        void printHuffmanTable() {
            for (auto wc : huffmanTable) {
                if (std::iswspace(wc.first)) {
                    std::wcout << "' '" << L" -> " << wc.second << L"\n";

                } else { std::wcout << wc.first << L" -> " << wc.second << L"\n"; } 
                    
            }            
        }

};