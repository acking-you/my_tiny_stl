#include <bits/stdc++.h>
#include "BinarySearch.h"

using namespace std;



int main() {
    BinarySearch a;
    vector<int> aa{35,24,16,78,22,15,29,70,54,31,20,90,77,24};
    for(auto&&t:aa){
        a.insert(t);
    }
    a.print();
}