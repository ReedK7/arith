



#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "compress40.h"
#include "uarray2b.h"
#include "a2blocked.h"
#include "a2methods.h"
#include "uarray.h"
#include "assert.h"
#include "pnm.h"
#include "pnmrdr.h"
#include "uarray2.h"
#include "arith40.h"


UArray_T quantize(UArray_T pack);
UArray_T discrete_cosine_transform(UArray_T pack);
signed quanthelp(float num);
UArray_T bitize(UArray_T pack);
