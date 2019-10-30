#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
class STACK {
	int* const elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m) :max(m), elems((int*)malloc(sizeof(int)*m)) { pos = 0; }		//初始化栈：最多存m个元素
	STACK(const STACK&s) :max(s.max), elems(s.elems) { pos = s.pos; } 			//用栈s拷贝初始化栈
	STACK(STACK&&s) : max(s.max), elems(s.elems), pos(s.pos)     			//移动构造
	{
		int**p = (int**)&s.elems;
		*p = nullptr;
	}
	STACK() :max(0), elems(nullptr), pos(0) {};
	virtual int  size() const { return max; }			//返回栈的最大元素个数max
	virtual operator int() const { return pos; }			//返回栈的实际元素个数pos
	virtual int operator[ ] (int x) const
	{
		if (x < pos)
			return elems[x];
		else
			return 12138;//错误代码
	}//取下标x处的栈元素，第1个元素x=0
	virtual STACK& operator<<(int e)
		//将e入栈,并返回栈
	{
		if (pos < max)
		{
			elems[pos] = e;
			pos++;
			return *this;
		}
	}
	virtual STACK& operator>>(int &e)//出栈到e,并返回栈
	{
		if (pos >= 1)
		{
			pos--;
			e = elems[pos];
			return *this;
		}
	}
	virtual STACK& operator=(const STACK&s) //赋s给栈,并返回被赋值栈
	{
		if (s.max <= max)
		{
			int*p = (int*)&max;
			*p = s.max;
			pos = s.pos;
			for (int i = 0; i < s.pos; i++)
			{
				elems[i] = s.elems[i];
			}
		}
		else
		{
			int*p = (int*)&max;
			*p = s.max;
			pos = s.pos;
			if(elems)
			free(elems);
			int**q = (int**)&elems;
			*q = (int*)malloc(s.max * sizeof(int));
			for (int i = 0; i < s.pos; i++)
			{
				elems[i] = s.elems[i];
			}
		}

		return *this;
	}
	virtual STACK &operator=(STACK&&s)  //移动赋值
	{
		return *this;
	}
	virtual void print() const			//打印栈
	{
		for (int i = 0; i < pos; i++)
			cout << elems[i] << ' ';
	}
	virtual ~STACK()					//销毁栈
	{
		if (this->elems)
		{
			free(elems);
			int**p = (int**)&elems;
			*p = 0;
		}
	}
};
class QUEUE:public STACK {
	STACK  s;//这个当做s2
	int delete_num = 0;
public:
	QUEUE(int m):STACK(m), s(STACK(m)) //每个栈最多m个元素，要求实现的队列最多能入2m个元素
	{}
	QUEUE(const QUEUE&q):STACK((STACK)q),s(q.s) 			//用队列q拷贝初始化队列
	{}
	QUEUE(QUEUE&&q) :s(q.s), STACK(move((STACK)q)) {}				//移动构造
	virtual operator int() const { return int(s) + STACK::operator int(); };			//返回队列的实际元素个数
	virtual int full() const { return (STACK::operator int() == STACK::size()) && int(s); };		       //返回队列是否已满，满返回1，否则0
	virtual int operator[ ](int x)const   //取下标为x的元素，第1个元素下标为0
	{
		if (x + 1 <= int(s))
			return s[int(s) - x-1];
		else
			return STACK::operator[](x - int(s));
	}
	virtual QUEUE& operator<<(int e)  //将e入队列,并返回队列
	{
		if (STACK::operator int() < STACK::size())
		{
			STACK::operator<< (e);
		}
		else if (STACK::operator int() == STACK::size() && !int(s))
		{
			int temp;
			int l = STACK::operator int();
			for (int i = 0; i < l; i++)
			{
				STACK::operator>>(temp);
				s << temp;
			}
			STACK::operator<<(e);
		}
		return *this;
	}
	virtual QUEUE& operator>>(int &e)	//出队列到e,并返回队列
	{
		//先考虑s2是否为空 如果为空则将s1先赋给s2 然后再出队 否则直接出队
		if (int(s))//非空
			s >> e;
		else
		{
			int temp;
			int l = STACK::operator int();
			for (int i = 0; i < l; i++)
			{
				STACK::operator>>(temp);
				s << temp;
			}
			s >> e;
		}
		return *this;
	}
	virtual QUEUE& operator=(const QUEUE&q) //赋q给队列,并返回被赋值队列
	{
		if (s == *this)
		{
			return *this;
		}
		else
		{
			STACK::operator=((STACK)q);
			s = q.s;
		}

	}
	//virtual QUEUE& operator=(QUEUE&&q);  //移动赋值
	virtual void print() const			//打印队列
	{
		for (int i = int(s) - 1; i >= 0; i--)
		{
			cout << s[i] << ' ';
		}
		STACK::print();
	}
	virtual ~QUEUE()					//销毁队列
	{
		if (!delete_num)
		{
			s.~STACK();
			STACK::~STACK();
			delete_num++;
		}
	}
};

using namespace std;
int main()
{
    int M,F,m,f;
    cout<<"Input number M:";
    cin>>M;
    cout<<"Input number F:";
    cin>>F;
    QUEUE man(M),woman(F);
    cout<<"----couple-----"<<endl;
    cout<<"m:";
    cin>>m;
    cout<<"f:";
    cin>>f;
    int i=1;
    for(i=1;i <= M;i++)
    {
        man<<i;
    }
    for(i=1;i <= F;i++)
    {
        woman<<i;
    }
    for(i=1;;i++)
    {
        int temp_m;
        int temp_f;
        man>>temp_m;
        woman>>temp_f;
        cout<<"the number of song:"<<i<<endl;
        cout<<"this man  :"<<temp_m<<endl;
        cout<<"this woman:"<<temp_f<<endl;
        if(!(temp_m-m)&&!(temp_f-f))
        break;
        else
        {
            man<<temp_m;
            woman<<temp_f;
        }
        
    }
    cout<<"the number of song when they meet:"<<i<<endl;
    return 0;
}