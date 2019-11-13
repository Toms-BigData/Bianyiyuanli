#include <iostream>
using namespace std;

//文法规则个数
int num;
//转化后文法规则个数
int num_final;
//存储文法规则
char st[10][30];

//非终结符FIRSTVT集
char first[10][10];
//非终结符LASTVT集
char last[10][10];
//非终结符FirstVT标志集
int FirstFlag[10] = { 0 };
//非终结符LastVT标志集
int LastFlag[10] = { 0 };

//算符优先关系存储矩阵
char Data[20][20];
//符号栈s
char s[100];
//终结符
char TerminalSymbol[20];
//输入符号串
char input[100];
//用于输入串的分析
char In_str[20][10];

//打印栈内元素
void PrintStack(int j, int k, char *s)
{
    int n = 0;
    int i;
    for (i = j; i <= k; i++)
    {
        printf("%c", s[i]);
        n++;
    }
    for (; n<15; n++)
    {
        printf(" ");
    }
}

//返回字符串c在算符分析表中的下标
int getIndex(char c)
{
    int i;
    for (i = 0; TerminalSymbol[i] != '\0'; i++)
    {
        if (c == TerminalSymbol[i])
            return i;
    }
    return -1;
}

//判断终结符
int CheckTerminator(char c)
{
    int i;
    for (i = 0; TerminalSymbol[i] != '\0'; i++)
    {
        if (c == TerminalSymbol[i])
            return 1;
    }
    return 0;
}

//求FirstVT集
void FindFirstvt(char c)
{
    int i, j, k, m, n;
    for (i = 0; i<num; i++)
    {
        if (st[i][0] == c)
            break;
    }
    if (FirstFlag[i] == 0)
    {
        n = first[i][0] + 1;
        m = 0;
        do
        {
            if (m == 2 || st[i][m] == '|')
            {
                if (CheckTerminator(st[i][m + 1]))
                {
                    first[i][n] = st[i][m + 1];
                    n++;
                }
                else
                {
                    if (CheckTerminator(st[i][m + 2]))
                    {
                        first[i][n] = st[i][m + 2];
                        n++;
                    }
                    if (st[i][m + 1] != c)
                    {
                        FindFirstvt(st[i][m + 1]);
                        for (j = 0; j<num; j++)
                        {
                            if (st[j][0] == st[i][m + 1])
                                break;
                        }
                        for (k = 0; k<first[j][0]; k++)
                        {
                            int t;
                            for (t = 0; t<n; t++)
                            {
                                if (first[i][t] == first[j][k + 1])
                                    break;
                            }
                            if (t == n)
                            {
                                first[i][n] = first[j][k + 1];
                                n++;
                            }
                        }
                    }
                }
            }
            m++;
        } while (st[i][m] != '\0');
        first[i][n] = '\0';
        //存firstvt集中元素的个数
        first[i][0] = --n;
        FirstFlag[i] = 1;
    }
}

//求LastVT集
void FindLastvt(char c)
{
    int i, j, k, m, n;
    for (i = 0; i<num; i++)
    {
        if (st[i][0] == c)
            break;
    }
    if (LastFlag[i] == 0)
    {
        n = last[i][0] + 1;
        m = 0;
        do
        {
            if (st[i][m + 1] == '\0' || st[i][m + 1] == '|')
            {
                if (CheckTerminator(st[i][m]))
                {
                    last[i][n] = st[i][m];
                    n++;
                }
                else
                {
                    if (CheckTerminator(st[i][m - 1]))
                    {
                        last[i][n] = st[i][m - 1];
                        n++;
                    }
                    if (st[i][m] != c)
                    {
                        FindLastvt(st[i][m]);
                        for (j = 0; j<num; j++)
                        {
                            if (st[j][0] == st[i][m])
                                break;
                        }
                        for (k = 0; k<last[j][0]; k++)
                        {
                            int t;
                            for (t = 0; t<n; t++)
                            {
                                if (last[i][t] == last[j][k + 1])
                                    break;
                            }
                            if (t == n)
                            {
                                last[i][n] = last[j][k + 1];
                                n++;
                            }
                        }
                    }
                }
            }
            m++;
        } while (st[i][m] != '\0');
        last[i][n] = '\0';
        last[i][0] = --n;
        LastFlag[i] = 1;
    }
}

