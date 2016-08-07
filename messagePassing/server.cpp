//IPC_msgq_send.c
 
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 128

using namespace std;
 
void die(string s)
{
  cout<<s<<endl;
  exit(1);
}
 
struct msggbuf
{
    long mtype;
    char mtext[MAXSIZE];
};
 
main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    int msgflg2 = 0666;
    key_t key, key2;
    struct msggbuf sbuf,rbuf;
    size_t buflen;
 
    key = 1234;
    key2 = 1235;
 

    while(true){
            //send
        if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
            die("msgget");
        sbuf.mtype = 1; 
        cout<<endl;
        cout<<"Server: ";
        cin.getline(sbuf.mtext, MAXSIZE);
        buflen = strlen(sbuf.mtext) + 1 ;
        if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
            die("msgsnd");
    
        //receive
        if ((msqid = msgget(key2, msgflg2 )) < 0)   //Get the message queue ID for the given key
            die("msgget");
        if (msgrcv(msqid, &rbuf, MAXSIZE, 1, 0) < 0)
            die("msgrcv");
        else{
            cout<<"Clinet : "<<rbuf.mtext<<endl;
        }
    }

 
    exit(0);
}