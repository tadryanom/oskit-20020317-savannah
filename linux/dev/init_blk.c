/*
 * Copyright (c) 1997, 1998, 1999 The University of Utah and the Flux Group.
 * 
 * This file is part of the OSKit Linux Glue Libraries, which are free
 * software, also known as "open source;" you can redistribute them and/or
 * modify them under the terms of the GNU General Public License (GPL),
 * version 2, as published by the Free Software Foundation (FSF).
 * 
 * The OSKit is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GPL for more details.  You should have
 * received a copy of the GPL along with the OSKit; see the file COPYING.  If
 * not, write to the FSF, 59 Temple Place #330, Boston, MA 02111-1307, USA.
 */

#include <oskit/dev/linux.h>
#include <linux/autoconf.h>		/* CONFIG_foo */

#include "glue.h"

void oskit_linux_init_blk(void)
{
#ifdef CONFIG_BLK_DEV_IDE
	INIT_DRIVER(ide, "IDE driver");
#endif

#ifdef CONFIG_SCSI
	oskit_linux_init_scsi();
#endif

#ifdef CONFIG_BLK_DEV_FD
	INIT_DRIVER(floppy, "Floppy disk driver");
#endif
}
