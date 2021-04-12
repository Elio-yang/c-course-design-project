/* A generic sort program : a simple implementation of qsort in <stdlib.h>
 * tools/quick_sort.c
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/12
 */

#include "quick_sort.h"


void _qsort(void* v, int size, int left, int right,
            int (*cmp)(const void*, const void*))
{
        void *vt, *v3;
        int i, last, mid = (left + right) / 2;
        if (left >= right)
                return;
        void* vl = (char*)(v + (left * size));
        void* vr = (char*)(v + (mid * size));
        swap(vl, vr, size);
        last = left;
        for (i = left + 1; i <= right; i++) {
                vt = (char*)(v + (i * size));
                if ((*cmp)(vl, vt) > 0) {
                        ++last;
                        v3 = (char*)(v + (last * size));
                        swap(vt, v3, size);
                }
        }
        v3 = (char*)(v + (last * size));
        swap(vl, v3, size);
        _qsort(v, size, left, last - 1, cmp);
        _qsort(v, size, last + 1, right, cmp);
}

/*just use it like 'qsort' in <stdlib.h>*/
void sort(void* _base, size_t _nmemb, size_t _size, int (*_cmp)(const void*, const void*)){
        _qsort(_base, _size, 0, _nmemb - 1, _cmp);
}