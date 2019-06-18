#ifndef STRINGNUMBER_H
#define STRINGNUMBER_H

#include <string>

namespace scientific {
    class StringNumber {
        std::string m_number;
        bool m_isPositive = true;

        void initNumber(const std::string &number);


    public:
        using value_type = std::string::value_type;

        // CREATORS
        StringNumber() = default;
        explicit StringNumber(const std::string &number) {
            initNumber(number);
        }
        explicit StringNumber(const char *number) {
            initNumber(number);
        }

        StringNumber(const StringNumber &) = default;
        StringNumber(StringNumber &&) = default;
        StringNumber &operator=(const StringNumber &) = default;
        StringNumber &operator=(StringNumber &&) = default;

        void push_back(char c);
        void normalize();
        void setPositive(bool isPositive) { m_isPositive = isPositive; }

        bool isNull() const;
        bool isPositive() const { return m_isPositive; }

        size_t size() const { return m_number.size(); }

        auto cbegin() const { return m_number.cbegin(); }
        auto begin() { return m_number.begin(); }
        auto begin() const { return cbegin(); }
        auto crbegin() const { return m_number.crbegin(); }

        auto cend() const { return m_number.cend(); }
        auto end() { return m_number.end(); }
        auto end() const { return cend(); }
        auto crend() const { return m_number.crend(); }
    };

    StringNumber operator+(const StringNumber &lhs, const StringNumber &rhs);

    StringNumber operator*(const StringNumber &lhs, const StringNumber &rhs);

    bool operator<(const StringNumber& lhs, const StringNumber& rhs);
    bool operator==(const StringNumber& lhs, const StringNumber& rhs);

    std::ostream& operator<<(std::ostream& os, const StringNumber& number);
}

#endif // STRINGNUMBER_H
