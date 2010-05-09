#ifndef SWK_DTOOL_HPP_INCLUDED
#define SWK_DTOOL_HPP_INCLUDED

#include <iostream>
#include <sstream>

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

} // namespace swk

#define SWK_DOUT swk::dout2(__FILE__, __LINE__)
#define SWK_DVAR(v) do { SWK_DOUT << "{" #v "} " << (v) << "~"; } while (false)

#endif /* SWK_DTOOL_HPP_INCLUDED */

