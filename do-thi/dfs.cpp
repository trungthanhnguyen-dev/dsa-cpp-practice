// [Bug fix]: Gọi dfs() trong main — trước đó chỉ gọi bfs() mặc dù dfs được viết đầy đủ
// [Tối ưu]: Cho phép chọn DFS hoặc BFS qua input
#include <iostream>
#include<vector>
#include <algorithm>
#include<queue>
using namespace std;

vector<int> adj[1001];
bool visited[1001];

void dfs(int s){
    cout<<s<<'\n';
    visited[s]=true;
    for(int x:adj[s]){
        if(!visited[x]) dfs(x);
    }
}

void bfs(int s){
    queue<int> q;
    q.push(s);
    visited[s]=true;
    while(!q.empty()){
        int v=q.front(); q.pop();
        cout<<v<<'\n';
        for(int x:adj[v]){
            if(!visited[x]){
                q.push(x);
                visited[x]=true;
            }
        }
    }
}

int main(){
    int n,m,s,mode;
    cin>>n>>m>>s>>mode; // mode=0: DFS, mode=1: BFS
    for(int i=0;i<m;++i){
        int x,y; cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for(int i=1;i<=n;++i) sort(adj[i].begin(),adj[i].end());
    
    if(mode==0) dfs(s);   // BUG FIX: giờ có thể gọi dfs
    else        bfs(s);
}
