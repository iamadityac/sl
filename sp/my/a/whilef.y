%token ID NUM WHILE
%right '='
%left '+' '-'
%left '*' '/'
%left MINUS
%%

S : WHILE{label1();} '(' E ')'{label2();} E ';'{label3();}
  
E :V '='{push();} E{codegen_assign();}
  | E '+'{push();} E{codegen();}
  | E '-'{push();} E{codegen();}
  | E '*'{push();} E{codegen();}
  | E '/'{push();} E{codegen();}
  | '(' E ')'
  | '-'{push();} E{codegen_umin();} %prec MINUS
  | V
  | NUM{push();}
  ;
V : ID {push();}
  ;
%%

#include"lex.yy.c"
#include<ctype.h>
char st[100][10];
int top=0;
char i_[2]="0";
char temp[2]="t";
char tt[3]="t0";
int lnum=1;
int start=1;
main()
 {
 printf("Enter the expression : ");
 yyparse();
 }

push()
 {
  strcpy(st[++top],yytext);
 }

codegen()
 {
 printf("");
 strcpy(temp,"t");
 strcat(temp,i_);
  printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
  top-=2;
 strcpy(st[top],temp);
 i_[0]++;
 }

codegen_umin()
 {
 strcpy(temp,"t");
 strcat(temp,i_);
 printf("%s = -%s\n",temp,st[top]);
 top--;
 strcpy(st[top],temp);
 i_[0]++;
 }

codegen_assign()
 {
 printf("%s = %s\n",st[top-2],st[top]);
 top-=2;
 }


label1()
{
printf("\nL%d: \n",lnum++);
}

label2()
{
 strcpy(temp,"t");
 strcat(temp,i_);
 printf("%s = not %s\n",temp,st[top]);
 printf("if %s goto End\n",temp);
 i_[0]++;
 }

label3()
{
printf("goto L%d \n",start);
printf("End: end of while loop \n\n");
}
