#include "FileReader.cpp"

using namespace std;

string getFilename();
void advertance();

int main() {
    advertance();
    FileReader fRead;
    HuffmanTree ht;

    string name = getFilename();
    string fileName = "../arquivos/" + name;

    wstring strTxt = fRead.readFileToWString(fileName );

    fRead.compressFile(fileName, ht);
    ht.printHuffmanTable();
    ht.draw();

    std::wcout << L"Tamanho do arquivo original: " << fRead.getNormalFileSize() << L" bytes" << std::endl;
    std::wcout << L"Tamanho do arquivo compactado: " << fRead.getCompressedFileSize() << L" bytes" << std::endl;
    std::wcout << L"Taxa de compressão: " << fRead.getCompressionRate() << L"%" << std::endl;

    return 0;
}

string getFilename() {
    cout << "Digite o nome do arquivo a ser compactado (deve estar na pasta arquivos!) " << endl << "\tNome do arquivo: ";
    string fileName;
    cin >> fileName;
    return fileName;
}

void advertance() {
    cout << "1 - O arquivo a ser compactado deve estar na pasta arquivos(dentro da pasta do programa)!" 
    << endl
    << "2 - A funcionalidade de descompactar ainda não está implementada, o arquivo compactado é salvo sem o necesario para descompactar!"
    << endl
    << "Trabalho feito para disciplina de Estrutura de Dados 2 ministrada pelo professor Leonardo Costella"
    << endl
    <<"e para a disciplina de Programação Orientada a Objetos, ministrada pelo professor Jaqson Dalbosco"
    << endl
    << "Trabalho feito por: João Henrique Menezes, e Eric Mota!" 
    << endl 
    << "Link do Projeto no GitHub: https://github.com/JHenriqueUPF/CodificacaoDeHuffman" << endl << endl << endl;
}
