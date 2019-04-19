%%
while                return WHILE;
[A-Za-z]([A-Za-z]|[0-9])*    return ID;            // regular expression for Indentifier
[0-9]+             {yylval=atoi(yytext); return NUM;}       // number
[ \t]                 ;
\n                yyterminate();
.                 return yytext[0];
%%

