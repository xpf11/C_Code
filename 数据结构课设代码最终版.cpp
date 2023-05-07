#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;


typedef struct ListNode //结构体，双向链表
{  
	int data;//结构体数据             
	struct ListNode *pre; //前指针ci
	struct ListNode *next;//后指针
}Node, *NodeList;

int check(char a[], int m)//检查函数用来判断输入的数字格式是否正确,输入正确返回1，不正确返回-1
{
    if(a[0] == '+' || a[0] == '-')//第一个字符为符号位
	{
        for(int i = 1; i < m; i++)
		{
            if((int(a[i]) <= 57 && int(a[i]) >= 48) || a[i] == ',')//其余每一位均在0-9之间或者是逗号
			{
                if(i == m-1)
                    return 1;
            }
            else
                return -1;
        }
    }
	else
        return -1;
}


void input(NodeList &longint)//输入函数字符串型长整数,去掉分隔符后存入链表中-
{

    longint = new Node;
    longint -> pre = longint; //初始化结构体变量
    longint -> next = longint;
    int flag1 = 0;
    int num = 0;//用来存放临时数
    int len = 0;//字符串长度
    string str;
    char arr[1000];//字符数组来存放长整型
    cin >> str;//输入一个字符串

    len = str.length();
    for(int i = 0; i < len; i++)//将字符串赋值给字符数组，调用check函数
	{
        arr[i] = str[i];
    }
    flag1 = check(arr, len);//调用check函数
    while(flag1 == -1)//当输入格式不正确时提示，重新输入直至输入格式正确
	{
        cout << "请重新按照格式输入这个长整数！" << endl;
        cin >> str;
        len = str.length();
        for(int i = 0; i < len; i++){
            arr[i] = str[i];
        }
        flag1 = check(arr, len);
    }

    if(arr[0] == '+')//当第一个字符为'+'存储为整型43
	{
        longint->data = int('+');
    }
    if(arr[0] == '-')//当第一个字符为'-'存储为整型45
	{
        longint->data = int('-');
    }
	int i;
    NodeList prenode;//用来存放临时数据
    for(i = 1, prenode = longint; i < len; i++)//将字符串除去逗号的每一个数据存放到循环列表中
	{
        if(arr[i] != ',')
		{
            num = arr[i] - 48;//字符型转换为整型
            NodeList newn = new Node;//建立新结点
            newn -> data = num;
            newn -> pre = prenode;
            newn -> next = longint;
            prenode -> next = newn;
            longint -> pre = newn;
            prenode = newn;
        }
    }

    
    if(longint ->next == longint)//当输入的为"+,,,,,,"这种形式时，在链表中存储"+0"
	{
        NodeList newn = new Node;
        newn -> data = 0;
        newn -> pre = longint;
        newn -> next = longint;
        longint -> next = newn;
        longint -> pre = newn;
    }

   
}






int length(NodeList longint)//重新计算去掉分隔符后新链表长度，参数为链表，返回链表长度
{
    int sum = 0;
    NodeList p = longint->next;
    while(p != longint)
	{
        sum++;
        p = p->next;
    }
    return sum;
}

//比较函数，用来比较两个链表绝对值大小
//当第一参数大比第二参数绝对值大时返回1，第一参数比第二参数绝对值小时返回-1，否则返回0
int compare(NodeList &longint1, NodeList &longint2)
{
    NodeList p1, p2;
    p1 = longint1;
    p2 = longint2;
    while(p1->next != longint1 && p2->next != longint2)
	{
        p1 = p1->next;
        p2 = p2->next;
    }
    if(p1->next != longint1)//第一个链表长，则它的绝对值大
	{
        return 1;
	}
    else if(p2->next != longint2)//第二个链表长，则它的绝对值大
	{
        return -1;
	}
    else//两个链表一样长时，比较两个链表结点存放数据大小判断
	{
        p1 = longint1->next;
        p2 = longint2->next;
        while(p1->data == p2->data && p1->next != longint1)
		{
            p1 = p1->next;
            p2 = p2->next;
        }
        if(p1->data > p2->data)
            return 1;
        else if(p1->data < p2->data)
            return -1;
        else
            return 0;
    }
}


