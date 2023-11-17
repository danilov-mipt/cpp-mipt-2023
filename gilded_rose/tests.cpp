#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "gilded_rose.hpp"

TEST_CASE("Test on Quality bounds (0..50)") {
  std::cout << "begin Test on Quality bounds (0..50)\n------\n";
  GildedRose gr;
  
  gr.AddItem("Sulfuras", 50, 30);              // quality is constant
  gr.AddItem("Cheese", 3, 1);
  gr.AddItem("Aged Brie", 3, 1);              // quality gets better
  gr.AddItem("Backstage Pass", 3, 1);
  gr.AddItem("Conjured Cheese", 3, 1);
  gr.AddItem("Conjured Aged Brie", 3, 1);     // quality gets better
  gr.AddItem("Conjured Sulfuras", 3, 38);      // quality is constant
  gr.AddItem("Conjured Backstage Pass", 3, 1);
  
  auto items = gr.GetItems();
  std::cout << "Initial parameters:\n";
  for (auto item : items) {
    item->Print();
  }

  for (int32_t i = 0; i < 100; ++i) {
    gr.UpdateQuality();
  }
  
  std::cout << "------\nAfter 100 iterations:\n";
  for (auto item : items) {
    item->Print();
  }

  std::vector<int32_t> expected_qualities = {30, 0, 50, 0, 0, 50, 38, 0};

  for (size_t i = 0; i < 8; ++i) {
    REQUIRE( items[i]->quality == expected_qualities[i] );
  }

  std::cout << "------\nend Test on Quality bounds (0..50)\n";
}

TEST_CASE("Test on Item quality drop + expiry") {
  std::cout << "begin Test on Item quality drop + expiry\n------\n";
  GildedRose gr;
  
  gr.AddItem("Some Item", 3, 30);
  
  auto items = gr.GetItems();
  std::cout << "Initial parameters:\n";
  for (auto item : items) {
    item->Print();
  }

  const std::vector<int32_t> expected_qualities = {29, 28, 27, 25, 23, 21, 19, 17, 15, 13, 11};
  for (int32_t i = 0; i < 8; ++i) {
    gr.UpdateQuality();
    std::cout << "------\nAfter  " << i + 1 << " iterations:\n";
    for (auto item : items) {
      item->Print();
    }

    REQUIRE( items[0]->quality  ==  expected_qualities[i]);

  }
  std::cout << "------\nend Test on Item quality drop + expiry\n";
}

TEST_CASE("Test on Conjured items quality drop + expiry") {
  std::cout << "begin Test on Conjured items quality drop + expiry\n------\n";
  GildedRose gr;
  
  gr.AddItem("Conjured Cheese", 3, 30);
  
  auto items = gr.GetItems();
  std::cout << "Initial parameters:\n";
  for (auto item : items) {
    item->Print();
  }

  const std::vector<int32_t> expected_qualities = {28, 26, 24, 20, 16, 12, 8, 4, 0, 0, 0};
  for (int32_t i = 0; i < 8; ++i) {
    gr.UpdateQuality();
    std::cout << "------\nAfter  " << i + 1 << " iterations:\n";
    for (auto item : items) {
      item->Print();
    }

    REQUIRE( items[0]->quality  ==  expected_qualities[i]);

  }
  std::cout << "------\nend Test on Conjured items quality drop + expiry\n";
}


TEST_CASE("Test on Updating Sell In dates") {
  std::cout << "begin Test on Updating Sell In dates\n------\n";
  GildedRose gr;
  
  gr.AddItem("Sulfuras", 50, 30);              // sell_in is constant
  gr.AddItem("Cheese", 3, 1);
  gr.AddItem("Aged Brie", 3, 1);
  gr.AddItem("Backstage Pass", 3, 1);
  gr.AddItem("Conjured Cheese", 3, 1);
  gr.AddItem("Conjured Aged Brie", 3, 1);
  gr.AddItem("Conjured Sulfuras", 3, 38);      // sell_in is constant
  gr.AddItem("Conjured Backstage Pass", 3, 1);
  
  auto items = gr.GetItems();
  std::cout << "Initial parameters:\n";
  for (auto item : items) {
    item->Print();
  }

  for (int32_t i = 0; i < 30; ++i) {
    gr.UpdateQuality();
  }
  
  std::cout << "------\nAfter 30 iterations:\n";
  for (auto item : items) {
    item->Print();
  }

  const std::vector<int32_t> expected_dates = {50, -27, -27, -27, -27, -27, 3, -27};

  for (size_t i = 0; i < 8; ++i) {
    REQUIRE( items[i]->sell_in == expected_dates[i] );
  }

  std::cout << "------\nend Test on Updating Sell In dates\n";
}

TEST_CASE("Test on Backstage Pass Dynamics") {
  std::cout << "begin Test on Backstage Pass Dynamics\n------\n";
  GildedRose gr;
  
  gr.AddItem("Backstage Pass", 12, 0);
  gr.AddItem("Conjured Backstage Pass", 12, 0);
  
  auto items = gr.GetItems();
  std::cout << "Initial parameters:\n";
  for (auto item : items) {
    item->Print();
  }

  const std::vector<int32_t> expected_qualities = {0, 0, 2, 4, 6, 8, 10, 13, 16, 19, 22, 25, 0, 0, 0};
  for (int32_t i = 0; i < 15; ++i) {
    gr.UpdateQuality();
    std::cout << "------\nAfter  " << i + 1 << " iterations:\n";
    for (auto item : items) {
      item->Print();
    }

    REQUIRE( items[0]->quality  ==  expected_qualities[i]);
    REQUIRE( items[1]->quality  ==  expected_qualities[i]);

  }
  std::cout << "------\nend Test on Backstage Pass Dynamics\n";
}


