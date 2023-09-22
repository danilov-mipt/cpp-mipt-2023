#include <ctime>
#include <cstdlib>
#include <iostream>
#include "catch.hpp"
#include "Vector.hpp"
// MergeSort depends on Vector
#include "MergeSort.hpp"

bool comp(uint64_t left, uint64_t right) {
  return (left > right);
}

void BubbleSort(Vector v, bool (*comp)(uint64_t, uint64_t)) {
  for (size_t i = 0; i < v.size - 1; ++i) {
    for (size_t j = i + 1; j < v.size; ++j) {
      if ( comp(v[i], v[j]) ){
        Swap(&(v[i]), &(v[j]));
      }
    }
  }
}

TEST_CASE("Filling with 10 random numbers from 1 to 10e4, comparing with BubbleSort") {
  std::srand(std::time(nullptr));

  Vector v = CreateVector();
  Vector v1 = CreateVector();
  for (size_t i = 0; i < 10; ++i) {
    v.PushBack( 1 + std::rand() / ((RAND_MAX + 1u) / 10000) );
    v1.PushBack(v[i]);
  } 

  BubbleSort(v, comp);
  MergeSort(v1, comp);

  for (size_t i = 0; i < 10; ++i) {
    REQUIRE( v[i] == v1[i] );
  }

  v.DeleteVector();
  v1.DeleteVector();
}

TEST_CASE("Filling with 10e4 random numbers from 1 to 10e4, comparing with BubbleSort") {
  std::srand(std::time(nullptr));

  Vector v = CreateVector();
  Vector v1 = CreateVector();
  for (size_t i = 0; i < 10000; ++i) {
    v.PushBack( 1 + std::rand() / ((RAND_MAX + 1u) / 10000) );
    v1.PushBack(v[i]);
  } 

  BubbleSort(v, comp);
  MergeSort(v1, comp);

  for (size_t i = 0; i < 10000; ++i) {
    REQUIRE( v[i] == v1[i] );
  }

  v.DeleteVector();
  v1.DeleteVector();
}


void shuf(Vector v){
  std::srand(std::time(nullptr));
  // Fisher–Yates shuffle
  for (size_t i = 0 ; i < v.size - 1; ++i) {
    size_t j = std::rand() / ((RAND_MAX + 1u) / v.size);
    j = j % v.size; // for index safety;
    Swap(&(v[i]), &(v[j]));
  }
}

TEST_CASE("Filling two vectors with 10e4 natural numbers from 1 to 10e4, shuffling one with Fisher–Yates shuffle, then sorting. Comparing with untouched one.") {

  std::srand(std::time(nullptr));

  Vector v = CreateVector();
  Vector v1 = CreateVector();

  for (size_t i = 0; i < 10000; ++i) {
    v.PushBack(1 + i);
    v1.PushBack(v[i]);
  } 

  MergeSort(v, comp);

  for (size_t i = 0; i < 10000; ++i) {
    REQUIRE( v[i] == v1[i] );
  }

  v.DeleteVector();
  v1.DeleteVector();
}
