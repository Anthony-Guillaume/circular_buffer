#pragma once

#include <cstddef>
#include <cmath>
#include <numeric>
#include <concepts>
#include "circular_iterator.h"

/*
	Fixe sized circular buffer allocated on stack.
*/

namespace container
{
	template<typename T, std::size_t N>
	//requires std::default_initializable<T> && std::copy_constructible
	class circular_buffer
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const pointer;
		using iterator = circular_iterator<T, N>;
		using const_iterator = circular_iterator<const T, N>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		circular_buffer() : buffer{}, head{ 0 }, tail{ N - 1 } {}

		constexpr pointer data() noexcept { return buffer; }
		constexpr size_type size() const noexcept { return N; }
		constexpr size_type max_size() const noexcept { return std::numeric_limits<difference_type>::max(); }
		constexpr size_type capacity() const noexcept { return N; }

		constexpr reference operator[](size_type pos) { return buffer[pos]; }
		constexpr const_reference operator[](size_type pos) const { return buffer[pos]; }

		constexpr reference at(size_type pos) noexcept(false)
		{
			if (pos < N)
			{
				return buffer[pos];
			}
			throw std::out_of_range("circular_buffer::_M_range_check");
		}

		constexpr const_reference at(size_type pos) const noexcept(false)
		{
			if (pos < N)
			{
				return buffer[pos];
			}
			throw std::out_of_range("circular_buffer::_M_range_check");
		}

		constexpr reference front() noexcept { return buffer[head]; }
		constexpr const_reference front() const noexcept { return front(); }
		constexpr reference back() noexcept { return buffer[tail]; }
		constexpr const_reference back() const noexcept { return back(); }

		constexpr iterator begin() noexcept { return { buffer, head }; }
		constexpr const_iterator cbegin() const noexcept { return begin(); }
		constexpr iterator end() noexcept { return { buffer, tail }; }
		constexpr const_iterator cend() const noexcept { return end(); }

		//constexpr reverse_iterator rbegin() noexcept { return reverse_iterator{ end() }; }
		//constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }
		//constexpr reverse_iterator rend() noexcept { return reverse_iterator{ begin() }; }
		//constexpr const_reverse_iterator crend() const noexcept { return rend(); }

		constexpr void push_back(const value_type& value) noexcept
		{
			if (atLeastOneCycle) [[likely]]
			{
				++head;
				if (head == size())
				{
					head = 0;
				}
			}
			else
			{
				++head;
				if (head == size())
				{
					head = 0;
					atLeastOneCycle = true;
				}
			}
			if (head == tail)
			{
				++tail;
				if (tail == size())
				{
					tail = 0;
				}
			}
			buffer[head] = value;
		}

		constexpr void clear() noexcept
		{
			auto numberOfElementToClear{ atLeastOneCycle ? size() : head + 1 };
			for (auto i{ 0 }; i < numberOfElementToClear; ++i)
			{
				buffer[i] = value_type{};
			}
		}

		constexpr void fill(const value_type& value, size_type n) noexcept
		{
			for (auto i{ 0 }; i < n; ++i)
			{
				buffer[i] = value;
			}
		}

		constexpr void fill(const value_type& value) noexcept
		{
			fill(value, size());
		}

		friend bool operator== (const circular_buffer& a, const circular_buffer& b) { return a.buffer == b.buffer && a.head == b.head && a.tail == b.tail; };
		friend bool operator!= (const circular_buffer& a, const circular_buffer& b) { return a.buffer != b.buffer || a.head == b.head || a.tail == b.tail; };

		//constexpr auto operator<=>(const circular_buffer& lhs, const circular_buffer& rhs); partial support atm from VS

	private:
		size_type head;
		size_type tail;
		value_type buffer[N];
		bool atLeastOneCycle{ false };
	};
} // namespace container
