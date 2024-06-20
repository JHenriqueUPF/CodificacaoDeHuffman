#include "Node.cpp"
#include <unordered_map>
#include <queue>
#include <iostream>
#include <locale>
#include <codecvt>
#include <cstdlib> 


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
        std::unordered_map<wchar_t, std::vector<bool>> binariVector;
    
    public:
        HuffmanTree() : root() {}

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

        void createTree() { // mudar, criar uma copia da pq para adulterar dentro do methodo <Não mais necessario, retornar como estava>
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

        //codifica utilizando wchar_t <Propósito de compreensão do código>
        void createHuffmanTable(Node *root, std::wstring str) 
        {
            if(root == nullptr) {
                return;
            }

            if(root->isLeaf()) {
                huffmanTable[root->getWord()] = str;
            }

            createHuffmanTable(root->getLeftChield(), str + L"0");
	        createHuffmanTable(root->getRightChield(), str + L"1");

        }

        //codifica em bits
        void encode(Node *root, std::vector<bool> str) {
            if (root == nullptr) {
                return;
            }

            if (root->isLeaf()) {
                binariVector[root->getWord()] = str;
            }

            if (root->getLeftChield() != nullptr) {
                std::vector<bool> leftStr = str;
                leftStr.push_back(false);
                encode(root->getLeftChield(), leftStr);
            }

            if (root->getRightChield() != nullptr) {
                std::vector<bool> rightStr = str;
                rightStr.push_back(true);
                encode(root->getRightChield(), rightStr);
            }
        }

        void buildHuffmanTree(std::wstring strTxt) {
            createFrequencyMap(strTxt);
            createPriorityQueue();
            createTree();
            createHuffmanTable(root, L""); // mudar nome, createHuffmanTable
            std::vector<bool> bv;
            encode(root, bv);
        }

        Node* getRoot() {
            return root;
        }

        std::unordered_map<wchar_t, std::vector<bool>> getBinaryVector() {
            return binariVector;
        }

        std::unordered_map<wchar_t, std::wstring> getHuffmanTable() {
            return huffmanTable;
        }

        std::string freqToString() {
            std::string str = "";
            for (const auto& pair : frequencyMap) {
                str += pair.first; 
                str += ":";
                std::string numS = std::to_string(pair.second);
                str += numS;

                str += " ";
            }
            return str;
        }

        std::string mapToString() {
            std::string str = "";
            for (const auto& pair : huffmanTable) {
                str += pair.first; 
                str += ":";
                std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
                str += converter.to_bytes(pair.second);
                str += " ";
            }
            return str;
        }

        //********************
        // Metodos para exportar para .dot
        //********************
        void traverseAndGenerateDot(Node* node, std::ofstream& dot) {
            if (!node) return;

            if (node->getLeftChield()) {
                dot << "\t\"" << escapeChar(node->getWordChar()) << " (" << node->getFrequency() << ")\" -> \"" << escapeChar(node->getLeftChield()->getWordChar()) << " (" << node->getLeftChield()->getFrequency() << ")\";\n";
                traverseAndGenerateDot(node->getLeftChield(), dot);
            }
            if (node->getRightChield()) {
                dot << "\t\"" << escapeChar(node->getWordChar()) << " (" << node->getFrequency() << ")\" -> \"" << escapeChar(node->getRightChield()->getWordChar()) << " (" << node->getRightChield()->getFrequency() << ")\";\n";
                traverseAndGenerateDot(node->getRightChield(), dot);
            }
        }

        void export2dot(Node* root, const std::string& filename) {
            std::ofstream dot(filename);
            dot << "digraph HuffmanTree {\n";

            traverseAndGenerateDot(root, dot);

            dot << "}\n";
        }
        // Função para desenhar a árvore de Huffman usando Graphviz
        void draw() {
            export2dot(root, "../arquivos/huffman_tree.dot");
            std::system("dot -Tpng ../arquivos/huffman_tree.dot -o ../arquivos/huffman_tree.png"); // Windows
            // std::system("dot -Tx11 huffman_tree.dot"); // Linux
        }

        // Função para escapar caracteres especiais
        std::string escapeChar(wchar_t c) {
            switch (c) {
                case L'"':  return "\\\"";
                case L'\\': return "\\\\";
                case L'{':  return "\\{";
                case L'}':  return "\\}";
                case L'<':  return "\\<";
                case L'>':  return "\\>";
                case L'|':  return "\\|";
                case L'[':  return "\\[";
                case L']':  return "\\]";
                case L':':  return "\\:";
                case L';':  return "\\;";
                case L'\n': return "\\n";
                case L'\r': return "\\r";
                case L'\t': return "\\t";
                default:
                    // Caracteres normais no DOT
                    if (std::iswprint(c)) {
                        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
                        return converter.to_bytes(std::wstring(1, c));
                    } else {
                        // Caracteres que não são imprimíveis, como não sei o que fazer com eles, retorno vazio!
                        return "";
                    }
            }
        }


    private:
        void printHuffmanTree(Node* node) {
            if (node == nullptr) {
                return;
            }

            printHuffmanTree(node->getLeftChield());

            if (node->getWord() != L'+') {
                std::wcout << node->getWord() << L" -> " << node->getFrequency() << L"\n";
            } else {
                std::wcout << L"+ -> " << node->getFrequency() << L"\n";
            }

            printHuffmanTree(node->getRightChield());
        }

        std::string wstring_to_string(const std::wstring& wstr) {
            // Calcular o tamanho necessário para a string multibyte
            size_t len = wcstombs(nullptr, wstr.c_str(), 0);
            if (len == (size_t)-1) {
                throw std::runtime_error("Erro na conversão de wstring para string");
            }

            // Alocar espaço para a string multibyte
            std::vector<char> buf(len + 1);
            wcstombs(buf.data(), wstr.c_str(), len + 1);

            return std::string(buf.data());
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
