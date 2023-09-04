#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
typedef vector<pair<vector<int>,double> > vvid;
typedef pair<int,double> pid;
pair<int,double> findBest(const vvid & graph,vector<pair<int,double>>& final,vector<bool>& checked,int emp);
bool compare(pair<int,double>& a,pair<int,double>& b){
    if(a.first==b.first){
        return a.second<b.second;
    }
    return b.first>a.first;
}
pair<int,double> notTake(const vvid & graph,vector<pair<int,double>>& final,vector<bool>& checked,int emp){
    if(graph[emp].first.empty()) {
        checked[emp]= true;
        final[emp]= make_pair(0,0);
        return final[emp];
    }
    pid best=make_pair(0,0);
    for(int i=0;i<graph[emp].first.size();i++){
        pid son= findBest(graph,final,checked,graph[emp].first[i]);
        best.first+= son.first;
        best.second+=son.second;
    }
    return best;

}
pair<int,double> findBest(const vvid &  graph,vector<pair<int,double>>& final,vector<bool>& checked,int emp){
    if(checked[emp]) return final[emp];
    if(graph[emp].first.empty()) {
        checked[emp]= true;
        final[emp]= make_pair(0,0);
        return final[emp];
    }
    const pid notRes=notTake(graph,final,checked,emp);
    pid best=notRes;
    for(int i=0;i<graph[emp].first.size();i++){
        int son=graph[emp].first[i];
        pid take= notTake(graph,final,checked,son);
        pid sonBest=findBest(graph,final,checked,son);
        take.first+=notRes.first- sonBest.first+1;
        take.second+=notRes.second- sonBest.second +min(graph[emp].second,graph[son].second);
        if(compare(best,take)) {
            best=take;
        }
    }
    final[emp]=best;
    checked[emp]= true;
    return best;


}

int main() {
    map<string,int> translate;
    map<string,string> company;
    int n;
    cin>>n;
    vvid graph(n+1);
    string name;
    string supervisor;
    double speed;
    translate["CEO"]=0;
    for(int i=1;i<n+1;i++){
        cin>>name>>speed>>supervisor;
        translate[name]=i;
        graph[i].second=speed;
        company[name]=supervisor;
    }
    for(auto it=company.begin();it!=company.end();it++){
        graph[translate[it->second]].first.push_back(translate[it->first]);
    }
    vector<bool> isAv(n+1,false); //value of evey subtree of graph
    vector<pair<int,double>> final(n+1);
    pair<int,double> result= findBest(graph,final,isAv,graph[0].first[0]);
    double avr=result.second/(result.first);
    cout <<result.first<<" "<< std::fixed << std::setprecision(8) << avr <<endl;
    return 0;
}
