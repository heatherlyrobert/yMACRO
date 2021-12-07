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
      DEBUG_SCRP   yLOG_snote   ("set abs");
      if (a_which == 'd')  myMACRO.ddelay = a_delay;
      else                 myMACRO.edelay = a_delay;
   }
   if (a_delay == '-') {
      DEBUG_SCRP   yLOG_snote   ("decrease (-)");
      if (myMACRO.ddelay > MACRO_BLITZ) {
         if (a_which == 'd')  --(myMACRO.ddelay);
         else                 --(myMACRO.edelay);
      }
   }
   if (a_delay == '+') {
      DEBUG_SCRP   yLOG_snote   ("increase (+)");
      if (myMACRO.ddelay < MACRO_TRIPLE) {
         if (a_which == 'd')  ++(myMACRO.ddelay);
         else                 ++(myMACRO.edelay);
      }
   }
   /*---(new value)-------------------*/
   DEBUG_SCRP   yLOG_schar   (myMACRO.edelay);
   DEBUG_SCRP   yLOG_schar   (myMACRO.ddelay);
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_SCRP   yLOG_snote   ("set abs");
   if (a_which == 'd')  myMACRO.dupdate = a_update;
   else                 myMACRO.eupdate = a_update;
   /*---(new value)-------------------*/
   DEBUG_SCRP   yLOG_schar   (myMACRO.eupdate);
   DEBUG_SCRP   yLOG_schar   (myMACRO.dupdate);
   /*---(complete)--------------------*/
   DEBUG_SCRP   yLOG_sexit   (__FUNCTION__);
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
   g_macros [myMACRO.ecurr].pos    = -1;
   g_macros [myMACRO.ecurr].cur    = '·';
   g_macros [myMACRO.ecurr].repeat =  0;
   myMACRO.ecurr = -1;
   myMACRO.epos  = -1;
   yKEYS_loop_return ();
   return 0;
}

char
ymacro_set2play         (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   SET_MACRO_PLAYBACK;
   yKEYS_loop_return ();
   /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "macro");           <*/
   return 0;
}

char
ymacro_set2delay        (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   SET_MACRO_DELAY;
   yKEYS_loop_macro (myMACRO.ddelay, myMACRO.dupdate);
   /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "macro");           <*/
   return 0;
}

char
ymacro_set2run          (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   DEBUG_SCRP   yLOG_char    ("blitzing"  , myMACRO.blitzing);
   if (myMACRO.blitzing == 'y') {
      ymacro_set2blitz ();
   } else {
      SET_MACRO_RUN;
      yKEYS_loop_macro (myMACRO.edelay, myMACRO.eupdate);
      /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "macro");        <*/
   }
   return 0;
}

char
ymacro_set2blitz        (void)
{
   DEBUG_SCRP   yLOG_note    (__FUNCTION__);
   DEBUG_SCRP   yLOG_char    ("blitzing"  , myMACRO.blitzing);
   if (myMACRO.blitzing == 'y') return 0;
   SET_MACRO_RUN;
   yKEYS_loop_macro (MACRO_BLITZ, MACRO_BLIND);
   myMACRO.blitzing = 'y';
   return 0;
}



