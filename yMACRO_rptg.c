/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"

/*
 *  yVIKEYS statuses
 *     macros       
 *
 *
 */

char         /*-> tbd --------------------------------[ leaf   [ge.540.142.30]*/ /*-[01.0000.103.!]-*/ /*-[--.---.---.--]-*/
yMACRO_list             (char a_style, char *a_list)
{
   /*---(design notes)-------------------*/
   /*
    *  -   compact
    *  ,   sortable comma delimited
    *  0   system only
    *  a   normal only
    *  è   greek only
    *  *   all with little space
    *  F   all in fancy format
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_max       =    0;
   char        x_beg       =    0;
   char        x_end       =    0;
   int         i           =    0;
   int         n           =    0;
   int         c           =    0;
   char        x_entry     [LEN_LABEL];
   char        x_inc       =    0;
   /*---(defenses)-----------------------*/
   --rce;  if (a_list  == NULL)  return rce;
   /*---(prepare)------------------------*/
   strlcpy (a_list, "", LEN_HUND);
   x_max = strlen (S_MACRO_LIST);
   switch (a_style) {
   case '*' :
   case 'F' :  x_beg =  0; x_end = x_max - 2;  break;
   case '0' :  x_beg =  0; x_end = 9;          break;
   case 'a' :  x_beg = 10; x_end = 35;         break;
   case 'è' :  x_beg = 36; x_end = x_max - 2;  break;
   }
   /*---(walk the list)------------------*/
   switch (a_style) {
   case '-' : case ',' :
      if (a_style == ',')  strlcpy (a_list, ",", LEN_HUND);
      for (i = 0; i < g_nmacro; ++i) {
         if (g_macros [i].len <= 0) continue;
         if (a_style == ',')  sprintf    (x_entry, "%c,", S_MACRO_LIST [i]);
         else                 sprintf    (x_entry, "%c" , S_MACRO_LIST [i]);
         strlcat    (a_list, x_entry, LEN_HUND);
         ++c;
      }
      break;
   default  :
      for (i = x_beg; i <= x_end; ++i) {
         switch (i) {
         case   0 :
            if (a_style == 'F')  strlcat (a_list, "[" , LEN_HUND);
            break;
         case  10 :
            if (a_style == 'F')  strlcat (a_list, " [", LEN_HUND);
            if (a_style == '*')  strlcat (a_list, " " , LEN_HUND);
            break;
         }
         if (g_macros [i].len >  0)  {
            sprintf (x_entry, "%c" , S_MACRO_LIST [i]);
            strlcat (a_list, x_entry, LEN_HUND);
            ++c;
         } else {
            strlcat (a_list, "·"        , LEN_HUND);
         }
         switch (i) {
         case  35 :
            if (a_style == 'F')        strlcat (a_list, "] ", LEN_HUND);
            if (a_style == '*')        strlcat (a_list, " ", LEN_HUND);
            break;
         case  59 :
            if (a_style == 'F')        strlcat (a_list, "]", LEN_HUND);
            break;
         }
      }
      break;
   }
   /*---(catch empty)--------------------*/
   if (strcmp (a_list, ",") == 0)   strcpy (a_list, "·");
   if (strcmp (a_list, "" ) == 0)   strcpy (a_list, "·");
   /*---(complete)-----------------------*/
   return c;
}

