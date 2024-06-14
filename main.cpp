#include <iostream>
#include <fstream>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <cwctype>
#include <queue>

struct Node{
    int frequency;
    char word;
    Node *right, *left;
    

    // Construtor que inicializa o Node com a frequência e a palavra fornecidas
    Node(int freq, wchar_t w) : frequency(freq), word(w), right(nullptr), left(nullptr) {}

    Node(int freq, wchar_t w, Node *l, Node *r) : frequency(freq), word(w), right(l), left(r) {}
    
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

int main() {

    std::string nomeArquivo = "../teste.txt";
    std::wifstream file(nomeArquivo);

    // Configura a leitura de arquivos wide com codificação UTF-8
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    // Verifica se o arquivo foi aberto corretamente
    if (!file.is_open()) {
        std::wcerr << L"Nao foi possivel abrir o arquivo." << std::endl;
        return 1;
    }

    std::unordered_map<wchar_t, int> frequencyMap;
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> filaOrdenada;
    
    //cria a tabela de frequncia
    frequencyMap = createFrequencyMap(file);
    file.close();

    filaOrdenada = createPriorityQueue(frequencyMap);
    
    //printFrequencyMap(frequencyMap);
    //printPriorityQueue(filaOrdenada);

    return 0;
}