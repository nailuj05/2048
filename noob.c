#include "noob.h"

int main(int argc, const char *argv[]) {
  RebuildYourself(argc, argv);

  int run = HasFlag(argc, argv, "run");

  BuildAndRunCommand("rm -rf builds/2048 && gcc src/2048.c -Iinclude -lraylib "
                       "-lGL -lm -lpthread "
                       "-ldl -lrt -lX11 "
                       "-o builds/2048");


  if (run)
    BuildAndRunCommand("./builds/2048");

  return 0;
}
