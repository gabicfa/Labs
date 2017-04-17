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
  int row = src->nrows;
  int col = src->ncols;
  int row_dest = dest->nrows;
  int col_dest = dest->ncols;
  for (i = 0; i < row; i+=BLOCK_SIZE) {
    for (j = 0; j < col; j+=BLOCK_SIZE) {
      for(i1 = i; i1<i+BLOCK_SIZE; i1++){
        for(j1=j; j1<j+BLOCK_SIZE; j1 ++){
          dest->data[(row_dest - j1 - 1)* col_dest+i1]=
          src->data[i1*col+j1];

        }
      }
    }
  }
}

float better_avg_luma(image_t *img) {
  int i, j;
  double luma =0.0;
  pixel_t pix;

  for (i = 0; i < img->nrows; i++) {
    for (j = 0; j < img->ncols; j++) {
          pix = img->data[i*img->ncols+j];
          luma += 0.299 * (pix.c[0]) +
                  0.587 * (pix.c[1]) +
                  0.114 * (pix.c[2]);
    }
  }

  // int i1,j1;
  // for (i = 0; i < img->nrows; i+=BLOCK_SIZE) {
  //   for (j = 0; j < img->ncols; j+=BLOCK_SIZE) {
  //     for(i1 = i; i1<i+BLOCK_SIZE; i1++){
  //       for(j1=j; j1<j+BLOCK_SIZE; j1 ++){
  //         pix = img->data[i1*img->ncols+j1];
  //         luma += 0.299 * (pix.c[0]) +
  //                 0.587 * (pix.c[1]) +
  //                 0.114 * (pix.c[2]);
  //       }
  //     }
  //   }
  // }

  luma /= (img->nrows * img->ncols);

  return (float) luma;
}
