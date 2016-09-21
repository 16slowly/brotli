/* Copyright 2016 Google Inc. All Rights Reserved.
   Author: vanickulin@google.com (Ivan Nikulin)

   Distributed under MIT license.
   See file LICENSE for detail or copy at https://opensource.org/licenses/MIT
*/

/* API for reading distances from *.dist file. */

#include <cassert>
#include <cstdio>

#ifndef BROTLI_RESEARCH_READ_DIST_H_
#define BROTLI_RESEARCH_READ_DIST_H_

/* Reads backwards reference from .dist file. Sets all missing fields to -1.
   Returns false when EOF is met or input is corrupt. */
bool ReadBackwardReference(FILE* fin, int* copy, int* pos, int* dist) {
  int c = getc(fin);
  if (c == EOF) return false;
  if (c == 0) {
    assert(fread(copy, sizeof(int), 1, fin) == 1);
    if ((c = getc(fin)) != 1) {
      ungetc(c, fin);
      *pos = *dist = -1;
    } else {
      assert(fread(pos, sizeof(int), 1, fin) == 1);
      assert(fread(dist, sizeof(int), 1, fin) == 1);
    }
  } else if (c != 1) {
    return false;
  } else {
    assert(fread(pos, sizeof(int), 1, fin) == 1);
    assert(fread(dist, sizeof(int), 1, fin) == 1);
    *copy = -1;
  }
  return true;
}

#endif  /* BROTLI_RESEARCH_READ_DIST_H_ */
