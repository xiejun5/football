#include "head.h"
#include <math.h>
#include "game.h"
#include "thread_pool.h"
#define PI 3.1415926

extern WINDOW *Message;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

int can_kick(struct Point *loc, int strength) {
    int px = loc->x, py = loc->y;
    char tmp[512] = {0};
    sprintf(tmp, "loc(%d, %d) ball(%lf, %lf)", px, py, ball.x, ball.y);
	Show_Message(Message, NULL, tmp, 1);

    if (abs(px - (int)ball.x) <= 2 && abs(py - (int)ball.y) <= 2) {
		if (px == (int)ball.x && py == (int)ball.y) return 0;
		double tx = ball.x - px;
		double ty = ball.y - py;
		double dx = tx / sqrt(pow(tx, 2) + pow(ty, 2));
		double dy = ty / sqrt(pow(tx, 2) + pow(ty, 2));
		ball_status.a.x = -3.0 * dx;
		ball_status.a.y = -3.0 * dy;
		ball_status.v.x = 40 * strength * 0.15 * dx;
		ball_status.v.y = 40 * strength * 0.15 * dy;
		char tmp[512] = {0};
		sprintf(tmp, "a(%lf, %lf) v(%lf, %lf)", ball_status.a.x, ball_status.a.y, ball_status.v.x, ball_status.v.y);
		Show_Message(Message, NULL, tmp, 1);
		return 1;
	}
    return 0;     
}

int can_carry(struct Point *loc) {
    int px = loc->x, py = loc->y;
    char tmp[512] = {0};
    sprintf(tmp, "loc(%d, %d) ball(%lf, %lf)", px, py, ball.x, ball.y);
	Show_Message(Message, NULL, tmp, 1);

    if (abs(px - (int)ball.x) <= 1 && abs(py - (int)ball.y) <= 1) {
         
        return 1;
    }
    return 0;
}


