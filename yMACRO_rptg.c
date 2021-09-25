/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



char         /*-> tbd --------------------------------[ leaf   [ge.540.142.30]*/ /*-[01.0000.103.!]-*/ /*-[--.---.---.--]-*/
yMACRO_list             (int *a_count, char *a_list)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rce         =  -10;                                                <* 
    *> int         i           =    0;                                                <* 
    *> int         c           =    0;                                                <* 
    *> char        x_entry     [LEN_LABEL];                                           <* 
    *> /+---(defenses)-----------------------+/                                       <* 
    *> --rce;  if (a_list  == NULL)  return rce;                                      <* 
    *> if (a_list != NULL)  strncpy (a_list, ",", LEN_RECD);                          <* 
    *> /+---(walk the list)------------------+/                                       <* 
    *> for (i = 0; i < s_nmacro; ++i) {                                               <* 
    *>    if (s_macros [i].len <= 0) continue;                                        <* 
    *>    if (a_list != NULL)  sprintf    (x_entry, "%c,", S_MACRO_LIST [i]);         <* 
    *>    if (a_list != NULL)  strncat    (a_list, x_entry, LEN_RECD);                <* 
    *>    ++c;                                                                        <* 
    *> }                                                                              <* 
    *> /+---(catch empty)--------------------+/                                       <* 
    *> if (a_list != NULL && strcmp (a_list, ",") == 0)   strcpy (a_list, ".");       <* 
    *> if (a_count != NULL)  *a_count = c;                                            <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> return 0;                                                                      <*/
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
