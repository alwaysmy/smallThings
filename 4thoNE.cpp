#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
#define ElemType char

typedef struct TNode
{
	ElemType data[30]; //��������������Ϊ�ַ�����
    struct TNode *lchild, *rchild; //�������Һ��ӽڵ�ָ��
}TNode, *Tree;


int SearchBST(Tree T, char *key, Tree f, Tree *p)
{
    if (!T)    // ��Ϊ�գ����Ҳ��ɹ�
    {
        *p = f;
        return 0;
    }
    else if(strcmp(key,T->data)==0) // ���ҳɹ� 
    {
        *p = T;  //pָ����ҵ��Ľڵ�
        return 1;
    }
    else if (strcmp(key,T->data)<0)
        return SearchBST(T->lchild, key, T, p);  //  ���������м������� 
    else
        return SearchBST(T->rchild, key, T, p);  //  ���������м������� 
}

int InsertBST(Tree *T, char *key)
{
    Tree p,s;
    if (!SearchBST(*T, key, NULL, &p)) // ���Ҳ��ɹ�
    {
		TNode *s = new TNode;
		strcpy(s->data, key);
        s->lchild = s->rchild = NULL;
        if (!p)
            *T = s;            // ����sΪ�µĸ����
        else if (strcmp(key,p->data)<0)
            p->lchild = s;    //  ����sΪ���� 
        else
            p->rchild = s;  //  ����sΪ�Һ���
        return 1;
    }
    else
        return 0;  //  �������йؼ�����ͬ�Ľ�㣬���ٲ���
}


int Search(TNode *N,char *key)
{  //  ���������Ƿ����Ҫ����Ľڵ�
    TNode *M;
    M=N;
    while(M!=NULL&&strcmp(M->data,key)!=0)
    {  //  ������ֹ����Ϊ��Ϊ�ջ��߲��ҵĽڵ�����������ҵ�������ͬ
        if(strcmp(M->data,key)<0) 
            M=M->rchild;   //  ��������������
        else
            M=M->lchild;  //  ��������������
    }
    if(!M)
		cout<<"����ʧ�ܣ�\n";
    else
		cout<<"���ҳɹ���\n";
}

/* �Ӷ�����������ɾ�����p�����ؽ���������������� */
int Delete(Tree *p)
{
    Tree q,s;
    if((*p)->rchild==NULL) // ����������ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧)
    {
        q=*p;
		*p=(*p)->lchild;
		free(q); // �ͷŸýڵ�
    }
else if((*p)->lchild==NULL) // ֻ���ؽ�����������
    {
        q=*p;
        *p=(*p)->rchild;
        free(q);  // �ͷŸýڵ�
    }
    else // ��������������
    {
        q=*p;
        s=(*p)->lchild;
        while(s->rchild) // ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ��)
        {
            q=s;
            s=s->rchild;
        }
        strcpy((*p)->data,s->data); // sָ��ɾ����ֱ��ǰ��������ɾ���ǰ����ֵȡ����ɾ����ֵ��
        if(q!=*p)
            q->rchild=s->lchild; // �ؽ�q��������
        else
            q->lchild=s->lchild; //�ؽ�q�������� 
        free(s);
    }
    return 1;
}

int DeleteBST(Tree *T,char *key)
{
    if(!*T) //�����ڹؼ��ֵ���key������Ԫ��
        return 0;
    else
    {
        if (strcmp(key,(*T)->data)==0) //�ҵ��ؼ��ֵ���key������Ԫ�� 
            return Delete(T);  //����Delete����ɾ���ýڵ�
        else if (strcmp(key,(*T)->data)<0)
            return DeleteBST(&(*T)->lchild,key);// ��������������
        else
            return DeleteBST(&(*T)->rchild,key);//��������������

    }
}

void InOrder (TNode *root){ //��������ö���������
	if (!root) return ;  //�ݹ��������
	InOrder (root->lchild); //�ݹ����������
	cout<<root->data<<endl;
	InOrder (root->rchild);//�ݹ����������
}


void Gongneng(TNode *A)
{
	int k;
	char a[30],c[30],d[30];
	cout<<"ѡ�������\n1-����\n2-ɾ��\n3-����\n���룺";
	cin>>k;
	switch(k)
	{
	case 1 :
		system("cls");
		cout<<"����Ҫ���ҵĽڵ㣺";
		cin>>c;
	    Search(A, c);//���ò��Һ���
	    break;
	case 2:
		system("cls");
		cout<<"����Ҫɾ���Ľڵ㣺";
		cin>>a;
		if(!DeleteBST(&A,a))
			cout<<"\n�˽ڵ㲻����\n";
		else
			{
				cout<<"\nɾ���ڵ�ɹ���\n\nɾ���������������������£�\n";
				InOrder(A);
			}//ɾ���󣬽���һ�α������ɾ����Ķ���������
        break;
	case 3:
		system("cls");
		cout<<"������Ҫ����Ľڵ㣺";
		cin>>d;
		if(!InsertBST(&A,d))
			cout<<"����ʧ��!Ҫ����Ľڵ��Ѵ���!\n";
		else
		{
			cout<<"\n����ɹ�!\n\n����������������������£�\n";
		    InOrder(A);//����ɹ��������������
		}
		break;
   default : cout<<"������ֵ����!\n";

	}
}



int main()
{
	TNode *A;
	A = (TNode*)malloc(sizeof(TNode));//AΪ���ڵ�
	A->lchild = A->rchild= NULL;
	A->data[0] = ' ';
	int j,k,m=1;
	char b[30];
	char *s,*t;
	cout<<"�����ȴ���һ����������Ҫ���������������";

	cin>>k;
    for(j=0;j<k;j++)//forѭ����������
	{
		TNode *X;
		char *str;
		int i;
	    char ZhongZhuan[15];   //������ת����
		X = A;
		cout<<"��������"<<j+1<<":";
		cin>>b;
		s = b;  //sָ������b
		_strrev(s); //�����ַ����鷴ת
		for (; s != '\0';)
		{
			str = strchr(s, '.'); //strΪ�ַ���s�����״γ��֡�.����λ��
			if(str)
			{
				i = str - s;
				ZhongZhuan[i+1]='\0'; 
				for (; i>=0; i--, s++)
				{
					ZhongZhuan[i] = s[0]; //���õ�����룬���ַ������뵽��ת��������
				}
			}
			else
			{   //ʣ���ַ���������.��������ת�����ʵ�ʴ�СΪʣ���ַ����ĳ���
				_strrev(s); 
				i = strlen(s);
				ZhongZhuan[i + 1] = '\0';
				for (; i >= 0; i--)
				{
					ZhongZhuan[i] = s[i]; // ͬ�����õ������ķ���Ϊ��ת���鸳ֵ
				}
				s = '\0';
			}
			InsertBST(&A,ZhongZhuan); //����ת�������Ϣ���뵽����
		}
	}
	cout<<"����������Ϊ��\n";
	while(m)
	{
		system("cls");
		Gongneng(A);  //���ù��ܺ���
        cout<<"�Ƿ����������\t��-������1����-������0\n����:";
		cin>>m;
	}
		system("cls");
}

