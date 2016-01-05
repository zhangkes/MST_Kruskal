// MST_Kruskal.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"LGrahp.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Kruskal最小生成树算法" << endl;
	LGraph Graph = BuildLGraph();
	ShowGraph(Graph);
	MiniSpanTree_Kruskal(Graph);
	return 0;
}

