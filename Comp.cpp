#include "Comp.h"
using namespace std;
vector<int> merge(vector<int> v1,vector<int> v2){
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
vector<int> mergeSort(vector<int> v){
    if(v.size()<2)
    return v;
    int m=(v.size()+1)/2;
    vector<int> v1,v2;
    for(int i=0;i<m;i++)
    v1.push_back(v[i]);
    for(int i=m;i<v.size();i++)
    v2.push_back(v[i]);
    v1=mergeSort(v1);
    v2=mergeSort(v2);
    return merge(v1,v2);
}
int hash1(std::string id) {
    int p= 19;
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
void Comp::createAccount(std::string id, int count) {
    int idx=hash(id);
    if(bankStorage1d.size()<idx+1)
    bankStorage1d.resize(idx+1,Account{"",0}); 
    else{
    int i=0;
    while(bankStorage1d[idx].id!=""&&bankStorage1d[idx].id!="deleted"){
    i++;
    idx=(idx+i*hash1(id))%100000;
    if(bankStorage1d.size()<idx+1)
    {bankStorage1d.resize(idx+1,Account{"",0});break;}
    }}
    bankStorage1d[idx].balance=count;
    bankStorage1d[idx].id=id;
}

std::vector<int> Comp::getTopK(int k) {
    vector<int> vec;
    for(int i=0;i<bankStorage1d.size();i++)
    if(bankStorage1d[i].id!=""&&bankStorage1d[i].id!="deleted")
    vec.push_back(bankStorage1d[i].balance);
    vec=mergeSort(vec);
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

int Comp::getBalance(std::string id) {
    int idx=hash(id);
    int i=0;
    if(bankStorage1d.size()<idx+1)
    return -1;
    if(bankStorage1d[idx].id==id)
    return bankStorage1d[idx].balance;
    while(bankStorage1d[idx].id!=""){
        i++;
        if(bankStorage1d[idx].id==id)
        return bankStorage1d[idx].balance;
        idx=(idx+i*hash1(id))%100000;
        if(bankStorage1d.size()<idx+1)
        break;
    }
    return -1;
}

void Comp::addTransaction(std::string id, int count) {
    if(getBalance(id)==-1)
    {createAccount(id,count);return;}
    int idx=hash(id);
    int i=0;
    while(bankStorage1d[idx].id!=""){
    if(bankStorage1d[idx].id==id)
    {bankStorage1d[idx].balance+=count;break;}
    i++;
    idx=(idx+i*hash1(id))%100000;
    }   
}

bool Comp::doesExist(std::string id) {
    if(getBalance(id)==-1)
    return false;
    return true;  
}

bool Comp::deleteAccount(std::string id) {
    if(!doesExist(id))
    return false;
    int idx=hash(id);
    int i=0;
    while(bankStorage1d[idx].id!=""){
    if(bankStorage1d[idx].id==id)
    {bankStorage1d[idx].id="deleted";return true;}
    i++;
    idx=(idx+i*hash1(id))%100000;
    }
    return true;
}
int Comp::databaseSize() {
    int cnt=0;
    for(int i=0;i<bankStorage1d.size();i++)
    if(bankStorage1d[i].id!=""&&bankStorage1d[i].id!="deleted")
    cnt++;
    return cnt;
}

int Comp::hash(std::string id) {
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