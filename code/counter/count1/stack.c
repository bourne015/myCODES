#include "common.h"

#define MAXVAL	100

static int sp = 0;
static double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error:stack full!!!\n");
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		return 0.0;
	}
}