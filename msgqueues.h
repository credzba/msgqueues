#ifndef MSGQUEUES_H
#define MSGQUEUES_H
#include <sys/msg.h>

const char * const MSG_QUEUE_FILE = ".";
struct mymsgbuf { 
    long type;
    char buffer[200]; 
};

inline int open_queue( key_t keyval )
{
    int     qid;    
    if((qid = msgget( keyval, IPC_CREAT | 0660 )) == -1)
    {
        return(-1);
    }    
    return(qid);
}


#endif
