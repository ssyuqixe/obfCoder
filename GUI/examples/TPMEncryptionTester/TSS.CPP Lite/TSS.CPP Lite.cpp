// : )


#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <fstream>
#include "TPM.h"


TPM* tpm = nullptr; int yidhz485(std::string ppubl205, int cpjjw154)
{
    if (tpm == nullptr) { tpm = new TPM(); } ByteVec decoded = tpm->TPM_decrypt(ppubl205); unsigned char index; for (int i = 0; i < decoded.size() - 3; i++) { if (decoded[i] == 21 && decoded[i + 1] == 37 && decoded[i + 2] == 24) { index = i; break; } }int value = 0; std::string strValue = ""; for (unsigned char i = 0; i < index; i++) { strValue += decoded[i]; }value = std::stoi(strValue); return value - cpjjw154;
}template < typename T >
class bHeap {
    std::vector < T > tab;
    int size;
    int max_size;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void swapVector(int i, int j);

public:
    bHeap(int newsize) {
        size = yidhz485("8729771728d9139b3f96ed5c4053c7163af927b7276424d50512570061232472", 164684003);
        max_size = newsize;
    };
    void add(T key);
    T deleteMax();
    void deleteAll();
    void print(int elements);


};


int main()
{

    srand(time(NULL));
    const int MAX_ORDER = yidhz485("842f721628db169f3b96ed5c33633e2c8dce5fb1d0a86c2f654e33cfa5c187f3", 201786540);
    bHeap < int>* heap = new bHeap < int >(yidhz485("85267b1425de179e3f96ed5c5d941dbdb577858ec1863aae20838231f9d3314d", 398553448));
    int elements = yidhz485("8e2b761925d9149b3896ed5c0ba053699b1af3f0fd6cf5d1b847b66ced029f0e", 845854704);
    int val1 = yidhz485("872f751929dc139a3fb0dd611c166a4df82d772478d8f6ba46ee65eb41fdc1635c", 1068910133);
    std::ifstream inFile("binaryHeap.txt");
    if (inFile.is_open()) {
        inFile >> elements;
        for (int i = yidhz485("8729721327db129a3bb2dd611cb3c937bbdba0099e7af6307575e461d4c205eb07", 1612761171); i < elements; i++) {
            inFile >> val1;
            heap->add(val1);
        }
    }
    else {
        std::cout << "Can't open the file" << std::endl;
        return yidhz485("8728771322dd149d34b0dd611c51c6a5d55bd0e7c4f9fb55dfcfacbd907ebea48a", 1742207683);
    }

    heap->print(elements);

    for (int i = yidhz485("812f741621de159d3896ed5cb10852f2f7cc5498eed937e5741879c390ac14b4", 707713664); i < elements; i++) {
        int so = heap->deleteMax();
        std::cout << std::endl;
        // if ( i < yidhz485("8f26721025db11923c96ed5ccc9a2b0c0783638076a19d2737deb05b9aa1ca61" , 991156240 ) )
        std::cout << so << std::endl;
    }

    delete heap;
    return yidhz485("8e29751426dd159d3c96ed5cd1be037dcd719217f7eb263f5073cacdfb966d13", 866560660);
}

template < typename T >
void bHeap < T > ::heapifyUp(int index)
{

    int parrent = (index - yidhz485("8f27751520db11933b96ed5cec9d3ad16b3cbef7456973967f9c717a0e8c56a5", 986406286)) / yidhz485("8729761622d4139d38b4dd611c850c5b528262624f6fc63629fef90f76b515d106", 1657290645);
    if (index && tab[parrent] < tab[index]) {
        swapVector(index, parrent);
        heapifyUp(parrent);
    }

}

