/**
 * @mainpage
 * Most of the FITS documentation is included in the fits.h file.
 */

/**
 * @file fits.h
 * @brief Fits API
 */
#ifndef FITS_H
#define FITS_H

#include "fitscat.h"
#include "fitscat_defs.h"

/**
 * @see fitsread.c
 */
catstruct *new_cat(int ncat);

/**
 * @see fitsread.c
 */


/**
 * @see fitsread.c
 */
catstruct *read_cat(char *filename);

/**
 * @see fitsread.c
 */
catstruct *read_cats(char **filenames, int ncat);

/**
 * @see fitscat.c
 */
int	about_cat(catstruct *cat, FILE *stream);


extern tabstruct	*asc2bin_tab(catstruct *catin, char *tabinname, 
        catstruct *catout, char *taboutname),
       *init_readobj(tabstruct *tab, char **pbuf),
       *name_to_tab(catstruct *cat, char *tabname, int seg),
       *new_tab(char *tabname),
       *pos_to_tab(catstruct *cat, int pos, int seg);

extern keystruct	*name_to_key(tabstruct *tab, char *keyname),
       *new_key(char *keyname),
       *pos_to_key(tabstruct *tab, int pos),
       *read_key(tabstruct *tab, char *keyname);

extern void	add_cleanupfilename(char *filename),
       cleanup_files(void),
       copy_tab_fromptr(tabstruct *tabin, catstruct *catout, int pos),
       encode_checksum(unsigned int sum, char *str),
       end_readobj(tabstruct *keytab, tabstruct *tab, char *buf),
       end_writeobj(catstruct *cat, tabstruct *tab, char *buf),
       error(int, char *, char *),
       error_installfunc(void (*func)(char *msg1, char *msg2)),
       fixexponent(char *s),
       free_body(tabstruct *tab),
       free_cat(catstruct *cat),
       free_cats(catstruct **cat, int ncat),
       free_key(keystruct *key),
       free_tab(tabstruct *tab),
       init_writeobj(catstruct *cat, tabstruct *tab, char **pbuf),
       install_cleanup(void (*func)(void)),
       print_obj(FILE *stream, tabstruct *tab),
       read_keys(tabstruct *tab, char **keynames, keystruct **keys,
               int nkeys, unsigned char *mask),
       read_basic(tabstruct *tab),
       read_body(tabstruct *tab, PIXTYPE *ptr, size_t size),
       read_ibody(tabstruct *tab, FLAGTYPE *ptr, size_t size),
       readbasic_head(tabstruct *tab),
       remove_cleanupfilename(char *filename),
       save_cat(catstruct *cat, char *filename),
       save_tab(catstruct *cat, tabstruct *tab),
       show_keys(tabstruct *tab, char **keynames, keystruct **keys,
               int nkeys, unsigned char *mask, FILE *stream,
               int strflag,int banflag, int leadflag,
               output_type o_type),
       swapbytes(void *, int, int),
       ttypeconv(void *ptrin, void *ptrout,
               t_type ttypein, t_type ttypeout),
       voprint_obj(FILE *stream, tabstruct *tab),
       warning(char *, char *),
       write_body(tabstruct *tab, PIXTYPE *ptr, size_t size),
       write_ibody(tabstruct *tab, FLAGTYPE *ptr, size_t size),
       write_checksum(tabstruct *tab);

extern char	*tdisptoprintf(char *tdisp, char *str),
       *printftotdisp(char *cprintf, char *str),
       *fitsnfind(char *fitsbuf, char *str, int nblock),
       **tabs_list(catstruct *cat, int *n),
       **keys_list(tabstruct *tab, int *n),
       *warning_history(void);

extern unsigned int
compute_blocksum(char *buf, unsigned int sum),
    compute_bodysum(tabstruct *tab, unsigned int sum),
    decode_checksum(char *str);

extern int about_tab(catstruct *cat, char *tabname, FILE *stream),
       addhistoryto_cat(catstruct *cat, char *str),
       add_key(keystruct *key, tabstruct *tab, int pos),
       addkeyto_head(tabstruct *tab, keystruct *key),
       addkeywordto_head(tabstruct *tab, char *keyword,char *comment),
       add_tab(tabstruct *tab, catstruct *cat, int pos),
       blank_keys(tabstruct *tab),
       close_cat(catstruct *cat),
       copy_key(tabstruct *tabin, char *keyname, tabstruct *tabout,
               int pos),
       copy_tab(catstruct *catin, char *tabname, int seg,
               catstruct *catout, int pos),
       copy_tabs(catstruct *catin, catstruct *catout),
       copy_tabs_blind(catstruct *catin, catstruct *catout),
       ext_head(tabstruct *tab),
       findkey(char *, char *, int),
       findnkey(char *, char *, int, int),
       fitsadd(char *fitsbuf, char *keyword, char *comment),
       fitsfind(char *fitsbuf, char *keyword),
       fitspick(char *fitsbuf, char *keyword, void *ptr,
               h_type *htype, t_type *ttype, char *comment),
       fitsread(char *fitsbuf, char *keyword, void *ptr,
               h_type htype, t_type ttype),
       fitsremove(char *fitsbuf, char *keyword),
       fitswrite(char *fitsbuf, char *keyword, void *ptr,
               h_type htype, t_type ttype),
       get_head(tabstruct *tab),
       inherit_cat(catstruct *catin, catstruct *catout),
       init_cat(catstruct *cat),
       map_cat(catstruct *cat),
       open_cat(catstruct *cat, access_type_t at),
       pad_tab(catstruct *cat, KINGSIZE_T size),
       prim_head(tabstruct *tab),
       readbintabparam_head(tabstruct *tab),
       read_field(tabstruct *tab, char **keynames, keystruct **keys,
               int nkeys, int field, tabstruct *ftab),
       read_obj(tabstruct *keytab, tabstruct *tab, char *buf),
       read_obj_at(tabstruct *keytab, tabstruct *tab, char *buf,
               long pos),
       remove_key(tabstruct *tab, char *keyname),
       remove_keys(tabstruct *tab),
       removekeywordfrom_head(tabstruct *tab, char *keyword),
       remove_tab(catstruct *cat, char *tabname, int seg),
       remove_tabs(catstruct *cat),
       save_head(catstruct *cat, tabstruct *tab),
       set_maxram(size_t maxram),
       set_maxvram(size_t maxvram),
       set_swapdir(char *dirname),
       tab_row_len(char *, char *),
       tformof(char *str, t_type ttype, int n),
       tsizeof(char *str),
       update_head(tabstruct *tab),
       update_tab(tabstruct *tab),
       verify_checksum(tabstruct *tab),
       write_obj(tabstruct *tab, char *buf),
       wstrncmp(char *, char *, int);

extern PIXTYPE	*alloc_body(tabstruct *tab,
        void (*func)(PIXTYPE *ptr, int npix));

extern FLAGTYPE	*alloc_ibody(tabstruct *tab,
        void (*func)(FLAGTYPE *ptr, int npix));

extern t_type	ttypeof(char *str);

extern  void	error(int, char *, char *),
        swapbytes(void *ptr, int nb, int n),
        warning(char *msg1, char *msg2);


int		bswapflag;


/**
 * end
 */

#endif // FITS_H

