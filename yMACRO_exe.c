/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



/*
 * four execution modes...
 *
 *   blitz       runs all out, as fast as possible
 *
 *   normal      runs at configurable speed, no playback controls
 *
 *   delay       temporarily slowed down to observe, can use playback controls
 *
 *   playback    stepwise execution, must use playback controls
 *
 *
 *
 */


/*> char    g_depth  =   0;                                                           <*/
/*> char    g_stack [LEN_LABEL] = "";                                                 <*/



char yMACRO_exe_mode     (void)         { return myMACRO.emode; }

char
ymacro_exe_set             (uchar a_abbr)
{
   int         n           =   -1;
   if (a_abbr == 0)  return n;
   if (a_abbr == ',')  a_abbr = '.';
   n  = ystrlchr (S_MACRO_LIST, a_abbr, S_MACRO_MAX);
   if (n >= 0) {
      myMACRO.ename = a_abbr;
      myMACRO.ecurr = n;
   } else {
      myMACRO.ename = '-';
      myMACRO.ecurr = -1;
   }
   return n;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_exe_reset        (void)
{
   if (myMACRO.rcurr < 0)  return 0;
   ymacro_wipe (S_MACRO_LIST [myMACRO.ecurr]);
   return 0;
}

char
yMACRO_exe_pos              (char *a_name, short *a_pos)
{
   DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
   DEBUG_YMACRO   yLOG_schar   (myMACRO.ename);
   DEBUG_YMACRO   yLOG_spoint  (a_name);
   if (a_name != NULL)  *a_name = myMACRO.ename;
   DEBUG_YMACRO   yLOG_sint    (g_macros [myMACRO.ecurr].pos);
   DEBUG_YMACRO   yLOG_spoint  (a_pos);
   if (a_pos  != NULL)  *a_pos  = g_macros [myMACRO.ecurr].pos;
   DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yMACRO_exe_current          (uchar *a_abbr, short *a_len, short *a_pos, uchar *a_prev, uchar *a_curr)
{
   char        rce         =  -10;
   if (a_abbr != NULL)  *a_abbr = '-';
   if (a_len  != NULL)  *a_len  =  -1;
   if (a_pos  != NULL)  *a_pos  =  -1;
   if (a_prev != NULL)  *a_abbr = ' ';
   if (a_curr != NULL)  *a_abbr = ' ';
   --rce;  IF_MACRO_NOT_PLAYING                   return  rce;
   --rce;  if (myMACRO.ename == '-')              return rce;
   if (a_abbr != NULL)  *a_abbr = myMACRO.ename;
   if (a_len  != NULL)  *a_len  = g_macros [myMACRO.ecurr].len;
   if (a_pos  != NULL)  *a_pos  = g_macros [myMACRO.ecurr].pos;
   --rce;  if (g_macros [myMACRO.ecurr].pos < 0)  return rce;
   if (a_prev != NULL && myMACRO.epos >= 1)  *a_prev = g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].pos - 1];
   if (a_curr != NULL && myMACRO.epos >= 0)  *a_curr = g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].pos];
   return 0;
}

char
yMACRO_exe_repos            (int a_pos)
{
   g_macros [myMACRO.ecurr].pos = a_pos;
   g_macros [myMACRO.ecurr].cur = g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].pos];
   return 0;
}

char
ymacro_exe__repeater    (void)
{
   /*---(locals)-------------------------*/
   g_macros [myMACRO.ecurr].pos    =  0;
   g_macros [myMACRO.ecurr].cur    = '·';
   --(g_macros [myMACRO.ecurr].repeat);
   /*---(globals)------------------------*/
   myMACRO.epos = -1;
   DEBUG_YMACRO  yLOG_complex ("repeater"  , "%3d pos, %c cur, %3d rep, %3d  epos", g_macros [myMACRO.ecurr].pos, g_macros [myMACRO.ecurr].cur, g_macros [myMACRO.ecurr].repeat, myMACRO.epos);
   /*---(complete)-----------------------*/
   return 1;
}

