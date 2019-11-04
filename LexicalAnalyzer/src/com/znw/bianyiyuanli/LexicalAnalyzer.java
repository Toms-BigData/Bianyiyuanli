package com.znw.bianyiyuanli;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
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
//        无识别符：35
//        运算符：36
//        变量：37
public class LexicalAnalyzer  {
    //编译前准备
    String keyWord[] = {"char","double","enum","float","int","long","short","signed","struct",
            "union","unsigned","void","for","do","while","break","contionue","if","else","goto",
            "switch","case","default","return","auto","extern","register","static","const","sizeof",
            "typedef","volatile"};
    char ch;

    

    //返回字符串中关键字对应关键字表的位置
    int KeyWordNumber(String str){
        for(int i = 0;i < keyWord.length;i++)
        {
            if(keyWord[i].equals(str))
                return i+1;
        }
        return 0;
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
    void lexicalanalyze(char[] chars) throws IOException
    {
        //创建新文件用以存储词法分析信息
        String outputfile = "/Users/znw_mac/Downloads/output.txt";
        File myFile = new File(outputfile);
        FileWriter fw = new FileWriter(myFile,true);
        if (!myFile.exists()) {
            // 创建文件(前提是目录已存在，若不在，需新建目录即文件夹)
            myFile.createNewFile();

            // 删除文件
            myFile.delete();
        }



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
                if(KeyWordNumber(arr) != 0){
                    //关键字
                    fw.write("< "+arr+"\t,\t"+KeyWordNumber(arr)+">\n");
                }
                else {
                    //变量
                    fw.write("< "+arr+"\t,\t37>\n");
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
                fw.write("< "+arr+"\t,\t33>\n");
            }
            else switch(ch){
                    //运算符
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                        fw.write("< "+ch+"\t,\t36>\n");
                        break;
                    //分界符
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case ';':
                    case '{':
                    case '}':
                        fw.write("< "+ch+"\t,\t34>\n");
                        break;
                    //运算符
                    case '=':{
                        ch = chars[++i];
                        if(ch == '=') {
                            fw.write("< ==\t,\t36>\n");
                        }

                        else {
                            fw.write("< =\t,\t36>\n");
                            i--;
                        }
                    }break;
                    case ':':{
                        ch = chars[++i];
                        if(ch == '=')
                            fw.write("< :=\t,\t36>\n");
                        else {
                            fw.write("< :\t,\t36>\n");
                            i--;
                        }
                    }break;
                    case '>':{
                        ch = chars[++i];
                        if(ch == '=')
                            fw.write("< >=\t,\t36>\n");
                        else {
                            fw.write("< >\t,\t36>\n");
                            i--;
                        }
                    }break;
                    case '<':{
                        ch = chars[++i];
                        if(ch == '=')
                            fw.write("< <=\t,\t36>\n");
                        else {
                            fw.write("< <\t,\t36>\n");
                            i--;
                        }
                    }break;
                    //无识别
                    default:
                        fw.write("< "+ch+"\t,\t35>\n");
                }
        }
        fw.close();
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
