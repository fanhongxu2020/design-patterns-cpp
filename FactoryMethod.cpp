#include <iostream>

class Robot {
public:
    virtual ~Robot() {}
    virtual void work() = 0;
};

class FloorMoppingRobot : public Robot {
public:    
    void work() override {
        std::cout << "I'm a FloorMoppingRobot, I'm mopping the floor." << std::endl;
    }
};

class DishesWashingRobot : public Robot {
public:
    void work() override {
        std::cout << "I'm a DishesWashingRobot, I'm washing the dishes." << std::endl;
    }
};

class RobotFactory {
public:
    virtual ~RobotFactory() {}
    virtual Robot* Product() const = 0;
    void TestProduction() const {
        auto robot = Product();
        robot->work();
        delete robot;
    }
};

class FloorMoppingRobotFactory : public RobotFactory {
public:
    Robot* Product() const override {
        auto robot = new FloorMoppingRobot();
        return robot;
    }
};

class DishesWashingRobotFactory : public RobotFactory {
public:
    Robot* Product() const override {
        auto robot = new DishesWashingRobot();
        return robot;
    }
};

void FactoryTest(const RobotFactory& factory) {
    factory.TestProduction();
}

int main() {
    auto factory1 = new FloorMoppingRobotFactory();
    auto factory2 = new DishesWashingRobotFactory();

    FactoryTest(*factory1);
    FactoryTest(*factory2);
}