//构造算符优先分析表
void Createtable()
{
    char text[20][10];
    int i, j, k, t, l, x = 0, y = 0;
    int m, n;
    x = 0;
    //求firstvt集和lastvt集
    for (i = 0; i<num; i++)
    {
        FindFirstvt(st[i][0]);
        FindLastvt(st[i][0]);
    }
    //转化文法
    for (i = 0; i<num; i++)
    {
        text[x][y] = st[i][0];
        y++;
        for (j = 1; st[i][j] != '\0'; j++)
        {
            if (st[i][j] == '|')
            {
                text[x][y] = '\0';
                x++;
                y = 0;
                text[x][y] = st[i][0];
                y++;
                text[x][y++] = '-';
                text[x][y++] = '>';
            }
            else
            {
                text[x][y] = st[i][j];
                y++;
            }
        }
        text[x][y] = '\0';
        x++;
        y = 0;
    }
    num_final = x;

    //输出转化后的文法规则串
    printf("转化后的文法为:\n");
    for (i = 0; i<x; i++)
    {
        printf("%s\n", text[i]);
    }

    //求每个终结符的推导结果
    for (i = 0; i<x; i++)
    {
        In_str[i][0] = text[i][0];
        for (j = 3, l = 1; text[i][j] != '\0'; j++, l++)
            In_str[i][l] = text[i][j];
        In_str[i][l] = '\0';
    }

    //构造算符优先分析表
    for (i = 0; i<x; i++)
    {
        for (j = 1; text[i][j + 1] != '\0'; j++)
        {
            if (CheckTerminator(text[i][j]) && CheckTerminator(text[i][j + 1]))
            {
                m = getIndex(text[i][j]);
                n = getIndex(text[i][j + 1]);
                Data[m][n] = '=';
            }
            if (text[i][j + 2] != '\0'&&CheckTerminator(text[i][j]) && CheckTerminator(text[i][j + 2]) && !CheckTerminator(text[i][j + 1]))
            {
                m = getIndex(text[i][j]);
                n = getIndex(text[i][j + 2]);
                Data[m][n] = '=';
            }
            if (CheckTerminator(text[i][j]) && !CheckTerminator(text[i][j + 1]))
            {
                for (k = 0; k<num; k++)
                {
                    if (st[k][0] == text[i][j + 1])
                        break;
                }
                m = getIndex(text[i][j]);
                for (t = 0; t<first[k][0]; t++)
                {
                    n = getIndex(first[k][t + 1]);
                    Data[m][n] = '<';
                }
            }
            if (!CheckTerminator(text[i][j]) && CheckTerminator(text[i][j + 1]))
            {
                for (k = 0; k<num; k++)
                {
                    if (st[k][0] == text[i][j])
                        break;
                }
                n = getIndex(text[i][j + 1]);
                for (t = 0; t<last[k][0]; t++)
                {
                    m = getIndex(last[k][t + 1]);
                    Data[m][n] = '>';
                }
            }
        }
    }

    m = getIndex('#');
    for (t = 0; t<first[0][0]; t++)
    {
        n = getIndex(first[0][t + 1]);
        Data[m][n] = '<';
    }
    n = getIndex('#');
    for (t = 0; t<last[0][0]; t++)
    {
        m = getIndex(last[0][t + 1]);
        Data[m][n] = '>';
    }
    Data[n][n] = '=';
}

