
#include "process_image.h"

Pnm_ppm prep(Pnm_ppm pic)
{
        UArray2b_T array = pic->pixels;
        if (pic->width % 2 != 0) {
            UArray2b_T shaved = UArray2b_new(pic->width - 1, pic->height, (sizeof (struct Pnm_rgb)), 2);
            UArray2b_map(array, shave_column, shaved);
            UArray2b_free(&array);
            array = shaved;
            pic->width = pic->width - 1;
        }
        if (pic->height % 2 != 0) {
                UArray2b_T shaved = UArray2b_new(pic->width, pic->height - 1, (sizeof (struct Pnm_rgb)), 2);
                UArray2b_map(array, shave_row, shaved);
                UArray2b_free(&array);
                array = shaved;
                pic->height = pic->height - 1;
        }
        pic->pixels = array;
        fprintf(stdout, "Write after image\n");
        FILE *writeTo2 = fopen("after.ppm", "w");
        Pnm_ppmwrite(writeTo2, pic);
        fclose(writeTo2);
        return pic;
}


void shave_column(int col, int row, UArray2b_T array2b, void *elem,
                    void *cl)
{
    if (col < UArray2b_width(array2b) - 1) {
        *(Pnm_rgb) UArray2b_at((UArray2b_T)(cl), col, row) = *(Pnm_rgb)elem;
    } else {
    }
}


void shave_row(int col, int row, UArray2b_T array2b, void *elem,
                void *cl)
{
    if (row < UArray2b_height(array2b) - 1) {   
        *(Pnm_rgb) UArray2b_at((UArray2b_T)(cl), col, row) = *(Pnm_rgb)elem;
    }

    else {
    }
}

