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
static  char   s_dblitz =  '?';
static  char   s_dsaved =  '?';
static  char   s_bsaved =  '?';

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
   else                                     ystrlcpy (x_name, a_name, LEN_HUND);
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
   ystrlcpy (s_name, x_name, LEN_DESC);
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
   ystrlcpy (s_name, "", LEN_DESC);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ymacro_script__temp     (char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rcf         =    0;
   int         l           =    0;
   char       *p           = NULL;
   char       *q           = " ";
   char       *r           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char        x_name      [LEN_PATH]  = "/tmp/screen_print.scrn";
   char        c           =   0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_recd"    , a_recd);
   l = strlen (a_recd);
   DEBUG_YMACRO   yLOG_value   ("l"         , l);
   /*---(DEPRICATED)---------------------*/
   if (strncmp (a_recd, ":skip"        ,  5) == 0) {
      DEBUG_YMACRO   yLOG_note    ("handling :skip");
      yMACRO_skip   ();
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   if (strncmp (a_recd, ":unskip"      ,  7) == 0) {
      DEBUG_YMACRO   yLOG_note    ("handling :unskip");
      yMACRO_unskip ();
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(quick-out)----------------------*/
   if (strncmp (a_recd, "#<", 2) != 0) {
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(skipping sections)--------------*/
   if (rcf == 0 && strncmp (a_recd, "#<<< SKIP"       ,  9) == 0) {
      DEBUG_YMACRO   yLOG_note    ("handling SKIP");
      yMACRO_skip   ();
      rcf = 1;
   }
   if (rcf == 0 && strncmp (a_recd, "#<<< UNSKIP"     , 11) == 0) {
      DEBUG_YMACRO   yLOG_note    ("handling UNSKIP");
      yMACRO_unskip ();
      rcf = 1;
   }
   /*---(blitzing between markers)-------*/
   if (rcf == 0 && strncmp (a_recd, "#<<< BLITZ"      , 10) == 0) {
      DEBUG_YMACRO   yLOG_note    ("handling BLITZ");
      if (s_dsaved != '?') {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      s_dsaved = myMACRO.edelay;
      s_dblitz = myMACRO.blitz;
      yMACRO_edelay ('0');
      myMACRO.blitz = 'Y';
      rcf = 1;
   }
   --rce;  if (rcf == 0 && strncmp (a_recd, "#<<< UNBLITZ"    , 12) == 0) {
      DEBUG_YMACRO   yLOG_note    ("handling UNBLITZ");
      if (s_dsaved == '?') {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yMACRO_edelay (s_dsaved);
      myMACRO.blitz = s_dblitz;
      s_dsaved = '?';
      s_dblitz = '?';
      rcf = 1;
   }
   /*---(screen prints)------------------*/
   --rce;  if (rcf == 0 && strncmp (a_recd, "#<<< SCREEN_PRINT" , 17) == 0) {
      DEBUG_YMACRO   yLOG_note    ("handling SCREEN_PRINT");
      if (myMACRO.e_drawer  != NULL) {
         DEBUG_YMACRO   yLOG_note    ("update drawing");
         rc = myMACRO.e_drawer ();
      }
      if (myMACRO.e_printer == NULL) {
         DEBUG_YMACRO   yLOG_note    ("no screen printer configured");
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ystrlcpy  (x_recd, a_recd + 17, LEN_PATH);
      p = strtok_r (x_recd, q, &r);
      if (p != 0)  {
            ystrlcpy  (x_name, p,         LEN_PATH);
            ystrltrim (x_name, ySTR_BOTH, LEN_PATH);
      }
      DEBUG_YMACRO   yLOG_value   ("c"         , c);
      DEBUG_YMACRO   yLOG_info    ("x_name"    , x_name);
      rc = myMACRO.e_printer (x_name);
      if (rc < 0) {
         DEBUG_YMACRO   yLOG_note    ("screen printer failed");
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rcf = 1;
   }
   /*---(trouble)------------------------*/
   DEBUG_YMACRO   yLOG_value   ("rcf"      , rcf);
   --rce;  if (rcf == 0) {
      DEBUG_YMACRO   yLOG_note    ("no handler found for control");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return rcf;
}

char
ymacro_script__braces   (char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(quick-out)----------------------*/
   if (a_recd != NULL && strchr ("{}", a_recd [0]) == NULL)   return 0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_recd"    , a_recd);
   /*---(handle)-------------------------*/
   --rce;  switch (a_recd [0]) {
   case '{'  :
      DEBUG_YMACRO   yLOG_note    ("beg braced {");
      if (s_bsaved != '?') {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      s_bsaved = myMACRO.edelay;
      DEBUG_YMACRO   yLOG_value   ("s_bsaved"  , s_bsaved);
      yMACRO_edelay ('0');
      break;
   case '}'  :
      DEBUG_YMACRO   yLOG_note    ("end braced }");
      DEBUG_YMACRO   yLOG_value   ("s_bsaved"  , s_bsaved);
      if (s_bsaved == '?') {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yMACRO_edelay (s_bsaved);
      s_bsaved = '?';
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 1;
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
      ystrlcpy (x_recd, "", LEN_RECD); /* clear it */
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
      ystrltrim (x_recd, ySTR_BOTH, LEN_RECD);
      x_len = strlen (x_recd);
      /*---(fix end-of-line)----------------*/
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      DEBUG_YMACRO   yLOG_info    ("x_recd"    , x_recd);
      /*---(handle controls)----------------*/
      rc = ymacro_script__temp (x_recd);
      if (rc == 1)              continue;
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
      if (x_recd [0] == '#') {
         DEBUG_YMACRO   yLOG_note    ("comment leader, skipping");
         continue;
      }
      /*---(lightning speed)----------------*/
      rc = ymacro_script__braces (x_recd);
      if (rc == 1)              continue;
      /*> switch (x_recd [0]) {                                                       <* 
       *> case '{'  :                                                                 <* 
       *>    DEBUG_YMACRO   yLOG_note    ("beg braced {");                            <* 
       *>    s_bsaved = myMACRO.edelay;                                               <* 
       *>    DEBUG_YMACRO   yLOG_value   ("s_bsaved"  , s_bsaved);                    <* 
       *>    yMACRO_edelay ('0');                                                     <* 
       *>    continue;                                                                <* 
       *>    break;                                                                   <* 
       *> case '}'  :                                                                 <* 
       *>    DEBUG_YMACRO   yLOG_note    ("end braced }");                            <* 
       *>    DEBUG_YMACRO   yLOG_value   ("s_bsaved"  , s_bsaved);                    <* 
       *>    yMACRO_edelay (s_bsaved);                                                <* 
       *>    continue;                                                                <* 
       *>    break;                                                                   <* 
       *> }                                                                           <*/
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
         rc = ymacro_exe_beg  ('.', s_style);
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
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_name"    , a_name);
   rc = ymacro_script__open (a_name);
   DEBUG_YMACRO   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_char    ("a_style"   , a_style);
   if (a_style == '!') {
      /*> yvikeys_sizes_switch ("status", "script");                                  <*/
      a_style = '.';
   }
   s_style = a_style;
   DEBUG_YMACRO   yLOG_char    ("s_style"   , s_style);
   yMACRO_unskip ();
   DEBUG_YMACRO   yLOG_char    ("ignore"    , myMACRO.ignore);
   if (strchr ("Yy", myMACRO.blitz) != NULL)  myMACRO.blitzing = 'y';
   DEBUG_YMACRO   yLOG_char    ("blitz"     , myMACRO.blitz);
   DEBUG_YMACRO   yLOG_char    ("blitzing"  , myMACRO.blitzing);
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
char yMACRO_script_rapido    (char *a_name) { myMACRO.blitz  = 'y';  return ymacro_script__start (a_name, '.'); }
char yMACRO_script_blitz     (char *a_name) { myMACRO.blitz  = 'Y';  return ymacro_script__start (a_name, '.'); }

