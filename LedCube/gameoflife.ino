// Create life in a dead cell if neighbours == 4
#define GOL_CREATE_MIN 4
#define GOL_CREATE_MAX 4

// Underpopulation
#define GOL_TERMINATE_LONELY 3
// Overpopulation
#define GOL_TERMINATE_CROWDED 5

#define GOL_X 8
#define GOL_Y 8
#define GOL_Z 8

#define GOL_WRAP 0
byte tmp_data[8][8];


byte fb[8][8];

void gol_play (int del) {
  int i = 0;
  while(1) {
    i++;
    delay(del);
    gol_nextgen();
    if (gol_count_changes() == 0){
      if (searchlivevoxel() > 0){  
        delay(2000);  //pausa de 1s caso o ponto fixo tenha led aceso
        Serial.println("PF ACESO"); //remover
        return;
      }
      return;
    }
    if (i==300) //resetar caso caia no caso periodico
      return;
    if (!tmp2cube())
      return;
  }
}

void gol_nextgen (void)
{
  int x, y, z;
  unsigned char neigh;

  tmpfill(0x00);

  for (x = 0; x < GOL_X; x++)
  {
    for (y = 0; y < GOL_Y; y++)
    {
      for (z = 0; z < GOL_Z; z++)
      {
        neigh = gol_count_neighbors(x, y, z);

        // Current voxel is alive.
        if (getvoxel(x, y, z) == 0x01)
        {
          if (neigh <= GOL_TERMINATE_LONELY)
          {
            tmpclrvoxel(x, y, z);
          } else if (neigh >= GOL_TERMINATE_CROWDED)
          {
            tmpclrvoxel(x, y, z);
          } else
          {
            tmpsetvoxel(x, y, z);
          }
          // Current voxel is dead.
        } else
        {
          if (neigh >= GOL_CREATE_MIN && neigh <= GOL_CREATE_MAX)
            tmpsetvoxel(x, y, z);
        }
      }
    }
  }
}

unsigned char gol_count_neighbors (int x, int y, int z)
{
  int ix, iy, iz; // offset 1 in each direction in each dimension
  int nx, ny, nz; // neighbours address.

  unsigned char neigh = 0; // number of alive neighbours.

  for (ix = -1; ix < 2; ix++)
  {
    for (iy = -1; iy < 2; iy++)
    {
      for (iz = -1; iz < 2; iz++)
      {
        // Your not your own neighbour, exclude 0,0,0, offset.
        if ( !(ix == 0 && iy == 0 && iz == 0) )
        {
          if (GOL_WRAP == 0x01)
          {
            nx = (x + ix) % GOL_X;
            ny = (y + iy) % GOL_Y;
            nz = (z + iz) % GOL_Z;
          } else
          {
            nx = x + ix;
            ny = y + iy;
            nz = z + iz;
          }

          if ( getvoxel(nx, ny, nz) )
            neigh++;
        }
      }
    }
  }
  return neigh;
}

int gol_count_changes (void)
{
  int x, y;
  int i = 0;

  for (x = 0; x < GOL_X; x++)
  {
    for (y = 0; y < GOL_Y; y++)
    {
      if (fb[x][y] != data[x][y])
        i++;
    }
  }

  return i;
}

int tmp2cube (void)
{
  int y, z, val = 0;

  for (z = 0; z < 8; z++)
  {
    for (y = 0; y < 8; y++)
    {
      if (tmp_data[z][y] != fb[z][y])
        val = 1;
    }
  }
  if(val){

    for (z = 0; z < 8; z++){
      for (y = 0; y < 8; y++) {
        tmp_data[z][y] = data[z][y];
        data[z][y] = fb[z][y];
      }
    }
    
    return 1;
  } else {
    return 0;
  }
}

void tmpfill (unsigned char pattern)
{
  int z;
  int y;
  for (z = 0; z < 8; z++)
  {
    for (y = 0; y < 8; y++)
    {
      fb[z][y] = pattern;
    }
  }
}

void tmpsetvoxel(int x, int y, int z)
{
  if (inrange(x, y, z))
    fb[z][y] |= (1 << x);
}

void tmpclrvoxel(int x, int y, int z)
{
  if (inrange(x, y, z))
    fb[z][y] &= ~(1 << x);
}

// VERIFICAR SE EXITE LED ACESO

int searchlivevoxel(void)
{
  int x, y, z;
  int alive = 0;

  for (x = 0; x < GOL_X; x++)
  {
    for (y = 0; y < GOL_Y; y++)
    {
      for (z = 0; z < GOL_Z; z++)
      {
        if (getvoxel(x, y, z) == 0x01)
          alive++;
      }
    }
  }
  return alive;
}
