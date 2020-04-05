#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#define WINDOWWIDTH 70		// 窗口宽度
#define WINDOWHIGH 40		// 窗口高度
#define MAX 1000		// 式子长度
#define MAXBIT 20		// 最多支持20位的单个数据（包括小数点）

typedef int Status;		// 用于判断优先级

typedef struct node1      	// 创建数字结点
{
	double data;
	struct node1 * next;
}Node1;

typedef struct node2		// 创建符号结点
{
	char data;
	struct node2 * next;
}Node2;

typedef struct stack1		// 数字栈
{
	Node1 * top;
	int quantity;
}Stack1;

typedef struct stack2		// 符号栈
{
	Node2 * top;
	int quantity;
}Stack2;

void push1(Stack1 * stack,double e);		// 进数字栈
void push2(Stack2 * stack,char e);		// 进符号栈
double pop1(Stack1 * stack);			// 出数字栈
char pop2(Stack2 * stack);			// 出符号栈
Status priority(char c);			// 判断优先级
void InitStack(Stack1 * num,Stack2 * sign);	// 两个栈初始化
char * s_gets(char * str);			// 输入函数
void calculate();				// 计算的主函数
bool egal(char ch);				// 除了+-*/.()=之外的输入皆为非法
bool judge(char * ch);				// 检测是否有非法输入
void remove_blank(char *ch);			// 剔除空格
void space_blank_bracket(char * ch);		// 剔除空括号
bool transit();					// 过渡函数
void Exit();

void FixedWindow();			// 设置cmd窗口
void gotoxy(int x,int y); 	 	//光标移动到(x,y)位置
void DrawBoundary();			// 绘制边框

#endif // FUNCTION_H_INCLUDED
