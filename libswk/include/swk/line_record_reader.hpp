#ifndef SWK_LINE_RECORD_READER_HPP_INCLUDED
#define SWK_LINE_RECORD_READER_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/fs_local.hpp>
#include <swk/file_traits.hpp>
#include <swk/misc.hpp>
#include <boost/io/ios_state.hpp>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>

namespace swk {

template <class FS = fs_local>
class line_record_reader /* : public record_reader<uint64_t, std::string> */
{
public:

	line_record_reader(const file_split& split)
		: split_(split)
		, line_beg_(split.start())
		, line_end_(split.start())
		, ic_(split.path().c_str(), std::ios::binary)
	{
	}

	std::pair<uint64_t, std::string> current()
	{
		if (line_end_ <= line_beg_) {
			throw std::runtime_error("No current value yet. Please advance() first.");
		}
//		SWK_DVAR(line_beg_);
//		SWK_DVAR(line_end_);
		size_t length = line_end_ - line_beg_;
//		SWK_DVAR(length);
		boost::io::ios_all_saver ips(ic_);
		auto_buffer<> buffer(length);
		ic_.seekg(line_beg_);
		if (ic_) {
//			SWK_DVAR(line_beg_);
//			SWK_DVAR(line_end_);
//			SWK_DVAR(length);
			if (ic_.read(buffer.get(), length)) {
				std::pair<uint64_t, std::string> c;
				c.first = line_beg_;
				c.second = std::string(buffer.get(), length);
//				SWK_DVAR(c.second);
//				std::cerr << "@" << length << "@" << c.second << "||";
				return c;
			}
		}
		throw std::runtime_error("Failed to get current key/value.");
	}

	bool advance()
	{
		line_beg_ = line_end_;
		if (line_beg_ > split_.end()) {
			return false;
		}
		size_t le = std::min(
			text_file_traits<FS>::find_boundary(ic_, line_beg_),
			split_.end()
		);
//		SWK_DVAR(line_beg_);
//		SWK_DVAR(line_end_);
//		SWK_DVAR(le);
		if (le <= line_beg_) {
			return false;
		}
		line_end_ = le;
		return true;
	}

private:

	file_split split_;
	size_t line_beg_;
	size_t line_end_;
	std::ifstream ic_;

}; // class swk::line_record_reader

} // namespace swk

#endif /* SWK_LINE_RECORD_READER_HPP_INCLUDED */

