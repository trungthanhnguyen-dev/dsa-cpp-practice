#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
bool visited[maxn];
vector<int> adj1[maxn];
vector<int> adj2[maxn];
stack<int> st;
void DFS1(int s){
    visited[s]=true;
    for(int i=0;i<adj1[s].size();++i){
        int v=adj1[s][i];
        if(!visited[v]) DFS1(v);
    }
    st.push(s);
}
void DFS2(int s){
    visited[s]=true;
    for(int i=0;i<adj2[s].size();++i){
        int v=adj2[s][i];
        if(!visited[v]) DFS2(v);
    }
}
int main()
{
    int n,m;cin>>n>>m;
    for(int i=0;i<m;++i){
        int x,y;cin>>x>>y;
        adj1[x].push_back(y);
        adj2[y].push_back(x);
    }
    for(int i=1;i<=n;++i){
        if(!visited[i]) DFS1(i);
    }
    memset(visited,false,sizeof(visited));
    int SCC=0;
    while (!st.empty()) {
    int u = st.top();
    st.pop();
    if(!visited[u]){
        DFS2(u);
        SCC++;
    }
}
    cout<<SCC;

}