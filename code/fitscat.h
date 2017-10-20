/*
 *				fitscat.h
 *
 * Main include file for the LDACTools FITS library.
 *
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *
 *	This file part of:	AstrOmatic FITS/LDAC library
 *
 *	Copyright:		(C) 1995-2012 Emmanuel Bertin -- IAP/CNRS/UPMC
 *
 *	License:		GNU General Public License
 *
 *	AstrOmatic software is free software: you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation, either version 3 of the
 *	License, or (at your option) any later version.
 *	AstrOmatic software is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	You should have received a copy of the GNU General Public License
 *	along with AstrOmatic software.
 *	If not, see <http://www.gnu.org/licenses/>.
 *
 *	Last modified:		29/08/2012
 *
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef _FITSCAT_H_
#define _FITSCAT_H_

#include <stdio.h>

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#define	MAXCHARS	256	/* max. number of characters */
#define WARNING_NMAX	1000	/* max. number of recorded warnings */

/*---------------------------- return messages ------------------------------*/

#ifndef	RETURN_OK
#define	RETURN_OK		0
#endif
#ifndef	RETURN_ERROR
#define	RETURN_ERROR		(-1)
#endif
#ifndef	RETURN_FATAL_ERROR
#define	RETURN_FATAL_ERROR	(-2)
#endif

/*--------------------------- FITS BitPix coding ----------------------------*/

#define		BP_BYTE		8
#define		BP_SHORT	16
#define		BP_LONG		32
#define		BP_LONGLONG	64
#define		BP_FLOAT	(-32)
#define		BP_DOUBLE	(-64)

/*-------------------------------- macros -----------------------------------*/

/* Standard FITS name suffix*/

#define		FITS_SUFFIX		".fits"	

/* size (in bytes) of one FITS block */

#define		FBSIZE		2880L	

/* FITS size after adding padding */

#define		PADTOTAL(x)	(((x-1)/FBSIZE+1)*FBSIZE)

/* extra size to add for padding */

#define		PADEXTRA(x)	((FBSIZE - (x%FBSIZE))% FBSIZE)

/*--------------------------------- typedefs --------------------------------*/

typedef enum            {H_INT, H_FLOAT, H_EXPO, H_BOOL, H_STRING, H_STRINGS,
    H_COMMENT, H_HCOMMENT, H_KEY}	h_type;
/* type of FITS-header data */
typedef enum		{T_BYTE, T_SHORT, T_LONG, T_LONGLONG,
    T_FLOAT, T_DOUBLE, T_STRING}
    t_type;		/* Type of data */
    typedef enum		{WRITE_ONLY, READ_ONLY}
    access_type_t;	/* Type of access */
    typedef enum		{SHOW_ASCII, SHOW_SKYCAT}
    output_type;    /* Type of output */

    typedef	float		PIXTYPE;		/* Pixel type */
    typedef	unsigned int	FLAGTYPE;		/* Flag type */

#ifdef	HAVE_UNSIGNED_LONG_LONG_INT
    typedef	unsigned long long		KINGSIZE_T;	/* for large sizes */
    typedef unsigned long long		ULONGLONG;
#else
    typedef	size_t				KINGSIZE_T;/* better than nothing */
    typedef union {unsigned int l[2];}	ULONGLONG;
#endif
#ifdef HAVE_LONG_LONG_INT
    typedef long long			SLONGLONG;
#else
    typedef union {int l[2];}		SLONGLONG;
#endif

#if defined(_FILE_OFFSET_BITS) && !defined(OFF_T)
#define OFF_T	off_t
#else
#define OFF_T	long
#endif

    /*------------------------------- constants ---------------------------------*/

    extern const int	t_size[]; /* size in bytes per t_type (see fitshead.c) */

    /*---------------------------------- key ------------------------------------*/

    typedef struct structkey
{
    char		name[80];		/* name */
    char		comment[80];		/* a comment */
    void		*ptr;			/* pointer to the data */
    h_type	htype;			/* standard ``h_type'' (display) */
    t_type	ttype;			/* standard ``t_type'' (storage) */
    char		printf[80];		/* printing format (C Convention) */
    char		unit[80];		/* physical unit */
    char		voucd[80];		/* VO ucd */
    char		vounit[80];		/* VO unit */
    int		naxis;			/* number of dimensions */
    int		*naxisn;		/* pointer to an array of dim. */
    int		nobj;			/* number of objects */
    int		nbytes;			/* number of bytes per element */
    long		pos;			/* position within file */
    struct structkey	*prevkey;	/* previous key within the chain */
    struct structkey	*nextkey;	/* next key within the chain */
    struct structtab	*tab;		/* (original) parent tab */
    int         allocflag;              /* true if ptr dynamically allocated */
}		keystruct;

/*------------------------------- catalog  ---------------------------------*/

typedef struct structcat
{
    char		filename[MAXCHARS];	/* file name */
    FILE		*file;			/* pointer to the file structure */
    struct structtab *tab;		/* pointer to the first table */
    int		ntab;			/* number of tables included */
    access_type_t	access_type;		/* READ_ONLY or WRITE_ONLY */
}		catstruct;

/*-------------------------------- table  ----------------------------------*/

typedef struct structtab
{
    int		bitpix;			/* bits per element */
    int		bytepix;		/* bytes per element */
    int		bitsgn;			/* = 0 if unsigned data */
    double	bscale;			/* data scale factor */
    double	bzero;			/* data offset parameter */
    int		blank;			/* integer code for undefined values */
    int		blankflag;		/* set if a blank keyword was found */
    enum {COMPRESS_NONE, COMPRESS_BASEBYTE, COMPRESS_PREVPIX}
    compress_type;		/* image compression type */
    char		*compress_buf;		/* de-compression buffer */
    char		*compress_bufptr;	/* present pixel in buffer */
    int		compress_curval;	/* current pixel or checksum value */
    int		compress_checkval;	/* foreseen pixel or checksum value */
    size_t	compress_npix;		/* remaining pixels in buffer */
    int		naxis;			/* number of dimensions */
    int		*naxisn;		/* array of dimensions */
    int		tfields;		/* number of fields */
    int		pcount, gcount;		/* alignment of the data */
    KINGSIZE_T	tabsize;		/* total table size (bytes) */
    char		xtension[82];		/* FITS extension type */
    char		extname[82];		/* FITS extension name */
    char		*headbuf;		/* buffer containing the header */
    int		headnblock;		/* number of FITS blocks */
    char		*bodybuf;		/* buffer containing the body */
    OFF_T		bodypos;		/* position of the body in the file */
    OFF_T		headpos;		/* position of the head in the file */
    struct structcat *cat;		/* (original) parent catalog */
    struct structtab *prevtab, *nexttab;	/* previous and next tab in chain */
    int		seg;			/* segment position */
    int		nseg;			/* number of tab segments */
    keystruct	*key;			/* pointer to keys */
    int		nkey;			/* number of keys */
    int		swapflag;		/* mapped to a swap file ? */
    char		swapname[MAXCHARS];	/* name of the swapfile */
    unsigned int	bodysum;		/* Checksum of the FITS body */
}		tabstruct;

#endif // _FITSCAT_H_
