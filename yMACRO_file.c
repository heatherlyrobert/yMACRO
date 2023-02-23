/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
ymacro_file_handlers    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(handlers)-----------------------*/
   rc = yPARSE_handler_max (SMOD_MACRO   , "macro"     , 7.3, "cO----------", -1, yMACRO_reader, yMACRO_writer, "------------" , "a,keys", "keyboard macros"           );
   DEBUG_YMACRO   yLOG_value   ("macro"     , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       saving and fetching                    ----===*/
/*====================------------------------------------====================*/
static void  o___SAVING__________o () { return; }

char         /*-> save current recording -------------[ ------ [ge.631.052.22]*/ /*-[01.0000.014.4]-*/ /*-[--.---.---.--]-*/
ymacro_save             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char        x_keys      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_value   ("myMACRO.rcurr"    , myMACRO.rcurr);
   --rce;  if (myMACRO.rcurr < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free existing)------------------*/
   ymacro_clear (myMACRO.rname);
   /*> ymacro_reset (myMACRO.rname);                                                  <*/
   /*---(save to macro)------------------*/
   if (myMACRO.rlen == 0)   g_macros [myMACRO.rcurr].keys  = g_stub;
   else                     g_macros [myMACRO.rcurr].keys  = strdup (myMACRO.rkeys);
   g_macros [myMACRO.rcurr].len   = strlen (myMACRO.rkeys);
   /*---(trim)---------------------------*/
   strlcpy (x_keys, myMACRO.rkeys, LEN_RECD);
   x_len = strlen (x_keys);
   if (x_len > 0)  x_keys [--x_len] = G_KEY_NULL;
   /*---(save gyges)---------------------*/
   if (myMACRO.e_saver != NULL)  myMACRO.e_saver (myMACRO.rname, x_keys);
   /*---(clear)--------------------------*/
   yMACRO_zero  ();
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> fetch specific macro keystrokes ----[ ------ [ge.A52.134.63]*/ /*-[01.0000.023.#]-*/ /*-[--.---.---.--]-*/
ymacro_fetch             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_ch        =  ' ';
   char        x_index     =    0;
   /*---(quick out)----------------------*/
   if (myMACRO.ename == '.')  return 0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(prefetch)--------------------*/
   if (myMACRO.e_loader != NULL) {
      DEBUG_YMACRO   yLOG_value   ("ecurr"    , myMACRO.ecurr);
      DEBUG_YMACRO   yLOG_char    ("ename"     , myMACRO.ename);
      /*> ymacro_wipe  (myMACRO.ename);                                               <*/
      ymacro_reset (myMACRO.ename);
      myMACRO.e_loader (myMACRO.ename, g_macros [myMACRO.ecurr].keys);
      if (g_macros [myMACRO.ecurr].keys != NULL) {
         g_macros [myMACRO.ecurr].len = strlen (g_macros [myMACRO.ecurr].keys);
         x_ch = g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].len - 1];
         if (x_ch != G_CHAR_HALT)  g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].len++] = G_CHAR_HALT;
         g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].len  ] = G_KEY_NULL;
      } else {
         g_macros [myMACRO.ecurr].len = 0;
      }
   }
   /*---(information)-----------------*/
   DEBUG_YMACRO   yLOG_info    ("macro"     , g_macros [myMACRO.ecurr].keys);
   DEBUG_YMACRO   yLOG_value   ("len"       , g_macros [myMACRO.ecurr].len);
   /*---(set globals)-----------------*/
   if (g_macros [myMACRO.ecurr].pos < 0)  g_macros [myMACRO.ecurr].cur = 0;
   else                             g_macros [myMACRO.ecurr].cur = g_macros [myMACRO.ecurr].keys [g_macros [myMACRO.ecurr].pos];
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      reading and writing                     ----===*/
/*====================------------------------------------====================*/
static void  o___FILE____________o () { return; }

