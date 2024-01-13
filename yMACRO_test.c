/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yMACRO.h"
#include    "yMACRO_priv.h"



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char          unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
ymacro__unit_quiet      (void)
{
   char        rc           =    0;
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMACRO_unit" };
   rc = yPARSE_config (YPARSE_AUTO, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_FILL);
   /*> yURG_logger   (x_narg, x_args);                                                <*/
   /*> yURG_urgs     (x_narg, x_args);                                                <*/
   rc = yMODE_init  (MODE_MAP);
   rc = yMODE_init_after ();
   yKEYS_unit_handlers ();
   yKEYS_init  ();
   yKEYS_init_after ();
   yMACRO_init ();
   yMACRO_init_after ();
   yMACRO_config (NULL, NULL);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ymacro__unit_loud       (void)
{
   char        rc           =    0;
   int         x_narg       = 1;
   char       *x_args [20]  = {"yMACRO_unit" };
   rc = yPARSE_config (YPARSE_AUTO, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_FILL);
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ystr"         , YURG_ON);
   yURG_by_name  ("yparse"       , YURG_ON);
   yURG_by_name  ("ymode"        , YURG_ON);
   yURG_by_name  ("ykeys"        , YURG_ON);
   yURG_by_name  ("ymacro"       , YURG_ON);
   DEBUG_YMACRO   yLOG_info     ("yMACRO"     , yMACRO_version   ());
   rc = yMODE_init  (MODE_MAP);
   rc = yMODE_init_after ();
   yMODE_unit_handlers ();
   yKEYS_init  ();
   yKEYS_init_after ();
   yMACRO_init ();
   yMACRO_init_after ();
   yMACRO_config (NULL, NULL);
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ymacro__unit_end        (void)
{
   DEBUG_YMACRO   yLOG_enter   (__FUNCTION__);
   /*> yVIKEYS_wrap ();                                                               <*/
   DEBUG_YMACRO   yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yMACRO__unit            (char *a_question, uchar a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =    0;
   char        x_list      [LEN_RECD];
   char        t           [LEN_RECD];
   int         c           =    0;
   int         x_len       =    0;
   int         i           =    0;
   char        x_ddelay    [LEN_TERSE];
   char        x_dupdate   [LEN_TERSE];
   char        x_edelay    [LEN_TERSE];
   char        x_eupdate   [LEN_TERSE];
   /*---(preprare)-----------------------*/
   strcpy  (unit_answer, "MACRO unit       : question not understood");
   /*---(simple questions)---------------*/
   if      (strcmp (a_question, "rec"            )   == 0) {
      if (myMACRO.rcurr < 0) snprintf (unit_answer, LEN_RECD, "MACRO rec    (%c) : macro pointer grounded", myMACRO.rname);
      else {
         sprintf (t, "å%-.33sæ", myMACRO.rkeys);
         if (myMACRO.rlen > 33)  t [34] = '>';
         snprintf (unit_answer, LEN_RECD, "MACRO rec    (%c) : %c %2d %2d%s", myMACRO.rname, myMACRO.rmode, myMACRO.rpos, myMACRO.rlen, t);
      }
      return unit_answer;
   }
   else if (strcmp (a_question, "rec_mode"       )   == 0) {
      if (myMACRO.rcurr < 0) snprintf (unit_answer, LEN_RECD, "MACRO recm   (%c) : macro pointer grounded", myMACRO.rname);
      else {
         sprintf (t, "å%-.33sæ", myMACRO.modes);
         if (myMACRO.rlen > 33)  t [34] = '>';
         snprintf (unit_answer, LEN_RECD, "MACRO recm   (%c) : %c %2d %2d%s", myMACRO.rname, myMACRO.rmode, myMACRO.rpos, myMACRO.rlen - 1, t);
      }
      return unit_answer;
   }
   else if (strcmp (a_question, "exec"           )   == 0) {
      if (myMACRO.ecurr < 0)  snprintf (unit_answer, LEN_RECD, "MACRO exec   (%c) : macro pointer grounded", myMACRO.ename);
      else              snprintf (unit_answer, LEN_RECD, "MACRO exec   (%c) : %c %c %3d %02x %3d[%-.30s]", myMACRO.ename, myMACRO.emode, myMACRO.ddelay, zMACRO_macros [myMACRO.ecurr].pos, (uchar) zMACRO_macros [myMACRO.ecurr].cur, zMACRO_macros [myMACRO.ecurr].len, zMACRO_macros [myMACRO.ecurr].keys);
      return unit_answer;
   }
   /*> else if (strcmp (a_question, "keys"           )   == 0) {                                             <* 
    *>    snprintf (unit_answer, LEN_RECD, "MACRO keys   (%c) : %-.45s", a_abbr, zMACRO_macros [myMACRO.ecurr].keys);   <* 
    *>    return unit_answer;                                                                                <* 
    *> }                                                                                                     <*/
   else if (strcmp (a_question, "list"           )   == 0) {
      c = yMACRO_list (',', x_list);
      snprintf (unit_answer, LEN_RECD, "MACRO list       : %2d %s", c, x_list);
      return unit_answer;
   }
   else if (strcmp (a_question, "speed"          )   == 0) {
      /*> snprintf (unit_answer, LEN_FULL, "MACRO speed    %c : %8.6fd %5.3fu %2d/%2ds, deb %c/%c, exe %c/%c, %2dp", myMACRO.blitzing, myMACRO.edelay, myMACRO.eupdate, myMACRO.cskip, myMACRO.nskip, myMACRO.ddelay, myMACRO.dupdate, myMACRO.edelay, myMACRO.eupdate, myMACRO.pauses);   <*/
      yKEYS_ddelay_info  (myMACRO.ddelay , x_ddelay , NULL, NULL);
      yKEYS_dupdate_info (myMACRO.dupdate, x_dupdate, NULL);
      yKEYS_ddelay_info  (myMACRO.edelay , x_edelay , NULL, NULL);
      yKEYS_dupdate_info (myMACRO.eupdate, x_eupdate, NULL);
      /*> snprintf (unit_answer, LEN_FULL, "MACRO speed    %c : deb %c/%c, exe %c/%c, %2dp", myMACRO.blitzing, myMACRO.ddelay, myMACRO.dupdate, myMACRO.edelay, myMACRO.eupdate, myMACRO.pauses);   <*/
      snprintf (unit_answer, LEN_FULL, "MACRO speed      : exec  %c %-5.5s, %c %-5.5s  §  delay  %c %-5.5s, %c %-5.5s  §  macro  %c %c %2dp",
            myMACRO.edelay, x_edelay, myMACRO.eupdate, x_eupdate,
            myMACRO.ddelay, x_ddelay, myMACRO.dupdate, x_dupdate,
            myMACRO.blitz, myMACRO.blitzing, myMACRO.pauses);
      return unit_answer;
   }
   /*> else if (strcmp (a_question, "speed"          )   == 0) {                                                                                                                                                                                      <* 
    *>    snprintf (unit_answer, LEN_RECD, "MACRO speed    %c : %8.6fd %5.3fu %2d/%2ds, deb %c/%c, exe %c/%c, %2dp", g_blitzing, myVIKEYS.delay, myVIKEYS.update, myMACRO.cskip, myMACRO.nskip, myMACRO.ddelay, myMACRO.dupdate, myMACRO.edelay, myMACRO.eupdate, myMACRO.pauses);   <* 
    *>    return unit_answer;                                                                                                                                                                                                                         <* 
    *> }                                                                                                                                                                                                                                              <*/
   /*> else if (strcmp (a_question, "clip"           )   == 0) {                                  <* 
    *>    yvikeys_dump_read (a_abbr, t, &x_len);                                                  <* 
    *>    snprintf (unit_answer, LEN_RECD, "MACRO clip  (%2d) : %2d[%.40s]", a_abbr, x_len, t);   <* 
    *>    return unit_answer;                                                                     <* 
    *> }                                                                                          <*/
   /*---(complex questions)--------------*/
   n = ymacro_index (a_abbr);
   if (n < 0) {
      strcpy  (unit_answer, "MACRO unit       : not a valid macro name");
      return unit_answer;
   }
   else if (strcmp (a_question, "saved"          )   == 0) {
      if (n < 0)  snprintf (unit_answer, LEN_RECD, "MACRO saved  (%c) : not a valid macro name", a_abbr);
      else {
         sprintf (t, "å%-.33sæ", zMACRO_macros [n].keys);
         if (zMACRO_macros [n].len > 33)  t [34] = '>';
         snprintf (unit_answer, LEN_RECD, "MACRO saved  (%c) : %2d%-35.35s %2d %2d %2d", a_abbr, zMACRO_macros [n].len, t, zMACRO_macros [n].pos, zMACRO_macros [n].runby, zMACRO_macros [n].repeat);
      }
   }
   else if (strcmp (a_question, "full"           )   == 0) {
      if (n < 0)  snprintf (unit_answer, LEN_RECD, "MACRO full   (%c) : not a valid macro name", a_abbr);
      else {
         snprintf (unit_answer, LEN_RECD, "MACRO full   (%c) : %3då%-sæ", a_abbr, zMACRO_macros [n].len, zMACRO_macros [n].keys);
      }
   }
   else if (strcmp (a_question, "modes"          )   == 0) {
      if (n < 0)  snprintf (unit_answer, LEN_RECD, "MACRO modes  (%c) : not a valid macro name", a_abbr);
      else {
         sprintf (t, "å%-.33sæ", zMACRO_macros [n].modes);
         if (zMACRO_macros [n].len > 33)  t [34] = '>';
         snprintf (unit_answer, LEN_RECD, "MACRO modes  (%c) : %2d%-35.35s %2d %2d %2d", a_abbr, zMACRO_macros [n].len, t, zMACRO_macros [n].pos, zMACRO_macros [n].runby, zMACRO_macros [n].repeat);
      }
   }
   /*> else if (strcmp (a_question, "full"           )   == 0) {                                                <* 
    *>    if (n < 0)  snprintf (unit_answer, LEN_RECD, "MACRO full   (%c) : not a valid macro name", a_abbr);   <* 
    *>    else        snprintf (unit_answer, LEN_RECD, "MACRO full   (%c) : %s", a_abbr, zMACRO_macros [n].keys);    <* 
    *> }                                                                                                        <*/
   else if (strcmp (a_question, "repeat"       )  == 0) {
      snprintf (unit_answer, LEN_FULL, "MACRO repeat     : %d", yKEYS_repeats ());
   }
   else if (strcmp (a_question, "agrios"       )  == 0) {
      snprintf (unit_answer, LEN_FULL, "yMACRO agrios    : %d", yKEYS_repeats ());
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


