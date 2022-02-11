#include<algorithm>
#include <iostream>
#include <vector>
using namespace std;
int eqto(int& x){
    return x;
}
void print(int x){
    cout<<x;
}
int main() {
    vector<int>d(3,1);
    vector<int>t(3);
    transform(d.begin(),d.end(),t.begin(),eqto);
    for_each(t.begin(),t.end(),print  );
    t.front();
    return 0;


}