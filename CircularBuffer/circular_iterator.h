#pragma once

//#include <compare>
#include <iterator>

template <typename T, std::size_t capacity>
class circular_iterator
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator_category = std::random_access_iterator_tag;

    circular_iterator(pointer buffer, const size_type offset) :
        buffer{ buffer },
        offset{ offset }
    {
    }

    pointer operator->() { return buffer + offset % capacity; }
    reference operator[](value_type index) const { return *(buffer + index); }
    reference operator*() const { return buffer[offset % capacity]; }

    circular_iterator& operator++() 
    { 
        ++offset;
        return *this;
    }

    circular_iterator operator++(difference_type)
    { 
        const auto old{ *this };
        ++offset;
        return old;
    }

    circular_iterator& operator--()
    {
        --offset;
        return *this;
    }

    circular_iterator operator--(difference_type)
    {
        const auto old{ *this };
        --offset;
        return old;
    }

    circular_iterator operator+(difference_type value)
    {
        return circular_iterator< value_type, capacity>{buffer, offset + value};
    }

    circular_iterator operator-(difference_type value)
    {
        return circular_iterator< value_type, capacity>{buffer, offset - value};
    }

    circular_iterator& operator+=(difference_type value)
    { 
        offset += value;
        return *this; 
    }

    circular_iterator& operator-=(difference_type value)
    { 
        offset -= value;
        return *this; 
    }

    difference_type operator-(circular_iterator const& sibling) const { return offset - sibling.offset; }
    difference_type operator+(circular_iterator const& sibling) const { return offset + sibling.offset; }

    // auto operator<=>(const circular_iterator&) const = default; partial support atm from VS

    friend bool operator== (const circular_iterator& a, const circular_iterator& b) { return a.buffer == b.buffer && a.offset == b.offset; };
    friend bool operator!= (const circular_iterator& a, const circular_iterator& b) { return a.buffer != b.buffer || a.offset != b.offset; };
    
    //friend bool operator> (const circular_iterator& a, const circular_iterator& b) { return a.offset > b.offset; }
    //friend bool operator>= (const circular_iterator& a, const circular_iterator& b) { return a.offset >= b.offset; }

    //friend bool operator< (const circular_iterator& a, const circular_iterator& b) { return a.offset < b.offset; }
    //friend bool operator<= (const circular_iterator& a, const circular_iterator& b) { return a.offset <= b.offset; }

    bool operator>(const circular_iterator& sibling) const { return offset > sibling.offset; }
    bool operator>=(const circular_iterator& sibling) const { return offset >= sibling.offset; }

    bool operator<(const circular_iterator& sibling) const { return offset < sibling.offset; }
    bool operator<=(const circular_iterator& sibling) const { return offset <= sibling.offset; }
    
private:
    pointer buffer;
    size_type offset;
};

