/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1995
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>

#include "extern.h"

void
infer_fs_type(const char* path, const char** result)
{
    const char* cmd_fmt = "/usr/sbin/fstyp %s 2> /dev/null";
    char cmd[MAXPATHLEN + sizeof(cmd_fmt)];
    char fs_type[64];
    const char* fs_type_result;
    int res;
    FILE *file;

    res = snprintf(cmd, sizeof cmd, cmd_fmt, path);

    if (res < 0)
    {
        warnx("error parsing path");
        return;
    }

    if ((size_t) res > sizeof(cmd) -1)
    {
        warnx("path was too long");
        return;
    }
    
    file = popen(cmd, "r");
    
    if (file != NULL)
    {
        fscanf(file, "%s\n", fs_type);

        // If fstyp exits without error
        if (pclose(file) == 0) {
            if ((fs_type_result = strdup(fs_type)) == NULL) {
                warnx("failed to allocate result");
                return;
            }
    
            *result = fs_type_result;
        }
    }

    return;
}