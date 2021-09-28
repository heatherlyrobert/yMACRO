/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"


char    S_MACRO_LIST   [S_MACRO_MAX];

tMACRO  g_macros    [S_MACRO_MAX];
int     g_nmacro    =    0;

char    g_emode     =  '-';          /* run, playback, delay, etc      */
char    g_ename     =  '-';
char    g_ecurr     =   -1;
char    g_esave     =  '-';          /* saved mode for menus           */
short   g_epos      =   -1;

char    g_edelay    = MACRO_BLITZ;   /* execution delay between steps  */
char    g_ddelay    = MACRO_BLITZ;   /* debug delay between steps      */
char    g_eupdate   = MACRO_NORMAL;  /* execution sceen update speed   */
char    g_dupdate   = MACRO_NORMAL;  /* debug sceen update speed       */
char    g_pause     =    0;
char    s_skips     =    0;
char    g_blitzing  =  '-';          /* macro blitzing mode º´´´»      */
char    g_blitz     =  '-';          /* stay in blitz mode (duration)  */

char    g_rmode     =  '-';          /* recording or not               */
char    g_rname     =  '-';
char    g_rcurr     =   -1;
/*> char   *s_rbackup   = NULL;                                                <*/
uchar   g_rkeys     [LEN_RECD];
short   g_rlen      =    0;
short   g_rpos      =    0;
uchar   g_rcur      =  '-';

uchar   *g_stub     = "";

char    (*s_loader) (char a_name, char *a_keys);
char    (*s_saver ) (char a_name, char *a_keys);



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yMACRO_ver [200] = "";

