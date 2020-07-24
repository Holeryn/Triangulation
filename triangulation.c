#include "triangulation.h"

#define GFX_WIDTH 500
#define GFX_HEIGHT 500

int nvertices;

int main(int argc, char *argv[]){
  gfx_open(GFX_WIDTH,GFX_HEIGHT,"triangulitation");
  gfx_color(255,250,250);

  srand(time(NULL));

  ReadVertices(argv[1][0] == '0' ? 0 : 1);
  printf("vertices readed\n");
  PrintVertices();
  gfx_flush();
  printf("Triangulating\n");
  gfx_color(46,246,0);
  Triangulate();
  pause();
}

void PrintVertices(void){
  tVertex v;
  v = vertices;
  for(int i = 0; i <= nvertices; i++ , v = v->next){
    gfx_line(v->v[X],v->v[Y],v->next->v[X],v->next->v[Y]);
    printf("vertix:%d x:%d y:%d\n",v->vnum,v->v[X],v->v[Y]);
  }
}

void ReadVertices(int mode)
{
  if(mode == 0){
    int i;
    tVertex	v;

    nvertices = rand() % 15 + 3;

    printf("%d\n",nvertices);
    for (i = 0; i <= (nvertices - 1); i++)  {
      v = MakeNullVertex();

      v->v[X] = rand() % GFX_WIDTH / 2;
      v->v[Y] = rand() % GFX_HEIGHT / 2;
      v->vnum = i;
    }

    v = MakeNullVertex();
    v->v[X] = vertices->v[X];
    v->v[Y] = vertices->v[Y];
    v->vnum = i + 1;
  }else{
    tVertex	v;
    int		x, y;
    int		vnum = 0;

    printf("Inserisci le coordinate: \n");
    scanf ("%d %d", &x, &y );
    while (x != GFX_WIDTH + 1 && y != GFX_HEIGHT + 1)  {
      v = MakeNullVertex();
      v->v[X] = x;
      v->v[Y] = y;
      v->vnum = vnum++;
      scanf ("%d %d", &x, &y );
    }

    nvertices = vnum;
  }

  if (nvertices < 3){
    printf("%%Error in ReadVertices: nvertices=%d<3\n", nvertices);
    exit(EXIT_FAILURE);
  }
}

tVertex   MakeNullVertex( void )
{
  tVertex  v;

  NEW( v, tsVertex );
  ADD( vertices, v );
  return v;
}

void PrintDiagonal(tVertex v1,tVertex v2){
  printf("Disegnando la diagonale\n");
  gfx_line(v1->v[X],v1->v[Y],v2->v[X],v2->v[Y]);
  gfx_flush();
}

void Triangulate(){
   tVertex v0, v1, v2, v3, v4;	/* five consecutive vertices */
   int   n = nvertices;		/* number of vertices; shrinks to 3. */

   EarInit();
   printf("\nnewpath\n");
   /* Each step of outer loop removes one ear. */
   while ( n > 3 ) {
      /* Inner loop searches for an ear. */
      v2 = vertices;
      do {
         if (v2->ear) {
            /* Ear found. Fill variables. */
            v3 = v2->next; v4 = v3->next;
            v1 = v2->prev; v0 = v1->prev;

            /* (v1,v3) is a diagonal */
            PrintDiagonal( v1, v3 );

            /* Update earity of diagonal endpoints */
            v1->ear = Diagonal( v0, v3 );
            v3->ear = Diagonal( v1, v4 );

            /* Cut off the ear v2 */
            v1->next = v3;
            v3->prev = v1;
            vertices = v3;	/* In case the head was v2. */
            n--;
            break;   /* out of inner loop; resume outer loop */
         } /* end if ear found */
         v2 = v2->next;
      } while ( v2 != vertices );
   } /* end outer while loop */
   printf("closepath stroke\n\n");
}

void EarInit(void){
  tVertex v0,v1,v2; // Three consecutive vertices

  // Init v1->ear for all vertices
  v1 = vertices;
  do {
    v2 = v1->next;
    v0 = v1->prev;
    v1->ear = Diagonal(v0,v2);
    v1 = v1->next;
  }while(v1 != vertices);
}
