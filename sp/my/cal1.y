%{
    #include<stdio.h>
    char sys[10];
%}

%token VARIABLE INTEGER
%left '-' '+' '*' '/'

%%

ss:ss stat '\n'
  |
  ;
stat:
    exp {printf("Answr is: %d\n",$1);}
    |VARIABLE '=' exp   {sys[$1]=$3;}
exp:
    INTEGER    
    |    VARIABLE   {$$=sys[$1];}
    |   exp '+' exp {$$=$1+$3;}
    |   exp '-' exp {$$=$1-$3;}
    |   exp '*' exp {$$=$1*$3;}
    |   exp '/' exp { $$=$1/$3;}
    ;
%%


void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(){
    while(1)
    yyparse();
}
