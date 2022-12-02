%option noyywrap
%{
    #define YY_NO_UNPUT
    #define YY_NO_INPUT

    #include "parser.h"
    #include <ostream>
    #include <fstream>
    using namespace std;

    extern FILE *yyin; 
    extern FILE *yyout;
    //从哪extern的？
    extern bool dump_tokens;

    void DEBUG_FOR_LAB4(std::string s){
        std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
    int linenum=1;//当前行数
    int offset=0;//记录偏移
%}
DECIMIAL ([1-9][0-9]*|0)
OCTAL  (0[0-7]*)
HEXADECIMAL (0[X|x][0-9A-Fa-f]*)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]
LINECOMMENT \/\/[^\n]*
commentbegin "/*"
commentelement .
commenteol  \n  
commentend "*/"

%x comment
%%
{EOL} {

    }
{LINECOMMENT} {
}
{commentbegin} {
    BEGIN comment;
     }
<comment>{commentelement} {
    //什么也不做
    }
<comment>{commenteol} {
}
<comment>{commentend} {
    BEGIN INITIAL;
    }
"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    if(dump_tokens)
        DEBUG_FOR_LAB4("INT\tint");
    return INT;
}
"void" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("VOID\tvoid");
    return VOID;
}
"if" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("IF\tif");
    return IF;
};
"else" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ELSE\telse");
    return ELSE;
};
"return" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RETURN\treturn");
    return RETURN;
}

"=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGN\t=");
    return ASSIGN;
}
"+" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ADD\t+");
    return ADD;
}
"-" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SUB\t-");
    return SUB;
}
"/" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("DIV\t/");
    return DIV;
    }
"%" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MOD\t%");
    return MOD;
    }
"*" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MUL\t*");
    return MUL;
    }
">" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATER\t>");
    return GREATER;
    }
"<" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESS\t<");
    return LESS;
    }
";" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SEMICOLON\t;");
    return SEMICOLON;
}
"!" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("TILDE\t!");
    offset+=1;
    return TILDE;
    }
"(" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LPAREN\t(");
    return LPAREN;
}
")" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RPAREN\t)");
    return RPAREN;
}
"[" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACKET\t[");
    return LBRACKET;
}
"]" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACKET\t]");
    return RBRACKET;
}
"{" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACE\t{");
    return LBRACE;
}
"}" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACE\t}");
    return RBRACE;
}
"~" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("TILDE\t~");
    return TILDE;
    }
"," {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COMMA\t,");
    return COMMA;
    }
"#" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SHA\t#");
    return SHA;
    }
":" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COLON\t:");
    return COLON;
    }
"<<" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MLEFT");
    return MLEFT;
}
">>" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MRIGHT");
    return MRIGHT;
}
">=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GEQUAL\t>=");
    return GEQUAL;
    }
"<=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LEQUAL\t<=");
    return LEQUAL;
    }
"--" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SUBONE\t--");
    return SUBONE;
    }
"++" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ADDONE\t++");
    return ADDONE;
}
"==" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("EQUAL\t==");
    return EQUAL;
    }
"!=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NOTEQUAL");
    return NOTEQUAL;
    }
"&&" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ANDAND\t&&");
    return ANDAND;
    }
"||" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("OROR\t||");
    return OROR;
    }
"/=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGNDIV\t/=");
    return ASSIGNDIV;
   }
"*=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGNSTAR\t*=");
    return ASSIGNSTAR;
    }
"%=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGNMOD\t%=");
    return ASSIGNMOD;
    }
"+=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGNADD\t+=");
    return ASSIGNADD;
    }
"-=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGNSUB\t-=");
    return ASSIGNSUB;
    }
"do" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("DO\tdo");
    return DO;
    }
"while" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("WHILE\twhile");
    return WHILE;
    }
{DECIMIAL} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    yylval.itype = atoi(yytext);
    return INTEGER;
}
{OCTAL} {
    int temp;
    sscanf(yytext, "%o", &temp);    //sscanf是把字符串转为八进制数值赋给temp
    string str="OCTAL\t"+to_string(temp);
    if(dump_tokens)
        DEBUG_FOR_LAB4(str);
    yylval.itype = temp;
    return INTEGER;
}
{HEXADECIMAL} {
    int temp;
    sscanf(yytext, "%x", &temp);
    string str="HEXADECIMAL\t "+to_string(temp);
    if(dump_tokens)
    {
        DEBUG_FOR_LAB4(str);
    }
    yylval.itype = temp;
    return INTEGER;
}
"switch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SWITCH\tswitch");
    return SWITCH;
    }
"case" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CASE\tcase");
    return CASE;
    }
"default" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("DEFAULT\tdefault");
    return DEFAULT;
    }
"sizeof" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SIZEOF\tsizeof");
    return SIZEOF;
    }
"const" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONST\tconst");
    return CONST;
    }
"continue" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONTINUE\tcontinue");
    return CONTINUE;
    }
"break" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("BREAK\tbreak");
    return BREAK;
    }
"for" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("FOR\tfor");
    return FOR;
    }
"scanf" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SCANF\tscanf");
    return SCANF;
    }
"printf" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("PRINTF\tprintf");
    return PRINTF;
    }
"getint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GETINT\tgetint");
    char *lexeme = new char[strlen(yytext) + 1];
    //yytext为解析出的词法单元字符串的指针
    strcpy(lexeme, yytext);
    //设置yylval的strtype是getint
    yylval.strtype = lexeme;
    //getint是一个函数，所以将yylval的type设置为functiontype
    //返回类型int，无参数
    Type* funcType = new FunctionType(TypeSystem::intType, {});
    //创建一个新的符号表项，类型为函数类型、名字为yytext，即getint，作用域为0，即为全局变量
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
    //把当前的ID放进globalTable的最前面
    globals->install(yytext, entry);
    return ID;
}
"putint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("PUTINT\tputint");
    //lexeme为putint
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    //是一个函数，所以设置yylval为strtype
    yylval.strtype = lexeme;
    //形参类型表
    std::vector<Type*> vec; 
    //放进去的应该是int类型，并且只有一个int型的参数
    vec.push_back(TypeSystem::intType);
    //返回类型void，参数表[int]
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
    globals->install(yytext, entry);
    return ID;
}
"putch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("PUTCH\tputch");
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<Type*> vec; //形参类型表
    vec.push_back(TypeSystem::intType);
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);//返回类型void，参数表[int]
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
    globals->install(yytext, entry);
    return ID;
}
{ID} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}
{WHITE}
%%