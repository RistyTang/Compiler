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
    extern bool dump_tokens;
    int chars = 0;
    void DEBUG_FOR_LAB4(std::string s){
        std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
    #include <iostream>
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
"const" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONST\tconst");
    return CONST;
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
"break" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("BREAK\tbreak");
    return BREAK;
}
"continue" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONTINUE\tcontinue");
    return CONTINUE;
}
"==" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("EQUAL\t==");
    return EQUAL;
}
"!=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NOTEQUAL\t!=");
    return NOTEQUAL;
}
"=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGN\t=");
    return ASSIGN;
}
"<" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESS\t<");
    return LESS;
}
"<=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESSEQUAL\t<");
    return LESSEQUAL;
}
">" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATER\t<");
    return GREATER;
}
">=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATEREQUAL\t<");
    return GREATEREQUAL;
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
"*" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MUL\t*");
    return MUL;
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
"&&" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("AND\t&&");
    return AND;
}
"||" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("OR\t||");
    return OR;
}
"!" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NOT\t!");
    return NOT;
}
";" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SEMICOLON\t;");
    return SEMICOLON;
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
"[" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACKET\t[");
    return LBRACKET;
}
"]" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACKET\t}");
    return RBRACKET;
}
"," {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COMMA\t,");
    return COMMA;
}
"~" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("TILDE\t~");
    return TILDE;
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
{DECIMIAL} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + string(yytext));
    chars += strlen(yytext);
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
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + to_string(temp));
    yylval.itype = temp;
    return INTEGER;
}

"putint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    Type* funcType = new FunctionType(TypeSystem::intType, {},{});
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0, true);//作用域GLOBAL(0)
    globals->install(yytext, entry);
    return ID;
}

"getint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    Type* funcType = new FunctionType(TypeSystem::intType, {},{});
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0, true);//作用域GLOBAL(0)
    globals->install(yytext, entry);
    return ID;
}

"putch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    Type* funcType = new FunctionType(TypeSystem::intType, {},{});
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0, true);//作用域GLOBAL(0)
    globals->install(yytext, entry);
    return ID;
}

"getch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    Type* funcType = new FunctionType(TypeSystem::intType, {},{});
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0, true);//作用域GLOBAL(0)
    globals->install(yytext, entry);
    return ID;
}

"putarray" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<Type*> vec;
    vec.push_back(TypeSystem::intType);
    ArrayType* arr = new ArrayType(TypeSystem::intType, -1);
    vec.push_back(arr);
    Type* funcType = new FunctionType(TypeSystem::voidType, vec,{});
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0, true);//作用域GLOBAL(0)
    globals->install(yytext, entry);
    return ID;
}

"getarray" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    std::vector<Type*> vec;
    ArrayType* arr = new ArrayType(TypeSystem::intType, -1);
    vec.push_back(arr);
    Type* funcType = new FunctionType(TypeSystem::intType, vec,{});
    SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0, true);//作用域GLOBAL(0)
    globals->install(yytext, entry);
    return ID;
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

{ID} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}

%%
