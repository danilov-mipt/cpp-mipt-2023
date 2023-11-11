#include <iostream>
#include <string>
#include <vector>

class Item {
public:
  std::string name;
  int32_t quality;
  int32_t sell_in;
protected:
  /* quality_decrement is a retrofit for Conjured modifier */
  virtual int32_t quality_decrement() const { return 1; }
  virtual void DecrementSellIn() {
    sell_in -= 1;
  }
  virtual void UpdateItemQuality() {
    if (sell_in >= 0) {
      quality -= quality_decrement();
    } else {
      /* Once the sell by date has passed, Quality degrades twice as fast */
      quality -= 2 * quality_decrement();
    }
  }
public:
  Item(const std::string& name_, int32_t sell_in_, int32_t init_qual_) {
    name = name_;
    sell_in = sell_in_;
    quality = init_qual_;
  }
  
  virtual void UpdateQuality() {
  /* At the end of each day our system lowers both
   * quality and sell_in for every item
   * Note that I separated these two updates so they won't interfere
   * with each other in inheriting classes.*/
    DecrementSellIn();
    UpdateItemQuality();
  }

  virtual void Print() {
    std::cout << name << " [q=" << quality << ", s=" << sell_in << "]\n";
  }
};

class BoundQualityItem : public Item {
  using Item::Item;
protected:
  void FixLimits() {
    if (quality < 0) {
      quality = 0;
    }
    if (quality > 50) {
      quality = 50;
    }
  }
public:
  virtual void UpdateQuality() override {
    DecrementSellIn();
    UpdateItemQuality();
    FixLimits();
  }
};

/*
 * I made Sulfuras bound (to fix its limits, even though it doesnt
 * change quality) to more strictly follow the rule:
 * The Quality of an item is never more than 50
 */
class Sulfuras : public BoundQualityItem{
protected:
  using BoundQualityItem::BoundQualityItem;
  /* Sulfuras never have to be sold */
  virtual void DecrementSellIn() override {}
  virtual void UpdateItemQuality() override {}
};

class AgedBrie : public BoundQualityItem {
public:
  using BoundQualityItem::BoundQualityItem;
  virtual void UpdateItemQuality() override {
    quality += 1;
  }
};

class BackstagePass : public BoundQualityItem{
  using BoundQualityItem::BoundQualityItem; 
protected:
  virtual void UpdateItemQuality() override {
    /* note that we operate on the updated
     * sell_in value */
    if (sell_in < 0) {
      quality = 0;
    }
    else if (sell_in < 5) {
      quality += 3;
    }
    else if (sell_in < 10) {
      quality += 2;
    }
  }
};

/* Conjured modifier is a template */
template <typename T>
class Conjured : public T {
  using T::T;
protected:
  virtual int32_t quality_decrement() const override { return 2; }
};

/* Shop class */
class GildedRose {
private:
  std::vector<Item*> items;
  
  Item * MakeItem(const std::string& name,
                  int32_t sell_in,
                  int32_t initial_quality) {
    Item * new_item = nullptr;

    if (name == "Conjured Sulfuras") {
      new_item = new Conjured<Sulfuras>(name, sell_in, initial_quality);
    }
    else if(name == "Conjured Aged Brie"){
      new_item = new Conjured<AgedBrie>(name, sell_in, initial_quality);
    }
    else if(name == "Conjured Backstage Pass"){
      new_item = new Conjured<BackstagePass>(name, sell_in, initial_quality);
    }
    else if(name.substr(0, 8) == "Conjured"){
      new_item = new Conjured<BoundQualityItem>(name, sell_in, initial_quality);
    }
    else if(name == "Backstage Pass"){
      new_item = new BackstagePass(name, sell_in, initial_quality);
    }
    else if (name == "Aged Brie") {
      new_item = new AgedBrie(name, sell_in, initial_quality);
    }
    else if (name == "Sulfuras"){
      new_item = new Sulfuras(name, sell_in, initial_quality);
    }
    else {
      new_item = new BoundQualityItem(name, sell_in, initial_quality);
    } 
    return new_item;
  }

public:
  void UpdateQuality() {
    for (auto item : items) {
      item->UpdateQuality();
    }
  }

  void AddItem(const std::string& name,
               int32_t sell_in,
               int32_t initial_quality) {
    Item * new_item = MakeItem(name, sell_in, initial_quality);
    if (new_item != nullptr) {
      items.push_back(new_item);
    }
  }

  void Print() {
    for (auto item : items) {
      item->Print();
    }
  }
};
