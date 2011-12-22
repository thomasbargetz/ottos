/* semaphor.h
 * 
 * Copyright (c) 2011 The ottos project.
 *
 * This work is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 * 
 * This work is distributed in the hope that it will be useful, but without
 * any warranty; without even the implied warranty of merchantability or
 * fitness for a particular purpose. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *
 *  Created on: Dec 22, 2011
 *      Author: Matthias Schmid <ramsondon@gmail.com>
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include <ottos/const.h>

/*
 * Ottos Semaphor
 *
 *
 */
typedef struct semaphor_t {

} semaphor_t;

EXTERN void semaphor_init(semaphor_t* sem, int foo, int baz/* TODO: identify params */);
EXTERN int semaphor_wait(semaphor_t* sem);
EXTERN int semaphor_trywait(semaphor_t* sem);
EXTERN int semaphor_timedwait(semaphor_t* sem, const struct time_t *abs_timeout);
EXTERN int semaphor_getvalue();
EXTERN int semaphor_post();

#endif /* SEMAPHOR_H_ */
