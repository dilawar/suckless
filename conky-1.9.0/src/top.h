/* -*- mode: c; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*-
 * vim: ts=4 sw=4 noet ai cindent syntax=c
 *
 * Conky, a system monitor, based on torsmo
 *
 * Any original torsmo code is licensed under the BSD license
 *
 * All code written since the fork of torsmo is licensed under the GPL
 *
 * Please see COPYING for details
 *
 * Copyright (c) 2005 Adi Zaimi, Dan Piponi <dan@tanelorn.demon.co.uk>,
 *					  Dave Clark <clarkd@skynet.ca>
 * Copyright (c) 2005-2010 Brenden Matthews, Philip Kovacs, et. al.
 *	(see AUTHORS)
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _top_h_
#define _top_h_

/* Ensure there's an operating system defined.
 * compile with gcc -DOS ...
 * There is *no* default because every OS has it's own way of revealing
 * CPU/memory usage. */

/******************************************
 * Includes								  *
 ******************************************/

#include "conky.h"
#include "text_object.h"
#define CPU_THRESHHOLD	0	/* threshhold for the cpu diff to appear */
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/time.h>

#include <regex.h>
#include <pwd.h>

/******************************************
 * Defines								  *
 ******************************************/

/* XXX: I shouldn't really use this BUFFER_LEN variable but scanf is so lame
 * and it'll take me a while to write a replacement. */
#define BUFFER_LEN 1024

#define PROCFS_TEMPLATE "/proc/%d/stat"
#define PROCFS_TEMPLATE_MEM "/proc/%d/statm"
#define PROCFS_TEMPLATE_IO "/proc/%d/io"
#define PROCFS_CMDLINE_TEMPLATE "/proc/%d/cmdline"
#define MAX_SP 10	// number of elements to sort

enum top_field {
	TOP_CPU,
	TOP_NAME,
	TOP_PID,
	TOP_MEM,
	TOP_TIME,
	TOP_MEM_RES,
	TOP_MEM_VSIZE,
	TOP_UID,
	TOP_USER,
#ifdef IOSTATS
	TOP_READ_BYTES,
	TOP_WRITE_BYTES,
	TOP_IO_PERC
#endif
};

/******************************************
 * Process class						  *
 ******************************************/

struct process {
	struct process *next;
	struct process *previous;

	pid_t pid;
	char *name;
	uid_t uid;
	float amount;
	// User and kernel times are in hundredths of seconds
	unsigned long user_time;
	unsigned long total;
	unsigned long kernel_time;
	unsigned long previous_user_time;
	unsigned long previous_kernel_time;
	unsigned long total_cpu_time;
	unsigned long long vsize;
	unsigned long long rss;
#ifdef IOSTATS
	unsigned long long read_bytes;
	unsigned long long previous_read_bytes;
	unsigned long long write_bytes;
	unsigned long long previous_write_bytes;
	float io_perc;
#endif
	unsigned int time_stamp;
	unsigned int counted;
	unsigned int changed;
};

struct sorted_process {
	struct sorted_process *greater;
	struct sorted_process *less;
	struct process *proc;
};

/* Pointer to head of process list */
void process_find_top(struct process **, struct process **, struct process **
#ifdef IOSTATS
		, struct process **
#endif
		);

/* lookup a program by it's name */
struct process *get_process_by_name(const char *);

int parse_top_args(const char *s, const char *arg, struct text_object *obj);
void print_top(struct text_object *, char *, int);
void free_top(struct text_object *, int);

/* return zero on success, non-zero otherwise */
int set_top_name_width(const char *);


#endif /* _top_h_ */
