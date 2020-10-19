#include<bits/stdc++.h>
using namespace std;
using uch=unsigned char;
char etb[64];
void init_tb(){
	int p=0;
	for(int i='A';i<='Z';i++)etb[p++]=i;
	for(int i='a';i<='z';i++)etb[p++]=i;
	for(int i='0';i<='9';i++)etb[p++]=i;
	etb[p++]='+';etb[p++]='/';
}
int to_base64(const char *c,char *o,int l){
	int p=0;
	for(int i=0;i<l;i+=3){
		int s=(uch)c[i]<<16|(i+1<l)*(uch)c[i+1]<<8|(i+2<l)*(uch)c[i+2];
		o[p++]=etb[s>>18];o[p++]=etb[s>>12&63];
		o[p++]=i+1<l?etb[s>>6&63]:'=';
		o[p++]=i+2<l?etb[s&63]:'=';
	}
	o[p]=0;return p;
}

char buf[1<<20],obuf[1<<20];

int main(){
	init_tb();
	freopen("input","r",stdin);

	int l=fread(buf,1,1<<20,stdin);
	to_base64(buf,obuf,l);
	freopen("template.cpp","r",stdin);
	freopen("output.cpp","w",stdout);
	for(int i=0;i<7;i++){
		fgets(buf,1<<10,stdin);
		fputs(buf,stdout);
	}
	putchar('"');
	fputs(obuf,stdout);
	putchar('"');
	while(fgets(buf,1<<10,stdin))fputs(buf,stdout);
	return 0;
}
