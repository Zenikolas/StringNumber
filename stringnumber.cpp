#include "stringnumber.h"
#include <iostream>
#include <algorithm>

namespace scientific {
    namespace {
        bool isLessModule(const StringNumber &lhs, const StringNumber &rhs) {
            if (lhs.size() < rhs.size()) {
                return true;
            } else if (rhs.size() < lhs.size()) {
                return false;
            }

            auto rit = rhs.begin();
            for (auto lit = lhs.cbegin(); lit != lhs.cend(); ++lit, ++rit) {
                if (*lit < *rit) {
                    return true;
                } else if (*rit < *lit) {
                    return false;
                }
            }

            return false;
        }

        void initBinaryOperandBounds(std::string::const_reverse_iterator &shortBegin,
                                     std::string::const_reverse_iterator &shortEnd,
                                     std::string::const_reverse_iterator &longBegin,
                                     std::string::const_reverse_iterator &longBeginAppend,
                                     std::string::const_reverse_iterator &longEnd,
                                     const StringNumber &lhs,
                                     const StringNumber &rhs) {
            if (isLessModule(lhs, rhs)) {
                shortBegin = lhs.crbegin();
                shortEnd = lhs.crend();
                longBegin = rhs.crbegin();
                longBeginAppend = longBegin + lhs.size();
                longEnd = rhs.crend();
            } else {
                shortBegin = rhs.crbegin();
                shortEnd = rhs.crend();
                longBegin = lhs.crbegin();
                longBeginAppend = longBegin + rhs.size();
                longEnd = lhs.crend();
            }
        }
    }

    bool StringNumber::isNull() const {
        bool isNull = true;
        for (auto &digit : m_number) {
            if (digit != '0') {
                isNull = false;
                break;
            }
        }

        return isNull;
    }

    void StringNumber::push_back(char c) {
        if (c >= '0' && c <= '9') {
            m_number.push_back(c);
        }
    }

    void StringNumber::initNumber(const std::string &number) {
        auto begin = number.cbegin();
        if (number.front() == '+') {
            m_isPositive = true;
            ++begin;
        } else if (number.front() == '-') {
            m_isPositive = false;
            ++begin;
        }

        begin = std::find_if(begin, number.cend(), [](char ch) { return ch != '0'; });

        m_number.assign(begin, number.cend());
    }

    void StringNumber::normalize() {
        m_number.erase(std::find_if(m_number.rbegin(), m_number.rend(),
                                    [](char ch) {
                                        return ch != '0';
                                    }).base(), m_number.end());
    }

    StringNumber operator+(const StringNumber &lhs, const StringNumber &rhs) {
        if (lhs.isNull()) {
            return rhs;
        }
        if (rhs.isNull()) {
            return lhs;
        }

        std::string::const_reverse_iterator shortBegin;
        std::string::const_reverse_iterator shortEnd;
        std::string::const_reverse_iterator longBegin;
        std::string::const_reverse_iterator longBeginAppend;
        std::string::const_reverse_iterator longEnd;
        initBinaryOperandBounds(shortBegin, shortEnd, longBegin,
                                longBeginAppend, longEnd, lhs, rhs);

        bool shift = false;
        bool negative = false;
        bool isSum = lhs.isPositive() == rhs.isPositive();
        auto sumSymbolicDigits = [&shift, &negative, isSum](char lch, char rch) {
            int sum{};
            if (isSum) {
                sum = rch + lch;
            } else {
                sum = rch - lch;
            }

            if (shift && !negative) {
                ++sum;
            } else if (shift && negative) {
                --sum;
            }

            sum %= '0';
            sum += '0';
            if (sum > '9') {
                sum -= 10;
                shift = true;
                negative = false;
            } else if (sum < '0') {
                sum += 10;
                shift = true;
                negative = true;
            } else {
                negative = false;
                shift = false;
            }

            return (char) sum;
        };

        StringNumber result;
        std::transform(shortBegin, shortEnd, longBegin, std::back_inserter(result),
                       sumSymbolicDigits);

        for (auto it = longBeginAppend; it != longEnd; ++it) {
            int sum = *it;
            if (shift && !negative) {
                ++sum;
            } else if (shift && negative) {
                --sum;
            }

            if (sum < '0') {
                sum += 10;
                shift = true;
                negative = true;
            } else if (sum > '9') {
                sum -= 10;
                shift = true;
                negative = false;
            } else {
                shift = false;
                negative = false;
            }

            result.push_back(sum);
        }

        if (shift) {
            result.push_back('1');
        }

        if (!lhs.isPositive() && isLessModule(rhs, lhs)) {
            negative = true;
        } else if (!rhs.isPositive() && isLessModule(lhs, rhs)) {
            negative = true;
        }

        if (negative || (!lhs.isPositive() && !rhs.isPositive())) {
            result.setPositive(false);
        }

        result.normalize();
        std::reverse(result.begin(), result.end());

        return result;
    }

    StringNumber operator*(const StringNumber &lhs, const StringNumber &rhs) {
        if (lhs.isNull() || rhs.isNull()) {
            return StringNumber{};
        }

        std::string::const_reverse_iterator shortBegin;
        std::string::const_reverse_iterator shortEnd;
        std::string::const_reverse_iterator longBegin;
        std::string::const_reverse_iterator longBeginAppend;
        std::string::const_reverse_iterator longEnd;
        initBinaryOperandBounds(shortBegin, shortEnd, longBegin,
                                longBeginAppend, longEnd, lhs, rhs);


        return StringNumber{};
    }

    bool operator<(const StringNumber &lhs, const StringNumber &rhs) {
        bool inverse = false;
        if (!lhs.isPositive()) {
            if (rhs.isPositive()) {
                return true;
            } else {
                inverse = true;
            }
        } else {
            if (!rhs.isPositive()) {
                return false;
            }
        }

        bool isLess = isLessModule(lhs, rhs);
        if (inverse && isLess) {
            return false;
        }

        return isLess;
    }

    bool operator==(const StringNumber &lhs, const StringNumber &rhs) {
        return !((lhs < rhs) || (rhs < lhs));
    }

    std::ostream &operator<<(std::ostream &os, const
    StringNumber &number) {
        if (!number.isPositive()) {
            os << "-";
        }

        if (number.isNull()) {
            os << "0";
        }

        for (auto &sym : number) {
            os << sym;
        }

        return os;
    }
}
