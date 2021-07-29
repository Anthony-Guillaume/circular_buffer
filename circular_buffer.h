#pragma once

#include <cstddef>
#include <cmath>
#include <numeric>
#include "circular_iterator.h"

namespace container
{
	template<typename T, std::size_t N>
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

			circular_buffer();
			~circular_buffer();

			constexpr size_type size() const noexcept;
			constexpr size_type max_size() const noexcept;
			constexpr size_type capacity() const noexcept;
			constexpr bool empty() const noexcept;
			constexpr bool full() const noexcept;

			constexpr reference at(size_type pos) noexcept(false);
			constexpr const_reference at(size_type pos) const noexcept(false);
			constexpr reference front() noexcept;
			constexpr const_reference front() const noexcept;
			constexpr reference back() noexcept;
			constexpr const_reference back() const noexcept;

			constexpr pointer data() noexcept;

			constexpr iterator begin() noexcept;
			constexpr const_iterator cbegin() const noexcept;
			constexpr iterator end() noexcept;
			constexpr const_iterator cend() const noexcept;

			constexpr reverse_iterator rbegin() noexcept;
			constexpr const_reverse_iterator crbegin() const noexcept;
			constexpr reverse_iterator rend() noexcept;
			constexpr const_reverse_iterator crend() const noexcept;
			
			//constexpr reference emplace_back(value_type&& value) noexcept;
			//constexpr reference emplace_back(value_type&& value...) noexcept;
			constexpr void push_back(value_type&& value) noexcept;
			//constexpr void push_back(value_type& value...) noexcept;

			//constexpr void clear() noexcept;
			//constexpr void fill(value_type& value) noexcept;
			//constexpr void fill(value_type& value, size_type n) noexcept;
			//constexpr void swap(circular_buffer& other) noexcept;

			//constexpr reference operator[](size_type pos);
			//constexpr const_reference operator[](size_type pos) const;

			//constexpr bool operator==(const circular_buffer<value_type, size_type>& lhs,
			//	const circular_buffer<value_type, size_type>& rhs);
			//constexpr auto operator<=>(const circular_buffer<value_type, size_type>& lhs,
			//	const circular_buffer<value_type, size_type>& rhs);

		private:
			size_type head;
			size_type tail;
			pointer buffer;
	};

	template<typename T, std::size_t N>
	circular_buffer<T, N>::circular_buffer() :
		buffer{ new value_type[N] },
		head{ 0 },
		tail{ 0 }
	{
	}

	template<typename T, std::size_t N>
	circular_buffer<T, N>::~circular_buffer()
	{
		delete[] buffer;
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::size_type circular_buffer<T, N>::size() const noexcept
	{
		return std::abs(head - tail);
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::size_type circular_buffer<T, N>::max_size() const noexcept
	{
		return  std::numeric_limits<difference_type>::max();
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::size_type circular_buffer<T, N>::capacity() const noexcept
	{
		return N;
	}

	template<typename T, std::size_t N>
	constexpr bool circular_buffer<T, N>::empty() const noexcept
	{
		return head == tail;
	}

	template<typename T, std::size_t N>
	constexpr bool circular_buffer<T, N>::full() const noexcept
	{
		return false;
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::reference circular_buffer<T, N>::at(size_type pos) noexcept(false)
	{
		if (pos >= std::min(head, tail) and pos <= std::max(head, tail))
		{
			return buffer[pos];
		}
		throw std::out_of_range("circular_buffer::_M_range_check");
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::const_reference circular_buffer<T, N>::at(size_type pos) const noexcept(false)
	{
		if (pos >= std::min(head, tail) and pos <= std::max(head, tail))
		{
			return buffer[pos];
		}
		throw std::out_of_range("circular_buffer::_M_range_check");
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::reference circular_buffer<T, N>::front() noexcept
	{
		return buffer[head];
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::const_reference circular_buffer<T, N>::front() const noexcept
	{
		return front();
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::reference circular_buffer<T, N>::back() noexcept
	{
		return buffer[tail];
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::const_reference circular_buffer<T, N>::back() const noexcept
	{
		return back();
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::pointer circular_buffer<T, N>::data() noexcept
	{
		return buffer;
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::iterator circular_buffer<T, N>::begin() noexcept
	{
		return { buffer, head };
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::const_iterator circular_buffer<T, N>::cbegin() const noexcept
	{
		return begin();
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::iterator circular_buffer<T, N>::end() noexcept
	{
		return { buffer, tail };
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::const_iterator circular_buffer<T, N>::cend() const noexcept
	{
		return end();
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::reverse_iterator circular_buffer<T, N>::rbegin() noexcept 
	{
		return reverse_iterator{ end() };
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::const_reverse_iterator circular_buffer<T, N>::crbegin() const noexcept
	{
		return rbegin();
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::reverse_iterator circular_buffer<T, N>::rend() noexcept
	{
		return reverse_iterator{ begin() };
	}

	template<typename T, std::size_t N>
	constexpr circular_buffer<T, N>::const_reverse_iterator circular_buffer<T, N>::crend() const noexcept
	{
		return rend();
	}

	template<typename T, std::size_t N>
	constexpr void circular_buffer<T, N>::push_back(circular_buffer<T, N>::value_type&& value) noexcept
	{
		if (tail < size())
		{

		}
		//buffer[tail] = std::move(_element);
	}

} // namespace container


