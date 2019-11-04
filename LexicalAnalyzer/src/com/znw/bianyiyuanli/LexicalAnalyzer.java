package com.znw.bianyiyuanli;

import java.io.File;
import java.io.FileReader;
import java.util.Scanner;


//关键字表如下
//        char ：1
//        double ：2
//        enum ：3
//        float：4
//        int： 5
//        long ：6
//        short ：7
//        signed：8
//        struct：9
//        union：10
//        unsigned：11
//        void ：12
//        for：13
//        do ：14
//        while ：15
//        break：16
//        continue：17
//        if: 18
//        else ：19
//        goto：20
//        switch : 21
//        case：22
//        default：23
//        return ：24
//        auto ：25
//        extern：26
//        register：27
//        static ：28
//        const ：29
//        sizeof：30
//        typedef：31
//        volatile：32
//        数字：33
//        分界符：34
//        变量：35

public class LexicalAnalyzer {

    String keyWord[] = {"char","double","enum","float","int","long","short","signed","struct",
            "union","unsigned","void","for","do","while","break","contionue","if","else","goto",
            "switch","case","default","return","auto","extern","register","static","const","sizeof",
            "typedef","volatile"};
    char ch;

    //判断是否是关键字
    boolean isKeyWord(String str)
    {
        for(int i = 0;i < keyWord.length;i++)
        {
            if(keyWord[i].equals(str))
                return true;
        }
        return false;
    }
    //判断是否是字母
    boolean isLetter(char letter)
    {
        if((letter >= 'a' && letter <= 'z')||(letter >= 'A' && letter <= 'Z'))
            return true;
        else
            return false;
    }
    //判断是否是数字
    boolean isDigit(char digit)
    {
        if(digit >= '0' && digit <= '9')
            return true;
        else
            return false;
    }
    //词法分析
    void lexicalanalyze(char[] chars)
    {
        String arr = "";
        for(int i = 0;i< chars.length;i++) {
            ch = chars[i];
            arr = "";
            if(ch == ' '||ch == '\t'||ch == '\n'||ch == '\r'){}
            else if(isLetter(ch)){
                while(isLetter(ch)||isDigit(ch)){
                    arr += ch;
                    ch = chars[++i];
                }
                //回退一个字符
                i--;
                if(isKeyWord(arr)){
                    //关键字
                    System.out.println(arr+"\t4"+"\t关键字");
                }
                else{
                    //标识符
                    System.out.println(arr+"\t4"+"\t标识符");
                }
            }
            else if(isDigit(ch)||(ch == '.'))
            {
                while(isDigit(ch)||(ch == '.'&&isDigit(chars[++i])))
                {
                    if(ch == '.') i--;
                    arr = arr + ch;
                    ch = chars[++i];
                }
                //属于无符号常数
                System.out.println(arr+"\t5"+"\t常数");
            }
            else switch(ch){
                    //运算符
                    case '+':System.out.println(ch+"\t2"+"\t运算符");break;
                    case '-':System.out.println(ch+"\t2"+"\t运算符");break;
                    case '*':System.out.println(ch+"\t2"+"\t运算符");break;
                    case '/':System.out.println(ch+"\t2"+"\t运算符");break;
                    //分界符
                    case '(':System.out.println(ch+"\t3"+"\t分界符");break;
                    case ')':System.out.println(ch+"\t3"+"\t分界符");break;
                    case '[':System.out.println(ch+"\t3"+"\t分界符");break;
                    case ']':System.out.println(ch+"\t3"+"\t分界符");break;
                    case ';':System.out.println(ch+"\t3"+"\t分界符");break;
                    case '{':System.out.println(ch+"\t3"+"\t分界符");break;
                    case '}':System.out.println(ch+"\t3"+"\t分界符");break;
                    //运算符
                    case '=':{
                        ch = chars[++i];
                        if(ch == '=')System.out.println("=="+"\t2"+"\t运算符");
                        else {
                            System.out.println("="+"\t2"+"\t运算符");
                            i--;
                        }
                    }break;
                    case ':':{
                        ch = chars[++i];
                        if(ch == '=')System.out.println(":="+"\t2"+"\t运算符");
                        else {
                            System.out.println(":"+"\t2"+"\t运算符");
                            i--;
                        }
                    }break;
                    case '>':{
                        ch = chars[++i];
                        if(ch == '=')System.out.println(">="+"\t2"+"\t运算符");
                        else {
                            System.out.println(">"+"\t2"+"\t运算符");
                            i--;
                        }
                    }break;
                    case '<':{
                        ch = chars[++i];
                        if(ch == '=')System.out.println("<="+"\t2"+"\t运算符");
                        else {
                            System.out.println("<"+"\t2"+"\t运算符");
                            i--;
                        }
                    }break;
                    //无识别
                    default: System.out.println(ch+"\t6"+"\t无识别符");
                }
        }
    }

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        String filepath;
        System.out.println("Input the file`s path:");
        filepath =  scanner.nextLine();
        File file = new File(filepath);
        FileReader reader = new FileReader(file);
        int length = (int) file.length();
        char code[] = new char[length+1];
        reader.read(code);
        reader.close();
        LexicalAnalyzer la = new LexicalAnalyzer();
        la.lexicalanalyze(code);

    }
}
