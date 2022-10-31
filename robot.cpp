#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 1000
void printarr(int **arr,int V)
{
	for(int i=0;i<V;i++)
	{
		for(int j=0;j<V;j++)
			printf("%d	",arr[i][j]);
		printf("\n\n");
	}
}
bool end(bool Free[],int V);
int minarr(int arr[],int V,bool Free[]);
void insert(int **arr,int i,int j, int c)
{
	arr[i][j] = arr[j][i] = c;
}
int min(int a,int b)
{
	if(a>b) return b;
	else return a;
}
void printdf(int d[],int V,bool Free[])
{
		printf("\n");
	for(int i=0;i<V;i++)
	{
		printf("%d  ",d[i]);
	}
	printf("\n");
	for(int i=0;i<V;i++)
	{
		printf("%d  ",Free[i]);
	}
}
int distance(int a,int b,int V, int **arr);
int lacanh(int a,int b, int **arr);
int compare(int a, int b, int c,int V, int** arr);
int main()
{
	int a,b,c,d,r;
	int V, E;
	int **arr;
	scanf("%d%d",&V,&E);
	arr = (int**)malloc(V*sizeof(int*));
	for(int i=0;i<V;i++)
	{
		arr[i] = (int*)malloc(V*sizeof(int));
	}
	for(int i=0;i<V;i++)
	{
		for(int j=0;j<V;j++)
		{
			if(i==j) arr[i][j]=0;
			else arr[i][j] = INF;
		}
	}
	for(int i =0;i<E;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		insert(arr,a,b,c);
	}
	printf("Nhap 2 diem xuat phat: ");
	fflush(stdin);
	scanf("%d%d",&a,&b);
	fflush(stdin);
	printf("\nNhap diem ket thuc: ");
	scanf("%d%d",&c,&d);
	fflush(stdin);
	printf("\nNhap ban kinh nhieu: ");
	scanf("%d",&r);
	int **xungkhac;
	xungkhac = (int**)malloc(V*sizeof(int*));
	for(int i=0;i<V;i++)
	{
		xungkhac[i] = (int*)calloc(V,sizeof(int));
	}
	int n1 = a,n2 =b,n=0;
	int lichdichuyen[150][3];
	int index=0;
	int trc1[V]; int trc2[V];
		for(int i=0;i<V;i++)
		{
			trc1[i] = trc2[i] = -1;
		}
	bool check1 =false,check2 =false;
	index =0;
	while(!xungkhac[a][b]&&(n1!=c||n2!=d))
	{
		if(n1!=lichdichuyen[index-1][0]||n2!=lichdichuyen[index-1][1])
		{
			lichdichuyen[index][0] = n1;	
			lichdichuyen[index][1] = n2;
			lichdichuyen[index][2] = distance(n1,n2,V,arr);
			index++;
		}
		if(n1!=c)
		{
			int m=n1;
			for(int i=0;i<V;i++)
			{
				if(lacanh(m,i,arr))	
				if(distance(i,n2,V,arr)>r&&trc1[m]!=i&&!xungkhac[i][n2])
				{
					trc1[i] = m;
					n1 = i;
					break;
				}
			}

			if(m==n1)
			{
				check1=true;
			}
			if(check1&&check2)
			{
				xungkhac[n1][n2]=xungkhac[n2][n1] = 1;
				if(distance(n1,trc2[n2],V,arr)>r&&!xungkhac[n1][trc2[n2]])
				{
					int tmp = n2;
					n2 = trc2[n2];
					trc2[n2] =tmp;
					check2=false;
				}				
			}									
		}						
		if(n1!=lichdichuyen[index-1][0]||n2!=lichdichuyen[index-1][1])
		{
			lichdichuyen[index][0] = n1;
			lichdichuyen[index][1] = n2;
			lichdichuyen[index][2] = distance(n1,n2,V,arr);
			index++;
		}		
		if(n2!=d)
		{
			int p = n2;
			for(int i=0;i<V;i++)
			{
				if(lacanh(p,i,arr))
					if(distance(i,n1,V,arr)>r&&trc2[p]!=i&&!xungkhac[i][n1])
					{					
						trc2[i] =p;						
			 			n2 = i;
						break;
					}
			}
			if(n2 ==p) check2=true;
			if(check1&&check2)
			{
				xungkhac[n1][n2] = xungkhac[n2][n1] = 1;
				if(distance(n2,trc1[n1],V,arr)>r&&!xungkhac[n2][trc1[n1]])
				{
					int tmp = n1;
					n1 = trc1[n1];
					trc1[n1] =tmp;
					check1=false;
				}
			}			
		}
	}
	if(n1!=lichdichuyen[index-1][0]||n2!=lichdichuyen[index-1][1])
	{
		lichdichuyen[index][0] = n1;
		lichdichuyen[index][1] = n2;
		lichdichuyen[index][2] = distance(n1,n2,V,arr);
		index++;
	}		
	if(n1==c&&n2==d)
	{
		printf("Lich di chuyen      Khoang cach\n");
		printf("     A    B\n");
		for(int i=0;i<index;i++)
		{	
			printf("     %d    %d              %d\n",lichdichuyen[i][0],lichdichuyen[i][1],lichdichuyen[i][2]);
		}
	}		
	else printf("\nKHONG TIM THAY DUONG DI!");
	return 0;
}
bool end(bool Free[],int V)
{
	for(int i=0;i<V;i++)
	{
		if(!Free[i])
		return false;		
	}
	return true;
}
int minarr(int arr[],int V,bool Free[])
{
	int m,i,min;
	for(i=0;i<V;i++)
	{
		if(!Free[i])
		{
			min = arr[i];
			m = i;
			break;
		}
	}
	for(int j=i+1;!Free[j]&&j<V;j++)
	{
		if(min>arr[j])
		{
			min = arr[j];
			m =j;
		}
	}
	return m;
}
int distance(int a,int b,int V,int **arr)
{
	int d[V];
   	bool Free[V];	  
   	for(int i=0;i<V;i++)
   	{
   		Free[i] = false;
   		if(i==a) d[i]=0;
   		else
   		d[i] = INF;
	}
	while(!end(Free,V))
	{
		int u = minarr(d,V,Free);
		Free[u] = true;
		for(int v=0;v<V;v++)
		{
			int c_u_v = arr[u][v];
			d[v]= min(d[v],d[u]+c_u_v);
		}
	}
	return d[b];
}
int compare(int a, int b, int c,int V, int **arr)
{
	if(lacanh(a,c,arr))
	{
		if(lacanh(b,c,arr))
		{
			if(distance(a,c,V,arr)<distance(b,c,V,arr)) return b;
			else return a;
		}
		else return a;
	}
	else
	{
		if(lacanh(b,c,arr)) return b;
		else 
		{
			if(distance(a,c,V,arr)<distance(b,c,V,arr)) return b;
			else return a;
		}
	}
}
int lacanh(int a,int b, int **arr)
{
	return (arr[a][b]>0&&arr[a][b]<INF);
}







