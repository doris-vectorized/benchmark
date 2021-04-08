#pragma once
#include <fmt/format.h>

#include <cstring>

namespace DB {
class BufferWritable {
public:

    virtual void write(const char* data, int len) = 0;

    template <typename T>
    void write_number(T data) {
        fmt::memory_buffer buffer;
        fmt::format_to(buffer, "{}", data);
        buffer.push_back('\0');
        write(buffer.data(), buffer.size());
    }

    int count() const {
        return _writer_counter;
    }
protected:
    void update_writer_counter(int delta) {
        _writer_counter += delta;
    }
private:
    int _writer_counter = 0;
};

template <class T>
class VectorBufferWriter: public BufferWritable {
public:
    VectorBufferWriter(T & vector):_vector(vector) {}

    void write(const char* data, int len) {
        _vector.insert(data, data + len);
        update_writer_counter(len);
    }
private:
    T & _vector;
};
} // namespace DB
