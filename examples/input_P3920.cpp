#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
using ll=long long;
const int maxn=200010;
int n,fa[maxn],siz[maxn],son[maxn],vis[maxn],Dep[maxn],Fa[maxn][20];
int sw[maxn],S,R,mn,dep[maxn],dp1[maxn],r[maxn],Dis[maxn];
struct edge{int v,w;};
vector<edge> v[maxn];
ll now;
template<class T>struct Splay:tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>{
	int qry(int x){return this->order_of_key(T{x,n+1});}
	void Clear(){Splay<T> x;this->swap(x);}
};
Splay<pair<int,int>> tr[maxn],t1[maxn];
void getrt(int p,int fa){
	siz[p]=1;int mx=-1;
	for(edge&e:v[p])if(e.v!=fa&&!vis[e.v])
		dep[e.v]=dep[p]+e.w,getrt(e.v,p),
		siz[p]+=siz[e.v],mx=max(mx,siz[e.v]);
	mx=max(mx,S-siz[p]);
	if(mx<mn)mn=mx,R=p;
}
void dfs(int p,int fa){
	siz[p]=1;tr[R].insert({dp1[p]-r[p],p}),t1[R].insert({dep[p]-r[p],p});
	for(edge&e:v[p])if(e.v!=fa&&!vis[e.v])
		dp1[e.v]=dp1[p]+e.w,dfs(e.v,p),siz[p]+=siz[e.v];
}
int rebuild(int p){
	S=siz[p],mn=1e9,dep[son[p]]=sw[p];
	getrt(son[p],0);
	son[R]=son[p];sw[R]=sw[p];fa[R]=fa[p];
	tr[R].Clear(),t1[R].Clear();
	dp1[R]=0;dfs(R,0);vis[R]=1;
	int t=R;
	for(edge&e:v[t])if(!vis[e.v])
		son[e.v]=e.v,sw[e.v]=e.w,
		fa[e.v]=t,rebuild(e.v);
	vis[t]=0;return t;
}
int dis(int u,int v){
	int ans=Dis[u]+Dis[v];
	if(Dep[u]<Dep[v])swap(u,v);
	for(int k=19;~k;k--)if(Dep[Fa[u][k]]>=Dep[v])u=Fa[u][k];
	if(u==v)return ans-2*Dis[u];
	for(int k=19;~k;k--)if(Fa[u][k]!=Fa[v][k])
		u=Fa[u][k],v=Fa[v][k];
	return ans-2*Dis[*Fa[u]];
}
int main(){
	scanf("%*d%d",&n);
	for(int i=1;i<=n;i++){
		int a,c;scanf("%d%d%d",&a,&c,r+i);
		a^=now%(int)1e9;
		fa[i]=*Fa[i]=a;siz[i]=1;Dis[i]=Dis[a]+c;son[i]=i;sw[i]=c;
		if(!c){tr[i].insert({-r[i],i});puts("0");continue;}
		v[a].push_back({i,c});v[i].push_back({a,c});Dep[i]=Dep[a]+1;
		for(int k=1;k<20;k++)Fa[i][k]=Fa[Fa[i][k-1]][k-1];
		for(int x=i;fa[x];x=fa[x]){
			now+=tr[fa[x]].qry(r[i]-dis(fa[x],i))-t1[x].qry(r[i]-dis(fa[x],i));
			siz[fa[x]]++;
		}
		for(int x=i;fa[x];)
			if(siz[x]>0.75*siz[fa[x]]){
				for(int y=fa[fa[x]];y;y=fa[y])vis[y]=1;
				x=rebuild(fa[x]);
				for(int y=fa[x];y;y=fa[y])vis[y]=0;
			}else x=fa[x];
		for(int x=i;x;x=fa[x])
			tr[x].insert({dis(x,i)-r[i],i}),t1[x].insert({dis(fa[x],i)-r[i],i});
		printf("%lld\n",now);
	}
	return 0;
}
