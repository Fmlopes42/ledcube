//Liga os leds do segundo (de baixo para cima) plano horizontal de forma circular.
void effect_test (void)
{

  int x, y, i;

  for (i = 0; i < 1000; i++)
  {
    x = sin(i / 8) * 2 + 3.5;
    y = cos(i / 8) * 2 + 3.5;

    setvoxel(x, y, 1);
    setvoxel(x, y, 1);
    delay_ms(1000);
    fill(0x00);
  }

}


//void effext_stringfly2 (char *str, char axis, char mirror, char direction, int delay, int space)
//Escreve uma string na matriz.
void effect_stringfly2(char * str)
{
  int x, y, i, ii;
  int state;

  unsigned char chr[5];

  while (*str)
  {
    font_getchar(*str++, chr);

    for (x = 0; x < 5; x++)
    {
      for (y = 0; y < 8; y++)
      {
        if ((chr[x] & (0x80 >> y)))
        {
          setvoxel(7, x + 2, y);
        }
      }
    }

    for (ii = 0; ii < 6; ii++)
    {
      delay_ms(1500);
      for (i = 0; i < 7; i++)
      {
        for (x = 0; x < 8; x++)
        {
          for (y = 0; y < 8; y++)
          {
            state = getvoxel(i + 1, x, y);
            altervoxel(i, x, y, state);
          }
        }
      }
      for (x = 0; x < 8; x++)
      {
        for (y = 0; y < 8; y++)
        {
          clrvoxel(7, x, y);
        }
      }
    }
  }
  for (ii = 0; ii < 8; ii++)
  {
    delay_ms(1500);
    for (i = 0; i < 7; i++)
    {
      for (x = 0; x < 8; x++)
      {
        for (y = 0; y < 8; y++)
        {
          state = getvoxel(i + 1, x, y);
          altervoxel(i, x, y, state);
        }
      }
    }
    for (x = 0; x < 8; x++)
    {
      for (y = 0; y < 8; y++)
      {
        clrvoxel(7, x, y);
      }
    }
  }

}

//Liga todos os leds de cada plano sequencialmente em uma direcao (plane) e em 
//uma velocidade (speed) em milisegundos. Os valores para plane sao 1, 2 ou 3.
void effect_planboing (int plane, int speed)
{
  int i;
  for (i = 0; i < 8; i++)
  {
    fill(0x00);
    if (plane == AXIS_Z)
      setplane_z(i);

    if (plane == AXIS_X)
      setplane_x(i);

    if (plane == AXIS_Y)
      setplane_y(i);

    delay_ms(speed);
  }

  for (i = 7; i >= 0; i--)
  {
    fill(0x00);
    if (plane == AXIS_Z)
      setplane_z(i);

    if (plane == AXIS_X)
      setplane_x(i);

    if (plane == AXIS_Y)
      setplane_y(i);

    delay_ms(speed);
  }
}

//Semelhante ao effect_planboing mas percorre cada plano varias vezes muito rapidamente.
void effect_blinky2()
{
  int i, r;
  fill(0x00);

  for (r = 0; r < 2; r++)
  {
    i = 750;
    while (i > 0)
    {
      fill(0x00);
      delay_ms(i);

      fill(0xff);
      delay_ms(100);

      i = i - (15 + (1000 / (i / 10)));
    }

    delay_ms(1000);

    i = 750;
    while (i > 0)
    {
      fill(0x00);
      delay_ms(751 - i);

      fill(0xff);
      delay_ms(100);

      i = i - (15 + (1000 / (i / 10)));
    }
  }

}

