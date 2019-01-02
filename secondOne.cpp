#include <iostream>
#include <cstring>
using namespace std;
typedef char data;
#define MaxSize 10
typedef  struct Queue{
    int first;
    int trail;
    int len;
    data Queue_List[MaxSize];
}Queue;
void initQueue(Queue &que);
void addQueue(Queue &que,char val);
bool isFull(const Queue &que);
bool isEmpty(Queue &que);
void showQueue(Queue &que);
data out_Queue(Queue &que);
int main()
{
    Queue men;
    Queue women;
    initQueue(men);
    initQueue(women);
    char m,w;
    int k,n,o;
    cout<<"初始化男生队列："<<endl;
    cout<<"请输入你想入队的人数(最多10人)：";
    cin>>k;
    men.len = k;
    cout<<"请依次输入入队信息：";
    for(int i=0;i<k;i++)
    {
        cin>>m;
        addQueue(men, m);
    }
    for(int i=k;i<MaxSize-1;i++)
        addQueue(men, '\0');
    cout<<"初始化女生队列："<<endl;
    cout<<"请输入你想入队的人数："<<endl;
    cin>>n;
    women.len = n;
    cout<<"请依次输入入队信息：";
    for(int i=0;i<n;i++)
    {
        cin>>w;
        addQueue(women, w);
    }
    for(int i=n;i<MaxSize-1;i++)
        addQueue(women, '\0');
    cout<<"请输出配对伦数：";
    cin>>o;
    for(int i=0;i<o;i++)
    {
        cout<<"第"<<(i+1)<<"次配对："<<endl;
        if(men.len>=women.len)
        {
            while(1)
            {
                if(!men.Queue_List[men.first])
                    men.first=0;
                if(women.Queue_List[women.first])
                {
                    m = out_Queue(men);
                    w = out_Queue(women);
                    cout<<"("<<m<<","<<w<<")"<<endl;
                }
                else
                {
                    for(int u=men.first;u<men.len;u++)
                        cout<<"男队"<<men.Queue_List[u]<<"轮空"<<endl;
                    break;
                }
            }
            women.first=0;
        }
        else{
            while(1)
            {
                if(!women.Queue_List[men.first])
                    women.first=0;
                if(men.Queue_List[men.first])
                {
                    m = out_Queue(men);
                    w = out_Queue(women);
                    cout<<"("<<m<<","<<w<<")"<<endl;
                }
                else
                {
                    for(int u=women.first;u<women.len;u++)
                        cout<<"女队"<<women.Queue_List[u]<<"轮空"<<endl;
                    break;
                }
            }
        men.first=0;
        }
    }
    return 0;
}
void initQueue(Queue &que)
{
    que.first = 0;
    que.trail = 0;
}
bool isFull(const Queue &que)
{
    if(que.first == (que.trail+1)%MaxSize)
        return true;
    return false;
}
bool isEmpty(Queue &que)
{
    if (que.first == que.trail)
        return true;
    return false;
}
void addQueue(Queue &que,char val)
{
    if(isFull(que))
    {
        cout<<"Queue is already full.";
        return;
    }
    que.Queue_List[que.trail] = val;
    que.trail = (que.trail+1)%MaxSize;
}
data out_Queue(Queue &que)
{
    char a;
    if(isEmpty(que)){
        que.first = (que.first+1)%MaxSize;
        return que.Queue_List[que.first];
    }
    else
    {
        a = que.Queue_List[que.first];
        que.first = (que.first+1)%MaxSize;
        return a;
    }
}
void showQueue(Queue que)
{
    cout<<"队列存储元素为：";
    for(int i=0;i<que.len;i++)
        cout<<que.Queue_List[i]<<" ";
    cout<<endl;
}

