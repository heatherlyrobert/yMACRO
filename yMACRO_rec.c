/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"

/*
 * metis § yv8·· § add yKEYS modes to recording for later control during execution        § M2K5xx §  · §
 *
 */


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
/*===----                        status control                        ----===*/
/*====================------------------------------------====================*/
static void  o___CONTROL_________o () { return; }

char 
ymacro_rec_set          (uchar a_abbr)
{
   int         n           =   -1;
   if (a_abbr == 0)  return n;
   if (a_abbr == ',')  a_abbr = '.';
   n  = strlchr (S_MACRO_LIST, a_abbr, S_MACRO_MAX);
   if (n >= 0) {
      myMACRO.rname = a_abbr;
      myMACRO.rcurr = n;
   } else {
      myMACRO.rname = '-';
      myMACRO.rcurr = -1;
   }
   return n;
}

char         /*-> fully reset macro mode -------------[ leaf   [gz.532.011.00]*/ /*-[00.0000.183.!]-*/ /*-[--.---.---.--]-*/
ymacro_rec_reset        (void)
{
   if (myMACRO.rcurr < 0)  return 0;
   ymacro_wipe (S_MACRO_LIST [myMACRO.rcurr]);
   return 0;
}

char yMACRO_rec_mode  (void)         { return myMACRO.rmode; }



/*====================------------------------------------====================*/
/*===----                     character-by-character                   ----===*/
/*====================------------------------------------====================*/
static void  o___DETAIL__________o () { return; }

char
ymacro_rec_clear        (void)
{
   myMACRO.rkeys [0] = G_KEY_NULL;
   /*> myMACRO.modes [0] = G_KEY_NULL;                                                <*/
   myMACRO.rlen      = 0;
   myMACRO.rpos      = 0;
   myMACRO.rcur      = '-';
   return 0;
}