char
ymacro_exe__return      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_runby     =   -1;
   /*---(save)---------------------------*/
   x_runby = g_macros [myMACRO.ecurr].runby;
   DEBUG_YMACRO  yLOG_value   ("x_runby"   , x_runby);
   /*---(locals)-------------------------*/
   g_macros [myMACRO.ecurr].pos    = -1;
   g_macros [myMACRO.ecurr].cur    = '·';
   g_macros [myMACRO.ecurr].repeat =  0;
   g_macros [myMACRO.ecurr].runby  = -1;
   /*---(globals)------------------------*/
   myMACRO.ecurr = x_runby;
   myMACRO.ename = S_MACRO_LIST [myMACRO.ecurr];
   /*> myMACRO.epos  = g_macros [myMACRO.ecurr].pos;                                  <*/
   --(g_macros [myMACRO.ecurr].pos);
   myMACRO.epos  = g_macros [myMACRO.ecurr].pos;
   /*---(check halt)---------------------*/
   if (g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].pos] == G_CHAR_HALT) {
      g_macros [myMACRO.ecurr].pos--;
   }
   /*---(update stack)---------------------*/
   --(myMACRO.edepth);
   myMACRO.estack [myMACRO.edepth] = '\0';
   DEBUG_YMACRO  yLOG_complex ("return"    , "%3d pos, %c cur, %3d rep, %3d  epos", g_macros [myMACRO.ecurr].pos, ychrvisible (g_macros [myMACRO.ecurr].cur), g_macros [myMACRO.ecurr].repeat, myMACRO.epos);
   /*---(complete)-----------------------*/
   return 1;
}

char
ymacro_exe__done        (void)
{
   /*---(clear mode)-----*/
   ymacro_set2stop ();
   /*---(locals)---------*/
   g_macros [myMACRO.ecurr].runby  = -1;
   /*---(globals)--------*/
   /*> myMACRO.ename      = '-';                                                      <*/
   myMACRO.blitz      = '-';
   myMACRO.blitzing   = '-';
   /*---(reset stack)----*/
   myMACRO.estack [0] = '\0';
   myMACRO.edepth     = 0;
   /*---(complete)-----------------------*/
   return 1;
}

/*> char                                                                              <* 
 *> ymacro_exe__script      (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rc          =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);                                    <* 
 *>    /+---(clear mode)-----+/                                                       <* 
 *>    ymacro_set2stop ();                                                            <* 
 *>    /+---(check next)-----+/                                                       <* 
 *>    rc = ymacro_script__read ();                                                   <* 
 *>    if (rc < 0) {                                                                  <* 
 *>       DEBUG_YMACRO   yLOG_note    ("full script complete");                       <* 
 *>       ymacro_exe__done ();                                                        <* 
 *>    } else {                                                                       <* 
 *>       DEBUG_YMACRO   yLOG_note    ("script line complete");                       <* 
 *>       myMACRO.estack [0] = '\0';                                                  <* 
 *>       myMACRO.edepth     = 0;                                                     <* 
 *>    }                                                                              <* 
 *>    DEBUG_YMACRO   yLOG_char    ("myMACRO.blitz"   , myMACRO.blitz);               <* 
 *>    DEBUG_YMACRO   yLOG_char    ("myMACRO.blitzing", myMACRO.blitzing);            <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);                                    <* 
 *>    return 1;                                                                      <* 
 *> }                                                                                 <*/

