/*
 * Copyright (c) 2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "exceptions.h"
#include "log.h"

static void dumpStackFrame(const ExceptionStackFrame *frame, bool sameEl)
{
#ifndef NDEBUG
    for (u32 i = 0; i < 30; i += 2) {
        serialLog("x%d\t\t%08lx\t\tx%d\t\t%08lx\r\n", i, frame->x[i], i + 1, frame->x[i + 1]);
    }

    serialLog("x30\t\t%08lx\r\n\r\n", frame->x[30]);
    serialLog("elr_el2\t\t%08lx\r\n", frame->elr_el2);
    serialLog("spsr_el2\t%08lx\r\n", frame->spsr_el2);
    if (sameEl) {
        serialLog("sp_el2\t\t%08lx\r\n", frame->sp_el2);
    } else {
        serialLog("sp_el0\t\t%08lx\r\n", frame->sp_el0);
    }
    serialLog("sp_el1\t\t%08lx\r\n", frame->sp_el1);
#endif
}

void handleLowerElSyncException(ExceptionStackFrame *frame, u32 esr)
{
    serialLog("Lower EL sync exception, ESR = 0x%08lx\r\n", esr);
    dumpStackFrame(frame, false);
}

void handleSameElSyncException(ExceptionStackFrame *frame, u32 esr)
{
    serialLog("Same EL sync exception, ESR = 0x%08lx\r\n", esr);
    dumpStackFrame(frame, true);
}

void handleUnknownException(u32 offset)
{
    serialLog("Unknown exception! (offset 0x%03lx)\r\n", offset);
}