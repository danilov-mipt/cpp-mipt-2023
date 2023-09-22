using v_type = uint64_t;
const size_t InitialVectorAlloc = 8;

struct Vector {
  v_type* data;
  size_t size, reserved;

  void DeleteVector() {
    delete[] data;
    size = 0;
    reserved = 0;
  }

  void Realloc_() {
    size_t new_reserve = reserved * 2;
    v_type* new_data = new v_type[new_reserve];
    for (size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    reserved = new_reserve;
  }

  void PushBack(v_type value) {
    if (size + 1 > reserved) {
      Realloc_();
    }
    data[size] = value;
    ++size;
  }

  void PopBack() {
    --size;
  }

  v_type& operator [](size_t index) { return data[index]; }
//      ^ note this &. this is because data[index] needs to be v_type&
//        because otherwise it will not be an lvalue, but v_type.
};

Vector CreateVector() {
  Vector v;
  v.data = new v_type[InitialVectorAlloc];
  v.reserved = InitialVectorAlloc;
  v.size = 0;
  return v;
}

