void Swap(uint64_t* left, uint64_t* right) {
  uint64_t buffer = *(left);
  *(left) = *(right);
  *(right) = buffer; 
}

void MergeSort(Vector sublist, bool (*comp)(uint64_t, uint64_t)) {
  size_t size = sublist.size;
  
  if (size == 2) {
    if (comp(sublist[0], sublist[1])) {
      Swap(&(sublist[0]), &(sublist[1]));
    }
  }

  if (size > 2) { 
    size_t split = size / 2;
    
    Vector left = sublist;
    Vector right = sublist;

    size_t left_len = split, right_len = size - split;

    left.size = left_len;
    right.size = right_len;
    right.data = &(right.data[split]);

    MergeSort(left, comp);
    MergeSort(right, comp);
    
    Vector buffer = CreateVector();
    size_t i = 0, j = 0, k = 0;
    while (i < left_len && j < right_len) {
      if (comp(left[i], right[j])) {
        buffer.PushBack(right[j]);
        ++j;
      }
      else{
        buffer.PushBack(left[i]);
        ++i;
      }
      ++k;
    }
    // filling in the leftovers in the buffer
    for (; i < left_len; ++i, ++k) {
      buffer.PushBack(left[i]);
    }
    for (; j < right_len; ++j, ++k) {
      buffer.PushBack(right[j]);
    }
    // replacing subarray with buffer
    for (size_t h = 0; h < size; ++h) {
      sublist[h] = buffer[h];
    }
    
    buffer.DeleteVector();
  }
}
