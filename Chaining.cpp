#include "Chaining.h"
#include<iostream>

using namespace std;
vector<int> merge2(vector<int> v1,vector<int> v2){
    vector<int> res;
    int i=0,j=0,k=0;
    while (i<v1.size()&&j<v2.size())
    {
        if(v1[i]<v2[j])
        res.push_back(v1[i++]);
        else
        res.push_back(v2[j++]);
    }
    while(i<v1.size())
    res.push_back(v1[i++]);
    while(j<v2.size())
    res.push_back(v2[j++]);
    return res;
    
}
vector<int> mergeSort2(vector<int> v){
    if(v.size()<2)
    return v;
    int m=(v.size())/2;
    vector<int> v1,v2;
    for(int i=0;i<m;i++)
    v1.push_back(v[i]);
    for(int i=m;i<v.size();i++)
    v2.push_back(v[i]);
    v1=mergeSort2(v1);
    v2=mergeSort2(v2);
    return merge2(v1,v2);
}
void Chaining::createAccount(std::string id, int count) {
    Account obj;
    obj.id=id;
    obj.balance=count;
    int idx=hash(id);
    if(bankStorage2d.size()<idx+1)
    bankStorage2d.resize(idx+1);
    bankStorage2d[idx].push_back(obj);
}

std::vector<int> Chaining::getTopK(int k) {
    vector<int> vec;
    for(int i=0;i<bankStorage2d.size();i++){
       for(int j=0;j<bankStorage2d[i].size();j++)
        vec.push_back(bankStorage2d[i][j].balance);
    }
    vec=mergeSort2(vec);
    int n=vec.size();
    vector<int> v;
    if(k>databaseSize())
    k=databaseSize();
    while(k--){
        v.push_back(vec[n-1]);
        n--;
    }
    return v;
    

}

int Chaining::getBalance(std::string id) {
    int idx=hash(id);
    if(idx<0||idx>=bankStorage2d.size())
    return -1;
    if(bankStorage2d.size()<idx+1)
    return -1;
    if(bankStorage2d[idx].size()==0)
    return -1;
    for (int i = 0; i < bankStorage2d[idx].size(); i++)
        if (bankStorage2d[idx][i].id==id)
        return bankStorage2d[idx][i].balance;
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    int idx=hash(id);
    if(bankStorage2d.size()<idx+1)
    bankStorage2d.resize(idx+1);    
    for (int i = 0; i < bankStorage2d[idx].size(); i++)
        if (bankStorage2d[idx][i].id==id)
        {bankStorage2d[idx][i].balance+=count;return;}
    createAccount(id,count);
}

bool Chaining::doesExist(std::string id) {
    if(getBalance(id)==-1)
    return false;
    return true;
}

bool Chaining::deleteAccount(std::string id) {
    int idx=hash(id);
    if(bankStorage2d.size()<idx+1)
    return false;
    for (int i = 0; i < bankStorage2d[idx].size(); i++)
        if(bankStorage2d[idx][i].id==id)
       {bankStorage2d[idx].erase(bankStorage2d[idx].begin()+i);return true;}
    return false;
    

}
int Chaining::databaseSize() {
    int size=0;
    for (int i = 0; i < bankStorage2d.size(); i++)
    size+=bankStorage2d[i].size();
    return size; 
}

int Chaining::hash(std::string id) {
    int p= 23;
    long long  h=0;
    long power =1;
    int mod=100000;
    for(int i=0;i<id.length();i++)
    {
        h=(h+id[i]*power)%mod;
        power=(power*p)%mod;
    }
    return h;
}


