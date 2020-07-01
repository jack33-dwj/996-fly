#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<string>
using namespace std;

struct link//链路
{
	int num;
	int point1;
	int point2;
	bool explore = false;
};
struct node//节点
{
	int num;
	bool explore = false;
	vector<link*> link_list;
};
typedef vector<node> node_List;//节点集合
vector<node> node_list;//点集合
vector<link*> link_list;//边集合
vector<string> path_list;//最佳路径集合
string DFS(string path, node node)//深度优先探索
{
	//将节点设置为已探索
	node.explore = true;
	//将当前节点添加进路径
	path = path + to_string(node.num) + ' ';
	for (unsigned i = 0;i < node.link_list.size();i++)
	{
		if (!(*(node.link_list[i])).explore)
		{
			if (path == "")//用来处理递归返回之后再次进入递归之前要将新的探测点计入
			{
				path = path + to_string(node.num) + ' ';
			}
			//将节点的边设置为已搜索
			(*(node.link_list[i])).explore = true;
			if ((*(node.link_list[i])).point1 == node.num)
			{
				path = DFS(path, node_list[(*(node.link_list[i])).point2]);
			}
			else
			{
				path = DFS(path, node_list[(*(node.link_list[i])).point1]);
			}
		}
	}
	//当一个节点没有未访问的边的时候返回
	if (path != "")
		path_list.push_back(path);
	// 为了防止在输出的路径集之间有交集 回溯之后为进的探测路径 满足条件1 再递归返回的时候将path清空
	return "";
}
int main()
{
	vector<node>().swap(node_list);
	vector<link*>().swap(link_list);
	int link_num = 0;
	int t;
	string path;
	cin >> t;
	for (int i = 0;i < t;i++)
	{
		node v;
		v.num = i;//将i到t的链路间接到节点i
		for (int j = i + 1;j < t;j++)//对链路进行初始化
		{
			link* link_pointer = new link;
			(*link_pointer).explore = false;
			(*link_pointer).num = link_num++;
			(*link_pointer).point1 = i;
			(*link_pointer).point2 = j;
			v.link_list.push_back(link_pointer);//将该链路分别记录在对应的节点中
			link_list.push_back(link_pointer);//将该链路记录到链路集合
		}
		for (int j = 0;j < i;j++)//将0到i的链路链接到节点i
		{
			link* link_pointer = NULL;
			for (unsigned list_num = 0;list_num < link_list.size();list_num++)
			{
				if ((*link_list[list_num]).point1 == j && (*link_list[list_num]).point2 == i)
				{
					link_pointer = link_list[list_num];
					break;
				}
			}
			v.link_list.push_back(link_pointer);
		}
		node_list.push_back(v);//将节点记录到节点集合
	}
	DFS(path, node_list[0]);
	for (unsigned i = 0;i < path_list.size();i++)
	{
		cout << path_list[i] << endl;
	}
	system("pause");
	return 0;
}