#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

/* ͼ���ڽӱ��ʾ�� */
#define MaxVertexNum 100        /* ��󶥵�����Ϊ100 */
typedef int Vertex;             /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;         /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;          /* ����洢������������Ϊ�ַ��� */
bool  Visited[MaxVertexNum];	/* ���ʱ�ʾ */

/* �ߵĶ��� */
//typedef struct ENode *PtrToENode;
typedef struct ENode{
	Vertex V1, V2;      /* �����<V1, V2> */
	WeightType Weight;  /* Ȩ�� */
}*PtrToENode;
typedef PtrToENode Edge;
ENode Edges[MaxVertexNum];  /*����߼�����*/

/* �ڽӵ�Ķ��� */
//typedef struct AdjVNode *PtrToAdjVNode;
typedef struct AdjVNode{
	Vertex AdjV;        /* �ڽӵ��±� */
	WeightType Weight;  /* ��Ȩ�� */
	struct AdjVNode *Next;    /* ָ����һ���ڽӵ��ָ�� */
}*PtrToAdjVNode;

/* �����ͷ���Ķ��� */
typedef struct Vnode{
	PtrToAdjVNode FirstEdge;/* �߱�ͷָ�� */
	DataType Data;            /* �涥������� */
	/* ע�⣺�ܶ�����£����������ݣ���ʱData���Բ��ó��� */
} AdjList[MaxVertexNum];    /* AdjList���ڽӱ����� */

/* ͼ���Ķ��� */
//typedef struct GNode *PtrToGNode;
typedef struct GNode{
	int Nv;     /* ������ */
	int Ne;     /* ����   */
	AdjList G;  /* �ڽӱ� */
}*PtrToGNode;
typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */

LGraph CreateLGraph(int VertexNum)
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӱ�ͷָ�� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V<Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	/* ����� <V1, V2> */
	/* ΪV2�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* ��V2����V1�ı�ͷ */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* ��������ͼ����Ҫ����� <V2, V1> */
	/* ΪV1�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	/* ��V1����V2�ı�ͷ */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildLGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	cout << "���붥��ĸ����ͱ���" << endl;
	cin >> Nv;   /* ���붥����� */
	Graph = CreateLGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	cin >> Graph->Ne; /* ������� */
	if (Graph->Ne != 0) { /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i < Graph->Ne; i++) {
			cout << "����ߣ���ʽΪ <��� �յ� Ȩ��> " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;

			/*��*/
			Edges[i].V1 = E->V1;
			Edges[i].V2 = E->V2;
			Edges[i].Weight = E->Weight;

			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge(Graph, E);
		}
	}


	/* ������������ݵĻ����������� */
	/*for (V = 0; V < Graph->Nv; V++)
	{
	cout << "��"<<V<<"����������� " << endl;
	cin >> Graph->G[V].Data;
	} 	*/

	return Graph;
}

void ShowGraph(LGraph Graph){
	AdjVNode* p;
	for (int i = 0; i < Graph->Nv; i++)
	{
		cout << "��" << i << "����";
		p = Graph->G[i].FirstEdge;
		while (p)
		{
			cout << "->" << p->AdjV;
			p = p->Next;
		}
		cout << endl;
	}
}

/*�������߶����β���±�*/
int Find1(int *parent, int index)
{
	while (parent[index]>0)
		index = parent[index];
	return index;
}
/*�Դ洢�ߣ���Ȩ���������ʾͼ��*/
void MiniSpanTree_Kruskal(LGraph Graph)	   /*������С��*/
{
	Vertex V1, V2;
	int j;
	int i = 0;
	int parent[MaxVertexNum]; /*����һ���������жϱ�����Ƿ��γɻ�·*/
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
		parent[i] = 0;/*��ʼ������ֵΪ0*/
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