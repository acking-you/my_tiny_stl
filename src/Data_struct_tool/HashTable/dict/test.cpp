//
// Created by Alone on 2022-6-28.
//
#include<unordered_map>
#include<vector>
#include "../cpp_version/unordered_map.hpp"
#include "Timer.h"

#define MY
class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        UnorderedMap<int,int> s;
        for (int x: nums) {
            if (s.Exist(x)) {
                return true;
            }
            s.Insert({x,0});
        }
        return false;
    }
};

int main(){
    Timer t;
    freopen("./a.txt","w",stdout);
#ifdef MY
    UnorderedMap<std::string ,int >cnt;

    for(int i=1;i<100000;i++){
        cnt[std::to_string(i)]++;
    }
    auto iter = cnt.Iterator();
    while(iter.hasNext()){
        auto p = iter.next();
        std::cout<<"k:"<<p.first<<" v:"<<p.second<<"\n";
    }
#else
    std::unordered_map<std::string,int>cnt;
    for(int i=1;i<10000000;i++){
        cnt[std::to_string(i)]++;
    }
#endif

}