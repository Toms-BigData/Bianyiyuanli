本程序基于算符优先文法手动编写语法分析器
开发平台：MacOS 10.14.6
开发环境：CLion 2017.3
开发语言：C++
本程序实现功能：
    1.判断输入文法是否为算符优先文法
    2.求出非终结符的FirstVT集与LastVT集
    3.打印算法优先文法的算符优先表
    4.输入一个句子，以'#'结束，判断句子是否合法，若合法则输出符号栈的每步变化
程序测试文法：
    (1) E -> TE`
        E` -> +TE|空
        T -> FT`
        T` -> *FT`|空
        F -> (E)|i
    (2) E -> E+T|T
        T -> T*F|F
        F -> P^F|P
        P -> (E)|i
程序参考引用：编译原理书中算法、CDSN相关博客
