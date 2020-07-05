#include "head.h"
#include "game.h"
#include <math.h>
#define MAX 50

extern struct User *rteam, *bteam;
extern WINDOW *Football, *Help;
extern struct Bpoint ball;
extern struct BallStatus ball_status;
extern struct Map court;
extern struct Score arge;

void re_drew_player(int team, char *name, struct Point *loc) {
    char p = 'k';
    if (team)
        wattron(Football, COLOR_PAIR(6));
    else 
        wattron(Football, COLOR_PAIR(2));
    w_gotoxy_putc(Football, loc->x, loc->y, p);
    w_gotoxy_puts(Football, loc->x + 1, loc->y - 1, name);
}

void re_drew_team(struct User *team) {
    for (int i = 0; i < MAX; i++) {
        if (!team[i].online) continue;
        re_drew_player(team[i].team, team[i].name, &team[i].loc);
    }
}

void re_draw_ball() {
	double t = 0.1;
	if (ball_status.v.x != 0 || ball_status.v.y != 0) {
        ball.x += ball_status.v.x * 0.1 + ball_status.a.x * 0.5 * 0.01;
	    ball.y += ball_status.v.y * 0.1 + ball_status.a.y * 0.5 * 0.01;
	    ball_status.v.x += ball_status.a.x * 0.1;
		ball_status.v.y += ball_status.a.y * 0.1;
	}
	if (abs(ball_status.v.y) < 1 && abs(ball_status.v.x) < 1) {
		ball_status.v.x = ball_status.v.y = 0;
		ball_status.a.x = ball_status.a.y = 0;
	}
	if (ball_status.v.x || ball_status.v.y) {
		char tmp[512] = {0};
		sprintf(tmp, "a(%lf, %lf) v(%lf, %lf)", ball_status.a.x, ball_status.a.y, ball_status.v.x, ball_status.v.y);
		Show_Message( , NULL, tmp, 1);
	}
	if (ball.x <= 1 || ball.x >= 114 || ball.y <= 1 || ball.y >= 24) {
        ball.x += (-ball_status.v.x) * 0.1 + (ball_status.a.x * 0.5 * 0.1);
	    ball.y += (-ball_status.v.y) * 0.1 + (ball_status.a.y * 0.5 * 0.1);
		ball_status.v.x = ball_status.v.y = 0;
		ball_status.a.x = ball_status.a.y = 0;
	}
    w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, 'O');   
    if (ball.y >= 6 && ball.y <= 19 && (ball.x >= 114 || ball.x <= 2)) {
        ball.x = 57;
        ball.y = 12;
        if (ball_status.who) {
            ++arge.red;
        } else {
            ++arge.blue;
        }
        bzero(&ball_status, sizeof(ball_status));
        w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, 'O');   
        show_arge(Help);
    }

    
}

void re_drew() {
    wclear(Football_t);
    box(Football_t, 0, 0);
    box(Football, 0, 0);
    re_draw_ball();
    re_drew_team(rteam);
    re_drew_team(bteam);
    wrefresh(Football);
    wrefresh(Football_t);
}
