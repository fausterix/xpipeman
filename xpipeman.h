/*
 * xpipeman.h  - Xpipeman
 *
 * Send Constructive comments, bug reports, etc. to either
 *
 *          JANET: pavern@uk.ac.man.cs
 *
 *  or      INER : pavern%cs.man.ac.uk@nsfnet-relay.ac.uk
 *
 * All other comments > /dev/null !!
 * 
 * 
 * Copyright 1991 Nigel Paver
 * 
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the author's name not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The author makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 * 
 * THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING 
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL THE 
 * AUTHOR BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY 
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN 
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF 
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 */

/* 
 * from main.c
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern Display 	*display;
extern Window 	playfield;
extern Widget 	playfield_widget;
extern GC 	gc,
		cleargc;

typedef struct {
    Pixel fg;
    Pixel bg;
    XtTranslations translations;
    String score_file;
} AppData;

extern AppData app_data;

extern void 	update_score(int score);
extern void 	update_level(int level);
extern void 	update_bonus(int score);
extern void 	update_remain(int score);
extern void     all_popdown(void);

/*
 * from graphics.c
 */

/* defines the order of the blocks in the pixmap array */

#define NUMBLOCKS 8     /* number of empty blocks */
#define TOTALBLOCKS (ONEWAY+6)   /* including one way blocks */
#define NoBlksDefined BAR+1
#define EMPTY 	0
#define ONEWAY NUMBLOCKS
#define HFULL TOTALBLOCKS
#define VFULL (HFULL+1)
#define FILLBLKSTART (VFULL+1)
#define OBSRT   (FILLBLKSTART+50)
#define OBSFIN  (OBSRT+6)
#define SHOWFLOW (OBSFIN +1)
#define START    (SHOWFLOW +4)
#define STARTFULL (START+1)
#define ARROW  (STARTFULL +1)
#define BAR    (ARROW +1)
#define NUM_TMP_CURSOR_PIXMAPS (BAR+5)


extern void redisplay_level(Widget w, XtPointer closure, XEvent *event, Boolean *cont);

extern void init_pixmaps(Widget top_shell),
            display_allpixmaps(void),
            display_level(void),
            free_pixmaps(void),
            show_movement(void),
            redraw_block(int x, int y),
            start_new_level(void),
            redisplay_sequence(void);


#define CELLSIZE 40

#define pos_to_coord( _pos_ ) (( _pos_ ) * CELLSIZE + 5)
#define coord_to_pos( _pos_ ) ((( _pos_ ) - 5) / CELLSIZE)

/*
 * from actions.c
 */


extern void     do_nothing_action( Widget w, XEvent *event, String *params, Cardinal *num_params);
extern void     move_here_action(Widget w, XButtonEvent *event, String *params, Cardinal *num_params);
extern void     fast_flow_action(Widget w, XEvent *event, String *params, Cardinal *num_params);
extern void     place_action(Widget w, XButtonEvent *event, String *params, Cardinal *num_params);
extern void     move_action( Widget w, XButtonEvent *event, String *params, Cardinal *num_params);
extern void     pointer_moved(Widget w, XtPointer closure, XEvent *event, Boolean *cont);


/*
 * from score.c
 */

//#define XSTR(x) STR(x)
//#define STR(x) #x
//#pragma message "The value of SCORE_FILE: " XSTR(SCORE_FILE)

#ifndef SCORE_FILE
#  define SCORE_FILE "/usr/games/lib/xpipescores"
#  error "undefined SCORE_FILE"
#endif

#ifndef MAXSCORES
#  define MAXSCORES 20
#endif

extern void create_high_score_popup(Widget parent);
extern void check_score(int current_score, int level);

extern void show_scores_callback(void);
extern void show_scores();
extern char *score_filename;

/*
 * from game.c
 */

# 	define 	MAXX 15
#  	define 	MAXY 10


#define FASTFLOW 100

#define LEFT    1
#define RIGHT   2
#define UP      4
#define DOWN    8
#define STILL   16

#define for_each	for(x=0;x<MAXX;x++) \
			  for(y=0;y<MAXY;y++)

/* I know, I KNOW... global variables! */

extern XtIntervalId current_callback;

extern int 	block_x, block_y,level,
           	last_block_x, last_block_y;

extern int	pipe_board[MAXX][MAXY];

extern int      buttons_disabled; /*stops button events during level change*/

extern int 	score,
		game_active;

#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)

#define INXRANGE( _x_ )  (((_x_) >=0) && ((_x_)<(MAXX-3)))
#define INYRANGE( _y_ )  (((_y_) >=0) && ((_y_)<MAXY))

extern void 	new_game(void),
		//add_score(void),
		new_level(void),
                increment_sequence(void),
                reset_block_origin(void),
                remove_block(void),
                speed_up_flow(void),
                draw_flow(void * data, XtIntervalId *id),
                increment_flow(),
                block_replace(int flw_dir);
extern int  	can_go(int x, int y),
                can_place(int x, int y),
                place_block(void);
extern int      current_block;

extern void     new_score(int n);
extern void     reset_bonus(void);
extern void     show_when_flow(void * data, XtIntervalId *id);
extern void     game_over( void * data, XtIntervalId *id);


/*
   From info.c
*/
extern void  show_info(void);
void create_info_popup(Widget parent);

/*
   From popup.c
*/

extern void  show_level_over_popup(void),
             show_game_over_popup(void),
	     level_over_popdown(void),
	     game_over_popdown(void),
	     create_general_popups(Widget parent),
             show_nomore_popup(void),
             nomore_popdown(void);
