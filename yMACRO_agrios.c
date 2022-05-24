/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



static char   s_type          = '-';
static uchar  s_active        = '-';
static uchar  s_agrios        [LEN_RECD]  = "";
static char   s_jump          [LEN_LABEL] = "";

static  char   s_style  =  '.';



/*====================------------------------------------====================*/
/*===----                         common support                       ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char
ymacro_agrios_init      (void)
{
   int         i           =    0;
   myMACRO.e_getter = NULL;
   myMACRO.e_forcer = NULL;
   myMACRO.e_pusher = NULL;
   myMACRO.g_level  = 0;
   for (i = 0; i < MAX_AGRIOS; ++i) {
      strlcpy (myMACRO.g_curr [i], "", LEN_LABEL);
      strlcpy (myMACRO.g_code [i], "", LEN_RECD);
      strlcpy (myMACRO.g_next [i], "", LEN_LABEL);
   }
   return 0;
}

char
yMACRO_agrios_config    (void *a_getter, void *a_forcer, void *a_pusher)
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
   if (a_getter != NULL) myMACRO.e_getter = a_getter;
   DEBUG_YMACRO   yLOG_point   ("getter"    , myMACRO.e_getter);
   if (a_forcer != NULL) myMACRO.e_forcer = a_forcer;
   DEBUG_YMACRO   yLOG_point   ("forcer"    , myMACRO.e_forcer);
   if (a_pusher != NULL) myMACRO.e_pusher = a_pusher;
   DEBUG_YMACRO   yLOG_point   ("pusher"    , myMACRO.e_pusher);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_agrios__reset    (void)
{
   yKEYS_repeat_reset ();
   strcpy (s_agrios, "");
   s_active = '-';
   strcpy (s_jump  , "");
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        agrios execution                      ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTION_______________o (void) {;}

char
ymacro_agrios__range    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        t           [LEN_LABEL] = "";
   char        x_beg       [LEN_TERSE] = "";
   char        x_end       [LEN_TERSE] = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   l = strlen (s_agrios);
   DEBUG_YMACRO   yLOG_value   ("l"         , l);
   --rce;  if (l < 7) {
      DEBUG_YMACRO   yLOG_note    ("too short for all parts, ex. ¶®a1..b6¶");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (l >= LEN_LABEL) {
      DEBUG_YMACRO   yLOG_note    ("too long for real need, ex. ¶®Jab1234..Tbc5678¶");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_char    ("prefix"    , s_agrios [0]);
   --rce;  if (s_agrios [0] != (uchar) '®') {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse)--------------------------*/
   strlcpy (t, s_agrios + 1, LEN_LABEL);
   p = strstr (t, "..");
   DEBUG_YMACRO   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p [0] = p [1] = '\0';
   strlcpy (x_beg, t    , LEN_TERSE);
   strlcpy (x_end, p + 2, LEN_TERSE);
   /*---(call range setting)-------------*/
   rc = yMAP_range (x_beg, x_end);
   DEBUG_YMACRO   yLOG_value   ("range"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_agrios__force_OLD(void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_mode      =  '-';
   char        x_type      =  '-';
   char        x_comp      =  ' ';
   int         l           =    0;
   char        t           [LEN_RECD]  = "";
   char        x_target    [LEN_TERSE] = "";
   char        x_contents  [LEN_RECD]  = "";
   char        x_final     [LEN_RECD]  = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   l = strlen (s_agrios);
   DEBUG_YMACRO   yLOG_value   ("l"         , l);
   --rce;  if (l < 4) {
      DEBUG_YMACRO   yLOG_note    ("too short for all parts, ex. ¶šs=0¶");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_mode = s_agrios [0];
   DEBUG_YMACRO   yLOG_char    ("x_mode"    , x_mode);
   --rce;  switch (x_mode) {
   case 'š'  :
      DEBUG_YMACRO   yLOG_note    ("force value");
      break;
   case 'Ù'  :
      DEBUG_YMACRO   yLOG_note    ("force formula");
      break;
   default   :
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(parse)--------------------------*/
   strlcpy (t, s_agrios + 1, LEN_RECD);
   DEBUG_YMACRO   yLOG_info    ("t"         , t);
   l--;
   DEBUG_YMACRO   yLOG_value   ("l"         , l);
   p = strchr (t, '=');
   DEBUG_YMACRO   yLOG_point   ("p (=)"     , p);
   --rce;  if (p == NULL) {
      p = strchr (t, '#');
      DEBUG_YMACRO   yLOG_point   ("p (#)"     , p);
      if (p == NULL) {
         DEBUG_YMACRO   yLOG_info    ("suffix"    , t + l - 2);
         if (strcmp (t + l - 2, "++") == 0) {
            DEBUG_YMACRO   yLOG_note    ("found increment");
            x_type = '=';
            x_comp = '1';
            t [l - 2] = '\0';
         } else if (strcmp (t + l - 2, "--") == 0) {
            DEBUG_YMACRO   yLOG_note    ("found decrement");
            x_type = '=';
            x_comp = '2';
            t [l - 2] = '\0';
         } else {
            DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         x_type = '#';
         p [0] = '\0';
         if (strchr ("#", p [ 1]) != NULL) {
            DEBUG_YMACRO   yLOG_note    ("compound string");
            x_comp = p [ 1];
            p [ 1] = '\0';
            p++;
         }
      }
   } else {
      x_type = '=';
      p [0] = '\0';
      if (strchr ("+-*/%", p [-1]) != NULL) {
         DEBUG_YMACRO   yLOG_note    ("compound numeric");
         x_comp = p [-1];
         p [-1] = '\0';
      }
   }
   /*---(check compound)-----------------*/
   DEBUG_YMACRO   yLOG_note    ("make target");
   strlcpy  (x_target  , t, LEN_TERSE);
   strltrim (x_target  , ySTR_BOTH, LEN_TERSE);
   DEBUG_YMACRO   yLOG_info    ("x_target"  , x_target);
   DEBUG_YMACRO   yLOG_complex ("special"   , "%c %c", x_type, x_comp);
   if      (x_comp == '1')   sprintf (x_contents, "%c %s + 1", x_type, x_target);
   else if (x_comp == '2')   sprintf (x_contents, "%c %s - 1", x_type, x_target);
   else if (x_comp != ' ')   sprintf (x_contents, "%c %s %c %s", x_type, x_target, x_comp, p + 1);
   else                      sprintf (x_contents, "%c %s", x_type, p + 1);
   DEBUG_YMACRO   yLOG_info    ("x_contents", x_contents);
   /*---(force)--------------------------*/
   DEBUG_YMACRO   yLOG_point   ("e_forcer"  , myMACRO.e_forcer);
   --rce;  if (myMACRO.e_forcer == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = myMACRO.e_forcer (x_mode, x_target, x_contents);
   DEBUG_YMACRO   yLOG_point   ("forcer"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_agrios__recurse  (char a_mode, char *a_sub)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   char        x_comp      =  ' ';
   int         l           =    0;
   char        x_target    [LEN_TERSE] = "";
   char        x_contents  [LEN_RECD]  = "";
   char        x_final     [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = NULL;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("a_sub"     , a_sub);
   --rce;  if (a_sub == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_sub"     , a_sub);
   l = strlen (a_sub);
   DEBUG_YMACRO   yLOG_value   ("l"         , l);
   /*---(get markers)--------------------*/
   p = strchr (a_sub, '=');
   DEBUG_YMACRO   yLOG_point   ("p (=)"     , p);
   q = strchr (a_sub, '#');
   DEBUG_YMACRO   yLOG_point   ("q (#)"     , q);
   /*---(handle numeric)-----------------*/
   --rce;  if (p != NULL) {
      DEBUG_YMACRO   yLOG_complex ("numeric"   , "%c at %d", p [0], p - a_sub);
      x_type = '=';
      p [0] = '\0';
      if (strchr ("+-*/%", p [-1]) != NULL) {
         DEBUG_YMACRO   yLOG_complex ("compound"  , "%c at %d", p [1], p - 1 - a_sub);
         x_comp = p [-1];
         p [-1] = '\0';
      }
      rc = ymacro_agrios__recurse (a_mode, p + 1);
      if (rc < 0) {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
   }
   /*---(handle string)------------------*/
   else if (q != NULL) {
      p = q;
      DEBUG_YMACRO   yLOG_complex ("string"    , "%c at %d", p [0], p - a_sub);
      x_type = '#';
      p [0] = '\0';
      if (strchr ("›", p [-1]) != NULL) {
         DEBUG_YMACRO   yLOG_complex ("compound"  , "%c at %d", p [1], p - 1 - a_sub);
         x_comp = p [-1];
         p [-1] = '\0';
      }
      rc = ymacro_agrios__recurse (a_mode, p + 1);
      if (rc < 0) {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
   }
   /*---(handle special)-----------------*/
   else if (l >= 3) {
      DEBUG_YMACRO   yLOG_info    ("suffix"    , a_sub + l - 2);
      if (strcmp (a_sub + l - 2, "++") == 0) {
         DEBUG_YMACRO   yLOG_note    ("found increment");
         x_type = '=';
         x_comp = '1';
         a_sub [l - 2] = '\0';
      } else if (strcmp (a_sub + l - 2, "--") == 0) {
         DEBUG_YMACRO   yLOG_note    ("found decrement");
         x_type = '=';
         x_comp = '2';
         a_sub [l - 2] = '\0';
      } else {
         DEBUG_YMACRO   yLOG_note    ("nothing found to do");
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(zip, zilch, nada)---------------*/
   else {
      DEBUG_YMACRO   yLOG_note    ("nothing found to do");
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(set target)---------------------*/
   DEBUG_YMACRO   yLOG_note    ("make target");
   strlcpy  (x_target  , a_sub, LEN_TERSE);
   strltrim (x_target  , ySTR_BOTH, LEN_TERSE);
   DEBUG_YMACRO   yLOG_info    ("x_target"  , x_target);
   /*---(check compound)-----------------*/
   DEBUG_YMACRO   yLOG_complex ("special"   , "%c %c", x_type, x_comp);
   if      (x_comp == '1')   sprintf (x_contents, "%c %s + 1", x_type, x_target);
   else if (x_comp == '2')   sprintf (x_contents, "%c %s - 1", x_type, x_target);
   else if (x_comp != ' ')   sprintf (x_contents, "%c %s %c %s", x_type, x_target, x_comp, p + 1);
   else                      sprintf (x_contents, "%c %s", x_type, p + 1);
   DEBUG_YMACRO   yLOG_info    ("x_contents", x_contents);
   /*---(clean contents)-----------------*/
   /*> strlunslash (x_contents, LEN_RECD);                                            <* 
    *> strldecode  (x_contents, LEN_RECD);                                            <*/
   /*> DEBUG_YMACRO   yLOG_info    ("x_contents", x_contents);                        <*/
   /*---(force)--------------------------*/
   DEBUG_YMACRO   yLOG_point   ("e_forcer"  , myMACRO.e_forcer);
   --rce;  if (myMACRO.e_forcer == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = myMACRO.e_forcer (a_mode, x_target, x_contents);
   DEBUG_YMACRO   yLOG_point   ("forcer"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ymacro_agrios__force    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_mode      =  '-';
   char        x_type      =  '-';
   char        x_comp      =  ' ';
   int         l           =    0;
   char        t           [LEN_RECD]  = "";
   char        x_target    [LEN_TERSE] = "";
   char        x_contents  [LEN_RECD]  = "";
   char        x_final     [LEN_RECD]  = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   l = strlen (s_agrios);
   DEBUG_YMACRO   yLOG_value   ("l"         , l);
   --rce;  if (l < 4) {
      DEBUG_YMACRO   yLOG_note    ("too short for all parts, ex. ¶šs=0¶");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_mode = s_agrios [0];
   DEBUG_YMACRO   yLOG_char    ("x_mode"    , x_mode);
   --rce;  switch (x_mode) {
   case 'š'  :
      DEBUG_YMACRO   yLOG_note    ("force value");
      break;
   case 'Ù'  :
      DEBUG_YMACRO   yLOG_note    ("force formula");
      break;
   default   :
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(prepare)------------------------*/
   strlcpy (t, s_agrios + 1, LEN_RECD);
   DEBUG_YMACRO   yLOG_info    ("t"         , t);
   /*---(recurse)------------------------*/
   rc = ymacro_agrios__recurse (x_mode, t);
   DEBUG_YMACRO   yLOG_value   ("recurse"   , rc);
   if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_agrios__call     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   int         l           =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        x_target    [LEN_LABEL] = "";
   char        x_args      [LEN_LABEL] = "";
   char       *p           = NULL;
   char        o           =    0;
   char        x_runby     =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   l = strlen (s_agrios);
   DEBUG_YMACRO   yLOG_value   ("l"         , l);
   --rce;  if (l < 2) {
      DEBUG_YMACRO   yLOG_note    ("too short for all parts, ex. ¶ a1¶");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_type = s_agrios [0];
   DEBUG_YMACRO   yLOG_char    ("x_type"    , x_type);
   --rce;  switch (x_type) {
   case ' '  :
      DEBUG_YMACRO   yLOG_note    ("function call/push");
      break;
   case '™'  :
      DEBUG_YMACRO   yLOG_note    ("absolute branch/goto");
      break;
   case 'Ø'  :
      DEBUG_YMACRO   yLOG_note    ("relative branch/goto");
      break;
   case 'ç'  :
      DEBUG_YMACRO   yLOG_note    ("self modification");
      break;
   default   :
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(clear mode)---------------------*/
   x_runby = g_macros [myMACRO.ecurr].runby;
   DEBUG_YMACRO  yLOG_value   ("x_runby"   , x_runby);
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   ymacro_set2stop ();
   g_macros [myMACRO.ecurr].runby = x_runby;
   DEBUG_YMACRO   yLOG_info    ("x_target"  , x_target);
   DEBUG_YMACRO   yLOG_info    ("x_args"    , x_args);
   /*---(parse)--------------------------*/
   strlcpy  (x_recd, s_agrios + 1, LEN_RECD);
   DEBUG_YMACRO   yLOG_info    ("x_recd"    , x_recd);
   strltrim (x_recd, ySTR_BOTH   , LEN_RECD);
   DEBUG_YMACRO   yLOG_info    ("x_recd"    , x_recd);
   p = strchr   (x_recd, ',');
   DEBUG_YMACRO   yLOG_point   ("p"         , p);
   --rce;  if (p != NULL) {
      p [0] = '\0';
      strlcpy (x_args, p + 1, LEN_LABEL);
   }
   strlcpy (x_target, x_recd, LEN_LABEL);
   /*---(push onto stack)----------------*/
   --rce;  if (x_type == ' ') {
      DEBUG_YMACRO   yLOG_note    ("push context onto stack for next level");
      yLOG_point   ("e_pusher"  , myMACRO.e_pusher);
      if (myMACRO.e_pusher == NULL) {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = myMACRO.e_pusher ('>', ++(myMACRO.g_level), x_args);
      DEBUG_YMACRO   yLOG_value   ("pusher"    , rc);
      if (rc < 0) {
         ymacro_agrios__reset ();
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   /*---(save jump for branch)-----------*/
   --rce;  if (x_type == 'Ø') {
      strlcpy  (s_jump, x_target, LEN_LABEL);
      DEBUG_YMACRO   yLOG_info    ("s_jump"    , s_jump);
      strlcpy (x_target, myMACRO.g_curr [myMACRO.g_level], LEN_LABEL);
   }
   /*---(get next)-----------------------*/
   if (x_type != 'ç') {
      strlcpy (myMACRO.g_curr [myMACRO.g_level], x_target, LEN_LABEL);
      strlcpy (myMACRO.g_code [myMACRO.g_level], ""      , LEN_RECD);
      strlcpy (myMACRO.g_next [myMACRO.g_level], ""      , LEN_LABEL);
      s_type = x_type;
      DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
      DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
      rc = ymacro_agrios__read ();
      g_macros [myMACRO.ecurr].runby = x_runby;
      DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
      DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_agrios__execute  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =   -1;
   /*---(dispatch)-----------------------*/
   switch (s_active) {
   case (uchar) '®'  :
      rc = ymacro_agrios__range   ();
      break;
   case (uchar) 'š'  : case (uchar) 'Ù'  :
      rc = ymacro_agrios__force   ();
      break;
   case (uchar) ' '  : case (uchar) '™'  : case (uchar) 'Ø'  :
      rc = ymacro_agrios__call    ();
      break;
   }
   /*---(clean-up)-----------------------*/
   ymacro_agrios__reset ();
   /*---(complete)-----------------------*/
   return rc;
}




/*====================------------------------------------====================*/
/*===----                        helper mode for yMAP                  ----===*/
/*====================------------------------------------====================*/
static void      o___HMODE___________________o (void) {;}

char
ymacro_agrios__biggies  (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =   -1;
   char        x_pos       =    0;
   /*---(quick out)----------------------*/
   if (a_major  != G_KEY_SPACE)  return 0;
   if (s_active == '-')          return 0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(major keys)---------------------*/
   switch (a_minor) {
   case G_KEY_SPACE  :
      DEBUG_YMACRO   yLOG_note    ("space, nothing to do");
      break;
   case G_KEY_ESCAPE :
      DEBUG_YMACRO   yLOG_note    ("escape, means forget and return to previous mode");
      ymacro_agrios__reset  ();
      break;
   case (uchar) '˜' :
      DEBUG_YMACRO   yLOG_note    ("low-tick, means execute helper");
      ymacro_agrios__execute ();
      break;
   default        :
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ymacro_agrios__capture  (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =   -1;
   char        x_pos       =    0;
   char        t           [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(begin)--------------------------*/
   if (s_active == '-') {
      switch (a_minor) {
      case (uchar) 'š' :
         DEBUG_YMACRO   yLOG_note    ("start a force value assignment");
         break;
      case (uchar) 'Ù' :
         DEBUG_YMACRO   yLOG_note    ("start a force formula assignment");
         break;
      case (uchar) '®' :
         DEBUG_YMACRO   yLOG_note    ("start a range setting");
         break;
      case (uchar) ' ' :
         DEBUG_YMACRO   yLOG_note    ("execute a function call/push");
         break;
      case (uchar) '™' :
         DEBUG_YMACRO   yLOG_note    ("execute a absolute branch/goto");
         break;
      case (uchar) 'Ø' :
         DEBUG_YMACRO   yLOG_note    ("execute a relative branch/goto");
         break;
      default        :
         DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      }
      ymacro_agrios__reset  ();
      s_active = a_minor;
   }
   /*---(add)----------------------------*/
   sprintf (t, "%c", a_minor);
   strlcat (s_agrios, t, LEN_RECD);
   DEBUG_YMACRO   yLOG_info    ("s_agrios"  , s_agrios);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yMACRO_agrios_hmode     (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   /*---(quick out)----------------------*/
   if (a_major != G_KEY_SPACE)  return 0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_char    ("a_major"   , a_major);
   DEBUG_YMACRO   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   /*---(defenses)-----------------------*/
   DEBUG_YMACRO   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_curr () != MODE_MAP ) {
      DEBUG_YMACRO   yLOG_note    ("must use in map mode");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(universal)----------------------*/
   rc = ymacro_agrios__biggies (a_major, a_minor);
   DEBUG_YMACRO   yLOG_value   ("biggies"   , rc);
   if (rc > 0) {
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(capture)------------------------*/
   rc = ymacro_agrios__capture (a_major, a_minor);
   DEBUG_YMACRO   yLOG_value   ("capture"   , rc);
   if (rc > 0) {
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_agrios__read     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_addr      [LEN_LABEL] = "";
   uchar       x_contents  [LEN_RECD]  = "";
   uchar       x_next      [LEN_LABEL] = "";
   int         x_len       =    0;
   uchar       x_ready     [LEN_RECD];
   char        x_runby     =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO  yLOG_value   ("ecurr"     , myMACRO.ecurr);
   x_runby = g_macros [myMACRO.ecurr].runby;
   DEBUG_YMACRO  yLOG_value   ("x_runby"   , x_runby);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("e_getter"  , myMACRO.e_getter);
   --rce;  if (myMACRO.e_getter == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   /*---(next line)----------------------*/
   --rce;  while (1) {
      /*---(read)------------------------*/
      DEBUG_YMACRO   yLOG_char    ("s_type"    , s_type);
      DEBUG_YMACRO   yLOG_info    ("g_curr"    , myMACRO.g_curr [myMACRO.g_level]);
      DEBUG_YMACRO   yLOG_info    ("s_type"    , s_jump);
      strlcpy (x_contents, s_jump, LEN_LABEL);
      rc = myMACRO.e_getter (s_type, myMACRO.g_curr [myMACRO.g_level], x_contents, x_next);
      strlcpy (s_jump, "", LEN_LABEL);
      DEBUG_YMACRO   yLOG_value   ("getter"    , rc);
      --rce;  if (rc < 0) {
         ymacro_agrios__reset ();
         strlcpy (x_contents, "", LEN_RECD);
         strlcpy (x_next    , "", LEN_LABEL);
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (s_type == ' ') {
         DEBUG_YMACRO   yLOG_note    ("function call, return quickly");
         strlcpy (x_contents, "·", LEN_RECD);
      }
      s_type = '-';
      /*---(filter comments/empties)--------*/
      if (x_contents [0] == '\0') {
         DEBUG_YMACRO   yLOG_note    ("empty line, end of function");
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
      if (x_len >= 2 && x_contents [0] == '#') {
         if (strchr ("#!>@", x_contents [1]) != NULL) {
            DEBUG_YMACRO   yLOG_note    ("comment leader, skipping");
            continue;
         }
      }
      strlcpy (myMACRO.g_code [myMACRO.g_level], x_contents, LEN_RECD);
      strlcpy (myMACRO.g_next [myMACRO.g_level], x_next    , LEN_LABEL);
      /*---(functions)----------------------*/
      if (strncmp (x_contents, "macro ", 6) == 0) {
         rc = ymacro_rec_full (x_contents + 6);
         DEBUG_YMACRO   yLOG_value   ("macro"     , rc);
         if (rc < 0) {
            DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      /*---(normal)-------------------------*/
      else {
         DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
         DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
         sprintf (x_ready, " =%s", x_contents);
         DEBUG_YMACRO   yLOG_info    ("current"   , x_ready);
         rc = ymacro_rec_full (x_ready);
         DEBUG_YMACRO   yLOG_value   ("normal"    , rc);
         if (rc < 0) {
            DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
         DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
         rc = ymacro_exe_beg  (s_style);
         DEBUG_YMACRO   yLOG_value   ("execute"   , rc);
         if (rc < 0) {
            DEBUG_YMACRO   yLOG_note    ("can not execute");
            DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
         /*> g_macros [myMACRO.ecurr].runby = x_runby;                                <*/
         DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
         DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
         break;
      }
      /*---(done)---------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_agrios_next      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_runby     =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
   x_runby =  g_macros [myMACRO.ecurr].runby;
   /*---(clear mode)-----*/
   ymacro_set2stop ();
   /*---(check next)-----*/
   g_macros [myMACRO.ecurr].runby = x_runby;
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
   strlcpy (myMACRO.g_curr [myMACRO.g_level], myMACRO.g_next [myMACRO.g_level], LEN_LABEL);
   strlcpy (myMACRO.g_code [myMACRO.g_level], ""            , LEN_RECD);
   strlcpy (myMACRO.g_next [myMACRO.g_level], ""            , LEN_LABEL);
   rc = ymacro_agrios__read ();
   g_macros [myMACRO.ecurr].runby = x_runby;
   DEBUG_YMACRO   yLOG_value   ("read"      , rc);
   DEBUG_YMACRO   yLOG_complex ("stack"     , "%2då%sæ", myMACRO.edepth, myMACRO.estack);
   DEBUG_YMACRO   yLOG_value   ("runby"     , g_macros [myMACRO.ecurr].runby);
   --rce;  if (rc < 0 && myMACRO.g_level <= 0) {
      DEBUG_YMACRO   yLOG_note    ("full agrios complete");
      /*> ymacro_exe_done ();                                                         <*/
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return G_KEY_NOOP;
   }
   --rce;  if (rc < 0 && myMACRO.g_level > 0) {
      DEBUG_YMACRO   yLOG_note    ("returning from function");
      yLOG_point   ("e_pusher"  , myMACRO.e_pusher);
      if (myMACRO.e_pusher == NULL) {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = myMACRO.e_pusher ('<', --(myMACRO.g_level), "");
      DEBUG_YMACRO   yLOG_value   ("pusher"    , rc);
      if (rc < 0) {
         ymacro_agrios__reset ();
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = ymacro_agrios_next  ();
   }
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitz"   , myMACRO.blitz);
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitzing", myMACRO.blitzing);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ymacro_agrios__start    (char *a_label, char a_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(starting point)-----------------*/
   DEBUG_YMACRO   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_label == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_label"   , a_label);
   strlcpy (myMACRO.g_curr [myMACRO.g_level], a_label, LEN_LABEL);
   /*---(execution style)----------------*/
   if (a_style == '!') {
      /*> yvikeys_sizes_switch ("status", "script");                                  <*/
      a_style = ' ';
   }
   s_style = a_style;
   DEBUG_YMACRO   yLOG_char    ("s_style"   , s_style);
   if (myMACRO.blitz == 'y')  myMACRO.blitzing = 'y';
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitz"   , myMACRO.blitz);
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitzing", myMACRO.blitzing);
   /*---(begin)--------------------------*/
   rc = ymacro_agrios__read ();
   DEBUG_YMACRO   yLOG_value   ("read"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yMACRO_agrios_start     (char *a_label) { return ymacro_agrios__start (a_label, ' '); }
char yMACRO_agrios_follow    (char *a_label) { return ymacro_agrios__start (a_label, '!'); }
char yMACRO_agrios_playback  (char *a_label) { return ymacro_agrios__start (a_label, ','); }
char yMACRO_agrios_blitz     (char *a_label) { myMACRO.blitz  = 'y';  return ymacro_agrios__start (a_label, ' '); }

