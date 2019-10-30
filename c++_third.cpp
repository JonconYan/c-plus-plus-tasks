
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
class STACK {
	int* const elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK() :max(5), elems((int*)malloc(sizeof(int) * 5)), pos(0) {};
	STACK(int m) :max(m), elems((int*)malloc(sizeof(int)*m)) { pos = 0; }		//初始化栈：最多存m个元素
	STACK(const STACK&s) :max(s.max), elems(s.elems) { pos = s.pos; } 			//用栈s拷贝初始化栈
	//STACK(STACK&&s);       			//移动构造
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
		//if (s.max <= max)
		//{
		//	int*p = (int*)&max;
		//	*p = s.max;
		//	pos = s.pos;
		//	for (int i = 0; i < s.pos; i++)
		//	{
		//		elems[i] = s.elems[i];
		//	}
		//}
		//else
		//{
		int*p = (int*)&max;
		*p = s.max;
		pos = s.pos;
		free(elems);
		int**q = (int**)&elems;
		*q = (int*)malloc(s.max * sizeof(int));
		for (int i = 0; i < s.pos; i++)
		{
			elems[i] = s.elems[i];
		}
		/*}*/

		return *this;
	}
	//virtual STACK &operator=(STACK&&s);  //移动赋值
	virtual void print() const			//打印栈
	{
		for (int i = 0; i < pos; i++)
			cout << elems[i] << ' ';
	}
	virtual ~STACK()					//销毁栈
	{
		if (this->elems)
		{
			free(this->elems);
			*(int*)&(this->elems) = 0;
		}
	}

};
class QUEUE {
	STACK s1, s2;
	//s1用于入队 s2用于出队
	int delete_num = 0;
public:
	QUEUE(int m) { STACK temp(m); s1 = temp; s2 = temp; }; //每个栈最多m个元素，要求实现的队列最多能入2m个元素
	QUEUE(const QUEUE&q) {}; 			//用队列q拷贝初始化队列
	QUEUE(QUEUE&&q);				//移动构造
	virtual operator int() const { return int(s1) + int(s2); };			//返回队列的实际元素个数
	virtual int full() const { return (int(s1) == s1.size()) && int(s2); };		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const //取下标为x的元素,第1个元素下标为0
	{
		if (x + 1 <= int(s2))
			return s2[int(s2) - x - 1];
		else
			return s1[x - int(s2)];
	};
	virtual QUEUE& operator<<(int e) 	//将e入队列,并返回队列
	{
		if (int(s1) < s1.size())
		{
			s1 << e;
		}
		else if ((int)s1 == s1.size() && !int(s2))//如果第一个栈满且第二个栈为空则将第一个栈出到第二个再进队
		{
			int temp;
			int l = int(s1);
			for (int i = 0; i < l; i++)
			{
				s1 >> temp;
				s2 << temp;
			}
			s1 << e;
		}
		return *this;
	}
	virtual QUEUE& operator>>(int &e)	//出队列到e,并返回队列
	{
		//先考虑s2是否为空 如果为空则将s1先赋给s2 然后再出队 否则直接出队
		if (int(s2))//非空
			s2 >> e;
		else
		{
			int temp;
			int l = int(s1);
			for (int i = 0; i < l; i++)
			{
				s1 >> temp;
				s2 << temp;
			}
			s2 >> e;
		}
		return *this;
	}
	//virtual QUEUE& operator=(const QUEUE&q); //赋q给队列,并返回被赋值的队列
	//virtual QUEUE& operator=(QUEUE&&q);	//移动赋值
	virtual void print() const			//打印队列
	{
		for (int i = int(s2) - 1; i >= 0; i--)
		{
			cout << s2[i] << ' ';
		}
		s1.print();
	}
	virtual ~QUEUE()					//销毁队列
	{
		if (!delete_num)
		{
			s1.~STACK();
			s2.~STACK();
		}
	}
};


void main(int argc, char* argv[])
{
	int i = 3;
	const char*s1 = "-S";//设定队列大小
	const char*s2 = "-I";//入对
	const char*s3 = "-O";//出队
	const char*s4 = "-C";//深拷贝构造
	const char*s5 = "-A";//深拷贝赋值
	const char*s6 = "-N";//队列中剩余元素个数
	const char*s7 = "-G";//命令“-G  1”表示得到栈中下标为1的元素（即队列的第2个元素）。
	cout << "S ";
	cout << atoi(argv[2]) << ' ';
	QUEUE que(atoi(argv[2]));
	while (i != argc)
	{
		if (!strcmp(argv[i], s2))//此时需要入队列
		{
			cout << "I ";
			i++;
			for (; i < argc&&*argv[i] != '-'; i++)
			{
				if (que.full())//每次入队列之前判断是否溢出
				{
					cout << "E ";
					exit(0);
				}
				int num = atoi(argv[i]);
				que << num;
			}
			//程序应正确
			que.print();
		}
		else if (!strcmp(argv[i], s3))//此时需要出队
		{
			cout << "O ";
			i++;
			int number = atoi(argv[i]);
			if (number > int(que))
			{
				cout << "E ";
				exit(0);
			}
			else
			{
				//可以做此动作
				int e;
				for (int j = 0; j < number; j++)
				{
					que >> e;
				}
				que.print();
				i++;
			}

		}
		else if (!strcmp(argv[i], s4))//此时需要深度拷贝构造
		{
			cout << "C ";
			i++;
			// p_new = (STACK*)malloc(sizeof(STACK));
			// initSTACK(p_new, p->max);
			// for (int j = 0; j < p->max; j++)
			// {
			// 	p_new->elems[j] = p->elems[j];
			// }
			// p_new->pos = p->pos;
			//STACK stk_new(stk.size());
			//for (int j = 0; j < int(stk); j++)
			//{
			//	stk_new << stk[j];
			//}
			//stk = stk_new;
			que.print();

		}
		else if (!strcmp(argv[i], s5))//此时需要深度拷贝赋值
		{
			cout << "A ";
			i++;
			int num = atoi(argv[i]);
			num = num < int(que) ? num : int(que);//取两者拥有的最小值
			if (num <= 0)
			{
				cout << "E ";
				exit(0);
			}
			//else if (p_new)//此时新栈中已经存在元素
			//{
			//	print(p);
			//}
			else
			{
				//STACK*q = (STACK*)malloc(sizeof(STACK));//分配新栈
				//initSTACK(q, p->max);
				//for (int j = 0; j < num; j++)
				//{
				//	q->elems[j] = p->elems[j];
				//}
				//q->pos = num;
				//destroySTACK(p);
				//p = q;
				que.print();
			}
			i++;
		}
		else if (!strcmp(argv[i], s6))
		{
			cout << "N " << int(que) << ' ';
			i++;
		}
		else if (!strcmp(argv[i], s7))
		{
			cout << "G ";
			i++;
			int num = atoi(argv[i]);
			if (num + 1 <= int(que))
			{
				cout << que[num] << ' ';
				i++;
			}
			else
			{
				cout << "E ";
				exit(0);
			}
		}

	}
}