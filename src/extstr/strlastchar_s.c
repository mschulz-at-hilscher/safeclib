/*------------------------------------------------------------------
 * strlastchar_s.c
 *
 * November 2008, Bo Berry
 *
 * Copyright (c) 2008-2011 by Cisco Systems, Inc
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *------------------------------------------------------------------
 */

#ifdef FOR_DOXYGEN
#include "safe_str_lib.h"
#else
#include "safeclib_private.h"
#endif

/**
 * @def strlastchar_s(dest,dmax,c,lastp)
 * @brief
 *    Returns a pointer to the last occurrence of character c in
 *    dest.  The scanning stops at null or after dmax
 *    characters.
 *
 * @remark EXTENSION TO
 *    ISO/IEC TR 24731, Programming languages, environments
 *    and system software interfaces, Extensions to the C Library,
 *    Part I: Bounds-checking interfaces
 *
 * @param[in]   dest  pointer to string to compare against
 * @param[in]   dmax  restricted maximum length of string
 * @param[in]   c     character to locate
 * @param[out]  lastp returned pointer to last occurrence of c
 *
 * @pre  dest and lastp shall not be a null pointer.
 * @pre  dmax shall not be 0
 * @pre  dmax shall not be greater than RSIZE_MAX_STR and size of dest
 *
 * @return  pointer to last occurence of c, NULL if not found
 * @retval  EOK         when pointer to last occurrence is returned
 * @retval  ESNULLP     when dst/first is NULL pointer
 * @retval  ESZEROL     when dmax = 0
 * @retval  ESLEMAX     when dmax > RSIZE_MAX_STR
 *
 * @see
 *    strfirstchar_s(), strfirstdiff_s(), strfirstsame_s(),
 *    strlastdiff_s(), strlastsame_s()
 *
 */
EXPORT errno_t
_strlastchar_s_chk(char *dest, rsize_t dmax, char c, char **lastp,
                   const size_t destbos)
{
    CHK_SRC_NULL("strlastchar_s", lastp)
    *lastp = NULL;

    CHK_DEST_NULL("strlastchar_s")
    CHK_DMAX_ZERO("strlastchar_s")
    if (destbos == BOS_UNKNOWN) {
        CHK_DMAX_MAX("strlastchar_s", RSIZE_MAX_STR)
        BND_CHK_PTR_BOUNDS(dest, dmax);
    } else {
        CHK_DEST_OVR("strlastchar_s", destbos)
    }

    while (*dest && dmax) {

        if (*dest == c) {
            *lastp = dest;
        }

        dest++;
        dmax--;
    }

    if (*lastp == NULL) {
        return (ESNOTFND);
    } else {
        return (EOK);
    }
}
