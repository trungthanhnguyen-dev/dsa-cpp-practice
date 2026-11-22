#include <bits/stdc++.h>
using namespace std;
vector<int> adj[1001];
bool visited[1001];
vector<int> topo;
vector<int> indegree(1001);
vector<int> parent(1001);
void DFS(int s){
    visited[s]=true;
    for(int i:adj[s]){
        if(!visited[i])DFS(i);
    }
    topo.push_back(s);
}
void kahn(int n){
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int x=q.front();
        q.pop();
        cout<<x<<" ";
        for(int v:adj[x]){
            indegree[v]--;
            if(indegree[v]==0) q.push(v);
        }
    }

}
int main(){
    int n,m,mode; cin>>n>>m>>mode;
    for(int i=0;i<m;++i){
        int x,y;cin>>x>>y;
        adj[x].push_back(y);
        indegree[y]++;
    }
    if(mode==1){
    for(int i=1;i<=n;i++){
        if(!visited[i]) DFS(i);
    }
    reverse(topo.begin(),topo.end());
    for(int x:topo) cout<<x<<" ";}
    if(mode==2) kahn(n);
    
}