char         /*-> prepare a macro recording ----------[ ------ [ge.831.112.53]*/ /*-[01.0000.023.A]-*/ /*-[--.---.---.--]-*/
ymacro_rec_beg          (uchar a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =   -1;
   uchar       x_lower     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_char    ("a_name"    , a_name);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_YMACRO   yLOG_note    ("can not execute until operational");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_char    ("myMACRO.rmode"   , myMACRO.rmode);
   --rce;  IF_MACRO_RECORDING {
      DEBUG_YMACRO   yLOG_note    ("can not record two macros at once");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check macro name)------------*/
   x_lower = tolower (a_name);
   DEBUG_YMACRO   yLOG_char    ("x_lower"   , x_lower);
   n = ymacro_index  (x_lower);
   DEBUG_YMACRO   yLOG_value   ("n"         , n);
   if (n <  0)  {
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for illegal)-----------*/
   DEBUG_YMACRO   yLOG_value   ("rcurr"    , myMACRO.rcurr);
   DEBUG_YMACRO   yLOG_char    ("rname"    , myMACRO.rname);
   --rce;  if (myMACRO.rcurr >= 0) {
      DEBUG_YMACRO   yLOG_note    ("already recording a macro");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_value   ("ecurr"     , myMACRO.ecurr);
   --rce;  if (n == myMACRO.ecurr) {
      DEBUG_YMACRO   yLOG_note    ("currently executing this macro");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_value   ("pos"       , g_macros [n].pos);
   --rce;  if (g_macros [n].pos >= 0) {
      DEBUG_YMACRO   yLOG_note    ("this macro is active");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [n].runby);
   --rce;  if (g_macros [n].runby >= 0 && n != 61) {
      DEBUG_YMACRO   yLOG_note    ("this macro is running higher in tree");
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check macro name)------------*/
   rc = ymacro_rec_set (x_lower);
   DEBUG_YMACRO   yLOG_value   ("rec_set"   , rc);
   if (rc <  0)  {
      yKEYS_set_lock ();
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_value   ("myMACRO.rcurr"   , myMACRO.rcurr);
   /*---(prepare)---------------------*/
   ymacro_rec_clear ();
   if (strchr (YSTR_UPPER, a_name) != NULL && g_macros [myMACRO.rcurr].len > 0) {
      strlcpy (myMACRO.rkeys, g_macros [myMACRO.rcurr].keys , LEN_RECD);
      /*> strlcpy (myMACRO.modes, g_macros [myMACRO.rcurr].modes, LEN_RECD);          <*/
   } else {
      strlcpy (myMACRO.rkeys, "¤", LEN_RECD);
   }
   myMACRO.rlen = strlen (myMACRO.rkeys);
   myMACRO.rpos = myMACRO.rlen - 2;
   /*---(turn on record)--------------*/
   DEBUG_YMACRO   yLOG_info    ("keys"      , myMACRO.rkeys);
   SET_MACRO_RECORD;
   DEBUG_YMACRO   yLOG_char    ("myMACRO.rmode"   , myMACRO.rmode);
   /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "record");          <*/
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> add a key to a macro ---------------[ leaf   [gc.440.102.10]*/ /*-[01.0000.103.9]-*/ /*-[--.---.---.--]-*/
yMACRO_rec_key          (uchar a_key, uchar a_mode)
{
   IF_MACRO_RECORDING {
      DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
      switch (a_key) {
      case G_KEY_RETURN  :  a_key  = G_CHAR_RETURN;  break;  /* return char           */
      case G_KEY_ENTER   :  a_key  = G_CHAR_RETURN;  break;  /* return char           */
      case G_KEY_ESCAPE  :  a_key  = G_CHAR_ESCAPE;  break;  /* escape char           */
      case G_KEY_TAB     :  a_key  = G_CHAR_SPACE;   break;  /* tab char              */
      case G_KEY_BS      :  a_key  = G_CHAR_BS;      break;  /* backspace char        */
      case G_KEY_SPACE   :  a_key  = G_CHAR_SPACE;   break;  /* visual space          */
      }
      myMACRO.rcur                     = a_key;
      myMACRO.rkeys [myMACRO.rlen - 1] = a_key;
      myMACRO.rkeys [myMACRO.rlen    ] = G_CHAR_PLACE;
      myMACRO.rkeys [myMACRO.rlen + 1] = G_KEY_NULL;
      /*> myMACRO.modes [myMACRO.rlen - 1] = a_mode;                                  <*/
      /*> myMACRO.modes [myMACRO.rlen    ] = G_KEY_NULL;                              <*/
      ++myMACRO.rlen;
      myMACRO.rpos                     = myMACRO.rlen - 2;
      DEBUG_YMACRO   yLOG_sint    (myMACRO.rlen);
      DEBUG_YMACRO   yLOG_snote   (myMACRO.rkeys);
      DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
   }
   return 0;
}

char         /*-> put keys in globals ----------------[ leaf   [gz.530.101.60]*/ /*-[01.0000.01#.5]-*/ /*-[--.---.---.--]-*/
ymacro_rec_str          (char *a_keys)
{
   int         i           = 0;
   char        x_ch        = '-';
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_char    ("rec_mode"  , yMACRO_rec_mode);
   IF_MACRO_RECORDING {
      /*---(look for suffix)----------------*/
      if (myMACRO.rkeys [myMACRO.rlen - 1] == G_CHAR_PLACE) {
         myMACRO.rkeys [--myMACRO.rlen  ] =  G_KEY_NULL;
      }
      if (myMACRO.rkeys [myMACRO.rlen - 1] == G_CHAR_HALT ) {
         myMACRO.rkeys [--myMACRO.rlen  ] =  G_KEY_NULL;
      }
      /*---(add keys)-----------------------*/
      if (a_keys == NULL)  strlcat (myMACRO.rkeys, ""    , LEN_RECD);
      else                 strlcat (myMACRO.rkeys, a_keys, LEN_RECD);
      myMACRO.rlen  = strlen (myMACRO.rkeys);
      /*---(fix keys)-----------------------*/
      /*> strlencode   (myMACRO.rkeys, ySTR_MAX, LEN_RECD);                           <*/
      strlencode   (myMACRO.rkeys, '-', LEN_RECD);
      /*---(add suffix)---------------------*/
      myMACRO.rkeys [myMACRO.rlen  ] =  G_CHAR_PLACE;
      myMACRO.rkeys [++myMACRO.rlen] =  G_KEY_NULL;
      /*---(update pos/char)----------------*/
      myMACRO.rpos = myMACRO.rlen - 2;
      if (myMACRO.rpos < 0)  myMACRO.rpos = 0;
      /*> printf ("myMACRO.rkeys <<%s>>¦", myMACRO.rkeys);                                <*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> complete a macro recording ---------[ ------ [gz.420.001.21]*/ /*-[02.0000.113.5]-*/ /*-[--.---.---.--]-*/
yMACRO_rec_end          (void)
{
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_char    ("rec_mode"  , yMACRO_rec_mode);
   IF_MACRO_RECORDING {
      DEBUG_YMACRO   yLOG_note    ("recording, so save");
      DEBUG_YMACRO   yLOG_value   ("rlen"      , myMACRO.rlen);
      DEBUG_YMACRO   yLOG_char    ("last char" , myMACRO.rkeys [myMACRO.rlen - 2]);
      if (myMACRO.rlen > 2 && myMACRO.rkeys [myMACRO.rlen - 2] == 'q') {
         myMACRO.rkeys [myMACRO.rlen - 2] = G_CHAR_HALT;
         myMACRO.rkeys [myMACRO.rlen - 1] = G_KEY_NULL;
         --myMACRO.rlen;
         ymacro_save ();
         /*> ymacro_wipe (myMACRO.rname);                                             <*/
      } else if (myMACRO.rlen == 2 && myMACRO.rkeys [myMACRO.rlen - 2] == 'q') {
         myMACRO.rkeys [0] = G_KEY_NULL;
         myMACRO.rlen      = 0;
         ymacro_save ();
         /*> ymacro_wipe (myMACRO.rname);                                             <*/
      }
      DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.rcurr].runby);
      /*> ymacro_rec_clear ();                                                        <*/
      ymacro_rec_reset  ();
      /*> myMACRO.rkeys [0] = G_KEY_NULL;                                             <* 
       *> myMACRO.rlen      = 0;                                                      <* 
       *> myMACRO.rpos      = 0;                                                      <* 
       *> myMACRO.rcur      = '-';                                                    <*/
      SET_MACRO_IGNORE;
      myMACRO.rcurr = -1;
   } else {
      DEBUG_YMACRO   yLOG_note    ("not recording, nothing to do");
   }
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.rcurr].runby);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("a_string"  , a_string);
   --rce;  if (a_string == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_string);
   DEBUG_YMACRO   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 2) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_char    ("= sign"    , a_string [1]);
   --rce;  if (a_string [1] != '=') {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin recording)----------------*/
   x_id = a_string [0];
   DEBUG_YMACRO   yLOG_char    ("x_id"      , x_id);
   rc = ymacro_rec_beg (x_id);
   DEBUG_YMACRO   yLOG_value   ("recbeg"    , rc);
   --rce;  if (rc < 0) {
      ymacro_clear (x_id);
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(fix quotes)---------------------*/
   DEBUG_YMACRO   yLOG_char    ("[2]"       , a_string [2]);
   DEBUG_YMACRO   yLOG_char    ("[x_len-1]" , a_string [x_len - 1]);
   if (a_string [2] == G_KEY_DQUOTE && a_string [x_len - 1] == G_KEY_DQUOTE) {
      DEBUG_YMACRO   yLOG_note    ("quoted macro format");
      strlcpy (t, a_string + 3, LEN_RECD);
      x_len = strlen (t);
      t [--x_len] = G_KEY_NULL;
   } else {
      strlcpy (t, a_string + 2, LEN_RECD);
   }
   DEBUG_YMACRO   yLOG_note    ("done with quotes");
   DEBUG_YMACRO   yLOG_info    ("t"         , t);
   /*---(add keys)-----------------------*/
   rc = ymacro_rec_str (t);
   DEBUG_YMACRO   yLOG_value   ("recstr"    , rc);
   --rce;  if (rc < 0) {
      ymacro_clear (x_id);
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(append end record key)----------*/
   rc = yMACRO_rec_key ('q', '·');
   /*---(end recording)------------------*/
   rc = yMACRO_rec_end ();
   DEBUG_YMACRO   yLOG_value   ("recend"    , rc);
   --rce;  if (rc < 0) {
      ymacro_clear (x_id);
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> enter a macro directly -------------[ ------ [ge.850.137.A4]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yMACRO_direct           (char *a_string)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_abbr      =  '-';
   char        x_div       =  '-';
   char       *x_valid     = "*aA0è";
   char        x_other     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_YMACRO   yLOG_note    ("can not execute until operational");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("a_string"  , a_string);
   --rce;  if (a_string == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_string"  , a_string);
   x_len = strlen (a_string);
   DEBUG_YMACRO   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_abbr  = a_string [0];
   DEBUG_YMACRO   yLOG_char    ("x_abbr"      , x_abbr);
   /*---(check for purge)----------------*/
   --rce;  if (strcmp (a_string, "purge") == 0) {
      rc = yMACRO_reset_all ();
      rc = ymacro_purge (MACRO_ALL);
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(check for reset)----------------*/
   --rce;  if (strcmp (a_string, "reset") == 0) {
      rc = yMACRO_reset_all ();
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(check for one-letter)-----------*/
   --rce;  if (x_len == 1) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(multi-character)----------------*/
   x_div = a_string [1];
   DEBUG_YMACRO   yLOG_char    ("x_div"     , x_div);
   /*---(check for shorts)---------------*/
   --rce;  if (x_len == 2) {
      DEBUG_YMACRO   yLOG_char    ("x_div"     , x_div);
      switch (x_div) {
      case '-' :
         rc = yMACRO_export      (x_abbr);
         break;
      case '+' :
         rc = yMACRO_import      (x_abbr);
         break;
      case 'x' : case 'd' : case '#' :
         rc = ymacro_clear       (x_abbr);
         break;
      case 'y' :
         rc = yMACRO_yank        (x_abbr, "");
         break;
      case 'p' :
         rc = yMACRO_paste       (x_abbr, "");
         break;
      case '~' :
         rc = yMACRO_to_sreg     (x_abbr, '"');
         break;
      case '/' :
         rc = yMACRO_flatten     (x_abbr);   /* to 0 */
         break;
      case '*' :
         rc = yMACRO_install     (x_abbr);   /* to 0 */
         break;
      case '=' :
         rc = ymacro_rec_full   (a_string);
         break;
      default  :
         DEBUG_YMACRO   yLOG_note    ("two-char action not understood");
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(normals)------------------------*/
   x_other = a_string [2];
   DEBUG_YMACRO   yLOG_char    ("x_other"   , x_other);
   --rce;  if (x_len == 3) {
      DEBUG_YMACRO   yLOG_char    ("x_div"     , x_div);
      switch (x_div) {
      case '>' :
         rc = yMACRO_copy        (x_abbr, x_other);
         break;
      case ']' :
         rc = yMACRO_copy        (x_abbr, x_other);
         rc = ymacro_clear       (x_abbr);
         break;
      case ')' :
         rc = yMACRO_copy        (x_abbr , '¤');
         rc = yMACRO_copy        (x_other, x_abbr);
         rc = yMACRO_copy        ('¤'    , x_other);
         break;
      case '/' :
         rc = yMACRO_flatten_at  (x_abbr, x_other);
         break;
      case '*' :
         rc = yMACRO_install_at  (x_abbr, x_other);
         break;
      case '~' :
         rc = yMACRO_to_sreg     (x_abbr, x_other);
         break;
      case '=' :
         rc = ymacro_rec_full   (a_string);
         break;
      default  :
         DEBUG_YMACRO   yLOG_note    ("three-char action not understood");
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(recording)----------------------*/
   --rce;  if (x_len >  2 && x_div == '=') {
      rc = ymacro_rec_full   (a_string);
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(global)-------------------------*/
   --rce;  if (x_len >  2 && x_div == '!') {
      rc = yMACRO_central    (x_abbr, a_string);
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}


