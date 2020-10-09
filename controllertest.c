#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>
#include <stdlib.h>
void draw_text_green(display_context_t display_context, int x, int y, char *str, const char *format, int value)
{
	sprintf(str, format, value);
	graphics_set_color(graphics_make_color(0, 255, 0, 255), 0);
	graphics_draw_text(display_context, x, y, str);
	graphics_set_color(graphics_make_color(255, 255, 255, 255), 0);
}
void draw_text_red(display_context_t display_context, int x, int y, char *str, const char *format, int value)
{
	sprintf(str, format, value);
	graphics_set_color(graphics_make_color(255, 0, 0, 255), 0);
	graphics_draw_text(display_context, x, y, str);
	graphics_set_color(graphics_make_color(255, 255, 255, 255), 0);
}
int main(void)
{
	/* enable interrupts (on the CPU) */
	init_interrupts();

	/* Initialize Display */
	display_init(RESOLUTION_320x240, DEPTH_32_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);

	/* Initialize Filesystem for Sprites */
	dfs_init(DFS_DEFAULT_LOCATION);

	/* Initialize Controller */
	controller_init();

	/* Read in single sprite */
	int fp = dfs_open("/u.sprite");
	sprite_t *u = malloc(dfs_size(fp));
	dfs_read(u, 1, dfs_size(fp), fp);
	dfs_close(fp);

	fp = dfs_open("/d.sprite");
	sprite_t *d = malloc(dfs_size(fp));
	dfs_read(d, 1, dfs_size(fp), fp);
	dfs_close(fp);

	fp = dfs_open("/l.sprite");
	sprite_t *l = malloc(dfs_size(fp));
	dfs_read(l, 1, dfs_size(fp), fp);
	dfs_close(fp);

	fp = dfs_open("/r.sprite");
	sprite_t *r = malloc(dfs_size(fp));
	dfs_read(r, 1, dfs_size(fp), fp);
	dfs_close(fp);

	fp = dfs_open("/ur.sprite");
	sprite_t *ur = malloc(dfs_size(fp));
	dfs_read(ur, 1, dfs_size(fp), fp);
	dfs_close(fp);

	fp = dfs_open("/ul.sprite");
	sprite_t *ul = malloc(dfs_size(fp));
	dfs_read(ul, 1, dfs_size(fp), fp);
	dfs_close(fp);

	fp = dfs_open("/dr.sprite");
	sprite_t *dr = malloc(dfs_size(fp));
	dfs_read(dr, 1, dfs_size(fp), fp);
	dfs_close(fp);

	fp = dfs_open("/dl.sprite");
	sprite_t *dl = malloc(dfs_size(fp));
	dfs_read(dl, 1, dfs_size(fp), fp);
	dfs_close(fp);

	fp = dfs_open("/m.sprite");
	sprite_t *m = malloc(dfs_size(fp));
	dfs_read(m, 1, dfs_size(fp), fp);
	dfs_close(fp);

	/* Define Variables */
	int screen = 0;
	int test = 1;
	int results = 0;
	int goodRange = 77;
	int angleDiff = 4;

	/* YX Axis */
	int xax = 120;
	int yax = 120;
	int zax = 120;

	/* Benchmark */
	int bupx = 0;
	int bupy = 0;
	int buprightx = 0;
	int buprighty = 0;
	int brightx = 0;
	int brighty = 0;
	int bdownrightx = 0;
	int bdownrighty = 0;
	int bdownx = 0;
	int bdowny = 0;
	int bdownleftx = 0;
	int bdownlefty = 0;
	int bleftx = 0;
	int blefty = 0;
	int bupleftx = 0;
	int buplefty = 0;

	/* oem values */
	int OEMupx = 1;
	int OEMupy = 84;
	int OEMuprightx = 67;
	int OEMuprighty = 68;
	int OEMrightx = 83;
	int OEMrighty = -2;
	int OEMdownrightx = 67;
	int OEMdownrighty = -69;
	int OEMdownx = 3;
	int OEMdowny = -85;
	int OEMdownleftx = -69;
	int OEMdownlefty = -70;
	int OEMleftx = -85;
	int OEMlefty = 0;
	int OEMupleftx = -68;
	int OEMuplefty = 68;


	/* hori values */
	int HORIupx = 2;
	int HORIupy = 99;
	int HORIuprightx = 81;
	int HORIuprighty = 79;
	int HORIrightx = 101;
	int HORIrighty = 2;
	int HORIdownrightx = 85;
	int HORIdownrighty = -82;
	int HORIdownx = 2;
	int HORIdowny = -100;
	int HORIdownleftx = -78;
	int HORIdownlefty = -80;
	int HORIleftx = -101;
	int HORIlefty = -2;
	int HORIupleftx = -78;
	int HORIuplefty = 80;


	/* Main loop */
	while (1)
	{
		/* Create Place for Keys */
		struct controller_data keys;

		/* Create Place for Text */
		char tStr[256];

		/* Display Name */
		static display_context_t disp = 0;

		/* Grab a render buffer */
		while (!(disp = display_lock()));

		switch (screen)
		{
		case 0: /* Diagram */
		{
			xax = 120; /* midpoint x */
			yax = 120; /* midpoint y */
			zax = 120; /* size */

			controller_scan();
			keys = get_keys_pressed();

			/* fill screen */
			graphics_fill_screen(disp, 0);

			/* Draw Axis */
			graphics_draw_line(disp, xax - zax, yax, xax + zax, yax, graphics_make_color(255, 255, 255, 150));
			graphics_draw_line(disp, xax, yax - zax, xax, yax + zax, graphics_make_color(255, 255, 255, 150));
			graphics_draw_pixel(disp, xax, yax, graphics_make_color(0, 0, 0, 255));
			graphics_draw_pixel(disp, xax + 80, yax, graphics_make_color(0, 0, 0, 255));
			graphics_draw_pixel(disp, xax - 80, yax, graphics_make_color(0, 0, 0, 255));
			graphics_draw_pixel(disp, xax, yax + 80, graphics_make_color(0, 0, 0, 255));
			graphics_draw_pixel(disp, xax, yax - 80, graphics_make_color(0, 0, 0, 255));

			/* Draw Analog Stick Value */
			sprintf(tStr, "X: %d\n", keys.c[0].x);
			graphics_draw_text(disp, 250, 30, tStr);
			sprintf(tStr, "Y: %d\n", keys.c[0].y);
			graphics_draw_text(disp, 250, 40, tStr);

			graphics_draw_pixel(disp, xax + keys.c[0].x, yax - keys.c[0].y, graphics_make_color(255, 125, 0, 255));

			/* Go back to screen */
			keys = get_keys_down();
			if (keys.c[0].start)
			{
				screen = 1;

			}
			break;
		}

		case 1: /* Benchmark */
		{
			/* fill screen */
			graphics_fill_screen(disp, 0);

			/* User input */
			controller_scan();
			keys = get_keys_pressed();

			switch (test)
			{

			case 0:	/* Display results */
			{
				switch (results)
				{
				case 0:
				{
					//int aupx = abs(bupx);
					int aupy = abs(bupy);
					int auprightx = abs(buprightx);
					int auprighty = abs(buprighty);
					int arightx = abs(brightx);
					//int arighty = abs(brighty);
					int adownrightx = abs(bdownrightx);
					int adownrighty = abs(bdownrighty);
					//int adownx = abs(bdownx);
					int adowny = abs(bdowny);
					int adownleftx = abs(bdownleftx);
					int adownlefty = abs(bdownlefty);
					int aleftx = abs(bleftx);
					//int alefty = abs(blefty);
					int aupleftx = abs(bupleftx);
					int auplefty = abs(buplefty);

					graphics_draw_text(disp, 83, 10, "Your Stick");

					graphics_draw_line(disp, xax + bupx, yax - bupy, xax + buprightx, yax - buprighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + buprightx, yax - buprighty, xax + brightx, yax - brighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + brightx, yax - brighty, xax + bdownrightx, yax - bdownrighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownrightx, yax - bdownrighty, xax + bdownx, yax - bdowny, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownx, yax - bdowny, xax + bdownleftx, yax - bdownlefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownleftx, yax - bdownlefty, xax + bleftx, yax - blefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bleftx, yax - blefty, xax + bupleftx, yax - buplefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bupleftx, yax - buplefty, xax + bupx, yax - bupy, graphics_make_color(0, 50, 255, 255));
					
					if(aupy > goodRange)
					{
						draw_text_green(disp, 230, 20, tStr, "UP: %d  ", bupy);
					}
					else
					{
						draw_text_red(disp, 230, 20, tStr, "UP: %d  ", bupy);
					}
					
					if(adowny > goodRange)
					{
						draw_text_green(disp, 230, 30, tStr, "DOWN: %d  ", bdowny);
					}
					else
					{
						draw_text_red(disp, 230, 30, tStr, "DOWN: %d  ", bdowny);
					}
					
					if(aleftx > goodRange)
					{
						draw_text_green(disp, 230, 40, tStr, "LEFT: %d  ", aleftx);
					}
					else
					{
						draw_text_red(disp, 230, 40, tStr, "LEFT: %d  ", aleftx);
					}
					
					if(arightx > goodRange)
					{
						draw_text_green(disp, 230, 50, tStr, "RIGHT: %d  ", arightx);
					}
					else
					{
						draw_text_red(disp, 230, 50, tStr, "RIGHT: %d  ", arightx);
					}

					if(abs(auprightx - auprighty) < angleDiff)
					{
						draw_text_green(disp, 230, 70, tStr, "U-R:  %d", buprightx);
						draw_text_green(disp, 230, 80, tStr, "      %d", buprighty);
					}
					else
					{
						draw_text_red(disp, 230, 70, tStr, "U-R:  %d", buprightx);
						draw_text_red(disp, 230, 80, tStr, "      %d", buprighty);;
					}
					
					if(abs(adownrightx - adownrighty) < angleDiff)
					{
						draw_text_green(disp, 230, 95, tStr, "D-R:  %d", bdownrightx);
						draw_text_green(disp, 230, 105, tStr, "     %d", bdownrighty);
					}
					else
					{
						draw_text_red(disp, 230, 95, tStr, "D-R:  %d", bdownrightx);
						draw_text_red(disp, 230, 105, tStr, "     %d", bdownrighty);
					}
					
					if(abs(adownleftx - adownlefty) < angleDiff)
					{
						draw_text_green(disp, 230, 120, tStr, "D-L: %d", bdownleftx);
						draw_text_green(disp, 230, 130, tStr, "     %d", bdownlefty);
					}
					else
					{
						draw_text_red(disp, 230, 120, tStr, "D-L: %d", bdownleftx);
						draw_text_red(disp, 230, 130, tStr, "     %d", bdownlefty);
					}
					
					if(abs(aupleftx - auplefty) < angleDiff)
					{
						draw_text_green(disp, 230, 145, tStr, "U-L: %d", bupleftx);
						draw_text_green(disp, 230, 155, tStr, "      %d", buplefty);
					}
					else
					{
						draw_text_red(disp, 230, 145, tStr, "U-L: %d", bupleftx);
						draw_text_red(disp, 230, 155, tStr, "      %d", buplefty);
					}
									
					
					keys = get_keys_down();
					if (keys.c[0].L)
					{
						results = 4;
					}
					if (keys.c[0].R)
					{
						results = 1;
					}

					break;
				}
				case 1:
				{
					//int aupx = abs(bupx);
					int aOEMupy = abs(OEMupy);
					int aOEMuprightx = abs(OEMuprightx);
					int aOEMuprighty = abs(OEMuprighty);
					int aOEMrightx = abs(OEMrightx);
					//int aOEMrighty = abs(OEMrighty);
					int aOEMdownrightx = abs(OEMdownrightx);
					int aOEMdownrighty = abs(OEMdownrighty);
					//int aOEMdownx = abs(OEMdownx);
					int aOEMdowny = abs(OEMdowny);
					int aOEMdownleftx = abs(OEMdownleftx);
					int aOEMdownlefty = abs(OEMdownlefty);
					int aOEMleftx = abs(OEMleftx);
					//int aOEMlefty = abs(OEMlefty);
					int aOEMupleftx = abs(OEMupleftx);
					int aOEMuplefty = abs(OEMuplefty);
					
					graphics_draw_text(disp, 47, 10, "Brand New OEM Stick");

					graphics_draw_line(disp, xax + OEMupx, yax - OEMupy, xax + OEMuprightx, yax - OEMuprighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMuprightx, yax - OEMuprighty, xax + OEMrightx, yax - OEMrighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMrightx, yax - OEMrighty, xax + OEMdownrightx, yax - OEMdownrighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMdownrightx, yax - OEMdownrighty, xax + OEMdownx, yax - OEMdowny, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMdownx, yax - OEMdowny, xax + OEMdownleftx, yax - OEMdownlefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMdownleftx, yax - OEMdownlefty, xax + OEMleftx, yax - OEMlefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMleftx, yax - OEMlefty, xax + OEMupleftx, yax - OEMuplefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMupleftx, yax - OEMuplefty, xax + OEMupx, yax - OEMupy, graphics_make_color(0, 255, 0, 255));

					if(aOEMupy > goodRange)
					{
						draw_text_green(disp, 230, 20, tStr, "UP: %d  ", OEMupy);
					}
					else
					{
						draw_text_red(disp, 230, 20, tStr, "UP: %d  ", OEMupy);
					}
					
					if(aOEMdowny > goodRange)
					{
						draw_text_green(disp, 230, 30, tStr, "DOWN: %d  ", OEMdowny);
					}
					else
					{
						draw_text_red(disp, 230, 30, tStr, "DOWN: %d  ", OEMdowny);
					}
					
					if(aOEMleftx > goodRange)
					{
						draw_text_green(disp, 230, 40, tStr, "LEFT: %d  ", OEMleftx);
					}
					else
					{
						draw_text_red(disp, 230, 40, tStr, "LEFT: %d  ", OEMleftx);
					}
					
					if(aOEMrightx > goodRange)
					{
						draw_text_green(disp, 230, 50, tStr, "RIGHT: %d  ", OEMrightx);
					}
					else
					{
						draw_text_red(disp, 230, 50, tStr, "RIGHT: %d  ", OEMrightx);
					}

					if(abs(aOEMuprightx - aOEMuprighty) < angleDiff)
					{
						draw_text_green(disp, 230, 70, tStr, "U-R:  %d", OEMuprightx);
						draw_text_green(disp, 230, 80, tStr, "      %d", OEMuprighty);
					}
					else
					{
						draw_text_red(disp, 230, 70, tStr, "U-R:  %d", OEMuprightx);
						draw_text_red(disp, 230, 80, tStr, "      %d", OEMuprighty);;
					}
					
					if(abs(aOEMdownrightx - aOEMdownrighty) < angleDiff)
					{
						draw_text_green(disp, 230, 95, tStr, "D-R:  %d", OEMdownrightx);
						draw_text_green(disp, 230, 105, tStr, "     %d", OEMdownrighty);
					}
					else
					{
						draw_text_red(disp, 230, 95, tStr, "D-R:  %d", OEMdownrightx);
						draw_text_red(disp, 230, 105, tStr, "     %d", OEMdownrighty);
					}
					
					if(abs(aOEMdownleftx - aOEMdownlefty) < angleDiff)
					{
						draw_text_green(disp, 230, 120, tStr, "D-L: %d", OEMdownleftx);
						draw_text_green(disp, 230, 130, tStr, "     %d", OEMdownlefty);
					}
					else
					{
						draw_text_red(disp, 230, 120, tStr, "D-L: %d", OEMdownleftx);
						draw_text_red(disp, 230, 130, tStr, "     %d", OEMdownlefty);
					}
					
					if(abs(aOEMupleftx - aOEMuplefty) < angleDiff)
					{
						draw_text_green(disp, 230, 145, tStr, "U-L: %d", OEMupleftx);
						draw_text_green(disp, 230, 155, tStr, "      %d", OEMuplefty);
					}
					else
					{
						draw_text_red(disp, 230, 145, tStr, "U-L: %d", OEMupleftx);
						draw_text_red(disp, 230, 155, tStr, "      %d", OEMuplefty);
					}



					keys = get_keys_down();
					if (keys.c[0].L)
					{
						results = 0;
					}
					if (keys.c[0].R)
					{
						results = 2;
					}

					break;
				}
				case 2:
				{
					
					//int aupx = abs(bupx);
					int aHORIupy = abs(HORIupy);
					int aHORIuprightx = abs(HORIuprightx);
					int aHORIuprighty = abs(HORIuprighty);
					int aHORIrightx = abs(HORIrightx);
					//int aHORIrighty = abs(HORIrighty);
					int aHORIdownrightx = abs(HORIdownrightx);
					int aHORIdownrighty = abs(HORIdownrighty);
					//int aHORIdownx = abs(HORIdownx);
					int aHORIdowny = abs(HORIdowny);
					int aHORIdownleftx = abs(HORIdownleftx);
					int aHORIdownlefty = abs(HORIdownlefty);
					int aHORIleftx = abs(HORIleftx);
					//int aHORIlefty = abs(HORIlefty);
					int aHORIupleftx = abs(HORIupleftx);
					int aHORIuplefty = abs(HORIuplefty);
					
					graphics_draw_text(disp, 55, 10, "Perfect Hori Stick");

					graphics_draw_line(disp, xax + HORIupx, yax - HORIupy, xax + HORIuprightx, yax - HORIuprighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIuprightx, yax - HORIuprighty, xax + HORIrightx, yax - HORIrighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIrightx, yax - HORIrighty, xax + HORIdownrightx, yax - HORIdownrighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIdownrightx, yax - HORIdownrighty, xax + HORIdownx, yax - HORIdowny, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIdownx, yax - HORIdowny, xax + HORIdownleftx, yax - HORIdownlefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIdownleftx, yax - HORIdownlefty, xax + HORIleftx, yax - HORIlefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIleftx, yax - HORIlefty, xax + HORIupleftx, yax - HORIuplefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIupleftx, yax - HORIuplefty, xax + HORIupx, yax - HORIupy, graphics_make_color(0, 255, 0, 255));

					if(aHORIupy > goodRange)
					{
						draw_text_green(disp, 230, 20, tStr, "UP: %d  ", HORIupy);
					}
					else
					{
						draw_text_red(disp, 230, 20, tStr, "UP: %d  ", HORIupy);
					}
					
					if(aHORIdowny > goodRange)
					{
						draw_text_green(disp, 230, 30, tStr, "DOWN: %d  ", HORIdowny);
					}
					else
					{
						draw_text_red(disp, 230, 30, tStr, "DOWN: %d  ", HORIdowny);
					}
					
					if(aHORIleftx > goodRange)
					{
						draw_text_green(disp, 230, 40, tStr, "LEFT: %d  ", HORIleftx);
					}
					else
					{
						draw_text_red(disp, 230, 40, tStr, "LEFT: %d  ", HORIleftx);
					}
					
					if(aHORIrightx > goodRange)
					{
						draw_text_green(disp, 230, 50, tStr, "RIGHT: %d  ", HORIrightx);
					}
					else
					{
						draw_text_red(disp, 230, 50, tStr, "RIGHT: %d  ", HORIrightx);
					}

					if(abs(aHORIuprightx - aHORIuprighty) < angleDiff)
					{
						draw_text_green(disp, 230, 70, tStr, "U-R:  %d", HORIuprightx);
						draw_text_green(disp, 230, 80, tStr, "      %d", HORIuprighty);
					}
					else
					{
						draw_text_red(disp, 230, 70, tStr, "U-R:  %d", HORIuprightx);
						draw_text_red(disp, 230, 80, tStr, "      %d", HORIuprighty);;
					}
					
					if(abs(aHORIdownrightx - aHORIdownrighty) < angleDiff)
					{
						draw_text_green(disp, 230, 95, tStr, "D-R:  %d", HORIdownrightx);
						draw_text_green(disp, 230, 105, tStr, "     %d", HORIdownrighty);
					}
					else
					{
						draw_text_red(disp, 230, 95, tStr, "D-R:  %d", HORIdownrightx);
						draw_text_red(disp, 230, 105, tStr, "     %d", HORIdownrighty);
					}
					
					if(abs(aHORIdownleftx - aHORIdownlefty) < angleDiff)
					{
						draw_text_green(disp, 230, 120, tStr, "D-L: %d", HORIdownleftx);
						draw_text_green(disp, 230, 130, tStr, "     %d", HORIdownlefty);
					}
					else
					{
						draw_text_red(disp, 230, 120, tStr, "D-L: %d", HORIdownleftx);
						draw_text_red(disp, 230, 130, tStr, "     %d", HORIdownlefty);
					}
					
					if(abs(aHORIupleftx - aHORIuplefty) < angleDiff)
					{
						draw_text_green(disp, 230, 145, tStr, "U-L: %d", HORIupleftx);
						draw_text_green(disp, 230, 155, tStr, "      %d", HORIuplefty);
					}
					else
					{
						draw_text_red(disp, 230, 145, tStr, "U-L: %d", HORIupleftx);
						draw_text_red(disp, 230, 155, tStr, "      %d", HORIuplefty);
					}

					keys = get_keys_down();
					if (keys.c[0].L)
					{
						results = 1;
					}
					if (keys.c[0].R)
					{
						results = 3;
					}
					break;
				}
				case 3:
				{
					
					//int aupx = abs(bupx);
					int aupy = abs(bupy);
					int auprightx = abs(buprightx);
					int auprighty = abs(buprighty);
					int arightx = abs(brightx);
					//int arighty = abs(brighty);
					int adownrightx = abs(bdownrightx);
					int adownrighty = abs(bdownrighty);
					//int adownx = abs(bdownx);
					int adowny = abs(bdowny);
					int adownleftx = abs(bdownleftx);
					int adownlefty = abs(bdownlefty);
					int aleftx = abs(bleftx);
					//int alefty = abs(blefty);
					int aupleftx = abs(bupleftx);
					int auplefty = abs(buplefty);
					
					graphics_draw_text(disp, 50, 10, "New OEM Comparison");

					graphics_draw_line(disp, xax + OEMupx, yax - OEMupy, xax + OEMuprightx, yax - OEMuprighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMuprightx, yax - OEMuprighty, xax + OEMrightx, yax - OEMrighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMrightx, yax - OEMrighty, xax + OEMdownrightx, yax - OEMdownrighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMdownrightx, yax - OEMdownrighty, xax + OEMdownx, yax - OEMdowny, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMdownx, yax - OEMdowny, xax + OEMdownleftx, yax - OEMdownlefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMdownleftx, yax - OEMdownlefty, xax + OEMleftx, yax - OEMlefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMleftx, yax - OEMlefty, xax + OEMupleftx, yax - OEMuplefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + OEMupleftx, yax - OEMuplefty, xax + OEMupx, yax - OEMupy, graphics_make_color(0, 255, 0, 255));

					graphics_draw_line(disp, xax + bupx, yax - bupy, xax + buprightx, yax - buprighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + buprightx, yax - buprighty, xax + brightx, yax - brighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + brightx, yax - brighty, xax + bdownrightx, yax - bdownrighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownrightx, yax - bdownrighty, xax + bdownx, yax - bdowny, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownx, yax - bdowny, xax + bdownleftx, yax - bdownlefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownleftx, yax - bdownlefty, xax + bleftx, yax - blefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bleftx, yax - blefty, xax + bupleftx, yax - buplefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bupleftx, yax - buplefty, xax + bupx, yax - bupy, graphics_make_color(0, 50, 255, 255));

					if(aupy > goodRange)
					{
						draw_text_green(disp, 230, 20, tStr, "UP: %d  ", bupy);
					}
					else
					{
						draw_text_red(disp, 230, 20, tStr, "UP: %d  ", bupy);
					}
					
					if(adowny > goodRange)
					{
						draw_text_green(disp, 230, 30, tStr, "DOWN: %d  ", bdowny);
					}
					else
					{
						draw_text_red(disp, 230, 30, tStr, "DOWN: %d  ", bdowny);
					}
					
					if(aleftx > goodRange)
					{
						draw_text_green(disp, 230, 40, tStr, "LEFT: %d  ", aleftx);
					}
					else
					{
						draw_text_red(disp, 230, 40, tStr, "LEFT: %d  ", aleftx);
					}
					
					if(arightx > goodRange)
					{
						draw_text_green(disp, 230, 50, tStr, "RIGHT: %d  ", arightx);
					}
					else
					{
						draw_text_red(disp, 230, 50, tStr, "RIGHT: %d  ", arightx);
					}

					if(abs(auprightx - auprighty) < angleDiff)
					{
						draw_text_green(disp, 230, 70, tStr, "U-R:  %d", buprightx);
						draw_text_green(disp, 230, 80, tStr, "      %d", buprighty);
					}
					else
					{
						draw_text_red(disp, 230, 70, tStr, "U-R:  %d", buprightx);
						draw_text_red(disp, 230, 80, tStr, "      %d", buprighty);;
					}
					
					if(abs(adownrightx - adownrighty) < angleDiff)
					{
						draw_text_green(disp, 230, 95, tStr, "D-R:  %d", bdownrightx);
						draw_text_green(disp, 230, 105, tStr, "     %d", bdownrighty);
					}
					else
					{
						draw_text_red(disp, 230, 95, tStr, "D-R:  %d", bdownrightx);
						draw_text_red(disp, 230, 105, tStr, "     %d", bdownrighty);
					}
					
					if(abs(adownleftx - adownlefty) < angleDiff)
					{
						draw_text_green(disp, 230, 120, tStr, "D-L: %d", bdownleftx);
						draw_text_green(disp, 230, 130, tStr, "     %d", bdownlefty);
					}
					else
					{
						draw_text_red(disp, 230, 120, tStr, "D-L: %d", bdownleftx);
						draw_text_red(disp, 230, 130, tStr, "     %d", bdownlefty);
					}
					
					if(abs(aupleftx - auplefty) < angleDiff)
					{
						draw_text_green(disp, 230, 145, tStr, "U-L: %d", bupleftx);
						draw_text_green(disp, 230, 155, tStr, "      %d", buplefty);
					}
					else
					{
						draw_text_red(disp, 230, 145, tStr, "U-L: %d", bupleftx);
						draw_text_red(disp, 230, 155, tStr, "      %d", buplefty);
					}

					keys = get_keys_down();
					if (keys.c[0].L)
					{
						results = 2;
					}
					if (keys.c[0].R)
					{
						results = 4;
					}
					break;
				}
				case 4:
				{
					
					//int aupx = abs(bupx);
					int aupy = abs(bupy);
					int auprightx = abs(buprightx);
					int auprighty = abs(buprighty);
					int arightx = abs(brightx);
					//int arighty = abs(brighty);
					int adownrightx = abs(bdownrightx);
					int adownrighty = abs(bdownrighty);
					//int adownx = abs(bdownx);
					int adowny = abs(bdowny);
					int adownleftx = abs(bdownleftx);
					int adownlefty = abs(bdownlefty);
					int aleftx = abs(bleftx);
					//int alefty = abs(blefty);
					int aupleftx = abs(bupleftx);
					int auplefty = abs(buplefty);
					
					graphics_draw_text(disp, 42, 10, "Perfect Hori Comparison");

					graphics_draw_line(disp, xax + HORIupx, yax - HORIupy, xax + HORIuprightx, yax - HORIuprighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIuprightx, yax - HORIuprighty, xax + HORIrightx, yax - HORIrighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIrightx, yax - HORIrighty, xax + HORIdownrightx, yax - HORIdownrighty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIdownrightx, yax - HORIdownrighty, xax + HORIdownx, yax - HORIdowny, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIdownx, yax - HORIdowny, xax + HORIdownleftx, yax - HORIdownlefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIdownleftx, yax - HORIdownlefty, xax + HORIleftx, yax - HORIlefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIleftx, yax - HORIlefty, xax + HORIupleftx, yax - HORIuplefty, graphics_make_color(0, 255, 0, 255));
					graphics_draw_line(disp, xax + HORIupleftx, yax - HORIuplefty, xax + HORIupx, yax - HORIupy, graphics_make_color(0, 255, 0, 255));

					graphics_draw_line(disp, xax + bupx, yax - bupy, xax + buprightx, yax - buprighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + buprightx, yax - buprighty, xax + brightx, yax - brighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + brightx, yax - brighty, xax + bdownrightx, yax - bdownrighty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownrightx, yax - bdownrighty, xax + bdownx, yax - bdowny, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownx, yax - bdowny, xax + bdownleftx, yax - bdownlefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bdownleftx, yax - bdownlefty, xax + bleftx, yax - blefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bleftx, yax - blefty, xax + bupleftx, yax - buplefty, graphics_make_color(0, 50, 255, 255));
					graphics_draw_line(disp, xax + bupleftx, yax - buplefty, xax + bupx, yax - bupy, graphics_make_color(0, 50, 255, 255));

					if(aupy > goodRange)
					{
						draw_text_green(disp, 230, 20, tStr, "UP: %d  ", bupy);
					}
					else
					{
						draw_text_red(disp, 230, 20, tStr, "UP: %d  ", bupy);
					}
					
					if(adowny > goodRange)
					{
						draw_text_green(disp, 230, 30, tStr, "DOWN: %d  ", bdowny);
					}
					else
					{
						draw_text_red(disp, 230, 30, tStr, "DOWN: %d  ", bdowny);
					}
					
					if(aleftx > goodRange)
					{
						draw_text_green(disp, 230, 40, tStr, "LEFT: %d  ", aleftx);
					}
					else
					{
						draw_text_red(disp, 230, 40, tStr, "LEFT: %d  ", aleftx);
					}
					
					if(arightx > goodRange)
					{
						draw_text_green(disp, 230, 50, tStr, "RIGHT: %d  ", arightx);
					}
					else
					{
						draw_text_red(disp, 230, 50, tStr, "RIGHT: %d  ", arightx);
					}

					if(abs(auprightx - auprighty) < angleDiff)
					{
						draw_text_green(disp, 230, 70, tStr, "U-R:  %d", buprightx);
						draw_text_green(disp, 230, 80, tStr, "      %d", buprighty);
					}
					else
					{
						draw_text_red(disp, 230, 70, tStr, "U-R:  %d", buprightx);
						draw_text_red(disp, 230, 80, tStr, "      %d", buprighty);;
					}
					
					if(abs(adownrightx - adownrighty) < angleDiff)
					{
						draw_text_green(disp, 230, 95, tStr, "D-R:  %d", bdownrightx);
						draw_text_green(disp, 230, 105, tStr, "     %d", bdownrighty);
					}
					else
					{
						draw_text_red(disp, 230, 95, tStr, "D-R:  %d", bdownrightx);
						draw_text_red(disp, 230, 105, tStr, "     %d", bdownrighty);
					}
					
					if(abs(adownleftx - adownlefty) < angleDiff)
					{
						draw_text_green(disp, 230, 120, tStr, "D-L: %d", bdownleftx);
						draw_text_green(disp, 230, 130, tStr, "     %d", bdownlefty);
					}
					else
					{
						draw_text_red(disp, 230, 120, tStr, "D-L: %d", bdownleftx);
						draw_text_red(disp, 230, 130, tStr, "     %d", bdownlefty);
					}
					
					if(abs(aupleftx - auplefty) < angleDiff)
					{
						draw_text_green(disp, 230, 145, tStr, "U-L: %d", bupleftx);
						draw_text_green(disp, 230, 155, tStr, "      %d", buplefty);
					}
					else
					{
						draw_text_red(disp, 230, 145, tStr, "U-L: %d", bupleftx);
						draw_text_red(disp, 230, 155, tStr, "      %d", buplefty);
					}

					keys = get_keys_down();
					if (keys.c[0].L)
					{
						results = 3;
					}
					if (keys.c[0].R)
					{
						results = 0;
					}
					break;
				}

				}

				xax = 120; /* midpoint x */
				yax = 120; /* midpoint y */
				zax = 120; /* size */


				graphics_draw_pixel(disp, xax, yax, graphics_make_color(255, 255, 255, 255));
				graphics_draw_pixel(disp, xax + 80, yax, graphics_make_color(255, 255, 255, 255));
				graphics_draw_pixel(disp, xax - 80, yax, graphics_make_color(255, 255, 255, 255));
				graphics_draw_pixel(disp, xax, yax + 80, graphics_make_color(255, 255, 255, 255));
				graphics_draw_pixel(disp, xax, yax - 80, graphics_make_color(255, 255, 255, 255));

				break;
			}

			case 1:	/* +y Up */
			{
				graphics_draw_sprite_trans(disp, 110, 60, u);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					bupx = keys.c[0].x;
					bupy = keys.c[0].y;
					test = 2;
				}
				break;
			}

			case 2:	/* +y+x Up-Right */
			{
				graphics_draw_sprite_trans(disp, 110, 60, ur);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					buprightx = keys.c[0].x;
					buprighty = keys.c[0].y;
					test = 3;
				}
				break;
			}

			case 3:	/* +x Right */
			{
				graphics_draw_sprite_trans(disp, 110, 60, r);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					brightx = keys.c[0].x;
					brighty = keys.c[0].y;
					test = 4;
				}
				break;
			}

			case 4:	/* -y+x Down-Right*/
			{
				graphics_draw_sprite_trans(disp, 110, 60, dr);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					bdownrightx = keys.c[0].x;
					bdownrighty = keys.c[0].y;
					test = 5;
				}
				break;
			}

			case 5:	/* -y Down*/
			{
				graphics_draw_sprite_trans(disp, 110, 60, d);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					bdownx = keys.c[0].x;
					bdowny = keys.c[0].y;
					test = 6;
				}
				break;
			}

			case 6:	/* -y-x Down-Left */
			{
				graphics_draw_sprite_trans(disp, 110, 60, dl);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					bdownleftx = keys.c[0].x;
					bdownlefty = keys.c[0].y;
					test = 7;
				}
				break;
			}

			case 7:	/* -x Left */
			{
				graphics_draw_sprite_trans(disp, 110, 60, l);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					bleftx = keys.c[0].x;
					blefty = keys.c[0].y;
					test = 8;
				}
				break;
			}

			case 8:	/* +y+x Up-Left */
			{
				graphics_draw_sprite_trans(disp, 110, 60, ul);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					bupleftx = keys.c[0].x;
					buplefty = keys.c[0].y;
					test = 9;
				}
				break;
			}

			case 9:	/* center */
			{
				graphics_draw_sprite_trans(disp, 110, 60, m);

				keys = get_keys_down();
				if (keys.c[0].A)
				{
					keys = get_keys_pressed();
					test = 0;
				}
				break;
			}
			}

			/* Go back to screen */
			keys = get_keys_down();
			if (keys.c[0].start)
			{
				screen = 0;
				test = 1;
				results = 0;
			}
			break;
		}


		} /* main menu switch */

		/* Show display */
		display_show(disp);

	} /* while 1*/

} /* main */