//分析串内容
int Analyze()
{
    int i, j;
    int x, y;
    //句子的长度
    int length;
    int k = 1;
    char a;
    char q;
    //栈置初值添加进#，输入句子时以#结束
    s[k] = '#';
    //for语句空转来找到串的末尾
    for (i = 0; input[i] != '\0'; i++);
    length = i--;
    i = 0;
    while ((a = input[i]) != '\0')
    {
        //j指向最接近栈顶的终极符
        if (CheckTerminator(s[k]))
            j = k;
        else
            j = k - 1;
        x = getIndex(s[j]);
        y = getIndex(a);

        //归约
        if (Data[x][y] == '>')
        {
            PrintStack(1, k, s);
            printf("%c", a);
            PrintStack(i + 1, length, input);
            printf("规约\n");
            do
            {
                q = s[j];
                if (CheckTerminator(s[j - 1]))
                    j = j - 1;
                else j = j - 2;
                x = getIndex(s[j]);
                y = getIndex(q);
            } while (Data[x][y] != '<');
            int m, n, N;
            for (m = j + 1; m <= k; m++)
            {
                for (N = 0; N<num_final; N++)
                    for (n = 1; In_str[N][n] != '\0'; n++)
                    {
                        if (!CheckTerminator(s[m]) && !CheckTerminator(In_str[N][n]))
                        {
                            if (CheckTerminator(s[m + 1]) && CheckTerminator(In_str[N][n + 1])
                                && s[m + 1] == In_str[N][n + 1])
                            {
                                s[j + 1] = In_str[N][0];
                                break;
                            }
                        }
                        else
                        if (CheckTerminator(s[m]))
                            if (s[m] == In_str[N][n])
                            {
                                s[j + 1] = In_str[N][0];
                                break;
                            }
                    }
            }
            k = j + 1;
            if (k == 2 && a == '#')
            {
                PrintStack(1, k, s);
                printf("%c", a);
                PrintStack(i + 1, length, input);
                printf("结束\n");
                printf("\n句子符合文法的定义！\n");
                return 1;
            }
        }
            //移进
        else if (Data[x][y] == '<' || Data[x][y] == '=')
        {
            PrintStack(1, k, s);
            printf("%c", a);
            PrintStack(i + 1, length, input);
            printf("移进\n");
            k++;
            s[k] = a;
            i++;
        }
        else
        {
            printf("\n句子不符合文法的定义！\n");
            return 0;
        }
    }
    printf("\n句子不符合文法的定义！\n");
    return 0;
}

int main()
{

    int i, j, k = 0;

    //输入文法
    printf("请输入文法规则条数：");
    cin >> num;
    printf("请输入文法规则：\n");
    for (i = 0; i<num; i++)
    {
        //存储文法规则，初始化FIRSTVT集和LASTVT集
        cin >> st[i];
        first[i][0] = 0;
        last[i][0] = 0;
    }

    ////判断是否为算符优先文法
    for (i = 0; i<num; i++)
    {
        for (j = 0; st[i][j] != '\0'; j++)
        {
            if (st[i][0]<'A' || st[i][0]>'Z')
            {
                printf("不是算符文法!\n");
                exit(-1);
            }
            if (st[i][j] >= 'A'&&st[i][j] <= 'Z')
            {
                if (st[i][j + 1] >= 'A'&&st[i][j + 1] <= 'Z')//两非终结符不能相邻
                {
                    printf("不是算符文法!\n");
                    exit(-1);
                }
            }
        }
    }
    for (i = 0; i<num; i++)
    {
        for (j = 0; st[i][j] != '\0'; j++)
        {
            if ((st[i][j]<'A' || st[i][j]>'Z') && st[i][j] != '-'&&st[i][j] != '>'&&st[i][j] != '|')
                TerminalSymbol[k++] = st[i][j];
        }
    }
    TerminalSymbol[k] = '#';
    TerminalSymbol[k + 1] = '\0';
    Createtable();

    //输出每个非终结符的FIRSTVT集
    printf("非终结符FirstVT集为：\n");
    for (i = 0; i<num; i++)
    {
        printf("%c: ", st[i][0]);
        for (j = 0; j<first[i][0]; j++)
        {
            printf("%c ", first[i][j + 1]);
        }
        printf("\n");
    }

    //输出每个非终结符的LASTVT集
    printf("非终结符LastVT集为：\n");
    for (i = 0; i<num; i++)
    {
        printf("%c: ", st[i][0]);
        for (j = 0; j<last[i][0]; j++)
        {
            printf("%c ", last[i][j + 1]);
        }
        printf("\n");
    }

    //输出算符优先分析表
    printf("算符优先分析表:\n");
    for (i = 0; TerminalSymbol[i] != '\0'; i++)
        printf("\t%c", TerminalSymbol[i]);
    printf("\n");
    for (i = 0; i<k + 1; i++)
    {
        printf("%c\t", TerminalSymbol[i]);
        for (j = 0; j<k + 1; j++)
        {
            printf("%c\t", Data[i][j]);
        }
        printf("\n");
    }

    //输入句子
    printf("请输入句子以#结束:");
    while (cin >> input && input != "exit") {
        Analyze();
        printf("请输入句子以#结束:");
    }

    system("终止");
}












