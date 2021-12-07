/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



static  char   s_name   [LEN_FULL]  = "";
static  FILE  *s_script = NULL;
static  int    s_line   =    0;
static  char   s_style  =  '.';

char
ymacro_script__open     (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_name      [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_SCRP   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_info    ("a_name"    , a_name);
   /*---(fix)----------------------------*/
   if (strstr (a_name, ".script") == NULL)  sprintf (x_name, "%s.script", a_name);
   else                                     strlcpy (x_name, a_name, LEN_HUND);
   /*---(prepare)------------------------*/
   DEBUG_SCRP   yLOG_point   ("s_script"  , s_script);
   --rce;  if (s_script != NULL) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_info    ("x_name"    , x_name);
   /*---(read)---------------------------*/
   s_script = fopen (x_name, "rt");
   DEBUG_SCRP   yLOG_point   ("s_script"  , s_script);
   --rce;  if (s_script == NULL) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save name)----------------------*/
   strlcpy (s_name, x_name, LEN_DESC);
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_script__close    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(clear script macros)------------*/
   /*> ymacro_purge (YMACRO_GREEK);                                                   <*/
   ymacro_clear ('.');
   /*---(prepare)------------------------*/
   DEBUG_SCRP   yLOG_point   ("s_script"  , s_script);
   --rce;  if (s_script == NULL) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = fclose (s_script);
   DEBUG_SCRP   yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground pointer)-----------------*/
   s_script = NULL;
   strlcpy (s_name, "", LEN_DESC);
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_script__read     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_recd      [LEN_RECD];
   uchar       x_ready     [LEN_RECD];
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_point   ("s_script"  , s_script);
   --rce;  if (s_script == NULL) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(next line)----------------------*/
   --rce;  while (1) {
      /*---(done with line)-----------------*/
      DEBUG_SCRP   yLOG_value   ("feof"      , feof (s_script));
      if (feof (s_script)) {
         ymacro_script__close ();
         DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(process line)-------------------*/
      fgets (x_recd, LEN_RECD, s_script);
      ++s_line;
      if (x_recd [0] <  ' ') {
         DEBUG_SCRP   yLOG_note    ("blank leader, skipping");
         continue;
      }
      if (x_recd [0] == '#') {
         DEBUG_SCRP   yLOG_note    ("comment marker, skipping");
         continue;
      }
      x_len = strlen (x_recd);
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      DEBUG_SCRP   yLOG_info    ("x_recd"    , x_recd);
      /*---(functions)----------------------*/
      if (strncmp (x_recd, "macro ", 6) == 0) {
         rc = ymacro_rec_full (x_recd + 6);
         DEBUG_SCRP   yLOG_value   ("macro"     , rc);
         if (rc < 0) {
            DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      /*---(normal)-------------------------*/
      else {
         sprintf (x_ready, ".=%s", x_recd);
         DEBUG_SCRP   yLOG_info    ("current"   , x_ready);
         rc = ymacro_rec_full (x_ready);
         DEBUG_SCRP   yLOG_value   ("normal"    , rc);
         if (rc < 0) {
            DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         rc = ymacro_exe_beg  (s_style);
         DEBUG_SCRP   yLOG_value   ("execute"   , rc);
         if (rc < 0) {
            DEBUG_SCRP   yLOG_note    ("can not execute");
            DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         break;
      }
      /*---(done)---------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_script__start    (char *a_name, char a_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   rc = ymacro_script__open (a_name);
   DEBUG_SCRP   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_style == '!') {
      /*> yvikeys_sizes_switch ("status", "script");                                  <*/
      a_style = '.';
   }
   s_style = a_style;
   DEBUG_SCRP   yLOG_char    ("s_style"   , s_style);
   if (myMACRO.blitz == 'y')  myMACRO.blitzing = 'y';
   DEBUG_SCRP   yLOG_char    ("myMACRO.blitz"   , myMACRO.blitz);
   DEBUG_SCRP   yLOG_char    ("myMACRO.blitzing", myMACRO.blitzing);
   rc = ymacro_script__read ();
   DEBUG_SCRP   yLOG_value   ("read"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> g_macros [myMACRO.ecurr].pos       =   -1;                                     <* 
    *> rc = ymacro_exe_beg  ('.');                                                    <* 
    *> DEBUG_SCRP   yLOG_value   ("execute"   , rc);                                  <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_SCRP   yLOG_note    ("can not execute");                              <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yMACRO_script_start     (char *a_name) { return ymacro_script__start (a_name, '.'); }
char yMACRO_script_follow    (char *a_name) { return ymacro_script__start (a_name, '!'); }
char yMACRO_script_playback  (char *a_name) { return ymacro_script__start (a_name, ','); }
char yMACRO_script_blitz     (char *a_name) { myMACRO.blitz  = 'y';  return ymacro_script__start (a_name, '.'); }

