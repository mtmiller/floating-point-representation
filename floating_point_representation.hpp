#ifndef FLOATING_POINT_REPRESENTATION_HPP
#define FLOATING_POINT_REPRESENTATION_HPP

#include <limits>
#include <iterator>
#include <boost/dynamic_bitset.hpp>

class floating_point_representation {
public:
    typedef unsigned char block_type;
    typedef std::size_t size_type;

    floating_point_representation() : m_bits(0, 0), m_num_mant_bits(0),
                                      m_num_exp_bits(0) {}
    floating_point_representation(const floating_point_representation& rhs) :
        m_bits(rhs.m_bits), m_num_mant_bits(rhs.m_num_mant_bits),
        m_num_exp_bits(rhs.m_num_exp_bits) {}

    template<typename FloatT>
    floating_point_representation(const FloatT& value) :
        m_bits(rep<FloatT>::total_bits, 0ul),
        m_num_mant_bits(rep<FloatT>::mantissa_bits),
        m_num_exp_bits(rep<FloatT>::exponent_bits) { set_value(value); }

    floating_point_representation&
    operator=(const floating_point_representation& rhs) {
        m_bits = rhs.m_bits;
        m_num_mant_bits = rhs.m_num_mant_bits;
        m_num_exp_bits = rhs.m_num_exp_bits;
        return *this;
    }

    template<typename FloatT>
    floating_point_representation&
    operator=(const FloatT& value) {
        m_bits.resize(rep<FloatT>::total_bits);
        m_num_mant_bits = rep<FloatT>::mantissa_bits;
        m_num_exp_bits = rep<FloatT>::exponent_bits;
        set_value(value);
    }

    size_type size() const { return m_bits.size(); }
    size_type bits() const { return m_bits.size(); }
    size_type mantissa_bits() const { return m_num_mant_bits; }
    size_type exponent_bits() const { return m_num_exp_bits; }
    size_type sign_bits() const { return 1; }

    int exponent() const {
        const int bias = (1 << (exponent_bits() - 1)) - 1;
        int exp = 0;
        int i = mantissa_bits() + exponent_bits();
        while (i > mantissa_bits()) { exp = (exp << 1) | bitval(--i); }
        return exp - bias;
    }

    bool operator[](size_type n) const { return m_bits[n]; }
    int bitval(size_type n) const { return m_bits[n] ? 1 : 0; }
    char bitchar(size_type n) const { return m_bits[n] ? '1' : '0'; }

private:
    template<typename FloatT>
    struct rep {
        static const int total_bits = sizeof(FloatT) * CHAR_BIT;
        static const int unused_bits = 0;
        static const int implied_lead_bit = 1;
        static const int mantissa_digits = std::numeric_limits<FloatT>::digits;
        static const int mantissa_bits = mantissa_digits - implied_lead_bit;
        static const int exponent_bits = total_bits - mantissa_bits - 1;
        static const int blocks = sizeof(FloatT) / sizeof(block_type);
    };

    typedef boost::dynamic_bitset<> buffer_type;

    buffer_type m_bits;
    size_type m_num_mant_bits;
    size_type m_num_exp_bits;

    template<typename FloatT>
    void set_value(const FloatT& value) {
        const block_type* barray = reinterpret_cast<const block_type*>(&value);
        const int blen = rep<FloatT>::blocks;
#if defined(__i386__) || defined(__alpha__) || defined(__ia64) || defined(__ia64__)
        std::reverse_iterator<const block_type*> first(barray + blen);
        std::reverse_iterator<const block_type*> last(barray);
#else
        const block_type* first(barray);
        const block_type* last(barray + blen);
#endif
        for ( ; first != last; ++first) {
            buffer_type lsb(size(), static_cast<unsigned long>(*first));
            m_bits <<= (sizeof(block_type) * CHAR_BIT);
            m_bits |= lsb;
        }
    }
};

#if defined(__i386__)
template<>
struct floating_point_representation::rep<long double> {
    static const int total_bits = sizeof(long double) * CHAR_BIT;
    static const int unused_bits = 16;
    static const int implied_lead_bit = 0;
    static const int mantissa_digits = std::numeric_limits<long double>::digits;
    static const int mantissa_bits = mantissa_digits - implied_lead_bit;
    static const int exponent_bits = total_bits-unused_bits-mantissa_bits-1;
    static const int blocks = sizeof(long double) / sizeof(block_type);
};
#endif // __i386__

#endif // FLOATING_POINT_REPRESENTATION_HPP
