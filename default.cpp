#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <cmath>  
#include <algorithm> 




bool checkWW ( double 戂 [ ] , int 亙 ) { 
 	 for ( int 啃 = 0 ; 啃 < 亙 ; 啃 ++ ) 
 	 { 
 	 	 if ( 戂 [ 啃 ] > 0 ) { 
 	 	 	 return 1 ; 
 	 	 } 
 	 } 
 	 return 0 ; 
 } 



int findMaxElementIndex ( double 戂 [ ] , int 亙 ) { 
 	 int 伛 = 戂 [ 0 ] ; 
 	 int 僘 = 0 ; 
 	 for ( int 啃 = 0 ; 啃 < 亙 ; 啃 ++ ) 
 	 { 
 	 	 if ( 伛 < 戂 [ 啃 ] ) { 
 	 	 	 伛 = 戂 [ 啃 ] ; 
 	 	 	 僘 = 啃 ; 
 	 	 } 
 	 } 
 	 return 僘 ; 
 } 

int findMinElementIndex ( double 戂 [ ] , int 亙 ) { 
 	 int 伛 = 戂 [ 0 ] ; 
 	 int 僘 = 0 ; 
 	 for ( int 啃 = 0 ; 啃 < 亙 ; 啃 ++ ) 
 	 { 
 	 	 if ( 伛 > 戂 [ 啃 ] && 戂 [ 啃 ] > 0 ) { 
	 啃 ++ ; 
	 啃 ++ ; 
	 啃 ++ ; 
	 啃 ++ ; 
	 啃 ++ ; 
	 啃 ++ ; 
	 啃 ++ ; 
	 啃 ++ ; 
	 啃 -- ; 
	 啃 -- ; 
	 啃 -- ; 
	 啃 -- ; 
	 啃 -- ; 
	 啃 -- ; 
	 啃 -- ; 
	 啃 -- ; 
 	 	 	 伛 = 戂 [ 啃 ] ; 
 	 	 	 僘 = 啃 ; 
 	 	 } 
 	 } 

 	 return 僘 ; 
 } 

