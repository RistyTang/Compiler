%option noyywrap
%top{
#include<math.h>
#include<string.h>
}

%{
    /*
    * You will need to comment this line in lab5.
    */

    #define ONLY_FOR_LEX
    
    #ifdef ONLY_FOR_LEX
    #else
    #define YYSTYPE void *
    #include "parser.h"
    #endif

    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #include <string>

    #ifdef ONLY_FOR_LEX
    #include <ostream>
    #include <fstream>
    #include <iostream>
    #include <stack>
    #include <list>
    using namespace std;
    extern FILE *yyin; 
    extern FILE *yyout;
    int linenum=1;//当前行数
    void DEBUG_FOR_LAB4(std::string s){
        std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
    int offset=0;//记录偏移量
    struct IDstruct//记录符号
    {
        string name;//此处修改为string类型，容纳更长的变量名
        int scopebegin=0;//记录作用域起始行，初始化为0
        int scopeend=-1;//
        bool writable=1;//初始化为作用域有效，1代表后续可以引用
    };
    list<IDstruct> IDlist;//使用一个链表存储符号表
    stack<int> scope;//使用一个栈结构来帮助记录定义域
    bool declaration=0;//当它为1说明是一个新定义的量
    
    #endif
%}
main "main"
EOL (\r\n|\n|\r) 
WHITE [\t ]  
letter [A-Za-z]
ID [[:alpha:]_][[:alpha:][:digit:]_]*
DECIMIAL ([1-9][0-9]*|0)
OCTAL  (0[0-7]*)
HEXADECIMAL (0[X|x][0-9A-Fa-f]*)
LINECOMMENT \/\/[^\n]*
commentbegin "/*"
commentelement .
commenteol  \n  
commentend "*/"

%x comment

%%

{main} {
    //保留字
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("MAIN\tmain\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("main");
    #else
        return MAIN;
    #endif
}
{EOL} {
    linenum+=1;
    offset=0;//偏移量置0
    }
{LINECOMMENT} {
    //什么也不做
    offset=0;
}
{commentbegin} {
    BEGIN comment;
     }
<comment>{commentelement} {
    //什么也不做
    }
<comment>{commenteol} {
    //注释内换行也要加一
    linenum+=1;
}
<comment>{commentend} {
    BEGIN INITIAL;
    }
"void" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("VOID\tvoid\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("void");
    #else
        return VOID;
    #endif
    }
"char" {
     declaration=1;//说明新定义变量
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("CHAR\t\tchar\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("char");
    #else
        return CHAR;
    #endif
    }
"int"  {
    declaration=1;//说明新定义变量
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("INT\t\tint\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("int");
    #else
        return INT;
    #endif
    }
"sizeof" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SIZEOF\tsizeof\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("sizeof");
    #else
        return SIZEOF;
    #endif
    }
"const" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("CONST\tconst\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("const");
    #else
        return CONST;
    #endif
    }
"return" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RETURN\treturn\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("return");
    #else
        return RETURN;
    #endif
    }
"continue" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("CONTINUE\tcontinue\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("continue");
    #else
        return CONTINUE;
    #endif
    }
"break" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("BREAK\tbreak\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("break");
    #else
        return BREAK;
    #endif
    }
"if" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("IF\t\tif\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("if");
    #else
        return IF;
    #endif
    }
"else" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ELSE\telse\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("else");
    #else
        return ELSE;
    #endif
    }
"switch" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SWITCH\tswitch\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("switch");
    #else
        return SWITCH;
    #endif
    }
"case" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("CASE\tcase\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("case");
    #else
        return CASE;
    #endif
    }
"default" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("DEFAULT\tdefault\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("default");
    #else
        return DEFAULT;
    #endif
    }
"for" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("FOR\tfor\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("for");
    #else
        return FOR;
    #endif
    }
"do" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("DO\tdo\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("do");
    #else
        return DO;
    #endif
    }
"while" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("WHILE\twhile\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("while");
    #else
        return WHILE;
    #endif
    }
"scanf" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SCANF\tscanf\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("scanf");
    #else
        return SCANF;
    #endif
    }
