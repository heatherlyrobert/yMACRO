/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



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
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_value   ("g_rcurr"    , g_rcurr);
   --rce;  if (g_rcurr < 0) {
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free existing)------------------*/
   ymacro_clear (g_rname);
   /*---(save to macro)------------------*/
   if (g_rlen == 0)   g_macros [g_rcurr].keys  = g_stub;
   else               g_macros [g_rcurr].keys  = strdup (g_rkeys);
   g_macros [g_rcurr].len   = strlen (g_rkeys);
   /*---(trim)---------------------------*/
   strlcpy (x_keys, g_rkeys, LEN_RECD);
   x_len = strlen (x_keys);
   if (x_len > 0)  x_keys [--x_len] = G_KEY_NULL;
   /*---(save gyges)---------------------*/
   if (s_saver != NULL)  s_saver (g_rname, x_keys);
   /*---(clear)--------------------------*/
   yMACRO_zero  ();
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
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
   if (g_ename == '.')  return 0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(prefetch)--------------------*/
   if (s_loader != NULL) {
      DEBUG_SCRP   yLOG_value   ("g_ecurr"   , g_ecurr);
      DEBUG_SCRP   yLOG_char    ("g_ename"   , g_ename);
      ymacro_wipe (g_ename);
      s_loader (g_ename, g_macros [g_ecurr].keys);
      if (g_macros [g_ecurr].keys != NULL) {
         g_macros [g_ecurr].len = strlen (g_macros [g_ecurr].keys);
         x_ch = g_macros [g_ecurr].keys [g_macros [g_ecurr].len - 1];
         if (x_ch != G_CHAR_HALT)  g_macros [g_ecurr].keys [g_macros [g_ecurr].len++] = G_CHAR_HALT;
         g_macros [g_ecurr].keys [g_macros [g_ecurr].len  ] = G_KEY_NULL;
      } else {
         g_macros [g_ecurr].len = 0;
      }
   }
   /*---(information)-----------------*/
   DEBUG_SCRP   yLOG_info    ("macro"     , g_macros [g_ecurr].keys);
   DEBUG_SCRP   yLOG_value   ("len"       , g_macros [g_ecurr].len);
   /*---(set globals)-----------------*/
   if (g_macros [g_ecurr].pos < 0)  g_macros [g_ecurr].cur = 0;
   else                             g_macros [g_ecurr].cur = g_macros [g_ecurr].keys [g_macros [g_ecurr].pos];
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
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
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_OUTP   yLOG_note    ("can not execute until operational");
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear output)-------------------*/
   yPARSE_outclear  ();
   /*---(defense)------------------------*/
   DEBUG_OUTP   yLOG_char    ("a_abbr"    , a_abbr);
   n  = ymacro_index (a_abbr);
   DEBUG_OUTP   yLOG_char    ("index"     , n);
   --rce; if (n  < 0) { 
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(label)--------------------------*/
   DEBUG_OUTP   yLOG_value   ("len"       , g_macros [n].len);
   if (g_macros [n].len <= 0)  {
      DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(keys)---------------------------*/
   strlcpy (x_keys, g_macros [n].keys, LEN_RECD);
   x_keys [g_macros [n].len - 1] = G_KEY_NULL;
   /*---(write)-----------------------*/
   yPARSE_vprintf (c, "macro", a_abbr, x_keys);
   /*---(complete)-----------------------*/
   DEBUG_OUTP  yLOG_exit    (__FUNCTION__);
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
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_OUTP   yLOG_note    ("can not execute until operational");
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
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
   DEBUG_OUTP  yLOG_exit    (__FUNCTION__);
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
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (SMOD_MACRO)) {
      DEBUG_INPT   yLOG_note    ("can not execute until operational");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(label)--------------------------*/
   rc = yPARSE_popchar (&x_abbr);
   DEBUG_INPT   yLOG_value   ("pop abbr"  , rc);
   DEBUG_INPT   yLOG_char    ("abbr"      , x_abbr);
   m  = ymacro_index (x_abbr);
   DEBUG_INPT   yLOG_char    ("m"         , m);
   --rce; if (m < 0) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get command)--------------------*/
   rc = yPARSE_popstr (x_keys);
   DEBUG_INPT   yLOG_value   ("pop keys"  , rc);
   DEBUG_INPT   yLOG_info    ("x_keys"    , x_keys);
   /*---(save)---------------------------*/
   DEBUG_INPT   yLOG_note    ("saving values");
   ymacro_clear (x_abbr);
   if (x_keys [strlen (x_keys) - 1] != '�')   strlcat (x_keys, "�"   , LEN_RECD );
   g_macros [m].keys = strdup (x_keys);
   g_macros [m].len  = strlen (x_keys);
   if (s_saver != NULL)  s_saver (x_abbr, x_keys);
   /*---(complete)-----------------------*/
   DEBUG_INPT  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yMACRO_export           (char a_id)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rce         =  -10;                                                <* 
    *> char        rc          =    0;                                                <* 
    *> char        n           =   -1;                                                <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(defense)------------------------+/                                       <* 
    *> n = yvikeys_macro__index (a_id);                                               <* 
    *> --rce;  if (n <  0)  {                                                         <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> /+---(write)--------------------------+/                                       <* 
    *> rc = yvikeys_dump_write (s_macros [n].keys);                                   <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return rc;                                                                     <*/
}

char
yMACRO_import           (char a_id)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rce         =  -10;                                                <* 
    *> char        rc          =    0;                                                <* 
    *> char        x_recd      [LEN_RECD];                                            <* 
    *> char        x_direct    [LEN_RECD];                                            <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(read)---------------------------+/                                       <* 
    *> rc = yvikeys_dump_read  (0, x_recd, NULL);                                     <* 
    *> DEBUG_SCRP   yLOG_value   ("read"      , rc);                                  <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> DEBUG_SCRP   yLOG_info    ("x_recd"    , x_recd);                              <* 
    *> /+---(add)----------------------------+/                                       <* 
    *> sprintf (x_direct, "%c=%s", a_id, x_recd);                                     <* 
    *> DEBUG_SCRP   yLOG_info    ("x_direct"  , x_direct);                            <* 
    *> rc = yvikeys_macro__recdir (a_id, x_direct);                                   <* 
    *> DEBUG_SCRP   yLOG_value   ("recdir"    , rc);                                  <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return rc;                                                                     <*/
}

