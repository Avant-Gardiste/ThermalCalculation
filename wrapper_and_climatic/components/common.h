/****************************************************************************
**
** Copyright (C) 2018 Eric Lee.
** Contact: levanhong05@gmail.com
** Company: DFM-Engineering Vietnam
**
** This file is part of the Vitrages Decision 6.0 project.
**
**All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
**
****************************************************************************/

#pragma once

#include <math.h>

#ifndef COMMON_H
#define COMMON_H

/**
 * @brief
 *
 * @param a
 * @param b
 * @param threshold
 * @return bool
 */
inline bool equalDouble(double a, double b, double threshold = 0.00001)
{
    return abs(a - b) <= threshold;
}

/**
 * @brief
 *
 * @param d
 * @param n
 * @return double
 */
inline double round(double d, unsigned n)
{
    return floor(d * pow(10.0, n) + 0.5) / pow(10.0, n);
}

#endif // COMMON_H
