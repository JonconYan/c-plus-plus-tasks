#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
struct STACK {
	int  *elems;	//申请内存用于存放栈的元素
	int   max;	//栈能存放的最大元素个数
	int   pos;	//栈实际已有元素个数，栈空时pos=0;
};
void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈
int  size(const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany(const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem(const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈
void main(int argc, char* argv[])
{
	// int argc;
	// scanf("%d",&argc);
	// char argv[20][10];
	// for(int i=1;i<argc;i++)
	// {
	//     scanf("%s",argv[i]);
	// }
	int i = 1;
	const char*s1 = "-S";//设定栈大小
	const char*s2 = "-I";//入栈
	const char*s3 = "-O";//出栈
	const char*s4 = "-C";//深拷贝构造
	const char*s5 = "-A";//深拷贝赋值
	const char*s6 = "-N";//栈中剩余元素个数
	const char*s7 = "-G";//命令“-G  1”表示得到栈中下标为1的元素（即栈的第2个元素）。
	STACK*p = (STACK*)malloc(sizeof(STACK));
	STACK*p_new = NULL;
	while (i != argc)
	{
		if (!strcmp(argv[i], s1))
		{
			cout << "S ";
			i++;
			int num = atoi(argv[i]);
			if (atoi(argv[i]) <= 0)
			{
				cout << "E ";
				exit(0);
			}
			else
			{
				initSTACK(p, num);//atoi为字符串转化为int型数字的函数
				cout << num << ' ';
			}
			i++;//用了argv[1]和argv[2]指针向后移动两次
		}
		else if (!strcmp(argv[i], s2))//此时需要入栈
		{
			cout << "I ";
			i++;
			for (; i < argc&&*argv[i] != '-'; i++)
			{
				if (p->pos == p->max)//每次入栈之前判断是否溢出
				{
					cout << "E ";
					exit(0);
				}
				int num = atoi(argv[i]);
				p = push(p, num);
			}
				//程序应正确
				print(p);
			

		}
		else if (!strcmp(argv[i], s3))//此时需要出栈
		{
			cout << "O ";
			i++;
			int number = atoi(argv[i]);
			if (number > p->pos)
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
					pop(p, e);
				}
				print(p);
				i++;
			}

		}
		else if (!strcmp(argv[i], s4))//此时需要深度拷贝构造
		{
			cout << "C ";
			i++;
			p_new = (STACK*)malloc(sizeof(STACK));
			initSTACK(p_new, p->max);
			for (int j = 0; j < p->max; j++)
			{
				p_new->elems[j] = p->elems[j];
			}
			p_new->pos = p->pos;
			print(p_new);
			p = p_new;
		}
		else if (!strcmp(argv[i], s5))//此时需要深度拷贝赋值
		{
			cout << "A ";
			i++;
			int num = atoi(argv[i]);
			num = num < p->pos ? num : p->pos;//取两者拥有的最小值
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
				print(p);
			}
			i++;
		}
		else if (!strcmp(argv[i], s6))
		{
			cout << "N " << p->pos << ' ';
			i++;
		}
		else if (!strcmp(argv[i], s7))
		{
			cout << "G ";
			i++;
			int num = atoi(argv[i]);
			if (num + 1 <= p->pos)
			{
				cout << p->elems[num] << ' ';
				i++;
			}
			else
			{
				cout << "E ";
				exit(0);
			}
		}

	}
	free(p);
}

void initSTACK(STACK *const p, int m)
{
	p->max = m;
	p->pos = 0;
	p->elems = (int*)malloc(m * sizeof(int));
}

void initSTACK(STACK *const p, const STACK&s)
{
	p->max = s.max;
	p->pos = s.pos;
	p->elems = s.elems;
}

int  size(const STACK *const p)		//返回p指向的栈的最大元素个数max
{
	return p->max;
}

int  howMany(const STACK *const p)	//返回p指向的栈的实际元素个数pos
{
	return p->pos;
}

int  getelem(const STACK *const p, int x)	//取下标x处的栈元素
{
	return p->elems[x];
}

STACK *const push(STACK *const p, int e) 	//将e入栈，并返回p
{
	p->elems[p->pos] = e;
	p->pos++;
	return p;
}

STACK *const pop(STACK *const p, int &e) 	//出栈到e，并返回p
{
	e = p->elems[p->pos - 1];
	p->pos--;
	return p;
}

STACK *const assign(STACK*const p, const STACK&s) //赋s给p指的栈,并返回p
{
	*p = s;
	return p;
}

void print(const STACK*const p)			//打印p指向的栈
{
	for (int i = 0; i < p->pos; i++)
	{
		cout << p->elems[i] << ' ';
	}
}

void destroySTACK(STACK*const p)		//销毁p指向的栈
{
	delete(p->elems);
	delete(p);
}