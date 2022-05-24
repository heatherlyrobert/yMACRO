/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"

/*
 * metis § dn2#· § macro execution is not taking repeat/count for times                   § M2K6RX §  1 §
 *
 *
 *
 */

tMY         myMACRO;



char    S_MACRO_LIST   [S_MACRO_MAX];

tMACRO  g_macros    [S_MACRO_MAX];
int     g_nmacro    =    0;


uchar   *g_stub     = "";




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

char
yMACRO_global_init      (void)
{
   /*---(clear execution)----------------*/
   myMACRO.erepeat   =   0;
   myMACRO.emode     = '-';
   myMACRO.ename     = '-';
   myMACRO.ecurr     =  -1;
   myMACRO.esave     = '-';
   myMACRO.epos      =  -1;
   myMACRO.edelay    = MACRO_BLITZ;
   myMACRO.eupdate   = MACRO_NORMAL;
   myMACRO.pauses    =  0;
   myMACRO.nskip     =  0;
   myMACRO.cskip     =  0;
   myMACRO.blitz     = '-';
   myMACRO.blitzing  = '-';
   yMACRO_unskip  ();
   /*---(playback)-------------*/
   myMACRO.ddelay    = MACRO_BLITZ;
   myMACRO.dupdate   = MACRO_NORMAL;
   /*---(clear recording)----------------*/
   myMACRO.rmode     = '-';
   myMACRO.rname     = '-';
   myMACRO.rcurr     =  -1;
   myMACRO.rkeys [0] = '\0';
   myMACRO.rlen      =   0;
   myMACRO.rpos      =   0;
   myMACRO.rcur      = '-';
   /*---(stack)----------------*/
   myMACRO.edepth    =  0;   
   myMACRO.estack [0]= '\0';
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> initialize macro environment -------[ shoot  [gz.210.001.01]*/ /*-[00.0000.102.4]-*/ /*-[--.---.---.--]-*/
yMACRO_init             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (SMOD_MACRO)) {
      DEBUG_YMACRO   yLOG_note    ("status is not ready for init");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(macro abbrev list)--------------*/
   strlcpy (S_MACRO_LIST, ""         , S_MACRO_MAX);
   strlcat (S_MACRO_LIST, YSTR_NUMBER, S_MACRO_MAX);
   strlcat (S_MACRO_LIST, YSTR_LOWER , S_MACRO_MAX);
   strlcat (S_MACRO_LIST, YSTR_GREEK , S_MACRO_MAX);
   strlcat (S_MACRO_LIST, ". "       , S_MACRO_MAX);
   DEBUG_YMACRO   yLOG_info    ("LIST"      , S_MACRO_LIST);
   g_nmacro = strlen (S_MACRO_LIST);
   /*---(clear globals)------------------*/
   yMACRO_global_init ();
   /*---(clear pointers)-----------------*/
   myMACRO.e_loader  = NULL;
   myMACRO.e_saver   = NULL;
   /*---(clear data)---------------------*/
   ymacro_purge (MACRO_ALL);
   /*> strlcpy (myVIKEYS.m_script, "", LEN_DESC);                                     <*/
   /*---(other updates)------------------*/
   rc = yFILE_dump_add ("macros"    , "mac", "inventory of macros"         , ymacro_dump        );
   ymacro_file_handlers ();
   /*---(agrios)-------------------------*/
   ymacro_agrios_init   ();
   /*---(update status)------------------*/
   DEBUG_YMACRO   yLOG_note    ("update status");
   yMODE_init_set   (SMOD_MACRO, NULL, ymacro_smode);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> initialize macro environment -------[ shoot  [gz.210.001.01]*/ /*-[00.0000.102.4]-*/ /*-[--.---.---.--]-*/
yMACRO_config           (void *a_loader, void *a_saver)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (SMOD_MACRO)) {
      DEBUG_YMACRO   yLOG_note    ("init must complete before config");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   if (a_loader != NULL) myMACRO.e_loader = a_loader;
   DEBUG_YMACRO   yLOG_point   ("loader"    , myMACRO.e_loader);
   if (a_saver  != NULL) myMACRO.e_saver  = a_saver;
   DEBUG_YMACRO   yLOG_point   ("saver"     , myMACRO.e_saver);
   /*---(update status)------------------*/
   yMODE_conf_set   (SMOD_MACRO, '1');
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
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
   if      (a_mode == MACRO_IGNORE)  myMACRO.rmode = a_mode;
   else if (a_mode == MACRO_RECORD)  myMACRO.rmode = a_mode;
   else                              myMACRO.emode = a_mode;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          repeating                           ----===*/
/*====================------------------------------------====================*/
static void  o___REPEAT__________o () { return; }

char
yMACRO_zero             (void)
{
   if (myMACRO.ecurr < 0)  return 0;
   g_macros [myMACRO.ecurr].repeat = 0;
   return 0;
}

char
yMACRO_count            (void)
{
   if (myMACRO.ecurr < 0)                   return 0;
   return g_macros [myMACRO.ecurr].repeat;
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
   DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
   DEBUG_YMACRO   yLOG_schar   (a_abbr);
   /*---(defense)------------------------*/
   n = ymacro_index (a_abbr);
   DEBUG_YMACRO   yLOG_sint    (n);
   if (n < 0) {
      DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(running)------------------------*/
   DEBUG_YMACRO   yLOG_snote   ("runby");
   g_macros [n].runby     =   -1;
   /*---(contents)-----------------------*/
   DEBUG_YMACRO   yLOG_snote   ("data");
   if (g_macros [n].keys != g_stub)  free (g_macros [n].keys);
   g_macros [n].keys      = g_stub;
   g_macros [n].len       =    0;
   /*---(execute)------------------------*/
   DEBUG_YMACRO   yLOG_snote   ("exec");
   g_macros [n].pos       =   -1;
   g_macros [n].cur       =    0;
   g_macros [n].repeat    =    0;
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> fully reset a macro ----------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_reset            (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
   DEBUG_YMACRO   yLOG_schar   (a_abbr);
   /*---(defense)------------------------*/
   n = ymacro_index (a_abbr);
   DEBUG_YMACRO   yLOG_sint    (n);
   if (n < 0) {
      DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(execute)------------------------*/
   DEBUG_YMACRO   yLOG_snote   ("exec");
   g_macros [n].pos       =   -1;
   g_macros [n].cur       =    0;
   g_macros [n].repeat    =    0;
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> fully reset a macro ----------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_wipe             (uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
   DEBUG_YMACRO   yLOG_schar   (a_abbr);
   /*---(defense)------------------------*/
   n = ymacro_index (a_abbr);
   DEBUG_YMACRO   yLOG_sint    (n);
   if (n < 0) {
      DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, n);
      return n;
   }
   /*---(running)------------------------*/
   DEBUG_YMACRO   yLOG_snote   ("runby");
   g_macros [n].runby     =   -1;
   /*---(execute)------------------------*/
   DEBUG_YMACRO   yLOG_snote   ("exec");
   g_macros [n].pos       =   -1;
   g_macros [n].cur       =    0;
   g_macros [n].repeat    =    0;
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(turn off)-----------------------*/
   SET_MACRO_IGNORE;
   SET_MACRO_STOP;
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_scope"   , a_scope);
   --rce;  switch (a_scope) {
   case YMACRO_LOWER  : case YMACRO_NUMBER :
   case YMACRO_GREEK  : case YMACRO_FULL   :
      break;
   default :
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   DEBUG_YMACRO   yLOG_value   ("g_nmacro"  , g_nmacro);
   for (i = 0; i < g_nmacro; ++i) {
      x_abbr = S_MACRO_LIST [i];
      if (a_scope == YMACRO_LOWER  && strchr (YSTR_LOWER , x_abbr) == NULL)  continue;
      if (a_scope == YMACRO_NUMBER && strchr (YSTR_NUMBER, x_abbr) == NULL)  continue;
      if (a_scope == YMACRO_GREEK  && strchr (YSTR_GREEK , x_abbr) == NULL)  continue;
      ymacro_clear (x_abbr);
   }
   /*---(clear current)------------------*/
   myMACRO.emode = '-';
   myMACRO.ename = '-';
   myMACRO.ecurr = -1;
   myMACRO.rmode = '-';
   myMACRO.rname = '-';
   myMACRO.rcurr = -1;
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
yMACRO_reset_all        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        x_abbr      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
   /*---(mode)---------------------------*/
   ymacro_rec_reset ();
   ymacro_exe_reset ();
   DEBUG_YMACRO   yLOG_snote   ("macro_off");
   SET_MACRO_IGNORE;
   SET_MACRO_STOP;
   /*---(reset positions)----------------*/
   for (i = 0; i < g_nmacro; ++i) {
      x_abbr = S_MACRO_LIST [i];
      ymacro_wipe  (x_abbr);
   }
   /*---(record clear)-------------------*/
   myMACRO.rkeys [0] = G_KEY_NULL;
   myMACRO.rlen      = 0;
   myMACRO.rpos      =   0;
   myMACRO.rcur      = '-';
   myMACRO.rcurr     = -1;
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yMACRO_hmode            (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =   -1;
   int         x_repeat    =    0;
   /*---(quick out)----------------------*/
   if (a_major != G_KEY_SPACE)  return 0;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(macros modes)-------------------*/
   switch (a_minor) {
   case '@'      :
      DEBUG_USER   yLOG_note    ("macro execution");
      myMACRO.erepeat = yKEYS_repeats ();
      yKEYS_repeat_reset ();
      DEBUG_USER   yLOG_value   ("erepeat"   , myMACRO.erepeat);
      yMODE_enter  (SMOD_MACRO   );
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return a_minor;
      break;
   case 'q'      :
      yKEYS_repeat_reset ();
      IF_MACRO_RECORDING {
         DEBUG_USER   yLOG_note    ("end macro recording");
         rc = yMACRO_rec_end ();
      } else {
         DEBUG_USER   yLOG_note    ("begin macro recording");
         yMODE_enter  (SMOD_MACRO   );
         rc = a_minor;
      }
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rc;
      break;
   case 'Q'      :
      DEBUG_USER   yLOG_note    ("reset macro recording");
      yKEYS_repeat_reset ();
      rc = yMACRO_reset_all ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rc;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
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
         a_minor = myMACRO.ename;
      }
      /*---(execute)---------------------*/
      DEBUG_USER   yLOG_note    ("running stored macro");
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