//Desnha uma caixa de leds expandindo e retraindo por (iterations) vezes a partir de 
//um dos vertices (direction) do cubo em um certo tempo (delay).
//(mode) 2 liga os leds das faces, 3 liga todos os leds do cubo, qualquer outro valor 
//liga apenas os led dos vertices do cubo.
void effect_box_shrink_grow (int iterations, int mode, int direction, uint16_t delay)
{
  int x;
  int i;

  int x1 = 0;
  int y1 = 0;
  int z1 = 0;
  int x2 = 0;
  int y2 = 0;
  int z2 = 0;


  for (x = 0; x < iterations; x++)
  {
    for (i = 7; i >= 0; i--)
    {
      if (direction == 0)
      {
        // Dette funker ogs�..
        // memcpy(test, (int[]){1, 2, 3, 4, 5, 6}, 6 * sizeof(int));
        x1 = 0; y1 = 0; z1 = 0; x2 = i; y2 = i; z2 = i;
      }

      if (direction == 1) // fail
      {
        x1 = 0; y1 = 0; z1 = 7 - i; x2 = i; y2 = i; z2 = 7;
      }

      if (direction == 2)
      {
        x1 = 0; y1 = 7; z1 = 0; x2 = i; y2 = 7 - i; z2 = i;
      }

      if (direction == 3) //fail
      {
        x1 = 0; y1 = 7; z1 = 7; x2 = i; y2 = 7 - i; z2 = 7 - i;
      }

      if (direction == 4) //fail
      {
        x1 = 7; y1 = 0; z1 = 0; x2 = 7 - i; y2 = i; z2 = i;
      }

      if (direction == 5)
      {
        x1 = 7; y1 = 0; z1 = 7; x2 = 7 - i; y2 = i; z2 = 7 - i;
      }

      if (direction == 6) //fail
      {
        x1 = 7; y1 = 7; z1 = 0; x2 = 7 - i; y2 = 7 - i; z2 = i;
      }

      if (direction == 7)
      {
        x1 = 7; y1 = 7; z1 = 7; x2 = 7 - i; y2 = 7 - i; z2 = 7 - i;
      }

      if (mode == 3)
      {
        box_filled(x1, y1, z1, x2, y2, z2);
      }
      else if (mode == 2)
      {
        box_walls(x1, y1, z1, x2, y2, z2);
      }
      else
      {
        box_wireframe(x1, y1, z1, x2, y2, z2);
      }

      delay_ms(delay);
      fill(0x00);
    }
    for (i = 0; i < 8; i++)
    {
      if (direction == 0)
      {
        x1 = 0; y1 = 0; z1 = 0; x2 = i; y2 = i; z2 = i;
      }

      if (direction == 1) // fail
      {
        x1 = 0; y1 = 0; z1 = 7 - i; x2 = i; y2 = i; z2 = 7;
      }

      if (direction == 2)
      {
        x1 = 0; y1 = 7; z1 = 0; x2 = i; y2 = 7 - i; z2 = i;
      }

      if (direction == 3) //fail
      {
        x1 = 0; y1 = 7; z1 = 7; x2 = i; y2 = 7 - i; z2 = 7 - i;
      }

      if (direction == 4) //fail
      {
        x1 = 7; y1 = 0; z1 = 0; x2 = 7 - i; y2 = i; z2 = i;
      }

      if (direction == 5)
      {
        x1 = 7; y1 = 0; z1 = 7; x2 = 7 - i; y2 = i; z2 = 7 - i;
      }

      if (direction == 6) //fail
      {
        x1 = 7; y1 = 7; z1 = 0; x2 = 7 - i; y2 = 7 - i; z2 = i;
      }

      if (direction == 7)
      {
        x1 = 7; y1 = 7; z1 = 7; x2 = 7 - i; y2 = 7 - i; z2 = 7 - i;
      }

      if (mode == 3)
      {
        box_filled(x1, y1, z1, x2, y2, z2);
      }
      else if (mode == 2)
      {
        box_walls(x1, y1, z1, x2, y2, z2);
      }
      else
      {
        box_wireframe(x1, y1, z1, x2, y2, z2);
      }

      delay_ms(delay);
      fill(0x00);
    }
  }
}

//Semelhante ao effect_box_shrink_grow com mode 1, mas comeca no centro do 
//cubo se (grow) = 1 ou na borda se (grow) = 2.
void effect_box_woopwoop (int delay, int grow)
{
  int i;

  fill(0x00);
  if (grow == 1)
  {
    for (i = 0; i < 4; i++)
    {
      box_wireframe(4 + i, 4 + i, 4 + i, 3 - i, 3 - i, 3 - i);
      delay_ms(delay);
      fill(0x00);
    }
  } else
  {
    for (i = 3; i >= 0; i--)
    {
      box_wireframe(4 + i, 4 + i, 4 + i, 3 - i, 3 - i, 3 - i);
      delay_ms(delay);
      fill(0x00);
    }
  }
}


