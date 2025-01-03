// src/ds/circular_buffer.cppm
module;   // Global module fragment

#include <cstddef>
#include <array>
#include <algorithm>
#include <expected>

export module me.ds.circular_buffer;

export namespace me::ds {

enum class circular_buffer_error {
    index_out_of_bounds,
    empty_buffer,
};

template <typename T, std::size_t Size>
    requires(Size > 0)
class circular_buffer_iterator;

template <typename T, std::size_t Size>
    requires(Size > 0)
class circular_buffer {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type &;
    using const_reference = value_type const &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using difference_type = std::ptrdiff_t;
    using iterator = circular_buffer_iterator<T, Size>;
    using const_iterator = circular_buffer_iterator<T const, Size>;

    // Default constructor
    constexpr circular_buffer() = default;

    template <typename Range, typename U = std::ranges::range_value_t<Range>>
        requires std::convertible_to<U, value_type>
    constexpr explicit circular_buffer(Range const &range)
        requires(std::ranges::size(range) <= Size)
    {
        constexpr auto range_size = std::ranges::size(range);
        std::ranges::copy_n(std::ranges::begin(range), range_size, data_.begin());
    }

    constexpr explicit circular_buffer(value_type const (&other)[Size]) {
        std::ranges::copy_n(other, Size, data_.begin());
    }

    template <typename U, size_type OtherSize>
        requires std::convertible_to<U, value_type>
    constexpr explicit circular_buffer(circular_buffer<U, OtherSize> &other)
        requires (OtherSize <= Size)
    {
        std::ranges::copy_n(other.data_.begin(), Size, data_.begin());
    }

    // Destructor
    ~circular_buffer() = default;

    circular_buffer &operator=(circular_buffer const &) = delete;

    // Disallow move operations
    circular_buffer(circular_buffer &&) noexcept = delete;
    circular_buffer &operator=(circular_buffer &&) noexcept = delete;

    // Capacity accessors
    [[nodiscard]] constexpr std::size_t size() const noexcept { return size_; }
    [[nodiscard]] constexpr bool full() const noexcept { return size_ == Size; }
    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] static std::size_t capacity() noexcept { return Size; }

    // Element accessors
    constexpr std::expected<reference, circular_buffer_error> operator[](size_type const index) {
        if (!validate_index(index)) {
            return std::unexpected(circular_buffer_error::index_out_of_bounds);
        }
        if constexpr (is_power_of_two()) {
            return data_[(head_ + index) & (Size - 1)];
        } else {
            return data_[(head_ + index) % Size];
        }
    }

    constexpr std::expected<const_reference, circular_buffer_error> operator[] (size_type const index) const {
        if (!validate_index(index)) {
            return std::unexpected(circular_buffer_error::index_out_of_bounds);
        }
        if constexpr (is_power_of_two()) {
            return data_[(head_ + index) & (Size - 1)];
        } else {
            return data_[(head_ + index) % Size];
        }
    }

    constexpr std::expected<reference, circular_buffer_error> at(size_type const index) {
        if (!validate_index(index)) {
            return std::unexpected(circular_buffer_error::index_out_of_bounds);
        }
        return data_[index];
    }

    void clear() noexcept {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

    constexpr std::expected<reference, circular_buffer_error> front() {
        if (empty()) {
            return std::unexpected(circular_buffer_error::empty_buffer);
        }
        return data_[head_];
    }

    constexpr std::expected<const_reference, circular_buffer_error> front() const {
        if (empty()) {
            return std::unexpected(circular_buffer_error::empty_buffer);
        }
        return data_[head_];
    }

    constexpr std::expected<reference, circular_buffer_error> back() {
        if (empty()) {
            return std::unexpected(circular_buffer_error::empty_buffer);
        }
        return data_[tail_];
    }

    constexpr std::expected<const_reference, circular_buffer_error> back() const {
        if (empty()) {
            return std::unexpected(circular_buffer_error::empty_buffer);
        }
        return data_[tail_];
    }

    constexpr void push_back(value_type const &value) {
        if (empty()) {
            size_++;
        }
        else if (!full()) {
            advance(tail_);
            size_++;
        }
        else {
            // Overwrite the oldest element
            advance(head_);
            advance(tail_);
        }
        data_[tail_] = value;
    }

    constexpr void push_back(value_type &&value) {
        if (empty()) {
            size_++;
        }
        else if (!full()) {
            advance(tail_);
            size_++;
        }
        else {
            // Overwrite the oldest element
            advance(head_);
            advance(tail_);
        }
        data_[tail_] = std::move(value);
    }

    constexpr std::expected<value_type, circular_buffer_error> pop_front() {
        if (empty()) {
            return std::unexpected(circular_buffer_error::empty_buffer);
        }
        auto const value = std::move(data_[head_]);
        advance(head_);
        size_--;
        return value;
    }

    constexpr std::expected<value_type, circular_buffer_error> pop_back() {
        if (empty()) {
            return std::unexpected(circular_buffer_error::empty_buffer);
        }
        auto const value = std::move(data_[tail_]);
        retreat(tail_);
        size_--;
        return value;
    }

private:
    static void advance(size_type& index) noexcept {
        if constexpr (is_power_of_two()) {
            index = (index + 1) & (Size - 1);
        } else {
            index = (index + 1) % Size;
        }
    }

    static void retreat(size_type& index) noexcept {
        if constexpr (is_power_of_two()) {
            index = (index - 1) & (Size - 1);
        } else {
            index = (index - 1) % Size;
        }
    }

    [[nodiscard]] static constexpr bool is_power_of_two() noexcept { return (Size > 0) && (Size & (Size - 1)) == 0; }
    [[nodiscard]] bool validate_index(size_type const index) const noexcept { return index < size_; }

    std::array<value_type, Size> data_;
    size_type head_{0};
    size_type tail_{0};
    size_type size_{0};
};

}   // namespace me::ds
