#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<limits.h>
#define IL inline
#define re register
#define LL long long
#define ULL unsigned long long
#ifdef TH
#define debug printf("Now is %d\n",__LINE__);
#else
#define debug
#endif
using namespace std;
#define N 100010
int n,m;
struct node
{
	LL l,r,sum;
	bool lazy;
	LL lmax,lmaxr,rmax,rmaxl;
	LL lmin,lminr,rmin,rminl;
	LL zmax,zmaxl,zmaxr,zmin,zminl,zminr;
	#define l(x) b[x].l
	#define r(x) b[x].r
	#define lazy(x) b[x].lazy
	#define lmax(x) b[x].lmax
	#define lmaxr(x) b[x].lmaxr
	#define rmax(x) b[x].rmax
	#define rmaxl(x) b[x].rmaxl
	#define lmin(x) b[x].lmin
	#define lminr(x) b[x].lminr
	#define rmin(x) b[x].rmin
	#define rminl(x) b[x].rminl
	#define zmax(x) b[x].zmax
	#define zmaxl(x) b[x].zmaxl
	#define zmaxr(x) b[x].zmaxr
	#define zmin(x) b[x].zmin
	#define zminl(x) b[x].zminl
	#define zminr(x) b[x].zmaxr
	#define sum(x) b[x].sum
}t,b[N*4];
LL a[N];
#define ls (p<<1)
#define rs (p<<1|1)
IL void upd(int p)
{
	
	//base
	sum(p)=sum(ls)+sum(rs);
	//lmax
	if(lmax(ls)>sum(ls)+lmax(rs))
	{
		lmax(p)=lmax(ls);
		lmaxr(p)=lmaxr(ls);
	}
	else
	{
		lmax(p)=sum(ls)+lmax(rs);
		lmaxr(p)=lmax(rs);
	}
	//rmax
	if(rmax(rs)>sum(rs)+rmax(ls))
	{
		rmax(p)=rmax(rs);
		rmaxl(p)=rmaxl(rs);
	}
	else
	{
		rmax(p)=sum(rs)+rmax(ls);
		rmaxl(p)=rmaxl(ls);
	}
	//lmin
	if(lmin(ls)<sum(ls)+lmax(rs))
	{
		lmin(p)=lmin(ls);
		lminr(p)=lminr(ls); 
	}
	else
	{
		lmin(p)=sum(ls)+lmin(rs);
		lminr(p)=lminr(rs);
	}
	//rmin
	if(rmin(rs)<sum(rs)+rmin(ls))
	{
		rmin(p)=rmin(rs);
		rminl(p)=rminl(rs);
	}
	else
	{
		rmin(p)=sum(rs)+rmin(ls);
		rminl(p)=rminl(ls);
	}
	//zmax
	if(zmax(ls)<zmax(rs))
	{
		if(zmax(rs)<rmax(ls)+lmax(rs))
		{
			zmax(p)=rmax(ls)+lmax(rs);
			zmaxl(p)=rmaxl(ls);
			zmaxr(p)=lmaxr(rs);
		}
		else
		{
			zmax(p)=zmax(rs);
			zmaxl(p)=zmaxl(rs);
			zmaxr(p)=zmaxr(rs);
		}
	}
	else
	{
		if(zmax(ls)<rmax(ls)+lmax(rs))
		{
			zmax(p)=rmax(ls)+lmax(rs);
			zmaxl(p)=rmaxl(ls);
			zmaxr(p)=lmaxr(rs);
		}
		else
		{
			zmax(p)=zmax(ls);
			zmaxl(p)=zmaxl(ls);
			zmaxr(p)=zmaxr(ls);
		}
	}
	//zmin
	if(zmin(ls)>zmin(rs))
	{
		if(zmin(rs)>rmin(ls)+lmin(rs))
		{
			zmin(p)=rmin(ls)+lmin(rs);
			zminl(p)=rminl(ls);
			zminr(p)=lminr(rs);
		}
		else
		{
			zmin(p)=zmin(rs);
			zmaxl(p)=zminl(rs);
			zmaxr(p)=zmaxr(rs);
		}
	}
	else
	{
		if(zmin(ls)>rmin(ls)+lmin(rs))
		{
			zmin(p)=rmin(ls)+lmin(rs);
			zminl(p)=rminl(ls);
			zminr(p)=lminr(rs);
		}
		else
		{
			zmin(p)=zmin(ls);
			zminl(p)=zminl(ls);
			zminr(p)=zminr(ls);
		}
	}
}
void work(int p)
{
	lazy(p)^=1;
	zmax(p)*=-1;
	zmin(p)*=-1;
	lmax(p)*=-1;
	lmin(p)*=-1;
	rmax(p)*=-1;
	rmin(p)*=-1;
	swap(zmax(p),zmin(p));swap(zmaxl(p),zminl(p));swap(zmaxr(p),zminr(p));
	swap(lmax(p),lmin(p));swap(lmaxr(p),lminr(p));
	swap(rmax(p),rmin(p));swap(rmaxl(p),rminl(p));
}
void spread(int p)
{
	if(lazy(p))
	{
		lazy(p<<1)^=1;
		lazy(p<<1|1)^=1;
		work(p<<1);
		work(p<<1|1);
	}
}
void work(int p,int k)
{
	sum(p)=zmax(p)=zmin(p)=lmax(p)=lmin(p)=rmax(p)=rmin(p)=k;
	lmaxr(p)=lminr(p)=rmaxl(p)=rminl(p)=zmaxl(p)=zmaxr(p)=zminl(p)=zminr(p)=l(p);
}
void change(int p,int x,int k)
{
	if(l(p)==r(p))
	{
		work(p,k);
		return;
	}
	spread(p);
	int mid=l(p)+r(p)>>1;
	if(x<=mid) change(p<<1,x,k);
	else change(p<<1|1,x,k);
	upd(p);
}
void change_fu(int p,int l,int r)
{
	if(l<=l(p)&&r(p)<=r)
	{
		work(p);
		return;
	}
	spread(p);
	int mid=l(p)+r(p)>>1;
	if(l<=mid) change_fu(p<<1,l,r);
	if(r>mid) change_fu(p<<1|1,l,r);
	upd(p);
}
node merge(node ls,node rs)
{
	
}
node ask(int p,int l,int r)
{
	
}
vector<pair<LL,LL>>vec;
LL ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cin>>m;
	for(int i=1,op,x,y,k;i<=m;i++)
	{
		cin>>op>>x>>y;
		if(op==0)
		{
			change(1,x,y);
		}
		else
		{
			vec.clear();
			cin>>k;
			ans=0;
			while(k--)
			{
				t=ask(1,x,y);
				if(t.zmax<=0) break;
				ans+=t.zmax;
				vec.push_back(make_pair(t.zmaxl,t.zmaxr));
				change_fu(1,t.zmaxl,t.zmaxr);
			}
			while(vec.size())
			{
				change_fu(1,vec.back().first,vec.back().second);
				vec.pop_back();
			}
			
		}
	}
	return 0;
}


