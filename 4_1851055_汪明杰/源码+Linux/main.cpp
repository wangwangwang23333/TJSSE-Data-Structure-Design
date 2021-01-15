#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdio>
#include"Stack.h"

using namespace std;

//运算符
enum OPERATORS 
{ 
	EQU, LP, RP, POS, NEG, ADD, SUB, MUL, DIV, POW, MOD 
};

static const char order[11][11] = {  //优先级表
	'=', '<', 'x', '<', '<', '<', '<', '<', '<', '<', '<',
	'x', '<', '=', '<', '<', '<', '<', '<', '<', '<', '<',
	'>', '?', '>', 'x', 'x', '>', '>', '>', '>', '>', '>',
	'>', '<', '>', '<', '<', '>', '>', '>', '>', '>', '>',
	'>', '<', '>', '<', '<', '>', '>', '>', '>', '>', '>',
	'>', '<', '>', '<', '<', '>', '>', '<', '<', '<', '<',
	'>', '<', '>', '<', '<', '>', '>', '<', '<', '<', '<',
	 '>', '<', '>', '<', '<', '>', '>', '>', '>', '<', '>',
	 '>', '<', '>', '<', '<', '>', '>', '>', '>', '<', '>',
	'>', '<', '>', '<', '<', '>', '>', '>', '>', '>', '>',
	 '>', '<', '>', '<', '<', '>', '>', '>', '>', '<', '>'
};

double calculate(OPERATORS op, double op1, double op2)
{
	switch (op) 
	{
	case POS: 
		return op1;
	case NEG: 
		//负数
		return -op1;
	case ADD: 
		//相加
		return op1 + op2;
	case SUB: 
		//相减
		return op1 - op2;
	case MUL: 
		//相乘
		return op1 * op2;
	case POW: 
		//幂次
		return pow(op1, op2);
	case DIV:
		//相除
		if (op2 == 0) 
		{
			printf("\n除数不能为0");
			exit(-1);
		}
		return op1 / op2;
	case MOD:
		//求模
		if (op2 == 0) 
		{
			printf("\n除数不能为0");
			exit(-1);
		}
		return fmod(op1, op2);
	}
	return 0;
}

OPERATORS dispatch(char op, int lastObj)
{
	switch (op) 
	{
	case '+': 
		return ((lastObj == -1 || lastObj == RP) ? ADD : POS);
	case '-': 
		return ((lastObj == -1 || lastObj == RP) ? SUB : NEG);
	case '*': 
		return MUL;
	case '/': 
		return DIV;
	case '^': 
		return POW;
	case '%': 
		return MOD;
	case '=':
	case '\0': 
		return EQU;
	case '(':
		if (lastObj == RP) 
		{
			printf("\n与上一个右括号间没有运算符");
			exit(-1);
		}
		return LP;
	case ')':
		if (lastObj == LP) 
		{
			printf("\n两个括号里没有内容");
			exit(-1);
		}
		return RP;
	default: 
		printf("\n尚不支持该运算符！");
		exit(-1);
	}
}

double dealWith(const char *s)
{
	Stack<double> opnd;
	Stack<OPERATORS> optr;

	//添加等号运算符
	int lastObj = EQU;
	optr.push(EQU);

	//递归判断
	while (!optr.empty()) 
	{
		while (isblank(*s)) 
			s++;
		if (isdigit(*s)) 
		{  
			//如果是数字
			double x; int len;
			sscanf(s, "%lf%n", &x, &len);
			opnd.push(x);
			s += len;
			lastObj = -1;
		}
		else 
		{  
			//如果是操作符
			OPERATORS newOp = dispatch(*s, lastObj);
			switch (order[optr.top()][newOp]) 
			{
			case '<':
				optr.push(newOp); s++;
				lastObj = newOp; break;
			case '=': //退栈
				optr.pop(); s++;
				lastObj = newOp; break;
			case '>': 
			{
				OPERATORS op = optr.top(); optr.pop();
				if (op == POS || op == NEG) 
				{
					double opnd1 = opnd.top(); opnd.pop();
					opnd.push(calculate(op, opnd1, 0));
				}
				else 
				{
					double opnd2 = opnd.top(); opnd.pop();
					double opnd1 = opnd.top(); opnd.pop();
					opnd.push(calculate(op, opnd1, opnd2));
				} break;
			}
			default: 
				cerr << "请检查表达式是否有误" << endl; 
				exit(-1);
			}
		}
	}
	return opnd.top();
}

//测试函数
void test(const char* str, double correctAnswer)
{
	static int index = 1;
	double calculateAnswer = dealWith(str);
	printf("-----------------------------------------------------------------\n");
	printf("%2d    %-10s   \t", index, str);
	cout << calculateAnswer;
	printf("          \t");
	cout << correctAnswer;
	printf("        \t%s\n", ((correctAnswer - calculateAnswer) < 1e-6 ? "T" : "F"));
	++index;
}


int main()
{
	//测试
	printf("序号    表达式       \t计算答案   \t正确答案     \t正确性\n");
	
	//加减法测试
	test("1+2=", 3);
	test("1.9+3.1=", 5);
	test("6-3=", 3);
	test("2-4=", -2);
	test("-0.3+2.2=", 1.9);
	test("1.6-2.7=", -1.1);

	//乘除法测试
	test("2*10=", 20);
	test("-6*3=", -18);
	test("0.6*0.1=", 0.06);
	test("4/4=", 1);
	test("-8/2=", -4);
	test("2/4=", 0.5);
	test("0.78/0.2=", 3.9);
	
	//幂运算和模运算
	test("2^3=", 8);
	test("0.6^2=", 0.36);
	test("6%2=", 0);
	test("7%6=", 1);
	test("21%5=", 1);

	//带括号的运算
	test("(2+1)*3=", 9);
	test("1-(2+3)=", -4);
	test("2*(1+3/(6-5))=", 8);
	test("(6-4)%4=", 2);

	//不带等号的运算
	test("6-2*3", 0);
	test("10-(2+3)/2", 7.5);
	

	//手动输入结果
	printf("\n24个样例测试完毕\n现在请手动输入表达式：");
	string expression;
	cin >> expression;
	printf("计算结果：");
	cout << dealWith(expression.c_str());

	cin.clear();
	cin.ignore(1024, '\n');
	cout << endl << "Enter to Exit";
	cin.get();
	
	return 0;
}