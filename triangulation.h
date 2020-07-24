#ifndef TRIANGULITATION
#define TRIANGULITATION

#include <stdlib.h>
#include <time.h>

#include "predicates.h"
#include "vertex.h"
#include "include/gfx.h"
#include "point.h"
#include "unistd.h"

void EarInit(void);
void Triangulate(void);
void ReadVertices(int mode);
void PrintVertices(void);
void PrintDiagonal(tVertex v1,tVertex v2);
tVertex   MakeNullVertex( void );

#endif