int
yMACRO_dump             (void *a_file)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                                                                      <* 
    *> char        x_end       =    0;                                                                                                                                                                                                                               <* 
    *> int         i           =    0;                                                                                                                                                                                                                               <* 
    *> char        c           =    0;                                                                                                                                                                                                                               <* 
    *> int         x_len       =    0;                                                                                                                                                                                                                               <* 
    *> /+---(header)-------------------------+//+  27 + 20 + 5 = 52 +/                                                                                                                                                                                               <* 
    *> DEBUG_OUTP   yLOG_enter   (__FUNCTION__);                                                                                                                                                                                                                     <* 
    *> /+---(prepare)------------------------+/                                                                                                                                                                                                                      <* 
    *> x_end = strlen (S_MACRO_LIST);                                                                                                                                                                                                                                <* 
    *> x_len = 80 - 52 - strlen (myVIKEYS.s_prog);                                                                                                                                                                                                                   <* 
    *> fprintf (a_file, "##===[[ yVIKEYS macro dump from %s (:dump macros) ]]%*.*s##\n", myVIKEYS.s_prog, x_len, x_len, "======================================================================================================================================");   <* 
    *> /+---(walk list)----------------------+/                                                                                                                                                                                                                      <* 
    *> for (i = 0; i <= x_end; ++i) {                                                                                                                                                                                                                                <* 
    *>    if (s_macros [i].len <= 0)  continue;                                                                                                                                                                                                                      <* 
    *>    fprintf (a_file, "%c=%s\n", S_MACRO_LIST [i], s_macros [i].keys);                                                                                                                                                                                          <* 
    *>    ++c;                                                                                                                                                                                                                                                       <* 
    *> }                                                                                                                                                                                                                                                             <* 
    *> fprintf (a_file, "##===[[ end-of-dump (%2d recs) ]]==============================================##\n", c);                                                                                                                                                   <* 
    *> /+---(complete)-----------------------+/                                                                                                                                                                                                                      <* 
    *> DEBUG_OUTP  yLOG_exit    (__FUNCTION__);                                                                                                                                                                                                                      <* 
    *> return c;                                                                                                                                                                                                                                                     <*/
}



/*====================------------------------------------====================*/
/*===----                        status control                        ----===*/
/*====================------------------------------------====================*/
static void  o___STATUS__________o () { return; }

/*> mac  8 e ´                                                                                                       <* 
 *> mac  8 e 2efhmyzò  ´                                                                                             <* 
 *> macros   8 - e 2efhmyzò                ´                                                                         <* 
 *> macros   8 - e [····ef·h····m···········yz] ···········ò············]´                                           <* 
 *> macros   8 - e [··2······· [····ef·h····m···········yz] ···········ò············]                            ´   <*/

char
ymacro_status__sizes    (char *a_size, short *a_wide, short *w)
{
   /*---(output)-------------------------*/
   DEBUG_SCRP   yLOG_complex ("request"   , "%c %3d %3d", *a_size, *a_wide, *w);
   /*---(check size)---------------------*/
   if (*a_size == '-') {
      if (*a_wide < 20)  *a_size = 'u';
      if (*a_wide < 30)  *a_size = 't';
   }
   /*---(maxlen)-------------------------*/
   switch (*a_size) {
   case 'u'  :  *a_wide =   0; break;
   case 't'  :  *a_wide =  20; break;
   case 's'  :  *a_wide =  40; break;
   case 'm'  :  *a_wide =  70; break;
   case 'l'  :  *a_wide = 110; break;
   case 'h'  :  *a_wide = 160; break;
   case 'g'  :  *a_wide = 220; break;
   }
   /*---(output)-------------------------*/
   DEBUG_SCRP   yLOG_complex ("revised"   , "%c %3d %3d", *a_size, *a_wide, *w);
}

