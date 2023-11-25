// imageTest - A program that performs some image processing.
//
// This program is an example use of the image8bit module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// João Manuel Rodrigues <jmr@ua.pt>
// 2023

#include <assert.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image8bit.h"
#include "instrumentation.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    error(1, 0, "Usage: imageTest input.pgm output.pgm");
  }

  ImageInit();
  Image img1 = ImageLoad(argv[1]);

  if (img1 == NULL) {
    error(2, errno, "Loading %s: %s", argv[1], ImageErrMsg());
  }

  int bestH1 = 50;
  int bestW1 = 50;
  printf("# Image Locate Melhor caso (Img2 = %dx%d) \n", bestH1, bestW1);
  Image img2 = ImageCrop(img1, 0, 0, bestH1, bestW1);
  int px = 0;
  int py = 0;

  InstrReset();
  ImageLocateSubImage(img1,&px, &py, img2);
  InstrPrint();

  int h1 = 1000;
  int w1 = 1000;
  int h2 = 50;
  int w2 = 50;
  Image black = ImageCreate(h1, w1, 255);
  Image white = ImageCreate(h2, w2, 255);
  ImageNegative(white);
  ImagePaste(black, 950, 950, white);

  printf("# Image Locate Pior caso (subimage = %dx%d) \n", w1, w2);

  InstrReset();
  ImageLocateSubImage(black,&px, &py, white);
  InstrPrint();

  printf("\n\nCalculado: %d\n", 2*((w1-w2+1)*(h1-h2+1) + w2*h2));


  if (ImageSave(black, argv[2]) == 0 ) {
    error(2, errno, "%s: %s", argv[2], ImageErrMsg());
  }


  ImageDestroy(&img1);
  ImageDestroy(&img2);

  return 0;
}

