#include <iostream>
#include <string>
#include <list>

class Finder {
public:
    virtual void Match(const std::string& name) = 0;
};

class File : public Finder {
public:
    File(const std::string& name) : name_(name) {}
    void Match(const std::string& name) {
        if (name_.find(name.data()) != std::string::npos) {
            std::cout << "file '" << name_.data() << "' matches." << std::endl;
        }
    }
private:
    std::string name_;
};

class Folder : public Finder {
public:
    ~Folder() {
        for (const auto& itor : component_) {
            delete itor;
        }
    }
    void Match(const std::string& name) {
        for (const auto& itor : component_) {
            if (itor) {
                itor->Match(name);
            }
        }
    }
    void Add(Finder* finder){
        component_.push_back(finder);
    }
private:
    std::list<Finder*> component_;
};

int main() {
    auto file_hello = new File("hello");
    auto file_world = new File("world");
    auto file_hello_world = new File("hello_world");

    auto folder_a = new Folder();
    auto folder_b = new Folder();

    folder_b->Add(file_hello);
    folder_b->Add(file_world);

    folder_a->Add(folder_b);
    folder_a->Add(file_hello_world);

    folder_a->Match("hello");

    return 0;
}
