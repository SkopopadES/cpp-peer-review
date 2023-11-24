#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <cassert>
#include <list>

using namespace std;

class Domain {
    // разработайте класс домена
public: 
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
    Domain(string_view str) : domain_(str) {
        reverse(domain_.begin(), domain_.end());
        domain_.push_back('.');
    }


    // разработайте operator==
    bool operator==(const Domain& other) {
        return domain_ == other.domain_;
    }
    bool operator<(const Domain& other) const {
        return lexicographical_compare(domain_.begin(), domain_.end(), 
                            other.domain_.begin(), other.domain_.end());
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& other) const {
        if (domain_.size() < other.domain_.size()) return false;
        auto res = std::mismatch(other.domain_.begin(), other.domain_.end(), domain_.begin());
        return res.first == other.domain_.end();
    }
    string GetDomain() const {
        return domain_;
    }
private:
        string domain_;
};

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template<typename InputIt>
    DomainChecker(InputIt begin, InputIt end) 
    : forbidden_domains_(begin, end)
    {
        sort(forbidden_domains_.begin(), forbidden_domains_.end());
        auto unique_end = unique(forbidden_domains_.begin(), forbidden_domains_.end(), 
        [](const Domain& lhs, const Domain& rhs){
            return lhs.IsSubdomain(rhs) || rhs.IsSubdomain(lhs);
        });
        forbidden_domains_.erase(unique_end, forbidden_domains_.end());
    }
    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& domain) const {
        auto it = upper_bound(forbidden_domains_.begin(), forbidden_domains_.end(), domain, [](const Domain& lhs, const Domain& rhs){
            return lhs.GetDomain() < rhs.GetDomain();
        });
        if (it == forbidden_domains_.begin()){
            return false; 
        } 
        else{
            return domain.IsSubdomain(*prev(it));
        } 
    }

    vector<Domain> forbidden_domains_;
};


template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
template <typename Number>
std::vector<Domain> ReadDomains(istream& input, Number number) {
    std::vector<Domain> result;
    string domain;

    for(int i = number; i > 0; --i) {
        getline(input, domain);
        result.push_back(Domain{domain});
    }

    return result;
}

void TestDomain()
{
    Domain domain_1_("abc.ru"s);
    Domain domain_2_("abc.ru"s);
    Domain domain_false_("ru.abc"s); 
    Domain domain_sub_true_("com.abc.ru"s);
    Domain domain_sub_false_("ru.abc.com"s);

    assert(!(domain_1_ == domain_false_));
    assert(domain_1_ == domain_2_);
    assert(domain_sub_true_.IsSubdomain(domain_1_));
    assert(!domain_sub_false_.IsSubdomain(domain_1_));
}

void TestDomainCheker()
{
    const std::vector<Domain> forbidden_domains{ Domain{"gdz.ru"s} };
    DomainChecker domain_checker( forbidden_domains.begin(), forbidden_domains.end() );
    assert(domain_checker.IsForbidden(Domain("math.gdz.ru")));
    assert(domain_checker.IsForbidden(Domain("history.gdz.ru")));
    assert(domain_checker.IsForbidden(Domain("biology.gdz.ru")));
    assert(!domain_checker.IsForbidden(Domain("freegdz.ru")));
}

int main() {

    TestDomain();
    TestDomainCheker();

    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}