#include<bits/stdc++.h>
using namespace std;
bool visited[1001];
vector<int> adj[1001];
vector<int> parent(1001);
bool checkdfs(int s, int par){
    visited[s]=true;
    for(int v:adj[s]){
        if(!visited[v]){
            if(checkdfs(v,s)) return true;
        }
        else if(v!=par) return true;
    }
    return false;
}
bool checkbfs(int s){
    queue<int> q;
    q.push(s);
    visited[s]=true;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int v:adj[x]){
            if(!visited[v]){
                q.push(v);
                visited[v]=true;
                parent[v]=x;
            }
            else if(v!=parent[x]) return true;
        }
    }
    return false;
}
int main(){
    int n,m,mode; cin>>n>>m>>mode;
    for(int i=0;i<m;++i){
        int x,y;cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    if(mode==3){
        bool ok=false;
        for(int i=1;i<=n;++i){
            if(!visited[i] && checkdfs(i,0)){
                ok=true;
                break;
            }
        }
        cout<<ok;
    }
    if(mode==4){
        bool ok=false;
        for(int i=1;i<=n;++i){
            if(!visited[i] && checkbfs(i)){
                ok=true;
                break;
            }
        }
        cout<<ok;
    }
}