char
ymacro_exe_done         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_agrios    =  '-';
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(decision makers)----------------*/
   DEBUG_YMACRO   yLOG_char    ("ename"     , myMACRO.ename);
   DEBUG_YMACRO   yLOG_value   ("ecurr"     , myMACRO.ecurr);
   DEBUG_YMACRO   yLOG_value   ("repeat"    , g_macros [myMACRO.ecurr].repeat);
   DEBUG_YMACRO   yLOG_value   ("g_level"   , myMACRO.g_level);
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
   /*---(check agrios)-----------*/
   if (myMACRO.ename == ' ') {
      rc = ymacro_agrios_next ();
      if (rc > 0) {
         DEBUG_YMACRO   yLOG_note    ("continuing agrios");
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return G_KEY_NOOP;
      }
      DEBUG_YMACRO   yLOG_note    ("agrios complete");
      x_agrios = 'y';
   }
   /*---(repeat)-------------------------*/
   if (g_macros [myMACRO.ecurr].repeat > 0) {
      DEBUG_YMACRO   yLOG_note    ("repeats left, so restart");
      ymacro_exe__repeater ();
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return 1;
      /*---(done)-----------*/
   }
   /*---(return to higher level)---------*/
   if (g_macros [myMACRO.ecurr].runby >= 0) {
      DEBUG_YMACRO   yLOG_note    ("return to caller/runby");
      DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
      ymacro_exe__return   ();
      DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
      DEBUG_YMACRO   yLOG_value   ("pos"       , g_macros [myMACRO.ecurr].pos);
      if (x_agrios != 'y' && g_macros [myMACRO.ecurr].pos >= 0) {
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return G_KEY_NOOP;
      }
      /*---(done)-----------*/
   }
   /*---(check script)-----------*/
   DEBUG_YMACRO   yLOG_char    ("ename"     , myMACRO.ename);
   DEBUG_YMACRO   yLOG_value   ("ename"     , myMACRO.ename);
   /*---(check script)-----------*/
   if (myMACRO.ename == '.') {
      DEBUG_YMACRO   yLOG_note    ("check script for next");
      rc = ymacro_script_next   ();
      DEBUG_YMACRO   yLOG_value   ("__script"  , rc);
      if (rc < 0) {
         DEBUG_YMACRO   yLOG_note    ("script is fully done");
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      DEBUG_YMACRO   yLOG_note    ("script advanced to next line");
   }
   /*---(really done)--------------------*/
   else {
      DEBUG_YMACRO   yLOG_note    ("macro really complete");
      ymacro_exe__done     ();
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return G_KEY_NOOP;
      /*---(done)-----------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return G_KEY_NOOP;
}

char         /*-> prepare a macro execution ----------[ ------ [ge.832.122.52]*/ /*-[01.0000.112.5]-*/ /*-[--.---.---.--]-*/
ymacro_exe_beg          (uchar a_name, uchar a_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =   -1;
   int         x_curr      =   -1;
   uchar       x_name      =  '-';
   uchar       x_style     =  '-';
   uchar       x_lower     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_char    ("a_name"    , a_name);
   DEBUG_YMACRO   yLOG_value   ("erepeat"   , myMACRO.erepeat);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_YMACRO   yLOG_note    ("can not execute until operational");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check macro name)------------*/
   DEBUG_YMACRO   yLOG_char    ("ename"     , myMACRO.ecurr);
   x_curr  = myMACRO.ecurr;
   DEBUG_YMACRO   yLOG_char    ("x_curr"    , x_curr);
   DEBUG_YMACRO   yLOG_char    ("ename"     , myMACRO.ename);
   --rce;  if (a_name == 0) {
      DEBUG_YMACRO   yLOG_note    ("macro name can not be null");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check macro name)------------*/
   if (strchr (YSTR_CHARS, a_name) != NULL)  x_lower = tolower (a_name);
   else                                      x_lower = a_name;
   DEBUG_YMACRO   yLOG_char    ("x_lower"   , x_lower);
   n = ymacro_index  (x_lower);
   DEBUG_YMACRO   yLOG_value   ("n"         , n);
   if (n <  0)  {
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for empty)-------------*/
   DEBUG_YMACRO   yLOG_value   ("len"       , g_macros [n].len);
   --rce;  if (g_macros [n].len <= 0) {
      DEBUG_YMACRO   yLOG_note    ("macro is empty/null");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for illegal)-----------*/
   DEBUG_YMACRO   yLOG_value   ("rcurr"     , myMACRO.rcurr);
   --rce;  if (n == myMACRO.rcurr) {
      DEBUG_YMACRO   yLOG_note    ("this macro is currently recording");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_note    ("this macro verified as not currently recording");
   DEBUG_YMACRO   yLOG_value   ("ecurr"   , myMACRO.ecurr);
   --rce;  if (n == myMACRO.ecurr) {
      DEBUG_YMACRO   yLOG_note    ("this macro is currently executing");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_note    ("this macro verified as not currently executing");
   DEBUG_YMACRO   yLOG_value   ("pos"       , g_macros [n].pos);
   --rce;  if (g_macros [n].pos >= 0) {
      DEBUG_YMACRO   yLOG_note    ("this macro is active");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_note    ("this macro verified as not executing anywhere");
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [n].runby);
   --rce;  if (g_macros [n].runby >= 0) {
      DEBUG_YMACRO   yLOG_note    ("this macro is running higher");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_note    ("this macro verified as not executing higher up");
   /*---(set as current)--------------*/
   rc = ymacro_exe_set (x_lower);
   DEBUG_YMACRO   yLOG_value   ("exe_set"   , rc);
   --rce;  if (rc <  0)  {
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(execution style)-------------*/
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   IF_MACRO_OFF {
      /*---(handle agrios/script)-----*/
      if (strchr (" .", a_name) != NULL) {
         switch (a_style) {
         case ',' :
            DEBUG_YMACRO   yLOG_note    ("set script/agrios to playback");
            SET_MACRO_PLAYBACK;
            break;
         default  :
            if (myMACRO.ddelay != MACRO_BLITZ) {
               DEBUG_YMACRO   yLOG_note    ("set script/agrios to delay");
               SET_MACRO_DELAY;
            } else {
               DEBUG_YMACRO   yLOG_note    ("set script/agrios to run");
               SET_MACRO_RUN;
            }
            break;
         }
      }
      /*---(normal macros)------------*/
      else if (a_name == x_lower && a_name != ',') {
         if (myMACRO.ddelay != MACRO_BLITZ) {
            DEBUG_YMACRO   yLOG_note    ("set macro to delay execution");
            SET_MACRO_DELAY;
         } else {
            DEBUG_YMACRO   yLOG_note    ("set macro to run/normal execution");
            SET_MACRO_RUN;
         }
      }
      /*---(debugging/playback)-------*/
      else {
         DEBUG_YMACRO   yLOG_note    ("set macro to playback execution");
         SET_MACRO_PLAYBACK;
      }
   }
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   /*---(update stack)----------------*/
   if (myMACRO.edepth <= 0 || (uchar) myMACRO.estack [myMACRO.edepth - 1] != (uchar) x_lower) {
      myMACRO.estack [myMACRO.edepth] = x_lower;
      ++myMACRO.edepth;
      myMACRO.estack [myMACRO.edepth] = '\0';
   }
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   /*---(get macro)-------------------*/
   ymacro_fetch ();
   /*---(update settings)-------------*/
   myMACRO.epos   = -1;
   myMACRO.pauses =  0;
   myMACRO.cskip  =  0;
   ymacro_exe_reset ();
   if (strchr (" .,", a_name) == NULL)  ymacro_exe_adv (0);
   /*> else {                                                                         <* 
    *>    IF_MACRO_PLAYBACK  ymacro_exe_adv (0);                                      <* 
    *> }                                                                              <*/
   g_macros [myMACRO.ecurr].runby  = x_curr;
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
   DEBUG_YMACRO   yLOG_char    ("ename"     , myMACRO.ename);
   DEBUG_YMACRO   yLOG_value   ("erepeat"   , myMACRO.erepeat);
   yMACRO_zero  ();
   g_macros [myMACRO.ecurr].repeat = myMACRO.erepeat;
   DEBUG_YMACRO   yLOG_value   ("repeat"    , g_macros [myMACRO.ecurr].repeat);
   myMACRO.erepeat = 0;  /* reset */
   /*---(reset main delay)---------------*/
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitz"   , myMACRO.blitz);
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitzing", myMACRO.blitzing);
   if (myMACRO.blitz == 'y')   ymacro_set2blitz ();
   else {
      IF_MACRO_RUN             ymacro_set2run   ();
      else IF_MACRO_PLAYBACK   ymacro_set2play  ();
      else                     ymacro_set2delay ();
   }
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_exe_skips        (void)
{
   ++myMACRO.cskip;
   DEBUG_YMACRO   yLOG_sint    (myMACRO.cskip);
   DEBUG_YMACRO   yLOG_sint    (myMACRO.nskip);
   if (myMACRO.cskip < myMACRO.nskip) {
      DEBUG_YMACRO   yLOG_snote   ("no position update due yet");
      return -1;
   }
   myMACRO.cskip = 0;
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gc.220.002.20]*/ /*-[00.0000.102.7]-*/ /*-[--.---.---.--]-*/
ymacro_exe_adv          (uchar a_play)
{
   char        rc          =   -1;
   uchar       x_ch        =    0;
   /*---(header)-------------------------*/
   IF_MACRO_OFF   return 0;
   DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
   DEBUG_YMACRO   yLOG_sint    (a_play);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_sint    (myMACRO.ecurr);
   if (myMACRO.ecurr < 0) {
      DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_YMACRO   yLOG_schar   (S_MACRO_LIST [myMACRO.ecurr]);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_schar   (myMACRO.emode);
   switch (myMACRO.emode) {
   case MACRO_STOP     :
      DEBUG_YMACRO   yLOG_snote   ("stopped, get out");
      DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
      return 0;
      break;
   case MACRO_DELAY    :
      DEBUG_YMACRO   yLOG_snote   ("delay mode");
      if (ymacro_exe_skips () < 0) {
         DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      break;
   case MACRO_PLAYBACK :
      DEBUG_YMACRO   yLOG_snote   ("playback mode");
      DEBUG_YMACRO   yLOG_sint    (g_macros [myMACRO.ecurr].pos);
      x_ch = g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].pos];
      DEBUG_YMACRO   yLOG_schar   (x_ch);
      if (a_play != 0) {
         DEBUG_YMACRO   yLOG_snote   ("play character, no position update requested");
         DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      break;
   case MACRO_RUN      :
      if (ymacro_exe_skips () < 0) {
         DEBUG_YMACRO   yLOG_snote   ("normal mode, in a skip cycle");
         DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      DEBUG_YMACRO   yLOG_snote   ("normal run mode");
      break;
   }
   /*---(next key)-----------------------*/
   if (yKEYS_repeating ()) {
      DEBUG_YMACRO   yLOG_snote   ("older keys");
      g_macros [myMACRO.ecurr].cur = yKEYS_current ();
      yKEYS_repos (yKEYS_position + 1);
   } else if (myMACRO.pauses > 0) {
      DEBUG_YMACRO   yLOG_snote   ("pausing");
      DEBUG_YMACRO   yLOG_sint    (g_macros [myMACRO.ecurr].pos);
      --myMACRO.pauses;
   } else {
      DEBUG_YMACRO   yLOG_snote   ("new keystroke");
      ++g_macros [myMACRO.ecurr].pos;
      if (g_macros [myMACRO.ecurr].pos < 0)  g_macros [myMACRO.ecurr].cur = 0;
      else                             g_macros [myMACRO.ecurr].cur = g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].pos];
      DEBUG_YMACRO   yLOG_sint    (g_macros [myMACRO.ecurr].pos);
   }
   DEBUG_YMACRO   yLOG_schar   (g_macros [myMACRO.ecurr].cur);
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> return current key in macro --------[ ------ [ge.A63.034.52]*/ /*-[02.0000.102.8]-*/ /*-[--.---.---.--]-*/
ymacro_exe_key          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_uch       =  ' ';
   int         x_runby     =   -1;
   static int  x_pause     =    0;
   char        x_last      =  '-';
   /*---(header)-------------------------*/
   IF_MACRO_OFF   return 0;
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YMACRO   yLOG_value   ("ecurr"     , myMACRO.ecurr);
   DEBUG_YMACRO   yLOG_char    ("abbr"      , S_MACRO_LIST [myMACRO.ecurr]);
   DEBUG_YMACRO   yLOG_value   ("pos"       , g_macros [myMACRO.ecurr].pos);
   /*---(handle playback/delay)----------*/
   DEBUG_YMACRO   yLOG_value   ("epos"      , myMACRO.epos);
   if (g_macros [myMACRO.ecurr].pos == myMACRO.epos) {
      DEBUG_YMACRO   yLOG_note    ("return a no-action (NOOP)");
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return G_KEY_NOOP;  /* return a no-action */
   }
   /*---(handle end of macro)------------*/
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
   DEBUG_YMACRO   yLOG_value   ("repeat"    , g_macros [myMACRO.ecurr].repeat);
   --rce;  if (g_macros [myMACRO.ecurr].pos >= g_macros [myMACRO.ecurr].len - 1) {
      rc = ymacro_exe_done ();
      if (rc == 0) {
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return G_KEY_NOOP;
      }
   }
   /*---(get next key)-------------------*/
   x_uch = g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].pos];
   DEBUG_YMACRO   yLOG_value   ("x_uch"     , x_uch);
   /*---(check key)----------------------*/
   if (x_uch == G_CHAR_SPACE) {
      /*> if (yMODE_curr () == UMOD_INPUT) {                                          <* 
       *>    DEBUG_YMACRO   yLOG_note    ("found a spacer (·) in input mode");        <* 
       *>    DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);                              <* 
       *>    return G_KEY_SPACE;                                                      <* 
       *> }                                                                           <*/
      if (yMODE_curr () == UMOD_SENDKEYS) {
         DEBUG_YMACRO   yLOG_note    ("found a spacer (·) in sendkeys mode");
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return G_KEY_NOOP;
      }
      IF_MACRO_RUN {
         DEBUG_YMACRO   yLOG_note    ("found a spacer (·) in macro run mode");
         myMACRO.cskip = myMACRO.nskip;
         ++myMACRO.epos;
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return G_KEY_SKIP;
      } else {
         DEBUG_YMACRO   yLOG_note    ("found a spacer (·) in macro playback/debug mode");
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return G_KEY_NOOP;
      }
   }
   /*---(translate)----------------------*/
   x_uch = chrworking (x_uch);
   DEBUG_YMACRO   yLOG_char    ("x_uch"     , x_uch);
   /*---(handle controls)-------------*/
   if (x_uch < 0 || x_uch > 127) {
      x_uch = ymacro_exe_control (x_uch);
   }
   /*---(next)------------------------*/
   myMACRO.epos = g_macros [myMACRO.ecurr].pos;   /* x_pos is static, so this is key */
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return x_uch;
}

char         /*-> tbd --------------------------------[ ------ [gc.340.102.21]*/ /*-[00.0000.013.!]-*/ /*-[--.---.---.--]-*/
ymacro_exe_control      (uchar a_key)
{
   float       x_delay     =  0.0;
   float       x_update    =  0.0;
   char        s           [LEN_TERSE] = "";
   char        t           [LEN_TERSE] = "";
   if (a_key >= 0 && a_key <= 127)  return 0;
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_value   ("a_key"     , a_key);
   switch (a_key) {
   case G_CHAR_SLBRACK :
      DEBUG_YMACRO   yLOG_note    ("blitz (º)");
      IF_MACRO_RUN {
         ymacro_set2blitz ();
         myMACRO.blitzing = 'y';
      }
      else  DEBUG_YMACRO   yLOG_note    ("blitzing not active in debug/playback");
      a_key = G_KEY_SKIP;
      break;
   case  G_CHAR_SRBRACK :
      DEBUG_YMACRO   yLOG_note    ("unblitz (»)");
      IF_MACRO_RUN {
         if (myMACRO.blitz != 'y') {
            myMACRO.blitzing = '-';
            ymacro_set2run   ();
         }
      }
      else  DEBUG_YMACRO   yLOG_note    ("blitzing not active in debug/playback");
      a_key = G_KEY_SKIP;
      break;
   case  G_CHAR_BIGDOT  :
      DEBUG_YMACRO   yLOG_note    ("wait one tick/beat (´)");
      /*> if (yMODE_curr () != UMOD_INPUT)  a_key = G_KEY_NOOP;                       <*/
      if (yMODE_curr () != UMOD_INPUT)  a_key = G_KEY_NOOP;
      break;
   case G_CHAR_HUGEDOT :
      if (myMACRO.ddelay == MACRO_BLITZ) {
         DEBUG_YMACRO   yLOG_note    ("wait five tick/beat (Ï), ignored in BLITZ");
      } else IF_MACRO_RUN {
         DEBUG_YMACRO   yLOG_note    ("wait five tick/beat (Ï), pause only in run");
         myMACRO.pauses =  4;
      } else {
         DEBUG_YMACRO   yLOG_note    ("wait five tick/beat (Ï), becomes one beat in playback/debug");
         myMACRO.pauses =  0;
      }
      /*> a_key = G_KEY_NOOP;                                                         <*/
      a_key = G_KEY_NOOP;
      break;
   case G_CHAR_WAIT    :
      DEBUG_YMACRO   yLOG_note    ("wait («)");
      /*> DEBUG_YMACRO   yLOG_double  ("delay"     , myVIKEYS.delay);                   <*/
      DEBUG_YMACRO   yLOG_value   ("skip"      , myMACRO.nskip);
      yKEYS_loop_get (&x_delay, s, &x_update, t);
      DEBUG_YMACRO   yLOG_double  ("x_delay"   , x_delay);
      DEBUG_YMACRO   yLOG_info    ("s"         , s);
      DEBUG_YMACRO   yLOG_double  ("x_update"  , x_update);
      DEBUG_YMACRO   yLOG_info    ("t"         , t);
      if (myMACRO.ddelay == MACRO_BLITZ) {
         DEBUG_YMACRO   yLOG_note    ("wait five tick/beat (Ï), ignored in BLITZ");
      } IF_MACRO_NOT_RUN {
         DEBUG_YMACRO   yLOG_note    ("pauses not useful in debug/playback");
         myMACRO.pauses =  0;
      } else if (x_delay >= 0.500) {
         DEBUG_YMACRO   yLOG_note    ("running too slow, pauses not required");
         myMACRO.pauses =  0;
      } else if (x_delay < 0.009) {
         DEBUG_YMACRO   yLOG_note    ("running too fast, pauses are proportional");
         myMACRO.pauses = 19;       /* for total of 20 loops in main */
      } else {
         DEBUG_YMACRO   yLOG_note    ("sweet spot, pauses are exactly 0.5s");
         DEBUG_YMACRO   yLOG_double  ("calc"      , 0.5 / x_delay);
         DEBUG_YMACRO   yLOG_value   ("trunc"     , trunc (0.5 / x_delay));
         myMACRO.pauses = trunc (0.5 / x_delay) - 1;
         /*> myMACRO.pauses = 50;                                                     <*/
      }
      DEBUG_YMACRO   yLOG_value   ("myMACRO.pauses"   , myMACRO.pauses);
      a_key = G_KEY_NOOP;
      break;
   case G_CHAR_BREAK   :
      DEBUG_YMACRO   yLOG_note    ("break (ª)");
      ymacro_set2play ();
      ymacro_agrios_style (',');
      a_key = G_KEY_NOOP;
      break;
   case G_CHAR_DISPLAY :
      DEBUG_YMACRO   yLOG_note    ("display (©)");
      a_key = G_KEY_NOOP;
      break;
   case G_CHAR_SPACE   :
      DEBUG_YMACRO   yLOG_note    ("macro spacer (·), fast skip only in run");
      IF_MACRO_RUN  a_key = G_KEY_SKIP;
      else          a_key = G_KEY_NOOP;
      break;
   case G_CHAR_HALT    :
      DEBUG_YMACRO   yLOG_note    ("halt (³)");
      ymacro_set2stop ();
      ymacro_script__close ();
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return -1;
      break;
   default             :
      DEBUG_YMACRO   yLOG_note    ("other key, pass through");
      break;
   }
   DEBUG_YMACRO   yLOG_value   ("a_key"     , a_key);
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return a_key;
}

char         /*-> tbd --------------------------------[ ------ [gc.A43.108.12]*/ /*-[02.0000.102.!]-*/ /*-[--.---.---.--]-*/
ymacro_exe_play         (uchar a_key)
{
   char        rc          =    1;
   IF_MACRO_OFF   return 0;
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_char    ("a_key"     , a_key);
   DEBUG_YMACRO   yLOG_value   ("a_key"     , a_key);
   switch (a_key) {
   case '0' : case '1' : case '2' : case '3' : case '4' :
   case '5' : case '6' : case '7' : case '8' : case '9' :
   case '-'      : case '+'      :
      DEBUG_YMACRO   yLOG_note    ("reqested change to delay");
      yMACRO_ddelay (a_key);
      break;
   case 'n' : case 's' : case 'b' : case 'p' : case 'd' :
      DEBUG_YMACRO   yLOG_note    ("reqested change to update");
      myMACRO.dupdate = a_key;
      break;
   case ',' :
      DEBUG_YMACRO   yLOG_note    ("reqested delay mode");
      ymacro_set2delay ();
      break;
   case '.' :
      DEBUG_YMACRO   yLOG_note    ("reqested playback mode");
      ymacro_set2play ();
      break;
   case G_KEY_ESCAPE : case G_CHAR_ESCAPE :
      DEBUG_YMACRO   yLOG_note    ("reqested termination with escape");
      ymacro_set2stop ();
      ymacro_script__close ();
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return -1;
      break;
   case G_KEY_RETURN : case G_KEY_ENTER  : case G_CHAR_RETURN :
      DEBUG_YMACRO   yLOG_note    ("reqested normal run with return");
      ymacro_set2run   ();
      break;
   case G_KEY_SPACE  : case G_CHAR_SPACE :
      DEBUG_YMACRO   yLOG_note    ("requested step macro forward");
      rc = 0;
      break;
   default  :
      DEBUG_YMACRO   yLOG_note    ("unknown playback key");
      break;
   }
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return rc;
}

uchar
yMACRO_exec             (uchar a_play)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_key       =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(playback)-----------------------*/
   DEBUG_YMACRO   yLOG_note    ("handle playback control");
   DEBUG_YMACRO   yLOG_value   ("a_play"    , a_play);
   --rce;  IF_MACRO_MOVING {
      if (a_play == G_KEY_ESCAPE || a_play ==  G_CHAR_ESCAPE) {
         DEBUG_YMACRO   yLOG_note    ("reqested termination with escape");
         ymacro_set2stop ();
         ymacro_script__close ();
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else IF_MACRO_PLAYBACK {
      a_play = ymacro_exe_play (a_play);
      DEBUG_YMACRO   yLOG_value   ("play"      , rc);
      if (rc < 0) {
         DEBUG_YMACRO   yLOG_note    ("terminated, do not execute next key");
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      if (rc > 0) {
         DEBUG_YMACRO   yLOG_note    ("playback key, no impact on macro");
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(not-repeating)------------------*/
   DEBUG_YMACRO   yLOG_note    ("macro running, delay, or playback");
   x_key = (uchar) ymacro_exe_key ();
   DEBUG_YMACRO   yLOG_value   ("x_key"     , x_key);
   IF_MACRO_OFF {
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return x_key;
   }
   /*---(advance)------------------------*/
   DEBUG_YMACRO   yLOG_note    ("advance");
   ymacro_exe_adv (0);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return x_key;
}




