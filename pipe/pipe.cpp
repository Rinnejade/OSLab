/*
EXPT NO.01
VINOD KUMAR S
S7-R-062
30/06/2016
PIPE
*/ 
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string>

using namespace std;

int isPrime(int n){
	if(n<2 || ( !(n&1) && n!=2 ))
		return 0;
	for(int i = 3;i<n/2;i++)
		if(!(n%2))
			return 0;
	return 1;
}
int main(){
	int p_id ;
	int c_id ;
	int pipefd[2];

	if(pipe(pipefd) == -1){
		cout<< "error in pipe"<<endl;
		return -1;
	}
	int data[20],receive[20], prime[10],n;
	cout<<"Input size : ";
	cin>>n;
	cout<<"enter numbers : ";
	for(int i=0;i<n;i++)
		cin>>data[i];
	c_id = fork();
	if(c_id==0){
		close(pipefd[1]);
		read(pipefd[0], receive, sizeof(data));
		for(int i=0;i<n;i++)
			if(isPrime(receive[i]))
				cout<<receive[i]<<endl;
		close(pipefd[0]);
	}
	else{
		close(pipefd[0]);
		write(pipefd[1], data, sizeof(data));
		cout<<"prime " << endl;
		close(pipefd[1]);
	}

	return 0;
}



/*

=====================OUTPUT====================
Input size : 5
enter numbers : 3 4 5 6 8
prime 
3
5
=====================OUTPUT====================
*/