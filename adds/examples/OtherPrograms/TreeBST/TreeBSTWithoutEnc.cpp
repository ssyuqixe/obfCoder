#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
struct node_bst{  node_bst*parent;  node_bst*left;  node_bst*right;  double 嵀;  size_t 叽;};class bst{private:  size_t 峨;public:  node_bst*root;  bst()  {   root=nullptr;   峨=0; };  void Add(double 嵀);  node_bst*Search(double 嵀);  void Delete(node_bst*& node);  void preorder(node_bst*& node);  node_bst*find_min(node_bst*node);  void DeleteAll();};int main() {  std::ifstream in("tree.txt");  bst*tree=new bst();  double 徎=0;  if(in.is_open()){   bool 匄=1;   std::string item;   while(in>>徎)   {    tree->Add(徎);  }    in.close(); }   else{   std::cout<<"Cant open the file"<<std::endl;   return 0; }   tree->preorder(tree->root);  tree->DeleteAll();  return 0;} void bst::Add(double 嵀){  int 伅=0; bool 亀=true; int 囚;for(囚=0;囚<4;囚 ++){ 伅 +=(int) 嵀; if(伅) 亀=false;}  嵀-=7;  int 徠;for(徠=0;徠<9;徠 ++){ 嵀 ++;}  嵀-=9; 嵀+=9; 嵀-=9; 嵀+=7;  node_bst*previous=nullptr;  node_bst*p=root;  while(p){   if(p->嵀 == 嵀) return;   previous=p;  (p->嵀<嵀)?p=p->right : p=p->left; }   node_bst*new_node=new node_bst();  new_node->嵀=嵀;  new_node->left=nullptr;  new_node->right=nullptr;  new_node->叽=峨 ++;  if(! previous){   root=new_node;   return; }  (previous->嵀<嵀)?previous->right=new_node : previous->left=new_node;  new_node->parent=previous;} node_bst*bst::Search(double 嵀) {  bool 屃=0;  node_bst*p=root;  while((p) &&!屃)  {   if(p->嵀 == 嵀)   {    屃=1;  }    else if(p->嵀<嵀)     {    p=p->right;  }    else   {    p=p->left;  }  }   return p;} void bst::Delete(node_bst*& node) {  if(! node) return;  node_bst*temp=node;  if(node->parent &&(node->left||node->right)){   if(! node->left){    node->right->parent=node->parent;    if(node->parent->left == node)      node->parent->left=node->right;    else     node->parent->right=node->right;    delete temp;    峨 --;    return;  }    else if(! node->right){    node->left->parent=node->parent;    if(node->parent->left == node)      node->parent->left=node->left;    else     node->parent->right=node->left;    delete temp;    峨 --; 峨+=7; 峨 ++; 峨 ++; 峨 ++;  int 书;for(书=0;书<3;书 ++){ 峨 ++;}  峨-=3;  int 彬=0; bool 俇=true; int 丟;for(丟=0;丟<0;丟 ++){ 彬 +=(int) 峨; if(彬) 俇=false;}  峨-=9; 峨-=8; 峨+=8; 峨+=9; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 ++; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨 --; 峨+=4; 峨-=9; 峨+=9; 峨-=4; 峨-=7;    return;  }  }   else if(! node->left &&!node->right){   if(node!=root)    (node->parent->left == node)?node->parent->left=nullptr : node->parent->right=nullptr;   else    root=nullptr;   delete temp;   峨 --;   return; }   temp=find_min(node->right);  if(node && temp){   double 喺=node->嵀;   node->嵀=temp->嵀;   temp->嵀=喺;   int 埜=0; int 峝=1; int 壦;for(壦=0;壦<8;壦 ++){ 埜*=峝; switch(埜){case 0: 峝=0;break;case 1: 峝=1;break;case 3: 峝=3;break;case 7: 峝=7;break;case 10: 峝=10;break;default: 峝=14;break;}}    int 垗=0; int 呑=1; int 堲;for(堲=0;堲<5;堲 ++){ 垗*=呑; switch(垗){case 0: 呑=0;break;case 1: 呑=1;break;case 3: 呑=3;break;case 7: 呑=7;break;case 10: 呑=10;break;default: 呑=14;break;}}  喺+=5;   int 帙=0; int 岲=1; int 嬨;for(嬨=0;嬨<0;嬨 ++){ 帙*=岲; switch(帙){case 0: 岲=0;break;case 1: 岲=1;break;case 3: 岲=3;break;case 7: 岲=7;break;case 10: 岲=10;break;default: 岲=14;break;}}  喺-=5; }   Delete(temp);} node_bst*bst::find_min(node_bst*node) {  while(node->left) node=node->left;  return node;} void bst::preorder(node_bst*& node) {  if(node){   std::cout<<"("<<node->叽<<": [p: ";  (node->parent)?std::cout<<node->parent->叽 : std::cout<<"NULL";   std::cout<<", l: ";  (node->left && node->left->叽)?std::cout<<node->left->叽 : std::cout<<"NULL";   std::cout<<", r: ";  (node->right && node->right->叽)?std::cout<<node->right->叽 : std::cout<<"NULL";   std::cout<<"], data: "<<node->嵀<<" ) , "<<std::endl;   preorder(node->left);   preorder(node->right); } } void bst::DeleteAll() {  while(root &&(root->right||root->left)){   if(root->right)     Delete(root->right);   if(root->left)     Delete(root->left); }   delete root;  root=nullptr;  return;} 