//#include "circular_buffer.h"
//
//#include <cmath>
//#include <numeric>
//
//namespace container
//{
//	template<typename T, std::size_t N>
//	circular_buffer<T, N>::circular_buffer() : 
//		buffer{new value_type[default_capacity]},
//		head{0},
//		tail{0}
//	{
//	}
//
//	template<typename T, std::size_t N>
//	circular_buffer<T, N>::~circular_buffer()
//	{
//		delete[] buffer;
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::size_type circular_buffer<T, N>::size() const noexcept
//	{
//		return std::abs(head - tail);
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::size_type circular_buffer<T, N>::max_size() const noexcept
//	{
//		return  std::numeric_limits<difference_type>::max();
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::size_type circular_buffer<T, N>::capacity() const noexcept
//	{
//		return N;
//	}
//
//	template<typename T, std::size_t N>
//	constexpr bool circular_buffer<T, N>::empty() const noexcept
//	{
//		return head == tail;
//	}
//
//	template<typename T, std::size_t N>
//	constexpr bool circular_buffer<T, N>::full() const noexcept
//	{
//		return false;
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::reference circular_buffer<T, N>::at(size_type pos) noexcept(false)
//	{
//		if (pos >= std::min(head, tail) and pos <= std::max(head, tail))
//		{
//			return buffer[pos];
//		}
//		throw std::out_of_range("circular_buffer::_M_range_check");
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::const_reference circular_buffer<T, N>::at(size_type pos) const noexcept(false)
//	{
//		if (pos >= std::min(head, tail) and pos <= std::max(head, tail))
//		{
//			return buffer[pos];
//		}
//		throw std::out_of_range("circular_buffer::_M_range_check");
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::reference circular_buffer<T, N>::front() noexcept
//	{
//		return buffer[head];
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::const_reference circular_buffer<T, N>::front() const noexcept
//	{
//		return buffer[head];
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::reference circular_buffer<T, N>::back() noexcept
//	{
//		return buffer[tail];
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::const_reference circular_buffer<T, N>::back() const noexcept
//	{
//		return buffer[tail];
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::pointer circular_buffer<T, N>::data() noexcept
//	{
//		return buffer;
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::pointer circular_buffer<T, N>::data() const noexcept
//	{
//		return buffer;
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::iterator begin() noexcept 
//	{
//		return circular_iterator{ buffer + head, buffer + tail };
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::const_iterator circular_buffer<T, N>::cbegin() const noexcept
//	{
//		return circular_iterator{ buffer + head, buffer + tail };
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::iterator end() noexcept 
//	{
//		return circular_iterator{ buffer + tail, buffer + head, buffer + tail };
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::const_iterator circular_buffer<T, N>::cend() const noexcept
//	{
//		return circular_iterator{ buffer + tail, buffer + head, buffer + tail };
//	}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::reverse_iterator rbegin() noexcept {}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::const_reverse_iterator circular_buffer<T, N>::crbegin() const noexcept {}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::reverse_iterator rend() noexcept {}
//
//	template<typename T, std::size_t N>
//	constexpr circular_buffer<T, N>::const_reverse_iterator circular_buffer<T, N>::crend() const noexcept {}
//}