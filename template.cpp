#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/mman.h>

using namespace std;

const char *prog=

;char dtb[128],buf[1<<20],cmd[128];
void init_tb(){
	int p=0;
	for(int i='A';i<='Z';i++)dtb[i]=p++;
	for(int i='a';i<='z';i++)dtb[i]=p++;
	for(int i='0';i<='9';i++)dtb[i]=p++;
	dtb[(int)'+']=p++;dtb[(int)'/']=p++;
	dtb[(int)'=']=0;
}
int from_base64(const char *c,char *o,int l){
	assert((l&3)==0);int p=0,r=l/4*3;
	for(int i=0;i<l;i+=4){
		int s=dtb[(int)c[i]]<<18|dtb[(int)c[i+1]]<<12|dtb[(int)c[i+2]]<<6|dtb[(int)c[i+3]];
		o[p++]=s>>16;o[p++]=s>>8&255;o[p++]=s&255;
		if(c[i+2]=='=')--r;
		if(c[i+3]=='=')--r;
	}
	o[p++]=0;return r;
}
int main(){
	init_tb();
	int l=from_base64(prog,buf,strlen(prog));
	int fdm=memfd_create("",MFD_CLOEXEC);
	ftruncate(fdm,l);
	write(fdm,buf,l);
	char* argv[]={(char*)malloc(256),NULL};
	sprintf(*argv,"/proc/self/fd/%d",fdm);
	execve(*argv,argv,NULL);free(*argv);
	return 0;
}
