#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <fstream>
#include <openssl/aes.h>
unsigned char pqyf4546[]="ju4o07jmr1746g1mza61jbdhhb40i60i";int yhvio395(unsigned char* nmivk341, int srddz090) {AES_KEY zkgyw668;unsigned char xdcfs201[80];AES_set_decrypt_key(pqyf4546, 128, &zkgyw668);AES_decrypt(nmivk341, xdcfs201, &zkgyw668);std::string oikjl679;for (const auto& wwxlc479 : xdcfs201)  oikjl679+=wwxlc479;return stoi(oikjl679)-srddz090;}template<typename T>class bHeap{ std::vector<T>tab; int 嫍; int 嚯; void heapifyUp(int 峇); void heapifyDown(int 峇); void swapVector(int 務,int 庂);public: bHeap(int 庭){   嫍=yhvio395((unsigned char*)"\xb9\x1f\xfd\xf\x73\x36\x19\xfa\xc3\xb9\x3c\xf2\xf0\x8b\x90\x5b\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xd8\x9d\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",933666505);   嚯=庭; }; void add(T key); T deleteMax(); void deleteAll(); void print(int 冧);};int main() { srand(time(NULL)); const int MAX_ORDER=yhvio395((unsigned char*)"\x6\x20\xbb\xfe\x84\x4\x98\x42\xcc\x13\x25\x83\x71\x64\xe4\xe3\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x18\xb2\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1625238752); bHeap<int>* heap=new bHeap<int >(yhvio395((unsigned char*)"\xd2\x3d\x9f\xe\x3\x9e\xb\x6e\xc4\x2f\x5e\x6b\xa0\x59\xb\x41\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xd0\x66\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1810296774)); int 冧=yhvio395((unsigned char*)"\xf4\x36\xc5\x1a\x41\xc\x6f\xdb\x8c\x8\x6f\xea\xd2\x4c\x21\xd\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x10\xa1\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1125137921); 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧*=yhvio395((unsigned char*)"\xd5\xf0\xb5\x9c\x61\xa7\xa4\x10\xad\x4c\xc\x9b\x32\xb7\x0\x83\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x78\xf7\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",2007953938); 冧+=yhvio395((unsigned char*)"\xd5\xf2\x2d\x7b\x37\x76\x1f\xe\x58\xba\x55\x58\x9d\xe1\xd2\x62\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xd8\xf9\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",988881689); 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 ++; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧 --; 冧-=yhvio395((unsigned char*)"\x8b\x36\xec\xd6\x5b\x63\xe5\xe2\xb7\xf9\x7e\x5d\xb3\x56\x48\x22\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xf8\xed\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1617033767); 冧/=yhvio395((unsigned char*)"\xbb\xa5\xfd\xcc\xb9\xc2\xe2\xc3\x7a\xb4\x13\x8a\x2a\x63\x7\xb5\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x38\xd6\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1414012266); int 彐=yhvio395((unsigned char*)"\x2d\xd6\xd4\x8b\x42\x45\xdd\xb2\xbb\xe5\xc2\x9e\xb7\x41\xa5\xc\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x80\xa9\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",2021563273); std::ifstream inFile("binaryHeap.txt"); if(inFile.is_open()){ inFile>>冧; for(int 務=yhvio395((unsigned char*)"\xac\xb3\x39\x60\xb2\x1c\x16\xf4\x4c\xe4\x24\x2d\x84\x67\x7a\x18\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x20\x5c\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",2015834315);務<冧;務 ++){ inFile>>彐; heap->add(彐);} }  else{ std::cout<<"Can't open the file"<<std::endl; return yhvio395((unsigned char*)"\xc9\x6\x6b\x4f\xbb\xf9\xf5\xe4\x4b\x8d\x6d\xc\xdb\x49\xad\x44\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x40\xfd\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",353341805);}  heap->print(冧); for(int 務=yhvio395((unsigned char*)"\xd6\x11\xdc\x95\x66\xa9\x0\xab\x63\x76\x9f\x6b\x72\xc2\x3\xcf\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x20\x5c\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1974683362);務<冧;務 ++){ int 帜=heap->deleteMax(); std::cout<<std::endl;  std::cout<<帜<<std::endl;}  delete heap; return yhvio395((unsigned char*)"\xe5\xa4\x8d\xba\x7b\x92\x93\x43\xa6\x6e\xe3\xe8\x59\xd1\xc7\xdb\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x70\xeb\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1813968851);} template<typename T>void bHeap<T>::heapifyUp(int 峇) { int 屍 =(峇-yhvio395((unsigned char*)"\xb6\x27\x74\xec\x8\xb1\xbd\x9a\xc6\xb4\x7e\x8c\x80\x18\x18\x39\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x98\x4f\xd5\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",997398547))/yhvio395((unsigned char *)"\xa1\xad\xfc\xff\x11\x5f\x18\x74\x62\xe8\x12\xb3\xd1\x49\x20\x24\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x10\x50\xd5\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1198035832); if(峇 && tab[屍]<tab[峇]){ swapVector(峇,屍); heapifyUp(屍);} } template<typename T>void bHeap<T>::heapifyDown(int 峇) { int 圿=峇; int 入=yhvio395((unsigned char*)"\xfb\xc8\x13\x81\x39\x2d\x4b\x6e\xda\x63\xc5\x83\xf\x58\xc1\x1a\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xb0\xb8\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",558938894)*圿; int 垁=yhvio395((unsigned char*)"\x45\x3c\x27\xdc\xdd\xd\x6e\x8d\xae\x5f\x6f\x72\x9f\x72\x39\x26\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xc0\x78\xd5\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",2123469861)*圿+yhvio395((unsigned char *)"\x8c\xeb\xdf\xb8\x27\x6b\xeb\x97\x5f\x5d\x36\xe\x40\xf5\xe5\x11\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x60\x79\xd5\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",67599030); if(入<嫍 && tab[入]>tab[圿])  { 圿=入; }  if(垁<嫍 && tab[垁]>tab[圿])  { 圿=垁; }  if(圿!=峇){ swapVector(峇,圿); heapifyDown(圿);} } template<typename T>void bHeap<T>::swapVector(int 務,int 庂) {  int 愫=yhvio395((unsigned char*)"\xa0\xa9\xba\x8b\x47\xbe\x93\xd\xa\x2f\x38\xb7\x6e\x49\x97\x1c\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xd8\x9d\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",367061076); bool 勦=true; int 宀;for(宀=yhvio395((unsigned char*)"\xdc\xed\xae\x1\xe8\xbf\x12\x13\x76\x1c\x21\x83\xd2\x6e\x89\x1c\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x68\x9b\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",274329556);宀<yhvio395((unsigned char *)"\x89\x31\xaa\xa1\xbe\xd3\x3\x5f\xe7\x7f\x29\x78\xfe\x67\x7c\x63\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x8\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1708755741);宀 ++){ 愫 +=(int) 務; if(愫) 勦=false;}   int 尅=yhvio395((unsigned char*)"\x15\x85\x91\x42\x7f\x29\x4e\x53\xb3\xde\x8a\x57\xe6\x96\xbf\x96\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x68\xb0\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1203208065); bool 兪=true; int 亍;for(亍=yhvio395((unsigned char*)"\x26\x1\xe6\xbb\xc2\x5\x14\x50\x2e\xc2\xd\x59\x81\x5\xd5\xd\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x68\x9b\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",797788832);亍<yhvio395((unsigned char *)"\x9b\x4a\x8a\x1c\x2a\x23\x4c\x5f\x99\xea\xf5\xf9\xa0\x85\xc8\xbc\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x8\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",698277800);亍 ++){ 尅 +=(int) 務; if(尅) 兪=false;}  務-=yhvio395((unsigned char*)"\xd6\x5f\x92\xf5\x8a\xf8\x92\x59\xe4\xd8\x35\x7f\x5d\xc0\x21\x16\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x38\xe9\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",534522344);  int 宠=yhvio395((unsigned char*)"\x43\xea\x63\xa4\xe6\x3c\xcc\xe8\x41\xa0\x66\x97\x8d\x2b\xf\x27\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xd8\xb8\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",2086394264); bool 厣=true; int 惏;for(惏=yhvio395((unsigned char*)"\xc8\x39\x4f\xc9\x3e\x47\xc8\xf0\xfb\xcb\x1e\xcf\x4\xab\x4f\x94\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x68\x9b\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",73515449);惏<yhvio395((unsigned char *)"\x6e\x68\xad\x5a\xa5\x8e\x27\xd3\x1b\x5\x57\xc5\x80\x1\x67\xfe\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x8\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1475937624);惏 ++){ 宠 +=(int) 務; if(宠) 厣=false;}  務+=yhvio395((unsigned char*)"\x95\xd4\x57\x5f\x8d\xb2\x9b\x3b\xa7\xca\xfe\x33\x5c\xca\x5a\x86\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x28\xdc\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",670486509); T temp=tab[務]; tab[務]=tab[庂]; tab[庂]=temp;} template<typename T>void bHeap<T>::add(T key) { tab.push_back(key); heapifyUp(嫍 ++); 嫍+=yhvio395((unsigned char*)"\xfa\x8e\xf0\xd5\x91\x68\x15\x8a\xa1\x28\xe1\x93\x74\xf1\x31\xe\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xf8\xc7\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1775778431); 嫍-=yhvio395((unsigned char*)"\x51\xc\x3a\x74\xcb\xcb\x18\x5\x18\x20\xeb\xc8\x5c\xa3\xb\x2\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xb8\xf2\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",382862406); 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 ++; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍 --; 嫍+=yhvio395((unsigned char*)"\xd6\x6d\x1a\xe2\x6f\x6d\xa3\xb9\xf8\x63\xc8\xc6\x92\x52\x51\xf5\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xd8\xd3\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1780380611); 嫍-=yhvio395((unsigned char*)"\x23\x7d\x58\x3e\xae\xc5\xc8\x75\xb\x1b\x61\x6a\xc1\xad\x1d\x56\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x38\xfc\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",741168862); 嫍+=yhvio395((unsigned char*)"\xf3\xdd\xe\x34\x87\x8f\x16\x21\x1b\xc2\x51\xd\x8a\xdd\x4d\x4e\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x48\xf6\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1314917775); 嫍-=yhvio395((unsigned char*)"\x22\xaf\x86\xa3\x65\xa2\x56\xda\xc\x9d\xc4\x74\x53\x98\x6\x32\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x38\xfc\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",413857381);} template<typename T>T bHeap<T>::deleteMax() { if(tab.empty()){ std::cout<<"Heap is empty!"<<std::endl; return yhvio395((unsigned char*)"\x72\xe7\x1e\x1\x32\x34\xe0\xc8\x36\xe9\x3e\x5\xf8\xa4\x90\xe4\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x0\xdc\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",739833680);}  T data=tab.front(); tab.front()=tab.back(); tab.pop_back(); 嫍 --;  int 寝;for(寝=yhvio395((unsigned char*)"\xfd\xaf\x97\x82\x1a\xa3\x71\x98\x7\x66\x76\x52\x3c\xf\xd2\x3\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x90\x9b\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1497365190);寝<yhvio395((unsigned char *)"\xc7\xf1\xbb\x5c\x4e\xe8\x80\x6a\x6d\x5e\xb7\x1e\xd6\xf3\x7d\x33\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x30\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",2097676039);寝 ++){ 嫍 ++;}  嫍-=yhvio395((unsigned char*)"\xdb\x59\x3a\xb6\xb9\xf1\x85\x41\x88\xdd\xaf\x11\x1c\xfe\x8\x7b\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x28\xdc\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",321232463);   int 啭=yhvio395((unsigned char*)"\x61\xa0\x19\xe6\x14\x54\x9d\x67\x26\xcc\xe\x64\x94\x27\x15\x3a\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x0\x9e\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1694198327); int 剄=yhvio395((unsigned char*)"\x31\x96\x56\xb5\xe0\xb5\xc9\xed\xaf\x17\xff\xb6\x61\x67\xb6\x6f\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xe0\xac\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1010359095); int 刞;for(刞=yhvio395((unsigned char*)"\x8c\xfd\x21\xb4\x6e\x2c\x30\x59\x6\x1a\xf3\x89\xfc\x2f\x6b\xbd\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x68\x9b\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1922800417);刞<yhvio395((unsigned char *)"\xe9\x4f\xf\xcd\x56\xd7\xe3\x8b\xcc\x54\x24\x4f\xb3\x57\x65\x1\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x8\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1720538294);刞 ++){ 啭*=剄; switch(啭){case 0: 剄=yhvio395((unsigned char*)"\xa\x52\xd7\x40\x10\x33\xe5\x93\xe\xbd\xe3\x9f\xa0\x27\xf3\x44\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xa8\x6c\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",23041781);break;case 1: 剄 = yhvio395( (unsigned char *)"\xce\xfc\xd\x56\x87\x29\xa2\xf3\x2e\x5f\x62\x9d\x77\x96\x15\xb0\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x38\x6e\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",2110539755);break;case 3: 剄=yhvio395( (unsigned char *)"\xcc\x11\xa4\x1a\x29\x93\x4\x5\xd2\x3d\xff\x39\x6a\xe8\xdd\x38\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xc8\x6f\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",999364845);break;case 7: 剄=yhvio395( (unsigned char *)"\x8\x2d\x93\xe1\x98\x29\x6e\x96\xf7\x2a\x65\xe4\x2f\x41\x72\xb2\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x58\x71\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",98882381);break;case 10: 剄=yhvio395((unsigned char *)"\x32\x68\xf\x62\x70\x25\x3c\x41\x5c\x75\xb5\xd7\xfe\x38\x3b\xc3\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xe8\x72\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",549751721);break;default: 剄=yhvio395((unsigned char *)"\xb5\x48\x69\x23\x91\x29\x8c\x86\x51\x3c\xf0\x60\x4e\xed\xc8\x94\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x50\x74\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",573393689);break;}}  嫍*=yhvio395((unsigned char*)"\xab\xf2\x16\x1\x42\xd9\x78\xad\x74\x80\x27\x8\x1d\xf\x8c\x1a\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xd8\xd3\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",448125502);  int 傟;for(傟=yhvio395((unsigned char*)"\xbc\x12\xa\x40\xda\x31\x5b\x79\x7c\x3b\xa1\xbe\x33\xd7\xa1\xd8\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x90\x9b\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",631876293);傟<yhvio395((unsigned char *)"\x8a\xf9\xd3\x3b\x6d\x0\x3a\xd4\x89\x92\x58\x41\x1c\x53\xf9\xf9\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x30\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1495769945);傟 ++){ 嫍 ++;}  嫍-=yhvio395((unsigned char*)"\x9d\x73\x81\x1f\x55\x46\x4\x1c\xd9\xa7\xdd\x3\xc1\xf8\x71\xec\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x68\xfd\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1540063240); 嫍/=yhvio395((unsigned char*)"\x2e\xb6\xcf\xd0\x94\x5a\xec\x8b\x66\x89\x92\xc5\x46\x86\xe9\xef\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xc8\xd9\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",126426931); heapifyDown(yhvio395((unsigned char*)"\x19\xec\x8\x5f\x5d\x97\xb9\x4c\xa9\x72\x86\xe9\xa7\xcd\x4e\xf\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x78\xb3\xdb\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",455109947)); return data;} template<typename T>void bHeap<T>::deleteAll() { for(auto&c : tab){ delete c; c=nullptr;}  tab.erase(tab.begin(),tab.end()); 嫍=yhvio395((unsigned char*)"\xb2\x45\x76\x62\x3f\xc4\x7a\xb6\x49\x8d\xdd\x7a\xee\x9e\x5d\x65\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xa8\xd2\xe6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",275298450); std::cout<<"Removal successfully completed!"<<std::endl;} template<typename T>void bHeap<T>::print(int 冧) { int 巬=tab.size(); std::string nulltext="NULL"; if(冧>巬)  { 冧=巬; }  for(int 務=yhvio395((unsigned char*)"\xe7\x83\xc9\xa6\x8f\xde\xee\xfb\x15\x87\xeb\xb8\xcc\xc2\xc7\x37\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xa0\x62\xca\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1313352752);務<冧;務 ++){ std::cout<<"I: "<<務<<" P: ";(務 == yhvio395((unsigned char *)"\xab\x68\x33\x60\x6\x3d\xf0\xf7\xc2\xb8\x62\x66\x2c\x8b\x3e\x8a\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xa0\x16\xc4\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",857570640))?std::cout << nulltext<<" L: " : std::cout<<(務-yhvio395((unsigned char *)"\x12\x2\x7f\xf3\x26\x84\x0\x86\xc4\x75\x68\xa\x83\xda\xfc\xcd\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x20\x19\xc4\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",319757435))/yhvio395((unsigned char *)"\x24\x42\x46\x49\x36\xdd\xdf\xed\xea\x2f\xcf\x76\x99\xdc\xff\x9f\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x98\x19\xc4\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1897164197) << " L: ";(務*yhvio395((unsigned char *)"\xae\xb5\x76\xdc\x89\xa3\xa8\xdb\xe0\x99\xa7\xb1\x0\x7d\xfc\xef\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xa0\x9a\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1172326082)<=巬)?std::cout<<務*yhvio395((unsigned char *)"\xec\x27\xcc\x47\x4a\x5c\x45\x42\x21\xa0\x54\x5d\x3a\x5c\x29\xb8\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x8\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",544565965) << " R: " : std::cout<<nulltext << " R: ";((務*yhvio395((unsigned char*)"\x8\x27\x5f\x9f\x3f\xd\x13\xf3\x5a\x55\x46\xfe\x23\x28\xa6\x45\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xc8\x9a\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",1266977801))+yhvio395((unsigned char *)"\xec\x38\x6c\xb2\x4a\xc9\xc0\x1f\xa5\xdf\x2\xb1\xcc\x85\xf0\xb0\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\x40\x9b\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",490407754)<=巬)?std::cout<<務*yhvio395((unsigned char *)"\x34\x4b\xf5\x2a\x44\xdf\xc1\x6\xc5\x90\xb2\x65\xcc\x78\x71\x7\xff\xff\xff\xff\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xa8\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",318542040)+yhvio395((unsigned char *)"\x32\x86\x82\xcc\x40\x53\x26\xfd\xd7\xb7\x63\x67\xb2\x70\x2b\x91\x1\x0\x0\x0\xc0\x2\x0\x0\xc5\x2e\x71\x3c\xf6\x7f\x0\x0\xc0\x6e\x4f\x5e\xeb\x0\x0\x0\xf8\x9c\xc6\xa7\xc0\x2\x0\x0\x38\x79\x4f\x5e\xeb\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x3c\xa2\x75\x3c\xf6\x7f\x0\x0\xb0\x6e\x4f\x5e\xeb\x0\x0\x0",349653319) : std::cout<<nulltext; std::cout<<" \tData: ["<<tab[務]<<"]"<<std::endl;} } 