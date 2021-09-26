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
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   DEBUG_SCRP   yLOG_value   ("a_lvl"     , a_lvl);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_char    ("a_src"     , a_src);
   x_in   = ymacro_index (a_src);
   DEBUG_SCRP   yLOG_value   ("x_in"      , x_in);
   --rce; if (x_in < 0) { 
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SCRP   yLOG_point   ("a_out"     , a_out);
   --rce; if (a_out == NULL) { 
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_rlen = strlen (a_out);
   DEBUG_SCRP   yLOG_value   ("g_rlen"    , g_rlen);
   /*---(prefix)-------------------------*/
   DEBUG_SCRP   yLOG_value   ("s_abbrs"   , s_abbrs [x_in]);
   if (s_abbrs [x_in] > 0) {
      DEBUG_SCRP   yLOG_note    ("repeating macro");
      sprintf (x_sub, "�@%d�", s_abbrs [x_in]);
      strlcat (a_out, x_sub, LEN_RECD);
      g_rlen = strlen (a_out);
      DEBUG_SCRP  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prefix)-------------------------*/
   if (a_lvl > 0)  {
      DEBUG_SCRP   yLOG_note    ("prefixing");
      strlcat (a_out, "�", LEN_RECD);
      s_abbrs [x_in] = ++s_index;
      DEBUG_SCRP   yLOG_value   ("s_abbrs"   , s_abbrs [x_in]);
      ++g_rlen;
      DEBUG_SCRP   yLOG_value   ("g_rlen"    , g_rlen);
   }
   /*---(copy)---------------------------*/
   for (i = 0; i < g_macros [x_in].len; ++i) {
      DEBUG_SCRP   yLOG_char    ("char"      , g_macros [x_in].keys [i]);
      if (g_macros [x_in].keys [i] == G_CHAR_HALT)  break;
      if (g_macros [x_in].keys [i] == '@') {
         rc = ymacro__flatten (a_lvl + 1, g_macros [x_in].keys [++i], a_out);
         DEBUG_SCRP   yLOG_value   ("flatone"   , rc);
         if (rc < 0) {
            DEBUG_SCRP  yLOG_exit    (__FUNCTION__);
            return rc;
         }
         continue;
      }
      a_out [g_rlen++]   = g_macros [x_in].keys [i];
      a_out [g_rlen]     = '\0';
      if (g_rlen < 30)  sprintf (x_msg, "[%s]", a_out);
      else              sprintf (x_msg, "<%s]", a_out + g_rlen - 30);
      DEBUG_SCRP   yLOG_complex ("added"     , "%3d, %3d, %s", g_rlen, g_rlen, x_msg);
   }
   /*---(suffix)-------------------------*/
   if (a_lvl > 0)  {
      DEBUG_SCRP   yLOG_note    ("suffixing");
      strlcat (a_out, "�", LEN_RECD);
      ++g_rlen;
      DEBUG_SCRP   yLOG_value   ("g_rlen"    , g_rlen);
   }
   /*---(complete)-----------------------*/
   DEBUG_SCRP  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_flatten          (char a_src, char a_dst)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        rc          =    0;
   char        x_out       =    0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(destination)--------------------*/
   DEBUG_SCRP   yLOG_char    ("a_dst"     , a_dst);
   x_out  = ymacro_index (a_dst);
   DEBUG_SCRP   yLOG_char    ("x_out"     , x_out);
   --rce; if (x_out < 0) { 
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ymacro_clear (a_dst);
   /*---(prepare)------------------------*/
   s_index = 0;
   for (i = 0; i < S_MACRO_MAX; ++i)  s_abbrs [i] = 0;
   /*---(call on main)-------------------*/
   rc = ymacro__flatten (0, a_src, g_rkeys);
   DEBUG_SCRP   yLOG_value   ("flatone"   , rc);
   /*---(save)---------------------------*/
   strlcat (g_rkeys, "�"   , LEN_RECD );
   g_macros [x_out].keys = strdup (g_rkeys);
   g_macros [x_out].len  = strlen (g_rkeys);
   /*---(clear)--------------------------*/
   g_rkeys [0] = '\0';
   g_rlen      = 0;
   /*---(complete)-----------------------*/
   DEBUG_SCRP  yLOG_exit    (__FUNCTION__);
   return rc;
}

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
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   DEBUG_SCRP   yLOG_complex ("args"      , "%2dl, %2di, %2dl, %2dp, %2do", a_lvl, a_in, a_len, a_pos, a_out);
   for (i = a_pos; i < a_len; ++i) {
      DEBUG_SCRP   yLOG_char    ("char"      , g_rkeys [i]);
      /*---(layering operator)-----------*/
      if (g_rkeys [i] == G_CHAR_SLPAREN) {
         /*---(repeat sub-macro call)----*/
         if (g_rkeys [i + 1] == '@') {
            DEBUG_SCRP   yLOG_note    ("sub-macro repeat call");
            sprintf (x_sub, "@%c", g_rkeys [i + 2]);
            strlcat (x_keys, x_sub, LEN_RECD);
            x_len = strlen (x_keys);
            i += 3;
         }
         /*---(create new sub-macro)-----*/
         else {
            DEBUG_SCRP   yLOG_note    ("sub-macro first call");
            ++s_index;
            i = ymacro__install (a_lvl + 1, a_in, a_len, i + 1, s_index);
            sprintf (x_sub, "@%c", S_MACRO_LIST [s_index]);
            strlcat (x_keys, x_sub, LEN_RECD);
            x_len = strlen (x_keys);
         }
         /*---(done)---------------------*/
      }
      /*---(end of sub-macro)------------*/
      else if (g_rkeys [i] == G_CHAR_SRPAREN) {
         strlcat (x_keys, "�", LEN_RECD);
         x_len = strlen (x_keys);
         DEBUG_SCRP  yLOG_exit    (__FUNCTION__);
         break;
      }
      /*---(normal)----------------------*/
      else {
         DEBUG_SCRP   yLOG_note    ("normal addition of keys");
         x_pos = x_len++;
         x_keys [x_pos] = g_rkeys [i];
         x_keys [x_pos + 1] = '\0';
         if (x_pos < 30)  sprintf (x_msg, "[%s]", x_keys);
         else             sprintf (x_msg, "<%s]", x_keys + x_pos - 30);
         DEBUG_SCRP   yLOG_complex ("added"     , "%c, %3d, %3d, %s", '0' + a_out, x_pos, x_len, x_msg);
      }
      /*---(done)------------------------*/
   }
   /*---(put in place)-------------------*/
   ymacro_clear (S_MACRO_LIST [a_out]);
   g_macros [a_out].keys = strdup (x_keys);
   g_macros [a_out].len  = x_len;
   /*---(complete)-----------------------*/
   DEBUG_SCRP  yLOG_exit    (__FUNCTION__);
   return i;
}

char
yMACRO_install          (char a_src)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        rc          =    0;
   char        x_dst       =  '0';
   char        x_in        =    0;
   char        x_out       =    0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_SCRP   yLOG_char    ("a_src"     , a_src);
   x_in   = ymacro_index (a_src);
   DEBUG_SCRP   yLOG_value   ("x_in"      , x_in);
   --rce; if (x_in  < 0) { 
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (g_rkeys, g_macros [x_in].keys, LEN_RECD);
   g_rlen = g_macros [x_in].len;
   DEBUG_SCRP   yLOG_value   ("g_rlen"    , g_rlen);
   --rce; if (g_rlen  <= 0) { 
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(destination)--------------------*/
   DEBUG_SCRP   yLOG_char    ("x_dst"     , x_dst);
   x_out  = ymacro_index (x_dst);
   DEBUG_SCRP   yLOG_value   ("x_out"     , x_out);
   --rce; if (x_out < 0) { 
      DEBUG_SCRP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ymacro_clear (x_dst);
   /*---(prepare)------------------------*/
   s_index = x_out;
   for (i = 0; i < S_MACRO_MAX; ++i)  s_abbrs [i] = 0;
   /*---(call on main)-------------------*/
   rc = ymacro__install (0, x_in, g_rlen, 0, s_index);
   DEBUG_SCRP   yLOG_value   ("instone"   , rc);
   /*---(complete)-----------------------*/
   DEBUG_SCRP  yLOG_exit    (__FUNCTION__);
   return 0;
}
