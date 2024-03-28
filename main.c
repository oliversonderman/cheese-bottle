#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define size 8
int gamecheck(int gridx[8][8], int gridp[8][8]) {
  int x = 0;
  int y = 0;
  int wk = 0;
  int bk = 0;
  while (y != 8) {
    while (x != 8) {
      if (gridx[x][y] == 107) {
        if (gridp[x][y] == -1) {
          bk = 1;
        }
        if (gridp[x][y] == 1) {
          wk = 1;
        }
      }
      x++;
    }
    x = 0;
    y++;
  }
  if (bk == 1 && wk == 1) {
    return 1;
  }
  if (bk == 1 && wk == 0) {
    return 2;
  }
  if (bk == 0 && wk == 1) {
    return 3;
  }
  return 4;
}
void saftyF(int pm, int xp, int yp, int gridx[8][8], int gridp[8][8], int P,
            int x, int y, int C11, int C12, int C21, int C22, int turn, int M1,
            int M2, int MC, int PC, int safty[8][8][8][8][8][8],
            int grid4[8][8][8][8], int pgridx[8][8][8][8][8][8],
            int pgridp[8][8][8][8][8][8]) {
  int n = 0;
  // grid x 16 y16 (piece being moved)
  // reset x 14 y 14 to normal grid x
  // grid x14 y14 (grid to ananlize the piece being moved)
  // grid x 15 y15 ( all the possible possitionsions in the grid of analization)
  // if   p=N if knight attacks {
  // if true safty x y ++}
  //  if p= r, q check pieces in between, y15-y14==0
  // if p = b, q chechk pieces in between
  // if p = king, check pieces distance away from center
  // store in two dimenstional x16y16 x 14 y14 grid
  int x16 = 0;
  int y16 = 0;
  int x15 = 0;
  int y15 = 0;
  int x14 = 0;
  int y14 = 0;
  int x17 = 0;
  int y17 = 0;
  int gridsx[size][size];
  int gridsp[size][size];
  int qu;
  int xu = 0;
  int yu = 0;
  // inital grid sx sp encodeing
  while (y17 != 0) {
    while (x17 != 0) {
      gridsx[x17][y17] = gridx[x17][y17];
      gridsp[x17][y17] = gridp[x17][y17];
      x17++;
    }
    x17 = 0;
    y17++;
  }
  y17 = 0;
  x17 = 0;
  y16 = 0;
  while (y17 != 8) {
    while (x17 != 8) {
      while (y16 != 8) {
        while (x16 != 8) {
          gridsx[x16][y16] = gridx[x17][y17];
          gridsx[x17][y17] = 0;
          gridsp[x16][y16] = gridp[x17][y17];
          gridsp[x17][y17] = 0;
          while (y15 < 8) {
            while (x15 < 8) {
              pgridx[x17][y17][x16][y16][x15][y15] = gridsx[x15][y15];
              if (gridsx[x15][y15] == 114 || gridsx[x15][y15] == 113) {
                x14 = x15;
                while (x14 != 8) {
                  x14++;
                  if (gridsp[x14][y15] == gridsp[x15][y15]) {
                    safty[x17][y17][x16][y16][x14][y15]++;
                    x14 = 8;
                  }
                  if (gridsp[x14][y15] == gridsp[x15][y15] * -1) {
                    safty[x17][y17][x16][y16][x14][y15]--;
                    x14 = 8;
                  }
                }
                x14 = x15;
                while (x14 != 0) {
                  x14--;
                  if (gridsp[x14][y15] == gridsp[x15][y15]) {
                    safty[x17][y17][x16][y16][x14][y15]++;
                    x14 = 0;
                  }

                  if (gridsp[x14][y15] == gridsp[x15][y15] * -1) {
                    if (x15 != x14) {
                      safty[x17][y17][x16][y16][x14][y15]--;
                      x14 = 0;
                    }
                    x == x;
                  }
                }
                // up down
                y14 = y15;
                while (y14 < 7) {
                  y14++;
                  if (gridsp[x15][y15] == gridsp[x15][y14]) {
                    safty[x17][y17][x16][y16][x15][y14]++;
                    y14 = 8;
                    goto here2;
                  }
                  if (gridsp[x15][y15] == gridsp[x15][y14] * -1) {
                    safty[x17][y17][x16][y16][x15][y14]--;
                    y14 = 8;
                  }
                here2:
                  x == x;
                }
                y14 = y15;
                while (y14 > 0) {
                  y14--;
                  if (gridsp[x15][y15] == gridsp[x15][y14]) {
                    safty[x17][y17][x16][y16][x15][y14]++;
                    y14 = 0;
                    goto here1;
                  }
                  if (gridsp[x15][y15] == gridsp[x15][y14] * -1) {
                    safty[x17][y17][x16][y16][x15][y14]--;
                    y14 = 0;
                  }
                here1:
                  x == x;
                }
              }
              if (gridsx[x15][y15] == 98 || gridsx[x15][y15] == 113) {
                x14 = x15;
                // top left
                y14 = y15;
                while (x14 != 8 && y14 != 8) {
                  x14++;
                  y14++;
                  if (gridsp[x14][y14] == gridsp[x15][y15]) {
                    safty[x17][y17][x16][y16][x14][y14]++;
                    x14 = 8;
                    goto here3;
                  }
                  if (gridsp[x14][y14] == gridsp[x15][y15] * -1) {
                    if (x14 > 8 && y14 > 8 && x15 > 8 && y15 > 8) {
                      safty[x17][y17][x16][y16][x14][y14]--;
                      x14 = 8;
                    }
                  }
                here3:
                  x == x;
                }
                // top right
                x14 = x15;
                y14 = y15;
                while (x14 != 0 && y14 != 7) {
                  x14--;
                  y14++;
                  if (gridsp[x14][y14] == gridsp[x15][y15]) {
                    safty[x17][y17][x16][y16][x14][y14]++; // done
                    x14 = 0;
                    goto here4;
                  }
                  if (gridsp[x14][y14] == gridsp[x15][y15] * -1) {
                    safty[x17][y17][x16][y16][x14][y14]--;
                    x14 = 0;
                  }
                here4:
                  x == x;
                }
                // bottom left
                x14 = x15;
                y14 = y15;
                while (x14 != 7 && y14 != 0) {
                  x14++;
                  y14--;
                  if (gridsp[x14][y14] == gridsp[x15][y15]) {
                    safty[x17][y17][x16][y16][x14][y14]++;
                    x14 = 7;
                    goto here5;
                  }
                  if (gridsp[x14][y14] == gridsp[x15][y15] * -1) {
                    safty[x17][y17][x16][y16][x14][y14]--;
                    x14 = 7;
                  }
                here5:
                  x == x;
                }
                // bottom right
                x14 = x15;
                y14 = y15;
                while (x14 != 0 && y14 != 0) {
                  x14--;
                  y14--;
                  if (gridsp[x14][y14] == gridsp[x15][y15]) {
                    safty[x17][y17][x16][y16][x14][y14]++;
                    x14 = 0;
                    goto here6;
                  }
                  if (gridsp[x14][y14] == gridsp[x15][y15] * -1) {
                    safty[x17][y17][x16][y16][x14][y14]--;
                    x14 = 0;
                  }
                here6:
                  x == x;
                }
              }
              if (gridsx[x15][y15] == 112) {
                if (gridsp[x15][y15] == 1) {
                  if (y15 > 7) {
                    if (x15 != 0) {
                      if (gridsp[x15][y15] == gridsp[x15 - 1][y15 + 1]) {
                        safty[x17][y17][x16][y16][x15 - 1][y15 + 1]++;
                      }
                      if (gridsp[x15][y15] == gridsp[x15 - 1][y15 + 1] * -1) {
                        safty[x17][y17][x16][y16][x15 - 1][x15 + 1]--;
                      }
                    }
                    if (x15 != 7) {
                      if (gridsp[x15][y15] == gridsp[x15 + 1][y15 + 1]) {
                        safty[x17][y17][x16][y16][x15 + 1][x15 + 1]++;
                      }
                      if (gridsp[x15][y15] == gridsp[x15 + 1][y15 + 1] * -1) {
                        safty[x17][y17][x16][y16][x15 + 1][x15 + 1]--;
                      }
                    }
                  }
                }
                if (gridsp[x15][y15] == -1) {
                  if (y15 != 0) {
                    if (x15 != 7) {
                      if (gridsp[x15][y15] == gridsp[x15 + 1][y15 - 1]) {
                        safty[x17][y17][x16][y16][x15 + 1][x15 - 1]++;
                      }
                      if (gridsp[x15][y15] == gridsp[x15 + 1][y15 - 1] * -1) {
                        safty[x17][y17][x16][y16][x15 + 1][x15 - 1]--;
                      }
                    }
                    if (x15 != 0) {
                      if (gridsp[x15][y15] == gridsp[x15 - 1][y15 - 1]) {
                        safty[x17][y17][x16][y16][x15 - 1][x15 - 1]++;
                      }
                      if (gridsp[x15][y15] == gridsp[x15 - 1][y15 - 1] * -1) {
                        safty[x17][y17][x16][y16][x15 - 1][x15 - 1]--;
                      }
                    }
                  }
                }
              }
              if (gridsx[x15][y15] == 107) {
                if (gridsp[x15][y15] == 1) {
                  if (x15 != 0 && y15 != 7) {
                    if (gridsp[x15 - 1][y15 + 1] == 1) {
                      safty[x17][y17][x16][y16][x15][y15]++;
                    }
                  }
                  if (y15 != 7) {
                    if (gridsp[x15][y15 + 1] == 1) {
                      safty[x17][y17][x16][y16][x15][y15]++;
                    }
                  }
                  if (x15 != 7 && y15 != 7) {
                    if (gridsp[x15 + 1][y15 + 1] == 1) {
                      safty[x17][y17][x16][y16][x15][y15]++;
                    }
                  }
                }
                if (gridsp[x15][y15] == -1) {
                  if (x15 != 0 && y15 != 0) {
                    if (gridsp[x15 - 1][y15 - 1] == -1) {
                      safty[x17][y17][x16][y16][x15][y15]++;
                    }
                  }
                  if (y15 != 0) {
                    if (gridsp[x15][y15 - 1] == -1) {
                      safty[x17][y17][x16][y16][x15][y15]++;
                    }
                  }
                  if (x15 != 7 && y15 != 0) {
                    if (gridsp[x15 + 1][y15 - 1] == -1) {
                      safty[x17][y17][x16][y16][x15][y15]++;
                    }
                  }
                }

                if (x15 != 7) {
                  if (y15 != 7) {
                    if (gridsp[x15][y15] == gridsp[x15 + 1][y15 + 1]) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 + 1]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15 + 1][y15 + 1] * -1) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 + 1]--;
                    }
                    if (gridsp[x15][y15] == gridsp[x15][y15 + 1]) {
                      safty[x17][y17][x16][y16][x15][y15 + 1]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15][y15 + 1] * -1) {
                      safty[x17][y17][x16][y16][x15][y15 + 1]--;
                    }
                  }
                }
                if (x15 != 0) {
                  if (y15 != 0) {
                    if (gridsp[x15][y15] == gridsp[x15 - 1][y15 - 1]) {
                      safty[x17][y17][x16][y16][x15 - 1][y15 - 1]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15 - 1][y15 - 1] * -1) {
                      safty[x17][y17][x16][y16][x15 - 1][y15 - 1]--;
                    }
                    if (gridsp[x15][y15] == gridsp[x15][y15 - 1]) {
                      safty[x17][y17][x16][y16][x15][y15 - 1]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15][y15 - 1] * -1) {
                      safty[x17][y17][x16][y16][x15][y15 - 1]--;
                    }
                  }
                }
                if (x15 != 7) {
                  if (gridsp[x15][y15] == gridsp[x15 + 1][y15]) {
                    safty[x17][y17][x16][y16][x15 + 1][y15]++;
                  }
                  if (gridsp[x15][y15] == gridsp[x15 + 1][y15] * -1) {
                    safty[x17][y17][x16][y16][x15 + 1][y15]--;
                  }
                  if (y15 != 7) {
                    if (gridsp[x15][y15] == gridsp[x15 - 1][y15 + 1]) {
                      safty[x17][y17][x16][y16][x15 - 1][y15 + 1]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15 - 1][y15 + 1] * -1) {
                      safty[x17][y17][x16][y16][x15 - 1][y15 + 1]--;
                    }
                  }
                }
                if (x15 != 0) {
                  if (gridsp[x15][y15] == gridsp[x15 - 1][y15]) {
                    safty[x17][y17][x16][y16][x15 - 1][y15]++;
                  }
                  if (gridsp[x15][y15] == gridsp[x15 - 1][y15] * -1) {
                    safty[x17][y17][x16][y16][x15 - 1][y15]--;
                  }
                  if (y15 != 0) {
                    if (gridsp[x15][y15] == gridsp[x15 + 1][y15 - 1]) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 - 1]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15 + 1][y15 - 1] * -1) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 - 1]--;
                    }
                  }
                }
              }
              if (gridsx[x15][y15] == 110) {
                if (x15 > 1) {
                  if (y15 < 7) {
                    if (gridsp[x15 - 2][y15 + 1] == gridsp[x15][y15]) {
                      safty[x17][y17][x16][y16][x15 - 2][y15 + 1]++;
                    }
                    if (gridsp[x15 + 2][y15 + 1] == gridsp[x15][y15] * -1) {
                      safty[x17][y17][x16][y16][x15 - 2][y15 + 1]--;
                    }
                  }
                  if (y15 > 0) {
                    if (gridsp[x15 - 2][y15 - 1] == gridsp[x15][y15]) {
                      safty[x17][y17][x16][y16][x15 - 2][y15 - 1]++;
                    }
                    if (gridsp[x15 - 2][y15 - 1] == gridsp[x15][y15] * -1) {
                      safty[x17][y17][x16][y16][x15 - 2][y15 - 1]--;
                    }
                  }
                }
                // left
                if (x15 > 0) {
                  if (y15 > 1) {
                    if (gridsp[x15][y15] == gridsp[x15 + 1][y15 - 2]) {
                      safty[x17][y17][x16][y16][x15 - 1][y15 - 2]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15 + 1][y15 - 2] * -1) {
                      safty[x17][y17][x16][y16][x15 - 1][y15 - 2]--;
                    }
                  }
                  if (y15 < 6) {
                    if (gridsp[x15][y15] == gridsp[x15 - 1][y15 + 2]) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 + 2]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15 + 1][y15 + 2] * -1) {
                      safty[x17][y17][x16][y16][x15 - 1][y15 + 2]--;
                    }
                  }
                }
                // far right
                if (x15 < 6) {
                  if (y15 > 0) {
                    if (gridsp[x15][y15] == gridsp[x15 + 2][y15 - 1]) {
                      safty[x17][y17][x16][y16][x15 + 2][y15 - 1]++;
                    }
                    if (gridsp[x15][y15] == gridsp[x15 + 2][y15 - 1] * -1) {
                      safty[x17][y17][x16][y16][x15 + 2][y15 - 1]--;
                    }
                  }
                  if (y15 < 7) {
                    if (gridsp[x15 + 2][y15 + 1] == gridsp[x15][y15]) {
                      safty[x17][y17][x16][y16][x15 + 2][y15 + 1]++;
                    }
                    if (gridsp[x15 + 2][y15 + 1] == gridsp[x15][y15] * -1) {
                      safty[x17][y17][x16][y16][x15 + 2][y15 + 1]--;
                    }
                  }
                }
                // right
                if (x15 < 7) {
                  if (y15 < 6) {
                    if (gridsp[x15 + 1][y15 + 2] == gridsp[x15][y15]) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 + 2]++;
                    }
                    if (gridsp[x15 + 1][y15 + 2] == gridsp[x15][y15] * -1) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 + 2]--;
                    }
                  }
                  if (y15 > 1) {
                    if (gridsp[x15 + 1][y15 - 2] == gridsp[x15][y15]) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 - 2]++;
                    }
                    if (gridsp[x15 + 1][y15 - 2] == gridsp[x15][y15] * -1) {
                      safty[x17][y17][x16][y16][x15 + 1][y15 - 2]--;
                    }
                  }
                }
              }
              x15++;
            }
            x15 = 0;
            y15++;
          }
          gridsx[x17][y17] = gridx[x17][y17];
          gridsx[x16][y16] = gridx[x16][y16];
          gridsp[x17][y17] = gridp[x17][y17];
          gridsp[x16][y16] = gridp[x16][y16];
          x16++;
          y15 = 0;
        }
        y16++;
        x16 = 0;
      }
      y16 = 0;
      x17++;
    }
    x17 = 0;
    y17++;
  }
}
void moveW(int x, int y, int gridx[8][8], int gridp[8][8], int P, int xp,
           int yp, int C11, int C21, int C22, int C12, int turn, int PC, int x5,
           int y5, int gridx2[8][8], int gridp2[8][8], int x13, int y13,
           int pm[size][size][size][size]) {
  int pmw = 0;
  int pmb = 0;
  if (gridp2[x5][y5] == 1) {
    pmw++;
  }
  if (gridp2[x5][y5] == -1) {
    pmb++;
  }
  pm[x13][y13][x5][y5] = pmb - pmw;
  pmb = 0;
  pmw = 0;
}
int validmove2(int x, int x2, int z, int y2, int result, int gridx[8][8],
               int gridp[8][8], int P) {
  // King
  int C11, C12, C21, C22, y, xp, yp, turn, valid;
  int C = 0;
  y = z;
  C11 = x;
  C12 = z;
  C21 = x2;
  C22 = y2;
  turn = 1;
  x = 0;
  y = 0;
  xp = 0;
  yp = 0;
  valid = 0;
  result = 0;
  if (gridp[C11][C12] == 1) {
    if (P == 107) {
      if (C11 - C21 == 1 || C11 - C21 == -1) {
        if (C12 - C22 == 0 || C12 - C22 == 1 || C12 - C22 == -1) {
          if (gridp[C21][C22] != gridp[C11][C12]) {
            valid = 1;
            goto confirmed;
            valid = 1;
          }
        }
      }
      if (C11 - C21 == 0) {
        if (C12 - C22 == 1 || C12 - C22 == -1) {
          if (gridp[C21][C22] != gridp[C11][C12]) {
            valid = 1;
            goto confirmed;
            valid = 1;
          }
        }
      }
    }
    // Knight
    else if (P == 110) {
      if (C21 == C11 + 1 || C21 == C11 - 1) {
        if (C22 == C12 - 2 || C22 == C12 + 2) {
          if (gridp[C11][C12] != gridp[C21][C22]) {
            valid = 1;
            goto confirmed;
            valid = 1;
          }
        }
      } else if (C11 == 2 + C21 || C11 == -2 + C21) {
        if (C22 == 1 + C22 || C22 == -1 + C22) {
          if (gridp[C11][C12] != gridp[C21][C22]) {
            valid = 1;
            goto confirmed;
            valid = 1;
          }
        }
      } else {
      }
    }
    // bishop
    else if (P == 98) {
      yp = C12;
      xp = C11;
      x = C11;
      y = C12;
      if (C21 > C11 && C22 > C12) {
        while (x != C21) {
          x++;
          y++;
          xp++;
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 > C21 && C12 > C22) {
        while (x != C21) {
          x--;
          y--;
          xp--;
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 > C21 && C12 < C22) {
        while (x != C21) {
          x--;
          y++;
          xp--;
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 < C21 && C12 > C22) {
        while (x != C21) {
          x++;
          y--;
          xp++;
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      }
    }
    // queen
    if (P == 113) {
      // right direction
      if (C11 < C21 && C22 == C12) {
        xp = C11;
        yp = C12;
        x = C11;
        y = C12;
        while (xp != C22) {
          xp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (xp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (xp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }
      if (C11 > C21 && C22 == C12) {
        xp = C11;
        yp = C12;
        x = C11;
        y = C12;
        while (xp != C22) {
          xp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (xp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (xp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      } else if (C11 == C21 && C12 > C22) {
        xp = C11;
        yp = C12;
        x = C11;
        y = C12;
        while (yp != C22) {
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (yp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }
      if (C11 == C21 && C22 > C12) {
        xp = C11;
        yp = C12;
        x = C11;
        y = C12;
        while (yp != C22) {
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (yp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
        }
      }
      if (C21 > C11 && C22 > C12) {
        x = C11;
        y = C12;
        xp = C11;
        yp = C12;
        while (x != C21) {

          x++;
          y++;
          xp++;
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            valid = 0;
            goto confirmed;
          }
        }
      } else if (C11 > C21 && C12 > C22) {
        x = C11;
        y = C12;
        xp = C11;
        yp = C12;
        while (x != C21) {
          x--;
          y--;
          xp--;
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 > C21 && C12 < C22) {
        x = C11;
        y = C12;
        xp = C11;
        yp = C12;
        while (x != C21) {
          x--;
          y++;
          xp--;
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 < C21 && C12 > C22) {
        x = C11;
        y = C12;
        xp = C11;
        yp = C12;
        while (x != C21) {
          x++;
          y--;
          xp++;
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      }
    }
    // rook
    if (P == 114) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      if (C11 > C21 && C12 == C22) {
        while (xp != C21) {
          xp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (xp == C21) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (xp == C21) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }
      if (C11 < C21 && C12 == C22) {
        while (xp != C21) {
          xp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (xp == C21) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (xp == C21) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }
      if (C12 > C22 && C21 == C11) {
        while (yp != C22) {
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (yp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
        }
      }
      if (C12 < C22 && C21 == C11) {
        while (yp != C22) {
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (yp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }

    }
    // pawn
    else if (P == 112) {
      if (C22 == C12 + 2) {
        if (C11 == C21) {
          if (gridp[C11][C12 + 1] == 0 && gridp[C11][C12 + 2] == 0) {
            if (C22 == C12 + 2) {
              if (C12 == 1 || C12 == 6) {
                valid = 1;
                goto confirmed;
              }
            }
          }
        }
      } else if (C11 != C21) {
        if (C22 == C12 + 1) {
          if (C21 == 1 + C11 || C21 == C11 - 1) {
            if (gridp[C11 + 1][C12 + 1] == 1 ||
                gridp[C11 - 1][C12 + 1] == gridp[C11][C12] * -1) {
              if (C21 == C11 + 1 || C21 == C11 - 1) {
                if (gridp[C11][C12] == gridp[C21][C22] * -1) {
                  valid = 1;
                  goto confirmed;
                }
              }
            }
          }
        }
      } else if (C22 == C12 + 1) {
        if (C11 == C21) {
          if (gridp[C11][C12 + 1] == 0) {
            valid = 1;
            goto confirmed;
          }
        }
      }
    }
  confirmed:
    P = 0;
    result = valid;
  }
  if (result == 1) {
    return 1;
  }
  return -1;
}
int validmove(int x, int x2, int z, int y2, int result, int gridx[8][8],
              int gridp[8][8], int P) {
  // King
  int C11, C12, C21, C22, y, xp, yp, turn, valid;
  int C = 0;
  y = z;
  C11 = x;
  C12 = z;
  C21 = x2;
  C22 = y2;
  turn = 1;
  x = 0;
  y = 0;
  xp = 0;
  yp = 0;
  valid = 0;
  result = 0;
  if (gridp[C11][C12] == -1) {
    if (P == 107) {
      if (C11 - C21 == 1 || C11 - C21 == -1) {
        if (C12 - C22 == 0 || C12 - C22 == 1 || C12 - C22 == -1) {
          if (gridp[C21][C22] != gridp[C11][C12]) {
            valid = 1;
            goto confirmed;
            valid = 1;
          }
        }
      }
      if (C11 - C21 == 0) {
        if (C12 - C22 == 1 || C12 - C22 == -1) {
          if (gridp[C21][C22] != gridp[C11][C12]) {
            valid = 1;
            goto confirmed;
            valid = 1;
          }
        }
      }
    }
    // Knight
    else if (P == 110) {
      if (C21 == C11 + 1 || C21 == C11 - 1) {
        if (C22 == C12 - 2 || C22 == C12 + 2) {
          if (gridp[C11][C12] != gridp[C21][C22]) {
            valid = 1;
            goto confirmed;
            valid = 1;
          }
        }
      } else if (C11 == 2 + C21 || C11 == -2 + C21) {
        if (C22 == 1 + C22 || C22 == -1 + C22) {
          if (gridp[C11][C12] != gridp[C21][C22]) {
            valid = 1;
            goto confirmed;
            valid = 1;
          }
        }
      } else {
      }
    }
    // bishop
    else if (P == 98) {
      yp = C12;
      xp = C11;
      x = C11;
      y = C12;
      if (C21 > C11 && C22 > C12) {
        while (x != C21) {
          x++;
          y++;
          xp++;
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 > C21 && C12 > C22) {
        while (x != C21) {
          x--;
          y--;
          xp--;
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 > C21 && C12 < C22) {
        while (x != C21) {
          x--;
          y++;
          xp--;
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 < C21 && C12 > C22) {
        while (x != C21) {
          x++;
          y--;
          xp++;
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      }
    }
    // queen
    if (P == 113) {
      // right direction
      if (C11 < C21 && C22 == C12) {
        xp = C11;
        yp = C12;
        x = C11;
        y = C12;
        while (xp != C22) {
          xp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (xp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (xp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }
      if (C11 > C21 && C22 == C12) {
        xp = C11;
        yp = C12;
        x = C11;
        y = C12;
        while (xp != C22) {
          xp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (xp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (xp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      } else if (C11 == C21 && C12 > C22) {
        xp = C11;
        yp = C12;
        x = C11;
        y = C12;
        while (yp != C22) {
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (yp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }
      if (C11 == C21 && C22 > C12) {
        xp = C11;
        yp = C12;
        x = C11;
        y = C12;
        while (yp != C22) {
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (yp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
        }
      }
      if (C21 > C11 && C22 > C12) {
        x = C11;
        y = C12;
        xp = C11;
        yp = C12;
        while (x != C21) {

          x++;
          y++;
          xp++;
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            valid = 0;
            goto confirmed;
          }
        }
      } else if (C11 > C21 && C12 > C22) {
        x = C11;
        y = C12;
        xp = C11;
        yp = C12;
        while (x != C21) {
          x--;
          y--;
          xp--;
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 > C21 && C12 < C22) {
        x = C11;
        y = C12;
        xp = C11;
        yp = C12;
        while (x != C21) {
          x--;
          y++;
          xp--;
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      } else if (C11 < C21 && C12 > C22) {
        x = C11;
        y = C12;
        xp = C11;
        yp = C12;
        while (x != C21) {
          x++;
          y--;
          xp++;
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (x == C21) {
            if (y == C22) {
              if (gridp[xp][yp] != turn) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
            goto confirmed;
            valid = 0;
          }
        }
      }
    }
    // rook
    if (P == 114) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      if (C11 > C21 && C12 == C22) {
        while (xp != C21) {
          xp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (xp == C21) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (xp == C21) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }
      if (C11 < C21 && C12 == C22) {
        while (xp != C21) {
          xp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (xp == C21) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (xp == C21) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }
      if (C12 > C22 && C21 == C11) {
        while (yp != C22) {
          yp--;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (yp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
        }
      }
      if (C12 < C22 && C21 == C11) {
        while (yp != C22) {
          yp++;
          if (gridp[C11][C12] == gridp[xp][yp]) {
            valid = 0;
            goto confirmed;
          }
          if (gridp[C11][C12] == gridp[xp][yp] * -1) {
            if (xp != C21) {
              if (yp != C22) {
                valid = 0;
                goto confirmed;
              }
            }
          }
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              valid = 1;
              goto confirmed;
              valid = 1;
            }
          }
          if (gridp[xp][yp] != 0) {
            if (yp == C22) {
              if (gridp[xp][yp] != gridp[C11][C12]) {
                valid = 1;
                goto confirmed;
                valid = 1;
              }
            }
          }
        }
      }

    }
    // pawn
    else if (P == 112) {
      if (C22 == C12 - 2) {
        if (C11 == C21) {
          if (gridp[C11][C12 - 1] == 0 && gridp[C11][C12 - 2] == 0) {
            if (C22 == C12 - 2) {
              if (C12 == 1 || C12 == 6) {
                valid = 1;
                goto confirmed;
              }
            }
          }
        }
      } else if (C11 != C21) {
        if (C22 == C12 - 1) {
          if (C21 == 1 + C11 || C21 == C11 - 1) {
            if (gridp[C11 + 1][C12 - 1] == -1 ||
                gridp[C11 - 1][C12 - 1] == gridp[C11][C12] * -1) {
              if (C21 == C11 + 1 || C21 == C11 - 1) {
                // if(C21==C11-1){
                if (gridp[C11][C12] == gridp[C21][C22] * -1) {
                  valid = 1;
                  goto confirmed;
                }
                //}
              }
            }
          }
        }
      } else if (C22 == C12 - 1) {
        if (C11 == C21) {
          if (gridp[C11][C12 - 1] == 0) {
            if (C22 == C12 - 1) {
              valid = 1;
              goto confirmed;
            }
          }
        }
      }
    }
  confirmed:
    P = 0;
    result = valid;
  }
  if (result == 1) {
    return 1;
  }
  return -1;
}
void possible(int pm, int x, int y, int gridx[8][8], int gridp[8][8], int P,
              int xp, int yp, int C11, int C21, int C22, int C12, int turn,
              int PC, int x5, int y5, int x13, int y13, int gridp2[8][8],
              int x6, int y6, int gridx2[8][8]) {
  int C = 0;
  // king
  C11 = x13;
  C12 = y13;
  C21 = x5;
  C22 = y5;
  P = gridp2[x6][y6];
  if (P == 107 || P == 75) {
    if (C11 - C21 == 1 || C11 - C21 == -1) {
      if (C12 - C22 == 0 || C12 - C22 == 1 || C12 - C22 == -1) {
        if (gridp[C21][C22] != gridp[C11][C12]) {
          moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC, pm,
                x5, y5, x13, y13, gridx2, gridp2);
          return;
        }
      }
    }
    if (C11 - C21 == 0) {
      if (C12 - C22 == 1 || C12 - C22 == -1) {
        moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC, pm,
              x5, y5, x13, y13, gridx2, gridp2);
        return;
      }
    }
  }
  // Knight
  else if (P == 110 || P == 78) {
    if (C11 - C21 == 1 || C11 - C21 == -1) {
      if (C12 - C22 == -2 || C12 - C22 == 2) {
        moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC, pm,
              x5, y5, x13, y13, gridx2, gridp2);
        return;
      }
    } else if (C11 - C21 == 2 || C11 - C21 == -2) {
      if (C22 - C21 == 1 || C22 - C21 == -1) {
        moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC, pm,
              x5, y5, x13, y13, gridx2, gridp2);
        return;
      }
    } else {
    }
  }
  // bishop
  else if (P == 98 || P == 66) {
    yp = C12;
    xp = C11;
    x = C11;
    y = C12;
    if (C21 > C11 && C22 > C12) {
      while (x != C21) {
        x++;
        y++;
        xp++;
        yp++;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 > C21 && C12 > C22) {
      while (x != C21) {
        x--;
        y--;
        xp--;
        yp--;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 > C21 && C12 < C22) {
      while (x != C21) {
        x--;
        y++;
        xp--;
        yp++;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 < C21 && C12 > C22) {
      while (x != C21) {
        x++;
        y--;
        xp++;
        yp--;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else {
    }
  }

  // queen
  if (P == 113 || P == 81) {
    // right direction
    if (C11 < C21 && C22 == C12) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      while (xp != C22) {
        xp++;
        if (xp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (xp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                    pm, x5, y5, x13, y13, gridx2, gridp2);
              return;
            }
          }
        }
      }
    }
    if (C11 > C21 && C22 == C12) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      while (xp != C22) {
        xp--;
        if (xp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (xp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                    pm, x5, y5, x13, y13, gridx2, gridp2);
              return;
            }
          }
        }
      }
    } else if (C11 == C21 && C12 > C22) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      while (yp != C22) {
        yp--;
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                    pm, x5, y5, x13, y13, gridx2, gridp2);
              return;
            }
          }
        }
      }
    }
    if (C11 == C21 && C22 > C12) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      while (yp != C22) {
        yp++;
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                    pm, x5, y5, x13, y13, gridx2, gridp2);
              return;
            }
          }
        }
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
      }
    }
    if (C21 > C11 && C22 > C12) {
      x = C11;
      y = C12;
      xp = C11;
      yp = C12;
      while (x != C21) {

        x++;
        y++;
        xp++;
        yp++;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 > C21 && C12 > C22) {
      x = C11;
      y = C12;
      xp = C11;
      yp = C12;
      while (x != C21) {
        x--;
        y--;
        xp--;
        yp--;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 > C21 && C12 < C22) {
      x = C11;
      y = C12;
      xp = C11;
      yp = C12;
      while (x != C21) {
        x--;
        y++;
        xp--;
        yp++;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 < C21 && C12 > C22) {
      x = C11;
      y = C12;
      xp = C11;
      yp = C12;
      while (x != C21) {
        x++;
        y--;
        xp++;
        yp--;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    }
  }
  // rook
  if (P == 82 || P == 114) {
    xp = C11;
    yp = C12;
    x = C11;
    y = C12;
    if (C11 > C21 && C12 == C22) {
      while (xp != C21) {
        xp--;
        if (xp == C21) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (xp == C21) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                    pm, x5, y5, x13, y13, gridx2, gridp2);
              return;
            }
          }
        }
      }
    }
    if (C11 < C21 && C12 == C22) {
      while (xp != C21) {
        xp++;
        if (xp == C21) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (xp == C21) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                    pm, x5, y5, x13, y13, gridx2, gridp2);
              return;
            }
          }
        }
      }
    }
    if (C12 > C22 && C21 == C11) {
      while (yp != C22) {
        yp--;
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                    pm, x5, y5, x13, y13, gridx2, gridp2);
              return;
            }
          }
        }
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
      }
    }
    if (C12 < C22 && C21 == C11) {
      while (yp != C22) {
        yp++;
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                  pm, x5, y5, x13, y13, gridx2, gridp2);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC,
                    pm, x5, y5, x13, y13, gridx2, gridp2);
              return;
            }
          }
        }
      }
    }

  }
  // pawn
  else if (P == 112 || P == 80) {
    if (C22 - C12 == 2 || C22 - C12 == -2) {
      if (gridx[C11][C12] == 1) {
        while (C != 2) {
          C++;
          xp++;
          yp++;
          if (gridp[xp][yp] == 0) {
          } else {
            return;
          }
        }
      } else if (gridx[C11][C12] == -1) {
        while (C != 2) {
          C++;
          xp--;
          yp--;
          if (gridp[xp][yp] == 0) {
          } else {
            return;
          }
        }
      }
      if (gridx[C11][C12] == gridx[1][C12] ||
          gridx[C11][C12] == gridx[6][C12]) {
        moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC, pm,
              x5, y5, x13, y13, gridx2, gridp2);
        return;
      }
    } else if (C11 - C21 == 1 || C11 - C21 == -1) {
      if (C22 - C12 == 1 || C22 - C12 == -1) {
        xp = C21;
        yp = C22;
        if (gridp[xp][yp] == turn * -1) {
          moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC, pm,
                x5, y5, x13, y13, gridx2, gridp2);
          return;
        }
      }
    } else if (C22 - C12 == 1 || C22 - C12 == -1) {
      if (C11 == C21) {
        if (turn == 1) {
          xp++;
          yp++;
        } else if (turn == -1) {
          xp--;
          yp--;
        }
        if (gridp[xp][yp] == 0) {
          moveW(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC, pm,
                x5, y5, x13, y13, gridx2, gridp2);
          return;
        }
      }
    }
  }
}
void moveZ(int gridx2[8][8], int gridp2[8][8], int x13, int y13, int x5,
           int y5) {
  gridp2[x5][y5] = gridp2[x13][y13];
  gridp2[x13][y13] = 0;
  gridx2[x13][y13] = gridx2[x5][y5];
  gridx2[x13][y13] = 0;
}
void encode(int gridp2[8][8], int gridx2[8][8], int x13, int y13,
            int gridp[8][8], int gridx[8][8], int x5, int y5) {
  gridp2[x13][y13] = gridp[x13][y13];
  gridx2[x13][y13] = gridx[x13][y13];
  gridp2[x5][y5] = gridp[x5][y5];
  gridx2[x5][y5] = gridx[x5][y5];
}
void encode0(int gridx2[8][8], int gridp2[8][8], int gridx[8][8],
             int gridp[8][8]) {
  int one = 0;
  int two = 0;
  while (two != 8) {
    while (one != 0) {
      gridx2[one][two] = gridx[one][two];
      gridp2[one][two] = gridp[one][two];
      one++;
    }
    two++;
  }
}
void moveP(int pm, int x, int y, int gridx[8][8], int gridp[8][8], int P,
           int xp, int yp, int C11, int C21, int C22, int C12, int turn, int PC,
           int gridp2[8][8], int gridx2[8][8], int x13, int y13) {
  int x5 = 0;
  int y5 = 0;
  int x6 = 0;
  int y6 = 0;
  int x19 = 0;
  int y19 = 0;
  encode0(gridx2, gridp2, gridx, gridp);
  while (x13 != 8) {
    while (y13 != 8) {
      while (y5 != 8) {
        while (x5 != 8) {
          moveZ(gridx2, gridp2, x13, y13, x5, y5);
          while (y6 != 8) {
            while (x6 != 8) {
              while (y19 != 8) {
                while (x19 != 8) {
                  possible(pm, x, y, gridx, gridp, P, xp, yp, C11, C21, C22,
                           C12, turn, PC, x5, y5, x13, y13, gridp2, x6, y6,
                           gridx2);
                  x19++;
                }
                x19 = 0;
                y19++;
              }
              y19 = 0;
              x6++;
            }
            y6++;
          }
          encode(gridp2, gridx2, x13, y13, gridp, gridx, x5, y5);
          x5++;
        }
        y5++;
      }
      x13++;
    }
    y13++;
  }
}
void moveS(int x, int y, int gridx[8][8], int gridp[8][8], int P, int xp,
           int yp, int C11, int C21, int C22, int C12, int turn, int PC) {
  x = C11;
  y = C12;
  xp = C11;
  yp = C12;
  gridx[x][y] = 0;
  gridp[xp][yp] = 0;
  x = C21;
  y = C22;
  xp = C21;
  yp = C22;
  gridx[x][y] = P;
  gridp[xp][yp] = 1;
  return;
}
void graph(int x, int y, int gridx[8][8]) {
  y = 7;
  int CB = 8;
  x = 0;
  printf("\n\n\n\n\n\n\n\n\n\n\n");
  while (y != -1) {
    printf("%i   ", CB);
    while (x != 8) {
      if (gridx[x][y] == 114) {
        printf(" R ");
      } else if (gridx[x][y] == 110) {
        printf(" N ");
      } else if (gridx[x][y] == 98) {
        printf(" B ");
      } else if (gridx[x][y] == 107) {
        printf(" K ");
      } else if (gridx[x][y] == 113) {
        printf(" Q ");
      } else if (gridx[x][y] == 112) {
        printf(" P ");
      } else if (gridx[x][y] == 0) {
        printf("   ");
      } else {
        printf("%d", gridx[x][y]);
      }
      x++;
    }
    x = 0;

    y--;
    CB--;
    printf("\n");
  }
  printf("\n     1  2  3  4  5  6  7  8\n");
  return;
}
void pieceM(int xp, int yp, int gridx[8][8], int gridp[8][8], int P, int x,
            int y, int C11, int C12, int C21, int C22, int turn, int M1, int M2,
            int MC, int PC) {
  char t;
  int b;
start:
  M1 = 0;
  M2 = 0;
  printf("\n");
  scanf(" %i", &M1);
  scanf(" %i", &M2);
  b = 0;
  int C = 0;
  C11 = M1 / 10;
  C11 = C11 * 10;
  C12 = M1 - C11;
  C11 = C11 / 10;
  C21 = M2 / 10;
  C21 = C21 * 10;
  C22 = M2 - C21;
  C21 = C21 / 10;
  C21--, C22--, C11--, C12--;
  P = gridx[C11][C12];
  turn = 1;
  // King
  if (P == 107 || P == 75) {
    if (C11 - C21 == 1 || C11 - C21 == -1) {
      if (C12 - C22 == 0 || C12 - C22 == 1 || C12 - C22 == -1) {
        if (gridp[C21][C22] != gridp[C11][C12]) {
          moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
          return;
        }
      }
    }
    if (C11 - C21 == 0) {
      if (C12 - C22 == 1 || C12 - C22 == -1) {
        moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
        return;
      }
    }
  }
  // Knight
  else if (P == 110 || P == 78) {
    if (C11 - C21 == 1 || C11 - C21 == -1) {
      if (C12 - C22 == -2 || C12 - C22 == 2) {
        moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
        return;
      }
    } else if (C11 - C21 == 2 || C11 - C21 == -2) {
      if (C22 - C21 == 1 || C22 - C21 == -1) {
        moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
        return;
      }
    } else {
    }
  }
  // bishop
  else if (P == 98 || P == 66) {
    yp = C12;
    xp = C11;
    x = C11;
    y = C12;
    if (C21 > C11 && C22 > C12) {
      while (x != C21) {
        x++;
        y++;
        xp++;
        yp++;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 > C21 && C12 > C22) {
      while (x != C21) {
        x--;
        y--;
        xp--;
        yp--;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 > C21 && C12 < C22) {
      while (x != C21) {
        x--;
        y++;
        xp--;
        yp++;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 < C21 && C12 > C22) {
      while (x != C21) {
        x++;
        y--;
        xp++;
        yp--;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else {
    }
  }

  // queen
  if (P == 113 || P == 81) {
    // right direction
    if (C11 < C21 && C22 == C12) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      while (xp != C22) {
        xp++;
        if (xp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (xp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn,
                    PC);
              return;
            }
          }
        }
      }
    }
    if (C11 > C21 && C22 == C12) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      while (xp != C22) {
        xp--;
        if (xp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (xp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn,
                    PC);
              return;
            }
          }
        }
      }
    } else if (C11 == C21 && C12 > C22) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      while (yp != C22) {
        yp--;
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn,
                    PC);
              return;
            }
          }
        }
      }
    }
    if (C11 == C21 && C22 > C12) {
      xp = C11;
      yp = C12;
      x = C11;
      y = C12;
      while (yp != C22) {
        yp++;
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn,
                    PC);
              return;
            }
          }
        }
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
      }
    }
    if (C21 > C11 && C22 > C12) {
      x = C11;
      y = C12;
      xp = C11;
      yp = C12;
      while (x != C21) {

        x++;
        y++;
        xp++;
        yp++;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 > C21 && C12 > C22) {
      x = C11;
      y = C12;
      xp = C11;
      yp = C12;
      while (x != C21) {
        x--;
        y--;
        xp--;
        yp--;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 > C21 && C12 < C22) {
      x = C11;
      y = C12;
      xp = C11;
      yp = C12;
      while (x != C21) {
        x--;
        y++;
        xp--;
        yp++;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    } else if (C11 < C21 && C12 > C22) {
      x = C11;
      y = C12;
      xp = C11;
      yp = C12;
      while (x != C21) {
        x++;
        y--;
        xp++;
        yp--;
        if (x == C21) {
          if (gridp[xp][yp] != turn) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] == 1 || gridp[xp][yp] == -1) {
          return;
        }
      }
    }
  }
  // rook
  if (P == 82 || P == 114) {
    xp = C11;
    yp = C12;
    x = C11;
    y = C12;
    if (C11 > C21 && C12 == C22) {
      while (xp != C21) {
        xp--;
        if (xp == C21) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (xp == C21) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn,
                    PC);
              return;
            }
          }
        }
      }
    }
    if (C11 < C21 && C12 == C22) {
      while (xp != C21) {
        xp++;
        if (xp == C21) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (xp == C21) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn,
                    PC);
              return;
            }
          }
        }
      }
    }
    if (C12 > C22 && C21 == C11) {
      while (yp != C22) {
        yp--;
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn,
                    PC);
              return;
            }
          }
        }
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
      }
    }
    if (C12 < C22 && C21 == C11) {
      while (yp != C22) {
        yp++;
        if (yp == C22) {
          if (gridp[xp][yp] != gridp[C11][C12]) {
            moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
            return;
          }
        }
        if (gridp[xp][yp] != 0) {
          if (yp == C22) {
            if (gridp[xp][yp] != gridp[C11][C12]) {
              moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn,
                    PC);
              return;
            }
          }
        }
      }
    }

  }
  // pawn
  else if (P == 112 || P == 80) {
    moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
    return;
    goto start;
    if (C22 - C12 == 2 || C22 - C12 == -2) {
      if (gridp[C11][C12] == 1) {
        while (C != 2) {
          C++;
          xp++;
          yp++;
          if (gridp[xp][yp] == 0) {
          } else {
            return;
            goto start;
          }
        }
      } else if (gridx[C11][C12] == -1) {
        while (C != 2) {
          C++;
          xp--;
          yp--;
          if (gridp[xp][yp] == 0) {
          } else {
            return;
            goto start;
          }
        }
      }
      if (gridx[C11][C12] == gridx[1][C12] ||
          gridx[C11][C12] == gridx[6][C12]) {
        moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
        return;
        goto start;
      }
    } else if (C11 - C21 == 1 || C11 - C21 == -1) {
      if (C22 - C12 == 1 || C22 - C12 == -1) {
        xp = C21;
        yp = C22;
        if (gridp[xp][yp] == turn * -1) {
          moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
          return;
          goto start;
        }
      }
    } else if (C22 - C12 == 1 || C22 - C12 == -1) {
      if (C11 == C21) {
        if (turn == 1) {
          xp++;
          yp++;
        } else if (turn == -1) {
          xp--;
          yp--;
        }
        if (gridp[xp][yp] == 0) {
          moveS(x, y, gridx, gridp, P, xp, yp, C11, C21, C22, C12, turn, PC);
          return;
          goto start;
        }
      }
    }
  }
  goto start;
}
void pieceB2(int pm, int xp, int yp, int gridx[8][8], int gridp[8][8], int P,
             int x, int y, int C11, int C12, int C21, int C22, int turn, int M1,
             int M2, int MC, int PC, int safty[8][8][8][8][8][8],
             int grid4[8][8][8][8], int y13, int x13, int gridx2[8][8],
             int gridp2[8][8], int pgridx[8][8][8][8][8][8],
             int pgridp[8][8][8][8][8][8]) {
  // puts pieces in all possible places and takes a value of the postition
  // create another x and y varible because two will be needed for the two
  // grids.
  // grid1y (picks a piece to analise all situations on){ compleated
  // grid1x{ compleated
  // if statement to see if the gridp value is -1 compleated
  // grid2y(analises all situations for a piece)  { compleated
  // grid2x{compleated
  // pieceM like funtion to check if the moves are valid compleated
  // formula
  // queen  9(safty(pieces gaurding the queen's square-pieces
  // attacking))(moves)- oppentents queen if aplicable + pieces gaurding +rook
  // 5(safty)(moves)- opps rook
  //+ bisop night 3(safty)(moves)-opp bishop kight
  //+ pawn 1(safty)(24/(distance from end+ 16))
  // grid1}
  // grid1}
  // reports the final value to another funtion for the results to be recorded
  int errs = 0;
  int x2 = 0;
  int y2 = 0;
  int x3 = 0;
  int y3 = 0;
  float vt = 0;
  int T;
  float H;
  int moves;
  int value[8][8][8][8][8][8];
  int valuetest = 0;
  float v[size][size][size][size];
  float saftyv = 0;
  int x18 = 0;
  int y18 = 0;
  int yq = 0;
  int xq = 0;
  int yw = 0;
  int xw = 0;
  int xb = 0;
  int yb = 0;
  int x2b = 0;
  int y2b = 0;
  int tmv = 0;
  int coin = 0;
  int ranb = 0;
  float random[8][8][8][8];
  int valid = 0;
  int result = 0;
  int z = 0;
  saftyF(pm, xp, yp, gridx, gridp, P, x, y, C11, C12, C21, C22, turn, M1, M2,
         MC, PC, safty, grid4, pgridx, pgridp);
  time_t t;
  srand((unsigned)time(&t));
  x = 0;
  y = 0;
  while (y != 8) {
    while (x != 8) {
      while (y2 != 8) {
        while (x2 != 8) {
          coin = rand() % 150;
          random[x][y][x2][y2] = coin;
          x2++;
        }
        y2++;
        x2 = 0;
      }
      x++;
      y2 = 0;
    }
    y++;
    x = 0;
  }
  y = 0;
  x = 0;
  y2 = 0;
  x2 = 0;
  yq = 0;
  xq = 0;
  xw = 0;
  yw = 0;
  while (yq != 8) {
    while (xq != 8) {
      while (yw != 8) {
        while (xw != 8) {
          while (y != 8) {
            while (x != 8) {
              if (pgridx[xq][yq][xw][yw][x][y] == 98) {
                value[xq][yq][xw][yw][x][y] = 3 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 107) {
                value[xq][yq][xw][yw][x][y] = 40 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 110) {
                value[xq][yq][xw][yw][x][y] = 3 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 112) {
                value[xq][yq][xw][yw][x][y] = 1 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 113) {
                value[xq][yq][xw][yw][x][y] = 9 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 114) {
                value[xq][yq][xw][yw][x][y] = 5 * gridp[x][y];
              } else {
                value[xq][yq][xw][yw][x][y] = 0;
              }
              x++;
            }
            x = 0;
            y++;
          }
          y = 0;
          xw++;
        }
        xw = 0;
        yw++;
      }
      yw = 0;
      xq++;
    }
    xq = 0;
    yq++;
  }
  x = 0;
  y = 0;
  while (y != 8) {
    while (x != 8) {
      if (gridp[x][y] == -1) {
        while (y2 != 8) {
          while (x2 != 8) {
            // moveP(pm,x,y,gridx,gridp,P,xp,yp,C11,C21,C22,C12,turn,PC,gridp2,
            // gridx2,x13,y13);
            while (y18 != 8) {
              while (x18 != 8) {
                if (safty[x][y][x2][y2][x18][y18] > 3) {
                  saftyv = 1.4;
                } else if (safty[x][y][x2][y2][x18][y18] == 3) {
                  saftyv = 1.3;
                } else if (safty[x][y][x2][y2][x18][y18] == 2) {
                  saftyv = 1.2;
                } else if (safty[x][y][x2][y2][x18][y18] == 1) {
                  saftyv = 1.1;
                } else if (safty[x][y][x2][y2][x18][y18] == 0) {
                  saftyv = 1;
                } else if (safty[x][y][x2][y2][x18][y18] == -1) {
                  saftyv = .1;
                } else if (safty[x][y][x2][y2][x18][y18] == -2) {
                  saftyv = .05;
                } else if (safty[x][y][x2][y2][x18][y18] == -3) {
                  saftyv = .001;
                } else if (safty[x][y][x2][y2][x18][y18] < -3) {
                  saftyv = 0;
                }
                H = saftyv * value[x][y][x2][y2][x18][y18];
                vt = vt + H;
                //   H = grid4[x][y][x2][y2] * .1;
                //  vt = vt + H;
                x18++;
              }
              x18 = 0;
              y18++;
            }
            v[x][y][x2][y2] = vt;
            vt = 0;
            y18 = 0;
            x2++;
          }

          x2 = 0;
          y2++;
        }
      }
      y2 = 0;
      x++;
    }
    x = 0;
    y++;
  }
  z = 0;
  // best value
  x2 = 0;
  y2 = 0;
  xb = 0;
  yb = 0;
  x2b = 0;
  y2b = 0;
  while (z != 8) {
    while (x != 8) {
      while (y2 != 8) {
        while (x2 != 8) {
          P = gridx[x][z];
          valid = 0;
          valid = validmove2(x, x2, z, y2, result, gridx, gridp, P);
          v[0][0][0][0] = -10000;
          if (valid == 1) {
            if (x + z + x2 + y2 != 0) {
              if (v[x][z][x2][y2] == v[xb][yb][x2b][y2b]) {
                if (random[x][z][x2][y2] > ranb) {
                  xb = x;
                  yb = z;
                  x2b = x2;
                  y2b = y2;
                  ranb = random[x][z][x2][y2];
                }
              }
              if (v[x][z][x2][y2] > v[xb][yb][x2b][y2b]) {
                xb = x;
                yb = z;
                x2b = x2;
                y2b = y2;
                ranb = random[x][z][x2][y2];
              }
            }
          }
          x2++;
        }
        y2++;
        x2 = 0;
      }
      x++;
      y2 = 0;
    }
    z++;
    x = 0;
  }
  x = 0;
  y = 0;
  gridp[x2b][y2b] = gridp[xb][yb];
  gridp[xb][yb] = 0;
  gridx[x2b][y2b] = gridx[xb][yb];
  gridx[xb][yb] = 0;
}
void pieceB(int pm, int xp, int yp, int gridx[8][8], int gridp[8][8], int P,
            int x, int y, int C11, int C12, int C21, int C22, int turn, int M1,
            int M2, int MC, int PC, int safty[8][8][8][8][8][8],
            int grid4[8][8][8][8], int y13, int x13, int gridx2[8][8],
            int gridp2[8][8], int pgridx[8][8][8][8][8][8],
            int pgridp[8][8][8][8][8][8]) {
  // puts pieces in all possible places and takes a value of the postition
  // create another x and y varible because two will be needed for the two
  // grids.
  // grid1y (picks a piece to analise all situations on){ compleated
  // grid1x{ compleated
  // if statement to see if the gridp value is -1 compleated
  // grid2y(analises all situations for a piece)  { compleated
  // grid2x{compleated
  // pieceM like funtion to check if the moves are valid compleated
  // formula
  // queen  9(safty(pieces gaurding the queen's square-pieces
  // attacking))(moves)- oppentents queen if aplicable + pieces gaurding +rook
  // 5(safty)(moves)- opps rook
  //+ bisop night 3(safty)(moves)-opp bishop kight
  //+ pawn 1(safty)(24/(distance from end+ 16))
  // grid1}
  // grid1}
  // reports the final value to another funtion for the results to be recorded
  int errs = 0;
  int x2 = 0;
  int y2 = 0;
  int x3 = 0;
  int y3 = 0;
  float vt = 0;
  int T;
  float H;
  int moves;
  int value[8][8][8][8][8][8];
  int valuetest = 0;
  float v[size][size][size][size];
  float saftyv = 0;
  int x18 = 0;
  int y18 = 0;
  int yq = 0;
  int xq = 0;
  int yw = 0;
  int xw = 0;
  int xb = 0;
  int yb = 0;
  int x2b = 0;
  int y2b = 0;
  int tmv = 0;
  int coin = 0;
  int ranb = 0;
  float random[8][8][8][8];
  int valid = 0;
  int result = 0;
  int z = 0;
  saftyF(pm, xp, yp, gridx, gridp, P, x, y, C11, C12, C21, C22, turn, M1, M2,
         MC, PC, safty, grid4, pgridx, pgridp);
  time_t t;
  srand((unsigned)time(&t));
  x = 0;
  y = 0;
  while (y != 8) {
    while (x != 8) {
      while (y2 != 8) {
        while (x2 != 8) {
          coin = rand() % 150;
          random[x][y][x2][y2] = coin;
          x2++;
        }
        y2++;
        x2 = 0;
      }
      x++;
      y2 = 0;
    }
    y++;
    x = 0;
  }
  y = 0;
  x = 0;
  y2 = 0;
  x2 = 0;
  yq = 0;
  xq = 0;
  xw = 0;
  yw = 0;
  while (yq != 8) {
    while (xq != 8) {
      while (yw != 8) {
        while (xw != 8) {
          while (y != 8) {
            while (x != 8) {
              if (pgridx[xq][yq][xw][yw][x][y] == 98) {
                value[xq][yq][xw][yw][x][y] = 3 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 107) {
                value[xq][yq][xw][yw][x][y] = 40 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 110) {
                value[xq][yq][xw][yw][x][y] = 3 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 112) {
                value[xq][yq][xw][yw][x][y] = 1 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 113) {
                value[xq][yq][xw][yw][x][y] = 9 * gridp[x][y];
              } else if (pgridx[xq][yq][xw][yw][x][y] == 114) {
                value[xq][yq][xw][yw][x][y] = 5 * gridp[x][y];
              } else {
                value[xq][yq][xw][yw][x][y] = 0;
              }
              x++;
            }
            x = 0;
            y++;
          }
          y = 0;
          xw++;
        }
        xw = 0;
        yw++;
      }
      yw = 0;
      xq++;
    }
    xq = 0;
    yq++;
  }
  x = 0;
  y = 0;
  while (y != 8) {
    while (x != 8) {
      if (gridp[x][y] == -1) {
        while (y2 != 8) {
          while (x2 != 8) {
            // moveP(pm,x,y,gridx,gridp,P,xp,yp,C11,C21,C22,C12,turn,PC,gridp2,
            // gridx2,x13,y13);
            while (y18 != 8) {
              while (x18 != 8) {
                if (safty[x][y][x2][y2][x18][y18] > 3) {
                  saftyv = 1.4;
                } else if (safty[x][y][x2][y2][x18][y18] == 3) {
                  saftyv = 1.3;
                } else if (safty[x][y][x2][y2][x18][y18] == 2) {
                  saftyv = 1.2;
                } else if (safty[x][y][x2][y2][x18][y18] == 1) {
                  saftyv = 1.1;
                } else if (safty[x][y][x2][y2][x18][y18] == 0) {
                  saftyv = 1;
                } else if (safty[x][y][x2][y2][x18][y18] == -1) {
                  saftyv = .1;
                } else if (safty[x][y][x2][y2][x18][y18] == -2) {
                  saftyv = .05;
                } else if (safty[x][y][x2][y2][x18][y18] == -3) {
                  saftyv = .001;
                } else if (safty[x][y][x2][y2][x18][y18] < -3) {
                  saftyv = 0;
                }
                H = saftyv * value[x][y][x2][y2][x18][y18];
                vt = vt + H;
                //   H = grid4[x][y][x2][y2] * .1;
                //  vt = vt + H;
                x18++;
              }
              x18 = 0;
              y18++;
            }
            v[x][y][x2][y2] = vt;
            vt = 0;
            y18 = 0;
            x2++;
          }

          x2 = 0;
          y2++;
        }
      }
      y2 = 0;
      x++;
    }
    x = 0;
    y++;
  }
  z = 0;
  // best value
  x2 = 0;
  y2 = 0;
  xb = 0;
  yb = 0;
  x2b = 0;
  y2b = 0;
  while (z != 8) {
    while (x != 8) {
      while (y2 != 8) {
        while (x2 != 8) {
          P = gridx[x][z];
          valid = 0;
          valid = validmove(x, x2, z, y2, result, gridx, gridp, P);
          v[0][0][0][0] = 10000;
          if (valid == 1) {
            if (x + z + x2 + y2 != 0) {
              if (v[x][z][x2][y2] == v[xb][yb][x2b][y2b]) {
                if (random[x][z][x2][y2] > ranb) {
                  xb = x;
                  yb = z;
                  x2b = x2;
                  y2b = y2;
                  ranb = random[x][z][x2][y2];
                }
              }
              if (v[x][z][x2][y2] < v[xb][yb][x2b][y2b]) {
                xb = x;
                yb = z;
                x2b = x2;
                y2b = y2;
                ranb = random[x][z][x2][y2];
              }
            }
          }
          x2++;
        }
        y2++;
        x2 = 0;
      }
      x++;
      y2 = 0;
    }
    z++;
    x = 0;
  }
  x = 0;
  y = 0;
  gridp[x2b][y2b] = gridp[xb][yb];
  gridp[xb][yb] = 0;
  gridx[x2b][y2b] = gridx[xb][yb];
  gridx[xb][yb] = 0;
  while (y != 8) {
    while (x != 8) {
      x++;
    }
    x = 0;
    y++;
  }
}
int main() {
  int x13, y13;
  int gridx2[8][8];
  int gridp2[8][8];
  int pgridx[8][8][8][8][8][8];
  int pgridp[8][8][8][8][8][8];
  int safty[8][8][8][8][8][8];
  int grid4[8][8][8][8];
  int pm;
  int P, C11, C22, C12, C21, M1, M2, MC = 0, PC;
  int placeholder;
  int turn = 1;
  int x = 0, y = 0;
  int xp = 0, yp = 0;
  int gridx[size][size];
  int gridp[size][size];
  int anothervalue = 0;
  printf("Enter 1 for the computer to face itself. Enter 2 to face the "
         "computer.\n");
valuescan:
  scanf("%i", &anothervalue);
  if (anothervalue != 1) {
    if (anothervalue != 2) {
      printf("Enter 1 or 2.\n");
      goto valuescan;
    }
  }
  if(anothervalue==2){
    printf("\nYou go first\n\n");
  }
  while (y != size) {
    while (x != size) {
      if (y > 1 && y < 6) {
        gridx[x][y] = 0;
      }
      if (y > 1 && y < 6) {
        gridp[xp][yp] = 0;
      }
      if (y < 2) {
        gridp[x][y] = 1;
      }
      if (y > 5) {
        gridp[x][y] = -1;
      }
      if (y == 1 || y == 6) {
        gridx[x][y] = 112;
      }
      if (x == 0 || x == 7) {
        if (y == 0 || y == 7) {
          gridx[x][y] = 114;
        }
      }
      if (x == 1 || x == 6) {
        if (y == 0 || y == 7) {
          gridx[x][y] = 110;
        }
      }
      if (x == 2 || x == 5) {
        if (y == 0 || y == 7) {
          gridx[x][y] = 98;
        }
      }
      if (x == 3) {
        if (y == 0 || y == 7) {
          gridx[x][y] = 107;
        }
      }
      if (x == 4) {
        if (y == 0 || y == 7) {
          gridx[x][y] = 113;
        }
      }
      x++;
      xp++;
    }
    x = 0;
    y++;
    yp++;
    xp = 0;
  }
  y = 7;
  x = 0;
  int CB = 8;
  while (y != -1) {
    printf("%i   ", CB);
    while (x != 8) {
      if (gridx[x][y] == 114) {
        printf(" R ");
      } else if (gridx[x][y] == 110) {
        printf(" N ");
      } else if (gridx[x][y] == 98) {
        printf(" B ");
      } else if (gridx[x][y] == 107) {
        printf(" K ");
      } else if (gridx[x][y] == 113) {
        printf(" Q ");
      } else if (gridx[x][y] == 112) {
        printf(" P ");
      } else if (gridx[x][y] == 0) {
        printf("   ");
      }
      x++;
    }
    CB--;
    x = 0;
    y--;
    printf("\n");
  }
  printf("\n     1  2  3  4  5  6  7  8  \n");
  while (MC == 0) {
    if (anothervalue == 1) {
      pieceB2(pm, xp, yp, gridx, gridp, P, x, y, C11, C12, C21, C22, turn, M1,
              M2, MC, PC, safty, grid4, y13, x13, gridx2, gridp2, pgridx,
              pgridp);
      sleep(1);
    }
    if (anothervalue == 2) {
      pieceM(xp, yp, gridx, gridp, P, x, y, C11, C12, C21, C22, turn, M1, M2,
             MC, PC);
    }
    graph(x, y, gridx);
    placeholder = gamecheck(gridx, gridp);
    if (placeholder == 1) {
    } else if (placeholder == 2) {
      printf("black won\n");
      sleep(100);
    } else if (placeholder == 3) {
      printf("white won\n");
      sleep(100);
    } else if (placeholder == 4) {
    }
    pieceB(pm, xp, yp, gridx, gridp, P, x, y, C11, C12, C21, C22, turn, M1, M2,
           MC, PC, safty, grid4, y13, x13, gridx2, gridp2, pgridx, pgridp);
    sleep(1);
    graph(x, y, gridx);
    placeholder = gamecheck(gridx, gridp);
    if (placeholder == 1) {

    } else if (placeholder == 2) {
      printf("black won\n");
      sleep(100);
    } else if (placeholder == 3) {
      printf("white won\n");
      sleep(100);
    } else if (placeholder == 4) {
      printf("here");
    }
  }
}
