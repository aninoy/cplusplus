#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <ctype.h>
#include <stdlib.h>

int term();
int factor();


char key[][10] = { {"if"}, {"for"}, {"else"}, {"while"}, {"main"}, {"include"} };
char dttype[][10] = { {"int"}, {"char"}, {"void"} };
char *buf, *pos, *ptr, token[50], *temp;
FILE *f1;


enum{SEMICOLON, IF, ELSE, DTYPE, MAIN, WHILE, FOR, IDENTIFIER, NUMBER, ENOF,
     UNKNOWN, LEFTP, RIGHTP, ISEQUALTO, PLUS, MINUS, EQUAL, GE, GT, LT, LE,
     NE, CURLO, CURLC, COMMA, PERIOD, COLON, TERN, DIV, MUL, SQUOTES, DQUOTES,
     SQO, SQC, UNSC, REM, NOT, HASH, NLINE, INCLUDE, OR, AND};
int line, tokentype, state, type;
char a[][10]={{"char"},{"int"}};
void eat_spaces() {
	while(*buf == ' '||*buf == '\t'||*buf == '\n') {
		if(*buf=='\n'){
			if(!fgets(buf,200,f1)){
				//cout<<"End of file";
				getch();
				exit(0);
			}
			continue;
		}
		buf++;
	}
}

struct sym_ta {
	char name[30];
	char type[10];
}symbol_table[40];


int symno=0;

int scanner() {
	eat_spaces();
	switch (*buf) {
		case ';':
			buf++;
			return SEMICOLON;
		case EOF:
			buf++;
			return ENOF;
		case '(':
			buf++;
			return LEFTP;
		case ')':
				buf++;
			return RIGHTP;
		case '+':
			buf++;
			return PLUS;
		case '-':

			buf++;
			return MINUS;
		case '=':
			if(*(buf+1)=='='){
				buf+=2;
				strcpy("==",token);
				return ISEQUALTO;
			}
			buf++;
			return EQUAL;
		case '>':
			if(*(buf+1)=='='){

				buf+=2;
				strcpy(">=",token);
				return GE;
			}

			buf++;
			return GT;
		case '<':
			if(*(buf+1)=='='){

				buf+=2;
				strcpy("<=",token);
				return LE;
			}

			buf++;
			return LT;
		case '{':

			buf++;
			return CURLO;
		case '}':

			buf++;
			return CURLC;
		case ',':

			buf++;
			return COMMA;
		case '.':
			buf++;
			return PERIOD;
		case ':':

			buf++;
			return COLON;
		case '?':

			buf++;
			return TERN;
		case '*':

			buf++;
			return MUL;
		case '/':

			buf++;
			return DIV;
		case '\'':

			buf++;
			return SQUOTES;
		case '"':

			buf++;
			return DQUOTES;
		case '[':

			buf++;
			return SQO;
		case ']':

			buf++;
			return SQC;
		case '!':
			if(*(buf+1)=='='){

				buf+=2;
				strcpy("!=",token);
				return NE;
			}

			buf++;
			return NOT;
		case '%':

			buf++;
			return REM;
		case '#':

			buf++;
			return HASH;
		case '&':

			buf++;
			return AND;
		case '|':

			buf++;
			return OR;
		case '\n':
			buf++;
			return NLINE;
		default:
			pos = token;
			if(isalpha(*buf)) {
				while(isalnum(*buf)||*buf == '_') {
					*pos = *buf;
					pos++;
					buf++;
				}
				if(*buf!=','&&*buf!=';'&&*buf!='='&&*buf!=')'
				   &&*buf!=']'&&*buf!='-'&&*buf!='+'&&*buf!='*'
				   &&*buf!='/'&&*buf!='<'&&*buf!='>'&&*buf!='&'
				   &&*buf!='|'&&*buf!=' '&&*buf!='\n'&&*buf!='!'
				   &&*buf!='('&&*buf!='['&&*buf!='}'&&*buf!='{') {
					while(*buf!=','&&*buf!=';'&&*buf!='='&&*buf!=')'
						&&*buf!=']'&&*buf!='-'&&*buf!='+'&&*buf!='*'
						&&*buf!='/'&&*buf!='<'&&*buf!='>'&&*buf!='&'
						&&*buf!='|'&&*buf!=' '&&*buf!='\n'&&*buf!='('
						&&*buf!='['&&*buf!='!'&&*buf!='}'&&*buf!='{') {
						*pos=*buf;
						pos++;
						buf++;
					}
					*pos='\0';
					return UNKNOWN;
				}
				*pos = '\0';
				int fl = 0;
				for(int i = 0; i < 6; i++) {
					if(!strcmp(token, key[i])) {
						fl = 1;
						break;
					}
				}
				if(fl) {
					if(!strcmp(token,"if")) {
						return IF;
					} else if(!strcmp(token,"else")) {
						return ELSE;
					} else if(!strcmp(token,"while")) {
						return WHILE;
					} else if(!strcmp(token,"for")) {
						return FOR;
					} else if(!strcmp(token,"main")) {
						return MAIN;
					} else {
						return INCLUDE;
					}
				}
				fl = 0;
				for(i = 0; i < 3; i++) {
					if(!strcmp(token, dttype[i])) {
						fl = 1;
						break;
					}
				}
				if(fl) {
					return DTYPE;
				} else {
					return IDENTIFIER;
				}
			} else if(isdigit(*buf)) {
				while(isdigit(*buf)) {
					*pos = *buf;
					pos++;
					buf++;
				}
				if(*buf!=','&&*buf!=';'&&*buf!='='&&*buf!=')'
				   &&*buf!=']'&&*buf!='-'&&*buf!='+'&&*buf!='*'
				   &&*buf!='/'&&*buf!='<'&&*buf!='>'&&*buf!='&'
				   &&*buf!='|'&&*buf!=' '&&*buf!='\n'&&*buf!='!'
				   &&*buf!='('&&*buf!='['&&*buf!='}'&&*buf!='{') {
					while(*buf!=','&&*buf!=';'&&*buf!='='&&*buf!=')'
						&&*buf!=']'&&*buf!='-'&&*buf!='+'&&*buf!='*'
						&&*buf!='/'&&*buf!='<'&&*buf!='>'&&*buf!='&'
						&&*buf!='|'&&*buf!=' '&&*buf!='\n'&&*buf!='('
						&&*buf!='['&&*buf!='!'&&*buf!='}'&&*buf!='{') {
						*pos=*buf;
						pos++;
						buf++;
					}
					*pos = '\0';
					return UNKNOWN;
				}
				*pos = '\0';
				return NUMBER;
			} else {
				buf++;
				return UNKNOWN;
			}
	}
}