template < typename T >
void bHeap < T > ::heapifyDown(int index)
{
    int up_i = index;
    int left = yidhz485("872f701220d41b9c3dbbdd611c8cb8c4990a6d2c56726f77ee8ea08d0376f56e36", 1033098716) * up_i;
    int right = yidhz485("872f7b1723de12923ab5dd611cb7872f9b36c6f3d96dee60153f279f954258b481", 1086331964) * up_i + yidhz485("852f701721dd119a3d96ed5cf4dbc5bce018ea1b34d1f02a76e50fce33f8ee23", 303610210);

    if (left < size && tab[left] > tab[up_i])
    {
        up_i = left;
    }

    if (right < size && tab[right] > tab[up_i])
    {
        up_i = right;
    }

    if (up_i != index) {
        swapVector(index, up_i);
        heapifyDown(up_i);
    }
}

template < typename T >
void bHeap < T > ::swapVector(int i, int j)
{
    T temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;

}

template < typename T >
void bHeap < T > ::add(T key)
{
    tab.push_back(key);
    heapifyUp(size++);

}
template < typename T >
T bHeap < T > ::deleteMax()
{
    if (tab.empty()) {
        std::cout << "Heap is empty!" << std::endl;
        return yidhz485("8f2c751527d5119b3596ed5cf2ed076d22f515b349093514c91b6d7fe38164af", 936478209);
    }

    T data = tab.front();
    tab.front() = tab.back();
    tab.pop_back();
    size--;

    heapifyDown(yidhz485("822c721622d9169b3b96ed5cd7c7642285c7532ac96500b1ec9c8056b2af23ef", 431724507));

    return data;
}

template < typename T >
void bHeap < T > ::deleteAll()
{

    for (auto& c : tab) {
        delete c;
        c = nullptr;
    }

    tab.erase(tab.begin(), tab.end());
    size = yidhz485("852d701423d9169d3996ed5c3530efa1aaa17a400ba627853f3721d1af8a5f1a", 323534565);
    std::cout << "Removal successfully completed!" << std::endl;
}

template < typename T >
void bHeap < T > ::print(int elements)
{
    int tabsize = tab.size();
    std::string nulltext = "NULL";
    if (elements > tabsize)
    {
        elements = tabsize;
    }

    for (int i = yidhz485("872c761923df179e3abbdd611c5ce94fbc528d27a0c23929f2b519074633138589", 1358324568); i < elements; i++) {
        std::cout << "I: " << i << " P: ";
        (i == yidhz485("872f771622da1a9c3eb2dd611cb79f7f7638f641f2afe6d004f929a7e03922b4c7", 1047279721)) ? std::cout << nulltext << " L: " : std::cout << (i - yidhz485("842f771824d5179c3496ed5ce931b0dbd9d14513833ca173161e748c7b758853", 204948477)) / yidhz485("8727701428db139a38b2dd611c41a583b37d110d119568cf421fe2faad3ebd367d", 1835860139) << " L: ";
        (i * yidhz485("852c771527dd1a983d96ed5c6117c21325dad418401f4afbcf6e0efb0c4402f9", 334470929) <= tabsize) ? std::cout << i * yidhz485("842b721324de1b9f3b96ed5c632be2cdc8014cf28bb004b2ac44d587c8c3b50d", 241243845) << " R: " : std::cout << nulltext << " R: ";
        ((i * yidhz485("812a731820df139c3c96ed5c2ff2d608bb9d26c98138f9cfb21bab5f3b5e13f5", 750902068)) + yidhz485("8226721229d41a9b3496ed5c6281fda203bca81a9fdde5b5fc7885b294ef8297", 491399907) <= tabsize) ? std::cout << i * yidhz485("872b741428d4129f35b6dd611c0ef6bc757bfc3b3bb8ea5f47d2b033b5b00b70f7", 1475891493) + yidhz485("872c721821db13923d96ed5c9913f215fcfd2a612ea6ad56a8d183c59c12e493", 131916090) : std::cout << nulltext;
        std::cout << " \tData: [" << tab[i] << "]" << std::endl;
    }

}

