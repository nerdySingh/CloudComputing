#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  const int KB = 1024; /* bytes */
  const int MB = 1024 * KB; /* bytes */
  const int GB = 1024 * MB; /* bytes */
  long size = 0;
  void *p = NULL;

  int ctr;
  int j;
  int times = 100000;
  long sum = 0;
  for(ctr = 0; ctr < times; ctr ++ ) {
    size = 100 * MB;
    printf("Allocating %d bytes memory \n", size);
    p = calloc(1, size);
    if(p != NULL) {
      printf("SUCCESS.\n");
      sum += size;

      for(j=0; j<size; j++) {
	((char*)p)[j] = 1;
      }

      if(sum < GB) {
	printf("Total allocated so far: %ld MB\n", sum/MB);
      } else {
	printf("Total al
