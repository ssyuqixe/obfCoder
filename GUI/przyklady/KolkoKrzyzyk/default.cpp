
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct { 
 char 匁 ; 
 char 嘗 ; 
 char 剪 [ 9 ] ; 
 char 弞 ; 

 } gameInformation ; 



void Draw ( gameInformation * memseg , char 嶨 ) { 
 system ( "clear" ) ; 
 if ( 嶨 == 0 ) 
 { 
 std::cout << "Host - krzyk" << std::endl ; 
 } 
 else
 { 
 std::cout << "User - kolko" << std::endl ; 
 } 
 for ( int 唋 = 1 ; 唋 <= 9 ; 唋 ++ ) 
 { 
 std::cout << memseg -> 剪 [ 唋 - 1 ] ; 
 if ( 唋 % 3 == 0 ) 
 { 
 std::cout << std::endl ; 
 } 
 } 

 } 


void DoMove ( gameInformation * memseg , char 嶨 ) { 
 int 嘗 = 0 ; 
 char 唌 = '0' ; 
 std::cout << "Wykonaj ruch [1-9]: " << std::endl ; 
 while ( 1 ) { 
 if ( scanf ( "%d" , & 嘗 ) == 0 ) 
 { 
 do { 
 唌 = getchar ( ) ; 
 } while ( ! isdigit ( 唌 ) ) ; 
 ungetc ( 唌 , stdin ) ; 
 } 

 if ( 嘗 >= 1 && 嘗 <= 9 && memseg -> 剪 [ 嘗 - 1 ] == '#' ) 
 { 
 break ; 
 } 
 else if ( memseg -> 剪 [ 嘗 - 1 ] != '#' ) 
 { 
 std::cout << "Wybrales zajete pole! Wybierz jeszcze raz: [1-9]" << std::endl ; 
 } 
 else
 { 
 std::cout << "Wybrales zle pole! Wybierz jeszcze raz: [1-9]" << std::endl ; 
 } 
 } 
 if ( 嶨 ) 
 { 
 
	 int 偟 = 0 ; 
	 bool 喼 = true ; 
	 int 冝 ; 
	 for ( 冝 = 0 ; 冝 < 0 ; 冝 ++ ) { 
	 偟 += ( int ) 嶨 ; 
	 if ( 偟 ) 喼 = false ; 
 } 
 
	 int 刃 ; 
	 for ( 刃 = 0 ; 刃 < 0 ; 刃 ++ ) { 
 	 嶨 ++ ; } 
	 嶨 -= 0 ; 
	 嶨 += 6 ; 
 
	 int 廤 ; 
	 for ( 廤 = 0 ; 廤 < 8 ; 廤 ++ ) { 
 	 嶨 ++ ; } 
	 嶨 -= 8 ; 
	 嶨 *= 9 ; 
	 嶨 /= 9 ; 
	 嶨 ++ ; 
	 嶨 ++ ; 
	 嶨 ++ ; 
	 嶨 ++ ; 
	 嶨 ++ ; 
	 嶨 ++ ; 
	 嶨 -- ; 
	 嶨 -- ; 
	 嶨 -- ; 
	 嶨 -- ; 
	 嶨 -- ; 
	 嶨 -- ; 
 
 	 int 乵 = 0 ; 
	 int 埒 = 1 ; 
	 int 垀 ; 
	 for ( 垀 = 0 ; 垀 < 1 ; 垀 ++ ) { 
	 乵 *= 埒 ; 
	 switch ( 乵 ) { 
 case 0: 埒 = 0 ; 
 break ; 
 case 1: 埒 = 1 ; 
 break ; 
 case 3: 埒 = 3 ; 
 break ; 
 case 7: 埒 = 7 ; 
 break ; 
 case 10: 埒 = 10 ; 
 break ; 
 default: 埒 = 14 ; 
 break ; } 
 } 
 
	 int 字 = 0 ; 
	 bool 御 = true ; 
	 int 帄 ; 
	 for ( 帄 = 0 ; 帄 < 9 ; 帄 ++ ) { 
	 字 += ( int ) 嶨 ; 
	 if ( 字 ) 御 = false ; 
 } 
	 嶨 *= 2 ; 
 
 	 int 倈 = 0 ; 
	 int 护 = 1 ; 
	 int 嵅 ; 
	 for ( 嵅 = 0 ; 嵅 < 1 ; 嵅 ++ ) { 
	 倈 *= 护 ; 
	 switch ( 倈 ) { 
 case 0: 护 = 0 ; 
 break ; 
 case 1: 护 = 1 ; 
 break ; 
 case 3: 护 = 3 ; 
 break ; 
 case 7: 护 = 7 ; 
 break ; 
 case 10: 护 = 10 ; 
 break ; 
 default: 护 = 14 ; 
 break ; } 
 } 
	 嶨 /= 2 ; 
	 嶨 -= 6 ; 
 memseg -> 剪 [ 嘗 - 1 ] = 'O' ; 
 memseg -> 嘗 = 0 ; 
 } 
 else
 { 
 memseg -> 剪 [ 嘗 - 1 ] = 'X' ; 
 memseg -> 嘗 = 1 ; 
 } 
 Draw ( memseg , 嶨 ) ; 

 std::cout << "Trwa ruch przeciwnika..." << std::endl ; 
 } 

