#include <iostream>
#include <fstream>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <cwctype>

struct Node{
    int frequency;
    char word;
    Node *right, *left;
    

    // Inicializa o nodo com a frequencia e a palavra fornecida 
    Node(int freq, wchar_t w) : frequency(freq), word(w), right(nullptr), left(nullptr) {}

    Node(int freq, wchar_t w, Node *l, Node *r) : frequency(freq), word(w), right(l), left(r) {}
    
};

struct Lista{
    Node* begin;
    int size;

    Lista() : begin(nullptr), size(0) {}

    Lista(Node* inicio) : begin(inicio), size(1) {}

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

//Testes
// Mostra a tabela de frequencia
void printFrequencyMap (std::unordered_map<wchar_t, int> &frequencyMap) {
    
    for (auto wc : frequencyMap) {
        if (std::iswspace(wc.first)) {
            std::wcout << "' '" << L" -> " << wc.second << L"\n";

        } else { std::wcout << wc.first << L" -> " << wc.second << L"\n"; } 
        
    }
}

int main() {

    std::string nomeArquivo = "../teste.txt";
    std::wifstream file(nomeArquivo);

    // Configura a leitura de arquivos wide com codificação UTF-8
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    // Verifica se o arquivo foi aberto corretamente
    !file.is_open() ? (std::wcerr << L"Nao foi possivel abrir o arquivo." << std::endl, 1) : 0;

    std::unordered_map<wchar_t, int> frequencyMap;
    
    //cria a tabela de frequncia
    frequencyMap = createFrequencyMap(file);
    file.close();

    
    printFrequencyMap(frequencyMap);

    return 0;
}