"printf" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("PRINTF\tprintfs\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("printf");
    #else
        return PRINTF;
    #endif
    }
"{" {
    #ifdef ONLY_FOR_LEX
    //左边大括号代表了一个新作用域的开始
    scope.push(linenum);
    #else
        return LC;
    #endif
    fprintf(yyout,"[DEBUG LAB4]: \tLC\t\t%s\t\t lineat:%d\t\toffset:%d \n",yytext,linenum,offset);
    offset+=1;
    }
"}" {
    #ifdef ONLY_FOR_LEX
    offset+=1;//偏移量+1
    //此时代表一个作用域结束！！！
    //遍历符号表，将这个作用域内的变量全部标记为不可取用状态！
    int scopelinefrom=scope.top();//是这个作用域开始时的
    for(list<IDstruct>::iterator it=IDlist.begin();it!=IDlist.end();it++)
    {
        //用一个迭代器来遍历符号表，进行对所有符号的遍历
        //这一点可以改进？
        if(it->scopebegin==scopelinefrom)//作用域起始范围相同
        {
            it->scopeend=linenum;//那么它在此之后结束
            it->writable=0;//之后不可再引用
        }
    }
    scope.pop();//弹出
    fprintf(yyout,"[DEBUG LAB4]: \tRC\t\t%s\t\t lineat:%d\t\toffset:%d \n",yytext,linenum,offset);
    #else
        return RC;
    #endif
    }
"[" {
    #ifdef ONLY_FOR_LEX
    offset+=1;
        DEBUG_FOR_LAB4("LB\t[\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
    #else
        return LB;
    #endif
    }
"]" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RB\t]\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return RB;
    #endif
    }
"(" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LP\t\t(\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return LP;
    #endif
    }
")" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RP\t\t)\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return RP;
    #endif
    }
"~" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LOGRE\t~\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return LOGRE;
    #endif
    }
"++" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("INPLUS\t++\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return INPLUS;
    #endif
    }
"--" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("INMINUS\t--\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return INMINUS;
    #endif
    }
"!" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LOCRE\t!\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return LOCRE;
    #endif
    }
"*" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("STAR\t*\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return STAR;
    #endif
    }
"/" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("DIVOP\t/\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return DIVOP;
    #endif
    }
"%" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("COMOP\t%\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return COMOP;
    #endif
    }
"+" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("PLUS\t+\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return PLUS;
    #endif
    }
"-" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("MINUS\t-\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return MINUS;
    #endif
    
    }
">" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RELG\t>\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return RELG;
    #endif
    
    }
"<" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RELL\t<\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return RELL;
    #endif

    }
">=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RELGEQ\t>=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return RELGEQ;
    #endif
    
    }
"<=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RELLEQ\t<=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return RELLEQ;
    #endif
    
    }
"==" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("EQUOP\t==\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return EQUOP;
    #endif
    
    }
"!=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("UEQUOP\t!=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return UEQUOP;
    #endif
    
    }
"&&" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ANDAND\t&&\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return ANDAND;
    #endif
    
    }
"||" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("OROR\t||\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return OROR;
    #endif
    }
"=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("EQUAL\t=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return EQUAL;
    #endif
    }
"/=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ASSIGNDIV\t/=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return ASSIGNDIV;
    #endif
   }
"*=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ASSIGNSTAR\t*=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return ASSIGNSTAR;
    #endif
    }
"%=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ASSIGNCOM\t%=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return ASSIGNCOM;
    #endif
    }
"+=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ASSIGNPLUS\t+=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return ASSIGNPLUS;
    #endif
    }
"-=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ASSIGNMINUS\t-=\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=2;
    #else
        return ASSIGNMINUS;
    #endif
    }
"," {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("COMMA\t,\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return COMMA;
    #endif
    }
"#" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SHA\t#\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return SHA;
    #endif
    }
";" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SEMI\t;\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return SEMI;
    #endif
    
    }
":" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("COLON\t:\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=1;
    #else
        return COLON;
    #endif
    }
{DECIMIAL} {
    #ifdef ONLY_FOR_LEX
    int temp;
    sscanf(yytext,"%d",&temp);
        string str="DECIMAL\t"+to_string(temp)+"\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset);
        DEBUG_FOR_LAB4(str);
        offset+=strlen(yytext);
    #else
        return DECIMIAL;
    #endif
}
"float" {
    declaration=1;//说明新定义变量
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("FLOAT\tvoidfloat\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset));
        offset+=strlen("float");
    #else
        return FLOAT;
    #endif
}
{OCTAL} {
    #ifdef ONLY_FOR_LEX
        int temp;
        sscanf(yytext, "%o", &temp);    //sscanf是把字符串转为八进制数值赋给temp
        string str="OCTAL\t"+to_string(temp)+"\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset);
        offset+=strlen(yytext);
        DEBUG_FOR_LAB4(str);
    #else
        return OCTAL;
    #endif
}
{HEXADECIMAL} {
    #ifdef ONLY_FOR_LEX
        int temp;
        sscanf(yytext, "%x", &temp);
        string str="HEXADECIMAL\t "+to_string(temp)+"\t\t lineat:"+to_string(linenum)+"\t\toffset:"+to_string(offset);
        DEBUG_FOR_LAB4(str);
        offset+=strlen(yytext);
    #else
        return HEXADECIMAL;
    #endif
}
{ID} {
    //重写ID方法
    int scopelinefrom=scope.top();//从当前作用域开始
    string nowname=string(yytext);//记录变量名字
    bool existincurscope=false;//查找此定义域内之前是否出现过这个变量
    for(list<IDstruct>::iterator it=IDlist.begin();it!=IDlist.end();it++)
    {
        if((it->name==nowname)&&(it->scopebegin==scopelinefrom))
        {
            //说明是此作用域内之前定义过的变量，也就是引用
            existincurscope=1;
            fprintf(yyout,"[DEBUG LAB4]: \tID\t\t%s \t\t lineat:%d\t\toffset:%d \t\t IDaddress:%p\n",yytext,linenum,offset,&(*it));
            break;
        }
    }
    if(existincurscope!=1)//没在当前作用域出现过
    {
        if(declaration==1)//说明是一个新定义的变量
        {
            IDstruct newID;
            newID.name=nowname;
            newID.scopebegin=scopelinefrom;//作用域起始行
            IDlist.push_back(newID);//加入符号表
            list<IDstruct>::iterator back=IDlist.end();
            back--;//以此实现指向最后一个元素开始
            fprintf(yyout,"[DEBUG LAB4]: \tID\t\t%s \t\t lineat:%d\t\toffset:%d \t\t IDaddress:%p\n",yytext,linenum,offset,&(*back));
        }
        else//不是一个新定义变量
        {
            bool existinprescope=0;//查看是否在之前的未结束作用域中被引用
            for(list<IDstruct>::iterator it =IDlist.end();it!=IDlist.begin();it--)//从后往前遍历
            {
                if((it->name==nowname)&&(it->writable==1))//是有效的
                {
                    existinprescope=1;//找到了
                    fprintf(yyout,"[DEBUG LAB4]: \tID\t\t%s \t\t lineat:%d\t\toffset:%d \t\t IDaddress:%p\n",yytext,linenum,offset,&(*it));
                    break;
                }
            }
            if(existinprescope==0)//没有找到，说明是错误语法啊
            {
                //错误的引用可以直接报错
                fprintf(yyout,"%s is an undefined variable,are you sure?\n",yytext);
            }
        }
    }
    declaration=0;//恢复
    
}
{EOL} yylineno++;
{WHITE} {offset+=1;}
%%

#ifdef ONLY_FOR_LEX
int main(int argc, char **argv)
{
    //初始时，scope应该为0，代表全局变量
    scope.push(0);
    if(argc != 5){
        fprintf(stderr, "Argument Not Enough");
        exit(EXIT_FAILURE);
    }

    if(!(yyin = fopen(argv[1], "r"))){
        fprintf(stderr, "No such file or directory: %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(!(yyout = fopen(argv[3], "w"))){
        fprintf(stderr, "No such file or directory: %s", argv[3]);
        exit(EXIT_FAILURE);
    }

    yylex();
    return 0;
}
#endif


