#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define ElemType char
#define QueueSize 50
#define push Push
#define empty Empty
#define pop Pop
#define front Front
typedef struct CSNode{
	ElemType data[10];
	struct CSNode *firstchild, *nextsibling;
}CSNode,*CSTree;//节点结构

void InitTree(CSNode *A)
{  //init a empty tree
    A = new CSNode;//creat a new node
    A->firstchild = A->nextsibling = NULL;
}
int Search_(CSNode *X, char *a)
{    //查找待插入的节点在树中是否存在
	//find if the node  exist in the tree
	CSNode *B;
	B = X;//set B to the root
	while (B->data)
	{
		if (strcmp(B->data, a) == 0)
		{
			X = B;  //find the node'data is equal,then do this
			return 1;
		}
		else
		{
			B = B->nextsibling;  //or set B to its sibling
		}
	}
	return 0;
}

void insert_one(CSNode *A, ElemType *s)
{
	//insert a node into the tree
	CSNode *B, *X;		
	char *str;
	int i;
	X = A;  //set X to the root
	B = new CSNode;
	B->firstchild = B->nextsibling = NULL;
	char Temp[15];  //中转数组

	//loop until the string end 
	while(s!='\0')
	{
		//zhongzhuan接受s中xxx.部分或取完翻转zhongzhuan	
		str = strchr(s, '.');//返回字符串s中第一次出现点的位置
		if (str)
		{
			i = str - s;
			Temp[i + 1] = '\0';
			for (; i >= 0; i--, s++)
			{
				Temp[i] = s[0];//将拆分后的节点传入中转数组中
			}
		}
		else
		{//字符串中不含点符号
			_strrev(s);
			i = strlen(s);
			Temp[i + 1] = '\0';
			for (; i >= 0; i--)
			{
				Temp[i] = s[i];//将字符串存入中转数组里
			}
			//s = '\0';
			break;
		}

		if (Search_(X, Temp))
		{//若要插入的字符串已存在该层面上
			X = X->firstchild;//x指向孩子节点
			continue;
		}
		if (X->data[0] == '0')//question
		{
			strcpy(X->data, Temp);//将中转数组的信息复制给待插入节点
			B = new CSNode;
			B->firstchild = B->nextsibling = NULL;
		}
		else
		{
			strcpy(B->data, Temp);
			if (X->firstchild)
			{
				X->nextsibling = B;//将Ｂ作为Ｘ的兄弟节点
				B = new CSNode;
				B->firstchild = B->nextsibling = NULL;
				
				X = X->nextsibling;  //x指向它的兄弟节点
			}
			else
			{	
				X->firstchild = B;
				B = new CSNode;
				B->firstchild = B->nextsibling = NULL;
				X = X->firstchild;
			}
		}
	}
}
struct Queue {
	int Top, Tail;
	CSNode *a[1000];
	void Clear();
	void Push(CSNode *e);
	void Pop();
	CSNode *Front();
	bool Empty();
};//队列封装为结构体

void Queue::Clear() {
	Top = Tail = 0;
	return;
}//清空队列

void Queue::Push(CSNode *e) {
	a[Tail++] = e;
	return;
}//入队列

void Queue::Pop() {
	Top++;
	return;
}//出队列

CSNode *Queue::Front() {
	return a[Top];
}//取队首元素

bool Queue::Empty() {
	return Top == Tail;
}//判空

void BFS(CSNode *root) {
	printf("The BFS result:\n");
	Queue que;
	que.Clear();
	que.push(root);//根节点入队列
	while (!que.empty()) {//队列不空的时候执行循环
		CSNode *xx = que.front(); //取队首元素
        que.pop();//出队列
		printf("%s\n", xx->data);
		if (xx->nextsibling) {//出队节点的孩子节点若不空则入队列
			que.push(xx->nextsibling);
		}
		if (xx->firstchild) {//同样若孩子节点不空则入队列
			que.push(xx->firstchild);
		}
	}
}

void DFS(CSNode *root) {
	if (!root) return;//递归结束条件
	printf("%s\n", root->data);
	DFS(root->firstchild);//递归遍历孩子节点
	DFS(root->nextsibling);//递归遍历兄弟节点
}

int main()
{
	int j;
//    CSNode *A;
//	A = (CSNode*)malloc(sizeof(CSNode));//根节点创建
	CSNode *A = new CSNode;
	A->firstchild = A->nextsibling = NULL;
	A->data[0] = '0';
	char b[30]; //定义字符数组接收域名
	char *s;
	for (j = 0; j<3; j++)
	{
		printf("Please input the domin:");
		gets(b);
		s = b;//s指向数组b
		_strrev(s);
		insert_one(A, s);//字符串s存入A中	
	}
	BFS(A);//层次优先遍历
	cout<<"The DFS result:\n";
	DFS(A);//深度优先遍历

}
