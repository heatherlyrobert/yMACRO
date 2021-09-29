/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



char    g_depth  =   0;
char    g_stack [LEN_LABEL] = "";



char yMACRO_exe_mode     (void)         { return g_emode; }

char
ymacro_exe_set             (uchar a_abbr)
{
   int         n           =   -1;
   if (a_abbr == 0)  return n;
   if (a_abbr == ',')  a_abbr = '.';
   n  = strlchr (S_MACRO_LIST, a_abbr, S_MACRO_MAX);
   if (n >= 0) {
      g_ename = a_abbr;
      g_ecurr = n;
   } else {
      g_ename = '-';
      g_ecurr = -1;
   }
   return n;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_exe_reset        (void)
{
   if (g_rcurr < 0)  return 0;
   ymacro_wipe (S_MACRO_LIST [g_ecurr]);
   return 0;
}

char
yMACRO_exe_pos              (char *a_name, int *a_pos)
{
   *a_name = g_ename;
   *a_pos  = g_macros [g_ecurr].pos;
   return 0;
}

char
yMACRO_exe_repos            (int a_pos)
{
   g_macros [g_ecurr].pos = a_pos;
   g_macros [g_ecurr].cur = g_macros [g_ecurr].keys [g_macros [g_ecurr].pos];
   return 0;
}

char         /*-> prepare a macro execution ----------[ ------ [ge.832.122.52]*/ /*-[01.0000.112.5]-*/ /*-[--.---.---.--]-*/
ymacro_exe_beg          (char a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   int         x_curr      =   -1;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_SCRP   yLOG_note    ("can not execute until operational");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check macro name)------------*/
   x_curr  = g_ecurr;
   /*---(check macro name)------------*/
   DEBUG_SCRP   yLOG_char    ("a_name"    , a_name);
   n = ymacro_index  (tolower (a_name));
   DEBUG_SCRP   yLOG_value   ("n"         , n);
   if (n <  0)  {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for illegal)-----------*/
   DEBUG_SCRP   yLOG_value   ("g_rcurr"   , g_rcurr);
   --rce;  if (n == g_rcurr) {
      DEBUG_SCRP   yLOG_note    ("currently recording");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_value   ("g_ecurr"   , g_ecurr);
   --rce;  if (n == g_ecurr) {
      DEBUG_SCRP   yLOG_note    ("currently executing");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_value   ("pos"       , g_macros [n].pos);
   --rce;  if (g_macros [n].pos >= 0) {
      DEBUG_SCRP   yLOG_note    ("macro is active");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_value   ("runby"     , g_macros [n].runby);
   --rce;  if (g_macros [n].runby >= 0) {
      DEBUG_SCRP   yLOG_note    ("macro is running higher");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set as current)--------------*/
   DEBUG_SCRP   yLOG_char    ("a_name"    , a_name);
   --rce;  if (ymacro_exe_set   (tolower (a_name)) <  0)  {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(execution style)-------------*/
   IF_MACRO_OFF {
      /*---(reset stack)--------------*/
      g_stack [0] = '\0';
      g_depth     = 0;
      /*---(normal)-------------------*/
      if (a_name == tolower (a_name) && a_name != ',') {
         DEBUG_SCRP   yLOG_note    ("normal execution");
         if (g_ddelay    != '0'      )  SET_MACRO_DELAY;
         IF_MACRO_OFF                   SET_MACRO_RUN;
      }
      /*---(debugging/playback)-------*/
      else {
         DEBUG_SCRP   yLOG_note    ("debug/playback execution");
         SET_MACRO_PLAYBACK;
      }
   }
   /*---(update stack)----------------*/
   g_stack [g_depth] = tolower (a_name);
   ++g_depth;
   g_stack [g_depth] = '\0';
   /*---(macro name)------------------*/
   DEBUG_SCRP   yLOG_char    ("macro_name", g_ename);
   /*---(get macro)-------------------*/
   ymacro_fetch ();
   /*---(update settings)-------------*/
   g_epos  = -1;
   g_pause =  0;
   s_skips =  0;
   ymacro_exe_reset ();
   if (strchr (".,", a_name) == NULL)  ymacro_exe_adv (0);
   g_macros [g_ecurr].runby  = x_curr;
   g_macros [g_ecurr].repeat = yKEYS_repeats ();
   yKEYS_repeat_reset ();
   yMACRO_zero  ();
   DEBUG_USER   yLOG_value   ("repeat"    , g_macros [g_ecurr].repeat);
   /*---(reset main delay)---------------*/
   DEBUG_SCRP   yLOG_char    ("g_blitz"   , g_blitz);
   DEBUG_SCRP   yLOG_char    ("g_blitzing", g_blitzing);
   if (g_blitz == 'y')         ymacro_set2blitz ();
   else {
      IF_MACRO_RUN             ymacro_set2run   ();
      else IF_MACRO_PLAYBACK   ymacro_set2play  ();
      else                     ymacro_set2delay ();
   }
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_exe_skips        (void)
{
   ++s_skips;
   DEBUG_SCRP   yLOG_sint    (s_skips);
   /*> DEBUG_SCRP   yLOG_sint    (myVIKEYS.macro_skip);                               <*/
   /*> if (s_skips < myVIKEYS.macro_skip) {                                           <* 
    *>    DEBUG_SCRP   yLOG_snote   ("no position update due yet");                   <* 
    *>    return -1;                                                                  <* 
    *> }                                                                              <*/
   s_skips = 0;
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gc.220.002.20]*/ /*-[00.0000.102.7]-*/ /*-[--.---.---.--]-*/
ymacro_exe_adv          (uchar a_play)
{
   char        rc          =   -1;
   uchar       x_ch        =    0;
   /*---(header)-------------------------*/
   IF_MACRO_OFF   return 0;
   DEBUG_SCRP   yLOG_senter  (__FUNCTION__);
   DEBUG_SCRP   yLOG_sint    (a_play);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_sint    (g_ecurr);
   if (g_ecurr < 0) {
      DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_SCRP   yLOG_schar   (S_MACRO_LIST [g_ecurr]);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_schar   (g_emode);
   switch (g_emode) {
   case MACRO_STOP     :
      DEBUG_SCRP   yLOG_snote   ("stopped, get out");
      DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
      return 0;
      break;
   case MACRO_DELAY    :
      DEBUG_SCRP   yLOG_snote   ("delay mode");
      if (ymacro_exe_skips () < 0) {
         DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      break;
   case MACRO_PLAYBACK :
      DEBUG_SCRP   yLOG_snote   ("playback mode");
      x_ch = g_macros [g_ecurr].keys [g_macros [g_ecurr].pos];
      DEBUG_SCRP   yLOG_schar   (x_ch);
      if (a_play != 0) {
         DEBUG_SCRP   yLOG_snote   ("play character, no position update requested");
         DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      break;
   case MACRO_RUN      :
      if (ymacro_exe_skips () < 0) {
         DEBUG_SCRP   yLOG_snote   ("normal mode, in a skip cycle");
         DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      DEBUG_SCRP   yLOG_snote   ("normal run mode");
      break;
   }
   /*---(next key)-----------------------*/
   if (yKEYS_repeating ()) {
      DEBUG_LOOP   yLOG_snote   ("older keys");
      g_macros [g_ecurr].cur = yKEYS_current ();
      yKEYS_repos (yKEYS_position + 1);
   } else if (g_pause > 0) {
      DEBUG_LOOP   yLOG_snote   ("pausing");
      DEBUG_SCRP   yLOG_sint    (g_macros [g_ecurr].pos);
      --g_pause;
   } else {
      DEBUG_LOOP   yLOG_snote   ("new keystroke");
      ++g_macros [g_ecurr].pos;
      if (g_macros [g_ecurr].pos < 0)  g_macros [g_ecurr].cur = 0;
      else                             g_macros [g_ecurr].cur = g_macros [g_ecurr].keys [g_macros [g_ecurr].pos];
      DEBUG_SCRP   yLOG_sint    (g_macros [g_ecurr].pos);
   }
   DEBUG_SCRP   yLOG_schar   (g_macros [g_ecurr].cur);
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_SCRP   yLOG_value   ("g_ecurr"   , g_ecurr);
   DEBUG_SCRP   yLOG_char    ("abbr"      , S_MACRO_LIST [g_ecurr]);
   DEBUG_SCRP   yLOG_value   ("pos"       , g_macros [g_ecurr].pos);
   /*---(handle playback/delay)----------*/
   DEBUG_SCRP   yLOG_value   ("g_epos"    , g_epos);
   if (g_macros [g_ecurr].pos == g_epos) {
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return G_KEY_NOOP;  /* return a no-action */
   }
   /*---(handle end of macro)------------*/
   DEBUG_SCRP   yLOG_value   ("runby"     , g_macros [g_ecurr].runby);
   DEBUG_SCRP   yLOG_value   ("repeat"    , g_macros [g_ecurr].repeat);
   --rce;  if (g_macros [g_ecurr].pos >= g_macros [g_ecurr].len - 1) {
      /*---(restart)------------------------*/
      if (g_macros [g_ecurr].repeat > 0) {
         DEBUG_SCRP   yLOG_note    ("repeats left, so restart");
         g_macros [g_ecurr].pos    =  0;
         g_epos = -1;
         g_macros [g_ecurr].cur    = '·';
         --g_macros [g_ecurr].repeat;
      }
      /*---(pop)----------------------------*/
      else if (g_macros [g_ecurr].runby >= 0) {
         DEBUG_SCRP   yLOG_note    ("return to caller/runby");
         /*---(reset current)----*/
         g_macros [g_ecurr].pos    = -1;
         g_epos = -1;
         g_macros [g_ecurr].cur    = '·';
         g_macros [g_ecurr].repeat =  0;
         /*---(update runby)-----*/
         x_runby = g_macros [g_ecurr].runby;
         g_macros [g_ecurr].runby  = -1;
         /*---(back to prev)-----*/
         g_ecurr = x_runby;
         g_ename = S_MACRO_LIST [g_ecurr];
         if (g_macros [g_ecurr].keys [g_macros [g_ecurr].pos] == G_CHAR_HALT) {
            g_macros [g_ecurr].pos--;
         }
         /*---(update stack)-----*/
         --g_depth;
         g_stack [g_depth] = '\0';
         /*---(output)-----------*/
         DEBUG_SCRP   yLOG_value   ("g_ecurr"    , g_ecurr);
         DEBUG_SCRP   yLOG_char    ("abbr"      , S_MACRO_LIST [g_ecurr]);
         DEBUG_SCRP   yLOG_value   ("pos"       , g_macros [g_ecurr].pos);
         DEBUG_SCRP   yLOG_value   ("runby"     , g_macros [g_ecurr].runby);
         DEBUG_SCRP   yLOG_value   ("repeat"    , g_macros [g_ecurr].repeat);
      }
      /*---(reset)--------------------------*/
      else {
         DEBUG_SCRP   yLOG_note    ("macro complete");
         /*---(check script)-----------*/
         x_last = g_ename;
         DEBUG_SCRP   yLOG_char    ("x_last"     , x_last);
         ymacro_set2stop ();
         if (x_last == '.')  {
            /*> rc = yvikeys_script_read ();                                          <*/
            if (rc < 0)  g_blitz = '-';
         } else g_blitz = '-';
         DEBUG_SCRP   yLOG_char    ("g_blitz"   , g_blitz);
         DEBUG_SCRP   yLOG_char    ("g_blitzing", g_blitzing);
         /*> g_macros [g_ecurr].pos    = -1;                                          <* 
          *> g_macros [g_ecurr].cur    = '·';                                         <* 
          *> g_macros [g_ecurr].repeat =  0;                                          <*/
         /*---(reset stack)--------------*/
         g_stack [0] = '\0';
         g_depth     = 0;
         /*---(done)---------------------*/
         DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
         return G_KEY_NOOP;
      }
   }
   /*---(get next key)-------------------*/
   x_uch = g_macros [g_ecurr].keys [g_macros [g_ecurr].pos];
   DEBUG_SCRP   yLOG_value   ("x_uch"     , x_uch);
   /*---(check key)----------------------*/
   if (x_uch == G_CHAR_SPACE) {
      if (/* yVIKEYS_mode () */ 1 == UMOD_INPUT) {
         DEBUG_SCRP   yLOG_note    ("found a spacer (·) in input mode");
         DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
         return G_KEY_SPACE;
      }
      else if (/* yVIKEYS_mode () */ 1 == UMOD_SENDKEYS) {
         DEBUG_SCRP   yLOG_note    ("found a spacer (·) in sendkeys mode");
         DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
         /*> return G_CHAR_STORAGE;                                                   <*/
         return G_KEY_NOOP;
      }
      IF_MACRO_RUN {
         DEBUG_SCRP   yLOG_note    ("found a spacer (·) in macro run mode");
         /*> s_skips = myVIKEYS.macro_skip;                                           <*/
         ++g_epos;
         DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
         return G_KEY_ACK;
      } else {
         DEBUG_SCRP   yLOG_note    ("found a spacer (·) in macro playback/debug mode");
         DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
         return G_KEY_NOOP;
      }
   }
   /*---(translate)----------------------*/
   x_uch = chrworking (x_uch);
   DEBUG_SCRP   yLOG_char    ("x_uch"     , x_uch);
   /*---(handle controls)-------------*/
   if (x_uch < 0 || x_uch > 127) {
      /*> x_uch = yvikeys_macro__exectl (x_uch);                                      <*/
   }
   /*---(next)------------------------*/
   g_epos = g_macros [g_ecurr].pos;   /* x_pos is static, so this is key */
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return x_uch;
}

char         /*-> tbd --------------------------------[ ------ [gc.A43.108.12]*/ /*-[02.0000.102.!]-*/ /*-[--.---.---.--]-*/
ymacro_exe_play         (uchar a_key)
{
   char        rc          =    1;
   IF_MACRO_OFF   return 0;
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   DEBUG_SCRP   yLOG_char    ("a_key"     , a_key);
   DEBUG_SCRP   yLOG_value   ("a_key"     , a_key);
   switch (a_key) {
   case '0' : case '1' : case '2' : case '3' : case '4' :
   case '5' : case '6' : case '7' : case '8' : case '9' :
   case '-'      : case '+'      :
      DEBUG_SCRP   yLOG_note    ("reqested change to delay");
      yMACRO_ddelay (a_key);
      break;
   case 'n' : case 's' : case 'b' : case 'p' : case 'd' :
      DEBUG_SCRP   yLOG_note    ("reqested change to update");
      g_dupdate = a_key;
      break;
   case ',' :
      DEBUG_SCRP   yLOG_note    ("reqested delay mode");
      ymacro_set2delay ();
      break;
   case '.' :
      DEBUG_SCRP   yLOG_note    ("reqested playback mode");
      ymacro_set2play ();
      break;
   case G_KEY_ESCAPE : case G_CHAR_ESCAPE :
      DEBUG_SCRP   yLOG_note    ("reqested termination with escape");
      ymacro_set2stop ();
      ymacro_script__close ();
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return -1;
      break;
   case G_KEY_RETURN : case G_KEY_ENTER  : case G_CHAR_RETURN :
      DEBUG_SCRP   yLOG_note    ("reqested normal run with return");
      ymacro_set2run   ();
      break;
   default  :
      DEBUG_SCRP   yLOG_note    ("requested step macro forward");
      rc = 0;
      break;
   }
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return rc;
}

uchar
yMACRO_exec             (uchar a_play)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_key       =  ' ';
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(playback)-----------------------*/
   DEBUG_SCRP   yLOG_note    ("handle playback control");
   DEBUG_SCRP   yLOG_value   ("a_play"    , a_play);
   a_play = ymacro_exe_play (a_play);
   DEBUG_SCRP   yLOG_value   ("play"      , rc);
   if (rc < 0) {
      DEBUG_SCRP   yLOG_note    ("terminated, do not execute next key");
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (rc > 0) {
      DEBUG_SCRP   yLOG_note    ("playback key, no impact on macro");
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(not-repeating)------------------*/
   DEBUG_SCRP   yLOG_note    ("macro running, delay, or playback");
   x_key = (uchar) ymacro_exe_key ();
   DEBUG_SCRP   yLOG_value   ("x_key"     , x_key);
   IF_MACRO_OFF {
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return x_key;
   }
   /*---(advance)------------------------*/
   DEBUG_SCRP   yLOG_note    ("advance");
   ymacro_exe_adv (a_play);
   /*> ymacro_exe_adv (0);                                                            <*/
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return x_key;
}