void WaitForMove ( gameInformation * memseg , char 嶨 ) { 
 while ( memseg -> 嘗 != 嶨 ) 
 { 
 Sleep ( 1 ) ; 
 } 
 Draw ( memseg , 嶨 ) ; 
 } 

void checkEnd ( gameInformation * memseg ) { 
 char 愍 = '#' ; 
	 愍 -= 6 ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
 
	 int 扫 ; 
	 for ( 扫 = 0 ; 扫 < 8 ; 扫 ++ ) { 
 	 愍 ++ ; } 
	 愍 -= 8 ; 
 
 	 int 偖 = 0 ; 
	 int 抏 = 1 ; 
	 int 惦 ; 
	 for ( 惦 = 0 ; 惦 < 8 ; 惦 ++ ) { 
	 偖 *= 抏 ; 
	 switch ( 偖 ) { 
 case 0: 抏 = 0 ; 
 break ; 
 case 1: 抏 = 1 ; 
 break ; 
 case 3: 抏 = 3 ; 
 break ; 
 case 7: 抏 = 7 ; 
 break ; 
 case 10: 抏 = 10 ; 
 break ; 
 default: 抏 = 14 ; 
 break ; } 
 } 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
 
	 int 伎 ; 
	 for ( 伎 = 0 ; 伎 < 2 ; 伎 ++ ) { 
 	 愍 ++ ; } 
	 愍 -= 2 ; 
 
 	 int 乼 = 0 ; 
	 int 愲 = 1 ; 
	 int 拽 ; 
	 for ( 拽 = 0 ; 拽 < 6 ; 拽 ++ ) { 
	 乼 *= 愲 ; 
	 switch ( 乼 ) { 
 case 0: 愲 = 0 ; 
 break ; 
 case 1: 愲 = 1 ; 
 break ; 
 case 3: 愲 = 3 ; 
 break ; 
 case 7: 愲 = 7 ; 
 break ; 
 case 10: 愲 = 10 ; 
 break ; 
 default: 愲 = 14 ; 
 break ; } 
 } 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 += 2 ; 
	 愍 *= 2 ; 
 
	 int 刈 = 0 ; 
	 bool 娖 = true ; 
	 int 怏 ; 
	 for ( 怏 = 0 ; 怏 < 3 ; 怏 ++ ) { 
	 刈 += ( int ) 愍 ; 
	 if ( 刈 ) 娖 = false ; 
 } 
	 愍 /= 2 ; 
	 愍 -= 2 ; 
	 愍 += 6 ; 
 if ( memseg -> 剪 [ 0 ] != '#' ) 
 { 
 if ( ( memseg -> 剪 [ 0 ] == memseg -> 剪 [ 1 ] ) && ( memseg -> 剪 [ 1 ] == memseg -> 剪 [ 2 ] ) ) 
 { 
 愍 = memseg -> 剪 [ 0 ] ; 
 } 
 else if ( ( memseg -> 剪 [ 0 ] == memseg -> 剪 [ 4 ] ) && ( memseg -> 剪 [ 4 ] == memseg -> 剪 [ 8 ] ) ) 
 { 
 愍 = memseg -> 剪 [ 0 ] ; 
 } 
 else if ( ( memseg -> 剪 [ 0 ] == memseg -> 剪 [ 3 ] ) && ( memseg -> 剪 [ 3 ] == memseg -> 剪 [ 6 ] ) ) 
 { 
 愍 = memseg -> 剪 [ 0 ] ; 
 } 
 } 

 if ( memseg -> 剪 [ 1 ] != '#' && ( memseg -> 剪 [ 1 ] == memseg -> 剪 [ 4 ] ) && ( memseg -> 剪 [ 4 ] == memseg -> 剪 [ 7 ] ) ) 
 { 
 愍 = memseg -> 剪 [ 1 ] ; 
 } 


 if ( memseg -> 剪 [ 2 ] != '#' ) 
 { 
 if ( ( memseg -> 剪 [ 2 ] == memseg -> 剪 [ 5 ] ) && ( memseg -> 剪 [ 5 ] == memseg -> 剪 [ 8 ] ) ) 
 { 
 愍 = memseg -> 剪 [ 2 ] ; 
 } 
 else if ( ( memseg -> 剪 [ 2 ] == memseg -> 剪 [ 4 ] ) && ( memseg -> 剪 [ 4 ] == memseg -> 剪 [ 6 ] ) ) 
 { 
 愍 = memseg -> 剪 [ 2 ] ; 
 } 

 } 

 if ( memseg -> 剪 [ 3 ] != '#' && ( memseg -> 剪 [ 3 ] == memseg -> 剪 [ 4 ] ) && ( memseg -> 剪 [ 4 ] == memseg -> 剪 [ 5 ] ) ) 
 { 
 愍 = memseg -> 剪 [ 3 ] ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 ++ ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 -- ; 
	 愍 += 4 ; 
 
	 int 宨 = 0 ; 
	 bool 媀 = true ; 
	 int 啾 ; 
	 for ( 啾 = 0 ; 啾 < 8 ; 啾 ++ ) { 
	 宨 += ( int ) 愍 ; 
	 if ( 宨 ) 媀 = false ; 
 } 
 
	 int 侦 = 0 ; 
	 bool 徶 = true ; 
	 int 尝 ; 
	 for ( 尝 = 0 ; 尝 < 9 ; 尝 ++ ) { 
	 侦 += ( int ) 愍 ; 
	 if ( 侦 ) 徶 = false ; 
 } 
 
 	 int 宎 = 0 ; 
	 int 勺 = 1 ; 
	 int 剭 ; 
	 for ( 剭 = 0 ; 剭 < 3 ; 剭 ++ ) { 
	 宎 *= 勺 ; 
	 switch ( 宎 ) { 
 case 0: 勺 = 0 ; 
 break ; 
 case 1: 勺 = 1 ; 
 break ; 
 case 3: 勺 = 3 ; 
 break ; 
 case 7: 勺 = 7 ; 
 break ; 
 case 10: 勺 = 10 ; 
 break ; 
 default: 勺 = 14 ; 
 break ; } 
 } 
	 愍 -= 4 ; 
 } 

 if ( memseg -> 剪 [ 6 ] != '#' && ( memseg -> 剪 [ 6 ] == memseg -> 剪 [ 7 ] ) && ( memseg -> 剪 [ 7 ] == memseg -> 剪 [ 8 ] ) ) 
 { 
 愍 = memseg -> 剪 [ 6 ] ; 
 } 
 if ( 愍 != '#' ) { 
 if ( 愍 == 'X' ) 
 { 
 memseg -> 匁 = 1 ; 
 } 
 else
 { 
 memseg -> 匁 = 2 ; 
 } 
 } 


 } 



