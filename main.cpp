#include <iostream>
#include "Trie_static.h"
using namespace std;
int main(){
  Trie_static a;
  a.insert("dream");
  if(a.search("drea"))
      cout<<"true";
  else
      cout<<"false";
}