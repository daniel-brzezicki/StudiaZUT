//SO IS1 210B LAB08
//Daniel Brzezicki
//bd46477@zut.edu.pl

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char* argv[]){
if(argc<2 || argc>2){
	fprintf(stderr,"Poprawne uzycie lab8 argument");
	return 1;
}

int length = strlen(argv[1]);

for(int i =0;i<length;i++){
	if(!isdigit(argv[1][i])){
	return 2;
	}

}

int a = atoi(argv[1]);
if(a<1 || a>13){
	fprintf(stderr,"Argument za duzy lub za maly");
	return 3;
}

if(a==1 || a==2){
	return 1;
}


int child_1 = fork();
	
if(child_1==0){
	char b[30];
	sprintf(b,"%d", a-1);
	execl(argv[0],argv[0],b,NULL);
}
int exit_1;
wait(&exit_1);

int child_2 = fork();
	
if(child_2==0){
	char b[30];
	sprintf(b,"%d",a-2);
	execl(argv[0],argv[0],b,NULL);
}
int exit_2;
wait(&exit_2);

int pid = getpid();
printf("%d\t%d\t%d\t%d\n",pid,child_1,a-1,WEXITSTATUS(exit_1));
printf("%d\t%d\t%d\t%d\n",pid,child_2,a-2,WEXITSTATUS(exit_2));
printf("%d\t%d\n",pid,WEXITSTATUS(exit_1+exit_2));

return WEXITSTATUS(exit_1+exit_2);
}
