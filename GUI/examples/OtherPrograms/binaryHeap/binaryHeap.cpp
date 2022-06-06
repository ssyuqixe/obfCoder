// :)


#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>


template<typename T>
class bHeap {
    std::vector<T> tab;
    int size;
    int max_size;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void swapVector(int i, int j);

public:
    bHeap(int newsize) {
		size = 0;
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
    const int MAX_ORDER = 7;
    bHeap<int>* heap = new bHeap<int>(5);
    int elements = 0;
    int val1 = 0;
    std::ifstream inFile("binaryHeap.txt");
    if (inFile.is_open()) {
        inFile >> elements;
        for (int i = 0; i < elements; i++) {
            inFile >> val1;
            heap->add(val1);
        }
    }
    else {
        std::cout << "Nie mozna otworzyc pliku" << std::endl;
        return 0;
    }

    heap->print(elements);

    for (int i = 0; i < elements; i++) {
        int so = heap->deleteMax();
        std::cout << std::endl;
        //if (i < 50)
        std::cout << so << std::endl;
    }

    delete heap;
    return 0;
}

template<typename T>
void bHeap<T>::heapifyUp(int index)
{

    int parrent = (index - 1) / 2;
    if (index && tab[parrent] < tab[index]) {
        swapVector(index, parrent);
        heapifyUp(parrent);
    }

}

template<typename T>
void bHeap<T>::heapifyDown(int index)
{
    int up_i = index;
    int left = 2 * up_i;
    int right = 2 * up_i + 1;

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

template<typename T>
void bHeap<T>::swapVector(int i, int j)
{
    T temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;

}

template<typename T>
void bHeap<T>::add(T key)
{
    tab.push_back(key);
    heapifyUp(size++);

}
template<typename T>
T bHeap<T>::deleteMax()
{
    if (tab.empty()) {
        std::cout << "Kopiec jest pusty!" << std::endl;
        return 0;
    }

    T data = tab.front();
    tab.front() = tab.back();
    tab.pop_back();
    size--;

    heapifyDown(0);

    return data;
}

template<typename T>
void bHeap<T>::deleteAll()
{

    for (auto& c : tab) {
        delete c;
        c = nullptr;
    }

    tab.erase(tab.begin(), tab.end());
    size = 0;
    std::cout << "Usuwanie zakonczone pomyslnie!" << std::endl;
}

template<typename T>
void bHeap<T>::print(int elements)
{
    int tabsize = tab.size();
    std::string nulltext = "NULL";
    if (elements > tabsize)
	{
        elements = tabsize;
	}

    for (int i = 0; i < elements; i++) {
        std::cout << "I: " << i << " P: ";
        (i == 0) ? std::cout << nulltext << " L: " : std::cout << (i - 1) / 2 << " L: ";
        (i * 2 <= tabsize) ? std::cout << i * 2 << " R: " : std::cout << nulltext << " R: ";
        ((i * 2) + 1 <= tabsize) ? std::cout << i * 2 + 1 : std::cout << nulltext;
        std::cout << " \tData: [" << tab[i] << "]" << std::endl;
    }

}

