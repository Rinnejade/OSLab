/*
EXPT NO.04
VINOD KUMAR S
S7-R-062
29/07/2016
MESSAGE PASSING CLIENT
*/ 
#include "iostream"
#include "sys/types.h"
#include "unistd.h"
#include "sys/msg.h"
#include "sys/ipc.h"
#include "sys/wait.h"
#include "string.h"
#define max 20
using namespace std;

void die(string err){
    cout<<err<<" error";
    exit(0);
}

struct msggbuf{
    long mtype;
    char mtext[max];
};

int main(int argc, char const *argv[])
{
    int msqid;
    int key = 1234;
    int msgflg = IPC_CREAT | 0666;
    struct msggbuf buf;

    while(true){
        //receive
        if((msqid = msgget(key, msgflg)) <0)
            die("msgget()");
        if((msgrcv(msqid, &buf, max,1,0))<0)
            die("msgrcv()");
        cout<<"Server : "<< buf.mtext<<endl;

        //send
        buf.mtype = 1;
        cout<<"Client : ";
        cin.getline(buf.mtext, max);
        if((msqid = msgget(key, msgflg)) <0)
            die("msgget()");
        if(msgsnd(msqid, &buf, strlen(buf.mtext)+1,IPC_CREAT)<0)
            die("msgsnd()");


    }
    
    return 0;
}

/*

=====================OUTPUT====================
Server: hello
Clinet : hey there

Server: how are you?
Clinet : i am fine.you?

Server: fine.
Clinet : ok.

=====================OUTPUT====================
*/
