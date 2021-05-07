/*
 * A generic sort program : a simple implementation of qsort in <stdlib.h>
 * tools/quick_sort.h
 * @author Elio Yang
 * @email  jluelioyang2001@gamil.com
 * @date 2021/4/12
 */

#ifndef CDESIGN_QUICK_SORT_H
#define CDESIGN_QUICK_SORT_H

#include <stdio.h>
#include <string.h>
static void swap(void* v1, void* v2, int size)
{
        char buf[size];
        memcpy(buf, v1, size);
        memcpy(v1, v2, size);
        memcpy(v2, buf, size);
}

void _qsort(void* v, int size, int left, int right,int (*cmp)(const void*, const void*));
/*just use it like 'qsort' in <stdlib.h>*/
void sort(void* _base, size_t _nmemb, size_t _size, int (*_cmp)(const void*, const void*));
#endif //CDESIGN_QUICK_SORT_H
