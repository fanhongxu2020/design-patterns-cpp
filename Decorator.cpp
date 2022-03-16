#include <iostream>
#include <string>
#include <memory>

static std::string static_file_data;

class DataSource {
public:
    virtual std::string Read() = 0;
    virtual void Write(const std::string & data) = 0;
};

class FileDataSource : public DataSource {
public:
    std::string Read() {
        return static_file_data;
    }
    void Write(const std::string & data) {
        static_file_data = data;
    }
};

class DataSourceDecorator : public DataSource {
public:
    DataSourceDecorator(const std::shared_ptr<DataSource> & source) : data_source_(source) {}
    std::string Read() {
        data_source_->Read();
    }
    void Write(const std::string & data) {
        data_source_->Write(data);
    }
protected:
    std::shared_ptr<DataSource> data_source_;
};

class EncryptionDecorator : public DataSourceDecorator {
public:
    EncryptionDecorator(const std::shared_ptr<DataSource> & source) : DataSourceDecorator(source) {}
    std::string Read() {
        return Decode(data_source_->Read());
    }
    void Write(const std::string & data) {
        data_source_->Write(Encode(data));
    }
private:
    std::string Encode(const std::string & data) {
        return std::string("encrypted data");
    }
    std::string Decode(const std::string & data) {
        return std::string("hello world");
    }
};

int main() {
    auto encoded = std::make_shared<EncryptionDecorator>(std::make_shared<FileDataSource>());

    encoded->Write("hello world");
    std::cout << "encoded file data : " << static_file_data.data() << std::endl;

    auto decoded = encoded->Read();
    std::cout << "decoded file data : " << decoded.data() << std::endl;
    return 0;
}
