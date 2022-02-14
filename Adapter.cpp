#include <iostream>

class ChineseSocket {
public:
    int GetVoltage() const {
        return volgage_;
    }
private:
    int volgage_ = 220;
};

class AmericanSocket {
public:
    int GetVoltage() const {
        return volgage_;
    }
private:
    int volgage_ = 120;
};

class ChineseTv {
public:
    bool PowerOn(ChineseSocket& socket) {
        if (socket.GetVoltage() == nominal_voltage_) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    int nominal_voltage_ = 220;
};

class Transformer : public ChineseSocket {
public:
    Transformer(AmericanSocket socket) : socket_(socket) {}
    int GetVoltage() const {
        return Transform();
    }
private:
    int Transform() const {
        return 120;
    }
private:
    AmericanSocket socket_;
};

int main() {
    ChineseSocket chinese_socket;
    AmericanSocket american_socket;
    ChineseTv chinese_tv;
    Transformer transformer(american_socket);

    if (chinese_tv.PowerOn(chinese_socket)) {
        std::cout << "chinese tv power on by chinese socket" << std::endl;
    }
    if (chinese_tv.PowerOn(transformer)) {
        std::cout << "chinese tv power on by transformer on american socket" << std::endl;
    }
}