// Send a voxel flying from one side of the cube to the other
// It its at the bottom, send it to the top..
//Liga sequencialmente uma linha de leds partindo da base para o topo do cubo em (delay) milisegundos.
//o ponto da base de onde parte a linha de leds e o ponto (x) (y).
void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay)
{
  int i, ii;
  for (i = 0; i < 8; i++)
  {
    if (z == 7)
    {
      ii = 7 - i;
      clrvoxel(x, y, ii + 1);
    } else
    {
      ii = i;
      clrvoxel(x, y, ii - 1);
    }
    setvoxel(x, y, ii);
    delay_ms(delay);
  }
}

// Send all the voxels from one side of the cube to the other
// Start at z and send to the opposite side.
// Sends in random order.
//Liga o (z)esimo (da base para o topo) plano horizontal de leds e 
//envia linhas de leds para o topo. 
//Semelhantes a bolhas ubindo em um copo de refrigerante.
void sendplane_rand_z (unsigned char z, int delay, int wait)
{
  unsigned char loop = 16;
  unsigned char x, y;

  fill(0x00);

  setplane_z(z);

  // Send voxels at random untill all 16 have crossed the cube.
  while (loop)
  {
    x = random() % 4;
    y = random() % 4;
    if (getvoxel(x, y, z))
    {
      // Send the voxel flying
      sendvoxel_z(x, y, z, delay);
      delay_ms(wait);
      loop--; // one down, loop-- to go. when this hits 0, the loop exits.
    }
  }
}

// For each coordinate along X and Y, a voxel is set either at level 0 or at level 7
// for n iterations, a random voxel is sent to the opposite side of where it was.
void sendvoxels_rand_z (int iterations, int delay, int wait)
{
  unsigned char x, y, last_x, last_y, i;

  last_x = 0;
  last_y = 0;

  fill(0x00);

  //srand(123);

  // Loop through all the X and Y coordinates
  for (x = 0; x < 8; x++)
  {
    for (y = 0; y < 8; y++)
    {
      // Then set a voxel either at the top or at the bottom
      if (random() % 2 == 0)
      {

        setvoxel(x, y, 0);
      } else
      {
        setvoxel(x, y, 7);
      }


    }
  }

  for (i = 0; i < iterations; i++)
  {
    // Pick a random x,y position
    x = random() % 8;
    y = random() % 8;
    // but not the sameone twice in a row
    if (y != last_y && x != last_x)
    {
      // If the voxel at this x,y is at the bottom
      if (getvoxel(x, y, 0))
      {
        // send it to the top
        sendvoxel_z(x, y, 0, delay);
      } else
      {
        // if its at the top, send it to the bottom
        sendvoxel_z(x, y, 7, delay);
      }
      delay_ms(wait);

      // Remember the last move
      last_y = y;
      last_x = x;
    }
  }

}