char
yMACRO_copy             (char a_id, char a_src)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rce         =  -10;                                                <* 
    *> char        rc          =    0;                                                <* 
    *> char        s           =   -1;                                                <* 
    *> char        x_recd      [LEN_RECD];                                            <* 
    *> int         x_len       =    0;                                                <* 
    *> char        x_direct    [LEN_RECD];                                            <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(defense)------------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_char    ("a_id"      , a_id);                                <* 
    *> DEBUG_SCRP   yLOG_char    ("a_src"     , a_src);                               <* 
    *> s = yvikeys_macro__index (a_src);                                              <* 
    *> DEBUG_SCRP   yLOG_value   ("s"         , s);                                   <* 
    *> --rce;  if (s <  0) {                                                          <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> /+---(copy)---------------------------+/                                       <* 
    *> strlcpy (x_recd, s_macros [s].keys, LEN_RECD);                                 <* 
    *> x_len = strlen (x_recd);                                                       <* 
    *> DEBUG_SCRP   yLOG_value   ("x_len"     , x_len);                               <* 
    *> --rce;  if (x_len <=  0) {                                                     <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> DEBUG_SCRP   yLOG_char    ("tail"      , chrvisible (x_recd [x_len - 1]));     <* 
    *> if (x_recd [x_len - 1] == '�' )  x_recd [--x_len] = '\0';                      <* 
    *> sprintf (x_direct, "%c=%s", a_id, x_recd);                                     <* 
    *> DEBUG_SCRP   yLOG_info    ("x_direct"  , x_direct);                            <* 
    *> rc = yvikeys_macro__recdir (a_id, x_direct);                                   <* 
    *> DEBUG_SCRP   yLOG_value   ("recdir"    , rc);                                  <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return rc;                                                                     <*/
}

char
yMACRO_to_reg           (char a_id, char a_reg)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rce         =  -10;                                                <* 
    *> char        rc          =    0;                                                <* 
    *> char        n           =   -1;                                                <* 
    *> char        x_recd      [LEN_RECD];                                            <* 
    *> int         x_len       =    0;                                                <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(defense)------------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_char    ("a_id"      , a_id);                                <* 
    *> n = yvikeys_macro__index (a_id);                                               <* 
    *> DEBUG_SCRP   yLOG_value   ("n"         , n);                                   <* 
    *> --rce;  if (n <  0) {                                                          <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> /+---(copy)---------------------------+/                                       <* 
    *> strlcpy (x_recd, s_macros [n].keys, LEN_RECD);                                 <* 
    *> x_len = strlen (x_recd);                                                       <* 
    *> DEBUG_SCRP   yLOG_value   ("x_len"     , x_len);                               <* 
    *> --rce;  if (x_len <=  0) {                                                     <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> DEBUG_SCRP   yLOG_char    ("tail"      , chrvisible (x_recd [x_len - 1]));     <* 
    *> if (x_recd [x_len - 1] == '�' )  x_recd [--x_len] = '\0';                      <* 
    *> rc = yvikeys_sreg_push       (a_reg, x_recd);                                  <* 
    *> DEBUG_SCRP   yLOG_value   ("push"      , rc);                                  <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return rc;                                                                     <*/
}

char
yMACRO_from_reg         (char a_id, char a_reg)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rce         =  -10;                                                <* 
    *> char        rc          =    0;                                                <* 
    *> char        x_recd      [LEN_RECD];                                            <* 
    *> int         x_len       =    0;                                                <* 
    *> char        x_direct    [LEN_RECD];                                            <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(defense)------------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_char    ("a_id"      , a_id);                                <* 
    *> /+---(copy)---------------------------+/                                       <* 
    *> rc = yvikeys_sreg_pop        (a_reg, x_recd);                                  <* 
    *> DEBUG_SCRP   yLOG_value   ("pop"       , rc);                                  <* 
    *> --rce;  if (rc <   0) {                                                        <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> sprintf (x_direct, "%c=%s", a_id, x_recd);                                     <* 
    *> DEBUG_SCRP   yLOG_info    ("x_direct"  , x_direct);                            <* 
    *> rc = yvikeys_macro__recdir (a_id, x_direct);                                   <* 
    *> DEBUG_SCRP   yLOG_value   ("recdir"    , rc);                                  <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return rc;                                                                     <*/
}

char
yMACRO_central          (char a_id, char *a_string)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                    <* 
    *> char        rce         =  -10;                                                             <* 
    *> char        rc          =    0;                                                             <* 
    *> FILE       *f           = NULL;                                                             <* 
    *> char        x_recd      [LEN_RECD];                                                         <* 
    *> char        x_seek      [LEN_RECD];                                                         <* 
    *> char        x_key       [LEN_RECD];                                                         <* 
    *> int         x_len       =    0;                                                             <* 
    *> char        x_direct    [LEN_RECD];                                                         <* 
    *> char        x_found     =  '-';                                                             <* 
    *> int         c           =    0;                                                             <* 
    *> char       *p           = NULL;                                                             <* 
    *> /+---(header)-------------------------+/                                                    <* 
    *> DEBUG_SCRP   yLOG_enter   (__FUNCTION__);                                                   <* 
    *> /+---(prepare)------------------------+/                                                    <* 
    *> strlcpy (x_seek, a_string + 2, 42);                                                         <* 
    *> x_len = strlen (x_seek);                                                                    <* 
    *> DEBUG_SCRP   yLOG_info    ("x_seek"    , x_seek);                                           <* 
    *> /+---(read)---------------------------+/                                                    <* 
    *> f = fopen (FILE_REPO, "r");                                                                 <* 
    *> DEBUG_SCRP   yLOG_point   ("f"         , f);                                                <* 
    *> --rce;  if (f == NULL) {                                                                    <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
    *>    return rce;                                                                              <* 
    *> }                                                                                           <* 
    *> --rce;  while (x_found == '-') {                                                            <* 
    *>    if (feof (f)) {                                                                          <* 
    *>       DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>       return rce;                                                                           <* 
    *>    }                                                                                        <* 
    *>    fgets (x_recd, LEN_RECD, f);                                                             <* 
    *>    ++c;                                                                                     <* 
    *>    if (x_recd [0] == '\0')         continue;                                                <* 
    *>    if (x_recd [0] == '\n')         continue;                                                <* 
    *>    if (x_recd [0] == '#')          continue;                                                <* 
    *>    if (x_recd [0] == ' ')          continue;                                                <* 
    *>    DEBUG_SCRP   yLOG_info    ("x_recd"    , x_recd);                                        <* 
    *>    if (x_recd [0] != x_seek [0])  continue;                                                 <* 
    *>    if (x_len == 6)  sprintf (x_key, "%2.2s%2.2s%2.2s", x_recd, x_recd + 15, x_recd + 30);   <* 
    *>    else {                                                                                   <* 
    *>       strlcpy  (x_key, x_recd, 42);                                                         <* 
    *>       strldchg (x_key, '', '.', LEN_RECD);                                                 <* 
    *>       strltrim (x_key, ySTR_MAX, LEN_RECD);                                                 <* 
    *>    }                                                                                        <* 
    *>    DEBUG_SCRP   yLOG_info    ("x_key"     , x_key);                                         <* 
    *>    if (strcmp (x_seek, x_key) != 0)  continue;                                              <* 
    *>    x_found = 'y';                                                                           <* 
    *> }                                                                                           <* 
    *> fclose (f);                                                                                 <* 
    *> DEBUG_SCRP   yLOG_value   ("c"         , c);                                                <* 
    *> DEBUG_SCRP   yLOG_char    ("x_found"   , x_found);                                          <* 
    *> --rce;  if (x_found != 'y') {                                                               <* 
    *>    DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
    *>    return rce;                                                                              <* 
    *> }                                                                                           <* 
    *> p = x_recd + 98;                                                                            <* 
    *> x_len = strlen (p);                                                                         <* 
    *> DEBUG_SCRP   yLOG_value   ("x_len"     , x_len);                                            <* 
    *> DEBUG_SCRP   yLOG_char    ("tail"      , chrvisible (p [x_len - 1]));                       <* 
    *> if (p [x_len - 1] == '\n')  p [--x_len] = '\0';                                             <* 
    *> DEBUG_SCRP   yLOG_char    ("tail"      , chrvisible (p [x_len - 1]));                       <* 
    *> if (p [x_len - 1] == '�' )  p [--x_len] = '\0';                                             <* 
    *> DEBUG_SCRP   yLOG_info    ("p"         , p);                                                <* 
    *> sprintf (x_direct, "%c=%s", a_id, p);                                                       <* 
    *> DEBUG_SCRP   yLOG_info    ("x_direct"  , x_direct);                                         <* 
    *> rc = yvikeys_macro__recdir (a_id, x_direct);                                                <* 
    *> DEBUG_SCRP   yLOG_value   ("recdir"    , rc);                                               <* 
    *> /+---(complete)-----------------------+/                                                    <* 
    *> DEBUG_SCRP   yLOG_exit    (__FUNCTION__);                                                   <* 
    *> return rc;                                                                                  <*/
}

