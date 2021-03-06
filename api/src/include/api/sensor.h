/* sensors.h
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
 *  Created on: 1 Feb 2012
 *      Author: Thomas Bargetz <thomas.bargetz@gmail.com>
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <ottos/types.h>
#include <ottos/const.h>

#define SENSOR_TYPE_TEMP      1
#define SENSOR_TYPE_SOLAR     2
#define SENSOR_TYPE_PRESSURE  3

typedef struct sensor_values {
    double temp;
    double pressure;
    double solar;
} sensor_values_t;

EXTERN double sensor_read_temp();
EXTERN double sensor_read_pressure();
EXTERN double sensor_read_solar();
EXTERN sensor_values_t sensor_read_values();

#endif /* SENSOR_H_ */
