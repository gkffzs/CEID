%{
	#include <stdio.h>
	#include <math.h>
	void yyerror(char *); 
	extern FILE *yyin;								
	extern FILE *yyout;
	extern yylineno;
	int errors;								
%}

%token IF ELSE INTEGER CHAR VOID CLASS NEW RETURN WHILE
%token PUBLIC PROTECTED PRIVATE
%token STATIC ABSTRACT FINAL
%token THIS SUPER
%token ADD SUB MUL DIV MOD
%token EQ DIF GR LE GREQ LEEQ
%token OR AND NOT
%token _INT _S_INT _CHAR _IDENT
%token LEFT_PAR RIGHT_PAR LEFT_C_BRA RIGHT_C_BRA LEFT_BRA RIGHT_BRA
%token DELIM ASSIGN COMMA

%right ASSIGN
%left OR AND
%left EQ DIF GR LE GREQ LEEQ
%left ADD SUB
%left MUL DIV MOD
%right NOT

%%

/***********************************************************************************************************************/

main_class: class_declaration
          | main_class class_declaration
          ;

class_declaration: CLASS _IDENT class_body {printf("\n------- VALID CLASS.\n\n");}
                 ;

class_body: LEFT_C_BRA variable_declaration_area constructor_declaration method_declaration RIGHT_C_BRA
          ;

/***********************************************************************************************************************/

variable_declaration_area: variable_declaration
                         | variable_declaration_area variable_declaration
                         ;

variable_declaration: type variable_declarators DELIM
                    | array_declarator DELIM
                    ;

type: INTEGER
    | CHAR
    ;

variable_declarators: variable_declarator
                    | variable_declarators COMMA variable_declarator
                    ;

variable_declarator: variable_declarator_name
                   | variable_declarator_name ASSIGN variable_init
                   ;

variable_declarator_name: _IDENT
                        ;
                        
variable_init: expression
             | _CHAR
             ;

array_declarator: array_declarator_name ASSIGN NEW type LEFT_BRA _INT RIGHT_BRA
                ;
                
array_declarator_name: _IDENT
                     ;

/***********************************************************************************************************************/

constructor_declaration: constructor_modifier constructor_declarator constructor_body
;

constructor_modifier: PUBLIC
                    | PROTECTED
                    | PRIVATE
                    ;

constructor_declarator: constructor_name LEFT_PAR parameter_list RIGHT_PAR
                      ;

constructor_name: _IDENT
                ;

parameter_list: parameter
              | parameter_list COMMA parameter
              ;

parameter: /* empty */
         | type variable_declarator_name
         ;

constructor_body: LEFT_C_BRA explicit_constructor_invocation block_statements RIGHT_C_BRA
                | LEFT_C_BRA explicit_constructor_invocation RIGHT_C_BRA /* check all cases */
                ;

explicit_constructor_invocation: /* empty */
                               | THIS LEFT_PAR explicit_parameter_list RIGHT_PAR DELIM
                               | SUPER LEFT_PAR explicit_parameter_list RIGHT_PAR DELIM
                               ;

explicit_parameter_list: explicit_parameter
                       | explicit_parameter_list COMMA explicit_parameter
                       ;

explicit_parameter: /* empty */
                  | _IDENT
                  ;

/***********************************************************************************************************************/

method_declaration: method_header method_body
;

method_header: method_modifiers result_type method_declarator 
;

method_modifiers: /* empty */
                | method_modifier
                | method_modifiers COMMA method_modifier
                ;

method_modifier: PUBLIC
               | PROTECTED
               | PRIVATE
               | STATIC
               | ABSTRACT
               | FINAL
               ;

result_type: type
           | VOID
           ;

method_declarator: method_name LEFT_PAR parameter_list RIGHT_PAR
                 ;
                 
method_name: _IDENT
           ;

method_body: LEFT_C_BRA variable_declaration block_statements RIGHT_C_BRA
           | LEFT_C_BRA variable_declaration RIGHT_C_BRA
           | DELIM
           ;

/***********************************************************************************************************************/

block: LEFT_C_BRA block_statements RIGHT_C_BRA
     ;

block_statements: block_statement
                | block_statements block_statement
                ;

block_statement: local_variable_declaration
               | statement
               ;

local_variable_declaration: type variable_declarators DELIM
                          ;

statement: if_statement
         | if_else_statement
         | while_statement
         | statement_without_trailing
         ;

statement_no_short: if_else_statement_no_short
                  | while_statement_no_short
                  | statement_without_trailing
                  ;

statement_without_trailing: block
                          | empty_statement
                          | expression_statement
                          | return_statement
                          ;

empty_statement: DELIM
               ;

expression_statement: expression
                    ;

if_statement: IF LEFT_PAR conditional_expression RIGHT_PAR statement
            ;

if_else_statement: IF LEFT_PAR conditional_expression RIGHT_PAR statement_no_short ELSE statement
                 ;

if_else_statement_no_short: IF LEFT_PAR conditional_expression RIGHT_PAR statement_no_short ELSE statement_no_short 
                          ;

while_statement: WHILE LEFT_PAR conditional_expression RIGHT_PAR statement
               ;

while_statement_no_short: WHILE LEFT_PAR conditional_expression RIGHT_PAR statement_no_short
                        ;

return_statement: RETURN expression
                ;
                
/***********************************************************************************************************************/

expression: number
          | _IDENT
          | LEFT_PAR expression RIGHT_PAR
          | assignment_expression
          | numerical_expression
          | logical_expression
          | array_expression
          ;

number: _INT
      | LEFT_PAR _S_INT RIGHT_PAR
      ;

conditional_expression: /* empty */
                      | expression
                      | relational_expression
                      ;
   
assignment_expression: expression ASSIGN expression
                     ;

numerical_expression: expression ADD expression
                    | expression SUB expression
                    | expression MUL expression
                    | expression DIV expression
                    | expression MOD expression
                    ;

relational_expression: expression EQ expression
                     | expression DIF expression
                     | expression GR expression
                     | expression LE expression
                     | expression GREQ expression
                     | expression LEEQ expression
                     ;
                     
logical_expression: expression OR expression
                  | expression AND expression
                  | NOT expression
                  ;

array_expression: _IDENT LEFT_BRA _INT RIGHT_BRA
                ;

/***********************************************************************************************************************/

%%								    

void yyerror(char *s){
     errors++;
	printf("\n------- ERROR AT LINE #%d.\n\n", yylineno);
}									

int main (int argc, char **argv){
	argv++;
	argc--;
	errors=0;
	  
	if(argc>0)
		yyin=fopen(argv[0], "r");
	else
		yyin=stdin;
			
	yyparse();
	
	if(errors==0)
	     printf("------- PARSING COMPLETED, VALID PROGRAM.\n\n"); 
	  
	return 0;
}							
