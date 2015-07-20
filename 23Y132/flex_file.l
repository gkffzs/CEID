%{
	#include "y.tab.h"  
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
%}
		
%option noyywrap
%option yylineno

%x comments
%x include_directive

sign ("+"|"-")
digit [0-9]
integer {digit}+
signed_integer {sign}{digit}+
character \'([^'"\\]|\\['"\\nt0])+\'
identifier [a-zA-Z_][a-zA-Z0-9_]*
white_spaces [ \t\n]

%%

#include BEGIN(include_directive);

"/*" BEGIN(comments);

<comments>{
     [^*\n]*
     "*"+[^*/\n]*
     \n
     "*/" BEGIN(INITIAL);
}

"if" {printf("\txxx KEYWORD: %s\n", yytext); return IF;}
"else" {printf("\txxx KEYWORD: %s\n", yytext); return ELSE;}
"integer" {printf("\txxx KEYWORD: %s\n", yytext); return INTEGER;}
"char" {printf("\txxx KEYWORD: %s\n", yytext); return CHAR;}
"void" {printf("\txxx KEYWORD: %s\n", yytext); return VOID;}
"class" {printf("\txxx KEYWORD: %s\n", yytext); return CLASS;}
"new" {printf("\txxx KEYWORD: %s\n", yytext); return NEW;}
"return" {printf("\txxx KEYWORD: %s\n", yytext); return RETURN;}
"while" {printf("\txxx KEYWORD: %s\n", yytext); return WHILE;}

"public" {printf("\txxx KEYWORD: %s\n", yytext); return PUBLIC;}
"protected" {printf("\txxx KEYWORD: %s\n", yytext); return PROTECTED;}
"private" {printf("\txxx KEYWORD: %s\n", yytext); return PRIVATE;}

"static" {printf("\txxx KEYWORD: %s\n", yytext); return STATIC;}
"abstract" {printf("\txxx KEYWORD: %s\n", yytext); return ABSTRACT;}
"final" {printf("\txxx KEYWORD: %s\n", yytext); return FINAL;}

"this" {printf("\txxx KEYWORD: %s\n", yytext); return THIS;}
"super" {printf("\txxx KEYWORD: %s\n", yytext); return SUPER;}

"+" {printf("\t||| SYMBOL: %s\n", yytext); return ADD;}
"-" {printf("\t||| SYMBOL: %s\n", yytext); return SUB;}
"*" {printf("\t||| SYMBOL: %s\n", yytext);return MUL;}
"/" {printf("\t||| SYMBOL: %s\n", yytext); return DIV;}
"%" {printf("\t||| SYMBOL: %s\n", yytext); return MOD;}

"==" {printf("\tooo XXXXXX %s\n", yytext); return EQ;}
"!=" {printf("\tooo XXXXXX %s\n", yytext); return DIF;}
">" {printf("\tooo XXXXXX %s\n", yytext); return GR;}
"<" {printf("\tooo XXXXXX %s\n", yytext); return LE;}
">=" {printf("\tooo XXXXXX %s\n", yytext); return GREQ;}
"<=" {printf("\tooo XXXXXX %s\n", yytext); return LEEQ;}

"||" {printf("\tooo YYYYYY %s\n", yytext); return OR;}
"&&" {printf("\tooo YYYYYY %s\n", yytext); return AND;}
"!" {printf("\tooo YYYYYY %s\n", yytext); return NOT;}

"(" {printf("\t... MMMMMM %s\n", yytext); return LEFT_PAR;}
")" {printf("\t... MMMMMM %s\n", yytext); return RIGHT_PAR;}
"{" {printf("\t... MMMMMM %s\n", yytext); return LEFT_C_BRA;}
"}" {printf("\t... MMMMMM %s\n", yytext); return RIGHT_C_BRA;}
"[" {printf("\t... MMMMMM %s\n", yytext); return LEFT_BRA;}
"]" {printf("\t... MMMMMM %s\n", yytext); return RIGHT_BRA;}

";" {printf("\t... MMMMMM %s\n", yytext); return DELIM;}
"=" {printf("\t... MMMMMM %s\n", yytext); return ASSIGN;}
"," {printf("\t... MMMMMM %s\n", yytext); return COMMA;}

{integer} {printf("\tvvv INTEGER: %s\n", yytext); return _INT;}
{signed_integer} {printf("\tvvv SIGNED INTEGER: %s\n", yytext); return _S_INT;}
{character} {printf("\twww CHARACTER: %s\n", yytext); return _CHAR;}
{identifier} {printf("\txxx IDENTIFIER: %s\n", yytext); return _IDENT;}
{white_spaces} {/* Ignore whitespaces. */}

<include_directive>[ \t]*      /* Ignore whitespaces. */
<include_directive>[^ \t\n]+ { /* Getting filename. */
     yyin=fopen(yytext, "r");
     
     if(!yyin)
          printf("\t\tERROR: could not include the selected file.");
     
     yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
     
     BEGIN(INITIAL);
}
                 
<<EOF>> {
     yypop_buffer_state();
     
     if(!YY_CURRENT_BUFFER){
          yyterminate();
     }
}
						    
%%
