#include	"../include/unp.h"
#include	<time.h>
#include    "str_echo.c"
#include    "sigchldwait.c"
#include    "signal.c"
void sigChild(int signo)
{
    pid_t   pid;
    int     stat;

    pid=wait(&stat);
    printf("child %d terminated\n",pid);
    return;
}
int
main(int argc, char **argv)
{
	int					listenfd, connfd;
    pid_t               childpid;
    socklen_t           clilen;
	struct sockaddr_in	servaddr,cliaddr;
    void                sig_chld(int);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	= htons(SERV_PORT);	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

    signal(SIGCHLD,sig_chld);
	
    for ( ; ; ) {
        clilen=sizeof(cliaddr);
	printf("sssss");
        if( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen))<0){
            if(errno==EINTR)
                continue;
            else
                err_sys("accept error");
        }
        if((childpid=Fork())==0){
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
		Close(connfd);
	}
}
