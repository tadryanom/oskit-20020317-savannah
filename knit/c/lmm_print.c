/*
 * Copyright (c) 2000 University of Utah and the Flux Group.
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

/*
 * Print useful messages for most lmm functions.
 */
#include <oskit/lmm.h>
#include <knit/c/lmm.h>
#include <oskit/machine/phys_lmm.h>
#include <stdio.h>

extern const char* prefix;

void out_add_region(lmm_region_t *lmm_region,
                    void *addr, oskit_size_t size,
                    lmm_flags_t flags, lmm_pri_t pri)
{
        printf("%s.add_region: %p %d %x %d\n", prefix, addr, size, flags, pri);
        in_add_region(lmm_region,addr,size,flags,pri);
}

void out_add_free(void *block, oskit_size_t size)
{
        printf("%s.add_free: %p %d\n", prefix, block, size);
        in_add_free(block,size);
}

void out_remove_free(void *block, oskit_size_t size)
{
        printf("%s.remove_free: %p %d\n", prefix, block, size);
        in_remove_free(block,size);
}

void *out_alloc(oskit_size_t size, lmm_flags_t flags)
{
        void* r;
        printf("%s.alloc: %d %x", prefix, size, flags);
        r = in_alloc(size,flags);
        printf(" = %p\n", r);
        return r;
}

void *out_alloc_aligned(oskit_size_t size, lmm_flags_t flags,
                        int align_bits, oskit_addr_t align_ofs)
{
        void* r;
        printf("%s.alloc_aligned: %d %x %d %x", 
               prefix, size, flags, align_bits, align_ofs);
        r = in_alloc_aligned(size,flags,align_bits,align_ofs);
        printf(" = %p\n", r);
        return r;
}

void *out_alloc_page(lmm_flags_t flags)
{
        void* r;
        printf("%s.alloc_page: %x", prefix, flags);
        r = in_alloc_page(flags);
        printf(" = %p\n", r);
        return r;
}

void *out_alloc_gen(oskit_size_t size, lmm_flags_t flags,
                    int align_bits, oskit_addr_t align_ofs,
                    oskit_addr_t bounds_min, oskit_addr_t bounds_max)
{
        void* r;
        printf("%s.alloc_aligned: %d %x %d %x %x %x", 
               prefix, size, flags,
               align_bits, align_ofs, bounds_min, bounds_max);
        r = in_alloc_gen(size,flags,align_bits,align_ofs,
                         bounds_min,bounds_max);
        printf(" = %p\n", r);
        return r;
}

oskit_size_t out_avail(lmm_flags_t flags)
{
        oskit_size_t r;
        r = in_avail(flags);
        return r;
}

void out_find_free(oskit_addr_t *inout_addr,
                   oskit_size_t *out_size, lmm_flags_t *out_flags)
{
        in_find_free(inout_addr,out_size,out_flags);
}

void out_free(void *block, oskit_size_t size)
{
        printf("%s.free: %p %d\n", prefix, block, size);
        in_free(block,size);
}

void out_free_page(void *block)
{
        printf("%s.free_page: %p\n", prefix, block);
        in_free_page(block);
}

/* Only available if debugging turned on.  */
void out_dump(void)
{
        in_dump();
}

void out_stats(void)
{
        in_stats();
}
