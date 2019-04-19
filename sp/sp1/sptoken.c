#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct symtable
{
	int sym_cnt,addr;
	char sym_name[10];
}st[10];

struct littable
{
	int lit_cnt,addr;
	char lit_name[10];
}lt[10];

struct poolt
{
	int lit_no;
}pt[10];

int ist=0,ilt=0,ipt=0,poolflag=0;
char mot[10][10]={"MOVER","MOVEM","ADD","SUB","MULT","DIV","COMP","PRINT","READ","BC"};
char pot[5][10]={"START","END","LTORG","ORIGIN","EQU"};
char reg[5][10]={"AREG","BREG","CREG","DREG"};
char dl[2][10]={"DC","DS"};
char bc[4][10]={"LT","LE","GT","GE"};

void accept(struct symtable *st)
{
	printf("\n\tEnter the table Contents (Symbol_count,Name,Address) : ");
	scanf("%d%s%d",&st->sym_cnt,st->sym_name,&st->addr);
}

void disp(struct symtable *st)
{
	printf("\n\t%d\t%s\t%d",st->sym_cnt,st->sym_name,st->addr);
}

void dispst(struct symtable *st)
{
	printf("\n\t%d\t %s\t   %d",st->sym_cnt,st->sym_name,st->addr);
}

void displt(struct littable *lt)
{
	printf("\n\t%d\t %s\t   %d",lt->lit_cnt,lt->lit_name,lt->addr);
}

void add_st(int cnt,char name[10],int addr)
{
	st[ist].sym_cnt=cnt;
	strcpy(st[ist].sym_name,name);
	st[ist].addr=addr;
	ist++;
}

void add_lt(int cnt,char name[10],int addr)
{
	lt[ilt].lit_cnt=cnt;
	strcpy(lt[ilt].lit_name,name);
	lt[ilt].addr=addr;
	ilt++;
}

int search_mot(char key[10])
{
	int i;
	for(i=0;i<10;i++)
		if(strcmp(key,mot[i])==0)
			return i+1;
	return -1;		
}

int search_pot(char key[10])
{
	int i;
	for(i=0;i<5;i++)
		if(strcmp(key,pot[i])==0)
			return i+1;
	return -1;		
}

int search_reg(char key[10])
{
	int i;
	for(i=0;i<5;i++)
		if(strcmp(key,reg[i])==0)
			return i+1;
	return -1;		
}

int search_dl(char key[10])
{
	int i;
	for(i=0;i<2;i++)
		if(strcmp(key,dl[i])==0)
			return i+1;
	return -1;		
}

int search_st(char key[10])
{
	int i;
	for(i=0;i<10;i++)
		if(strcmp(key,st[i].sym_name)==0)
			return st[i].sym_cnt;
	return -1;		
}

int search_lt(char key[10],int i)
{
	for(;i<10;i++)
		if(strcmp(key,lt[i].lit_name)==0)
			return lt[i].lit_cnt;
	return -1;		
}

int search_bc(char key[10])
{
	int i;
	for(i=0;i<4;i++)
		if(strcmp(key,bc[i])==0)
			return i+1;
	return -1;		
}

