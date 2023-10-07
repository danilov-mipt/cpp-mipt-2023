#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "TMergeSort.hpp"


/* BubbleSort Template */
template <class TRAI,
          class TCompare = std::less<
            typename std::iterator_traits<TRAI>::value_type
            >
          >
void BubbleSort(TRAI _begin, TRAI _end, TCompare cmp = {}) {
  bool is_change = true;
  while (is_change) {
    is_change = false;
    for (auto i = _begin; i!=_end-1; ++i) {
      if (cmp(*(i+1),*i)) {
        IteratorSwap(i, (i+1));
        is_change = true;
      }
    }
  }
}

/* Fisher-Yates shuffle template */
template <class TRAI>
void shuf(TRAI _begin, TRAI _end){
  std::srand(std::time(nullptr));
  auto v_size = std::distance(_begin, _end);
  // Fisher–Yates shuffle
  for (size_t i = 0 ; i < v_size - 1; ++i) {
    size_t j = std::rand() / ((RAND_MAX + 1u) / v_size);
    j = j % v_size; // for index safety;
    IteratorSwap(_begin + i, _begin + j);
  }
}

TEST_CASE("<int64_t> Filling with 2 numbers (0, 1) and (1, 0) to test the size == 2 case") {
  std::vector<int64_t> v;
  std::vector<int64_t> v1;
  for (size_t i = 0; i < 2; ++i) {
    v.push_back(i);
    v1.push_back(v[i]);
  } 

  BubbleSort(v.begin(), v.end());
  MergeSort(v1.begin(), v1.end());

  for (size_t i = 0; i < 2; ++i) {
    REQUIRE( v[i] == v1[i] );
  }

  for (size_t i = 0; i < 2; ++i) {
    v[i] = 1 - i;
    v1[i] = v[i];
  }

  for (size_t i = 0; i < 2; ++i) {
    REQUIRE( v[i] == v1[i] );
  }
}


TEST_CASE("<int64_t> Filling with 10 random numbers from 1 to 10e4, comparing with BubbleSort") {
  std::srand(std::time(nullptr));

  std::vector<int64_t> v;
  std::vector<int64_t> v1;
  for (size_t i = 0; i < 10; ++i) {
    v.push_back( 1 + std::rand() / ((RAND_MAX + 1u) / 10000) );
    v1.push_back(v[i]);
  } 

  BubbleSort(v.begin(), v.end());
  MergeSort(v1.begin(), v1.end());

  for (size_t i = 0; i < 10; ++i) {
    REQUIRE( v[i] == v1[i] );
  }
}

TEST_CASE("<int64_t> Filling with 10e4 random numbers from 1 to 10e4, comparing with BubbleSort") {
  std::srand(std::time(nullptr));

  std::vector<int64_t> v;
  std::vector<int64_t> v1;
  for (size_t i = 0; i < 10000; ++i) {
    v.push_back( 1 + std::rand() / ((RAND_MAX + 1u) / 10000) );
    v1.push_back(v[i]);
  } 

  BubbleSort(v.begin(), v.end());
  MergeSort(v1.begin(), v1.end());

  for (size_t i = 0; i < 10000; ++i) {
    REQUIRE( v[i] == v1[i] );
  }
}

TEST_CASE("<int64_t> Filling two vectors with 10e4 natural numbers from 1 to 10e4, shuffling one with Fisher–Yates shuffle, then sorting. Comparing with untouched one.") {

  std::srand(std::time(nullptr));

  std::vector<int64_t> v;
  std::vector<int64_t> v1;

  for (size_t i = 0; i < 10000; ++i) {
    v.push_back(1 + i);
    v1.push_back(v[i]);
  } 

  shuf(v.begin(), v.end());
  MergeSort(v.begin(), v.end());

  for (size_t i = 0; i < 10000; ++i) {
    REQUIRE( v[i] == v1[i] );
  }
}


TEST_CASE("<double> Filling with 10 random numbers from -50 to 49.99, comparing with BubbleSort") {
  std::srand(std::time(nullptr));

  std::vector<double> v;
  std::vector<double> v1;
  for (size_t i = 0; i < 10; ++i) {

    int64_t n = std::rand() / ((RAND_MAX + 1u) / 10000) - 50; 
    double m = (double)(n) / 100;
    
    v.push_back(m);
    v1.push_back(v[i]);
  } 

  BubbleSort(v.begin(), v.end());
  MergeSort(v1.begin(), v1.end());

  for (size_t i = 0; i < 10; ++i) {
    REQUIRE( v[i] == v1[i] );
  }
}


TEST_CASE("<double> Filling two vectors with 10e4 natural numbers from -50.00 to 50.00, shuffling one with Fisher–Yates shuffle, then sorting. Comparing with untouched one.") {

  std::srand(std::time(nullptr));

  std::vector<double> v;
  std::vector<double> v1;

  for (int64_t i = 0; i < 10000; ++i) {
    double m = (double)(i - 5000) / 100;

    v.push_back(m);
    v1.push_back(v[i]);
  } 

  shuf(v.begin(), v.end());
  MergeSort(v.begin(), v.end());

  for (size_t i = 0; i < 10000; ++i) {
    REQUIRE( v[i] == v1[i] );
  }
}

struct MyStructure {
  int64_t f;
};

TEST_CASE("<MyStructure> Filling with 10 MyStructure structures with random numbers from 1 to 10e4, comparing with BubbleSort\n. Also testing the custom compare function definition.") {
  std::srand(std::time(nullptr));

  std::vector<MyStructure> v;
  std::vector<MyStructure> v1;
  for (size_t i = 0; i < 10; ++i) {
    MyStructure s;
    s.f = 1 + std::rand() / ((RAND_MAX + 1u) / 10000);
    v.push_back(s);
    v1.push_back(v[i]);
  }
  auto MyComp = [](MyStructure a, MyStructure b) { return a.f < b.f; };
  BubbleSort(v.begin(), v.end(), MyComp);
  MergeSort(v1.begin(), v1.end(), MyComp);

  for (size_t i = 0; i < 10; ++i) {
    REQUIRE( v[i].f == v1[i].f );
  }
}
