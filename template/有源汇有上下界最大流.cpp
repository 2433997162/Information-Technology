#include <cstdio>
#include <cstring>
#include <fstream>
#include <queue>
#include <algorithm>
#define inf 0x7f7f7f7f
using namespace std;
const int maxn = 50004;
struct IO{
	template<typename T>
	IO & operator>>(T&res){
	 	res=0;
		bool flag=false;
		char ch;
		while((ch=getchar())>'9'||ch<'0')	flag|=ch=='-';
		while(ch>='0'&&ch<='9')	res=(res<<1)+(res<<3)+(ch^'0'),ch=getchar();
		if (flag)	res=~res+1;
		return *this;
	}
}cin;
int n,m,s,t,ss,tt,u,v,val,sum,cnt,b,c;
int M[maxn];
int head[maxn],cur[maxn],to[maxn],nxt[maxn],dep[maxn],w[maxn];
void add (int u,int v,int val)
{
	nxt[cnt]=head[u],head[u]=cnt,to[cnt]=v,w[cnt++]=val;
}
bool bfs ()
{
	queue<int> q;
	for (int i=0;i<=n+1;++i)	cur[i]=head[i],dep[i]=0;
	q.push(s),dep[s]=1;
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (int e=head[x];~e;e=nxt[e]){
			if (!dep[to[e]]&&w[e]>0){
				dep[to[e]]=dep[x]+1;
				if (to[e]==t)	return true;
				q.push(to[e]);
			}
		}
	}
	return false;
}
int dfs (int x,int dist)
{
	if (x==t)	return dist;
	for (int &e=cur[x];~e;e=nxt[e]){
		if (dep[to[e]]==dep[x]+1&&w[e]>0){
			int di=dfs(to[e],min(dist,w[e]));
			if (di){
				w[e]-=di;
				w[e^1]+=di;
				return di;
			}
		}
	}
	return 0;
}
int Dinic()
{
	int ans=0;
	while (bfs())
		while (int d=dfs(s,inf))	ans+=d;
	return ans;
}
int main()
{
	memset(head,-1,sizeof(head));
	cin>>n>>m>>ss>>tt;
	s=0,t=n+1;
	add(tt,ss,inf),add(ss,tt,0);
	for (int i=1;i<=m;++i){
		cin>>u>>v>>b>>c;
		add(u,v,c-b),add(v,u,0);
		M[u]-=b,M[v]+=b;
	}
	for (int i=1;i<=n;++i){
		if (M[i]>0)	add(s,i,M[i]),add(i,s,0),sum+=M[i];
		if (M[i]<0)	add(i,t,-M[i]),add(t,i,0);
	}
	if (Dinic()!=sum){	printf("please go home to sleep\n");return 0;}
	s=ss,t=tt;
	printf("%d\n",Dinic());
	return 0;
}
