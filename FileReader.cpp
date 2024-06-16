#include <fstream>
#include <sstream>
#include "Compress.cpp"
#include <filesystem> 


class FileReader {
    private:
        std::string nameCompressFile;
        std::string nameFile;
        std::wstring compressedFile;
        std::wstring normalFile;

    public:
        // Mthood para retornar o tamanho do compressedFile em bytes
        std::size_t getCompressedFileSize() const {
            size_t compressedFileSizeBits = compressedFile.size();
            size_t compressedFileSizeBytes = (compressedFileSizeBits + 7) / 8;
            return compressedFileSizeBytes;
        }

        // Metodo para retornar o tamanho do normalFile em bytes
        std::size_t getNormalFileSize() const {
            return normalFile.size() * sizeof(wchar_t);
        }
        
        // Metodo para calcular a taxa de compressão em %
        double getCompressionRate() const {
            std::size_t originalSize = getNormalFileSize();
            std::size_t compressedSize = getCompressedFileSize();
            
            if (originalSize == 0) {
                return 0.0; // Evitar divisão por zero
            }
            
            double compressionRate = (1.0 - static_cast<double>(compressedSize) / originalSize) * 100;
            return compressionRate;
        }

        static std::wstring readFileToWString(const std::string fileName) {
            std::wstring content = L"";
            std::wifstream file(fileName); // Converter std::wstring para const wchar_t*
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir o arquivo: " << fileName << std::endl;
                return content;
            }

            // Definir a locale para leitura UTF-8
            file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

            std::wstringstream wss;
            wss << file.rdbuf();  // Lê todo o conteúdo do arquivo para a wstringstream

            content = wss.str();  // Armazena o conteúdo em uma wstring

            file.close();
            return content;
        }

        void compressFile(std::string nameFile, HuffmanTree &ht) {
            std::wstring strTxt = readFileToWString(nameFile);
            normalFile = strTxt;
            ht.buildHuffmanTree(strTxt);
            Compress cp;
            compressedFile = cp.compressText(strTxt, ht.getHuffmanTable());
            saveCompressedFile(nameFile, compressedFile/*, ht*/);
        }

    private:
        static void saveCompressedFile(std::string nameFile, std::wstring str/*, HuffmanTree &ht*/) {
            
            std::string nameCompress = replaceTxtWithZip(nameFile);

            std::ofstream arquivo(nameCompress);
            if (arquivo.is_open()) {
                    
                /*std::string frS = ht.freqToString();
                arquivo << frS << "\n";

                std::string mapS = ht.mapToString();             
                arquivo << mapS << "\n";*/
                // Converter std::wstring para std::string antes de escrever no arquivo
                std::string strA = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
                    
                arquivo << strA; // Escreve a string convertida para o arquivo
                arquivo.close();
                std::cout << "String salva no arquivo \' "<< nameCompress <<"\'" << std::endl;
            } else {
                std::cerr << "Erro ao abrir o arquivo \' "<< nameCompress <<"\'" << std::endl;
            }
        }

        static std::string replaceTxtWithZip(const std::string& fileName) {
            std::string newFileName = fileName;

            // Verificar se o nome do arquivo termina com ".txt"
            if (newFileName.size() >= 4 && newFileName.compare(newFileName.size() - 4, 4, ".txt") == 0) {
                // Remover ".txt" e adicionar ".zip"
                newFileName.replace(newFileName.size() - 4, 4, ".zip");
            } else {
                std::cerr << "O arquivo não tem a extensão .txt" << std::endl;
            }

            return newFileName;
        }
};