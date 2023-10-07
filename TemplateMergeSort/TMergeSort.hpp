#include <iterator>

template <class TRAI,
          class TRAIElement = typename std::iterator_traits<TRAI>::value_type>
void IteratorSwap(TRAI left, TRAI right) {
  TRAIElement buffer = *(left);
  *(left) = *(right);
  *(right) = buffer; 
}

/*
 * The following is a rewrite of my MergeSort into
 * template form. The original sort was for array of int64
 * and served as a prototype for my Vector implementation sort. 
 */
template <class TRAI,
          class TRAIElement = typename std::iterator_traits<TRAI>::value_type,
          class TCompare = std::less<TRAIElement>
          >
void MergeSort(TRAI _begin, TRAI _end, TCompare cmp = {}) {

  /* according to cppreference, this counts the number of
   * hops from _begin to _end
   */
  auto size = std::distance(_begin, _end);

  if (size == 2) {
    if (cmp( *(_begin + 1), *(_begin) )) {
      IteratorSwap(_begin, _begin + 1);
    }
  }

  if (size > 2) { 
    auto split = size / 2;
    
    TRAI left = _begin;
    TRAI right = _begin + split;
    auto left_len = split, right_len = size - split;

    MergeSort(left, left + left_len, cmp);
    MergeSort(right, right + right_len, cmp);
    
    TRAIElement* buffer = new TRAIElement[size];
    size_t i = 0, j = 0, k = 0;
    while (i < left_len && j < right_len) {
      if (cmp( *(left + i) , *(right + j) )) {
        buffer[k] = *(left + i);
        ++i;
      }
      else{
        buffer[k] = *(right + j);
        ++j;
      }
      ++k;
    }
    // filling in the leftovers in the buffer
    for (; i < left_len; ++i, ++k) {
      buffer[k] = *(left + i);
    }
    for (; j < right_len; ++j, ++k) {
      buffer[k] = *(right + j);
    }
    // replacing subarray with buffer
    for (size_t h = 0; h < size; ++h) {
      *(_begin + h) = buffer[h];
    }

    delete[] buffer;
  }
}
