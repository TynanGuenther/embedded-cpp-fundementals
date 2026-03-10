#include <array>
#include <cstddef>
#include <cstring>

template<typename T, size_t N>
class ResourceBuffer {
    public:

	bool write(size_t index, const T& val) {
	    if(index >= N) return false;
	    data_[index] = val;
	    return true;
	}
	bool read(size_t index, T& out) const {
	    if (index >= N) return false;
	    out = data_[index];
	    return true;
	}

	static constexpr size_t capacity() { return N; }

	ResourceBuffer(const ResourceBuffer& other) = default;

	ResourceBuffer& operator=(const ResourceBuffer& other) = default;

	ResourceBuffer(ResourceBuffer&& other) noexcept = default;

	ResourceBuffer& operator=(ResourceBuffer&& other) noexcept = default;

	~ResourceBuffer() = default;

    private:
	    std::array<T, N> data_{};
};
