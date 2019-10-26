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
		if(s.max<=max)
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
			int*p=(int*)&max;
			*p=s.max;
			pos=s.pos;
			free(elems);
			int**q=&elems;
			*q=(int*)malloc(s.max*sizeof(int));
			for (int i = 0; i < s.pos; i++)
			{
				elems[i] = s.elems[i];
			}
		}
		
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
		free(this->elems);
	}
};
void main(int argc, char* argv[])
{
	int i = 3;
	const char*s1 = "-S";//设定栈大小
	const char*s2 = "-I";//入栈
	const char*s3 = "-O";//出栈
	const char*s4 = "-C";//深拷贝构造
	const char*s5 = "-A";//深拷贝赋值
	const char*s6 = "-N";//栈中剩余元素个数
	const char*s7 = "-G";//命令“-G  1”表示得到栈中下标为1的元素（即栈的第2个元素）。
	cout << "S ";
	cout << atoi(argv[2])<<' ';
	STACK stk(atoi(argv[2]));//第一个参数必定为创建栈
	while (i != argc)
	{
		if (!strcmp(argv[i], s2))//此时需要入栈
		{
			cout << "I ";
			i++;
			for (; i < argc&&*argv[i] != '-'; i++)
			{
				if (int(stk) == stk.size())//每次入栈之前判断是否溢出
				{
					cout << "E ";
					exit(0);
				}
				int num = atoi(argv[i]);
				stk << num;
			}
			//程序应正确
			stk.print();
		}
		else if (!strcmp(argv[i], s3))//此时需要出栈
		{
			cout << "O ";
			i++;
			int number = atoi(argv[i]);
			if (number > int(stk))
			{
				cout << "E ";
				exit(0);
			}
			else
			{
				//可以做此动作
				for (int j = 0; j < number; j++)
				{
					int e;
					stk >> e;
				}
				stk.print();
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
			STACK stk_new(stk.size());
			for (int j = 0; j < int(stk); j++)
			{
				stk_new << stk[j];
			}
			stk = stk_new;
			stk.print();

		}
		else if (!strcmp(argv[i], s5))//此时需要深度拷贝赋值
		{
			cout << "A ";
			i++;
			int num = atoi(argv[i]);
			num = num < int(stk) ? num : int(stk);//取两者拥有的最小值
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
				stk.print();
			}
			i++;
		}
		else if (!strcmp(argv[i], s6))
		{
			cout << "N " << int(stk) << ' ';
			i++;
		}
		else if (!strcmp(argv[i], s7))
		{
			cout << "G ";
			i++;
			int num = atoi(argv[i]);
			if (num + 1 <= int(stk))
			{
				cout << stk[num] << ' ';
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