#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
#define ElemType char

typedef struct TNode
{
	ElemType data[30]; //定义数据域类型为字符数组
    struct TNode *lchild, *rchild; //定义左右孩子节点指针
}TNode, *Tree;


int SearchBST(Tree T, char *key, Tree f, Tree *p)
{
    if (!T)    // 树为空，查找不成功
    {
        *p = f;
        return 0;
    }
    else if(strcmp(key,T->data)==0) // 查找成功 
    {
        *p = T;  //p指向查找到的节点
        return 1;
    }
    else if (strcmp(key,T->data)<0)
        return SearchBST(T->lchild, key, T, p);  //  在左子树中继续查找 
    else
        return SearchBST(T->rchild, key, T, p);  //  在右子树中继续查找 
}

int InsertBST(Tree *T, char *key)
{
    Tree p,s;
    if (!SearchBST(*T, key, NULL, &p)) // 查找不成功
    {
		TNode *s = new TNode;
		strcpy(s->data, key);
        s->lchild = s->rchild = NULL;
        if (!p)
            *T = s;            // 插入s为新的根结点
        else if (strcmp(key,p->data)<0)
            p->lchild = s;    //  插入s为左孩子 
        else
            p->rchild = s;  //  插入s为右孩子
        return 1;
    }
    else
        return 0;  //  树中已有关键字相同的结点，不再插入
}


int Search(TNode *N,char *key)
{  //  查找树中是否存在要插入的节点
    TNode *M;
    M=N;
    while(M!=NULL&&strcmp(M->data,key)!=0)
    {  //  查找终止条件为树为空或者查找的节点数据与待查找的数据相同
        if(strcmp(M->data,key)<0) 
            M=M->rchild;   //  继续查找左子树
        else
            M=M->lchild;  //  继续查找右子树
    }
    if(!M)
		cout<<"查找失败！\n";
    else
		cout<<"查找成功！\n";
}

/* 从二叉排序树中删除结点p，并重接它的左或右子树。 */
int Delete(Tree *p)
{
    Tree q,s;
    if((*p)->rchild==NULL) // 右子树空则只需重接它的左子树（待删结点是叶子也走此分支)
    {
        q=*p;
		*p=(*p)->lchild;
		free(q); // 释放该节点
    }
else if((*p)->lchild==NULL) // 只需重接它的右子树
    {
        q=*p;
        *p=(*p)->rchild;
        free(q);  // 释放该节点
    }
    else // 左右子树均不空
    {
        q=*p;
        s=(*p)->lchild;
        while(s->rchild) // 转左，然后向右到尽头（找待删结点的前驱)
        {
            q=s;
            s=s->rchild;
        }
        strcpy((*p)->data,s->data); // s指向被删结点的直接前驱（将被删结点前驱的值取代被删结点的值）
        if(q!=*p)
            q->rchild=s->lchild; // 重接q的右子树
        else
            q->lchild=s->lchild; //重接q的左子树 
        free(s);
    }
    return 1;
}

int DeleteBST(Tree *T,char *key)
{
    if(!*T) //不存在关键字等于key的数据元素
        return 0;
    else
    {
        if (strcmp(key,(*T)->data)==0) //找到关键字等于key的数据元素 
            return Delete(T);  //调用Delete函数删除该节点
        else if (strcmp(key,(*T)->data)<0)
            return DeleteBST(&(*T)->lchild,key);// 继续访问左子树
        else
            return DeleteBST(&(*T)->rchild,key);//继续访问右子树

    }
}

void InOrder (TNode *root){ //中序遍历该二叉排序树
	if (!root) return ;  //递归结束条件
	InOrder (root->lchild); //递归访问左子树
	cout<<root->data<<endl;
	InOrder (root->rchild);//递归访问右子树
}


void Gongneng(TNode *A)
{
	int k;
	char a[30],c[30],d[30];
	cout<<"选择操作：\n1-查找\n2-删除\n3-插入\n输入：";
	cin>>k;
	switch(k)
	{
	case 1 :
		system("cls");
		cout<<"输入要查找的节点：";
		cin>>c;
	    Search(A, c);//调用查找函数
	    break;
	case 2:
		system("cls");
		cout<<"输入要删除的节点：";
		cin>>a;
		if(!DeleteBST(&A,a))
			cout<<"\n此节点不存在\n";
		else
			{
				cout<<"\n删除节点成功！\n\n删除后树的中序遍历结果如下：\n";
				InOrder(A);
			}//删除后，进行一次遍历检查删除后的二叉排序树
        break;
	case 3:
		system("cls");
		cout<<"请输入要插入的节点：";
		cin>>d;
		if(!InsertBST(&A,d))
			cout<<"插入失败!要插入的节点已存在!\n";
		else
		{
			cout<<"\n插入成功!\n\n插入后树的中序遍历结果如下：\n";
		    InOrder(A);//插入成功后，中序遍历该树
		}
		break;
   default : cout<<"输入数值错误!\n";

	}
}



int main()
{
	TNode *A;
	A = (TNode*)malloc(sizeof(TNode));//A为根节点
	A->lchild = A->rchild= NULL;
	A->data[0] = ' ';
	int j,k,m=1;
	char b[30];
	char *s,*t;
	cout<<"请首先创建一棵树并输入要输入的域名个数：";

	cin>>k;
    for(j=0;j<k;j++)//for循环输入域名
	{
		TNode *X;
		char *str;
		int i;
	    char ZhongZhuan[15];   //定义中转数组
		X = A;
		cout<<"输入域名"<<j+1<<":";
		cin>>b;
		s = b;  //s指向数组b
		_strrev(s); //将该字符数组反转
		for (; s != '\0';)
		{
			str = strchr(s, '.'); //str为字符串s里面首次出现‘.’的位置
			if(str)
			{
				i = str - s;
				ZhongZhuan[i+1]='\0'; 
				for (; i>=0; i--, s++)
				{
					ZhongZhuan[i] = s[0]; //采用倒叙插入，将字符串插入到中转数组里面
				}
			}
			else
			{   //剩余字符串不含’.’，则中转数组的实际大小为剩余字符串的长度
				_strrev(s); 
				i = strlen(s);
				ZhongZhuan[i + 1] = '\0';
				for (; i >= 0; i--)
				{
					ZhongZhuan[i] = s[i]; // 同样采用倒叙插入的方法为中转数组赋值
				}
				s = '\0';
			}
			InsertBST(&A,ZhongZhuan); //将中转数组的信息插入到树中
		}
	}
	cout<<"中序遍历结果为：\n";
	while(m)
	{
		system("cls");
		Gongneng(A);  //调用功能函数
        cout<<"是否继续操作？\t是-请输入1；否-请输入0\n输入:";
		cin>>m;
	}
		system("cls");
}

