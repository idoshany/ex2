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
#include <errno.h>

void sighandler(int sig);
int stringtoint(char* PB);
int Calc(int P2, int P3, int P4);

int main(){
	pid_t cPid = 0;
	int P1 = 0,P2 = 0, P3 = 0, P4 = 0;
	char PB2[100] = "", PB3[100]="", PB4[100]= "";
	int to_srv, to_clientfd;
	char cBuf[100]= "";
	char to_client[100]= "to_client_";
	char PB1[100] = "";
	int i=0;
	char sBuf[100] = "";
	int j = 0;
	int calc = 0;
	signal(SIGCONT, sighandler);
	while(1){
		remove("to_srv.txt");
		printf("%d\n",getpid());
		pause();
		//opening the Child process, which will handle the client
		if((cPid = fork()) == 0){
			to_srv = open("to_srv.txt" , O_RDONLY);//opening the to_srv.txt fd
			read(to_srv, cBuf, 100); //Reading the to_srv string into a buffer
			while(cBuf[i] != ' '){
				to_client[i+10] = cBuf[i];
				PB1[i] = cBuf[i];
				i++;
			}
			printf("hey\n");
			P1 = stringtoint(PB1); //passing the value of the client pid into P1(int)
			printf("%d\n", P1);
			printf("%s\n", to_client);
			i++; // The index to the cBuf which contains t_srv string value is passed over the space
			j = i;//index for the buffer for P2
			//Passing the P2 argument to P2
			while(cBuf[i] != ' '){
				PB2[i-j] = cBuf[i];
				i++;
			}
			P2 = stringtoint(PB2);
			i++;// Same as before
			j = i;// Same as before
			// Passing the P3 argument to P3
			while(cBuf[i] != ' '){
                       		 PB3[i-j] = cBuf[i];
                       		 i++;
        	       	}
			P3 = stringtoint(PB3);
			i++;//Same as before
			j=i;//Same as before
			//Passing the P4 argument to P4
			while(cBuf[i] !='\n'){
        	                PB4[i-j] = cBuf[i];
                	        i++;
               		}
			P4 = stringtoint(PB4);
			printf("%d %d %d\n", P2, P3, P4); // Checking that the passing went well
			printf("%d\n" , Calc(P2, P3, P4));//The function that calculates the value of the operation
			calc  = Calc(P2, P3, P4);
			sprintf(sBuf, "%d\n", calc);
			to_clientfd = open(to_client, O_WRONLY | O_CREAT, 0777);//Creating the to_client text file
			write(to_clientfd, sBuf, strlen(sBuf));// Writing the calulation value into to_client
			remove("to_srv.txt");
			i = 0;// reseting the cBuf index
			kill(P1,SIGCONT);//sending a signal to the client
			exit(0);
		}
		if(cPid < 0){
			printf("%s\n", strerror(errno));
			exit(1);
		}
		printf("%d\n", cPid);
	}
	return 0;
}

//function make a string integer int type
int stringtoint(char* PB){
	int P=0;
	int i;
	for(i=0; i < strlen(PB); i++)
                P += pow(10,strlen(PB)-i-1) *(PB[i]-'0');
	return P;
}


//Function to Calculate the value
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
	printf("Continuing the Process\n");
	return;
}
