#include<bits/stdc++.h>
using namespace std;
vector<int> adj[1001];
vector<int> color(1001);
vector<int> indeg(1001);
bool checkdfs(int s){
    color[s]=1;
    for(int v:adj[s]){
        if(color[v]==0){
            if(checkdfs(v)) return true;
        }
        else if(color[v]==1)return true;
    }
    color[s]=2;
    return false;
}
bool kahn(int n){
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(indeg[i]==0)q.push(i);
    }
    int cnt=0;
    while(!q.empty()){
        int v=q.front();
        q.pop();
        cnt++;
        for(int x:adj[v]){
            indeg[x]--;
            if(indeg[x]==0) q.push(x);
        }
    }
    if(cnt==n) return false;
    return true;
}
int main(){
    int n,m,mode;cin>>n>>m>>mode;
    for(int i=0;i<m;i++){
        int x,y; cin>>x>>y;
        adj[x].push_back(y);
        indeg[y]++;
    }
    if(mode==1){
        bool ok=false;
        for(int i=1;i<=n;++i){
            if(color[i]==0 && checkdfs(i)){
                ok=true;
                break;
            }
        }
        cout<<ok;
    }
    if(mode==2){
        cout<<kahn(n);
    }
}
