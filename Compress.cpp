#include "HuffmanTree.cpp"

class Compress {
    public:
        static std::vector<bool> compressText(const std::wstring &str, const std::unordered_map<wchar_t, std::vector<bool>> &binaryVector) {
            std::vector<bool> compressTxt;

            for (wchar_t ch : str) {
                const std::vector<bool>& bits = binaryVector.at(ch);
                compressTxt.insert(compressTxt.end(), bits.begin(), bits.end());
            }

            return compressTxt;
        }

        static std::wstring compressText(std::string str, const std::unordered_map<wchar_t, std::wstring> &huffmanTable) {
            std::wstring compressTxt = L"";

            for (char ch : str) {
                wchar_t wc = static_cast<wchar_t>(ch); 
                compressTxt += huffmanTable.at(wc); 
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