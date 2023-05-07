#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;


typedef struct ListNode //�ṹ�壬˫������
{  
	int data;//�ṹ������             
	struct ListNode *pre; //ǰָ��ci
	struct ListNode *next;//��ָ��
}Node, *NodeList;

int check(char a[], int m)//��麯�������ж���������ָ�ʽ�Ƿ���ȷ,������ȷ����1������ȷ����-1
{
    if(a[0] == '+' || a[0] == '-')//��һ���ַ�Ϊ����λ
	{
        for(int i = 1; i < m; i++)
		{
            if((int(a[i]) <= 57 && int(a[i]) >= 48) || a[i] == ',')//����ÿһλ����0-9֮������Ƕ���
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


void input(NodeList &longint)//���뺯���ַ����ͳ�����,ȥ���ָ��������������-
{

    longint = new Node;
    longint -> pre = longint; //��ʼ���ṹ�����
    longint -> next = longint;
    int flag1 = 0;
    int num = 0;//���������ʱ��
    int len = 0;//�ַ�������
    string str;
    char arr[1000];//�ַ���������ų�����
    cin >> str;//����һ���ַ���

    len = str.length();
    for(int i = 0; i < len; i++)//���ַ�����ֵ���ַ����飬����check����
	{
        arr[i] = str[i];
    }
    flag1 = check(arr, len);//����check����
    while(flag1 == -1)//�������ʽ����ȷʱ��ʾ����������ֱ�������ʽ��ȷ
	{
        cout << "�����°��ո�ʽ���������������" << endl;
        cin >> str;
        len = str.length();
        for(int i = 0; i < len; i++){
            arr[i] = str[i];
        }
        flag1 = check(arr, len);
    }

    if(arr[0] == '+')//����һ���ַ�Ϊ'+'�洢Ϊ����43
	{
        longint->data = int('+');
    }
    if(arr[0] == '-')//����һ���ַ�Ϊ'-'�洢Ϊ����45
	{
        longint->data = int('-');
    }
	int i;
    NodeList prenode;//���������ʱ����
    for(i = 1, prenode = longint; i < len; i++)//���ַ�����ȥ���ŵ�ÿһ�����ݴ�ŵ�ѭ���б���
	{
        if(arr[i] != ',')
		{
            num = arr[i] - 48;//�ַ���ת��Ϊ����
            NodeList newn = new Node;//�����½��
            newn -> data = num;
            newn -> pre = prenode;
            newn -> next = longint;
            prenode -> next = newn;
            longint -> pre = newn;
            prenode = newn;
        }
    }

    
    if(longint ->next == longint)//�������Ϊ"+,,,,,,"������ʽʱ���������д洢"+0"
	{
        NodeList newn = new Node;
        newn -> data = 0;
        newn -> pre = longint;
        newn -> next = longint;
        longint -> next = newn;
        longint -> pre = newn;
    }

   
}






int length(NodeList longint)//���¼���ȥ���ָ������������ȣ�����Ϊ��������������
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

//�ȽϺ����������Ƚ������������ֵ��С
//����һ������ȵڶ���������ֵ��ʱ����1����һ�����ȵڶ���������ֵСʱ����-1�����򷵻�0
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
    if(p1->next != longint1)//��һ�������������ľ���ֵ��
	{
        return 1;
	}
    else if(p2->next != longint2)//�ڶ��������������ľ���ֵ��
	{
        return -1;
	}
    else//��������һ����ʱ���Ƚ����������������ݴ�С�ж�
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


void output(NodeList &longint)//����������������еĽ�����Ϸָ���','�����
{

    NodeList p;
    int num = 0;
    int sum = length(longint);

    int n = sum % 4;
    p = longint->next;
    if(p->next == longint && p->data == 0)//��������Ϊ0��+0��-0��ʱ���0
	{
        cout << "������Ϊ: " << 0 << endl;
    }else
	{
        if(longint -> data == 43)//���������
		{
            cout << "������Ϊ: " << '+';
		}
        else if(longint -> data == 45)
		{
            cout << "������Ϊ: " << '-';
		}

        while(p != longint)//��4Ϊһ���ö��Ÿ���
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




void same_add(NodeList &longint1, NodeList &longint2, NodeList &result)//�����ӷ�����
{
    int carry = 0;//��λ
    int newdata = 0;
    NodeList p1, p2, newn;
    p1 = longint1->pre;
    p2 = longint2->pre;

    NodeList nextnode = result;
    while(p1 != longint1 && p2 != longint2)//�������������ʼ��λ���мӷ�����
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
    while(p1 != longint1)//��p1ǰ���ֻ�������ʱ
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
    while(p2 != longint2)//��p2ǰ���ֻ�������ʱ
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
    if(carry != 0){//����󣬽�λ��Ϊ0ʱ����
        newn = new Node();
        newn->data = carry;
        newn->pre = result;
        newn->next = nextnode;
        result->next = newn;
        nextnode->pre = newn;
    }
    
}



void same_sub(NodeList &longint1, NodeList &longint2,  NodeList &result)//������������
{
    int borrow = 0;//��λ
    int newdata = 0;
    NodeList p1, p2, newn;
    p1 = longint1->pre;
    p2 = longint2->pre;

    NodeList nextnode = result;
    while(p1 != longint1 && p2 != longint2)//�������������ʼ��λ���м�������
	{
        if(p1->data - p2->data - borrow >= 0)//û�н�λ����ʱ
		{
            newdata = p1->data - p2->data - borrow;
            borrow = 0;
        }
        else//�н�λ����
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

     while(p1 != longint1)//��p1�ϳ�ʱ��ǰ���ֻ�������
	 {
        if(borrow)//����н�λ
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
        else//û�н�λ
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
    while(nextnode->data == 0 && nextnode->next != result)//ɾ����ͷ����0���磨+0001ת��Ϊ+1����������ֵΪ0ʱ��resultΪ��+��-��0
	{
        oldn = nextnode;
        nextnode = nextnode->next;
        result ->next = nextnode;
        nextnode ->pre = result;

        
    }

    
}



void add(NodeList &longint1, NodeList &longint2, NodeList &result)//�з��żӷ�����
{
    result = new Node;//��Ž��,��ʼ��
    result ->next = result;
    result ->pre = result;

    if(longint1->data == longint2->data)//������L1��L2������ͬ
	{
        if(longint1->data == 43)//L1��L2�������������Ϊ+��L1+L2��
		{
            result->data = 43;
		}
        if(longint1->data == 45)//L1��L2���Ǹ��������Ϊ-��L1+L2��
		{
            result->data = 45;
		}
        same_add(longint1, longint2, result);
    }

    else//L1��L2�����෴
	{
        if(longint1->data == 43 && longint2->data == 45)//L1����Ϊ����L2����Ϊ��
		{
            if(compare(longint1, longint2) == 1)//L1�ľ���ֵ����L2�ľ���ֵ���൱��+��L1-L2��
			{
                result->data = 43;
                same_sub(longint1, longint2, result);
            }
			else if(compare(longint1, longint2) == -1)//L1�ľ���ֵС��L2�ľ���ֵ���൱��-��L2-L1��
			{
                result->data = 45;
                same_sub(longint2, longint1, result);
            }
			else//L1�ľ���ֵ����L2�ľ���ֵ,������Ϊ0
			{
                 NodeList newn = new Node;
                 newn -> data = 0;
                 newn -> pre = result;
                 newn -> next = result;
                 result -> next = newn;
                 result -> pre = newn;
                 
            }
        }

        if(longint1->data == 45 && longint2->data == 43)//L1����Ϊ����L2����Ϊ��
		{
            if(compare(longint1, longint2) == 1)//L1�ľ���ֵ����L2�ľ���ֵ���൱��-��L1-L2��
			{
                result->data = 45;
                same_sub(longint1, longint2, result);
            }
			else if(compare(longint1, longint2) == -1)//L1�ľ���ֵС��L2�ľ���ֵ���൱��+��L2-L1��
			{
                result->data = 43;
                same_sub(longint2, longint1, result);
            }
			else//L1�ľ���ֵ����L2�ľ���ֵ,������Ϊ0
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








void welcome()//����ʾ����
{
    cout << "********************************************************************" << endl;
	cout << "*                     ���ⳤ�����ļӷ�����                     *" << endl;
	cout << "********************************************************************" << endl;
	cout << "��������Ҫ��" << endl;
	cout << "1.�����ʽÿ����һλ������ö��Ÿ�����" << endl;
	cout << "2.����ĳ�����������з��ţ�+��-��,�磺+1,0000,000��" << endl;
	cout << "3.������ָ�������һ��(�磺+1,,,1000 �൱�� +1,1000)��" << endl;
	cout << "********************************************************************" << endl;
	cout << endl;
}


void print()//��ӡ��������
{
    cout << "         ************************************************" << endl;
    cout << "         ************************************************" << endl;
    cout << "                      ����1��2ѡ�����             " << endl;
    cout << "                             1���ӷ�                     " << endl;
    cout << "                             2���˳�                     " << endl;
    cout << "         ************************************************" << endl;
    cout << "         ************************************************" << endl;
    cout << endl;
}



void handle_do()//��������
{
    char op;
    NodeList longint1, longint2, longresult;
    cout << "�������һ�������ŵĲ�����(��-1,0000,0001��+1,0000,0001): " << endl;//������������ⳤ������
    input(longint1);
    cout << "������ڶ��������ŵĲ�����(��-1,0000,0001��+1,0000,0001): " << endl;
    input(longint2);
    print();//��ӡ��������
    cout << "���������ѡ��:  " << endl;
    cin >> op;

    while(op > '2' || op < '1')//������ѡ����Ŵ���ʱ����ʾ������ȷ��ѡ��
	{
        cout << "��������ȷ��ѡ��  " << endl;
        cin >> op;
    }

    switch(op)//����ѡ��ƥ��ִ�ж�Ӧ����
	{
    case '1':
        add(longint1, longint2, longresult);
        output(longresult);
        break;

    

    case '2':
        exit(0);//�˳�ϵͳ
    }
    
}



int main()//������
{
    char ch;
    int flag = 1;

    welcome(); //��ӡ��ӭ����
    while(flag)//��־��Чʱ�����Գ���ִ��
	{
        handle_do();//������������
        cout << endl;
        cout << "�Ƿ��������(y)����(n):  " ;
        cin >> ch;
        cout << endl;
        while(ch != 'y' && ch != 'n')//��������Ч�ַ�ʱ���ѣ�ֱ��������Ч�ַ�
		{
            cout << "��������ȷѡ����(y)����(n):  " ;
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

