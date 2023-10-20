#include "CubicProbing.h"
using namespace std;
vector<int> merge13(vector<int> v1,vector<int> v2){
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
vector<int> mergeSort13(vector<int> v){
    if(v.size()<2)
    return v;
    int m=(v.size())/2;
    vector<int> v1,v2;
    for(int i=0;i<m;i++)
    v1.push_back(v[i]);
    for(int i=m;i<v.size();i++)
    v2.push_back(v[i]);
    v1=mergeSort13(v1);
    v2=mergeSort13(v2);
    return merge13(v1,v2);
}

void CubicProbing::createAccount(std::string id, int count) {
    int idx=hash(id);
    if(bankStorage1d.size()<idx+1)
    bankStorage1d.resize(idx+1,Account{"",0}); 
    else{
    int k=1;
    while(bankStorage1d[idx].id!=""&&bankStorage1d[idx].id!="deleted"){
    idx=(idx+(k*k*k))%100000;k++;
    if(bankStorage1d.size()<idx+1)
    {bankStorage1d.resize(idx+1,Account{"",0});break;}
    }}
    bankStorage1d[idx].balance=count;
    bankStorage1d[idx].id=id;
}

std::vector<int> CubicProbing::getTopK(int k) {
    vector<int> vec;
    for(int i=0;i<bankStorage1d.size();i++)
    if(bankStorage1d[i].id!=""&&bankStorage1d[i].id!="deleted")
    vec.push_back(bankStorage1d[i].balance);
    vec=mergeSort13(vec);
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

int CubicProbing::getBalance(std::string id) {
    int idx=hash(id);
    int k=1;
    if(bankStorage1d.size()<idx+1)
    return -1;
    while(bankStorage1d[idx].id!=""){
        if(bankStorage1d[idx].id==id)
        return bankStorage1d[idx].balance;
        idx=(idx+(k*k*k))%100000;k++;
    }
    return -1;
}

void CubicProbing::addTransaction(std::string id, int count) {
    if(getBalance(id)==-1)
    {createAccount(id,count);return;}
    int idx=hash(id);
    int k=1;
    while(bankStorage1d[idx].id!=""){
    if(bankStorage1d[idx].id==id)
    {bankStorage1d[idx].balance+=count;break;}
    idx=(idx+(k*k*k))%100000;k++;
    }   
}

bool CubicProbing::doesExist(std::string id) {
    if(getBalance(id)==-1)
    return false;
    return true;  
}

bool CubicProbing::deleteAccount(std::string id) {
    if(!doesExist(id))
    return false;
    int idx=hash(id);
    int k=1;
    while(bankStorage1d[idx].id!=""){
    if(bankStorage1d[idx].id==id)
    {bankStorage1d[idx].id="deleted";return true;}
    idx=(idx+(k*k*k))%100000;k++;
    }
    return true;
}
int CubicProbing::databaseSize() {
    int cnt=0;
    for(int i=0;i<bankStorage1d.size();i++)
    if(bankStorage1d[i].id!=""&&bankStorage1d[i].id!="deleted")
    cnt++;
    return cnt;
}

int CubicProbing::hash(std::string id) {
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

