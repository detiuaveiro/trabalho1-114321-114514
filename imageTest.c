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
  
  printf("# LOAD image\n");
  InstrReset();
  // Image imgOriginal = ImageLoad(argv[1]);
  Image img1 = ImageLoad(argv[1]);
  Image img2 = ImageLoad(argv[1]);


  if (img1 == NULL) {
    error(2, errno, "Loading %s: %s", argv[1], ImageErrMsg());
  }
  InstrPrint();

  printf("# Blur image\n");
  InstrReset();
  ImageBlur(img1, 10, 10);
  InstrPrint();


  printf("# Improved Blur image\n");
  InstrReset();
  ImageBlurImproved(img2, 10, 10);
  InstrPrint();

  printf("Compare BLUR with BLURIMPROVED:\n");
  if (ImageMatchSubImage(img2, 0, 0, img1))
    printf("MATCH!\n");
  else
    printf("DONT MATCH\n");

  // if (img2 == NULL) {
  //   error(2, errno, "Rotating img2: %s", ImageErrMsg());
  // }

  if (ImageSave(img1, argv[2]) == 0 && ImageSave(img2, argv[3]) == 0) {
    error(2, errno, "%s: %s", argv[2], ImageErrMsg());
  }


  ImageDestroy(&img1);
  return 0;
}

