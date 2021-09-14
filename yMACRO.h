/*============================----beg-of-source---============================*/
#ifndef yMACRO
#define yMACRO yes


/*---(mode)------------*/
#define     MACRO_STOP         '-'      /* normal keyboard input              */
#define     MACRO_RUN          'M'      /* macro running with redisplay       */
#define     MACRO_DELAY        'D'      /* macro delay playback controls      */
#define     MACRO_PLAYBACK     'P'      /* macro under playback controls      */
/*---(conditions)------*/
#define     IF_MACRO_OFF         if (yvikeys_macro_emode () == MACRO_STOP     ) 
#define     IF_MACRO_RUN         if (yvikeys_macro_emode () == MACRO_RUN      ) 
#define     IF_MACRO_NOT_RUN     if (yvikeys_macro_emode () != MACRO_RUN      ) 
#define     IF_MACRO_DELAY       if (yvikeys_macro_emode () == MACRO_DELAY    ) 
#define     IF_MACRO_PLAYBACK    if (yvikeys_macro_emode () == MACRO_PLAYBACK ) 
#define     IF_MACRO_MOVING      if (yvikeys_macro_emode () == MACRO_RUN      || yvikeys_macro_emode () == MACRO_DELAY   ) 
#define     IF_MACRO_NOT_MOVING  if (yvikeys_macro_emode () != MACRO_RUN      && yvikeys_macro_emode () != MACRO_DELAY   ) 
#define     IF_MACRO_NOT_PLAYING if (yvikeys_macro_emode () == MACRO_STOP     )
#define     IF_MACRO_PLAYING     if (yvikeys_macro_emode () != MACRO_STOP     )
#define     IF_MACRO_ON          if (yvikeys_macro_emode () != MACRO_STOP     ) 
/*---(setting)---------*/
#define     SET_MACRO_OFF        yvikeys_macro_modeset (MACRO_STOP);
#define     SET_MACRO_STOP       yvikeys_macro_modeset (MACRO_STOP);
#define     SET_MACRO_RUN        yvikeys_macro_modeset (MACRO_RUN);
#define     SET_MACRO_PLAYBACK   yvikeys_macro_modeset (MACRO_PLAYBACK);
#define     SET_MACRO_DELAY      yvikeys_macro_modeset (MACRO_DELAY);
/*---(speeds)----------*/
#define     MACRO_BLITZ        '0'
#define     MACRO_FAST         '1'
#define     MACRO_THOU         '2'
#define     MACRO_HUND         '3'
#define     MACRO_TWENTY       '4'
#define     MACRO_TENTH        '5'
#define     MACRO_HALF         '6'
#define     MACRO_SEC          '7'
#define     MACRO_DOUBLE       '8'
#define     MACRO_TRIPLE       '9'
/*---(updates)---------*/
#define     MACRO_NORMAL       'n'  /* normal updates */
#define     MACRO_SLOWER       's'  /* slower updates */
#define     MACRO_BLINKS       'b'  /* stop action looking */
#define     MACRO_PEEKS        'p'  /* very slow screen updates */
#define     MACRO_BLIND        'd'  /* no screen updates */


/*---(recording)-------*/
#define     MACRO_IGNORE       'i'      /* no recording                       */
#define     MACRO_RECORD       'r'      /* macro recording                    */
#define     IF_MACRO_RECORDING   if (yvikeys_macro_rmode () == MACRO_RECORD   ) 
#define     SET_MACRO_RECORD     yvikeys_macro_modeset (MACRO_RECORD);
#define     SET_MACRO_IGNORE     yvikeys_macro_modeset (MACRO_IGNORE);


typedef  const unsigned char  cuchar;
typedef  unsigned char        uchar;
typedef  const char           cchar;
typedef  const int            cint;
typedef  const float          cfloat;



#endif
/*============================----end-of-source---============================*/
