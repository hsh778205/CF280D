#include<bits/stdc++.h>
#define re register
#define LL long long
#define debug printf("Now is %d\n",__LINE__);
using namespace std;
inline int read()
{
	re int x=0,f=1;
	re char ch=getchar();
	for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') f*=-1;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
struct node
{
	LL l,r,sum;
	LL lmax,lmaxr,rmax,rmaxl;
	LL zmax,zmaxl,zmaxr;
	LL lmin,lminr,rmin,rminl;
	LL zmin,zminl,zminr;
	LL lazy;
	
	#define l(x) b[x].l
	#define r(x) b[x].r
	#define sum(x) b[x].sum
	
	#define lmax(x) b[x].lmax
	#define lmaxr(x) b[x].lmaxr
	#define rmax(x) b[x].rmax
	#define rmaxl(x) b[x].rmaxl
	#define zmax(x) b[x].zmax
	#define zmaxl(x) b[x].zmaxl
	#define zmaxr(x) b[x].zmaxr
	
	#define lmin(x) b[x].lmin
	#define lminr(x) b[x].lminr
	#define rmin(x) b[x].rmin
	#define rminl(x) b[x].rminl
	#define zmin(x) b[x].zmin
	#define zminl(x) b[x].zminl
	#define zminr(x) b[x].zminr
	
	#define lazy(x) b[x].lazy
	node()
	{
		l=r=sum=lmax=lmaxr=rmax=rmaxl=zmax=zmaxl=zmaxr=lmin=lminr=rmin=rminl=zmin=zminl=zminr=lazy=0;
	}
	node(LL L,LL R)
	{
		l=L; 
		r=R; 
		sum=lmax=lmaxr=rmax=rmaxl=zmax=zmaxl=zmaxr=lmin=lminr=rmin=rminl=zmin=zminl=zminr=lazy=0;
	}
	void clear()
	{
		sum=lmax=lmaxr=rmax=rmaxl=zmax=zmaxl=zmaxr=lmin=lminr=rmin=rminl=zmin=zminl=zminr=0;
	}
}b[400010];
void upd(node & x,node & y,node & z)
{
	x.l=y.l;
	x.r=z.r;
	x.sum=y.sum+z.sum;
	
	if(x.lmax>y.sum+z.lmax)//lmax
	{
		x.lmax=y.lmax;
		x.lmaxr=y.lmaxr;
	}
	else
	{
		x.lmax=y.sum+z.lmax;
		x.lmaxr=z.lmax;
	}
	
	if(x.rmax>z.sum+y.rmax)//rmax
	{
		x.rmax=z.rmax;
		x.rmaxl=z.rmaxl;
	}
	else
	{
		x.rmax=z.sum+y.rmax;
		x.rmaxl=y.rmax;
	}
	
	x.zmax=y.rmaxz+.lmax;//zmax
	x.zmaxl=y.rmaxl;
	x.zmaxr=z.lmaxr;
	if(x.zmax<y.zmax)
	{
		x.zmax=y.zmax;
		x.zmaxl=y.zmaxl;
		x.zmaxr=y.zmaxr;
	}
	if(x.zmax<z.zmax)
	{
		x.zmax=z.zmax;
		x.zmaxl=z.zmaxl;
		x.zmaxr=z.zmaxr;
	}
	
	
	if(x.lmin<y.sum+z.lmin)//lmin
	{
		x.lmin=y.lmin;
		x.lminr=y.lminr;
	}
	else
	{
		x.lmin=y.sum+z.lmin;
		x.lminr=z.lmin;
	}
	
	if(x.rmin<z.sum+y.rmin)//rmin
	{
		x.rmin=z.rmin;
		x.rminl=z.rminl;
	}
	else
	{
		x.rmin=z.sum+y.rmin;
		x.rminl=y.rmin;
	}
	
	x.zmin=y.rmin+z.lmin;//zmax
	x.zminl=y.rminl;
	x.zminr=z.lminr;
	if(x.zmin<y.zmin)
	{
		x.zmin=y.zmin;
		x.zminl=y.zminl;
		x.zminr=y.zminr;
	}
	if(x.zmin<z.zmin)
	{
		x.zmax=z.zmin;
		x.zmaxl=z.zmaxl;
		x.zmaxr=z.zmaxr;
	}
}

int main()
{

	return 0;
}


