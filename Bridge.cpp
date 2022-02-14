#include <iostream>

class KitchenWashing {
public:
  KitchenWashing(){}
  virtual ~KitchenWashing() {}
  virtual void Washing() = 0;
};

class CleanRobot {
public:
  CleanRobot(KitchenWashing* function) : dishes_washing_function_(function) {}
  ~CleanRobot() {
    if (dishes_washing_function_) {
      delete dishes_washing_function_;
      dishes_washing_function_ = nullptr;
    }
  }
  virtual void FloorMopping() = 0;
protected:
  KitchenWashing* dishes_washing_function_ = nullptr;
};

class FloorMoppingRobot : public CleanRobot {
public:
  enum FloorType{
    Wooden,
    Ceramic,
  };

  FloorMoppingRobot(KitchenWashing* function) : CleanRobot(function) {}
  void FloorMopping() {
    std::cout << "Starting mop floor, type:" << (floor_type_ == Wooden ? "wooden" : "ceramic") << std::endl;
  }
  void WashDishes() {
    if (dishes_washing_function_) {
      dishes_washing_function_->Washing();
    }
  }
  void SetFloorType(FloorType type) {
    floor_type_ = type;
  }
private:
  FloorType floor_type_ = Wooden;
};


class DishesWashing : public KitchenWashing {
public:
  DishesWashing() {}
  ~DishesWashing() {
  }
  void Washing() {
    std::cout << "Starting wash dishes" << std::endl;
  }
};

int main() {
  auto robot = new FloorMoppingRobot(new DishesWashing());
  robot->SetFloorType(FloorMoppingRobot::Ceramic);
  robot->FloorMopping();
  robot->WashDishes();

  delete robot;

  return 0;
}
