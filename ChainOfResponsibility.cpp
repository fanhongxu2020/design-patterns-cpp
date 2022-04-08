#include <iostream>
#include <string_view>
#include <memory>

class Middleware {
public:
  using Ptr = std::shared_ptr<Middleware>;

  Ptr LinkWith(Ptr next) {
    if (next) {
      next_ = next;
    }
    return next;
  }
  virtual bool Order(std::string_view name) = 0;
protected:
  bool TurnNext(std::string_view name) {
    if (next_ == nullptr) {
      return true;
    }
    return next_->Order(name);
  }
  Ptr next_;
};

class Waiter : public Middleware {
public:
  using Ptr = std::shared_ptr<Waiter>;

  bool Order(std::string_view name) {
    std::cout << "client order : " << name << std::endl;
    return TurnNext(name);
  }
};

class Cook : public Middleware {
public:
  using Ptr = std::shared_ptr<Cook>;

  bool Order(std::string_view name) {
    std::cout << "order : " << name << " cooked" << std::endl;
    return TurnNext(name);
  }
};

class Busboy : public Middleware {
public:
  using Ptr = std::shared_ptr<Busboy>;

  bool Order(std::string_view name) {
    std::cout << "clean table" << std::endl;
    return TurnNext(name);
  }
};

class Restaurant {
public:
  Restaurant() {
    waiter_ = std::make_shared<Waiter>();
    cook_ = std::make_shared<Cook>();
    busboy_ = std::make_shared<Busboy>();

    waiter_->LinkWith(cook_)->LinkWith(busboy_);
  }
  bool work() {
    return waiter_->Order("pizza");
  }

private:
  Waiter::Ptr waiter_;
  Cook::Ptr cook_;
  Busboy::Ptr busboy_;
};

int main() {
  Restaurant ra;
  ra.work();

  return 1;
}
