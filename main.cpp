#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>

// Estrutura para os node da arvore de Huffman
struct Node{
    int frequency;
    char word;
    Node *right, *left;
    
    Node(int freq, wchar_t w) : frequency(freq), word(w), right(nullptr), left(nullptr) {}

    Node(int freq, wchar_t w, Node *l, Node *r) : frequency(freq), word(w), right(l), left(r) {}
    
};

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
    file.close();
    
    return 0;
}