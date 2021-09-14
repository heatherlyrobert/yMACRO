/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"


char    S_MACRO_LIST   [S_MACRO_MAX];

tMACRO  s_macros    [S_MACRO_MAX];
int     s_nmacro    =    0;

char    s_emode     =  '-';          /* run, playback, delay, etc      */
char    s_ename     =  '-';
char    s_ecurr     =   -1;
char    s_esave     =  '-';          /* saved mode for menus           */
short   s_epos      =   -1;

char    s_edelay    = MACRO_BLITZ;   /* execution delay between steps  */
char    s_ddelay    = MACRO_BLITZ;   /* debug delay between steps      */
char    s_eupdate   = MACRO_NORMAL;  /* execution sceen update speed   */
char    s_dupdate   = MACRO_NORMAL;  /* debug sceen update speed       */
char    s_pause     =    0;
char    s_skips     =    0;
char    s_blitzing  =  '-';          /* macro blitzing mode º´´´»      */
char    s_blitz     =  '-';          /* stay in blitz mode (duration)  */

char    s_rmode     =  '-';          /* recording or not               */
char    s_rname     =  '-';
char    s_rcurr     =   -1;
/*> char   *s_rbackup   = NULL;                                                <*/
uchar   s_rkeys     [LEN_RECD];
short   s_rlen      =    0;
short   s_rpos      =    0;
uchar   s_rcur      =  '-';

uchar   *g_stub     = "";

char    (*s_loader) (char a_name, char *a_keys);
char    (*s_saver ) (char a_name, char *a_keys);



/*====================------------------------------------====================*/
/*===----                        finding/checking                      ----===*/
/*====================------------------------------------====================*/
static void  o___FINDING_________o () { return; }

int  
ymacro__index           (uchar a_abbr)
{
   int         n           =   -1;
   if (a_abbr == 0)  return n;
   if (a_abbr == ',')  a_abbr = '.';
   n  = strlchr (S_MACRO_LIST, a_abbr, S_MACRO_MAX);
   return n;
}

int  
ymacro__rset            (uchar a_abbr)
{
   int         n           =   -1;
   if (a_abbr == 0)  return n;
   if (a_abbr == ',')  a_abbr = '.';
   n  = strlchr (S_MACRO_LIST, a_abbr, S_MACRO_MAX);
   if (n >= 0) {
      s_rname = a_abbr;
      s_rcurr = n;
   } else {
      s_rname = '-';
      s_rcurr = -1;
   }
   return n;
}

int  
ymacro__eset            (uchar a_abbr)
{
   int         n           =   -1;
   if (a_abbr == 0)  return n;
   if (a_abbr == ',')  a_abbr = '.';
   n  = strlchr (S_MACRO_LIST, a_abbr, S_MACRO_MAX);
   if (n >= 0) {
      s_ename = a_abbr;
      s_ecurr = n;
   } else {
      s_ename = '-';
      s_ecurr = -1;
   }
   return n;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___CLEARING________o () { return; }

char         /*-> fully reset a macro ----------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro__clear           (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =   -1;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   DEBUG_PROG   yLOG_schar   (a_abbr);
   /*---(defense)------------------------*/
   n = ymacro__index (a_abbr);
   DEBUG_PROG   yLOG_sint    (n);
   if (n < 0) {
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(running)------------------------*/
   DEBUG_PROG   yLOG_snote   ("runby");
   s_macros [n].runby     =   -1;
   /*---(contents)-----------------------*/
   DEBUG_PROG   yLOG_snote   ("data");
   if (s_macros [n].keys != g_stub)  free (s_macros [n].keys);
   s_macros [n].keys      = g_stub;
   s_macros [n].len       =    0;
   /*---(execute)------------------------*/
   DEBUG_PROG   yLOG_snote   ("exec");
   s_macros [n].pos       =   -1;
   s_macros [n].cur       =    0;
   s_macros [n].repeat    =    0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> fully reset a macro ----------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
yvikeys_macro__wipe     (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   DEBUG_PROG   yLOG_schar   (a_abbr);
   /*---(defense)------------------------*/
   n = ymacro__index (a_abbr);
   DEBUG_PROG   yLOG_sint    (n);
   if (n < 0) {
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(running)------------------------*/
   DEBUG_PROG   yLOG_snote   ("runby");
   s_macros [n].runby     =   -1;
   /*---(execute)------------------------*/
   DEBUG_PROG   yLOG_snote   ("exec");
   s_macros [n].pos       =   -1;
   s_macros [n].cur       =    0;
   s_macros [n].repeat    =    0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
yvikeys_macro__purge    (char a_scope)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   char        x_abbr      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(turn off)-----------------------*/
   SET_MACRO_IGNORE;
   SET_MACRO_STOP;
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_char    ("a_scope"   , a_scope);
   --rce;  switch (a_scope) {
   case YMACRO_LOWER  : case YMACRO_NUMBER :
   case YMACRO_GREEK  : case YMACRO_FULL   :
      break;
   default :
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   DEBUG_SCRP   yLOG_value   ("s_nmacro"  , s_nmacro);
   for (i = 0; i < s_nmacro; ++i) {
      x_abbr = S_MACRO_LIST [i];
      if (a_scope == YMACRO_LOWER  && strchr (YSTR_LOWER , x_abbr) == NULL)  continue;
      if (a_scope == YMACRO_NUMBER && strchr (YSTR_NUMBER, x_abbr) == NULL)  continue;
      if (a_scope == YMACRO_GREEK  && strchr (YSTR_GREEK , x_abbr) == NULL)  continue;
      ymacro__clear (x_abbr);
   }
   /*---(clear current)------------------*/
   s_emode = '-';
   s_ename = '-';
   s_ecurr = -1;
   s_rmode = '-';
   s_rname = '-';
   s_rcurr = -1;
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
yvikeys_macro_resetall  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        x_abbr      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_senter  (__FUNCTION__);
   /*---(mode)---------------------------*/
   DEBUG_SCRP   yLOG_snote   ("macro_off");
   SET_MACRO_IGNORE;
   SET_MACRO_STOP;
   /*---(reset positions)----------------*/
   for (i = 0; i < s_nmacro; ++i) {
      x_abbr = S_MACRO_LIST [i];
      yvikeys_macro__wipe  (x_abbr);
   }
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
yvikeys_macro_rreset    (void)
{
   if (s_rcurr < 0)  return 0;
   yvikeys_macro__wipe (S_MACRO_LIST [s_rcurr]);
   return 0;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
yvikeys_macro_ereset    (void)
{
   if (s_rcurr < 0)  return 0;
   yvikeys_macro__wipe (S_MACRO_LIST [s_ecurr]);
   return 0;
}
