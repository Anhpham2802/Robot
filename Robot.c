#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define INF 1000
int **xungkhac;
int V, E;
int **arr;
int check =0;
int a,b,c,d,r;
typedef struct Path
{
	int x,y;
} PATH;
void printarr(int **arr,int V)
{
	for(int i=0;i<V;i++)
	{
		for(int j=0;j<V;j++)
			printf("%d	",arr[i][j]);
		printf("\n\n");
	}
}
int **path;
int count = 0;
bool end(bool Free[],int V);
int minarr(int arr[],int V,bool Free[]);
void swap(PATH *a,PATH *b)
{
	PATH tmp = *a;
	*a = *b;
	*b = tmp;
}
void insert(int **arr,int i,int j, int c)
{
	arr[i][j] = arr[j][i] = c;
}
void quicksort(PATH array[], int l,int r);
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
void find_path(int u1,int u2);
int main()
{
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
	xungkhac = (int**)malloc(V*sizeof(int*));
	for(int i=0;i<V;i++)
	{
		xungkhac[i] = (int*)calloc(V,sizeof(int));
	}
	path = (int**)malloc(E*sizeof(int));
	for(int i=0;i<E;i++)
		path[i]= (int*)malloc(3*sizeof(int));
	find_path(a,b);
	if(!check) printf("\nNO PATH FOUND");
	else printf("\nLich di chuyen    Khoang cach");
	for(int i = count-1;i>=0;i--)
		printf("\n%3d --%3d            %3d",path[i][0],path[i][1],path[i][2]);
	return 0;
}
void find_path(int u1,int u2)
{
	PATH *queue = (PATH*)malloc(E*sizeof(PATH));
	int top=0;
	xungkhac[u1][u2] = 1;
	if(u1 == c&&u2==d)
	{
		check = 1;
		path[count][0] = u1;
		path[count][1] = u2;
		path[count][2] = distance(u1,u2,V,arr);
		count++;
		return;
	}
	for(int i=0;i<V;i++)
	{
		if(lacanh(u1,i,arr)&&distance(i,u2,V,arr)>r)
		{
			queue[top].x = i;
			queue[top].y = u2;
			top++;
		}
		if(lacanh(i,u2,arr)&&distance(i,u1,V,arr)>r)
		{
			queue[top].x = u1;
			queue[top].y = i;
			top++;
		}
	}
	quicksort(queue,0,top-1);
	for(int v = 0;v<top;v++)
	{
		if(!xungkhac[queue[v].x][queue[v].y])
		{
			find_path(queue[v].x,queue[v].y);
			if(check==1)
			{
				path[count][0] = u1;
				path[count][1] = u2;
				path[count][2] = distance(u1,u2,V,arr);
				count++;
				return;
			}
		}
	}
	free(queue);
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
void quicksort(PATH array[], int l,int r)
{
	if(l<r){
	int pivot = distance(array[r].x,c,V,arr) + distance(array[r].y,d,V,arr);
	int left = l;
	int right = r-1;
	while(true)
	{
		while(left<=right&&distance(array[left].x,c,V,arr) + distance(array[left].y,d,V,arr)<pivot) left++;
		while(right>=left&&distance(array[right].x,c,V,arr) + distance(array[right].y,d,V,arr)>pivot)right--;
		if(left>=right) break;
		swap(&array[left], &array[right]);
		right--;
		left++;
	}
	swap(&array[r], &array[left]);

	
		int pi =left;
		quicksort(array,l,pi-1);
		quicksort(array,pi+1,r);
		
	}
}
int lacanh(int a,int b, int **arr)
{
	return (arr[a][b]>0&&arr[a][b]<INF);
}

