#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

#include "mraa.h"

#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 8

#define ENA 3
#define ENB 6

int blink();

int sweep();

int read();