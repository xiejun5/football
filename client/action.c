/*************************************************************************
	> File Name: action.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月05日 星期日 02时29分53秒
 ************************************************************************/
 #include "../common/head.h"
 #include "../common/datatype.h"
#include "action.h"

extern int sockfd;

void action_ball(char s) {
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = FT_CTL;
    switch(s) {
        case 'k': {
            msg.ctl.action = ACTION_KICK;
            msg.ctl.strength = 1;
            break;
        }
        case 'j': {
            msg.ctl.action = ACTION_STOP;
            break;
        }
        case 'l': {
            msg.ctl.action = ACTION_CARRY;
            break;
        }
    }
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    return ;
}
