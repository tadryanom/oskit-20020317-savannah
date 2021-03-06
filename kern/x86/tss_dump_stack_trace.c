/*
 * Copyright (c) 1994, 1998 University of Utah and the Flux Group.
 * All rights reserved.
 * 
 * This file is part of the Flux OSKit.  The OSKit is free software, also known
 * as "open source;" you can redistribute it and/or modify it under the terms
 * of the GNU General Public License (GPL), version 2, as published by the Free
 * Software Foundation (FSF).  To explore alternate licensing terms, contact
 * the University of Utah at csl-dist@cs.utah.edu or +1-801-585-3271.
 * 
 * The OSKit is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GPL for more details.  You should have
 * received a copy of the GPL along with the OSKit; see the file COPYING.  If
 * not, write to the FSF, 59 Temple Place #330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <oskit/x86/tss.h>

void
tss_dump_stack_trace(struct x86_tss *tss, int max_levels)
{
	unsigned int *fp, i;
	
	fp = (unsigned int *)tss->ebp;

	printf("Backtrace from TSS EBP:");
	for (i = 0; i < max_levels; i++) {
#if 1
		printf("\n%08x:", (unsigned int)fp);
		
#else
		if ((i % 8) == 0)
			printf("\n");
#endif			
		fp = (int *)(*fp);
		if (!(*(fp + 1) && *fp))
			break;

		printf(" %08x", *(fp + 1));
	}
	printf("\n");
}
