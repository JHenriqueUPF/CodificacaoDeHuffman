#include "HuffmanTree.cpp"

class Compress {


    public:
        static std::wstring compressText(std::string str, const std::unordered_map<wchar_t, std::wstring> &huffmanTable) {
            std::wstring compressTxt = L"";

            for (char ch : str) {
                wchar_t wc = static_cast<wchar_t>(ch); // Convertendo char para wchar_t
                compressTxt += huffmanTable.at(wc); // Usando at() para acessar o valor na tabela Huffman
            }

            return compressTxt;
        }

        //Sobrecarga
        static std::wstring compressText(std::wstring str, const std::unordered_map<wchar_t, std::wstring> &huffmanTable) {
            std::wstring compressTxt = L"";

            for (wchar_t ch : str) {
                compressTxt += huffmanTable.at(ch); 
            }

            return compressTxt;
        }
       

};