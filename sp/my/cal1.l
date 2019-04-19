%{  
    #include"y.tab.h"
    #include<math.h>
%}
%%

[a-z]+    {
                yylval=*yytext;
                return VARIABLE;
            }
            
[0-9]+      {
                yylval=atoi(yytext);
                return INTEGER;
            }
[-+*/()=\n] {
                return *yytext;
            }

[\t]        ;
         
%%