int main ( int 匠 , wchar_t ** 啝 ) { 
 if ( 匠 != 2 ) 
 { 
 if ( 匠 > 2 ) 
 { 
 std::cout << strerror ( errno ) << " uzyto za duzo argumentow" << std::endl ; 
 } 
 std::cout << strerror ( errno ) << " uzyj " << * 啝 [ 0 ] << " < nazwa pliku> \n np. " << * 啝 [ 0 ] << " abc123" << std::endl ; 
 return 1 ; 
 } 

 HANDLE MapFile ; 

 char 嶨 = 1 ; 
 MapFile = OpenFileMapping ( FILE_MAP_ALL_ACCESS , FALSE , 啝 [ 1 ] ) ; 
 if ( MapFile == NULL ) 
 { 
 MapFile = CreateFileMapping ( INVALID_HANDLE_VALUE , NULL , PAGE_READWRITE , 0 , sizeof ( gameInformation ) , 啝 [ 1 ] ) ; 
 嶨 = 0 ; 
 if ( MapFile == NULL ) 
 { 
 std::cout << strerror ( errno ) << "Could not create file mapping object" << std::endl ; 
 return 2 ; 
 } 
 } 

 gameInformation * memseg = ( gameInformation * ) MapViewOfFile ( MapFile , FILE_MAP_ALL_ACCESS , 0 , 0 , sizeof ( gameInformation ) ) ; 

 if ( memseg == NULL ) 
 { 
 std::cout << strerror ( errno ) << "Could not map view of file" << std::endl ; 
 CloseHandle ( MapFile ) ; 
 return 3 ; 
 } 

 

 if ( ! 嶨 ) 
 { 
 memseg -> 匁 = 0 ; 
 memseg -> 嘗 = 0 ; 
 memseg -> 剪 [ 9 ] ; 
 memseg -> 弞 = 0 ; 
 for ( int 唋 = 0 ; 唋 < 9 ; 唋 ++ ) 
 { 
 memseg -> 剪 [ 唋 ] = '#' ; 
 } 

 } 
 else
 { 
 Draw ( memseg , 嶨 ) ; 
 } 


 while ( memseg -> 匁 == 0 && memseg -> 弞 < 9 ) 
 { 
 if ( 嶨 == memseg -> 嘗 ) 
 { 
 Draw ( memseg , 嶨 ) ; 
 DoMove ( memseg , 嶨 ) ; 
 memseg -> 弞 ++ ; 
 checkEnd ( memseg ) ; 
 } 
 else
 WaitForMove ( memseg , 嶨 ) ; 
 } 
 if ( memseg -> 匁 == 0 && memseg -> 弞 == 9 ) 
 { 
 std::cout << "Remis!" << std::endl ; 
 } 
 else
 { 
 if ( memseg -> 匁 == 嶨 + 1 ) 
 { 
 std::cout << "Wygrales!" << std::endl ; 
 } 
 else
 { 
 std::cout << "Przegrales!" << std::endl ; 
 } 
 } 


 if ( ! UnmapViewOfFile ( memseg ) ) 
 { 
 std::cout << strerror ( errno ) << "Could not unmap view of file" << std::endl ; 
 CloseHandle ( MapFile ) ; 
 return 4 ; 
 } 
 CloseHandle ( MapFile ) ; 
 return 0 ; 
 } 