int main ( ) { 
 	 int 墒 = 0 ; 
 	 int 外 = 0 ; 
 	 double ** 岶 = nullptr ; 
 	 double * 愿 = nullptr ; 

 	 double * 侔 = nullptr ; 
 	 double * 崶 = nullptr ; 

 	 double * 儢 = nullptr ; ; 

 	 std::ifstream inFile ( "simplex.txt" ) ; 
 	 if ( inFile . is_open ( ) ) { 
 	 	 inFile >> 墒 >> 外 ; 

 	 	 岶 = new double * [ 墒 ] ; 
 	 	 for ( int 啃 = 0 ; 啃 < 墒 ; 啃 ++ ) 
 	 	 { 
 	 	 	 岶 [ 啃 ] = new double [ 外 ] ; 
 	 	 } 

for ( int 妈 = 0 ; 妈 < ( 墒 * 外 ) ; 妈 ++ ) 
 	 	 { 
 	 	 	 
 	 	 	 	 inFile >> 岶 [ ( 妈 / 外 ) ] [ ( 妈 % 外 ) ] ; 
 	 	 	 
 	 	 } 

 	 	 愿 = new double [ 墒 ] ; 
 	 	 for ( int 啃 = 0 ; 啃 < 墒 ; 啃 ++ ) 
 	 	 { 
 	 	 	 inFile >> 愿 [ 啃 ] ; 
 	 	 } 

 	 	 侔 = new double [ 外 ] ; 
 	 	 for ( int 啃 = 0 ; 啃 < 外 ; 啃 ++ ) 
 	 	 { 
 	 	 	 inFile >> 侔 [ 啃 ] ; 
 	 	 } 

 	 	 崶 = new double [ 墒 ] ; 
 	 	 for ( int 啃 = 0 ; 啃 < 墒 ; 啃 ++ ) 
 	 	 { 
 	 	 	 inFile >> 崶 [ 啃 ] ; 
 	 	 } 

 	 	 儢 = new double [ 外 ] ; 
 	 	 for ( int 啃 = 0 ; 啃 < 外 ; 啃 ++ ) 
 	 	 { 
 	 	 	 inFile >> 儢 [ 啃 ] ; 
 	 	 } 


 	 	 inFile . close ( ) ; 
 	 } 
 	 else { 
 	 	 std::cout << "Cant open the file" << std::endl ; 
 	 	 return 0 ; 
 	 } 


 	 for ( int 啃 = 0 ; 啃 < 外 ; 啃 ++ ) 
 	 { 
 	 	 儢 [ 啃 ] = 侔 [ 啃 ] ; 
 	 } 

 	 double 叽 = 0 ; 

 	 bool 傉 = 0 ; 

 	 while ( checkWW ( 儢 , 外 ) ) { 
 	 	 int 嘠 = findMaxElementIndex ( 儢 , 外 ) ; 

 	 	 double * 崚 = new double [ 墒 ] ; 

 	 	 for ( int 啃 = 0 ; 啃 < 墒 ; 啃 ++ ) 
 	 	 { 
 	 	 	 崚 [ 啃 ] = 愿 [ 啃 ] / 岶 [ 啃 ] [ 嘠 ] ; 
 	 	 } 

 	 	 int 亷 = findMinElementIndex ( 崚 , 墒 ) ; 
 	 	 delete [ ] 崚 ; 

 	 	 崶 [ 亷 ] = 侔 [ 嘠 ] ; 

 	 	 double 嶲 = 岶 [ 亷 ] [ 嘠 ] ; 

 	 	 for ( int 啃 = 0 ; 啃 < 外 ; 啃 ++ ) 
 	 	 { 
 	 	 	 岶 [ 亷 ] [ 啃 ] = 岶 [ 亷 ] [ 啃 ] / 嶲 ; 
 	 	 } 
 	 	 愿 [ 亷 ] = 愿 [ 亷 ] / 嶲 ; 

 	 	 double 伛 = 0 ; 

 	 	 for ( int 啃 = 0 ; 啃 < 墒 ; 啃 ++ ) 
 	 	 { 
 	 	 	 if ( 啃 != 亷 ) { 
 	 	 	 	 伛 = 岶 [ 啃 ] [ 嘠 ] / 岶 [ 亷 ] [ 嘠 ] ; 
 	 	 	 	 for ( int 卽 = 0 ; 卽 < 外 ; 卽 ++ ) 
 	 	 	 	 { 
 	 	 	 	 	 岶 [ 啃 ] [ 卽 ] = 岶 [ 啃 ] [ 卽 ] - 伛 * 岶 [ 亷 ] [ 卽 ] ; 
 	 	 	 	 } 
 	 	 	 	 愿 [ 啃 ] = 愿 [ 啃 ] - 伛 * 愿 [ 亷 ] ; 
 	 	 	 } 
 	 	 } 

 	 	 for ( int 啃 = 0 ; 啃 < 墒 ; 啃 ++ ) 
 	 	 { 
 	 	 	 叽 += 崶 [ 啃 ] * 愿 [ 啃 ] ; 
 	 	 } 

 	 	 double * 愎 = new double [ 外 ] ; 
for ( int 妈 = 0 ; 妈 < ( 外 * 墒 ) ; 妈 ++ ) 
 	 	 { 
	 if ( 妈 % ( 墒 ) == 0 ) 
 { 
 	 	 	 愎 [ ( 妈 / 墒 ) ] = 0 ; 
 } 
 	 	 	 
 	 	 	 	 愎 [ ( 妈 / 墒 ) ] += 崶 [ ( 妈 % 墒 ) ] * 岶 [ ( 妈 % 墒 ) ] [ ( 妈 / 墒 ) ] ; 
 	 	 	 
 	 	 } 

 	 	 for ( int 啃 = 0 ; 啃 < 外 ; 啃 ++ ) 
 	 	 { 
 	 	 	 儢 [ 啃 ] = 侔 [ 啃 ] - 愎 [ 啃 ] ; 
 	 	 } 



 	 } 

 	 double 嚮 = 0 ; 
 	 double 仳 = 0 ; 

 	 for ( int 啃 = 0 ; 啃 < 外 ; 啃 ++ ) 
 	 { 
 	 	 if ( 崶 [ 啃 ] == 侔 [ 0 ] ) { 
 	 	 	 嚮 = 愿 [ 啃 ] ; 
 	 	 } 
 	 	 if ( 崶 [ 啃 ] == 侔 [ 1 ] ) { 
 	 	 	 仳 = 愿 [ 啃 ] ; 
 	 	 } 
 	 } 

 	 std::cout << "Result: x1 = " << 嚮 << " x2 = " << 仳 << std::endl ; 

 	 for ( int 啃 = 0 ; 啃 < 墒 ; 啃 ++ ) 
 	 { 
 	 	 delete [ ] 岶 [ 啃 ] ; 
 	 } 
 	 delete [ ] 岶 ; 
 	 delete [ ] 愿 ; 
 	 delete [ ] 侔 ; 
 	 delete [ ] 崶 ; 
 	 delete [ ] 儢 ; 



 	 return 0 ; 
 } 
