#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include "msgqueues.h"

namespace {
int read_message( int qid, long type, struct mymsgbuf& qbuf );
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
    while (true) {
        int rc = read_message(qid, 1, mb);
        if (-1 == rc) {
            perror("read failure");
            exit(1);
        }
        std::cout << mb.buffer << std::endl;
    }

    return 0;
}

namespace {

int read_message( int qid, long type, struct mymsgbuf& qbuf ) {
    int     result, length;    
    /* The length is essentially the size of the structure minus sizeof(mtype) */
    length = sizeof(struct mymsgbuf) - sizeof(long);        
    
    if((result = msgrcv( qid, &qbuf, length, type,  0)) == -1)
    {
        return(-1);
    }    
    return(result);
}

} // end anonymous namespace