// Big ugly function :p but it looks pretty
void boingboing(uint16_t iterations, int delay, unsigned char mode, unsigned char drawmode)
{
  fill(0x00);		// Blank the cube

  int x, y, z;		// Current coordinates for the point
  int dx, dy, dz;	// Direction of movement
  int lol, i;		// lol?
  unsigned char crash_x, crash_y, crash_z;

  // Coordinate array for the snake.
  int snake[8][3];
  for (i = 0; i < 8; i++)
  {
    snake[i][0] = 4;
    snake[i][1] = 4;
    snake[i][2] = 4;
  }

  y = random() % 8;
  x = random() % 8;
  z = random() % 8;

  dx = 1;
  dy = 1;
  dz = 1;

  while (iterations)
  {
    crash_x = 0;
    crash_y = 0;
    crash_z = 0;


    // Let's mix things up a little:
    if (random() % 3 == 0)
    {
      // Pick a random axis, and set the speed to a random number.
      lol = random() % 3;
      if (lol == 0)
        dx = random() % 3 - 1;

      if (lol == 1)
        dy = random() % 3 - 1;

      if (lol == 2)
        dz = random() % 3 - 1;
    }


    if (dx == -1 && x == 0)
    {
      crash_x = 0x01;
      if (random() % 3 == 1)
      {
        dx = 1;
      } else
      {
        dx = 0;
      }
    }

    if (dy == -1 && y == 0)
    {
      crash_y = 0x01;
      if (random() % 3 == 1)
      {
        dy = 1;
      } else
      {
        dy = 0;
      }
    }

    if (dz == -1 && z == 0)
    {
      crash_z = 0x01;
      if (random() % 3 == 1)
      {
        dz = 1;
      } else
      {
        dz = 0;
      }
    }

    if (dx == 1 && x == 7)
    {
      crash_x = 0x01;
      if (random() % 3 == 1)
      {
        dx = -1;
      } else
      {
        dx = 0;
      }
    }

    if (dy == 1 && y == 7)
    {
      crash_y = 0x01;
      if (random() % 3 == 1)
      {
        dy = -1;
      } else
      {
        dy = 0;
      }
    }

    if (dz == 1 && z == 7)
    {
      crash_z = 0x01;
      if (random() % 3 == 1)
      {
        dz = -1;
      } else
      {
        dz = 0;
      }
    }

    // mode bit 0 sets crash action enable
    if (mode | 0x01)
    {
      if (crash_x)
      {
        if (dy == 0)
        {
          if (y == 7)
          {
            dy = -1;
          } else if (y == 0)
          {
            dy = +1;
          } else
          {
            if (random() % 2 == 0)
            {
              dy = -1;
            } else
            {
              dy = 1;
            }
          }
        }
        if (dz == 0)
        {
          if (z == 7)
          {
            dz = -1;
          } else if (z == 0)
          {
            dz = 1;
          } else
          {
            if (random() % 2 == 0)
            {
              dz = -1;
            } else
            {
              dz = 1;
            }
          }
        }
      }

      if (crash_y)
      {
        if (dx == 0)
        {
          if (x == 7)
          {
            dx = -1;
          } else if (x == 0)
          {
            dx = 1;
          } else
          {
            if (random() % 2 == 0)
            {
              dx = -1;
            } else
            {
              dx = 1;
            }
          }
        }
        if (dz == 0)
        {
          if (z == 3)
          {
            dz = -1;
          } else if (z == 0)
          {
            dz = 1;
          } else
          {
            if (random() % 2 == 0)
            {
              dz = -1;
            } else
            {
              dz = 1;
            }
          }
        }
      }

      if (crash_z)
      {
        if (dy == 0)
        {
          if (y == 7)
          {
            dy = -1;
          } else if (y == 0)
          {
            dy = 1;
          } else
          {
            if (random() % 2 == 0)
            {
              dy = -1;
            } else
            {
              dy = 1;
            }
          }
        }
        if (dx == 0)
        {
          if (x == 7)
          {
            dx = -1;
          } else if (x == 0)
          {
            dx = 1;
          } else
          {
            if (random() % 2 == 0)
            {
              dx = -1;
            } else
            {
              dx = 1;
            }
          }
        }
      }
    }

    // mode bit 1 sets corner avoid enable
    if (mode | 0x02)
    {
      if (	// We are in one of 8 corner positions
        (x == 0 && y == 0 && z == 0) ||
        (x == 0 && y == 0 && z == 7) ||
        (x == 0 && y == 7 && z == 0) ||
        (x == 0 && y == 7 && z == 7) ||
        (x == 7 && y == 0 && z == 0) ||
        (x == 7 && y == 0 && z == 7) ||
        (x == 7 && y == 7 && z == 0) ||
        (x == 7 && y == 7 && z == 7)
      )
      {
        // At this point, the voxel would bounce
        // back and forth between this corner,
        // and the exact opposite corner
        // We don't want that!

        // So we alter the trajectory a bit,
        // to avoid corner stickyness
        lol = random() % 3;
        if (lol == 0)
          dx = 0;

        if (lol == 1)
          dy = 0;

        if (lol == 2)
          dz = 0;
      }
    }

    // Finally, move the voxel.
    x = x + dx;
    y = y + dy;
    z = z + dz;

    if (drawmode == 0x01) // show one voxel at time
    {
      setvoxel(x, y, z);
      delay_ms(delay);
      clrvoxel(x, y, z);
    } else if (drawmode == 0x02) // flip the voxel in question
    {
      flpvoxel(x, y, z);
      delay_ms(delay);
    } if (drawmode == 0x03)
    {
      for (i = 7; i >= 0; i--)
      {
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
        snake[i][2] = snake[i - 1][2];
      }
      snake[0][0] = x;
      snake[0][1] = y;
      snake[0][2] = z;

      for (i = 0; i < 8; i++)
      {
        setvoxel(snake[i][0], snake[i][1], snake[i][2]);
      }
      delay_ms(delay);
      for (i = 0; i < 8; i++)
      {
        clrvoxel(snake[i][0], snake[i][1], snake[i][2]);
      }
    }


    iterations--;
  }
}

