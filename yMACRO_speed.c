/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"


/*
 *
 *   RUN  
 *     executing at normal speed (as set by edelay/eupdate)
 *     normally set to blitz, but demo's slow it down
 *
 *   DELAY
 *     executing at delay speed  (as set by ddelay/dupdate)
 *     debugging speed where macro moves automatically, but slower
 *
 *   PLAYBACK
 *     executs only according to interactive input, one key at a time
 *     allows user to act like using a debugger
 *
 *   BLITZ
 *     executing at fastest possible speed
 *
 *     there are three types of blitzing
 *
 *     TEST_BLITZ means execution speed (RUN) is set to blitz
 *
 *     BRACED BLITZ means a section { ... } runs blitzed, but goes back after
 *
 *     NORMAL BLITZ means a set of keys º ... » runs blitzed, but goes back after
 *
 *
 *
 *
 *
 */


/*====================------------------------------------====================*/
/*===----                       macro delay setting                    ----===*/
/*====================------------------------------------====================*/
static void  o___DELAY___________o () { return; }

char         /*-> set or adjust delay value ----------[ leaf   [gz.612.101.50]*/ /*-[01.0000.023.!]-*/ /*-[--.---.---.--]-*/
ymacro__delay           (char a_which, char a_delay)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
   /*---(defense)---------------------*/
   DEBUG_YMACRO   yLOG_schar   (a_which);
   --rce;  switch (a_which) {
   case 'd' :  break;
   case 'e' :  break;
   default  :
               DEBUG_YMACRO   yLOG_snote   ("a_which not legal");
               DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
               return rce;
   }
   /*---(set)----------------------------*/
   DEBUG_YMACRO   yLOG_schar   (a_delay);
   --rce;  if (a_delay >= MACRO_BLITZ && a_delay <= MACRO_TRIPLE) {
      DEBUG_YMACRO   yLOG_snote   ("set abs");
      if (a_which == 'd')  myMACRO.ddelay = a_delay;
      else                 myMACRO.edelay = a_delay;
   }
   else if (a_delay == '+') {
      DEBUG_YMACRO   yLOG_snote   ("increase (+) faster");
      switch (a_which) {
      case 'd' :
         if (myMACRO.ddelay > MACRO_BLITZ)   --(myMACRO.ddelay);
         else {
            DEBUG_YMACRO   yLOG_snote   ("ddelay already at fastest");
            DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
         break;
      case 'e' :
         if (myMACRO.edelay > MACRO_BLITZ)   --(myMACRO.edelay);
         else {
            DEBUG_YMACRO   yLOG_snote   ("edelay already at fastest");
            DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
      }
   }
   else if (a_delay == '-') {
      DEBUG_YMACRO   yLOG_snote   ("decrease (+) slower");
      switch (a_which) {
      case 'd' :
         if (myMACRO.ddelay < MACRO_TRIPLE)  ++(myMACRO.ddelay);
         else {
            DEBUG_YMACRO   yLOG_snote   ("ddelay already at fastest");
            DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
         break;
      case 'e' :
         if (myMACRO.edelay < MACRO_TRIPLE)  ++(myMACRO.edelay);
         else {
            DEBUG_YMACRO   yLOG_snote   ("edelay already at fastest");
            DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
      }
   }
   /*---(trouble)---------------------*/
   else {
      DEBUG_YMACRO   yLOG_snote   ("a_delay not legal");
      DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(new value)-------------------*/
   DEBUG_YMACRO   yLOG_schar   (myMACRO.edelay);
   DEBUG_YMACRO   yLOG_schar   (myMACRO.ddelay);
   /*---(implement)-------------------*/
   switch (a_which) {
   case 'd' :
      IF_MACRO_DELAY  yKEYS_loop_macro (myMACRO.edelay, myMACRO.eupdate);
      break;
   case 'e' :
      IF_MACRO_RUN    yKEYS_loop_macro (myMACRO.edelay, myMACRO.eupdate);
      break;
   }
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
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
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        l           =    0;
   char       *x_valid     = MACRO_UPDATES;
   char        x_curr      =  '·';
   char       *p           = NULL;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YMACRO   yLOG_senter  (__FUNCTION__);
   /*---(defense)---------------------*/
   DEBUG_YMACRO   yLOG_schar   (a_which);
   --rce;  switch (a_which) {
   case 'd' :
      x_curr = myMACRO.dupdate;
      break;
   case 'e' :
      x_curr = myMACRO.eupdate;
      break;
   default  :
      DEBUG_YMACRO   yLOG_snote   ("a_which not legal");
      DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_schar   (ychrvisible (x_curr));
   DEBUG_YMACRO   yLOG_snote   (x_valid);
   if (x_curr != 0)  p = strchr (x_valid, x_curr);
   DEBUG_YMACRO   yLOG_spoint  (p);
   if (p != NULL) {
      n = p - x_valid;
      DEBUG_YMACRO   yLOG_sint    (n);
   }
   DEBUG_YMACRO   yLOG_sint    (a_update);
   --rce;  if (a_update == 0) {
      DEBUG_YMACRO   yLOG_snote   ("a_update can not be 0");
      DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YMACRO   yLOG_schar   (ychrvisible (a_update));
   l = strlen (x_valid);
   /*---(set)----------------------------*/
   DEBUG_YMACRO   yLOG_schar   (a_update);
   --rce;  if (strchr (x_valid, a_update) != NULL) {
      DEBUG_YMACRO   yLOG_snote   ("set abs");
      if (a_which == 'd')  myMACRO.dupdate = a_update;
      else                 myMACRO.eupdate = a_update;
   }
   else if (a_update == '+') {
      DEBUG_YMACRO   yLOG_snote   ("increase (+) faster");
      if (n < 0)  {
         DEBUG_YMACRO   yLOG_snote   ("current update is not valid");
         DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (n > 0) {
         if (a_which == 'd')  myMACRO.dupdate = x_valid [--n];
         else                 myMACRO.eupdate = x_valid [--n];
      } else {
         DEBUG_YMACRO   yLOG_snote   ("update already at slowest");
         DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   else if (a_update == '-') {
      DEBUG_YMACRO   yLOG_snote   ("decrease (+) slower");
      if (n < 0) {
         DEBUG_YMACRO   yLOG_snote   ("current update is not valid");
         DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (n < l - 1) {
         if (a_which == 'd')  myMACRO.dupdate = x_valid [++n];
         else                 myMACRO.eupdate = x_valid [++n];
      } else {
         DEBUG_YMACRO   yLOG_snote   ("update already at fastest");
         DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(trouble)---------------------*/
   else {
      DEBUG_YMACRO   yLOG_snote   ("a_update not legal");
      DEBUG_YMACRO   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(new value)-------------------*/
   DEBUG_YMACRO   yLOG_schar   (myMACRO.eupdate);
   DEBUG_YMACRO   yLOG_schar   (myMACRO.dupdate);
   /*---(complete)--------------------*/
   DEBUG_YMACRO   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YMACRO   yLOG_note    (__FUNCTION__);
   SET_MACRO_STOP;
   zMACRO_macros [myMACRO.ecurr].pos    = -1;
   zMACRO_macros [myMACRO.ecurr].cur    = '·';
   zMACRO_macros [myMACRO.ecurr].repeat =  0;
   myMACRO.ecurr = -1;
   myMACRO.epos  = -1;
   yKEYS_loop_return ();
   return 0;
}

char
ymacro_set2play         (void)
{
   DEBUG_YMACRO   yLOG_note    (__FUNCTION__);
   SET_MACRO_PLAYBACK;
   ymacro_agrios_style (',');
   yKEYS_loop_return ();
   /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "macro");           <*/
   return 0;
}

char
ymacro_set2delay        (void)
{
   DEBUG_YMACRO   yLOG_note    (__FUNCTION__);
   SET_MACRO_DELAY;
   ymacro_agrios_style ('.');
   yKEYS_loop_macro (myMACRO.ddelay, myMACRO.dupdate);
   /*> if (myVIKEYS.loud == 'y')  yvikeys_sizes_switch ("status", "macro");           <*/
   return 0;
}

char
ymacro_set2run          (void)
{
   DEBUG_YMACRO   yLOG_note    (__FUNCTION__);
   DEBUG_YMACRO   yLOG_char    ("blitzing"  , myMACRO.blitzing);
   ymacro_agrios_style ('.');
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
   DEBUG_YMACRO   yLOG_note    (__FUNCTION__);
   DEBUG_YMACRO   yLOG_char    ("blitzing"  , myMACRO.blitzing);
   if (myMACRO.blitzing == 'y') return 0;
   SET_MACRO_RUN;
   yKEYS_loop_macro (MACRO_BLITZ, MACRO_BLIND);
   myMACRO.blitzing = 'y';
   return 0;
}



