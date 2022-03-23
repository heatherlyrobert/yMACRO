/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



static int   s_index         = 0;
static char  s_abbrs         [S_MACRO_MAX];

char
ymacro__flatten         (char a_lvl, char a_src, char *a_out)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_in        =    0;
   int         i           =    0;
   int         x_pos       =    0;
   char        x_sub       [LEN_LABEL];
   char        x_msg       [LEN_DESC];
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_value   ("a_lvl"     , a_lvl);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_src"     , a_src);
   x_in   = ymacro_index (a_src);
   DEBUG_YMACRO   yLOG_value   ("x_in"      , x_in);
   --rce; if (x_in < 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_point   ("a_out"     , a_out);
   --rce; if (a_out == NULL) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_info    ("a_out"     , a_out);
   myMACRO.rlen = strlen (a_out);
   DEBUG_YMACRO   yLOG_value   ("myMACRO.rlen"    , myMACRO.rlen);
   /*---(prefix)-------------------------*/
   DEBUG_YMACRO   yLOG_value   ("s_abbrs"   , s_abbrs [x_in]);
   if (s_abbrs [x_in] > 0) {
      DEBUG_YMACRO   yLOG_note    ("repeating macro");
      sprintf (x_sub, "¸@%d¹", s_abbrs [x_in]);
      strlcat (a_out, x_sub, LEN_RECD);
      myMACRO.rlen = strlen (a_out);
      DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prefix)-------------------------*/
   if (a_lvl > 0)  {
      DEBUG_YMACRO   yLOG_note    ("prefixing");
      strlcat (a_out, "¸", LEN_RECD);
      s_abbrs [x_in] = ++s_index;
      DEBUG_YMACRO   yLOG_value   ("s_abbrs"   , s_abbrs [x_in]);
      ++myMACRO.rlen;
      DEBUG_YMACRO   yLOG_value   ("myMACRO.rlen"    , myMACRO.rlen);
   }
   /*---(copy)---------------------------*/
   for (i = 0; i < g_macros [x_in].len; ++i) {
      DEBUG_YMACRO   yLOG_char    ("char"      , g_macros [x_in].keys [i]);
      if (g_macros [x_in].keys [i] == G_CHAR_HALT)  break;
      if (g_macros [x_in].keys [i] == '@') {
         rc = ymacro__flatten (a_lvl + 1, g_macros [x_in].keys [++i], a_out);
         DEBUG_YMACRO   yLOG_value   ("flatone"   , rc);
         if (rc < 0) {
            DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
            return rc;
         }
         continue;
      }
      a_out [myMACRO.rlen++]   = g_macros [x_in].keys [i];
      a_out [myMACRO.rlen]     = '\0';
      if (myMACRO.rlen < 30)  sprintf (x_msg, "[%s]", a_out);
      else              sprintf (x_msg, "<%s]", a_out + myMACRO.rlen - 30);
      DEBUG_YMACRO   yLOG_complex ("added"     , "%3d, %3d, %s", myMACRO.rlen, myMACRO.rlen, x_msg);
   }
   /*---(suffix)-------------------------*/
   if (a_lvl > 0)  {
      DEBUG_YMACRO   yLOG_note    ("suffixing");
      strlcat (a_out, "¹", LEN_RECD);
      ++myMACRO.rlen;
      DEBUG_YMACRO   yLOG_value   ("myMACRO.rlen"    , myMACRO.rlen);
   }
   /*---(complete)-----------------------*/
   DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_flatten_at       (uchar a_src, uchar a_dst)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        rc          =    0;
   char        x_src       =    0;
   char        x_dst       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(source)-------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_src"     , a_src);
   x_src  = ymacro_index (a_src);
   DEBUG_YMACRO   yLOG_value   ("x_src"     , x_src);
   --rce; if (x_src < 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_value   ("nkey"      , g_macros [x_src].len);
   --rce; if (g_macros [x_src].len <= 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(destination)--------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_dst"     , a_dst);
   x_dst  = ymacro_index (a_dst);
   DEBUG_YMACRO   yLOG_value   ("x_dst"     , x_dst);
   --rce; if (x_dst < 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ymacro_clear (a_dst);
   /*---(prepare)------------------------*/
   s_index = 0;
   for (i = 0; i < S_MACRO_MAX; ++i)  s_abbrs [i] = -1;
   DEBUG_YMACRO   yLOG_complex ("s_abbr"    , "%3d, %3d/%c %3d/%c %3d/%c %3d/%c %3d/%c", s_index, s_abbrs [0], S_MACRO_LIST [s_abbrs [0]], s_abbrs [1], S_MACRO_LIST [s_abbrs [1]], s_abbrs [2], S_MACRO_LIST [s_abbrs [2]], s_abbrs [3], S_MACRO_LIST [s_abbrs [3]], s_abbrs [4], S_MACRO_LIST [s_abbrs [4]]);
   /*---(clear)--------------------------*/
   myMACRO.rkeys [0] = '\0';
   myMACRO.rlen      = 0;
   /*---(call on main)-------------------*/
   rc = ymacro__flatten (0, a_src, myMACRO.rkeys);
   DEBUG_YMACRO   yLOG_value   ("flatone"   , rc);
   /*---(save)---------------------------*/
   strlcat (myMACRO.rkeys, "³"   , LEN_RECD );
   g_macros [x_dst].keys = strdup (myMACRO.rkeys);
   g_macros [x_dst].len  = strlen (myMACRO.rkeys);
   /*---(clear)--------------------------*/
   myMACRO.rkeys [0] = '\0';
   myMACRO.rlen      = 0;
   /*---(complete)-----------------------*/
   DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
   return rc;
}

char yMACRO_flatten  (uchar a_src) { return yMACRO_flatten_at (a_src, '0'); }

int
ymacro__install         (int a_lvl, int a_in, int a_len, int a_pos, int a_out)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_pos       =    0;
   int         x_len       =    0;
   uchar       x_sub       [LEN_LABEL];
   uchar       x_msg       [LEN_DESC];
   uchar       x_keys      [LEN_RECD];
   int         x_tmp       =    0;
   int         k           =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   DEBUG_YMACRO   yLOG_complex ("args"      , "%2dl, %2di, %2dl, %2dp, %2do", a_lvl, a_in, a_len, a_pos, a_out);
   for (i = a_pos; i < a_len; ++i) {
      DEBUG_YMACRO   yLOG_char    ("char"      , myMACRO.rkeys [i]);
      /*---(layering operator)-----------*/
      if (myMACRO.rkeys [i] == G_CHAR_SLPAREN) {
         /*---(repeat sub-macro call)----*/
         if (myMACRO.rkeys [i + 1] == '@') {
            DEBUG_YMACRO   yLOG_note    ("sub-macro repeat call");
            DEBUG_YMACRO   yLOG_complex ("s_abbr"    , "%3d, %3d/%c %3d/%c %3d/%c %3d/%c %3d/%c", s_index, s_abbrs [0], S_MACRO_LIST [s_abbrs [0]], s_abbrs [1], S_MACRO_LIST [s_abbrs [1]], s_abbrs [2], S_MACRO_LIST [s_abbrs [2]], s_abbrs [3], S_MACRO_LIST [s_abbrs [3]], s_abbrs [4], S_MACRO_LIST [s_abbrs [4]]);
            k     = s_abbrs [myMACRO.rkeys [i + 2] - '0'];
            DEBUG_YMACRO   yLOG_complex ("current"   , "%3d %3d %3d %c", myMACRO.rkeys [i + 2], myMACRO.rkeys [i + 2] - '0', k, S_MACRO_LIST [k]);
            sprintf (x_sub, "@%c", S_MACRO_LIST [k]);
            strlcat (x_keys, x_sub, LEN_RECD);
            x_len = strlen (x_keys);
            i += 3;
         }
         /*---(create new sub-macro)-----*/
         else {
            DEBUG_YMACRO   yLOG_note    ("sub-macro first call");
            ++s_index;
            s_abbrs [s_index] = s_abbrs [s_index - 1] + 1;
            DEBUG_YMACRO   yLOG_complex ("s_abbr"    , "%3d, %3d/%c %3d/%c %3d/%c %3d/%c %3d/%c", s_index, s_abbrs [0], S_MACRO_LIST [s_abbrs [0]], s_abbrs [1], S_MACRO_LIST [s_abbrs [1]], s_abbrs [2], S_MACRO_LIST [s_abbrs [2]], s_abbrs [3], S_MACRO_LIST [s_abbrs [3]], s_abbrs [4], S_MACRO_LIST [s_abbrs [4]]);
            i = ymacro__install (a_lvl + 1, a_in, a_len, i + 1, s_abbrs [s_index]);
            sprintf (x_sub, "@%c", S_MACRO_LIST [s_abbrs [s_index]]);
            strlcat (x_keys, x_sub, LEN_RECD);
            x_len = strlen (x_keys);
         }
         /*---(done)---------------------*/
      }
      /*---(end of sub-macro)------------*/
      else if (myMACRO.rkeys [i] == G_CHAR_SRPAREN) {
         strlcat (x_keys, "³", LEN_RECD);
         x_len = strlen (x_keys);
         DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
         break;
      }
      /*---(normal)----------------------*/
      else {
         DEBUG_YMACRO   yLOG_note    ("normal addition of keys");
         x_pos = x_len++;
         x_keys [x_pos] = myMACRO.rkeys [i];
         x_keys [x_pos + 1] = '\0';
         if (x_pos < 30)  sprintf (x_msg, "[%s]", x_keys);
         else             sprintf (x_msg, "<%s]", x_keys + x_pos - 30);
         DEBUG_YMACRO   yLOG_complex ("added"     , "%c, %3d, %3d, %s", '0' + a_out, x_pos, x_len, x_msg);
      }
      /*---(done)------------------------*/
   }
   /*---(put in place)-------------------*/
   ymacro_clear (S_MACRO_LIST [a_out]);
   g_macros [a_out].keys = strdup (x_keys);
   g_macros [a_out].len  = x_len;
   DEBUG_YMACRO  yLOG_complex ("final"     , "%3d/%c, %3d, å%sæ", a_out, S_MACRO_LIST [a_out], x_len, x_keys);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
   return i;
}

char
yMACRO_install_at       (uchar a_src, uchar a_dst)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        rc          =    0;
   char        x_src       =    0;
   char        x_dst       =    0;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_src"     , a_src);
   x_src  = ymacro_index (a_src);
   DEBUG_YMACRO   yLOG_value   ("x_src"     , x_src);
   --rce; if (x_src < 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_value   ("nkey"      , g_macros [x_src].len);
   --rce; if (g_macros [x_src].len <= 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (myMACRO.rkeys, g_macros [x_src].keys, LEN_RECD);
   myMACRO.rlen = g_macros [x_src].len;
   /*---(destination)--------------------*/
   DEBUG_YMACRO   yLOG_char    ("a_dst"     , a_dst);
   if (a_dst == 0)   x_dst  = ymacro_index ('0');
   else              x_dst  = ymacro_index (a_dst);
   DEBUG_YMACRO   yLOG_value   ("x_dst"     , x_dst);
   --rce; if (x_dst < 0) { 
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> ymacro_clear (x_dst);                                                          <*/
   ymacro_purge (YMACRO_NUMBER);
   /*---(prepare)------------------------*/
   s_index = 0;
   for (i = 0; i < S_MACRO_MAX; ++i)  s_abbrs [i] = -1;
   s_abbrs [s_index] = x_dst;
   DEBUG_YMACRO   yLOG_complex ("s_abbr"    , "%3d, %3d/%c %3d/%c %3d/%c %3d/%c %3d/%c", s_index, s_abbrs [0], S_MACRO_LIST [s_abbrs [0]], s_abbrs [1], S_MACRO_LIST [s_abbrs [1]], s_abbrs [2], S_MACRO_LIST [s_abbrs [2]], s_abbrs [3], S_MACRO_LIST [s_abbrs [3]], s_abbrs [4], S_MACRO_LIST [s_abbrs [4]]);
   /*---(call on main)-------------------*/
   rc = ymacro__install (0, x_src, myMACRO.rlen, 0, x_dst);
   DEBUG_YMACRO   yLOG_value   ("instone"   , rc);
   /*---(complete)-----------------------*/
   DEBUG_YMACRO  yLOG_exit    (__FUNCTION__);
   return 0;
}

char yMACRO_install  (uchar a_src) { return yMACRO_install_at (a_src, '0'); }