char         /*-> tbd --------------------------------[ ------ [ge.732.124.21]*/ /*-[02.0000.01#.#]-*/ /*-[--.---.---.--]-*/
ymacro__writer          (int c, uchar a_abbr)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   char        x_keys      [LEN_RECD ];
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_YMACRO   yLOG_note    ("can not execute until operational");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear output)-------------------*/
   yPARSE_outclear  ();
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_abbr"    , a_abbr);
   n  = ymacro_index (a_abbr);
   DEBUG_YMACRO   yLOG_value   ("index"     , n);
   --rce; if (n  < 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(label)--------------------------*/
   DEBUG_YMACRO   yLOG_value   ("len"       , g_macros [n].len);
   if (g_macros [n].len <= 0)  {
      DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(keys)---------------------------*/
   strlcpy (x_keys, g_macros [n].keys, LEN_RECD);
   x_keys [g_macros [n].len - 1] = G_KEY_NULL;
   DEBUG_YMACRO   yLOG_info    ("x_keys"    , x_keys);
   /*---(write)-----------------------*/
   rc = yPARSE_vprintf (c, "macro", a_abbr, x_keys);
   DEBUG_YMACRO   yLOG_value   ("vprintf"   , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yMACRO_writer           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_end       =    0;
   int         i           =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_YMACRO   yLOG_note    ("can not execute until operational");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_end = strlen (S_MACRO_LIST);
   /*> yPARSE_verb_begin ("macro");                                                   <*/
   /*---(walk list)----------------------*/
   for (i = 0; i <= x_end; ++i) {
      rc = ymacro__writer (c, S_MACRO_LIST [i]);
      if (rc < 1)  continue;
      ++c;
      /*> yPARSE_verb_break (c);                                                      <*/
   }
   /*---(wrap-up)------------------------*/
   /*> yPARSE_verb_end   (c);                                                         <*/
   /*---(complete)-----------------------*/
   DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
   return c;
}

char
yMACRO_reader           (int n, char *a_verb)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -11;
   char        rc          =    0;
   char        x_verb      [LEN_LABEL];
   char        x_abbr      =    0;
   int         m           =    0;
   char        x_keys      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_YMACRO   yLOG_note    ("can not execute until operational");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_point   ("a_verb"    , a_verb);
   --rce;  if (a_verb == NULL || strcmp (a_verb, "macro") != 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_verb"    , a_verb);
   /*---(label)--------------------------*/
   rc = yPARSE_popchar (&x_abbr);
   DEBUG_YMACRO   yLOG_value   ("pop abbr"  , rc);
   DEBUG_YMACRO   yLOG_char    ("abbr"      , x_abbr);
   m  = ymacro_index (x_abbr);
   DEBUG_YMACRO   yLOG_char    ("m"         , m);
   --rce; if (m < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get command)--------------------*/
   rc = yPARSE_popstr (x_keys);
   DEBUG_YMACRO   yLOG_value   ("pop keys"  , rc);
   DEBUG_YMACRO   yLOG_info    ("x_keys"    , x_keys);
   /*---(save)---------------------------*/
   DEBUG_YMACRO   yLOG_note    ("saving values");
   ymacro_clear (x_abbr);
   if (x_keys [strlen (x_keys) - 1] != '³')   strlcat (x_keys, "³"   , LEN_RECD );
   g_macros [m].keys = strdup (x_keys);
   g_macros [m].len  = strlen (x_keys);
   if (myMACRO.e_saver != NULL)  myMACRO.e_saver (x_abbr, x_keys);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yMACRO_export           (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   n = ymacro_index (a_abbr);
   --rce;  if (n <  0)  {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write)--------------------------*/
   rc = strlexport (0, g_macros [n].keys);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yMACRO_import           (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD];
   char        x_direct    [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(read)---------------------------*/
   rc = strlimport  (0, x_recd, NULL);
   DEBUG_YMACRO   yLOG_value   ("read"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("x_recd"    , x_recd);
   /*---(add)----------------------------*/
   sprintf (x_direct, "%c=%s", a_abbr, x_recd);
   DEBUG_YMACRO   yLOG_info    ("x_direct"  , x_direct);
   rc = ymacro_rec_full (x_direct);
   DEBUG_YMACRO   yLOG_value   ("full"      , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yMACRO_yank             (char a_abbr, char *a_label)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_ch        =  ' ';
   char        x_index     =    0;
   char        x_keys      [LEN_RECD]  = "";
   int         l           =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_abbr"    , a_abbr);
   n  = ymacro_index (a_abbr);
   DEBUG_YMACRO   yLOG_value   ("index"     , n);
   --rce; if (n  < 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(label)-----------------------*/
   if (a_label == NULL || strcmp (a_label, "") == 0) {
      strlcpy (x_keys, "(cur)", LEN_LABEL);
   } else {
      strlcpy (x_keys, a_label, LEN_LABEL);
   }
   /*---(load)---------------------------*/
   if (myMACRO.e_saver  != NULL) {
      /*---(free up)---------------------*/
      if (g_macros [n].len > 0)   free (g_macros [n].keys);
      g_macros [n].keys = NULL;
      ymacro_reset (a_abbr);
      /*---(grab)------------------------*/
      myMACRO.e_saver  (a_abbr, x_keys);
      l = strlen (x_keys);
      x_ch = x_keys [l - 1];
      if (x_ch != G_CHAR_HALT)  x_keys [l++] = G_CHAR_HALT;
      x_keys [l] = G_KEY_NULL;
      g_macros [n].keys = strdup (x_keys);
      g_macros [n].len = strlen (g_macros [n].keys);
   }
   /*---(information)-----------------*/
   DEBUG_YMACRO   yLOG_info    ("macro"     , g_macros [n].keys);
   DEBUG_YMACRO   yLOG_value   ("len"       , g_macros [n].len);
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_paste            (char a_abbr, char *a_label)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_ch        =  ' ';
   char        x_index     =    0;
   char        x_keys      [LEN_RECD]  = "";
   int         l           =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_abbr"    , a_abbr);
   n  = ymacro_index (a_abbr);
   DEBUG_YMACRO   yLOG_value   ("index"     , n);
   --rce; if (n  < 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(label)-----------------------*/
   if (a_label == NULL || strcmp (a_label, "") == 0) {
      strlcpy (x_keys, "(cur)", LEN_LABEL);
   } else {
      strlcpy (x_keys, a_label, LEN_LABEL);
   }
   /*---(load)---------------------------*/
   if (myMACRO.e_loader != NULL) {
      /*---(free up)---------------------*/
      /*> if (g_macros [n].len > 0)   free (g_macros [n].keys);                       <*/
      myMACRO.e_loader (a_abbr, x_keys);
   }
   /*---(information)-----------------*/
   DEBUG_YMACRO   yLOG_info    ("macro"     , g_macros [n].keys);
   DEBUG_YMACRO   yLOG_value   ("len"       , g_macros [n].len);
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;

}

char
yMACRO_copy             (char a_src, char a_dst)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =   -1;
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   char        x_direct    [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_dst"     , a_dst);
   DEBUG_YMACRO   yLOG_char    ("a_src"     , a_src);
   n = ymacro_index (a_src);
   DEBUG_YMACRO   yLOG_value   ("n"         , n);
   --rce;  if (n <  0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy)---------------------------*/
   strlcpy (x_recd, g_macros [n].keys, LEN_RECD);
   x_len = strlen (x_recd);
   DEBUG_YMACRO   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <=  0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_char    ("tail"      , chrvisible (x_recd [x_len - 1]));
   if (x_recd [x_len - 1] == '³' )  x_recd [--x_len] = '\0';
   sprintf (x_direct, "%c=%s", a_dst, x_recd);
   DEBUG_YMACRO   yLOG_info    ("x_direct"  , x_direct);
   rc = ymacro_rec_full   (x_direct);
   DEBUG_YMACRO   yLOG_value   ("rec_full"  , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yMACRO_to_sreg          (char a_abbr, char a_reg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =   -1;
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_abbr"      , a_abbr);
   n = ymacro_index (a_abbr);
   DEBUG_YMACRO   yLOG_value   ("n"         , n);
   --rce;  if (n <  0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy)---------------------------*/
   strlcpy (x_recd, g_macros [n].keys, LEN_RECD);
   x_len = strlen (x_recd);
   DEBUG_YMACRO   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <=  0) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_char    ("tail"      , chrvisible (x_recd [x_len - 1]));
   if (x_recd [x_len - 1] == '³' )  x_recd [--x_len] = '\0';
   rc = yVIHUB_ySRC_push (a_reg, x_recd);
   DEBUG_YMACRO   yLOG_value   ("push"      , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yMACRO_central          (char a_abbr, char *a_string)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD];
   char        x_seek      [LEN_RECD];
   char        x_key       [LEN_RECD];
   int         x_len       =    0;
   char        x_direct    [LEN_RECD];
   char        x_found     =  '-';
   int         c           =    0;
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   strlcpy (x_seek, a_string + 2, 42);
   x_len = strlen (x_seek);
   DEBUG_YMACRO   yLOG_info    ("x_seek"    , x_seek);
   /*---(read)---------------------------*/
   f = fopen (MACRO_REPO, "rt");
   DEBUG_YMACRO   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  while (x_found == '-') {
      if (feof (f)) {
         DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      fgets (x_recd, LEN_RECD, f);
      ++c;
      if (x_recd [0] == '\0')         continue;
      if (x_recd [0] == '\n')         continue;
      if (x_recd [0] == '#')          continue;
      if (x_recd [0] == ' ')          continue;
      DEBUG_YMACRO   yLOG_info    ("x_recd"    , x_recd);
      if (x_recd [0] != x_seek [0])  continue;
      if (x_len == 6)  sprintf (x_key, "%2.2s%2.2s%2.2s", x_recd, x_recd + 15, x_recd + 30);
      else {
         strlcpy  (x_key, x_recd, 42);
         strldchg (x_key, '', '.', LEN_RECD);
         strltrim (x_key, ySTR_MAX, LEN_RECD);
      }
      DEBUG_YMACRO   yLOG_info    ("x_key"     , x_key);
      if (strcmp (x_seek, x_key) != 0)  continue;
      x_found = 'y';
   }
   fclose (f);
   DEBUG_YMACRO   yLOG_value   ("c"         , c);
   DEBUG_YMACRO   yLOG_char    ("x_found"   , x_found);
   --rce;  if (x_found != 'y') {
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p = x_recd + 98;
   x_len = strlen (p);
   DEBUG_YMACRO   yLOG_value   ("x_len"     , x_len);
   DEBUG_YMACRO   yLOG_char    ("tail"      , chrvisible (p [x_len - 1]));
   if (p [x_len - 1] == '\n')  p [--x_len] = '\0';
   DEBUG_YMACRO   yLOG_char    ("tail"      , chrvisible (p [x_len - 1]));
   if (p [x_len - 1] == '³' )  p [--x_len] = '\0';
   DEBUG_YMACRO   yLOG_info    ("p"         , p);
   sprintf (x_direct, "%c=%s", a_abbr, p);
   DEBUG_YMACRO   yLOG_info    ("x_direct"  , x_direct);
   rc = ymacro_rec_full (x_direct);
   DEBUG_YMACRO   yLOG_value   ("recdir"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return rc;
}


