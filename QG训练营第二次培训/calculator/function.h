#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#define WINDOWWIDTH 70		// ���ڿ��
#define WINDOWHIGH 40		// ���ڸ߶�
#define MAX 1000		// ʽ�ӳ���
#define MAXBIT 20		// ���֧��20λ�ĵ������ݣ�����С���㣩

typedef int Status;		// �����ж����ȼ�

typedef struct node1      	// �������ֽ��
{
	double data;
	struct node1 * next;
}Node1;

typedef struct node2		// �������Ž��
{
	char data;
	struct node2 * next;
}Node2;

typedef struct stack1		// ����ջ
{
	Node1 * top;
	int quantity;
}Stack1;

typedef struct stack2		// ����ջ
{
	Node2 * top;
	int quantity;
}Stack2;

void push1(Stack1 * stack,double e);		// ������ջ
void push2(Stack2 * stack,char e);		// ������ջ
double pop1(Stack1 * stack);			// ������ջ
char pop2(Stack2 * stack);			// ������ջ
Status priority(char c);			// �ж����ȼ�
void InitStack(Stack1 * num,Stack2 * sign);	// ����ջ��ʼ��
char * s_gets(char * str);			// ���뺯��
void calculate();				// �����������
bool egal(char ch);				// ����+-*/.()=֮��������Ϊ�Ƿ�
bool judge(char * ch);				// ����Ƿ��зǷ�����
void remove_blank(char *ch);			// �޳��ո�
void space_blank_bracket(char * ch);		// �޳�������
bool transit();					// ���ɺ���
void Exit();

void FixedWindow();			// ����cmd����
void gotoxy(int x,int y); 	 	//����ƶ���(x,y)λ��
void DrawBoundary();			// ���Ʊ߿�

#endif // FUNCTION_H_INCLUDED
