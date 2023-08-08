/*============================----beg-of-source---============================*/
#ifndef yMACRO
#define yMACRO yes



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
char        yMACRO_agrios_status    (char a_size, short a_wide, char *a_list);



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
char        yMACRO_agrios_follow    (char *a_label);
char        yMACRO_agrios_playback  (char *a_label);
char        yMACRO_agrios_blitz     (char *a_label);
char        yMACRO_agrios_direct    (char a_active, char *a_content);


#endif
/*============================----end-of-source---============================*/
