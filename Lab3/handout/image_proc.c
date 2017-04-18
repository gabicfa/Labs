#include <stdlib.h>

#include "image.h"
#include "image_proc.h"
#define BLOCK_SIZE 8

void rotate_image(image_t *src, image_t *dest) {
  int i, j;
  pixel_t pix;
  for (i = 0; i < src->nrows; i++) {
    for (j = 0; j < src->ncols; j++) {
      pix = get_pix(src, i, j);
      set_pix(dest, dest->nrows - j - 1, i, pix);
    }
  }
}

float avg_luma(image_t *img) {
  int i, j;
  double luma;
  pixel_t pix;

  luma = 0.0;
  for (i = 0; i < img->nrows; i++) {
    for (j = 0; j < img->ncols; j++) {
      pix = get_pix(img, i, j);
      luma += 0.299 * ((double) pix.c[0]) +
              0.587 * ((double) pix.c[1]) +
              0.114 * ((double) pix.c[2]);
    }
  }
  luma /= (double) (img->nrows * img->ncols);
  return (float) luma;
}

void better_rotate_image(image_t *src, image_t *dest) {
  int i, j, i1, j1;
  int lado = src->nrows;

  for (i = 0; i < lado; i+=BLOCK_SIZE) {
    for (j = 0; j < lado; j+=BLOCK_SIZE) {
      for(i1 = i; i1<i+BLOCK_SIZE; i1++){
        for(j1 = j; j1<j+BLOCK_SIZE; j1++){
          dest->data[(lado - j1 - 1)* lado+i1]=
          src->data[i1*lado+j1];
        }
      }
    }
  }
}

float better_avg_luma(image_t *img) {
  int i, j;
  pixel_t pix;

  double luma = 0.0;
  int lado = img->nrows;

  for (i = 0; i < lado; i++) {
    for (j = 0; j < lado; j++) {
          pix = img->data[i*lado+j];
          luma += 0.299 * (pix.c[0]) +
                  0.587 * (pix.c[1]) +
                  0.114 * (pix.c[2]);
    }
  }
   
  luma /= (lado*lado);

  return (float) luma;
}
