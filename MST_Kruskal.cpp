// MST_Kruskal.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"LGrahp.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Kruskal��С�������㷨" << endl;
	LGraph Graph = BuildLGraph();
	ShowGraph(Graph);
	MiniSpanTree_Kruskal(Graph);
	return 0;
}

