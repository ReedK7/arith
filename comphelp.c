/*
 *          comphelp.c
 *      Authors: Nick Murphy and Reed Kass-Mullet
 *      Assignment: Comp40 Homework 4, arith
 *      Due: October 26
 * 
 * 
 */


#include "comphelp.h"


UArray_T quantize(UArray_T pack) 
{
    float pb, pr;
    pb = (*((float *) (UArray_at(pack, 4)))/4);
    pr = (*((float *) (UArray_at(pack, 5)))/4);
    float rep_pb = Arith40_index_of_chroma(pb);
    float rep_pr = Arith40_index_of_chroma(pr);
    *((unsigned *) (UArray_at(pack, 4))) = rep_pb;
    *((unsigned *) (UArray_at(pack, 5))) = rep_pr;
    printf("[pb  pr] == [%f  %f]\n", rep_pb, rep_pr);
    return pack;
}


UArray_T discrete_cosine_transform(UArray_T pack)
{
    float y1, y2, y3, y4, a, b, c, d;
   // int length = UArray_length(pack);
    //for(int i = 0; i < length; ++i) {
    //    int x = *((unsigned *) (UArray_at(pack, i)));
    //    if(x != 0){
        //printf("Heres: %d at %d ", x, i);
    //    }
    //}
    //printf("\n");
    y1 = *((float *) (UArray_at(pack, 0)));
    y2 = *((float *) (UArray_at(pack, 1)));
    y3 = *((float *) (UArray_at(pack, 2)));
    y4 = *((float *) (UArray_at(pack, 3)));
    printf("[y1  y2  y3  y4]  ==  [%f  %f  %f %f]\n", y1, y2, y3, y4);
    a = (y4 + y3 + y2 + y1) / 4;
    b = (y4 + y3 - y2 - y1) / 4;
    c = (y4 - y3 + y2 - y1) / 4;
    d = (y4 - y3 - y2 + y1) / 4;
    printf("[A  B  C  D]  ==  [%f  %f  %f  %f]\n", a, b, c, d);
    *((float *) (UArray_at(pack, 0))) = a;
    *((float *) (UArray_at(pack, 1))) = b;
    *((float *) (UArray_at(pack, 2))) = c;
    *((float *) (UArray_at(pack, 3))) = d;
    return pack;
}

signed quanthelp(float num) 
{
    if(fabs(num) > 0.3) {
        num = ((num > 0) - (num < 0)) * 3;
    }
    num = round((num * 104) - 0.5);
    return num;
}


UArray_T bitize(UArray_T pack) 
{
    float a = *((float *) (UArray_at(pack, 0)));
    unsigned rep_a = round(a * 63);
    *((unsigned *) (UArray_at(pack, 0))) = rep_a;
    *((signed *) UArray_at(pack, 1)) = quanthelp(*((float *) (UArray_at(pack, 1))));
    *((signed *) UArray_at(pack, 2)) = 
        quanthelp(*((float *) (UArray_at(pack, 2))));
    *((signed *) UArray_at(pack, 3)) = 
        quanthelp(*((float *) (UArray_at(pack, 3))));
    return pack;
}