int declarations() {
	do {
		cout<<"\n";
		cout<<buf<<endl<<endl;
		while(*buf != '\n'&&*buf != '\0') {
			switch(state) {
				case 7:
					if(scanner()!=IDENTIFIER){
						cout<<"Expected an Identifier\n";
						return 0;
					}
					strcpy(symbol_table[symno].name,token);
					strcpy(symbol_table[symno++].type,a[type]);
					state=8;
					break;
				case 8:
					tokentype=scanner();
					if(tokentype==COMMA){
						state=7;
						break;
					} else if(tokentype==SQO){
						state=9;
						break;
					} else if(tokentype==SEMICOLON){
						state=5;
						return 1;
					} else if(tokentype==EQUAL){
						state=12;
						break;
					} else {
						cout<<"Expected [ or ; or , or =\n";
						return 0;
					}
				case 9:
					if(scanner()!=NUMBER){
						cout<<"Expected an Number\n";
						return 0;
					}
					state=10;
					break;
				case 10:
					if(scanner()!=SQC){
						cout<<"Expected ]\n";
						return 0;
					}
					state=11;
					break;
				case 11:
					tokentype=scanner();
					if(tokentype==COMMA){
						state=7;
					} else if(tokentype==SEMICOLON){
						state=5;
						return 1;
					} else if(tokentype==EQUAL){
						state=12;
					} else {
						cout<<"Expected ; or , or =\n";
						return 0;
					}
					break;
				case 12:
					tokentype=scanner();
					if(tokentype==NUMBER || tokentype==IDENTIFIER){
						state=13;
					} else {
						cout<<"Expected a number or an identifier\n";
						return 0;
					}
					break;
				case 13:
					tokentype=scanner();
					if(tokentype==COMMA){
						state=7;
					} else if(tokentype==SEMICOLON){
						state=5;
						return 1;
					} else {
						cout<<"Expected ; or ,\n";
						return 0;
					}
					break;
			}
		}
		line++;
		getch();
	}while(fgets(buf, 200, f1));
	return 0;
}

