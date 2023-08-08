/*============================----beg-of-source---============================*/
#ifndef yMACRO_PRIV
#define yMACRO_PRIV yes


/*===[[ HEADER BEG ]]=========================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_NAME      "yMACRO"
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "macro processing"
#define     P_PURPOSE   ""
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "pan-agrios (god of the wilds)"
#define     P_PRONOUNCE ""
#define     P_HERITAGE  ""
#define     P_BRIEFLY   "god of the wilderness"
#define     P_IMAGERY   ""
#define     P_REASON    ""
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_HOMEDIR   "/home/system/yMACRO.standard_macro_processor"
#define     P_BASENAME  "yMACRO"
#define     P_FULLNAME  "/usr/local/lib64/libyMACRO"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 11.3.0"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
/*········· ··········· ´·····························´········································*/
#define     P_DEPSTDC   "stdio,stdlib,string"
#define     P_DEPPOSIX  "···"
#define     P_DEPCORE   "yURG,yLOG,ySTR"
#define     P_DEPVIKEYS "yVIHUB,yMODE,yKEYS"
#define     P_DEPOTHER  "yPARSE"
#define     P_DEPSOLO   "···"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.2-, better inter-library communication"
#define     P_VERNUM    "2.2e"
#define     P_VERTXT    "fixed agrios not falling back to scripts when complete"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*===[[ HEADER END ]]=========================================================*/


/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(custom vikeys)---------------------*/
#include    <yVIHUB.h>
#include    <yMODE.h>             /* heatherly vi-keys mode processing        */
#include    <yKEYS.h>             /* heatherly vi-keys mode processing        */
/*---(custom other)----------------------*/
#include    <yPARSE.h>            /* heatherly file reading and writing       */

/*
 * metis § mv8·· § macro keys to check current char against expected and act if true      § M2865o §  · §
 *
 * metis § yg8·· § force exact range with ® operator followed by range and ¦              § M2M1u5 §  · §
 * metis § yg8·· § char check with Û···¦ (match) or Ú···¦ (not) then ¢´ replace if match  § M2M1ur §  · §
 * metis § yg8·· § use ä (for each) operator to do something over selected area           § M2M1wI §  · §
 *
 */


/*---(conditions)------*/
#define     IF_MACRO_OFF         if (yMACRO_exe_mode () == MACRO_STOP     ) 
#define     IF_MACRO_RUN         if (yMACRO_exe_mode () == MACRO_RUN      ) 
#define     IF_MACRO_NOT_RUN     if (yMACRO_exe_mode () != MACRO_RUN      ) 
#define     IF_MACRO_DELAY       if (yMACRO_exe_mode () == MACRO_DELAY    ) 
#define     IF_MACRO_PLAYBACK    if (yMACRO_exe_mode () == MACRO_PLAYBACK ) 
#define     IF_MACRO_MOVING      if (yMACRO_exe_mode () == MACRO_RUN      || yMACRO_exe_mode () == MACRO_DELAY   ) 
#define     IF_MACRO_NOT_MOVING  if (yMACRO_exe_mode () != MACRO_RUN      && yMACRO_exe_mode () != MACRO_DELAY   ) 
#define     IF_MACRO_NOT_PLAYING if (yMACRO_exe_mode () == MACRO_STOP     )
#define     IF_MACRO_PLAYING     if (yMACRO_exe_mode () != MACRO_STOP     )
#define     IF_MACRO_ON          if (yMACRO_exe_mode () != MACRO_STOP     ) 
/*---(setting)---------*/
#define     SET_MACRO_OFF        yMACRO_modeset (MACRO_STOP);
#define     SET_MACRO_STOP       yMACRO_modeset (MACRO_STOP);
#define     SET_MACRO_RUN        yMACRO_modeset (MACRO_RUN);
#define     SET_MACRO_PLAYBACK   yMACRO_modeset (MACRO_PLAYBACK);
#define     SET_MACRO_DELAY      yMACRO_modeset (MACRO_DELAY);
/*---(speeds)----------*/
#define     MACRO_BLITZ        '0'
#define     MACRO_FAST         '1'
#define     MACRO_THOU         '2'
#define     MACRO_HUND         '3'
#define     MACRO_TWENTY       '4'
#define     MACRO_TENTH        '5'
#define     MACRO_HALF         '6'
#define     MACRO_SEC          '7'
#define     MACRO_DOUBLE       '8'
#define     MACRO_TRIPLE       '9'
/*---(updates)---------*/
#define     MACRO_FAST         'f'  /* fast   updates */
#define     MACRO_NORMAL       'n'  /* normal updates */
#define     MACRO_SLOWER       's'  /* slower updates */
#define     MACRO_BLINKS       'b'  /* stop action looking */
#define     MACRO_PEEKS        'p'  /* very slow screen updates */
#define     MACRO_BLIND        'd'  /* no screen updates */


/*---(recording)-------*/
#define     MACRO_IGNORE       'i'      /* no recording                       */
#define     MACRO_RECORD       'r'      /* macro recording                    */
#define     IF_MACRO_RECORDING   if (yMACRO_rec_mode () == MACRO_RECORD   ) 
#define     SET_MACRO_RECORD     yMACRO_modeset (MACRO_RECORD);
#define     SET_MACRO_IGNORE     yMACRO_modeset (MACRO_IGNORE);

