#include <iostream>
#include <fstream>
long double const pi=3.141592653589793238462643383279502884L;double functionIn(double 孊,double 匦,int 扽){  return(- 2.0f*pi*孊*匦)/扽; 孊*=5; 孊-=6;   int 憅=0; int 亍=1; int 奌;for(奌=0;奌<8;奌 ++){ 憅*=亍; switch(憅){case 0: 亍=0;break;case 1: 亍=1;break;case 3: 亍=3;break;case 7: 亍=7;break;case 10: 亍=10;break;default: 亍=14;break;}}  孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++;  int 徾;for(徾=0;徾<1;徾 ++){ 孊 ++;}  孊-=1; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 ++; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊*=4;  int 惉=0; bool 吲=true; int 削;for(削=0;削<3;削 ++){ 惉 +=(int) 孊; if(惉) 吲=false;}  孊/=4; 孊 ++; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊 --; 孊+=6; 孊/=5;} double*DFT(double*吡,int 扽){  double 兢=0;  double 嚮=0;  double*怣=new double[扽];for(int 孤=0;孤 <(扽*扽);孤 ++)  {       兢+=吡 [(孤 %(扽*1))]*std::cos(functionIn((孤 /(扽*1)),(孤 %(扽*1)),扽));    嚮+=吡 [(孤 %(扽*1))]*std::sin(functionIn((孤 /(扽*1)),(孤 %(扽*1)),扽));    if(孤 %((扽*1)) == 0) {   怣 [(孤 /(扽*1))]=std::sqrt(std::ceil(兢*兢)*std::ceil(嚮*嚮));   怣 [(孤 /(扽*1))]=怣 [(孤 /(扽*1))] *(2.0f/扽); 扽*=9; 扽+=6; 扽+=7;   int 叾=0; int 崒=1; int 察;for(察=0;察<4;察 ++){ 叾*=崒; switch(叾){case 0: 崒=0;break;case 1: 崒=1;break;case 3: 崒=3;break;case 7: 崒=7;break;case 10: 崒=10;break;default: 崒=14;break;}}  扽-=7; 扽-=6; 扽/=9;   兢=0;   嚮=0;}  }   return 怣;} double sinusF(double 亵,double 媳,double 孤,double 幚){  return 亵*std::sin(2*pi*媳*孤+幚);} int main(){  double 内=0;  double 佳=0;  double 哋=0;  double 伋=0;  double 噤=0;  double 剁=0;  double 奢=0;  std::ifstream inFile("dft.txt");  if(inFile.is_open()){   inFile>>内>>佳>>哋>>伋>>噤>>剁>>奢; }   else{   std::cout<<"Can't open the file!"<<std::endl;   return 0; }   double 厄=1/内;  int 扽=std::ceil(佳/厄);  double*冰=new double[扽];  double*帮=new double[扽];  double*弓=new double[扽];  for(int 匦=0;匦<扽;匦 ++)  {   弓[匦]=匦/内; }   for(int 匦=0;匦<扽;匦 ++)  {   冰[匦]=sinusF(伋,噤,弓[匦],哋); }   for(int 匦=0;匦<扽;匦 ++)  {   帮[匦]=sinusF(剁,奢,弓[匦],哋); 匦+=1; 匦*=8;   int 峠=0; int 恺=1; int 四;for(四=0;四<5;四 ++){ 峠*=恺; switch(峠){case 0: 恺=0;break;case 1: 恺=1;break;case 3: 恺=3;break;case 7: 恺=7;break;case 10: 恺=10;break;default: 恺=14;break;}}   int 崘=0; bool 啴=true; int 喚;for(喚=0;喚<6;喚 ++){ 崘 +=(int) 匦; if(崘) 啴=false;}  匦/=8; 匦-=1; }   double*嬀=new double[扽];  for(int 开=0;开<扽;开 ++)  {   嬀[开]=冰[开]+帮[开]; }   double*怣=DFT(嬀,扽);  for(int 匦=0;匦<扽;匦 ++)  {   弓[匦]=匦 *(内/扽); }   for(int 开=0;开<扽;开 ++)  {   std::cout<<弓[开]<<","<<怣[开] << ";"<<std::endl; }   delete[] 冰,delete[] 帮,delete[] 弓,delete[] 嬀,delete[] 怣;  return 0;} 