#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

/* 图的邻接表表示法 */
#define MaxVertexNum 100        /* 最大顶点数设为100 */
typedef int Vertex;             /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;         /* 边的权值设为整型 */
typedef char DataType;          /* 顶点存储的数据类型设为字符型 */
bool  Visited[MaxVertexNum];	/* 访问标示 */

/* 边的定义 */
//typedef struct ENode *PtrToENode;
typedef struct ENode{
	Vertex V1, V2;      /* 有向边<V1, V2> */
	WeightType Weight;  /* 权重 */
}*PtrToENode;
typedef PtrToENode Edge;
ENode Edges[MaxVertexNum];  /*定义边集数组*/

/* 邻接点的定义 */
//typedef struct AdjVNode *PtrToAdjVNode;
typedef struct AdjVNode{
	Vertex AdjV;        /* 邻接点下标 */
	WeightType Weight;  /* 边权重 */
	struct AdjVNode *Next;    /* 指向下一个邻接点的指针 */
}*PtrToAdjVNode;

/* 顶点表头结点的定义 */
typedef struct Vnode{
	PtrToAdjVNode FirstEdge;/* 边表头指针 */
	DataType Data;            /* 存顶点的数据 */
	/* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */

/* 图结点的定义 */
//typedef struct GNode *PtrToGNode;
typedef struct GNode{
	int Nv;     /* 顶点数 */
	int Ne;     /* 边数   */
	AdjList G;  /* 邻接表 */
}*PtrToGNode;
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

LGraph CreateLGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接表头指针 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V<Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	/* 插入边 <V1, V2> */
	/* 为V2建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* 将V2插入V1的表头 */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* 若是无向图，还要插入边 <V2, V1> */
	/* 为V1建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	/* 将V1插入V2的表头 */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildLGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	cout << "输入顶点的个数和边数" << endl;
	cin >> Nv;   /* 读入顶点个数 */
	Graph = CreateLGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

	cin >> Graph->Ne; /* 读入边数 */
	if (Graph->Ne != 0) { /* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i < Graph->Ne; i++) {
			cout << "读入边，格式为 <起点 终点 权重> " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;

			/*边*/
			Edges[i].V1 = E->V1;
			Edges[i].V2 = E->V2;
			Edges[i].Weight = E->Weight;

			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdge(Graph, E);
		}
	}


	/* 如果顶点有数据的话，读入数据 */
	/*for (V = 0; V < Graph->Nv; V++)
	{
	cout << "第"<<V<<"个顶点的数据 " << endl;
	cin >> Graph->G[V].Data;
	} 	*/

	return Graph;
}

void ShowGraph(LGraph Graph){
	AdjVNode* p;
	for (int i = 0; i < Graph->Nv; i++)
	{
		cout << "第" << i << "顶点";
		p = Graph->G[i].FirstEdge;
		while (p)
		{
			cout << "->" << p->AdjV;
			p = p->Next;
		}
		cout << endl;
	}
}

/*查找连线顶点的尾部下标*/
int Find1(int *parent, int index)
{
	while (parent[index]>0)
		index = parent[index];
	return index;
}
/*以存储边（带权）的数组表示图。*/
void MiniSpanTree_Kruskal(LGraph Graph)	   /*生成最小数*/
{
	Vertex V1, V2;
	int j;
	int i = 0;
	int parent[MaxVertexNum]; /*定义一数组用来判断边与边是否形成回路*/
	ENode TEdge;
	Edge   TempEdge = &TEdge;
	//cout << "-------------------------------------" << endl;
	for (i = 0; i < Graph->Ne-1; i++)
		for (j = 0; j < Graph->Ne-i-1; j++)
			if (Edges[j].Weight > Edges[j + 1].Weight)
			{
				memcpy(TempEdge, &Edges[j], sizeof(ENode));
				memcpy(&Edges[j], &Edges[j + 1], sizeof(ENode));
				memcpy(&Edges[j + 1], TempEdge, sizeof(ENode));
			}
	for (int i = 0; i < Graph->Ne; i++)
	{
		cout << "V" << Edges[i].V1 << "-V" << Edges[i].V2 << "=" << Edges[i].Weight << endl;
	}  
	cout << "-------------------------------------" << endl;	
	for (int i = 0; i < Graph->Nv; i++)
		parent[i] = 0;/*初始化数组值为0*/
	for (int i = 0; i < Graph->Ne; i++)	 
	{
		V1 = Find1(parent, Edges[i].V1);
		V2 = Find1(parent, Edges[i].V2);
		if (V1 != V2)
		{
			parent[V1] = V2;
			cout << "V" << Edges[i].V1 << "-V" << Edges[i].V2 << "=" << Edges[i].Weight << endl;
		}
	}
}