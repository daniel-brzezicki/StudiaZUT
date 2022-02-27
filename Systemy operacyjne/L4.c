//SO IS1 210B LAB12
//Daniel Brzezicki
//bd46477@zut.edu.pl
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void print_board(char * board){
	for(int i=1;i<10;i++){
		if(i%3==0)
			printf(" %c ",board[i]);
		else
			printf(" %c |",board[i]);
		if(i%3==0 && i!=9)
			printf("\n---+---+---\n");
		else if(i==9)
			printf("\n");
	}
}

void pick(char* board, char player){
	printf("Wykonaj ruch: ");
	int ruch;
	scanf("%d",&ruch);
	if(ruch<0||ruch>9){
	pick(board,player);
	}
	else{
		if(board[ruch]!='o'&&board[ruch]!='x'){
			board[ruch]=player;
			if(board[12]=='o')
				board[12]='x';
			else
				board[12]='o';
		}
		else{
			printf("To pole jest zajete!\n");
			pick(board,player);
		}
	}
	printf("\n");
	print_board(board);
}

void check(char* board, char player, int shmid){
	char winner;
	int win=0;
	if(board[1]==board[2] && board[2]==board[3]){winner = board[1];win=1;}
	else if (board[4]==board[5] && board[5]==board[6]){winner = board[4];win=1;}
	else if (board[4]==board[5] && board[5]==board[6]){winner = board[4];win=1;}
	else if (board[1]==board[4] && board[4]==board[7]){winner = board[1];win=1;}
	else if (board[2]==board[5] && board[5]==board[8]){winner = board[2];win=1;}
	else if (board[3]==board[6] && board[6]==board[9]){winner = board[3];win=1;}
	else if (board[3]==board[5] && board[5]==board[7]){winner = board[3];win=1;}
	else if (board[1]==board[5]&& board[5]==board[9]){winner = board[1];win=1;}
	
	if(win==1){
		if(player==winner)
			printf("Brawo wygrales! Player %c wygrywa\n", player);
		else
			printf("Niestety nie udalo sie! Player %c wygrywa\n", winner);
		shmctl(shmid,IPC_RMID,NULL);
		exit(1);
	}
	
	int draw = 1;
	for(int i =1;i<10;i++){
		if(board[i]==i+'0'){
			draw=0;
			break;
		}
	}
	
	if(draw==1){
		printf("Remis\n");
		shmctl(shmid,IPC_RMID,NULL);
		exit(1);
	}
	
		
}

int main(int argc,char* argv[]){
	if(argc<2 || argc>2){
		fprintf(stderr,"Nie podano klucza\n");
		return 1;
	}
	
	int max = 12;
	int shmid, i;
	char *buf;
	char player;
	int key = 0;
	
	int length = strlen(argv[1]);

	for(int i =0;i<length;i++){
		key+=argv[1][i];
	}


	
	shmid = shmget(key, max*sizeof(char),IPC_CREAT|0600);
	if(shmid==-1){
		perror("Utworzenie segmentu pamieci wspoldzielonej");
	}
	
	buf = (char*)shmat(shmid,NULL,0);
	if(buf==NULL){
		perror("Przylaczenie segmentu pamieci wspoldzielonej");
		if(buf[10]=='\0'){
			buf[10]='1';
			player='x';
		}
		else{
			buf[11]='1';
			player='o';
		}
	}
	else{
		if(buf[10]=='\0'){
			buf[10]='1';
			player='x';
		}
		else{
			buf[11]='1';
			player='o';
		}
	}
	buf[12]='x';
	for(int i=1;i<10;i++){
		buf[i%max]=i +'0';
	}
	
	int showWarning=0;
	int show=0;
	while(1){
		if(buf[10]=='1' && buf[11]=='1'){
		if(player==buf[12]){
			print_board(buf);
			check(buf,player,shmid);
			show=0;
			pick(buf,player);
			check(buf,player,shmid);
		}
		else{
			if(show==0){
				show=1;
				sleep(1);
				check(buf,player,shmid);
				printf("\nPoczekaj na ruch przeciwnika\n");
			}
		}
		}
		else{
			if(showWarning==0){
				showWarning=1;
				sleep(1);
				printf("\nOczekiwanie na dolaczenie przeciwnika\n");
			}
		}	
	}
	
	return 0;
	
}
