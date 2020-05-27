#ifndef ATTACH_H
#define ATTACH_H

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <string>
#include <sstream>
#include <fstream>

// need these for directory manipulation
#include <direct.h>
#include <errno.h>

#include <cmath>
#include <complex> 

#include <algorithm> // weird that you need this to define std::max

// Constants
static const double EPS=(1.0e-16);
static const double FPMIN=(1.0e-30);

static const double p=(atan(1.0)); // pi / 4
static const double Two_PI=(8.0*p); // 2 pi
static const double PI=(4.0*p); // pi
static const double PI_2=(2.0*p); // pi / 2
static const double PI_3=((4.0/3.0)*p); // pi / 3
static const double PI_4=(p); // pi / 4
static const double PI_5=((4.0/5.0)*p); // pi / 5
static const double PI_6=((2.0/3.0)*p); // pi / 6

#include "Templates.h"
#include "Useful.h"
#include "Chebyshev_Approximation.h"
#include "Special_Functions.h"
#include "Probability_Functions.h"

#endif