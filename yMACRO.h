/*============================----beg-of-source---============================*/
#ifndef yMACRO
#define yMACRO yes


/*---(mode)------------*/
#define     MACRO_STOP         '-'      /* normal keyboard input              */
#define     MACRO_RUN          'M'      /* macro running with redisplay       */
#define     MACRO_DELAY        'D'      /* macro delay playback controls      */
#define     MACRO_PLAYBACK     'P'      /* macro under playback controls      */
/*---(conditions)------*/
#define     IF_MACRO_OFF         if (yMACRO_exe_mode () == MACRO_STOP     ) 
#define     IF_MACRO_RUN         if (yMACRO_exe_mode () == MACRO_RUN      ) 
#define     IF_MACRO_NOT_RUN     if (yMACRO_exe_mode () != MACRO_RUN      ) 
#define     IF_MACRO_DELAY       if (yMACRO_exe_mode () == MACRO_DELAY    ) 
#define     IF_MACRO_PLAYBACK    if (yMACRO_exe_mode () == MACRO_PLAYBACK ) 
#define     IF_MACRO_MOVING      if (yMACRO_exe_mode () == MACRO_RUN      || yMACRO_exe_mode () == MACRO_DELAY   ) 
#define     IF_MACRO_NOT_MOVING  if (yMACRO_exe_mode () != MACRO_RUN      && yMACRO_exe_mode () != MACRO_DELAY   ) 
#define     IF_MACRO_NOT_PLAYING if (yMACRO_exe_mode () == MACRO_STOP     )
#define     IF_MACRO_PLAYING     if (yMACRO_exe_mode () != MACRO_STOP     )
#define     IF_MACRO_ON          if (yMACRO_exe_mode () != MACRO_STOP     ) 
/*---(setting)---------*/
#define     SET_MACRO_OFF        yMACRO_modeset (MACRO_STOP);
#define     SET_MACRO_STOP       yMACRO_modeset (MACRO_STOP);
#define     SET_MACRO_RUN        yMACRO_modeset (MACRO_RUN);
#define     SET_MACRO_PLAYBACK   yMACRO_modeset (MACRO_PLAYBACK);
#define     SET_MACRO_DELAY      yMACRO_modeset (MACRO_DELAY);
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
#define     MACRO_FAST         'f'  /* fast   updates */
#define     MACRO_NORMAL       'n'  /* normal updates */
#define     MACRO_SLOWER       's'  /* slower updates */
#define     MACRO_BLINKS       'b'  /* stop action looking */
#define     MACRO_PEEKS        'p'  /* very slow screen updates */
#define     MACRO_BLIND        'd'  /* no screen updates */


/*---(recording)-------*/
#define     MACRO_IGNORE       'i'      /* no recording                       */
#define     MACRO_RECORD       'r'      /* macro recording                    */
#define     IF_MACRO_RECORDING   if (yMACRO_rec_mode () == MACRO_RECORD   ) 
#define     SET_MACRO_RECORD     yMACRO_modeset (MACRO_RECORD);
#define     SET_MACRO_IGNORE     yMACRO_modeset (MACRO_IGNORE);

#define     CASE_MACRO_KEYS   '@' : case 'q' : case 'Q'


typedef  const unsigned char  cuchar;
typedef  unsigned char        uchar;
typedef  const char           cchar;
typedef  const int            cint;
typedef  const float          cfloat;


/*===[[ yMACRO_base.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char*       yMACRO_version          (void);
char        yMACRO_global_init      (void);       /* for other unit tests */
char        yMACRO_init             (void);
char        yMACRO_config           (void *a_loader, void *a_saver);
char        yMACRO_wrap             (void);
char        yMACRO_reset_all        (void);
char        yMACRO_hmode            (uchar a_major, uchar a_minor);

/*===[[ yMACRO_rec.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_rec_mode         (void);
char        yMACRO_rec_key          (uchar a_key, uchar a_mode);
char        yMACRO_rec_end          (void);
char        yMACRO_direct           (char *a_string);


/*===[[ yMACRO_exe.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_exe_mode         (void);
char        yMACRO_exe_pos          (char *a_name, short *a_pos);
char        yMACRO_exe_current      (uchar *a_abbr, short *a_len, short *a_pos, uchar *a_prev, uchar *a_curr);
char        yMACRO_exe_repos        (int a_pos);
uchar       yMACRO_exec             (uchar a_play);

/*===[[ yMACRO_file.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_yank             (char a_abbr, char *a_label);
char        yMACRO_paste            (char a_abbr, char *a_label);
char        yMACRO_writer           (void);
char        yMACRO_reader           (int n, char *a_verb);
char        yMACRO_export           (char a_id);
char        yMACRO_import           (char a_id);
char        yMACRO_copy             (char a_id, char a_src);
char        yMACRO_to_sreg          (char a_id, char a_reg);
char        yMACRO_central          (char a_id, char *a_string);


char        yMACRO_modeset          (char a_mode);

char        yMACRO_zero             (void);
char        yMACRO_count            (void);

char*       yMACRO__unit            (char *a_question, uchar a_abbr);



/*===[[ yMACRO_rptg.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_list             (char a_style, char *a_list);
int         yMACRO_dump             (void *a_file);
char        yMACRO_rec_status       (char a_size, short a_wide, char *a_list);
char        yMACRO_exe_status       (char a_size, short a_wide, char *a_list);
char        yMACRO_mex_status       (char a_size, short a_wide, char *a_list);
char        yMACRO_mac_status       (char a_size, short a_wide, char *a_list);
char        yMACRO_scrp_status      (char a_size, short a_wide, char *a_list);



/*===[[ yMACRO_flat.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_install_at       (uchar a_src, uchar a_dst);
char        yMACRO_install          (uchar a_src);
char        yMACRO_flatten_at       (uchar a_src, uchar a_dst);
char        yMACRO_flatten          (uchar a_src);



/*===[[ yMACRO_script.c ]]====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_skip             (void);
char        yMACRO_unskip           (void);
char        yMACRO_skipping         (void);
char        yMACRO_script_start     (char *a_name);
char        yMACRO_script_follow    (char *a_name);
char        yMACRO_script_playback  (char *a_name);
char        yMACRO_script_blitz     (char *a_name);



/*===[[ yMACRO_menu.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_menu_beg         (void);
char        yMACRO_menu_end         (void);



/*===[[ yMACRO_speed.c ]]=====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_edelay           (char a_delay);
char        yMACRO_ddelay           (char a_delay);
char        yMACRO_eupdate          (char a_update);
char        yMACRO_dupdate          (char a_update);



/*===[[ yMACRO_agrios.c ]]====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char        yMACRO_agrios_config    (void *a_getter, void *a_forcer, void *a_pusher);
char        yMACRO_agrios_hmode     (uchar a_major, uchar a_minor);
char        yMACRO_agrios_start     (char *a_label);


#endif
/*============================----end-of-source---============================*/
