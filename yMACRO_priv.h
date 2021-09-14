/*============================----beg-of-source---============================*/ #ifndef yVIKEYS_PRIV
#define yMACRO_PRIV yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "macro processing"
#define     P_PURPOSE   ""

#define     P_NAMESAKE  "pan-agrios (god of the wilderness)"
#define     P_HERITAGE  ""
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yMACRO"
#define     P_FULLNAME  "/usr/local/lib64/libyMACRO"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, separated into independent library"
#define     P_VERNUM    "2.0a"
#define     P_VERTXT    "bare-bones, initial break-out of yVIKEYS code"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
/*---(custom)----------------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */


#define      S_MACRO_MAX      75
extern char  S_MACRO_LIST   [S_MACRO_MAX];



typedef     struct        cMACRO    tMACRO;
struct cMACRO {
   /*---(running)-----------*/
   char        runby;                       /* run by who                     */
   /*---(contents)----------*/
   short       len;                         /* number of keys                 */
   uchar      *keys;                        /* keystrokes                     */
   /*---(execute)-----------*/
   short       pos;                         /* current position               */
   uchar       cur;                         /* current key                    */
   uchar       repeat;                      /* number of repeats              */ /*---(done)--------------*/
};
extern tMACRO  s_macros    [S_MACRO_MAX];
extern int     s_nmacro;           

extern char    s_emode;                     /* run, playback, delay, etc      */
extern char    s_ename;           
extern char    s_ecurr;           
extern char    s_esave;                     /* saved mode for menus           */
extern short   s_epos;           ;

extern char    s_edelay;                    /* execution delay between steps  */
extern char    s_ddelay;                    /* debug delay between steps      */
extern char    s_eupdate;                   /* execution sceen update speed   */
extern char    s_dupdate;                   /* debug sceen update speed       */
extern char    s_pause;           
extern char    s_skips;           
extern char    s_blitzing;                  /* macro blitzing mode º´´´»      */
extern char    s_blitz;                     /* stay in blitz mode (duration)  */

extern char    s_rmode;                     /* recording or not               */
extern char    s_rname;           
extern char    s_rcurr;           
/*> extern char   *s_rbackup   = NULL;                                                <*/
extern uchar   s_rkeys     [LEN_RECD];
extern short   s_rlen;
extern short   s_rpos;
extern uchar   s_rcur;

extern uchar  *g_stub;

extern char    (*s_loader) (char a_name, char *a_keys);
extern char    (*s_saver ) (char a_name, char *a_keys);

#define     MACRO_LOWER    'a'
#define     MACRO_SYSTEM   '0'
#define     MACRO_ALL      '*'


#define     YMACRO_UPPER     'A'
#define     YMACRO_LOWER     'a'
#define     YMACRO_NUMBER    '0'
#define     YMACRO_GREEK     'è'
#define     YMACRO_OTHER     '-'
#define     YMACRO_FULL      '*'



#endif
