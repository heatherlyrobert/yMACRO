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
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   IF_MACRO_PLAYING  {
      DEBUG_YMACRO   yLOG_char    ("emode bef" , myMACRO.emode);
      myMACRO.esave     = myMACRO.emode;
      myMACRO.eblitz    = myMACRO.blitz;
      myMACRO.eblitzing = myMACRO.blitzing;
      DEBUG_YMACRO   yLOG_char    ("esave"     , myMACRO.esave);
      ymacro_set2blitz ();
      SET_MACRO_STOP;
      DEBUG_YMACRO   yLOG_char    ("emode aft" , myMACRO.emode);
   } else {
      DEBUG_YMACRO   yLOG_note    ("nothing to do");
   }
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yMACRO_menu_end         (void)
{
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   if (myMACRO.esave != '?') {
      DEBUG_YMACRO   yLOG_char    ("emode bef" , myMACRO.emode);
      DEBUG_YMACRO   yLOG_char    ("esave"     , myMACRO.esave);
      myMACRO.emode     = myMACRO.esave;
      myMACRO.blitz     = myMACRO.eblitz;
      myMACRO.blitzing  = myMACRO.eblitzing;
      DEBUG_YMACRO   yLOG_char    ("emode aft" , myMACRO.emode);
      switch (myMACRO.emode) {
      case MACRO_RUN      :
         if (strchr ("Yy", myMACRO.blitz) != NULL)  ymacro_set2blitz ();
         else if (myMACRO.blitzing == 'y')  ymacro_set2blitz ();
         else                               ymacro_set2run   ();
         break;
      case MACRO_DELAY    :
         ymacro_set2delay ();
         break;
      case MACRO_PLAYBACK :
         ymacro_set2play  ();
         break;
      }
   } else {
      DEBUG_YMACRO   yLOG_note    ("nothing to do");
   }
   myMACRO.esave = '?';
   DEBUG_YMACRO   yLOG_char    ("esave aft" , myMACRO.esave);
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   return 0;
}


