/*
 * Copyright (c) 2001 Greg Haerr <greg@censoft.com>
 *
 * Byte and word swapping header file for big/little endian mapping
 */

#ifdef linux
#include <endian.h>
#if __BYTE_ORDER == __BIG_ENDIAN
#include <byteswap.h>
#define wswap(x)	bswap_16(x)
#define dwswap(x)	bswap_32(x)
/* read little endian format from buffer*/
#define dwread(addr)	((*(unsigned char *)(addr)) | \
			 (*(unsigned char *)(addr+1) << 8) | \
			 (*(unsigned char *)(addr+2) << 16) | \
			 (*(unsigned char *)(addr+3) << 24))
#else
/* little endian - no action required*/
#define wswap(x)	(x)
#define dwswap(x)	(x)
#define dwread(addr)	(*(unsigned long *)(addr))
#endif

#elif defined(__FreeBSD__)
#include <machine/endian.h>

#if __BYTE_ORDER == __BIG_ENDIAN

#ifndef __byte_swap_word
/* Either this isn't GCC or the implementation changed. */

#warning __byte_swap_word not defined in endian.h on FreeBSD.

#define __byte_swap_word(S) ((((S) << 8) & 0xff00) | (((S) >> 8) & 0x00ff))

#define __byte_swap_long(L) ( \
 (((L) << 24) & 0xff000000) | \
 (((L) <<  8) & 0x00ff0000) | \
 (((L) >>  8) & 0x0000ff00) | \
 (((L) >> 24) & 0x000000ff) )

#endif

#define wswap(x) __byte_swap_word(x)
#define dwswap(x) __byte_swap_long(x)
/* read little endian format from buffer*/
#define dwread(addr) ((*(unsigned char *)(addr)) | \
 (*(unsigned char *)(addr+1) << 8) | \
 (*(unsigned char *)(addr+2) << 16) | \
 (*(unsigned char *)(addr+3) << 24))
#else
/* little endian - no action required*/
#define wswap(x) (x)
#define dwswap(x) (x)
#define dwread(addr) (*(unsigned long *)(addr))
#endif /* FreeBSD*/

#endif /* !linux*/
