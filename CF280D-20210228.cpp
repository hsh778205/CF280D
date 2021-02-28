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
	#define zminr(x) b[x].zminr
	#define sum(x) b[x].sum
}t,b[N*4];
LL a[N];
IL void merge(node& p,node ls,node rs)
{
	//base
	p.sum=ls.sum+rs.sum;
	//lmax
	if(ls.lmax>ls.sum+rs.lmax)
	{
		p.lmax=ls.lmax;
		p.lmax=ls.lmaxr;
	}
	else
	{
		p.lmax=ls.sum+rs.lmax;
		p.lmax=rs.sum;
	}
	//rmax
	if(rs.rmax>rs.sum+ls.rmax)
	{
		p.rmax=rs.rmax;
		p.rmaxl=rs.rmaxl;
	}
	else
	{
		p.rmax=rs.sum+ls.rmax;
		p.rmaxl=ls.rmaxl;
	}
	//lmin
	if(ls.lmin<ls.sum+rs.lmin)
	{
		p.lmin=ls.lmin;
		p.lminr=ls.lminr;
	}
	else
	{
		p.lmin=ls.sum+rs.lmin;
		p.lminr=rs.lminr;
	}
	//rmin
	if(rs.rmin<rs.sum+ls.rmin)
	{
		p.rmin=rs.rmin;
		p.rminl=rs.rminl;
	}
	else
	{
		p.rmin=rs.sum+ls.rmin;
		p.rminl=ls.rminl;
	}
	//zmax
	if(ls.zmax<rs.zmax)
	{
		if(rs.zmax<ls.rmax+rs.lmax)
		{
			p.zmax=ls.rmax+rs.lmax;
			p.zmaxl=ls.rmaxl;
			p.zmaxr=rs.lmaxr;
		}
		else
		{
			p.zmax=rs.zmax;
			p.zmaxl=rs.zmaxl;
			p.zmaxr=rs.zmaxr;
		}
	}
	else
	{
		if(ls.zmax<ls.rmax+rs.lmax)
		{
			p.zmax=ls.rmax+rs.lmax;
			p.zmaxl=ls.rmaxl;
			p.zmaxr=rs.lmaxr;
		}
		else
		{
			p.zmax=ls.zmax;
			p.zmaxl=ls.zmaxl;
			p.zmaxr=ls.zmaxr;
		}
	}
	//zmin
	if(ls.zmin>rs.zmin)
	{
		if(rs.zmin>ls.rmin+rs.lmin)
		{
			p.zmin=ls.rmin+rs.lmin;
			p.zminl=ls.zminl;
			p.zminr=rs.zminr;
		}
		else
		{
			p.zmin=rs.zmin;
			p.zminl=rs.zminl;
			p.zminr=rs.zminr;
		}
	}
	else
	{
		if(ls.zmin>ls.rmin+rs.lmin)
		{
			p.zmin=ls.rmin+rs.lmin;
			p.zminl=ls.zminl;
			p.zminr=rs.zminr;
		}
		else
		{
			p.zmin=ls.zmin;
			p.zminl=ls.zminl;
			p.zminr=ls.zminr;
		}
	}
}
void upd(int p)
{
	merge(b[p],b[p<<1],b[p<<1|1]);
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

node ask(int p,int l,int r)
{
	if(l<=l(p)&&r(p)<=r)
	{
		return b[p];
	}
	spread(p);
	int mid=l(p)+r(p)>>1;
	node ans,ls,rs;
	if(l<=mid) ls=ask(p<<1,l,r);
	if(r>mid) rs=ask(p<<1|1,l,r);
	merge(ans,ls,rs);
	return ans;
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


