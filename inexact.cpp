#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <ctime>
#include <set>
using namespace std;

ifstream fin ("large2.txt");
ofstream fout("large2f_answer.txt");
int l;
vector<int> darim;
int n;
int tavizi=10;
int tahlil=2000;
int rst=300;
//int crs=200;
int prm=50;
int nokhbe=30;
map<int,bool> mp;

class cluase{
  public:
  vector<int> lits;
  cluase(vector<int> q){
    lits=q;
  }
};
bool edame;



bool is_true(cluase c,vector <bool> q){
int maj=0;
  for(int i=0;i<c.lits.size();i++)
    //  cerr<<c.lits[i]<<' ';
      maj+=q[c.lits[i]];
  return ((maj%2)==0);
}
vector<cluase> input;
int fitness(vector<bool> q){
//  cerr<<"h"<<endl;
  int ted=0;

  for(int i=0;i<q.size();i++)
    ted+=q[i];
  if(ted==0)
    return -1000000;
  int ans=0;
  for(int i=0;i<input.size();i++){
      ans+=is_true(input[i],q)*1000;
   //   cerr<<i<<endl;
  }
    ans-=ted;
  return ans;
}
bool operator<(vector<bool> a,vector<bool> b){
  for(int i=0;i<a.size();i++)
      if(a[i]!=b[i])
        return a[i]<b[i];
  return false;
}
class instance{
  public:
    vector<bool> sat;
    int fit;
    instance(vector<bool> x,int meghdar){
      sat=x;
      fit=meghdar;
    }
    void print(){
      fout<<"fitness  ="<<fit<<endl;
      for(int i=1;i<=l;i++)
          fout<<sat[i];
      fout<<endl;
    }
    instance(){
      sat.clear();
      fit=0;
    }

};
bool operator<(instance a,instance b){
  if(a.fit!=b.fit)
    return (a.fit>b.fit);
  return (a.sat<b.sat);
}
int read(){
  stringstream g;
    string s;
    int ted=0;
    int mot=0;
  fin>>n;
  getline(fin,s);
  for(int i=1;i<=n;i++){
   g.clear();
   s.clear();
    getline(fin,s);
    g<<s;
    vector<int> h;
    h.clear();
    int x;
    while(g>>x){
      h.push_back(x);
      if(x!=0){
        ted=max(ted,x);
        if(!mp[x]){
          mot++;
          mp[x]=true;
        }
        //cerr<<x<<endl;

        darim.push_back(x);
      }
    }
   // h.pop_back();
   // for(int j=0;j<h.size();j++)
    //  cerr<<h[j]<<' ';
   // cerr<<endl;
    input.push_back(cluase(h));
  }
  cerr<<n<<endl<<ted<<endl;
  return ted;
}
set<instance> population;
void make_in(int t){
  vector<bool> m;
  for(int i=1;i<=t;i++){
    m.clear();
    m.push_back(false);
    for(int j=0;j<l;j++){
      //  int ra=rand()%5+2;
     //   int md=rand()%2;
        m.push_back((bool)((rand()%(l/5)==1)));
    }
   /* for(int i=0;i<m.size();i++)
      cerr<<m[i];*/
  //  cerr<<endl;
  int f=fitness(m);
 // cerr<<f<<endl;
    population.insert(instance(m,f));
  }
  return;
}
void crossover(){
  int ted=population.size();
  set<instance>::iterator it=population.begin();
  int coun=0;
  vector<bool> e1;
  while(coun<nokhbe){
    instance f1=*it;
    e1.clear();
    e1=f1.sat;
    int x=f1.fit;
    bool made=false;
    for(int i=1;i<=l;i++)
        if(e1[i]==0){
        e1[i]=1-e1[i];
        int u=fitness(e1);
        if(u>=max(x-tahlil,0)){
          population.insert(instance(e1,u));
          edame=true;
          coun++;
        }
        e1[i]=1-e1[i];
    }
    coun++;
    if(x<(n-1)*1000){
      set<instance>::iterator it2=it;
  //
      it++;
      population.erase(it2);
    }
  }
 // population.erase(f1);
 // population.erase(f2);
 // make_in(tavizi);
  while(population.size()>nokhbe){
    set<instance>::reverse_iterator it2=population.rbegin();
    population.erase(*it2);
  }

 // make_in(tavizi);
  while(population.size()<nokhbe)
    make_in(tavizi);
  return;
}
int main(){
  srand(time(NULL));
  l=read();
  int ans=0;
  instance nahayi;
  for(int j=0;j<rst;j++){
      population.clear();
 // cerr<<l<<endl;
    make_in(prm);
    for(long i=0;i<l*3/4;i++){
      edame=false;
      crossover();
      if(!edame)
          break;
      set<instance>::iterator it=population.begin();
      instance f1=*it;
      if(f1.fit>ans){
        ans=f1.fit;
        cerr<<"tedad e satrha e erza shode="<<(ans/1000)+1<<" az beyn e "<<n<<" satr ba estefade az "<<1000-ans%1000<<" az beyn e "<<l<<" motoghayer"<<endl;
      //  cerr<<ans<<endl;
        nahayi=f1;
        nahayi.print();
    /*  if(ans>=2722)
        break;*/
      }
    }
  }
  nahayi.print();
 /* sort(darim.begin(),darim.end());
  for(int i=0;i<darim.size();i++)
      cerr<<darim[i]<<' ';
  cerr<<endl;*/

  return 0;
}