#define     CASE_MACRO_KEYS   '@' : case 'q' : case 'Q'


#define      S_MACRO_MAX      75
extern char  S_MACRO_LIST   [S_MACRO_MAX];
#define      MACRO_REPO          "/home/shared/yVIKEYS/repository.macro"
#define      MAX_AGRIOS       20

typedef    struct    cMY    tMY;
struct cMY {
   /*---(execution)------------*/
   short       erepeat;
   char        emode;                       /* run, playback, delay, etc      */
   char        ename;           
   char        ecurr;           
   char        esave;                       /* saved mode for menus           */
   char        eblitz;                      /* saved blitz for menus          */
   char        eblitzing;                   /* saved blitzing for menus       */
   short       epos;
   uchar       edelay;                      /* execution delay between steps  */
   uchar       eupdate;                     /* execution sceen update         */
   char        pauses;           
   char        nskip;           
   char        cskip;           
   char        blitzing;                    /* macro blitzing mode º´´´»      */
   char        blitz;                       /* stay in blitz mode (duration)  */
   char        ignore;
   /*---(playback)-------------*/
   uchar       ddelay;                      /* playback/delay between steps   */
   uchar       dupdate;                     /* playback/debug screen update   */
   /*---(recording)------------*/
   char        rmode;                       /* recording or not               */
   char        rname;           
   char        rcurr;           
   uchar       rkeys     [LEN_RECD];
   uchar       modes     [LEN_RECD];
   short       rlen;
   short       rpos;
   uchar       rcur;
   /*---(stack)----------------*/
   char        edepth;
   char        estack    [LEN_LABEL];
   /*---(functions)------------*/
   char      (*e_loader) (char a_name, char *a_keys);
   char      (*e_saver ) (char a_name, char *a_keys);
   /*---(agrios)---------------*/
   uchar       g_style;
   uchar       g_active;
   uchar       g_agrios  [LEN_RECD];
   char      (*e_getter) (char a_type, char *r_label, char *r_content, char *r_next);
   char      (*e_forcer) (char a_type, char *a_target, char *a_contents);
   char      (*e_pusher) (char a_dir , char  a_level, char *a_args);
   char        g_level;
   char        g_curr    [MAX_AGRIOS][LEN_LABEL];
   char        g_code    [MAX_AGRIOS][LEN_RECD];
   char        g_next    [MAX_AGRIOS][LEN_LABEL];
   /*---(done)-----------------*/
};
extern tMY         myMACRO;



typedef     struct        cMACRO    tMACRO;
struct cMACRO {
   /*---(running)-----------*/
   char        runby;                       /* run by who                     */
   /*---(contents)----------*/
   short       len;                         /* number of keys                 */
   uchar      *keys;                        /* keystrokes                     */
   uchar      *modes;                       /* expected modes                 */
   /*---(execute)-----------*/
   short       pos;                         /* current position               */
   uchar       cur;                         /* current key                    */
   uchar       repeat;                      /* number of repeats              */ /*---(done)--------------*/
};
extern tMACRO  g_macros    [S_MACRO_MAX];
extern int     g_nmacro;           


extern uchar  *g_stub;




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
char        ymacro_reset            (uchar a_abbr);
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
uchar       ymacro_smode            (uchar a_major, uchar a_minor);
/*---(unittest)-------------*/
char        ymacro__unit_quiet      (void);
char        ymacro__unit_loud       (void);
char        ymacro__unit_end        (void);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_rec_mode         (void);
char        ymacro_rec_set          (uchar a_abbr);
char        ymacro_rec_reset        (void);
char        ymacro_rec_clear        (void);
char        ymacro_rec_beg          (uchar a_name);
char        yMACRO_rec_key          (uchar a_key, uchar a_mode);
char        ymacro_rec_str          (char *a_keys);
char        yMACRO_rec_end          (void);
char        yMACRO_direct           (char *a_string);



/*===[[ yMACRO_file.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ymacro_file_handlers    (void);
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
char        yMACRO_exe_pos          (char *a_name, short *a_pos);
char        yMACRO_exe_repos        (int a_pos);
char        ymacro_exe_beg          (uchar a_name, uchar a_style);
char        ymacro_exe_skips        (void);
char        ymacro_exe_adv          (uchar a_play);
char        ymacro_exe_key          (void);
char        ymacro_exe_control      (uchar a_key);
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



/*===[[ yMACRO_rptg.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ymacro_status__exe      (char n, short h, char *a_rep, char *a_pos, char *a_len, char *a_list);
char        ymacro_dump             (FILE *f);



/*===[[ yMACRO_script.c ]]====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yMACRO_skip             (void);
char        yMACRO_unskip           (void);
char        yMACRO_skipping         (void);
char        ymacro_script__open     (char *a_name);
char        ymacro_script__close    (void);
char        ymacro_script__read     (void);
char        ymacro_script__start    (char *a_name, char a_style);


char*       yMACRO__unit            (char *a_question, uchar a_abbr);



/*===[[ yMACRO_agrios.c ]]====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ymacro_agrios_style     (char a_style);
char        ymacro_agrios_init      (void);
char        ymacro_agrios__read     (char a_first);



#endif