void output(NodeList &longint)//输出函数，将链表中的结果加上分隔符','后输出
{

    NodeList p;
    int num = 0;
    int sum = length(longint);

    int n = sum % 4;
    p = longint->next;
    if(p->next == longint && p->data == 0)//当计算结果为0（+0或-0）时输出0
	{
        cout << "计算结果为: " << 0 << endl;
    }else
	{
        if(longint -> data == 43)//输出正负号
		{
            cout << "计算结果为: " << '+';
		}
        else if(longint -> data == 45)
		{
            cout << "计算结果为: " << '-';
		}

        while(p != longint)//以4为一组用逗号隔开
		{
            if((num == n || (num - n) % 4 == 0) && num != sum && num!=0)
			{
                cout << ',';
			}
            cout << p->data;
            p = p->next;
            num++;
        }
    }
    cout << endl;
}




void same_add(NodeList &longint1, NodeList &longint2, NodeList &result)//基本加法运算
{
    int carry = 0;//进位
    int newdata = 0;
    NodeList p1, p2, newn;
    p1 = longint1->pre;
    p2 = longint2->pre;

    NodeList nextnode = result;
    while(p1 != longint1 && p2 != longint2)//从两长整数最后开始逐位进行加法运算
	{
        newdata = (p1->data + p2->data + carry);
        carry = newdata/10;
        newn = new Node;
        if(carry!=0)
		{
            newn->data = (newdata - 10);
		}
        else
		{
            newn->data = newdata;
		}
        newn->pre = result;
        newn->next = nextnode;
        result->next = newn;
        nextnode->pre = newn;
        nextnode = newn;
        p1 = p1->pre;
        p2 = p2->pre;
    }
    while(p1 != longint1)//当p1前部分还有数据时
	{
        newdata = (p1->data + carry);
        carry = newdata/10;
        newn = new Node();
        if(carry!=0)
		{
            newn->data = (newdata - 10);
		}
        else
		{
            newn->data = newdata;
		}
        newn->pre = result;
        newn->next = nextnode;
        result->next = newn;
        nextnode->pre = newn;
        nextnode = newn;
        p1 = p1->pre;
    }
    while(p2 != longint2)//当p2前部分还有数据时
	{
        newdata = (p2->data + carry);
        carry = newdata/10;
        newn = new Node();
        if(carry!=0)
		{
            newn->data = (newdata - 10);
		}
        else
		{
            newn->data = newdata ;
		}
        newn->pre = result;
        newn->next = nextnode;
        result->next = newn;
        nextnode->pre = newn;
        nextnode = newn;
        p2 = p2->pre;
    }
    if(carry != 0){//计算后，进位不为0时处理
        newn = new Node();
        newn->data = carry;
        newn->pre = result;
        newn->next = nextnode;
        result->next = newn;
        nextnode->pre = newn;
    }
    
}



void same_sub(NodeList &longint1, NodeList &longint2,  NodeList &result)//基本减法运算
{
    int borrow = 0;//借位
    int newdata = 0;
    NodeList p1, p2, newn;
    p1 = longint1->pre;
    p2 = longint2->pre;

    NodeList nextnode = result;
    while(p1 != longint1 && p2 != longint2)//从两长整数最后开始逐位进行减法运算
	{
        if(p1->data - p2->data - borrow >= 0)//没有借位产生时
		{
            newdata = p1->data - p2->data - borrow;
            borrow = 0;
        }
        else//有借位产生
		{
            newdata = (p1->data - p2->data - borrow + 10);
            borrow = 1;
        }
        newn = new Node();
        newn->data = newdata;
        newn->pre = result;
        newn->next = nextnode;
        result->next = newn;
        nextnode->pre = newn;
        nextnode = newn;
        p1 = p1->pre;
        p2 = p2->pre;
    }

     while(p1 != longint1)//当p1较长时，前部分还有数据
	 {
        if(borrow)//如果有借位
		{
            if(p1->data - borrow >= 0)
			{
                newdata = p1->data - borrow;
                borrow = 0;
            }
            else
			{
                newdata = (p1->data - borrow + 10);
                borrow = 1;
            }
        }
        else//没有借位
		{
            newdata = p1->data;
		}

        newn = new Node();
        newn->data = newdata;
        newn->pre = result;
        newn->next = nextnode;
        result->next = newn;
        nextnode->pre = newn;
        nextnode = newn;
        p1 = p1->pre;
    }

    nextnode = result ->next;
    NodeList oldn;
    while(nextnode->data == 0 && nextnode->next != result)//删除表开头结点的0，如（+0001转换为+1）；若链表值为0时，result为（+或-）0
	{
        oldn = nextnode;
        nextnode = nextnode->next;
        result ->next = nextnode;
        nextnode ->pre = result;

        
    }

    
}



