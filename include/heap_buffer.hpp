#include <cstddef>
#include <cstdint>
#include <cstring>

template<typename T, size_t N>
class HeapBuffer {
    public:
	explicit HeapBuffer(T type, size_t size)
	    : data_(new T[size]), size_(size) {}

	~HeapBuffer() {
	    delete[] data_;
	}

	HeapBuffer(const HeapBuffer& other)
	    : data_(new T[other.size_]), size_(other.size_) {
		std::memcpy(data_, other.data_, size_);
	}	

	HeapBuffer& operator=(const HeapBuffer& other) {
	    if (this == &other) return *this;

	    delete[] data_;
	    data_ = new T[other.size_];
	    size_ = other.size_;
	    std::memcpy(data_, other.data_, size_);
	    return *this;
	}

	HeapBuffer(HeapBuffer&& other) noexcept
	    : data_(other.data_), size_(other.size_) {
		other.data_ = nullptr;
		other.size_ = 0;
	    }

	HeapBuffer& operator=(HeapBuffer&& other) noexcept {
	    if (this == &other) return *this;

	    delete[] data_;
	    data_ = other.data_;
	    size_ = other.size_;
	    other.data_ = nullptr;
	    other.size_ = 0;
	    return *this;
	}
    private:
	    T* data_;
	    size_t size_;
};

