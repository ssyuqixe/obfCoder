


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


int main( )
{
 	 int 僧 = 0 ; 
 	 int 侘 = 0 ; 
 	 double ** 垎 ; 
 	 double * 壴 ; 
 	 bool 弚 = 1 ; 

 	 std::ifstream in( "matrix.txt" ) ; 
 	 if ( in . is_open( ) ) {
 	 	 bool 侢 = 1 ; 
 	 	 std::string item ; 
 	 	 int 伫 = 0 ; 
 	 	 int 国 = 0 ; 

 	 	 in >> 僧 >> 侘 ; 

 	 	 垎 = new double * [ 僧 ] ; 
 	 	 for ( int 伫 = 0 ; 伫 < 侘 ; 伫 ++ )
 	 	 {
 	 	 	 垎 [ 伫 ] = new double [ 侘 ] ; 
 	 	 }

 	 	 for ( int 伫 = 0 ; 伫 < 僧 ; 伫 ++ )
 	 	 {
 	 	 	 for ( int 国 = 0 ; 国 < 侘 ; 国 ++ )
 	 	 	 {
 	 	 	 	 in >> 垎 [ 伫 ] [ 国 ] ; 
 	 	 	 }
 	 	 }
 	 	 壴 = new double [ 僧 ] ; 

 	 	 for ( int 伫 = 0 ; 伫 < 僧 ; 伫 ++ )
 	 	 {
 	 	 	 in >> 壴 [ 伫 ] ; 
 	 	 }



 	 	 in . close( ) ; 
 	 }
 	 else {
 	 	 std::cout << "Cant open the file!" << std::endl ; 
 	 	 return 0 ; 
 	 }

 	 
 	 for ( int 峡 = 0 ; 峡 < 僧 ; 峡 ++ ) 
 	 {
 	 	 for ( int 吙 = 峡 + 1 ; 吙 < 僧 ; 吙 ++ ) 
 	 	 {
 	 	 	 if ( std::abs( 垎 [ 峡 ] [ 峡 ] ) < std::abs( 垎 [ 吙 ] [ 峡 ] ) ) {
 	 	 	 	 for ( int 伫 = 0 ; 伫 < 侘 ; 伫 ++ ) 
 	 	 	 	 {
 	 	 	 	 	 std::swap( 垎 [ 峡 ] [ 伫 ] , 垎 [ 吙 ] [ 伫 ] ) ; 
 	 	 	 	 }
 	 	 	 	 std::swap( 壴 [ 峡 ] , 壴 [ 吙 ] ) ; 

 	 	 	 }

 	 	 }

 	 }

 	 for ( int 伫 = 0 ; 伫 < 僧 - 1 ; 伫 ++ )
 	 {
 	 	 for ( int 国 = 0 ; 国 < 侘 - 1 ; 国 ++ )
 	 	 {
 	 	 	 if ( ! ( ( 垎 [ 伫 ] [ 国 ] / 垎 [ 伫 + 1 ] [ 国 ] ) == ( 壴 [ 伫 ] / 壴 [ 伫 + 1 ] ) ) ) 
 	 	 	 { 
 	 	 	 	 弚 = 0 ; 
 	 	 	 	 break ; 

 	 	 	 }
 	 	 }
 	 }


 	 
 	 double 匥 = 0 ; 
 	 if ( ! 弚 ) 
 	 {
 	 	 for ( int 伫 = 0 ; 伫 < 僧 ; 伫 ++ )
 	 	 {
 	 	 	 for ( int 国 = 伫 + 1 ; 国 < 僧 ; 国 ++ )
 	 	 	 {
 	 	 	 	 匥 = 垎 [ 国 ] [ 伫 ] / 垎 [ 伫 ] [ 伫 ] ; 
 	 	 	 	 for ( int 峡 = 0 ; 峡 < 侘 ; 峡 ++ ){
 	 	 	 	 	 垎 [ 国 ] [ 峡 ] = 垎 [ 国 ] [ 峡 ] - 匥 * 垎 [ 伫 ] [ 峡 ] ; 
 	 	 	 	 }
 	 	 	 	 壴 [ 国 ] -= 匥 * 壴 [ 伫 ] ; 
 	 	 	 }
 	 	 }


 	 	 for ( int 伫 = 0 ; 伫 < 僧 - 1 ; 伫 ++ )
 	 	 {
 	 	 	 for ( int 国 = 伫 + 1 ; 国 < 僧 ; 国 ++ )
 	 	 	 {
 	 	 	 	 垎 [ 国 ] [ 伫 ] = 0 ; 
 	 	 	 }
 	 	 }


 	 	 

 	 	 for ( int 伫 = ( 僧 > 侘 ) ? 侘 - 1 : 僧 - 1 ; 伫 >= 0 ; 伫 -- ) 
 	 	 {
 	 	 	 for ( int 国 = 伫 + 1 ; 国 < 侘 ; 国 ++ )
 	 	 	 {
 	 	 	 	 if ( 国 != 伫 )
 	 	 	 	 {
 	 	 	 	 	 壴 [ 伫 ] = 壴 [ 伫 ] - 垎 [ 伫 ] [ 国 ] * 壴 [ ( ( 僧 >= 侘 ) ? 国 : 国 - ( 僧 - 僧 ) ) ] ; 
 	 	 	 	 }

 	 	 	 }

 	 	 	 if ( 垎 [ 伫 ] [ 伫 ] == 0 )
 	 	 	 {
 	 	 	 	 return 1 ; 
 	 	 	 }
 	 	 	 else
 	 	 	 {
 	 	 	 	 壴 [ 伫 ] = 壴 [ 伫 ] / 垎 [ 伫 ] [ 伫 ] ; 
 	 	 	 }

 	 	 }
 	 }

 	 std::cout << "Result: " ; 
 	 for ( int 伫 = 0 ; 伫 < 僧 ; 伫 ++ )
 	 {
 	 	 std::cout << 壴 [ 伫 ] << " " ; 
 	 }
 	 std::cout << std::endl ; 


 	 for ( int 伫 = 0 ; 伫 < 侘 ; 伫 ++ )
 	 {
 	 	 delete [ ] 垎 [ 伫 ] ; 
 	 }
 	 delete [ ] 垎 ; 

 	 delete [ ] 壴 ; 


 	 return 0 ; 
}



