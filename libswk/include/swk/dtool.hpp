#ifndef SWK_DTOOL_HPP_INCLUDED
#define SWK_DTOOL_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <vector>
#include <map>

namespace swk {

inline
std::ostream& dout1(const char* file, int line, std::ostream& out = std::cerr)
{
	out << file << "(" << line << "): ";
	return out;
}

class dout2
{
public:

	dout2(const char* file, int line, std::ostream& out = std::cerr)
		: file_(file), line_(line), out_(out)
	{
	}

	~dout2()
	{
		print_();
	}

	template <class T>
	dout2& operator << (const T& x)
	{
		buf_ << x;
//		print_();
		return *this;
	}

private:

	void print_()
	{
		// TODO: mutex protection
		if (!buf_.str().empty()) {
			out_ << file_ << "(" << line_ << "): " << buf_.str() << std::endl;
			// clear buf_
			buf_.str("");
		}
	}

	const char* file_;
	int line_;
	std::ostream& out_;
	std::ostringstream buf_;

}; // class swk::dout2

template <class T>
void dvec(const char* name, const std::vector<T>& v, std::ostream& os = std::cerr)
{
	typename std::vector<T>::size_type n = 0;
	for (typename std::vector<T>::const_iterator it = v.begin();
	     it != v.end();
	     ++it) {
		os << name << "[" << n << "] == " << *it << std::endl;
		++n;
	}
}

template <class K, class V>
void dmap(const char* name, const std::map<K, V>& m, std::ostream& os = std::cerr)
{
	for (typename std::map<K, V>::const_iterator it = m.begin();
	     it != m.end();
	     ++it) {
		os << name << "[" << it->first << "] == " << it->second << std::endl;
	}
}

template <class K, class T>
void dmvec(const char* name, const std::map<K, std::vector<T> >& m, std::ostream& os = std::cerr)
{
	for (typename std::map<K, std::vector<T> >::const_iterator it = m.begin();
	     it != m.end();
	     ++it) {
		std::ostringstream tag;
		tag << name << "[" << it->first << "]";
		os << tag.str() << ":" << std::endl;
		dvec(tag.str().c_str(), it->second, os);
	}
}

} // namespace swk

#define SWK_DOUT swk::dout2(__FILE__, __LINE__)
#define SWK_DVAR(v) do { SWK_DOUT << "{" #v "} " << (v) << "~"; } while (false)
#define SWK_DVEC(v) swk::dvec(#v, (v))
#define SWK_DMAP(m) swk::dmap(#m, (m))
#define SWK_DMVEC(m) swk::dmvec(#m, (m))

#define SWK_STATIC_ASSERT(expr)

#endif /* SWK_DTOOL_HPP_INCLUDED */

