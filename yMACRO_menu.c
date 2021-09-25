/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



/*====================------------------------------------====================*/
/*===----                         menu support                         ----===*/
/*====================------------------------------------====================*/
static void  o___MENUS___________o () { return; }

char
yMACRO_menu_beg         (void)
{
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*> IF_MACRO_PLAYING  {                                                            <* 
    *>    DEBUG_SCRP   yLOG_char    ("emode bef" , s_emode);                          <* 
    *>    s_esave = s_emode;                                                          <* 
    *>    DEBUG_SCRP   yLOG_char    ("esave"     , s_esave);                          <* 
    *>    yvikeys_macro_set2blitz ();                                                 <* 
    *>    SET_MACRO_STOP;                                                             <* 
    *>    DEBUG_SCRP   yLOG_char    ("emode aft" , s_emode);                          <* 
    *> } else {                                                                       <* 
    *>    DEBUG_SCRP   yLOG_note    ("nothing to do");                                <* 
    *> }                                                                              <*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_menu_end         (void)
{
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*> if (s_esave != '?') {                                                          <* 
    *>    DEBUG_SCRP   yLOG_char    ("emode bef" , s_emode);                          <* 
    *>    DEBUG_SCRP   yLOG_char    ("esave"     , s_esave);                          <* 
    *>    s_emode = s_esave;                                                          <* 
    *>    DEBUG_SCRP   yLOG_char    ("emode aft" , s_emode);                          <* 
    *>    switch (s_emode) {                                                          <* 
    *>    case MACRO_RUN      :                                                       <* 
    *>       if      (s_blitz    == 'y')  yvikeys_macro_set2blitz ();                 <* 
    *>       else if (s_blitzing == 'y')  yvikeys_macro_set2blitz ();                 <* 
    *>       else                         yvikeys_macro_set2run   ();                 <* 
    *>       break;                                                                   <* 
    *>    case MACRO_DELAY    :                                                       <* 
    *>       yvikeys_macro_set2delay ();                                              <* 
    *>       break;                                                                   <* 
    *>    case MACRO_PLAYBACK :                                                       <* 
    *>       yvikeys_macro_set2play  ();                                              <* 
    *>       break;                                                                   <* 
    *>    }                                                                           <* 
    *> } else {                                                                       <* 
    *>    DEBUG_SCRP   yLOG_note    ("nothing to do");                                <* 
    *> }                                                                              <* 
    *> s_esave = '?';                                                                 <*/
   /*> DEBUG_SCRP   yLOG_char    ("esave aft" , s_esave);                             <*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}