// Set or clear exactly 512 voxels in a random order.
void effect_random_filler (int delay, int state)
{
  int x, y, z;
  int loop = 0;


  if (state == 1)
  {
    fill(0x00);
  } else
  {
    fill(0xff);
  }

  while (loop < 511)
  {
    x = random() % 8;
    y = random() % 8;
    z = random() % 8;

    if ((state == 0 && getvoxel(x, y, z) == 0x01) || (state == 1 && getvoxel(x, y, z) == 0x00))
    {
      altervoxel(x, y, z, state);
      delay_ms(delay);
      loop++;
    }
  }
}


void effect_rain (int iterations)
{
  int i, ii;
  int rnd_x;
  int rnd_y;
  int rnd_num;

  for (ii = 0; ii < iterations; ii++)
  {
    rnd_num = random() % 4;

    for (i = 0; i < rnd_num; i++)
    {
      rnd_x = random() % 8;
      rnd_y = random() % 8;
      setvoxel(rnd_x, rnd_y, 7);
    }

    delay_ms(1000);
    shift(AXIS_Z, -1);
  }
}

void effect_z_updown (int iterations, int delay)
{
  unsigned char positions[64];
  unsigned char destinations[64];

  int i, y, move, px;

  for (i = 0; i < 64; i++)
  {
    positions[i] = 4;
    destinations[i] = random() % 8;
  }

  for (i = 0; i < 8; i++)
  {
    effect_z_updown_move(positions, destinations, AXIS_Z);
    delay_ms(delay);
  }

  for (i = 0; i < iterations; i++)
  {
    for (move = 0; move < 8; move++)
    {
      effect_z_updown_move(positions, destinations, AXIS_Z);
      delay_ms(delay);
    }

    delay_ms(delay * 4);


    for (y = 0; y < 10; y++)
    {
      destinations[random() % 64] = random() % 8;
    }

  }

}

void effect_z_updown_move (unsigned char positions[64], unsigned char destinations[64], char axis)
{
  int px;
  for (px = 0; px < 64; px++)
  {
    if (positions[px] < destinations[px])
    {
      positions[px]++;
    }
    if (positions[px] > destinations[px])
    {
      positions[px]--;
    }
  }

  draw_positions_axis (AXIS_Z, positions, 0);
}

void effect_axis_updown_randsuspend (char axis, int delay, int sleep, int invert)
{
  unsigned char positions[64];
  unsigned char destinations[64];

  int i, px;

  for (i = 0; i < 64; i++)
  {
    positions[i] = 0;
    destinations[i] = random() % 8;
  }

  for (i = 0; i < 8; i++)
  {
    for (px = 0; px < 64; px++)
    {
      if (positions[px] < destinations[px])
      {
        positions[px]++;
      }
      if (positions[px] > destinations[px])
      {
        positions[px]--;
      }
    }
    draw_positions_axis (axis, positions, invert);
    delay_ms(delay);
  }

  for (i = 0; i < 64; i++)
  {
    destinations[i] = 7;
  }

  delay_ms(sleep);

  for (i = 0; i < 8; i++)
  {
    for (px = 0; px < 64; px++)
    {
      if (positions[px] < destinations[px])
      {
        positions[px]++;
      }
      if (positions[px] > destinations[px])
      {
        positions[px]--;
      }
    }
    draw_positions_axis (axis, positions, invert);
    delay_ms(delay);
  }



}

