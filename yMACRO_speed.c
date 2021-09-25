/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



/*====================------------------------------------====================*/
/*===----                       macro delay setting                    ----===*/
/*====================------------------------------------====================*/
static void  o___DELAY___________o () { return; }

char         /*-> set or adjust delay value ----------[ leaf   [gz.612.101.50]*/ /*-[01.0000.023.!]-*/ /*-[--.---.---.--]-*/
ymacro__delay           (char a_which, char a_delay)
{
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_senter  (__FUNCTION__);
   DEBUG_SCRP   yLOG_schar   (a_delay);
   /*---(set)----------------------------*/
   if (a_delay >= MACRO_BLITZ && a_delay <= MACRO_TRIPLE) {
      DEBUG_SCRP   yLOG_note    ("set abs");
      if (a_which == 'd')  g_ddelay = a_delay;
      else                 g_edelay = a_delay;
   }
   if (a_delay == '-') {
      DEBUG_SCRP   yLOG_note    ("decrease (-)");
      if (g_ddelay > MACRO_BLITZ) {
         if (a_which == 'd')  --g_ddelay;
         else                 --g_edelay;
      }
   }
   if (a_delay == '+') {
      DEBUG_SCRP   yLOG_note    ("increase (+)");
      if (g_ddelay < MACRO_TRIPLE) {
         if (a_which == 'd')  ++g_ddelay;
         else                 ++g_edelay;
      }
   }
   /*---(new value)-------------------*/
   DEBUG_SCRP   yLOG_schar   (g_edelay);
   DEBUG_SCRP   yLOG_schar   (g_ddelay);
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yMACRO_edelay  (char a_delay)    { return ymacro__delay  ('e', a_delay);  }
char yMACRO_ddelay  (char a_delay)    { return ymacro__delay  ('d', a_delay);  }



/*====================------------------------------------====================*/
/*===----                      macro update setting                    ----===*/
/*====================------------------------------------====================*/
static void  o___UPDATE__________o () { return; }

char         /*-> set or adjust update value ---------[ leaf   [gz.612.101.50]*/ /*-[01.0000.023.!]-*/ /*-[--.---.---.--]-*/
ymacro__update          (char a_which, char a_update)
{
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_senter  (__FUNCTION__);
   DEBUG_SCRP   yLOG_schar   (a_update);
   /*---(set)----------------------------*/
   DEBUG_SCRP   yLOG_note    ("set abs");
   if (a_which == 'd')  g_dupdate = a_update;
   else                 g_eupdate = a_update;
   /*---(new value)-------------------*/
   DEBUG_SCRP   yLOG_schar   (g_eupdate);
   DEBUG_SCRP   yLOG_schar   (g_dupdate);
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yMACRO_eupdate (char a_update)   { return ymacro__update ('e', a_update); }
char yMACRO_dupdate (char a_update)   { return ymacro__update ('d', a_update); }



/*====================------------------------------------====================*/
/*===----                        standard settings                     ----===*/
/*====================------------------------------------====================*/
static void  o___SETTINGS________o () { return; }

char
ymacro_set2stop         (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   SET_MACRO_STOP;
   g_macros [g_ecurr].pos    = -1;
   g_macros [g_ecurr].cur    = '·';
   g_macros [g_ecurr].repeat =  0;
   g_ecurr = -1;
   g_epos  = -1;
   /*> yvikeys_loop_normal ();                                                        <*/
   return 0;
}

char
ymacro_set2play         (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   SET_MACRO_PLAYBACK;
   /*> yvikeys_loop_normal ();                                                        <*/
   /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "macro");           <*/
   return 0;
}

char
ymacro_set2delay        (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   SET_MACRO_DELAY;
   /*> yvikeys_loop_macro (g_ddelay, g_dupdate);                                      <*/
   /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "macro");           <*/
   return 0;
}

char
ymacro_set2run          (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   DEBUG_SCRP   yLOG_char    ("blitzing"  , g_blitzing);
   if (g_blitzing == 'y') {
      ymacro_set2blitz ();
   } else {
      SET_MACRO_RUN;
      /*> yvikeys_loop_macro (g_edelay, g_eupdate);                                   <*/
      /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "macro");        <*/
   }
   return 0;
}

char
ymacro_set2blitz        (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   DEBUG_SCRP   yLOG_char    ("blitzing"  , g_blitzing);
   if (g_blitzing == 'y') return 0;
   SET_MACRO_RUN;
   /*> yvikeys_loop_macro (MACRO_BLITZ, MACRO_BLIND);                                 <*/
   g_blitzing = 'y';
   return 0;
}



