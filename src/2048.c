#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#define _FFD380 (Color){0xFF, 0xD3, 0x80, 0xFF}
#define _FFA600 (Color){0xFF, 0xA6, 0x00, 0xFF}
#define _FF8531 (Color){0xFF, 0x85, 0x31, 0xFF}
#define _FF6361 (Color){0xFF, 0x63, 0x61, 0xFF}
#define _8A508F (Color){0x8A, 0x50, 0x8F, 0xFF}
#define _2C4875 (Color){0x2C, 0x48, 0x75, 0xFF}
#define _003F5C (Color){0x00, 0x3F, 0x5C, 0xFF}
#define _00202E (Color){0x00, 0x20, 0x2E, 0xFF}


#define SW 600
#define SH 750
#define CELL 150
#define GRID(x,y) (((x)*4)+(y))

int newBlock(int*);
int moveL(int*);
int moveR(int*);
int moveU(int*);
int moveD(int*);

int score = 0;

int main() {
  InitWindow(SW, SH, "2048");

  int *grid = (int*)calloc(16, sizeof(int));
  Color colors[] = { PINK, _FFD380, _FFA600, _FF8531, _FF6361, _8A508F, _2C4875, _003F5C, _00202E};
  int state = 0; // 0 - Playing | 1 - Won | 2 - Failed
  
  newBlock(grid);
  
  SetTargetFPS(60);

  BeginDrawing();
  ClearBackground(WHITE);
  EndDrawing();
  
  while(!WindowShouldClose()) {
    if(state == 0) {
      if(IsKeyPressed(KEY_A)) {
	if(moveL(grid))
	  if(newBlock(grid))
	    state = 2;
      } else if(IsKeyPressed(KEY_D)) {
	if(moveR(grid))
	  if(newBlock(grid))
	    state = 2;
      } else if(IsKeyPressed(KEY_W)) {
	if(moveU(grid))
	  if(newBlock(grid))
	    state = 2;
      } else if(IsKeyPressed(KEY_S)) {
	if(moveD(grid))
	  if(newBlock(grid))
	    state = 2;
      }
    }
    
    // Rendering
    BeginDrawing();
    DrawRectangle(0,0,SW,SH, (Color){255, 255, 255, 60});

    int w = MeasureText("2048", 70) / 2;
    DrawText("2048", SW / 2 - w, 50, 70, BLACK);

    printf("%d\n", score);

    for(int x = 0; x < 4; ++x) {
      for(int y = 0; y < 4; ++y) {
	if(grid[GRID(x,y)] > 0)
	  DrawRectangle(x * CELL, CELL + y * CELL, CELL, CELL, colors[grid[GRID(x,y)]]);
	DrawRectangleLines(x * CELL, CELL + y * CELL, CELL, CELL, BLACK);
      }
    }

   if(state == 2) {
      int m = MeasureText("YOU FAILED", 70) / 2;
      DrawText("YOU FAILED", SW / 2 - m, SH / 2, 70, BLACK);
    }

    EndDrawing();
  }
  
  return 0;
}

int moveL(int *grid) {
  int moved = 0;
  for(int y = 0; y < 4; ++y) {
    for(int x = 0; x < 4; ++x) {
      // For this grid, merge if same/move if empty
      for(int d = x+1; d < 4; ++d) {
	if(grid[GRID(x,y)] == 0) {
	  grid[GRID(x,y)] = grid[GRID(d,y)];
	  grid[GRID(d,y)] = 0;
	  moved = 1;
	  continue;
	}
	else if(grid[GRID(x,y)] == grid[GRID(d,y)]) {
	  score += 2 << grid[GRID(x,y)]++;
	  grid[GRID(d,y)] = 0;
	  moved = 1;
	  continue;
	}
      }
    }
  }
   return moved;
}

int moveR(int *grid) {
  int moved = 0;
  for(int y = 0; y < 4; ++y) {
    for(int x = 3; x >= 0; --x) {
      // For this grid, merge if same/move if empty
      for(int d = x-1; d >= 0; --d) {
	if(grid[GRID(x,y)] == 0) {
	  grid[GRID(x,y)] = grid[GRID(d,y)];
	  grid[GRID(d,y)] = 0;
	  moved = 1;
	  continue;
	}
	else if(grid[GRID(x,y)] == grid[GRID(d,y)]) {
	  score += 2 << grid[GRID(x,y)]++;
	  grid[GRID(d,y)] = 0;
	  moved = 1;
	  continue;
	}
      }
    }
  }
   return moved;
}

int moveD(int *grid) {
  int moved = 0;
  for(int y = 3; y >= 0; --y) {
    for(int x = 0; x < 4; ++x) {
      // For this grid, merge if same/move if empty
      for(int d = y-1; d >= 0; --d) {
	if(grid[GRID(x,y)] == 0) {
	  grid[GRID(x,y)] = grid[GRID(x,d)];
	  grid[GRID(x,d)] = 0;
	  moved = 1;
	  continue;
	}
	else if(grid[GRID(x,y)] == grid[GRID(x,d)]) {
	  score += 2 << grid[GRID(x,y)]++;
	  grid[GRID(x,d)] = 0;
	  moved = 1;
	  continue;
	}
      }
    }
  }
  return moved;
}

int moveU(int *grid) {
  int moved = 0;
  for(int y = 0; y < 4; ++y) {
    for(int x = 0; x < 4; ++x) {
      // For this grid, merge if same/move if empty
      for(int d = y+1; d < 4; ++d) {
	if(grid[GRID(x,y)] == 0) {
	  grid[GRID(x,y)] = grid[GRID(x,d)];
	  grid[GRID(x,d)] = 0;
	  moved = 1;
	  continue;
	}
	else if(grid[GRID(x,y)] == grid[GRID(x,d)]) {
	  score += 2 << grid[GRID(x,y)]++;
	  grid[GRID(x,d)] = 0;
	  moved = 1;
	  continue;
	}
      }
    }
  }
  return moved;
}

int newBlock(int *grid) {
  int i, p;
  for(i = 0; i < 16; ++i)
    if(grid[i] == 0) break;
  
  if(i == 16) return 1;
  
  do {
    p = GetRandomValue(0, 15);
  } while(grid[p] != 0);

  grid[p] = 1;
  return 0;
}
