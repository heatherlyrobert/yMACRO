/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"

/*
 * metis § dn2#· § new script lines all appear to cause null/skip first key (wrong)       § M2N2RY §  1 § true, this is to keep key processing simple §
 *
 *
 *
 */


static  char   s_name   [LEN_FULL]  = "";
static  FILE  *s_script = NULL;
static  int    s_line   =    0;
static  char   s_style  =  '.';

char   yMACRO_skip       (void)   { myMACRO.ignore = 'y';  return 0; }
char   yMACRO_unskip     (void)   { myMACRO.ignore = '-';  return 0; }
char   yMACRO_skipping   (void)   { if (myMACRO.ignore == 'y') return 1;  return 0; }


char
ymacro_script__open     (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_name      [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_name"    , a_name);
   /*---(fix)----------------------------*/
   if (strstr (a_name, ".script") == NULL)  sprintf (x_name, "%s.script", a_name);
   else                                     strlcpy (x_name, a_name, LEN_HUND);
   /*---(prepare)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("s_script"  , s_script);
   --rce;  if (s_script != NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("x_name"    , x_name);
   /*---(read)---------------------------*/
   s_script = fopen (x_name, "rt");
   DEBUG_YMACRO   yLOG_point   ("s_script"  , s_script);
   --rce;  if (s_script == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save name)----------------------*/
   strlcpy (s_name, x_name, LEN_DESC);
   s_line = 0;
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_script__close    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(clear script macros)------------*/
   /*> ymacro_purge (YMACRO_GREEK);                                                   <*/
   ymacro_clear ('.');
   /*---(prepare)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("s_script"  , s_script);
   --rce;  if (s_script == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = fclose (s_script);
   DEBUG_YMACRO   yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground pointer)-----------------*/
   s_script = NULL;
   strlcpy (s_name, "", LEN_DESC);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
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
   static char x_ignore    =  '-';
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("s_script"  , s_script);
   --rce;  if (s_script == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (s_line == 0)  yMACRO_unskip ();
   /*---(next line)----------------------*/
   --rce;  while (1) {
      strlcpy (x_recd, "", LEN_RECD); /* clear it */
      /*---(done with line)-----------------*/
      DEBUG_YMACRO   yLOG_value   ("feof"      , feof (s_script));
      if (feof (s_script)) {
         DEBUG_YMACRO   yLOG_note    ("at end of script");
         ymacro_script__close ();
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(process line)-------------------*/
      fgets (x_recd, LEN_RECD, s_script);
      /*---(done with line)-----------------*/
      DEBUG_YMACRO   yLOG_value   ("feof"      , feof (s_script));
      if (feof (s_script) && strlen (x_recd) <= 0) {
         DEBUG_YMACRO   yLOG_note    ("at end of script");
         ymacro_script__close ();
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(process line)-------------------*/
      DEBUG_YMACRO   yLOG_value   ("line"      , s_line);
      ++s_line;
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      x_len = strlen (x_recd);
      /*---(check ignore status)------------*/
      if (strncmp (x_recd, ":skip"        ,  5) == 0)   yMACRO_skip   ();
      if (strncmp (x_recd, ":unskip"      ,  7) == 0)   yMACRO_unskip ();
      if (yMACRO_skipping ())   continue;
      /*---(filter comments/empties)--------*/
      if (x_recd [0] <  '\0') {
         DEBUG_YMACRO   yLOG_note    ("empty line, skipping");
         continue;
      }
      if (x_recd [0] <  ' ') {
         DEBUG_YMACRO   yLOG_note    ("blank leader, skipping");
         continue;
      }
      if (x_len >= 2 && x_recd [0] == '#') {
         if (strchr ("#!>@", x_recd [1]) != NULL) {
            DEBUG_YMACRO   yLOG_note    ("comment leader, skipping");
            continue;
         }
      }
      /*---(fix end-of-line)----------------*/
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      DEBUG_YMACRO   yLOG_info    ("x_recd"    , x_recd);
      /*---(functions)----------------------*/
      if (strncmp (x_recd, "macro ", 6) == 0) {
         rc = ymacro_rec_full (x_recd + 6);
         DEBUG_YMACRO   yLOG_value   ("macro"     , rc);
         if (rc < 0) {
            DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      /*---(normal)-------------------------*/
      else {
         sprintf (x_ready, ".=%s", x_recd);
         DEBUG_YMACRO   yLOG_info    ("current"   , x_ready);
         rc = ymacro_rec_full (x_ready);
         DEBUG_YMACRO   yLOG_value   ("normal"    , rc);
         if (rc < 0) {
            DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         rc = ymacro_exe_beg  (s_style);
         DEBUG_YMACRO   yLOG_value   ("execute"   , rc);
         if (rc < 0) {
            DEBUG_YMACRO   yLOG_note    ("can not execute");
            DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         break;
      }
      /*---(done)---------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_script_next      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(quick re-route)-----------------*/
   if (myMACRO.ename == ' ') {
      rc = ymacro_agrios_next ();
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(clear mode)-----*/
   ymacro_set2stop ();
   /*---(check next)-----*/
   rc = ymacro_script__read ();
   if (rc < 0) {
      DEBUG_YMACRO   yLOG_note    ("full script complete");
      ymacro_exe__done ();
   } else {
      DEBUG_YMACRO   yLOG_note    ("script line complete");
      /*> myMACRO.estack [0] = '\0';                                                  <*/
      /*> myMACRO.edepth     = 0;                                                     <*/
   }
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitz"   , myMACRO.blitz);
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitzing", myMACRO.blitzing);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ymacro_script__start    (char *a_name, char a_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   rc = ymacro_script__open (a_name);
   DEBUG_YMACRO   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_style == '!') {
      /*> yvikeys_sizes_switch ("status", "script");                                  <*/
      a_style = '.';
   }
   s_style = a_style;
   DEBUG_YMACRO   yLOG_char    ("s_style"   , s_style);
   if (myMACRO.blitz == 'y')  myMACRO.blitzing = 'y';
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitz"   , myMACRO.blitz);
   DEBUG_YMACRO   yLOG_char    ("myMACRO.blitzing", myMACRO.blitzing);
   rc = ymacro_script__read ();
   DEBUG_YMACRO   yLOG_value   ("read"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yMACRO_script_start     (char *a_name) { return ymacro_script__start (a_name, '.'); }
char yMACRO_script_follow    (char *a_name) { return ymacro_script__start (a_name, '!'); }
char yMACRO_script_playback  (char *a_name) { return ymacro_script__start (a_name, ','); }
char yMACRO_script_blitz     (char *a_name) { myMACRO.blitz  = 'y';  return ymacro_script__start (a_name, '.'); }