char
yMACRO_rec_status       (char a_size, short a_wide, char *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_len       = 0;
   int         x_wide;
   short       w;
   uchar       x_name      = '-';
   uchar       x_keys      [LEN_RECD]  = "";
   uchar       x_curr      = '¬';
   uchar       x_lenstr    [LEN_TERSE] = "---";
   uchar       x_pre       [LEN_DESC]  = "";
   uchar       x_over      = ' ';
   uchar       x_mid       [LEN_RECD]  = "";
   int         x_beg       =   0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(get size)-----------------------*/
   ymacro_status__sizes (&a_size, &a_wide, &w);
   w =  a_wide - 20;
   if (a_size == 't')  w = 10;
   /*---(length)-------------------------*/
   if (g_rcurr >= 0) {
      x_name = g_rname;
      strlcpy (x_keys, g_rkeys, LEN_RECD);
      x_len = strlen (x_keys) - 1;
      if (x_len > 0)  x_curr = x_keys [x_len - 1];
      sprintf (x_lenstr, "%3d", x_len);
   }
   DEBUG_SCRP   yLOG_info    ("x_keys"    , x_keys);
   DEBUG_SCRP   yLOG_value   ("x_len"     , x_len);
   DEBUG_SCRP   yLOG_value   ("x_curr"    , x_curr);
   /*---(prefix)-------------------------*/
   switch (a_size) {
   case 'u'  : case 't'  :
      sprintf (x_pre, "rec %c %c", x_name, x_curr);
      break;
   default   :
      sprintf (x_pre, "record  %c %3s %c", x_name, x_lenstr, x_curr);
      break;
   }
   /*---(correct len)--------------------*/
   IF_MACRO_RECORDING {
      if (x_len >= 1)  ++x_len;
   }
   if (x_len > w) {
      x_over = '<';
      x_beg  = x_len - w;
      x_len  = w;
   }
   /*---(keys)---------------------------*/
   switch (a_size) {
   case 'u'  :
      sprintf  (x_mid, " ´");
      break;
   case 't'  :
      snprintf (x_mid, LEN_RECD, "%c%*.*s%*.*s´", x_over, x_len, x_len, x_keys + x_beg, w - x_len, w - x_len, YSTR_MACRO + x_len);
      break;
   default   :
      snprintf (x_mid, LEN_RECD, "%c%*.*s%*.*s  ´", x_over, x_len, x_len, x_keys + x_beg, w - x_len, w - x_len, YSTR_MACRO + x_len);
      break;
   }
   /*---(concatenate)--------------------*/
   sprintf (a_list, "%s %s", x_pre, x_mid);
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_exe_status       (char a_size, short a_wide, char *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_len       =    0;
   int         x_wide;
   short       w;
   short       h;
   uchar       x_keys      [LEN_RECD]  = "";
   uchar       x_repstr    [LEN_TERSE] = "--";
   int         x_pos       =    0;
   uchar       x_posstr    [LEN_TERSE] = "---";
   uchar       x_curr      =  '¬';
   uchar       x_lenstr    [LEN_TERSE] = "---";
   uchar       x_pre       [LEN_DESC]  = "";
   uchar       x_over      =  ' ';
   char        x_bef       [LEN_RECD]  = "";
   char        x_aft       [LEN_RECD]  = "";
   int         x_rem       =    0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(get size)-----------------------*/
   if (a_size == '-') { /* no adapt option */
      if      (a_wide <  20)  a_size = 'u';
      else if (a_wide <  40)  a_size = 't';
      else if (a_wide <  70)  a_size = 's';
      else if (a_wide < 110)  a_size = 'm';
      else if (a_wide < 160)  a_size = 'l';
      else if (a_wide < 220)  a_size = 'h';
      else                    a_size = 'g';
   }
   ymacro_status__sizes (&a_size, &a_wide, &w);
   w =  a_wide - 20;
   switch (a_size) {
   case  'u' :  h =  0;  break;
   case  't' :  h =  4;  break;
   case  's' :  h =  9;  break;
   case  'm' :  h = 19;  break;
   case  'l' :  h = 39;  break;
   case  'h' :  h = 64;  break;
   case  'g' :  h = 94;  break;
   }
   /*---(length)-------------------------*/
   if (g_ecurr >= 0 && g_macros [g_ecurr].len > 0) {
      strlcpy (x_keys, g_macros [g_ecurr].keys, LEN_RECD);
      x_len  = g_macros [g_ecurr].len;
      sprintf (x_lenstr, "%3d", x_len);
      sprintf (x_repstr, "%2d", g_macros [g_ecurr].repeat);
      x_pos  = g_macros [g_ecurr].pos;
      sprintf (x_posstr, "%3d", x_pos);
      x_curr = g_macros [g_ecurr].cur;
      if (x_curr < 32)  x_curr = '£';
   }
   DEBUG_SCRP   yLOG_info    ("x_keys"    , x_keys);
   DEBUG_SCRP   yLOG_value   ("x_len"     , x_len);
   DEBUG_SCRP   yLOG_value   ("x_curr"    , x_curr);
   /*---(prefix)-------------------------*/
   switch (a_size) {
   case 'u'  : case 't'  :
      sprintf (x_pre, "exe %c", g_ename);
      break;
   default   :
      sprintf (x_pre, "execute %c %c %c %2s %3s %3s", g_ename, g_ddelay, g_dupdate, x_repstr, x_posstr, x_lenstr);
      break;
   }
   /*---(before)-------------------------*/
   if      (x_pos <=  0)  sprintf (x_bef , "%*.*s", h, h, YSTR_MACRO);
   else if (x_pos >   h)  sprintf (x_bef , "<%-*.*s", h - 1, h - 1, g_macros [g_ecurr].keys + x_pos - h + 1);
   else                   sprintf (x_bef , "%*.*s%*.*s"   , h - x_pos, h - x_pos, YSTR_MACRO, x_pos, x_pos, g_macros [g_ecurr].keys);
   /*---(after)--------------------------*/
   x_rem = g_macros [g_ecurr].len - g_macros [g_ecurr].pos - 1;
   if      (x_rem <=  0)  sprintf (x_aft , "%*.*s", h, h, YSTR_MACRO);
   else if (x_rem >   h)  sprintf (x_aft , "%-*.*s>", h - 1, h - 1, g_macros [g_ecurr].keys + x_pos + 1);
   else                   sprintf (x_aft , "%*.*s%*.*s"   , x_rem, x_rem, g_macros [g_ecurr].keys + x_pos + 1, h - x_rem, h - x_rem, YSTR_MACRO + x_rem);
   /*---(concat)-------------------------*/
   switch (a_size) {
   case 'u' :
      snprintf (a_list, LEN_RECD, "%s %c  ´", x_pre, x_curr);
      break;
   case 't' : case 's' :
      snprintf (a_list, LEN_RECD, "%s  %s %c %s ´", x_pre, x_bef, x_curr, x_aft);
      break;
   default  :
      snprintf (a_list, LEN_RECD, "%s  %s %c %s  ´", x_pre, x_bef, x_curr, x_aft);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_inv_status       (char a_size, short a_wide, char *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_len       =    0;
   short       w           =    0;
   int         c           =    0;
   uchar       x_list      [LEN_HUND]  = "";
   uchar       x_pre       [LEN_DESC]  = "";
   uchar       x_mid       [LEN_RECD]  = "";
   char        x_over      =  ' ';
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(get size)-----------------------*/
   if (a_size == '-') { /* no adapt option */
      if      (a_wide <  20)  a_size = 'u';
      else if (a_wide <  40)  a_size = 's';
      else if (a_wide <  56)  a_size = 'm';
   }
   ymacro_status__sizes (&a_size, &a_wide, &w);
   w =  a_wide - 15;
   if      (a_size == 'u')  w  =  0;
   else if (a_size == 't')  w  =  9;
   else if (a_size == 's')  w  = 26;
   else                     w -=  2;
   /*---(list)---------------------------*/
   c = yMACRO_list ('F', x_list);
   switch (a_size) {
   case 'u'  : case 't'  :
      yMACRO_list ('-', x_list);
      break;
   case 's'  :
      yMACRO_list ('a', x_list);
      break;
   default   :
      c = yMACRO_list ('F', x_list);
      break;
   }
   x_len = strlen (x_list);
   /*---(prefix)-------------------------*/
   switch (a_size) {
   case 'u'  : case 't'  :
      sprintf (x_pre, "mac %2d %c", c, g_ename);
      break;
   case 's'  :
      sprintf (x_pre, "macros  %2d %c", c, g_ename);
      break;
   default   :
      sprintf (x_pre, "macros  %2d %c %c", c, g_rname, g_ename);
      break;
   }
   /*---(middle)-------------------------*/
   if (x_len > w) {
      x_over = '>';
      x_len  = w;
   }
   switch (a_size) {
   case 'u'  :
      sprintf  (x_mid, "´");
      break;
   case 's'  :
      snprintf (x_mid, LEN_RECD, "%s´", x_list);
      break;
   default   :
      snprintf (x_mid, LEN_RECD, "%*.*s%c%*.*s´", x_len, x_len, x_list, x_over, w - x_len, w - x_len, YSTR_EMPTY);
      break;
   }
   /*---(concatenate)--------------------*/
   sprintf (a_list, "%s %s", x_pre, x_mid);
   /*---(complete)-----------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}
