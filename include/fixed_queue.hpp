#include <array>
#include <cstddef>
#include <cstdint>

template<typename T, std::size_t N>
class FixedQueue {
    public:
	bool push(const T& val) {
	    if(full()) return false;
	    data_[head_] = val;
	    head_ = (head_ + 1) % N;
	    size_++;
	    return true;
	}

	bool pop(T& out) {
	    if (empty()) return false;
	    out = data_[tail_];
	    tail_ = (tail_ + 1) % N;
	    size_--;
	    return true;
	}

	bool full() const { return size_ == N; }
	bool empty() const { return size_ == 0; }
	constexpr size_t capacity() const { return N; }
	static constexpr size_t capacity_v = N;

    private:
	std::array<T, N> data_{};
	std::size_t head_ = 0;
	std::size_t tail_ = 0;
	std::size_t size_ = 0;
};

