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
    int msgflg = 0666;
    int msgflg2 = IPC_CREAT |0666;
    key_t key, key2;
    struct msggbuf rbuf, sbuf;
 
    key = 1234;
    key2 = 1235;
 
    while(true){
        //receiving
        if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
          die("msgget");
        if (msgrcv(msqid, &rbuf, MAXSIZE, 1, 0) < 0)
            die("msgrcv");
        else{
            cout<<endl; 
            cout<<"Server : "<<rbuf.mtext<<endl;
        }

        //sending
        sbuf.mtype = 1;
        cout<<"Client : ";
        cin.getline(sbuf.mtext, MAXSIZE);
        int buflen = strlen(sbuf.mtext) + 1 ;
        if ((msqid = msgget(key2, msgflg2 )) < 0)   //Get the message queue ID for the given key
          die("msgget");
        if(msgsnd(msqid, &sbuf, buflen, IPC_CREAT)<0)
            die("msgsnd()");

    }
 
    exit(0);
}