void draw_positions_axis (char axis, unsigned char positions[64], int invert)
{
  int x, y, p;

  fill(0x00);

  for (x = 0; x < 8; x++)
  {
    for (y = 0; y < 8; y++)
    {
      if (invert)
      {
        p = (7 - positions[(x * 8) + y]);
      } else
      {
        p = positions[(x * 8) + y];
      }

      if (axis == AXIS_Z)
        setvoxel(x, y, p);

      if (axis == AXIS_Y)
        setvoxel(x, p, y);

      if (axis == AXIS_X)
        setvoxel(p, y, x);
    }
  }

}


void effect_boxside_randsend_parallel (char axis, int origin, int delay, int mode)
{
  int i;
  int done;
  unsigned char cubepos[64];
  unsigned char pos[64];
  int notdone = 1;
  int notdone2 = 1;
  int sent = 0;

  for (i = 0; i < 64; i++)
  {
    pos[i] = 0;
  }

  while (notdone)
  {
    if (mode == 1)
    {
      notdone2 = 1;
      while (notdone2 && sent < 64)
      {
        i = random() % 64;
        if (pos[i] == 0)
        {
          sent++;
          pos[i] += 1;
          notdone2 = 0;
        }
      }
    } else if (mode == 2)
    {
      if (sent < 64)
      {
        pos[sent] += 1;
        sent++;
      }
    }

    done = 0;
    for (i = 0; i < 64; i++)
    {
      if (pos[i] > 0 && pos[i] < 7)
      {
        pos[i] += 1;
      }

      if (pos[i] == 7)
        done++;
    }

    if (done == 64)
      notdone = 0;

    for (i = 0; i < 64; i++)
    {
      if (origin == 0)
      {
        cubepos[i] = pos[i];
      } else
      {
        cubepos[i] = (7 - pos[i]);
      }
    }


    delay_ms(delay);
    draw_positions_axis(axis, cubepos, 0);
  }

}




// Light all leds layer by layer,
// then unset layer by layer
void effect_loadbar(int delay)
{
  fill(0x00);

  int z, y;

  for (z = 0; z < 8; z++)
  {
    for (y = 0; y < 8; y++)
      data[z][y] = 0xff;

    delay_ms(delay);
  }

  delay_ms(delay * 3);

  for (z = 0; z < 8; z++)
  {
    for (y = 0; y < 8; y++)
      data[z][y] = 0x00;

    delay_ms(delay);
  }
}


// Set n number of voxels at random positions
void effect_random_sparkle_flash (int iterations, int voxels, int delay)
{
  int i;
  int v;
  for (i = 0; i < iterations; i++)
  {
    for (v = 0; v <= voxels; v++)
      setvoxel(random() % 8, random() % 8, random() % 8);

    delay_ms(delay);
    fill(0x00);
  }
}

// Set n number of voxels at random positions
void effect_random(int voxels, int delay)
{
  int i;
  int v;
  for (v = 0; v <= voxels; v++){
    setvoxel(random() % 8, random() % 8, random() % 8);
    delay_ms(delay);
  }
}

// blink 1 random voxel, blink 2 random voxels..... blink 20 random voxels
// and back to 1 again.
void effect_random_sparkle (void)
{
  int i;

  for (i = 1; i < 20; i++)
  {
    effect_random_sparkle_flash(5, i, 200);
  }

  for (i = 20; i >= 1; i--)
  {
    effect_random_sparkle_flash(5, i, 200);
  }

}

int effect_telcstairs_do(int x, int val, int delay)
{
  int y, z;

  for (y = 0, z = x; y <= z; y++, x--)
  {
    if (x < CUBE_SIZE && y < CUBE_SIZE)
    {
      data[x][y] = val;
    }
  }
  delay_ms(delay);
  return z;
}

