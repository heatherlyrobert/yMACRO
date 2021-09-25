/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



/*
 * this is almost a complete imitation of vi/vim, with some new twists
 *
 * macro names (60) are
 *    a-z          normal use
 *    0-9          system (folding/unfolding)
 *    è-ÿ          specialty and standard
 *    .            current (temp)
 *
 * in yVIKEYS, in interactive use macros are recorded like "q¢´´´´´q"
 *    -- the macro recording begins and ends with the letter 'q'
 *    -- if it ends with 'Q', the macro recording is forgotten
 *    -- the second letter (¢) is the macro name
 *    -- if ¢ is an illegal name, no recording takes place
 *    -- all keys between the q's are stored in the macro named ¢
 *    -- if ¢ is upper case, the keys are appended to the existing ones
 *    -- all keys (´) are executed normally during recording
 *
 * very simple theoretically (perfect), but super powerful and flexible
 *
 *
 *
 *
 *
 */



/*====================------------------------------------====================*/
/*===----                     character-by-character                   ----===*/
/*====================------------------------------------====================*/
static void  o___DETAIL__________o () { return; }

char 
ymacro_rec_set          (uchar a_abbr)
{
   int         n           =   -1;
   if (a_abbr == 0)  return n;
   if (a_abbr == ',')  a_abbr = '.';
   n  = strlchr (S_MACRO_LIST, a_abbr, S_MACRO_MAX);
   if (n >= 0) {
      g_rname = a_abbr;
      g_rcurr = n;
   } else {
      g_rname = '-';
      g_rcurr = -1;
   }
   return n;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_rec_reset        (void)
{
   if (g_rcurr < 0)  return 0;
   ymacro_wipe (S_MACRO_LIST [g_rcurr]);
   return 0;
}

char yMACRO_rec_mode  (void)         { return g_rmode; }

char         /*-> prepare a macro recording ----------[ ------ [ge.831.112.53]*/ /*-[01.0000.023.A]-*/ /*-[--.---.---.--]-*/
ymacro_rec_beg          (char a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_SCRP   yLOG_note    ("can not execute until operational");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_char    ("g_rmode"   , g_rmode);
   --rce;  IF_MACRO_RECORDING {
      DEBUG_SCRP   yLOG_note    ("can not record two macros at once");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
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
   --rce;  if (g_rcurr >= 0) {
      DEBUG_SCRP   yLOG_note    ("already recording a macro");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_value   ("g_ecurr"   , g_ecurr);
   --rce;  if (n == g_ecurr) {
      DEBUG_SCRP   yLOG_note    ("currently executing this macro");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_value   ("pos"       , g_macros [n].pos);
   --rce;  if (g_macros [n].pos >= 0) {
      DEBUG_SCRP   yLOG_note    ("this macro is active");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_value   ("runby"     , g_macros [n].runby);
   --rce;  if (g_macros [n].runby >= 0) {
      DEBUG_SCRP   yLOG_note    ("this macro is running higher in tree");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check macro name)------------*/
   DEBUG_SCRP   yLOG_char    ("a_name"    , a_name);
   if (ymacro_rec_set (tolower (a_name)) <  0)  {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_value   ("g_rcurr"   , g_rcurr);
   /*---(prepare)---------------------*/
   if (strchr (YSTR_UPPER, a_name) != NULL && g_macros [g_rcurr].len > 0) {
      strlcpy (g_rkeys, g_macros [g_rcurr].keys, LEN_RECD);
   } else {
      strlcpy (g_rkeys, "¤", LEN_RECD);
   }
   g_rlen = strlen (g_rkeys);
   g_rpos = g_rlen - 2;
   /*---(turn on record)--------------*/
   DEBUG_SCRP   yLOG_value   ("keys"      , g_rkeys);
   SET_MACRO_RECORD;
   DEBUG_SCRP   yLOG_char    ("g_rmode"   , g_rmode);
   /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "record");          <*/
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> add a key to a macro ---------------[ leaf   [gc.440.102.10]*/ /*-[01.0000.103.9]-*/ /*-[--.---.---.--]-*/
yMACRO_rec_key          (char a_key)
{
   IF_MACRO_RECORDING {
      switch (a_key) {
      case G_KEY_RETURN  :  a_key  = G_CHAR_RETURN;  break;  /* return char           */
      case G_KEY_ENTER   :  a_key  = G_CHAR_RETURN;  break;  /* return char           */
      case G_KEY_ESCAPE  :  a_key  = G_CHAR_ESCAPE;  break;  /* escape char           */
      case G_KEY_TAB     :  a_key  = G_CHAR_TAB;     break;  /* tab char              */
      case G_KEY_BS      :  a_key  = G_CHAR_BS;      break;  /* backspace char        */
      case G_KEY_SPACE   :  a_key  = G_CHAR_SPACE;   break;  /* visual space          */
      }
      g_rcur               = a_key;
      g_rkeys [g_rlen - 1] = a_key;
      g_rkeys [g_rlen++  ] = G_CHAR_PLACE;
      g_rkeys [g_rlen    ] = G_KEY_NULL;
      g_rpos               = g_rlen - 2;
   }
   return 0;
}

char         /*-> put keys in globals ----------------[ leaf   [gz.530.101.60]*/ /*-[01.0000.01#.5]-*/ /*-[--.---.---.--]-*/
ymacro_rec_str          (char *a_keys)
{
   int         i           = 0;
   char        x_ch        = '-';
   IF_MACRO_RECORDING {
      /*---(look for suffix)----------------*/
      if (g_rkeys [g_rlen - 1] == G_CHAR_PLACE) {
         g_rkeys [--g_rlen  ] =  G_KEY_NULL;
      }
      if (g_rkeys [g_rlen - 1] == G_CHAR_HALT ) {
         g_rkeys [--g_rlen  ] =  G_KEY_NULL;
      }
      /*---(add keys)-----------------------*/
      if (a_keys == NULL)  strlcat (g_rkeys, ""    , LEN_RECD);
      else                 strlcat (g_rkeys, a_keys, LEN_RECD);
      g_rlen  = strlen (g_rkeys);
      /*---(fix keys)-----------------------*/
      strlencode   (g_rkeys, ySTR_MAX, LEN_RECD);
      /*---(add suffix)---------------------*/
      g_rkeys [g_rlen  ] =  G_CHAR_PLACE;
      g_rkeys [++g_rlen] =  G_KEY_NULL;
      /*---(update pos/char)----------------*/
      g_rpos = g_rlen - 2;
      if (g_rpos < 0)  g_rpos = 0;
      /*> printf ("g_rkeys <<%s>>¦", g_rkeys);                                <*/
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> complete a macro recording ---------[ ------ [gz.420.001.21]*/ /*-[02.0000.113.5]-*/ /*-[--.---.---.--]-*/
yMACRO_rec_end          (void)
{
   IF_MACRO_RECORDING {
      if (g_rlen > 2 && g_rkeys [g_rlen - 2] == 'q') {
         g_rkeys [g_rlen - 2] = G_CHAR_HALT;
         g_rkeys [g_rlen - 1] = G_KEY_NULL;
         --g_rlen;
         ymacro_save ();
         ymacro_wipe (g_rname);
      } else if (g_rlen == 2 && g_rkeys [g_rlen - 2] == 'q') {
         g_rkeys [0] = G_KEY_NULL;
         g_rlen      = 0;
         ymacro_save ();
         ymacro_wipe (g_rname);
      }
      g_rkeys [0] = G_KEY_NULL;
      g_rlen      = 0;
      g_rpos      =   0;
      g_rcur      = '-';
      SET_MACRO_IGNORE;
      g_rcurr = -1;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        multi-character                       ----===*/
/*====================------------------------------------====================*/
static void  o___MULTI___________o () { return; }

char
ymacro_rec_full         (char *a_string)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =   -1;
   char        x_id        =  '-';
   int         x_len       =    0;
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_point   ("a_string"  , a_string);
   --rce;  if (a_string == NULL) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_string);
   DEBUG_SCRP   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 2) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_char    ("= sign"    , a_string [1]);
   --rce;  if (a_string [1] != '=') {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin recording)----------------*/
   x_id = a_string [0];
   DEBUG_SCRP   yLOG_char    ("x_id"      , x_id);
   rc = ymacro_rec_beg (x_id);
   DEBUG_SCRP   yLOG_value   ("recbeg"    , rc);
   --rce;  if (rc < 0) {
      ymacro_clear (x_id);
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(fix quotes)---------------------*/
   DEBUG_SCRP   yLOG_char    ("[2]"       , a_string [2]);
   DEBUG_SCRP   yLOG_char    ("[x_len-1]" , a_string [x_len - 1]);
   if (a_string [2] == G_KEY_DQUOTE && a_string [x_len - 1] == G_KEY_DQUOTE) {
      DEBUG_SCRP   yLOG_note    ("quoted macro format");
      strlcpy (t, a_string + 3, LEN_RECD);
      x_len = strlen (t);
      t [--x_len] = G_KEY_NULL;
   } else {
      strlcpy (t, a_string + 2, LEN_RECD);
   }
   DEBUG_SCRP   yLOG_note    ("done with quotes");
   DEBUG_SCRP   yLOG_info    ("t"         , t);
   /*---(add keys)-----------------------*/
   rc = ymacro_rec_str (t);
   DEBUG_SCRP   yLOG_value   ("recstr"    , rc);
   --rce;  if (rc < 0) {
      ymacro_clear (x_id);
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(append end record key)----------*/
   rc = yMACRO_rec_key ('q');
   /*---(end recording)------------------*/
   rc = yMACRO_rec_end ();
   DEBUG_SCRP   yLOG_value   ("recend"    , rc);
   --rce;  if (rc < 0) {
      ymacro_clear (x_id);
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> enter a macro directly -------------[ ------ [ge.850.137.A4]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yMACRO_direct           (char *a_string)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_id        =  '-';
   char        x_div       =  '-';
   char       *x_valid     = "*aA0è";
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_SCRP   yLOG_note    ("can not execute until operational");
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_point   ("a_string"  , a_string);
   --rce;  if (a_string == NULL) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_info    ("a_string"  , a_string);
   x_len = strlen (a_string);
   DEBUG_SCRP   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_id  = a_string [0];
   DEBUG_SCRP   yLOG_char    ("x_id"      , x_id);
   x_div = a_string [1];
   DEBUG_SCRP   yLOG_char    ("x_div"     , x_div);
   /*---(check for purge)----------------*/
   --rce;  if (x_len == 1) {
      rc = ymacro_purge  (x_id);
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(check for shorts)---------------*/
   --rce;  if (x_len == 2) {
      switch (x_div) {
      case '=' : rc = ymacro_clear     (x_id);        break;
      case '-' : rc = yMACRO_export    (x_id);        break;
      case '+' : rc = yMACRO_import    (x_id);        break;
      case '>' : rc = yMACRO_to_reg    (x_id, '"');   break;
      case '<' : rc = yMACRO_from_reg  (x_id, '"');   break;
      default  : rc = yMACRO_copy      (x_id, x_div); break;
      }
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(copy)---------------------------*/
   --rce;  if (x_len == 3 && x_div == '>') {
      rc = yMACRO_to_reg     (x_id, a_string [2]);
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   --rce;  if (x_len == 3 && x_div == '<') {
      rc = yMACRO_from_reg   (x_id, a_string [2]);
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(recording)----------------------*/
   --rce;  if (x_len >  2 && x_div == '=') {
      rc = ymacro_rec_full   (a_string);
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(global)-------------------------*/
   --rce;  if (x_len >  2 && x_div == '!') {
      rc = yMACRO_central    (x_id, a_string);
      DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_rec_status       (char *a_list)
{
   /*> char        x_dots      [LEN_HUND] = "····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····";                                            <* 
    *> /+> char        x_dots      [LEN_HUND] = "····´····´····´····´····´····´····´····´····´····´····´····´····´";   <+/                                                          <* 
    *> int         x_len       = 0;                                                                                                                                                 <* 
    *> int         x_wide;                                                                                                                                                          <* 
    *> int         w;                                                                                                                                                               <* 
    *> /+---(header)-------------------------+/                                                                                                                                     <* 
    *> DEBUG_SCRP   yLOG_enter   (__FUNCTION__);                                                                                                                                    <* 
    *> /+---(get size)-----------------------+/                                                                                                                                     <* 
    *> yVIKEYS_view_size   (YVIKEYS_STATUS, NULL, &x_wide, NULL, NULL, NULL);                                                                                                       <* 
    *> DEBUG_SCRP   yLOG_value   ("x_wide"    , x_wide);                                                                                                                            <* 
    *> if (myVIKEYS.env != YVIKEYS_CURSES)    x_wide /= 7.5;                                                                                                                        <* 
    *> DEBUG_SCRP   yLOG_value   ("x_wide"    , x_wide);                                                                                                                            <* 
    *> w = x_wide - 15;                                                                                                                                                             <* 
    *> DEBUG_SCRP   yLOG_value   ("w"         , w);                                                                                                                                 <* 
    *> DEBUG_SCRP   yLOG_value   ("s_rcurr"   , s_rcurr);                                                                                                                           <* 
    *> if (s_rcurr < 0) {                                                                                                                                                           <* 
    *>    snprintf (a_list, LEN_FULL, "record  - ---  %*.*s", w, w, x_dots);                                                                                                        <* 
    *>    DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                                                                                                                 <* 
    *>    return 0;                                                                                                                                                                 <* 
    *> }                                                                                                                                                                            <* 
    *> DEBUG_SCRP   yLOG_info    ("s_rkeys"   , s_rkeys);                                                                                                                           <* 
    *> x_len = strlen (s_rkeys) - 1;                                                                                                                                                <* 
    *> DEBUG_SCRP   yLOG_value   ("x_len"     , x_len);                                                                                                                             <* 
    *> if (x_len == 0) {                                                                                                                                                            <* 
    *>    snprintf (a_list, LEN_FULL, "record  %c   0  %*.*s", s_rname, w, w, x_dots);                                                                                              <* 
    *>    DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                                                                                                                 <* 
    *>    return 0;                                                                                                                                                                 <* 
    *> }                                                                                                                                                                            <* 
    *> w -= 3;                                                                                                                                                                      <* 
    *> if (x_len == 1) {                                                                                                                                                            <* 
    *>    snprintf (a_list, LEN_FULL, "record  %c %3d  [%c] %*.*s", s_rname, x_len, s_rkeys [x_len - 1], w - x_len, w - x_len, x_dots + x_len);                                     <* 
    *>    DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                                                                                                                 <* 
    *>    return 0;                                                                                                                                                                 <* 
    *> }                                                                                                                                                                            <* 
    *> w -= 1;                                                                                                                                                                      <* 
    *> snprintf (a_list, LEN_FULL, "record  %c %3d  %*.*s [%c] %*.*s", s_rname, x_len, x_len - 1, x_len - 1, s_rkeys, s_rkeys [x_len - 1], w - x_len, w - x_len, x_dots + x_len);   <* 
    *> /+---(complete)-----------------------+/                                                                                                                                     <* 
    *> DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                                                                                                                    <* 
    *> return 0;                                                                                                                                                                    <*/
}