char*        /*--> return library versioning info --------[ leaf-- [ ------ ]-*/
yMACRO_version          (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yMACRO_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yMACRO_ver;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char         /*-> initialize macro environment -------[ shoot  [gz.210.001.01]*/ /*-[00.0000.102.4]-*/ /*-[--.---.---.--]-*/
yMACRO_init             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (SMOD_MACRO)) {
      DEBUG_PROG   yLOG_note    ("status is not ready for init");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(macro abbrev list)--------------*/
   strlcpy (S_MACRO_LIST, ""         , S_MACRO_MAX);
   strlcat (S_MACRO_LIST, YSTR_NUMBER, S_MACRO_MAX);
   strlcat (S_MACRO_LIST, YSTR_LOWER , S_MACRO_MAX);
   strlcat (S_MACRO_LIST, YSTR_GREEK , S_MACRO_MAX);
   strlcat (S_MACRO_LIST, "."        , S_MACRO_MAX);
   DEBUG_PROG   yLOG_info    ("LIST"      , S_MACRO_LIST);
   g_nmacro = strlen (S_MACRO_LIST);
   /*---(clear exec)---------------------*/
   g_emode     = '-';
   g_ename     = '-';
   g_ecurr     =  -1;
   g_edelay    = MACRO_BLITZ;
   g_eupdate   = MACRO_NORMAL;
   g_ddelay    = MACRO_BLITZ;
   g_dupdate   = MACRO_NORMAL;
   g_pause     =  0;
   g_blitz     = '-';
   g_blitzing  = '-';
   /*---(clear rec)----------------------*/
   g_rmode     = '-';
   g_rname     = '-';
   g_rcurr     =  -1;
   g_rkeys [0] = '£';
   g_rlen      =   0;
   g_rpos      =   0;
   g_rcur      = '-';
   /*---(clear pointers)-----------------*/
   s_loader = NULL;
   s_saver  = NULL;
   /*---(clear data)---------------------*/
   ymacro_purge (MACRO_ALL);
   /*> strlcpy (myVIKEYS.m_script, "", LEN_DESC);                                     <*/
   /*---(file handlers)------------------*/
   rc = yPARSE_handler_max (SMOD_MACRO   , "macro"     , 7.3, "cO----------", -1, yMACRO_reader, yMACRO_writer, "------------" , "a,keys", "keyboard macros"           );
   DEBUG_FILE   yLOG_value   ("macro"     , rc);
   /*---(status)-------------------------*/
   /*> yVIKEYS_view_optionX (YVIKEYS_STATUS, "macro"  , yvikeys_macro_estatus , "details of macro playback"                );   <* 
    *> yVIKEYS_view_optionX (YVIKEYS_STATUS, "record" , yvikeys_macro_rstatus , "details of macro recording"               );   <*/
   /*---(update status)------------------*/
   DEBUG_PROG   yLOG_note    ("update status");
   yMODE_init_set   (SMOD_MACRO, ymacro_smode);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> initialize macro environment -------[ shoot  [gz.210.001.01]*/ /*-[00.0000.102.4]-*/ /*-[--.---.---.--]-*/
yMACRO_config           (void *a_loader, void *a_saver)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (SMOD_MACRO)) {
      DEBUG_SCRP   yLOG_note    ("init must complete before config");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   if (a_loader != NULL) s_loader = a_loader;
   DEBUG_SCRP   yLOG_point   ("loader"    , s_loader);
   if (a_saver  != NULL) s_saver  = a_saver;
   DEBUG_SCRP   yLOG_point   ("saver"     , s_saver);
   /*---(update status)------------------*/
   yMODE_conf_set   (SMOD_MACRO, '1');
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_wrap             (void)
{
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         mode setting                         ----===*/
/*====================------------------------------------====================*/
static void  o___MODES___________o () { return; }

char
yMACRO_modeset          (char a_mode)
{
   if      (a_mode == MACRO_IGNORE)  g_rmode = a_mode;
   else if (a_mode == MACRO_RECORD)  g_rmode = a_mode;
   else                              g_emode = a_mode;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          repeating                           ----===*/
/*====================------------------------------------====================*/
static void  o___REPEAT__________o () { return; }

char
yMACRO_zero             (void)
{
   if (g_ecurr < 0)  return 0;
   g_macros [g_ecurr].repeat = 0;
   return 0;
}

char
yMACRO_count            (void)
{
   if (g_ecurr < 0)                   return 0;
   return g_macros [g_ecurr].repeat;
}



/*====================------------------------------------====================*/
/*===----                        finding/checking                      ----===*/
/*====================------------------------------------====================*/
static void  o___FINDING_________o () { return; }

char 
ymacro_index            (uchar a_abbr)
{
   int         n           =   -1;
   if (a_abbr == 0)  return n;
   if (a_abbr == ',')  a_abbr = '.';
   n  = strlchr (S_MACRO_LIST, a_abbr, S_MACRO_MAX);
   return n;
}





/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___CLEARING________o () { return; }

char         /*-> fully reset a macro ----------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_clear            (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =   -1;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   DEBUG_PROG   yLOG_schar   (a_abbr);
   /*---(defense)------------------------*/
   n = ymacro_index (a_abbr);
   DEBUG_PROG   yLOG_sint    (n);
   if (n < 0) {
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(running)------------------------*/
   DEBUG_PROG   yLOG_snote   ("runby");
   g_macros [n].runby     =   -1;
   /*---(contents)-----------------------*/
   DEBUG_PROG   yLOG_snote   ("data");
   if (g_macros [n].keys != g_stub)  free (g_macros [n].keys);
   g_macros [n].keys      = g_stub;
   g_macros [n].len       =    0;
   /*---(execute)------------------------*/
   DEBUG_PROG   yLOG_snote   ("exec");
   g_macros [n].pos       =   -1;
   g_macros [n].cur       =    0;
   g_macros [n].repeat    =    0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> fully reset a macro ----------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_wipe             (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   DEBUG_PROG   yLOG_schar   (a_abbr);
   /*---(defense)------------------------*/
   n = ymacro_index (a_abbr);
   DEBUG_PROG   yLOG_sint    (n);
   if (n < 0) {
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(running)------------------------*/
   DEBUG_PROG   yLOG_snote   ("runby");
   g_macros [n].runby     =   -1;
   /*---(execute)------------------------*/
   DEBUG_PROG   yLOG_snote   ("exec");
   g_macros [n].pos       =   -1;
   g_macros [n].cur       =    0;
   g_macros [n].repeat    =    0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_purge            (char a_scope)
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
   DEBUG_SCRP   yLOG_value   ("g_nmacro"  , g_nmacro);
   for (i = 0; i < g_nmacro; ++i) {
      x_abbr = S_MACRO_LIST [i];
      if (a_scope == YMACRO_LOWER  && strchr (YSTR_LOWER , x_abbr) == NULL)  continue;
      if (a_scope == YMACRO_NUMBER && strchr (YSTR_NUMBER, x_abbr) == NULL)  continue;
      if (a_scope == YMACRO_GREEK  && strchr (YSTR_GREEK , x_abbr) == NULL)  continue;
      ymacro_clear (x_abbr);
   }
   /*---(clear current)------------------*/
   g_emode = '-';
   g_ename = '-';
   g_ecurr = -1;
   g_rmode = '-';
   g_rname = '-';
   g_rcurr = -1;
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
yMACRO_reset_all        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        x_abbr      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_senter  (__FUNCTION__);
   /*---(mode)---------------------------*/
   ymacro_rec_reset ();
   ymacro_exe_reset ();
   DEBUG_SCRP   yLOG_snote   ("macro_off");
   SET_MACRO_IGNORE;
   SET_MACRO_STOP;
   /*---(reset positions)----------------*/
   for (i = 0; i < g_nmacro; ++i) {
      x_abbr = S_MACRO_LIST [i];
      ymacro_wipe  (x_abbr);
   }
   /*---(record clear)-------------------*/
   g_rkeys [0] = G_KEY_NULL;
   g_rlen      = 0;
   g_rpos      =   0;
   g_rcur      = '-';
   g_rcurr     = -1;
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

uchar
yMACRO_handle_prep (uchar a_major, uchar a_minor)
{
   switch (a_minor) {
   case '@' :
      yMODE_enter  (SMOD_MACRO   );
      return a_minor;
      break;
   case 'q' :
      IF_MACRO_RECORDING {
         yMACRO_rec_end ();
      } else {
         yMODE_enter  (SMOD_MACRO   );
         return a_minor;
      }
      break;
   case 'Q' :
      yMACRO_reset_all ();
      break;
   }
   return 0;
}

uchar        /*-> process macro sub-mode keys --------[ ------ [ge.H65.229.88]*/ /*-[02.0000.102.!]-*/ /*-[--.---.---.--]-*/
ymacro_smode            (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_majors    [LEN_LABEL] = "q@<>";
   char        x_keys      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_char    ("a_major"   , a_major);
   DEBUG_USER   yLOG_char    ("a_minor"   , a_minor);
   /*---(defenses)-----------------------*/
   DEBUG_USER   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (SMOD_MACRO))  {
      DEBUG_USER   yLOG_note    ("not the correct mode");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_USER   yLOG_info    ("x_majors"   , x_majors);
   --rce;  if (strchr (x_majors, a_major) == 0) {
      DEBUG_USER   yLOG_note    ("a_major is not valid");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(mode changes)-------------------*/
   if (a_minor == G_KEY_ESCAPE || a_minor == G_KEY_RETURN || a_minor == G_KEY_ENTER ) {
      DEBUG_USER   yLOG_note    ("escape/return, nothing to do");
      yMODE_exit  ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check for recording)------------*/
   --rce;  if (a_major == 'q') {
      DEBUG_USER   yLOG_note    ("macro recording");
      /*---(start recording)-------------*/
      yMODE_exit  ();
      rc = ymacro_rec_beg (a_minor);
      if (rc < 0) {
         DEBUG_USER   yLOG_note    ("can not execute");
         DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check for execution)------------*/
   --rce;  if (a_major == '@') {
      DEBUG_USER   yLOG_note    ("macro execution");
      /*---(check for previous)----------*/
      if (a_minor == '@') {
         DEBUG_USER   yLOG_note    ("rerun previously used macro");
         a_minor = g_ename;
      }
      /*---(execute)---------------------*/
      yMODE_exit  ();
      rc = ymacro_exe_beg  (a_minor);
      if (rc < 0) {
         DEBUG_USER   yLOG_note    ("can not execute");
         DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
      /*---(done)------------------------*/
   }
   /*---(errors fall through)------------*/
   --rce;
   ymacro_rec_reset ();
   ymacro_exe_reset ();
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char          unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
ymacro__unit_quiet      (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMACRO_unit" };
   /*> yURG_logger   (x_narg, x_args);                                                <*/
   /*> yURG_urgs     (x_narg, x_args);                                                <*/
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   yMACRO_init ();
   yMACRO_config (NULL, NULL);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ymacro__unit_loud       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMACRO_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   yURG_name  ("yparse"       , YURG_ON);
   DEBUG_YVIKEYS yLOG_info     ("yMACRO"     , yMACRO_version   ());
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   yMACRO_init ();
   yMACRO_config (NULL, NULL);
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ymacro__unit_end        (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*> yVIKEYS_wrap ();                                                               <*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yMACRO__unit            (char *a_question, uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =    0;
   char        x_list      [LEN_RECD];
   char        t           [LEN_RECD];
   int         c           =    0;
   int         x_len       =    0;
   int         i           =    0;
   /*---(preprare)-----------------------*/
   strcpy  (unit_answer, "MACRO unit       : question not understood");
   /*---(simple questions)---------------*/
   if      (strcmp (a_question, "rec"            )   == 0) {
      if (g_rcurr < 0) snprintf (unit_answer, LEN_RECD, "MACRO rec    (%c) : macro pointer grounded", g_rname);
      else {
         sprintf (t, "[%-.33s]", g_rkeys);
         if (g_rlen > 33)  t [34] = '>';
         snprintf (unit_answer, LEN_RECD, "MACRO rec    (%c) : %c %2d %2d%s", g_rname, g_rmode, g_rpos, g_rlen, t);
      }
      return unit_answer;
   }
   else if (strcmp (a_question, "exec"           )   == 0) {
      if (g_ecurr < 0)  snprintf (unit_answer, LEN_RECD, "MACRO exec   (%c) : macro pointer grounded", g_ename);
      else             snprintf (unit_answer, LEN_RECD, "MACRO exec   (%c) : %c %c %3d %02x %3d[%-.30s]", g_ename, g_emode, g_ddelay, g_macros [g_ecurr].pos, (uchar) g_macros [g_ecurr].cur, g_macros [g_ecurr].len, g_macros [g_ecurr].keys);
      return unit_answer;
   }
   /*> else if (strcmp (a_question, "keys"           )   == 0) {                                             <* 
    *>    snprintf (unit_answer, LEN_RECD, "MACRO keys   (%c) : %-.45s", a_abbr, g_macros [g_ecurr].keys);   <* 
    *>    return unit_answer;                                                                                <* 
    *> }                                                                                                     <*/
   else if (strcmp (a_question, "list"           )   == 0) {
      c = yMACRO_list ('F', x_list);
      snprintf (unit_answer, LEN_RECD, "MACRO list       : %2d %s", c, x_list);
      return unit_answer;
   }
   /*> else if (strcmp (a_question, "speed"          )   == 0) {                                                                                                                                                                                      <* 
    *>    snprintf (unit_answer, LEN_RECD, "MACRO speed    %c : %8.6fd %5.3fu %2d/%2ds, deb %c/%c, exe %c/%c, %2dp", g_blitzing, myVIKEYS.delay, myVIKEYS.update, s_skips, myVIKEYS.macro_skip, g_ddelay, g_dupdate, g_edelay, g_eupdate, g_pause);   <* 
    *>    return unit_answer;                                                                                                                                                                                                                         <* 
    *> }                                                                                                                                                                                                                                              <*/
   /*> else if (strcmp (a_question, "clip"           )   == 0) {                                  <* 
    *>    yvikeys_dump_read (a_abbr, t, &x_len);                                                  <* 
    *>    snprintf (unit_answer, LEN_RECD, "MACRO clip  (%2d) : %2d[%.40s]", a_abbr, x_len, t);   <* 
    *>    return unit_answer;                                                                     <* 
    *> }                                                                                          <*/
   /*---(complex questions)--------------*/
   n = ymacro_index (a_abbr);
   if (n < 0) {
      strcpy  (unit_answer, "MACRO unit       : not a valid macro name");
      return unit_answer;
   }
   else if (strcmp (a_question, "saved"          )   == 0) {
      if (n < 0)  snprintf (unit_answer, LEN_RECD, "MACRO saved  (%c) : not a valid macro name", a_abbr);
      else {
         sprintf (t, "å%-.33sæ", g_macros [n].keys);
         if (g_macros [n].len > 33)  t [34] = '>';
         snprintf (unit_answer, LEN_RECD, "MACRO saved  (%c) : %2d%-35.35s %2d %2d %2d", a_abbr, g_macros [n].len, t, g_macros [n].pos, g_macros [n].runby, g_macros [n].repeat);
      }
   }
   /*> else if (strcmp (a_question, "full"           )   == 0) {                                                <* 
    *>    if (n < 0)  snprintf (unit_answer, LEN_RECD, "MACRO full   (%c) : not a valid macro name", a_abbr);   <* 
    *>    else        snprintf (unit_answer, LEN_RECD, "MACRO full   (%c) : %s", a_abbr, g_macros [n].keys);    <* 
    *> }                                                                                                        <*/
   else if (strcmp (a_question, "repeat"       )  == 0) {
      snprintf (unit_answer, LEN_FULL, "MACRO repeat     : %d", yKEYS_repeats ());
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