void effect_telcstairs (int invert, int delay, int val)
{
  int x;

  if (invert)
  {
    for (x = CUBE_SIZE * 2; x >= 0; x--)
    {
      x = effect_telcstairs_do(x, val, delay);
    }
  }
  else
  {
    for (x = 0; x < CUBE_SIZE * 2; x++)
    {
      x = effect_telcstairs_do(x, val, delay);
    }
  }
}

void effect_wormsqueeze (int size, int axis, int direction, int iterations, int delay)
{
  int x, y, i, j, k, dx, dy;
  int cube_size;
  int origin = 0;

  if (direction == -1)
    origin = 7;

  cube_size = 8 - (size - 1);

  x = random() % cube_size;
  y = random() % cube_size;

  for (i = 0; i < iterations; i++)
  {
    dx = ((random() % 3) - 1);
    dy = ((random() % 3) - 1);

    if ((x + dx) > 0 && (x + dx) < cube_size)
      x += dx;

    if ((y + dy) > 0 && (y + dy) < cube_size)
      y += dy;

    shift(axis, direction);


    for (j = 0; j < size; j++)
    {
      for (k = 0; k < size; k++)
      {
        if (axis == AXIS_Z)
          setvoxel(x + j, y + k, origin);

        if (axis == AXIS_Y)
          setvoxel(x + j, origin, y + k);

        if (axis == AXIS_X)
          setvoxel(origin, y + j, x + k);
      }
    }

    delay_ms(delay);
  }
}

void effect_smileyspin (int count, int delay, char bitmap)
{
  unsigned char dybde[] = {0, 1, 2, 3, 4, 5, 6, 7, 1, 1, 2, 3, 4, 5, 6, 6, 2, 2, 3, 3, 4, 4, 5, 5, 3, 3, 3, 3, 4, 4, 4, 4};
  int d = 0;
  int flip = 0;
  int x, y, off;
  int i, s;
  for (i = 0; i < count; i++)
  {
    flip = 0;
    d = 0;
    off = 0;
    // front:
    for (s = 0; s < 7; s++) {
      if (!flip) {
        off++;
        if (off == 4) {
          flip = 1;
          off = 0;
        }
      } else {
        off++;
      }
      for (x = 0; x < 8; x++)
      {
        d = 0;
        for (y = 0; y < 8; y++)
        {
          if (font_getbitmappixel ( bitmap, 7 - x, y)) {
            if (!flip)
              setvoxel(y, dybde[8 * off + d++], x);
            else
              setvoxel(y, dybde[31 - 8 * off - d++], x);
          } else {
            d++;
          }
        }
      }
      delay_ms(delay);
      fill(0x00);
    }

    // side:
    off = 0;
    flip = 0;
    d = 0;
    int s;
    for (s = 0; s < 7; s++) {
      if (!flip) {
        off++;
        if (off == 4) {
          flip = 1;
          off = 0;
        }
      } else {
        off++;
      }
      for (x = 0; x < 8; x++)
      {
        d = 0;
        for (y = 0; y < 8; y++)
        {
          if (font_getbitmappixel ( bitmap, 7 - x, y)) {
            if (!flip)
              setvoxel(dybde[8 * off + d++], 7 - y, x);
            else
              setvoxel(dybde[31 - 8 * off - d++], 7 - y, x);
          } else {
            d++;
          }
        }
      }
      delay_ms(delay);
      fill(0x00);
    }


    flip = 0;
    d = 0;
    off = 0;
    // back:
    for (s = 0; s < 7; s++) {
      if (!flip) {
        off++;
        if (off == 4) {
          flip = 1;
          off = 0;
        }
      } else {
        off++;
      }
      for (x = 0; x < 8; x++)
      {
        d = 0;
        for (y = 0; y < 8; y++)
        {
          if (font_getbitmappixel ( bitmap, 7 - x, 7 - y)) {
            if (!flip)
              setvoxel(y, dybde[8 * off + d++], x);
            else
              setvoxel(y, dybde[31 - 8 * off - d++], x);
          } else {
            d++;
          }
        }
      }
      delay_ms(delay);
      fill(0x00);
    }

    // other side:
    off = 0;
    flip = 0;
    d = 0;
    for (s = 0; s < 7; s++) {
      if (!flip) {
        off++;
        if (off == 4) {
          flip = 1;
          off = 0;
        }
      } else {
        off++;
      }
      for (x = 0; x < 8; x++)
      {
        d = 0;
        for (y = 0; y < 8; y++)
        {
          if (font_getbitmappixel ( bitmap, 7 - x, 7 - y)) {
            if (!flip)
              setvoxel(dybde[8 * off + d++], 7 - y, x);
            else
              setvoxel(dybde[31 - 8 * off - d++], 7 - y, x);
          } else {
            d++;
          }
        }
      }
      delay_ms(delay);
      fill(0x00);
    }

  }
}


