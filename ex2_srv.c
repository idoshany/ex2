#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <math.h>

void sighandler(int sig);
int stringtoint(char* PB);
int Calc(int P2, int P3, int P4);

int main(){
	pid_t cPid;
	int P2, P3, P4;
	char PB2[100] = "", PB3[100]="", PB4[100]= "";
	int to_srv, to_clientfd;
	char cBuf[100];
	char to_client[100]= "to_client_";
	int i=0;
	char sBuf[100];
	int j;
	int calc;
	int z;
	signal(SIGCONT, sighandler);
	while(1){
		remove("to_srv.txt");
		printf("%d\n",getpid());
		pause();
		if((cPid = fork()) == 0){
			to_srv = open("to_srv.txt" , O_RDONLY);
			read(to_srv, cBuf, 100);
			strcat(cBuf, "");
			while(cBuf[i] != ' '){
				to_client[i+10] = cBuf[i];
				i++;
			}
			printf("%s\n", to_client);
			i++;
			j = i;
			while(cBuf[i] != ' '){
				PB2[i-j] = cBuf[i];  
				i++;
			}
			P2 = stringtoint(PB2);
			i++;
			j = i;
			while(cBuf[i] != ' '){
                       		 PB3[i-j] = cBuf[i];
                       		 i++;
        	       	}
			P3 = stringtoint(PB3);
			i++;
			j=i;
			while(cBuf[i] !='\n'){
        	                PB4[i-j] = cBuf[i];
                	        i++;
               		 }
			P4 = stringtoint(PB4);
			printf("%d %d %d\n", P2, P3, P4);
			printf("%d\n" , Calc(P2, P3, P4));
			calc  = Calc(P2, P3, P4);
			sprintf(sBuf, "%d\n", calc);
			to_clientfd = open(to_client, O_WRONLY | O_CREAT, 0777);
			write(to_clientfd, sBuf, strlen(sBuf));
			remove("to_srv.txt");
			i = 0;
			return 0;
		}
	}
	return 0;
}

int stringtoint(char* PB){
	int P=0;
	int i;
	for(i=0; i < strlen(PB); i++)
                P += pow(10,strlen(PB)-i-1) *(PB[i]-'0');
	return P;
}

int Calc(int P2, int P3, int P4){
	int sw;
	switch(P3){
		case 1: 
			return P2 + P4;
			break;
		case 2:
			return P2 - P4;
			break;
		case 3:
			return P2 * P4;
			break;
		case 4:
			return P2 / P4;
			break;
		default:
			return -1;
	}
}


void sighandler(int sig){
	return;
}