void add(NodeList &longint1, NodeList &longint2, NodeList &result)//有符号加法运算
{
    result = new Node;//存放结果,初始化
    result ->next = result;
    result ->pre = result;

    if(longint1->data == longint2->data)//长整数L1、L2符号相同
	{
        if(longint1->data == 43)//L1、L2都是正数，结果为+（L1+L2）
		{
            result->data = 43;
		}
        if(longint1->data == 45)//L1、L2都是负数，结果为-（L1+L2）
		{
            result->data = 45;
		}
        same_add(longint1, longint2, result);
    }

    else//L1、L2符号相反
	{
        if(longint1->data == 43 && longint2->data == 45)//L1符号为正、L2符号为负
		{
            if(compare(longint1, longint2) == 1)//L1的绝对值大于L2的绝对值，相当于+（L1-L2）
			{
                result->data = 43;
                same_sub(longint1, longint2, result);
            }
			else if(compare(longint1, longint2) == -1)//L1的绝对值小于L2的绝对值，相当于-（L2-L1）
			{
                result->data = 45;
                same_sub(longint2, longint1, result);
            }
			else//L1的绝对值等于L2的绝对值,输出结果为0
			{
                 NodeList newn = new Node;
                 newn -> data = 0;
                 newn -> pre = result;
                 newn -> next = result;
                 result -> next = newn;
                 result -> pre = newn;
                 
            }
        }

        if(longint1->data == 45 && longint2->data == 43)//L1符号为负、L2符号为正
		{
            if(compare(longint1, longint2) == 1)//L1的绝对值大于L2的绝对值，相当于-（L1-L2）
			{
                result->data = 45;
                same_sub(longint1, longint2, result);
            }
			else if(compare(longint1, longint2) == -1)//L1的绝对值小于L2的绝对值，相当于+（L2-L1）
			{
                result->data = 43;
                same_sub(longint2, longint1, result);
            }
			else//L1的绝对值等于L2的绝对值,输出结果为0
			{
                 NodeList newn = new Node;
                 newn -> data = 0;
                 newn -> pre = result;
                 newn -> next = result;
                 result -> next = newn;
                 result -> pre = newn;
                 
            }
        }

    }
}








void welcome()//主显示函数
{
    cout << "********************************************************************" << endl;
	cout << "*                     任意长整数的加法运算                     *" << endl;
	cout << "********************************************************************" << endl;
	cout << "基本操作要求：" << endl;
	cout << "1.输入格式每四组一位，组间用逗号隔开。" << endl;
	cout << "2.输入的长整数必须带有符号（+或-）,如：+1,0000,000。" << endl;
	cout << "3.组间多个分隔符看做一个(如：+1,,,1000 相当于 +1,1000)。" << endl;
	cout << "********************************************************************" << endl;
	cout << endl;
}


void print()//打印操作界面
{
    cout << "         ************************************************" << endl;
    cout << "         ************************************************" << endl;
    cout << "                      输入1、2选择操作             " << endl;
    cout << "                             1、加法                     " << endl;
    cout << "                             2、退出                     " << endl;
    cout << "         ************************************************" << endl;
    cout << "         ************************************************" << endl;
    cout << endl;
}



void handle_do()//主处理函数
{
    char op;
    NodeList longint1, longint2, longresult;
    cout << "请输入第一个带符号的操作数(如-1,0000,0001或+1,0000,0001): " << endl;//输出两个数任意长的整数
    input(longint1);
    cout << "请输入第二个带符号的操作数(如-1,0000,0001或+1,0000,0001): " << endl;
    input(longint2);
    print();//打印操作界面
    cout << "请输入你的选择:  " << endl;
    cin >> op;

    while(op > '2' || op < '1')//当输入选择符号错误时，提示输入正确的选择
	{
        cout << "请输入正确的选择：  " << endl;
        cin >> op;
    }

    switch(op)//根据选择，匹配执行对应操作
	{
    case '1':
        add(longint1, longint2, longresult);
        output(longresult);
        break;

    

    case '2':
        exit(0);//退出系统
    }
    
}



int main()//主函数
{
    char ch;
    int flag = 1;

    welcome(); //打印欢迎界面
    while(flag)//标志有效时，可以持续执行
	{
        handle_do();//调用主处理函数
        cout << endl;
        cout << "是否继续？是(y)，否(n):  " ;
        cin >> ch;
        cout << endl;
        while(ch != 'y' && ch != 'n')//当键入无效字符时提醒，直至输入有效字符
		{
            cout << "请输入正确选择！是(y)，否(n):  " ;
            cin >> ch;
            cout << endl;
        }
        if(ch == 'n')
		{
            flag = 0;
        }
    }
    return 0;
}

