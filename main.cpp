#include <iostream>
#include <fstream>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <cwctype>
#include <queue>
#include <map>

struct Node{
    int frequency;
    char word;
    Node *right, *left;
    

    // Construtor que inicializa o Node com a frequência e a palavra fornecidas
    Node(int freq, wchar_t w) : frequency(freq), word(w), right(nullptr), left(nullptr) {}

    Node(int freq, wchar_t w, Node *l, Node *r) : frequency(freq), word(w), right(l), left(r) {}
    
};

struct Lista{
    Node* begin;
    int size;

    Lista() : begin(nullptr), size(0) {}

    Lista(Node* inicio) : begin(inicio), size(1) {}

};

struct CompareNodes {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};

//cria a tabela de frequencia
std::unordered_map<wchar_t, int> createFrequencyMap (std::wifstream &file) {
    
    std::unordered_map<wchar_t, int> frequencyMap;
    wchar_t c;
    while (file.get(c)) {
        frequencyMap[c]++;
    }
    return frequencyMap;
}



//Fila para a criação da arvore
std::priority_queue<Node*, std::vector<Node*>, CompareNodes> createPriorityQueue (std::unordered_map<wchar_t, int> frequencyMap) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue;
    for (auto c : frequencyMap) {
        priorityQueue.push(new Node(c.second, c.first));
    }
    return priorityQueue;
}

// cria a arvore

Node* criaArvore(std::priority_queue<Node*, std::vector<Node*>, CompareNodes> filaOrdenada) {
    while (filaOrdenada.size() > 1) {
        Node* aux1 = filaOrdenada.top(); 
        filaOrdenada.pop();
        Node* aux2 = filaOrdenada.top(); 
        filaOrdenada.pop();
        int fr = aux1->frequency + aux2->frequency;
        Node* no = new Node(fr, L'#', aux1, aux2);
        filaOrdenada.push(no);
    }

    Node* root = filaOrdenada.top();
    filaOrdenada.pop();
    return root;
}

void encode(Node *root, std::wstring str, std::unordered_map<wchar_t, std::wstring> &huffmanCode) {
        if (root == nullptr) 
            return;

        if (root->right == nullptr && root->left == nullptr) {
            huffmanCode[root->word] = str;
        } else {
            encode(root->left, str + L"0", huffmanCode);
            encode(root->right, str + L"1", huffmanCode);
        }
}

std::wstring encodeFile(std::wifstream &file, const std::unordered_map<wchar_t, std::wstring>& huffmanCode) {
    std::wstring encodedContent = L"";
    wchar_t c;
    while (file.get(c)) {
        encodedContent += huffmanCode.at(c);
        std::wcout << huffmanCode.at(c) << L" ";
    }
    return encodedContent;
}

//Testes
// Mostra a tabela de frequencia
void printFrequencyMap (std::unordered_map<wchar_t, int> &frequencyMap) {
    
    for (auto wc : frequencyMap) {
        if (std::iswspace(wc.first)) {
            std::wcout << "' '" << L" -> " << wc.second << L"\n";

        } else { std::wcout << wc.first << L" -> " << wc.second << L"\n"; } 
        
    }
}

void printPriorityQueue (std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue) {

    while (!priorityQueue.empty() ) {          
        Node aux = *priorityQueue.top();
        std::wcout << aux.word << " " << aux.frequency << "\n";
        priorityQueue.pop();
    }

}

void printHuffmanTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    // Traverse the left subtree
    printHuffmanTree(root->left);

    // Print the current node
    if (root->word != L'#') {
        std::wcout << root->word << L" -> " << root->frequency << L"\n";
    } else {
        std::wcout << L"# -> " << root->frequency << L"\n";
    }

    // Traverse the right subtree
    printHuffmanTree(root->right);
}

void traverseAndGenerateDot(const Node* node, std::ofstream& dot) {
    if (!node) return;

    if (node->left) {
        dot << "\t\"" << node->word << " (" << node->frequency << ")\" -> \"" << node->left->word << " (" << node->left->frequency << ")\";\n";
        traverseAndGenerateDot(node->left, dot);
    }
    if (node->right) {
        dot << "\t\"" << node->word << " (" << node->frequency << ")\" -> \"" << node->right->word << " (" << node->right->frequency << ")\";\n";
        traverseAndGenerateDot(node->right, dot);
    }
}

// Função para exportar a árvore de Huffman para um arquivo DOT
void export2dot(const Node* root, const std::string& filename) {
    std::ofstream dot(filename);
    dot << "digraph HuffmanTree {\n";

    traverseAndGenerateDot(root, dot);

    dot << "}\n";
}

// Função para desenhar a árvore de Huffman usando Graphviz
void draw(const Node* root) {
    export2dot(root, "huffman_tree.dot");
    std::system("dot -Tpng huffman_tree.dot -o huffman_tree.png"); // Windows
    // std::system("dot -Tx11 huffman_tree.dot"); // Linux
}

//printa o map dos códigos binarios
void printHuffmanCode(const std::unordered_map<wchar_t, std::wstring>& huffmanCode) {
    for (const auto& pair : huffmanCode) {
        std::wcout << pair.first << L": " << pair.second << std::endl;
    }
}

int main() {

    std::string nomeArquivo = "../teste.txt";
    std::wifstream file(nomeArquivo);

    // Configura a leitura de arquivos wide com codificação UTF-8
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    // Verifica se o arquivo foi aberto corretamente
    if (!file.is_open()) {
        std::wcerr << L"Não foi possível abrir o arquivo." << std::endl;
        return 1;
    }

    std::unordered_map<wchar_t, int> frequencyMap;
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> filaOrdenada;
    std::unordered_map<wchar_t, std::wstring> huffmanCode; 
    
    //cria a tabela de frequncia
    frequencyMap = createFrequencyMap(file);

    filaOrdenada = createPriorityQueue(frequencyMap);

    //printFrequencyMap(frequencyMap);
    //printPriorityQueue(filaOrdenada);

    Node *raiz = criaArvore(filaOrdenada);
    printHuffmanTree(raiz);
    std::cout << raiz->frequency;

    draw(raiz);

    encode(raiz, L"", huffmanCode);
    printHuffmanCode(huffmanCode);
    file.clear();
    file.seekg(0);
    std::wstring strcode = encodeFile(file, huffmanCode);
    std::wcout << strcode << std::endl;

    file.clear();
    file.seekg(0);

    size_t origFileSizeWchars = 0;
    wchar_t ch;
    while (file.get(ch)) {
        origFileSizeWchars++;
    }
    file.close();

    size_t origFileSizeBytes = origFileSizeWchars * sizeof(wchar_t);

    size_t compressedFileSizeBits = strcode.size();
    size_t compressedFileSizeBytes = (compressedFileSizeBits + 7) / 8;

    double compressionRatio = (1.0 - static_cast<double>(compressedFileSizeBytes) / origFileSizeBytes) * 100.0;

    std::wcout << L"Tamanho do arquivo original: " << origFileSizeBytes << L" bytes" << std::endl;
    std::wcout << L"Tamanho do arquivo compactado: " << compressedFileSizeBytes << L" bytes" << std::endl;
    std::wcout << L"Taxa de compressão: " << compressionRatio << L"%" << std::endl;

    file.close();

    return 0;
}