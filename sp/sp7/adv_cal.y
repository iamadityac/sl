%{
       #include<stdio.h>
       #include<math.h>
%}

%union				//to define possible symbol types
{ double p;}
%token<p>num
%token SIN COS TAN LOG SQRT

/*Defining the Precedence and Associativity*/
 %left '+''-'			//lowest precedence
%left '*''/'			//highest precedenc
%nonassoc uminu			//no associativity
%type<p>exp			//Sets the type for non - terminal
%%

/* for storing the answer */
ss: exp {printf("Answer =%g\n",$1);}

/* for binary arithmatic operators */
exp :    exp'+'exp      { $$=$1+$3; }
       |exp'-'exp      { $$=$1-$3; }
       |exp'*'exp      { $$=$1*$3; }
       |exp'/'exp      {
                               if($3==0)
                               {
                                       printf("Divide By Zero");
//exit(0);
                               }
                               else $$=$1/$3;
                       }
       |'-'exp         {$$=-$2;}
       |SIN'('exp')'   {$$=sin($3);}
       |COS'('exp')'   {$$=cos($3);}
       |TAN'('exp')'   {$$=tan($3);}
       |LOG'('exp')'   {$$=log($3);}
       |SQRT'('exp')'  {$$=sqrt($3);}
       |num;
 	|'('exp')'      {$$=$2;}
%%

/* extern FILE *yyin; */
main()
{
       do
       {
               yyparse();	/* repeatedly tries to parse the 				sentence until the i/p runs out */
       }while(1);

}

yyerror(s)			/* used to print the error message when an 				error is parsing of i/p */

char *s;
{
       printf("ERROR");
}