int main()
{
	FILE *fp,*fp1;
	
	int n,s1,i,cnt,LC,num;
	char buffer[180],t1[10],t2[10],t3[10],t4[10];
	
	printf("\n\t\t**Two Pass assembler (Pass #1)**\n");
	
	fp=fopen("sp1.txt","r");
	fp1=fopen("op.txt","w");
	
	while(fgets(buffer,180,fp))
	{
		n=sscanf(buffer,"%s%s%s%s",t1,t2,t3,t4);
		switch(n)
		{
			case 1:
				cnt=search_pot(t1);
				if(cnt==1)
				{
					fprintf(fp1,"\n\t\t(AD, 01) - (C, 0)");
					LC=0;
				}
				else if(cnt==2 || cnt==3)
				{
					for(i=(pt[ipt-1].lit_no)-1;i<ilt;i++)
					{
						lt[i].addr=LC;
						fprintf(fp1,"\n\t%d] (AD, 3) - %s",LC,&lt[i].lit_name[1]);
						LC++;
					}
					if(cnt==2)
					{
						fprintf(fp1,"\n\t%d] (AD, 2) - -",LC);
						LC++;
					}
					poolflag=0;
				}
				else if(cnt==4)
					LC=0;
				else if(cnt==-1)
					printf("\n\t ERROR \n");
			break;
			
			case 2:
				if((cnt=search_pot(t1))!=-1)
				{
					if(cnt==1)
					{
						LC=atoi(t2);
						fprintf(fp1,"\n\t(AD, 01) - (C, %d)",LC);
					}
					else if(cnt==4)
					{
						if(search_st(t2)==-1)
							LC=atoi(t2);
						else
							LC=st[search_st(t2)-1].addr;
					}
				}
				else if((cnt=search_mot(t1))!=-1)
				{
					if(cnt==8 || cnt==9)
					{
						if(t2[0]=='=')
						{
							if((num=search_lt(t2,pt[ipt-1].lit_no))==-1)
							{
								add_lt(ilt+1,t2,0);
								if(poolflag==0)
								{
									pt[ipt++].lit_no=ilt;
									poolflag=1;
								}
								num=ilt;
							}
							fprintf(fp1,"\n\t%d] (IS, %d) - (L, %d)",LC,cnt,num);
						}	
						else
						{
							if((num=search_st(t2))==-1)
							{
								add_st(ist+1,t2,0);
								num=ist;
							}
							fprintf(fp1,"\n\t%d] (IS, %d) - (S, %d)",LC,cnt,num);
						}
						LC++;		
					}
				}
				else
					printf("\n\tERROR");
			break;
			
			case 3:
				if((cnt=search_mot(t1))!=-1)
				{
					if(cnt==1 || cnt==2 || cnt==3 || cnt==4 || cnt==5 || cnt==6 || cnt==7)
					{
						if(t3[0]=='=')
						{
							if((num=search_lt(t3,pt[ipt-1].lit_no))==-1)
							{
								add_lt(ilt+1,t3,0);
								if(poolflag==0)
								{
									pt[ipt++].lit_no=ilt;
									poolflag=1;
								}
								num=ilt;
							}
							fprintf(fp1,"\n\t%d] (IS, %d) %d (L, %d)",LC,cnt,search_reg(t2),num);
						}	
						else
						{
							if((num=search_st(t3))==-1)
							{
								add_st(ist+1,t3,0);
								num=ist;
							}
							fprintf(fp1,"\n\t%d] (IS, %d) %d (S, %d)",LC,cnt,search_reg(t2),num);
						}
						LC++;		
					}
					else if(cnt==10)
					{
						if((n=search_bc(t2))!=-1)
						{
							if(t3[0]=='=')
							{
								if((num=search_lt(t3,pt[ipt-1].lit_no))==-1)
								{
									add_lt(ilt+1,t3,0);
									if(poolflag==0)
									{
										pt[ipt++].lit_no=ilt;
										poolflag=1;
									}
									num=ilt;
								}
								fprintf(fp1,"\n\t%d] (IS, %d) %d (L, %d)",LC,cnt,n,num);
							}	
							else
							{
								if((num=search_st(t3))==-1)
								{
									add_st(ist+1,t3,0);
									num=ist;
								}
								fprintf(fp1,"\n\t%d] (IS, %d) %d (S, %d)",LC,cnt,n,num);
							}
							LC++;								
						}
						else
						 printf("\n\tERROR 'BC instruction'\n");							
					}
				}
				else if((cnt=search_mot(t2))!=-1)
				{
					if((num=search_st(t1))==-1)
					{
						add_st(ist+1,t1,0);
						num=ist;
					}
					st[num-1].addr=LC;
				
					if(cnt==8 || cnt==9)
					{
						if(t3[0]=='=')
						{
							if((num=search_lt(t3,pt[ipt-1].lit_no))==-1)
							{
								add_lt(ilt+1,t3,0);
								if(poolflag==0)
								{
									pt[ipt++].lit_no=ilt;
									poolflag=1;
								}
								num=ilt;
							}
							fprintf(fp1,"\n\t%d] (IS, %d) - (L, %d)",LC,cnt,num);
						}	
						else
						{
							if((num=search_st(t3))==-1)
							{
								add_st(ist+1,t3,0);
								num=ist;
							}
							fprintf(fp1,"\n\t%d] (IS, %d) - (S, %d)",LC,cnt,num);
						}
						LC++;		
					}
				}
				else if((cnt=search_pot(t2))!=-1)
				{
					if(cnt==5)
					{
						if((cnt=search_st(t3))==-1 || st[search_st(t3)-1].addr==0)
						{
							printf("\n\tError EQU t3 \n");
							break;
						}	
						num=search_st(t1);
						st[num-1].addr=st[cnt-1].addr;
					}
				}
				else if((cnt=search_dl(t2))!=-1)
				{
					if(cnt==1 || cnt==2)
					{
						fprintf(fp1,"\n\t%d] -       - %d",LC,atoi(t3));
						if((num=search_st(t1))==-1)
						{
							add_st(ist+1,t1,0);
							num=ist;
						}
						st[num-1].addr=LC;		
						if(cnt==1)
							LC++;
						else if(cnt==2)
							LC+=atoi(t3);		
					}
				}
				else
					printf("\n\tERROR :");
			break;
			
			case 4:
				if((num=search_st(t1))==-1)
				{
					add_st(ist+1,t1,0);
					num=ist;
				}
				st[num-1].addr=LC;
					
				if((cnt=search_mot(t2))!=-1)
				{
					if(cnt==1 || cnt==2 || cnt==3 || cnt==4 || cnt==5 || cnt==6 || cnt==7)
					{
						if(t4[0]=='=')
						{
							if((num=search_lt(t4,pt[ipt-1].lit_no))==-1)
							{
								add_lt(ilt+1,t4,0);
								if(poolflag==0)
								{
									pt[ipt++].lit_no=ilt;
									poolflag=1;
								}
								num=ilt;
							}
							fprintf(fp1,"\n\t%d] (IS, %d) %d (L, %d)",LC,cnt,search_reg(t3),num);
						}	
						else
						{
							if((num=search_st(t4))==-1)
							{
								add_st(ist+1,t4,0);
								num=ist;
							}
							fprintf(fp1,"\n\t%d] (IS, %d) %d (S, %d)",LC,cnt,search_reg(t3),num);
						}
						LC++;		
					}
					else if(cnt==10)
					{
						if((n=search_bc(t3))!=-1)
						{
							if(t4[0]=='=')
							{
								if((num=search_lt(t4,pt[ipt-1].lit_no))==-1)
								{
									add_lt(ilt+1,t4,0);
									if(poolflag==0)
									{
										pt[ipt++].lit_no=ilt;
										poolflag=1;
									}
									num=ilt;
								}
								fprintf(fp1,"\n\t%d] (IS, %d) %d (L, %d)",LC,cnt,n,num);
							}	
							else
							{
								if((num=search_st(t4))==-1)
								{
									add_st(ist+1,t4,0);
									num=ist;
								}
								fprintf(fp1,"\n\t%d] (IS, %d) %d (S, %d)",LC,cnt,n,num);
							}
							LC++;								
						}
						else
						 printf("\n\tERROR 'BC instruction'\n");							
					}
				}
			break;		
		}
		//printf("\n\tTokens : %d\n\t%s  %s  %s  %s\n",n,t1,t2,t3,t4);
	}
	fclose(fp);
	fclose(fp1);
	
	/*printf("\n\tHow many symbols u want to enter?	: ");
	scanf("%d",&s1);
	
	for(i=0;i<s1;i++)
		accept(&st[i]);
	
	printf("\n\n\tSymbol Table : \n");
	printf("\n\tCount\tName\tAddr");
	for(i=0;i<s1;i++)
		disp(&st[i]);*/
	
	printf("\n\tSymbol Table: \n\t");
	printf("\n\tSym_Cnt  Sym_Name  Addr");	
	for(i=0;i<ist;i++)
		dispst(&st[i]);
	
	printf("\n\n\tLiteral Table: \n\t");
	printf("\n\tLit_Cnt  Lit_Name  Addr");		
	for(i=0;i<ilt;i++)
		displt(&lt[i]);
		
	printf("\n\n\tPool Table: \n\t");
	printf("\n\tIndex");	
	for(i=0;i<ipt;i++)
		printf("\n\t%d",pt[i].lit_no);
		
	printf("\n\n");	
	return 0;
}





