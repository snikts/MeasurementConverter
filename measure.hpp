#include <ratio>
namespace usu
{

    template <typename ratioType, typename storageType = std::uint64_t>
    class measure
    {
      private:
        storageType measureCount;

      public:
        using ratio = ratioType;
        measure()
        {
            measureCount = 0;
        }
        measure(storageType measurement)
        {
            measureCount = measurement;
        }
        storageType count() const
        {
            return measureCount;
        }
        measure operator+(measure m)
        {
            measure toReturn;
            toReturn.measureCount = measureCount + m.measureCount;
            return toReturn;
        }
        measure operator-(measure m)
        {
            measure toReturn;
            toReturn.measureCount = measureCount - m.measureCount;
            return toReturn;
        }
    };

    using millimeter = measure<std::ratio<1, 1000>, double>;
    using centimeter = measure<std::ratio<1, 100>, double>;
    using meter = measure<std::ratio<1, 1>, double>;
    using kilometer = measure<std::ratio<1000, 1>, double>;
    using inch = measure<std::ratio<1000000000, 39370078740>, double>;
    using feet = measure<std::ratio<1000000000, 3280839895>, double>;
    using yard = measure<std::ratio<1000000000, 1093613298>, double>;
    using mile = measure<std::ratio<1000000000, 621371>, double>;
    using league = measure<std::ratio<1000000000, 207123>, double>;

    template <typename M, typename S>
    M operator*(const S lhs, M& rhs)
    {
        M result(lhs * rhs.count());
        return result;
    }

    template <typename M, typename S>
    M operator*(M& lhs, const S rhs)
    {
        M result(lhs.count() * rhs);
        return result;
    }

    template <typename To, typename From>
    To measure_cast(From conversion)
    {
        double inMeters = conversion.count() * (static_cast<double>(From::ratio::num) / From::ratio::den);
        double count = (inMeters * (static_cast<double>(To::ratio::den) / To::ratio::num));
        To temp(count);
        return temp;
    }

    template <typename L, typename R>
    bool operator==(L lhs, R rhs)
    {
        meter lhsCount = measure_cast<meter, L>(lhs);
        meter rhsCount = measure_cast<meter, R>(rhs);
        if (lhsCount.count() == rhsCount.count())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename L, typename R>
    bool operator!=(L lhs, R rhs)
    {
        meter lhsCount = measure_cast<meter, L>(lhs);
        meter rhsCount = measure_cast<meter, R>(rhs);
        if (lhsCount.count() != rhsCount.count())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename L, typename R>
    bool operator>(L lhs, R rhs)
    {
        meter lhsCount = measure_cast<meter, L>(lhs);
        meter rhsCount = measure_cast<meter, R>(rhs);
        if (lhsCount.count() > rhsCount.count())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename L, typename R>
    bool operator<(L lhs, R rhs)
    {
        meter lhsCount = measure_cast<meter, L>(lhs);
        meter rhsCount = measure_cast<meter, R>(rhs);
        if (lhsCount.count() < rhsCount.count())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

} // namespace usu