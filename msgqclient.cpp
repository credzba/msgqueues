#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <string.h>
#include <string>
#include <iostream>

#include "msgqueues.h"

namespace {
int send_message( int qid, mymsgbuf&  qbuf );
} // end anonymous namespace


int main(int argc, char *argv[])
{
    int    qid;
    key_t  msgkey;

    /* Generate our IPC key value */
    msgkey = ftok(".", 'm');

    /* Open/create the queue */
    if(( qid = open_queue( msgkey)) == -1) {
        perror("open_queue");
        exit(1);
    }
    mymsgbuf mb;
    mb.type=1;
    strcpy(mb.buffer, "some text");
    if (-1 == send_message(qid, mb ) ) {
        perror("send fail");
        exit(1);
    }

    return 0;
}

namespace {

int send_message( int qid, mymsgbuf& qbuf )
{
        int     result, length;
        /* The length is essentially the size of the structure minus sizeof(mtype) */
        length = sizeof(struct mymsgbuf) - sizeof(long);        

        if((result = msgsnd( qid, &qbuf, length, IPC_NOWAIT)) == -1) {
            return(-1);
        }
        
        return(result);
}

} // end anonymous namespace


