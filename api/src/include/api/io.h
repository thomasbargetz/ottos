/* io.h
 * 
 * Copyright (c) 2011 The ottos_api project.
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
 *  Created on: 13 Jan 2012
 *      Author: Thomas Bargetz <thomas.bargetz@gmail.com>
 */

#ifndef API_IO_H_
#define API_IO_H_

#include <ottos/types.h>
#include <ottos/const.h>

#define STDIN    0
#define STDOUT   1
#define STDERR   2

/*
 * converts an integer to ascii
 * @param n number to convert
 * @param s the output buffer
 * @param b format (dec = 10)
 */
EXTERN char* itoa(int n, char* s, int b);

EXTERN char* strrev(char* str);

EXTERN void print(const char* buffer);

EXTERN size_t read_serial_with_end_char(char* buffer, size_t count, char end_character);

EXTERN size_t read_serial(char* buffer, size_t count);

#endif /* API_IO_H_ */
