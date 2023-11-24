
static const int MIN_YEAR_=0;
static const int MAX_YEAR_=9999;
static const int MIN_MONTH_=1;
static const int MAX_MONTH_=12;
static const int MIN_DAY_=1;
static const int MIN_HOURS_=0;
static const int MAX_HOURS_=23;
static const int MIN_MINUTES_=0;
static const int MAX_MINUTES_=59;
static const int MIN_SECONDS_=0;
static const int MAX_SECONDS_=59;


void CheckDateTimeValidity(const DateTime& dt) {
    if (dt.year < MIN_YEAR_) {
        throw domain_error("year is too small"s);
    }
    if (dt.year > MAX_YEAR_) {
        throw domain_error("year is too big"s);
    }

    if (dt.month < MIN_MONTH_) {
        throw domain_error("month is too small"s);
    }
    if (dt.month > MAX_MONTH_) {
        throw domain_error("month is too big"s);
    }

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dt.day < MIN_DAY_) {
        throw domain_error("day is too small"s);
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        throw domain_error("day is too big"s);
    }

    if (dt.hour < MIN_HOURS_) {
        throw domain_error("hour is too small"s);
    }
    if (dt.hour > MAX_HOURS_) {
        throw domain_error("hour is too big"s);
    }

    if (dt.minute < MIN_MINUTES_) {
        throw domain_error("minute is too small"s);
    }
    if (dt.minute > MAX_MINUTES_) {
        throw domain_error("minute is too big"s);
    }

    if (dt.second < MIN_SECONDS_) {
        throw domain_error("second is too small");
    }
    if (dt.second > MAX_SECONDS_) {
        throw domain_error("second is too big"s);
    }
}