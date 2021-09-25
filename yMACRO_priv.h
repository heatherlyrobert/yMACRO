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
#define     P_VERNUM    "2.0h"
#define     P_VERTXT    "all code copied over from yVIKEYS, but unclean"

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
#include    <yMODE.h>             /* heatherly vi/vim mode processing         */
#include    <yKEYS.h>             /* heatherly vi/vim mode processing         */
#include    <yVIKEYS_solo.h>      /* heatherly vi/vim keys processing         */


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
extern tMACRO  g_macros    [S_MACRO_MAX];
extern int     g_nmacro;           

extern char    g_emode;                     /* run, playback, delay, etc      */
extern char    g_ename;           
extern char    g_ecurr;           
extern char    g_esave;                     /* saved mode for menus           */
extern short   g_epos;           ;

extern char    g_edelay;                    /* execution delay between steps  */
extern char    g_ddelay;                    /* debug delay between steps      */
extern char    g_eupdate;                   /* execution sceen update speed   */
extern char    g_dupdate;                   /* debug sceen update speed       */
extern char    g_pause;           
extern char    s_skips;           
extern char    g_blitzing;                  /* macro blitzing mode º´´´»      */
extern char    g_blitz;                     /* stay in blitz mode (duration)  */

extern char    g_rmode;                     /* recording or not               */
extern char    g_rname;           
extern char    g_rcurr;           
/*> extern char   *s_rbackup   = NULL;                                                <*/
extern uchar   g_rkeys     [LEN_RECD];
extern short   g_rlen;
extern short   g_rpos;
extern uchar   g_rcur;

extern uchar  *g_stub;

extern char    (*s_loader) (char a_name, char *a_keys);
extern char    (*s_saver ) (char a_name, char *a_keys);


extern int   s_request;
extern int   s_repeat;
extern char  s_repeating;

extern int   s_level;
extern int   s_rep     [LEN_LABEL];
extern uchar s_src     [LEN_LABEL];
extern int   s_pos     [LEN_LABEL];

#define     MACRO_LOWER    'a'
#define     MACRO_SYSTEM   '0'
#define     MACRO_ALL      '*'


#define     YMACRO_UPPER     'A'
#define     YMACRO_LOWER     'a'
#define     YMACRO_NUMBER    '0'
#define     YMACRO_GREEK     'è'
#define     YMACRO_OTHER     '-'
#define     YMACRO_FULL      '*'




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
/*---(utility)--------------*/
char*       yMACRO_version          (void);
/*---(program)--------------*/
char        yMACRO_init             (void);
char        yMACRO_config           (void *a_loader, void *a_saver);
char        ymacro_clear            (uchar a_abbr);
char        ymacro_wipe             (uchar a_abbr);
char        ymacro_purge            (char a_scope);
/*---(modes)----------------*/
char        yMACRO_modeset          (char a_mode);
/*---(finding)--------------*/
char        ymacro_index            (uchar a_abbr);
/*---(repeat)---------------*/
char        yMACRO_zero             (void);
char        yMACRO_count            (void);
/*---(mode)-----------------*/
char        ymacro_smode            (uchar a_major, uchar a_minor);
/*---(unittest)-------------*/
char        ymacro__unit_quiet      (void);
char        ymacro__unit_loud       (void);
char        ymacro__unit_end        (void);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_rec_mode         (void);
char        ymacro_rec_set          (uchar a_abbr);
char        ymacro_rec_reset        (void);
char        ymacro_rec_beg          (char a_name);
char        yMACRO_rec_key          (char a_key);
char        ymacro_rec_str          (char *a_keys);
char        yMACRO_rec_end          (void);
char        yMACRO_direct           (char *a_string);



/*===[[ yMACRO_file.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(saving)---------------*/
char        ymacro_save             (void);
char        ymacro_fetch            (void);
/*---(file)-----------------*/
char        ymacro__writer          (int c, uchar a_abbr);
char        yMACRO_writer           (void);
char        yMACRO_reader           (int n, char *a_verb);
/*---(done)-----------------*/

/*===[[ yMACRO_exe.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yMACRO_exe_mode         (void);
char        ymacro_exe_set          (uchar a_abbr);
char        ymacro_exe_reset        (void);
char        yMACRO_exe_pos          (char *a_name, int *a_pos);
char        yMACRO_exe_repos        (int a_pos);
char        ymacro_exe_beg          (char a_name);
char        ymacro_exe_skips        (void);
char        ymacro_exe_adv          (uchar a_play);
char        ymacro_exe_key          (void);
char        ymacro_exe_play         (uchar a_key);
uchar       yMACRO_exec             (uchar a_play);


/*===[[ yMACRO_speed.c ]]=====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(delay)----------------*/
char        ymacro__delay           (char a_which, char a_delay);
/*---(update)---------------*/
char        ymacro__update          (char a_which, char a_update);
/*---(settings)-------------*/
char        ymacro_set2stop         (void);
char        ymacro_set2play         (void);
char        ymacro_set2delay        (void);
char        ymacro_set2run          (void);
char        ymacro_set2blitz        (void);


/*===[[ yMACRO_keys.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ymacro_keys__roll       (void);
char        yMACRO_keys_status      (char *a_msg);
char        ymacro_keys__multi      (int a_pos);
char        yMACRO_keys__logger     (uchar a_key);
char        ymacro_set_error        (void);
char        ymacro_keys_unique      (void);
int         yMACRO_keys_nkey        (void);
int         ymacro_keys_gpos        (void);
char        ymacro_keys_keygpos     (void);
char        ymacro_keys_repeating   (void);
char*       yMACRO_keys_last        (void);
char        ymacro_keys_dump        (FILE *a_file);
char        ymacro_keys_init        (void);
char        ymacro_keys_repos       (int a_pos);



char*       yMACRO__unit            (char *a_question, uchar a_abbr);

#endif
