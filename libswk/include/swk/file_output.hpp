#ifndef SWK_FILE_OUTPUT_HPP_INCLUDED
#define SWK_FILE_OUTPUT_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/file_traits.hpp>
#include <swk/file_split.hpp>
#include <swk/fs_local.hpp>
#include <swk/dtool.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>

namespace swk {

template <class OK, class OV>
class record_writer
{
public:

	typedef OK ok_type;
	typedef OV ov_type;

	record_writer(const std::string& path)
		: path_(path)
		, out_(0)
	{
	}

	~record_writer()
	{
		if (out_) {
			delete out_;
		}
	}

	void write(const ok_type& ok, const ov_type& ov)
	{
		if (out_ == 0) {
			out_ = new std::ofstream(path_.c_str());
		}
		out_ << ok << "\t" << ov << std::endl;
	}

private:

	std::string path_;
	std::ostream* out_;

}; // class swk::record_writer<>

/**
 * A section of an input file.
 */
template <class FS = fs_local, class FT = text_file_traits<FS> >
class file_output
{
public:

	file_output()
	{
	}

	template <class OK, class OV>
	std::auto_ptr< record_writer<OK, OV> > get_record_writer()
	{
		return new record_writer<OK, OV>(path_);
	}

	void set_path(const std::string& path)
	{
		path_ = path;
	}

	template <class OK, class OV>
	void write(const OK& ok, const OV& ov)
	{
		std::ofstream ofs(path_.c_str(), std::ios::app);
		ofs << ok << "\t" << ov << std::endl;
	}

private:

	std::string path_;

}; // class swk::file_output<>

} // namespace swk

#endif /* SWK_FILE_OUTPUT_HPP_INCLUDED */