int mulop(){
	do{
		cout<<"\n";
		cout<<buf<<" in mulop function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			tokentype=scanner();
			if(tokentype!=MUL&&tokentype!=DIV&&tokentype!=REM){
				//cout<<"Mulop fail\n";
				return 0;
			} else {
				//cout<<"Mulop success\n";
				return 1;
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int addop(){
	do{
		cout<<"\n";
		cout<<buf<<" in addop function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			tokentype=scanner();
			if(tokentype!=PLUS&&tokentype!=MINUS){
				//cout<<"Addop fail\n";
				return 0;
			} else {
				//cout<<"Addop success\n";
				return 1;
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int factor(){
	do{
		cout<<"\n";
		cout<<buf<<" in factor function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			tokentype=scanner();
			if(tokentype!=NUMBER&&tokentype!=IDENTIFIER){
				//cout<<"Factor fail\n";
				return 0;
			} else {
				//cout<<"Factor success\n";
				return 1;
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}


int tprime(){
	do{
		cout<<"\n";
		cout<<buf<<" in tprime function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			if(!mulop()) {
				//cout<<"Tprime fail\n";
				return 0;
			} else if(!factor()) {
				//cout<<"Tprime fail\n";
				return 0;
			} else {
				temp = buf;
				if(!tprime()) {
					buf=temp;
				}
				//cout<<"Tprime success\n";
				return 1;
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int seprime(){
	do{
		cout<<"\n";
		cout<<buf<<" in seprime function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			if(!addop()) {
				//cout<<"Sprime fail\n";
				return 0;
			} else if(!term()) {
				//cout<<"Sprime fail\n";
				return 0;
			} else {
				temp = buf;
				if(!seprime()) {
					buf=temp;
				}
				//cout<<"SPrime success\n";
				return 1;
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int term() {
	do{
		cout<<"\n";
		cout<<buf<<" in term function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			if(!factor()) {
				//cout<<"Term fail\n";
				return 0;
			} else {
				temp = buf;
				if(!tprime()) {
					buf=temp;
				}
				//cout<<"Term Success\n";
				return 1;
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int simple_expr() {
	do{
		cout<<"\n";
		cout<<buf<<" in simple_expr function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			if(!term()) {
				//cout<<"S_expr fail\n";
				return 0;
			} else {
				temp = buf;
				if(!seprime()) {
					buf=temp;
				}
				//cout<<"S_expr Success\n";
				return 1;
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int assig_stmt() {
	do{
		cout<<"\n";
		cout<<buf<<" in assign_stmt function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			if((tokentype=scanner())!=EQUAL) {
				//cout<<"Assign_stmt fail\n";
				return 0;
			} else {
				return simple_expr();
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int rel_stmt() {
	do{
		cout<<"\n";
		cout<<buf<<" in rel_stmt function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			tokentype=scanner();
			if(tokentype!=LT&&tokentype!=LE&&tokentype!=GT&&tokentype!=GE&&tokentype!=NE&&tokentype!=ISEQUALTO) {
				//cout<<"Rel_stmt fail\n";
				return 0;
			} else {
				return simple_expr();
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int statements();

int dprime(){
	do{
		cout<<"\n";
		cout<<buf<<" in dprime function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			if(scanner()!=ELSE) {
				//cout<<"dprime fail\n";
				return 0;
			} else {
				tokentype=scanner();
				if(!statements()) {
					//cout<<"dprime fail\n";
					return 0;
				} else {
					return 1;
				}
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int decision_stmt(){
	do{
		cout<<"\n";
		cout<<buf<<" in decision_stmt function"<<endl<<endl;
		getch();
		while(*buf != '\n'&&*buf != '\0') {
			if((tokentype=scanner())!=LEFTP) {
				//cout<<"Decision_stmt fail\n";
				return 0;
			} else if((tokentype=scanner())==IDENTIFIER){
				if(!rel_stmt()){
					//cout<<"in dec rel fail\n";
					return 0;
				} else if(scanner()!=RIGHTP){
					//cout<<"In decision right parenthesis fail\n";
					return 0;
				} else {
					//cout<<"right parenthesis success\n";
					tokentype=scanner();
					if(!statements()){
						//cout<<"Stmt error\n";
						return 0;
					} else {
						temp = buf;
						if(!dprime()){
							buf = temp;
						}
						//cout<<"dec_stmt success\n";
						return 1;
					}
				}
			} else {
				return 0;
			}
		}
	}while(fgets(buf,200,f1));
	return 0;
}

int loop_stmt(){
	if(tokentype==FOR){
		if(scanner()!=LEFTP){
			return 0;
		} else if(scanner()==IDENTIFIER){
			if(!assig_stmt()){
				return 0;
			} else if(scanner()!=SEMICOLON){
				return 0;
			} else if(scanner()==IDENTIFIER){
				if(!rel_stmt()){
					return 0;
				} else if(scanner()!=SEMICOLON){
					return 0;
				} else if(scanner()==IDENTIFIER){
					if(!assig_stmt()){
						cout<<"assig error\n";
						return 0;
					} else if(scanner()!=RIGHTP){
						cout<<"right parenthesis error\n";
						return 0;
					} else {
						tokentype=scanner();
						if(!statements()){
							return 0;
						} else {
							return 1;
						}
					}
				} else {
					return 0;
				}
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	} else {
		 if(scanner()!=LEFTP){
			return 0;
		} else if(scanner()==IDENTIFIER){
			if(!rel_stmt()){
				return 0;
			} else if(scanner()!=RIGHTP){
				return 0;
			} else {
				tokentype=scanner();
				if(!statements()){
					return 0;
				} else {
					return 1;
				}
			}
		} else {
			return 0;
		}
	}
}

int statements() {
	if(tokentype==IDENTIFIER) {
		if(assig_stmt()){
			tokentype=scanner();
			if(tokentype==SEMICOLON){
				//cout<<"Statement success\n";
				return 1;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	} else if(tokentype==IF) {
		if(decision_stmt()){
			return 1;
		} else {
			return 0;
		}
	} else if(tokentype==WHILE||tokentype==FOR) {
		if(loop_stmt()){
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

int init() {
	while(fgets(buf, 200, f1)) {
		line++;
		cout<<"\n";
		cout<<buf<<endl<<endl;
		while(*buf != '\n'&&*buf != '\0') {
			switch(state) {
				case 1:
					if(scanner()!=MAIN){
						cout<<"Expected main\n";
						return 0;
					}
					state++;
					break;
				case 2:
					if(scanner()!=LEFTP){
						cout<<"Expected (\n";
						return 0;
					}
					state++;
					break;
				case 3:
					if(scanner()!=RIGHTP){
						cout<<"Expected )\n";
						return 0;
					}
					state++;
					break;
				case 4:
					if(scanner()!=CURLO){
						cout<<"Expected {\n";
						return 0;
					}
					state++;
					break;
				case 5:
					tokentype=scanner();
					if(tokentype==CURLC){
						state=6;
					} else if(tokentype==DTYPE){
						if(!strcmp(token,"int")){
							type=1;
						} else {
							type=0;
						}
						state=7;
						if(!declarations()) {
							return 0;
						}
					} else {
						if(!statements()) {
							cout<<"Error\n";
							return 0;
						} else {
							state=5;
						}
					}
					break;
				case 6:
					return 1;
			}
		}
		getch();
	}
	return 1;
}

void main() {
	clrscr();
	cout<<"generating a parser for the given file \n\n";
	char *fname, *str;
	line=0;
	cout<<"Enter the filename : ";
	cin>>fname;
	f1 = fopen(fname, "r+");
	buf = (char *)malloc(200);
	state=1;
	if(!init()){
		cout<<"Error in main():"<<line<<"\n";
	} else {
		cout<<"program analysed successfully\n";
		getch();
		clrscr();
		cout<<"Symbol table is\n";
		cout<<"\n\n";
		cout<<"Name\t\tType\n\n";
		for(int i=0;i<symno;i++){
			cout<<symbol_table[i].name<<"\t\t"<<symbol_table[i].type<<endl;
		}
	}
	free(buf);
	fclose(f1);
	getch();
}