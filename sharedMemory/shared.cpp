/*
EXPT NO.03
VINOD KUMAR S
S7-R-062
18/07/2016
SHARED MEMORY
*/ 
#include <iostream>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
#define MAX 10;

class matrix{
public:
	int row, col;
	int A[10][10];
	matrix(int r, int c){
		row = r; col =c;
	}
	void read(){
		cout<<"enter elements"<<endl;
		for(int i =0;i<row;i++)
			for(int j=0;j<col;j++)
				cin>>A[i][j];
	}
	void display(){
		cout<<"matrix "<<endl;
		for(int i =0;i<row;i++){
			for(int j=0;j<col;j++)
				cout<<A[i][j]<<'\t';
		cout<<endl;
		}
	}
	matrix multiply(matrix m2){
		if(col != m2.row){
			cout<<"The matrix is not compatable"<<endl;
		}
		matrix m3(row, m2.col);
		for(int i = 0;i<row;i++)
			for(int j=0;j<m2.col;j++){
				m3.A[i][j]=0;
				for(int k = 0;k<col;k++)
					m3.A[i][j] = m3.A[i][j] + A[i][k]*m2.A[k][j];
			}
		return m3;
	}
};

int main(){
	int shmid;
	pid_t pid,pid2;
	int n;

	if((shmid = shmget(IPC_PRIVATE,10 * sizeof(matrix),0666))<0){
		cout<<"error in creating shmid"<<endl;
		return 0;
	}

	int p = fork();

	if(p){
		wait(NULL);
		int q = fork();
		if(q){
			wait(NULL);
			matrix *shmptr = (matrix*) shmat(shmid, NULL, 0);

			matrix m1 = *shmptr;
			m1.display();

			matrix m2 = *(shmptr+1);
			m2.display();

			matrix m3 = *(shmptr+2);
			m3.display();
		}else{
			matrix *shmptr = (matrix*) shmat(shmid, NULL, 0);
			matrix m1 = *shmptr;

			matrix m2 = *(shmptr+1);

			matrix m3 = m1.multiply(m2);
			 *(shmptr+2) = m3;

		}
	}else{
		matrix *s = (matrix*) shmat(shmid, NULL, 0);

		int r, c;
		cout<<"enter row and column"<<endl;
		cin>>r>>c;
		matrix m1(r,c);
		m1.read();
		*s = m1;

		cout<<"enter row and col "<<endl;
		cin>>r>>c;
		matrix m2(r,c);
		m2.read();
		*(s+1) = m2;
	}
	cout<<endl;
	return 0;
}

/*

=====================OUTPUT====================

enter row and column
2 3
enter elements
1 2 3
4 5 6
enter row and col 
3 2
enter elements
1 2
8 2 
9 3


matrix 
1	2	3	
4	5	6	
matrix 
1	2	
8	2	
9	3	
matrix 
44	15	
98	36	

=====================OUTPUT====================
/*