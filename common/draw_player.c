#include "head.h"

extern WINDOW *Football;
extern struct User *rteam, *bteam;
extern void w_gotoxy_puts();
#define MAX 50

void draw_player() {
	werase(Football);
	box(Football, 0, 0);
	for (int i = 0; i < MAX; i++) {
		if (rteam[i].online) w_gotoxy_puts(Football, rteam[i].loc.x, rteam[i].loc.y, "");
		if (bteam[i].online) w_gotoxy_puts(Football, bteam[i].loc.x, bteam[i].loc.y, "");
	}
}

