/* vim: set ts=8 sw=8 sts=8 noet tw=78:
 *
 * tup - A file-based build system
 *
 * Copyright (C) 2011-2018  Mike Shal <marfey@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include "dir_mutex.h"

int fchmodat(int dirfd, const char *pathname, mode_t mode, int flags)
{
	int rc;

	rc = dir_mutex_lock(dirfd);
	if(rc < 0)
		return rc;
	if(flags & AT_SYMLINK_NOFOLLOW) {
		fprintf(stderr, "tup error: fchmodat(AT_SYMLINK_NOFOLLOW) not supported in compat library.\n");
		rc = -1;
		errno = ENOSYS;
	} else {
		rc = chmod(pathname, mode);
	}
	dir_mutex_unlock();
	return rc;
}