void effect_pathmove (unsigned char *path, int length)
{
  int i, z;
  unsigned char state;

  for (i = (length - 1); i >= 1; i--)
  {
    for (z = 0; z < 8; z++)
    {

      state = getvoxel(((path[(i - 1)] >> 4) & 0x0f), (path[(i - 1)] & 0x0f), z);
      altervoxel(((path[i] >> 4) & 0x0f), (path[i] & 0x0f), z, state);
    }
  }
  for (i = 0; i < 8; i++)
    clrvoxel(((path[0] >> 4) & 0x0f), (path[0] & 0x0f), i);
}

void effect_rand_patharound (int iterations, int delay)
{
  int z, dz, i;
  z = 4;
  unsigned char path[28];

  font_getpath(0, path, 28);

  for (i = 0; i < iterations; i++)
  {
    dz = ((random() % 3) - 1);
    z += dz;

    if (z > 7)
      z = 7;

    if (z < 0)
      z = 0;

    effect_pathmove(path, 28);
    setvoxel(0, 7, z);
    delay_ms(delay);
  }
}

void effect_pathspiral (int iterations, int delay)
{
  int z, i;
  z = 4;
  unsigned char path[16];

  font_getpath(1, path, 16);

  for (i = 0; i < iterations; i++)
  {
    setvoxel(4, 0, i % 8);
    delay_ms(delay);
    effect_pathmove(path, 28);

  }
}

void effect_path_text (int delay, char *str)
{
  int z, i, ii;
  z = 4;
  unsigned char path[28];
  font_getpath(0, path, 28);

  unsigned char chr[5];
  unsigned char stripe;

  while (*str)
  {
    //charfly(*str++, direction, axis, mode, delay);


    font_getchar(*str++, chr);

    for (ii = 0; ii < 5; ii++)
    {
      //stripe = pgm_read_byte(&font[(chr*5)+ii]);
      stripe = chr[ii];

      for (z = 0; z < 8; z++)
      {
        if ((stripe >> (7 - z)) & 0x01)
        {
          setvoxel(0, 7, z);
        } else
        {
          clrvoxel(0, 7, z);
        }

      }
      effect_pathmove(path, 28);
      delay_ms(delay);
    }

    effect_pathmove(path, 28);
    delay_ms(delay);
  }
  for (i = 0; i < 28; i++)
  {
    effect_pathmove(path, 28);
    delay_ms(delay);
  }
}

void effect_path_bitmap (int delay, char bitmap, int iterations)
{
  int z, i, ii;
  z = 4;
  unsigned char path[28];
  font_getpath(0, path, 28);

  for (i = 0; i < iterations; i++)
  {
    for (ii = 0; ii < 8; ii++)
    {
      for (z = 0; z < 8; z++)
      {
        if (font_getbitmappixel(bitmap, (7 - z), ii))
        {
          setvoxel(0, 7, z);
        } else
        {
          clrvoxel(0, 7, z);
        }

      }
      delay_ms(delay);
      effect_pathmove(path, 28);
    }

    for (ii = 0; ii < 20; ii++)
    {
      delay_ms(delay);
      effect_pathmove(path, 28);
    }
  }
  for (ii = 0; ii < 10; ii++)
  {
    delay_ms(delay);
    effect_pathmove(path, 28);
  }
}



