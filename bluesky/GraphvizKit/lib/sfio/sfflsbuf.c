/* $Id: sfflsbuf.c,v 1.1.1.1 2004/12/23 04:04:06 ellson Exp $ $Revision: 1.1.1.1 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#include	"sfhdr.h"

/*	Write a buffer out to a file descriptor or
**	extending a buffer for a SF_STRING stream.
**
**	Written by Kiem-Phong Vo
*/

#if __STD_C
int _sfflsbuf(reg Sfio_t * f, reg int c)
#else
int _sfflsbuf(f, c)
reg Sfio_t *f;			/* write out the buffered content of this stream */
reg int c;			/* if c>=0, c is also written out */
#endif
{
    reg ssize_t n, w;
    reg uchar *data;
    uchar outc;
    reg int local, isall;
    int inpc = c;

    SFMTXSTART(f, -1);

    GETLOCAL(f, local);

    for (;; f->mode &= ~SF_LOCK) {	/* check stream mode */
	if (SFMODE(f, local) != SF_WRITE
	    && _sfmode(f, SF_WRITE, local) < 0)
	    SFMTXRETURN(f, -1);
	SFLOCK(f, local);

	/* current data extent */
	n = f->next - (data = f->data);

	if (n == (f->endb - data) && (f->flags & SF_STRING)) {	/* extend string stream buffer */
	    (void) SFWR(f, data, 1, f->disc);

	    /* !(f->flags&SF_STRING) is required because exception
	       handlers may turn a string stream to a file stream */
	    if (f->next < f->endb || !(f->flags & SF_STRING))
		n = f->next - (data = f->data);
	    else {
		SFOPEN(f, local);
		SFMTXRETURN(f, -1);
	    }
	}

	if (c >= 0) {		/* write into buffer */
	    if (n < (f->endb - (data = f->data))) {
		*f->next++ = c;
		if (c == '\n' &&
		    (f->flags & SF_LINE) && !(f->flags & SF_STRING)) {
		    c = -1;
		    n += 1;
		} else
		    break;
	    } else if (n == 0) {	/* unbuffered io */
		outc = (uchar) c;
		data = &outc;
		c = -1;
		n = 1;
	    }
	}

	if (n == 0 || (f->flags & SF_STRING))
	    break;

	isall = SFISALL(f, isall);
	if ((w = SFWR(f, data, n, f->disc)) > 0) {
	    if ((n -= w) > 0)	/* save unwritten data, then resume */
		memcpy((char *) f->data, (char *) data + w, n);
	    f->next = f->data + n;
	    if (c < 0 && (!isall || n == 0))
		break;
	} else if (w == 0) {
	    SFOPEN(f, local);
	    SFMTXRETURN(f, -1);
	} else if (c < 0)
	    break;
    }

    SFOPEN(f, local);

    if (inpc < 0)
	inpc = f->endb - f->next;

    SFMTXRETURN(f, inpc);
}
