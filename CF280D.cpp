#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
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

template<class T>inline void read(T&x)
{
	char ch=getchar();
	int fu;
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if(ch=='-') fu=-1,ch=getchar();
	x=ch-'0';ch=getchar();
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	x*=fu;
}
inline int read()
{
	int x=0,fu=1;
	char ch=getchar();
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if(ch=='-') fu=-1,ch=getchar();
	x=ch-'0';ch=getchar();
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*fu;
}
int G[55];
template<class T>inline void write(T x)
{
	int g=0;
	if(x<0) x=-x,putchar('-');
	do{G[++g]=x%10;x/=10;}while(x);
	for(int i=g;i>=1;--i)putchar('0'+G[i]);putchar('\n');
}

LL a[100010];
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
		if(l==r)
		{
			sum=lmax=rmax=zmax=lmin=rmin=zmin=a[l]; 
			lmaxr=rmaxl=zmaxl=zmaxr=lminr=rminl=zminl=zminr=l;
		}
		else sum=lmax=lmaxr=rmax=rmaxl=zmax=zmaxl=zmaxr=lmin=lminr=rmin=rminl=zmin=zminl=zminr=0;
		lazy=0;
	}
	void clear()
	{
		lazy=sum=lmax=lmaxr=rmax=rmaxl=zmax=zmaxl=zmaxr=lmin=lminr=rmin=rminl=zmin=zminl=zminr=0;
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
	
	x.zmax=y.rmax+z.lmax;//zmax
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
	
	
	if(x.lmin>y.sum+z.lmin)//lmin
	{
		x.lmin=y.lmin;
		x.lminr=y.lminr;
	}
	else
	{
		x.lmin=y.sum+z.lmin;
		x.lminr=z.lmin;
	}
	
	if(x.rmin>z.sum+y.rmin)//rmin
	{
		x.rmin=z.rmin;
		x.rminl=z.rminl;
	}
	else
	{
		x.rmin=z.sum+y.rmin;
		x.rminl=y.rmin;
	}
	
	x.zmin=y.rmin+z.lmin;//zmin
	x.zminl=y.rminl;
	x.zminr=z.lminr;
	if(x.zmin>y.zmin)
	{
		x.zmin=y.zmin;
		x.zminl=y.zminl;
		x.zminr=y.zminr;
	}
	if(x.zmin>z.zmin)
	{
		x.zmin=z.zmin;
		x.zminl=z.zminl;
		x.zminr=z.zminr;
	}
}
node upd(node y,node z)
{
	node res;
	upd(res,y,z);
	return res;
}
void upd(LL & x,LL y,LL z)
{
	upd(b[x],b[y],b[z]);
}
void upd(LL & p)
{
	upd(p,p<<1,p<<1|1);
}
void build(LL l,LL r,LL p)
{
	l(p)=l;
	r(p)=r;
	if(l==r)
	{
		b[p]=node(l,r);
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	upd(p);
}
void spread(LL p)
{
	if(lazy(p))
	{
		if(l(p)!=r(p)) lazy(p<<1)=lazy(p<<1|1)=1;
		
		sum(p)=-sum(p);
		
		lmax(p)=-lmax(p);
		rmax(p)=-rmax(p);
		zmax(p)=-zmax(p);
		
		lmin(p)=-lmin(p);
		rmin(p)=-rmin(p);
		zmin(p)=-zmin(p);
		
		swap(lmax(p),lmin(p));
		swap(lmaxr(p),lminr(p));
		swap(rmax(p),rmin(p));
		swap(rmaxl(p),rminl(p));
		swap(zmax(p),zmin(p));
		swap(zmaxl(p),zminl(p));
		swap(zmaxr(p),zminr(p));
		
		lazy(p)=0;
	} 
}
void change_one(LL p,LL x,LL k)
{
	if(l(p)==r(p))
	{
		a[l(p)]=k;
		b[p]=node(l(p),r(p));
		return;
	}
	spread(p);
	LL mid=(l(p)+r(p))>>1;
	if(x<=mid) change_one(p<<1,x,k);
	else change_one(p<<1|1,x,k);
	upd(p);
}
void change_fu(LL p,LL L,LL R)
{
	if(L<=l(p)&&r(p)<=R)
	{
		lazy(p)^=1;
		spread(p);
		return;
	}
	spread(p);
	LL mid=(l(p)+r(p))>>1;
	if(L<=mid) change_fu(p<<1,L,R);
	if(R>mid) change_fu(p<<1|1,L,R);
	upd(p);
}
node ask(LL p,LL L,LL R)
{
//	cout<<"p="<<p<<" lp="<<l(p)<<" rp="<<r(p)<<" L="<<L<<" R="<<R<<endl;
	if(L<=l(p)&&r(p)<=R)
	{
		return b[p];
	}
	spread(p); 
	LL mid=(l(p)+r(p))>>1;
	node now;
	if(R<=mid) return ask(p<<1,L,R);
	else if(L>mid) return ask(p<<1|1,L,R);
	return upd(ask(p<<1,L,R),ask(p<<1|1,L,R));
}
LL n,m,ans;
struct Order
{
	LL l,r;
}order[100];
int top;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,n,1);
	cin>>m;
	for(int i=1,op,x,y,l,r,k;i<=m;i++)
	{
		cin>>op;
		if(op)
		{
			cin>>l>>r>>k;
			node now;
			ans=top=0;
			for(int i=1;i<=k;i++)
			{
				now=ask(1,l,r);
				if(now.zmax<=0) break;
				debug cout<<"ready to change_fu "<<now.zmaxl<<" "<<now.zmaxr<<" "<<now.zmax<<endl;
				ans+=now.zmax;
				change_fu(1,now.zmaxl,now.zmaxr);
				order[top].l=now.zmaxl;
				order[top].r=now.zmaxr;
				top++;
			}
			while(top)
			{
				top--;
				change_fu(1,order[top].l,order[top].r);
			}
			cout<<ans<<endl;
		}
		else
		{
			cin>>x>>y;
			change_one(1,x,y);
		}
	}
	return 0;
}


