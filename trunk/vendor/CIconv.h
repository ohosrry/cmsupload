#ifndef M_iconv_hpp
#define M_iconv_hpp

#include<algorithm>
#include<cerrno>
#include<exception>
#include<string>
#include<iconv.h>

namespace Iconv
{

	/**
	* 这是一个为最常用的类型转换做简化工作，你可以向其中添加自己常用的类型。
	* 不过当你添加完之后别忘了把下面的实用工具也作相应的修改。
	*/
	typedef enum 
	{
		gbk_to_utf8,
		utf8_to_gbk,
		big5_to_utf8,
		utf8_to_big5,
		gb18030_to_utf8,
		utf8_to_gb18030,
	}
	conv_type;

	inline const char* type_from(const conv_type type)
	{
		switch(type)
		{
		case gbk_to_utf8: return "GBK";
		case big5_to_utf8: return "BIG5";
		case gb18030_to_utf8: return "GB18030";

		case utf8_to_gbk:
		case utf8_to_big5:
		case utf8_to_gb18030: return "UTF-8";
		default: return "UNKOWN";
		}
	}

	inline const char* type_to(const conv_type type)
	{
		switch(type)
		{
		case gbk_to_utf8:
		case big5_to_utf8:
		case gb18030_to_utf8: return "UTF-8";

		case utf8_to_gbk: return "GBK";
		case utf8_to_big5: return "BIG5";
		case utf8_to_gb18030: return "GB18030";
		default: return "UNKOWN";
		}
	}


	// -------------------------------------------------------------------
	struct No_throw
	{};
	const No_throw no_throw={};


	// -------------------------------------------------------------------
	class bad_convert : public std::exception
	{
	public:
		bad_convert(char const * descript)
			: _descript(descript)
		{}

		bad_convert(const std::string & descript)
			: _descript(descript)
		{}

		bad_convert()
			: _descript("iconv error: Unexpected.")
		{}

		virtual ~bad_convert() throw()
		{}

		virtual const char* what() const throw()
		{
			return _descript.c_str();
		}
	private:
		const std::string _descript;
	};

	/**
	* 这个类是iconv的一个C++ Wapper，它使用POSIX:2001的iconv库作为其工作基础
	* 由于iconv_t没有可复制的合理方式，所以删除了复制构造函数与赋值操作运算符
	*/
	template<typename String>
	class Convertor
	{
	public:
		Convertor(int error_unit=-1);
		Convertor(conv_type ct, int error_unit=-1) throw(bad_convert);
		Convertor(const String& to, const String& from, int error_unit=-1) throw(bad_convert);
		Convertor(Convertor&)=delete;//C++09新特征

		bool to_from_set(const String& to, const String& from, No_throw);
		void to_from_set(const String& to, const String& from) throw(bad_convert);
		bool to_from_set(const conv_type type, No_throw);
		void to_from_set(const conv_type type) throw(bad_convert);

		const String& conv(const String& from) const throw(bad_convert);
		const String& conv(const char* from, size_t size) const throw(bad_convert);
		bool conv(String& to, const String& from) const;
		bool conv(String& to, const char* from, size_t size) const;

		Convertor& operator=(Convertor&)=delete;

		~Convertor();

	private:
		bool conv_do(String& t, const char* from, size_t from_size) const;
		iconv_t _cd;
		mutable String _to;
		//多少个字节允许一个非法序列
		//负数说明不允许任何非法序列
		int _error_unit;
	};

	/**
	* 提供的一组便利函数，以使得简单的情况不复杂
	*/
	template<typename String>
	String easy_conv(const conv_type type, const String& from) throw(bad_convert);

	template<typename String>
	String easy_conv(const conv_type type, const char* from, size_t size) throw(bad_convert);

	std::string easy_conv(const conv_type type, const char* from, size_t size) throw(bad_convert);

	template<typename String>
	String easy_conv(const String& to_type, const String& from_type, const String& from) throw(bad_convert);

	template<typename String>
	String easy_conv(const String& to_type, const String& from_type, const char* from, size_t size) throw(bad_convert);

}

namespace Iconv
{


	// -------------------------------------------------------------------
	template<typename String>
	Convertor<String>::Convertor(int error_unit)
		:_cd((iconv_t)-1),  _error_unit(error_unit)
	{

	}


	// -------------------------------------------------------------------
	template<typename String>
	Convertor<String>::Convertor(const String& to, const String& from, int error_unit) throw(bad_convert)
		:_cd((iconv_t)-1),  _error_unit(error_unit)
	{
		to_from_set(to, from);
	}


	// -------------------------------------------------------------------
	template<typename String>
	Convertor<String>::Convertor(const conv_type type, int error_unit) throw(bad_convert)
		:_cd((iconv_t)-1),  _error_unit(error_unit)
	{
		to_from_set(type);
	}


	// -------------------------------------------------------------------
	template<typename String>
	bool Convertor<String>::to_from_set(const String& to, const String& from, No_throw)
	{
		if((iconv_t)-1!=_cd)
		{
			::iconv_close(_cd);
		}
		_cd=::iconv_open(to.c_str(), from.c_str());
		return ((iconv_t)(-1)!=_cd);
	}


	// -------------------------------------------------------------------
	template<typename String>
	void Convertor<String>::to_from_set(const String& to, const String& from) throw(bad_convert)
	{
		if((iconv_t)-1!=_cd)
		{
			::iconv_close(_cd);
		}
		_cd=::iconv_open(to.c_str(), from.c_str());
		if((iconv_t)(-1)==_cd)
		{
			throw bad_convert("iconv failed: unknow encodec or decodec.");
		}
	}

	// -------------------------------------------------------------------
	template<typename String>
	void Convertor<String>::to_from_set(const conv_type type) throw(bad_convert)
	{
		to_from_set(type_to(type), type_from(type));
	}


	// -------------------------------------------------------------------
	template<typename String>
	bool Convertor<String>::to_from_set(const conv_type type, No_throw)
	{
		return to_from_set(type_to(type), type_from(type), no_throw);
	}


	// -------------------------------------------------------------------
	template<typename String>
	const String& Convertor<String>::conv(const char* from, size_t size) const throw(bad_convert)
	{
		if(!conv_do(_to, from, size))
		{
			throw bad_convert("iconv error: Too many invalid multibyte"
				" sequence has been encountered in the input.");
		}
		return _to;
	}


	// -------------------------------------------------------------------
	template<typename String>
	const String& Convertor<String>::conv(const String& from) const throw(bad_convert)
	{
		if(!conv_do(_to, from.c_str(), sizeof(from[0])*from.size()))
		{
			throw bad_convert("iconv error: Too many invalid multibyte"
				" sequence has been encountered in the input.");
		}
		return _to;
	}


	// -------------------------------------------------------------------
	template<typename String>
	bool Convertor<String>::conv(String& to, const String& from) const
	{
		return conv_do(to, from.c_str(), sizeof(from[0])*from.size());
	}


	// -------------------------------------------------------------------
	template<typename String>
	bool Convertor<String>::conv(String& to, const char* from, size_t size) const
	{
		return conv_do(to, from, size);
	}


	// -------------------------------------------------------------------
	template<typename String>
	bool Convertor<String>::conv_do(String& t, const char* from, size_t from_size) const
	{
		t.clear();
		typename String::value_type tmp[1025];

		const char * const head=from;
		const char * const end=head+from_size;
		int from_unit=static_cast<int>(sizeof(tmp)/8);
		int errs_lim=static_cast<int>(from_size)/_error_unit;

		int errs=0;
		for(int c=0; from<end; ++c)
		{
			size_t inleft=std::min(from_unit, end-from);
			size_t outleft=sizeof(tmp);
			char *to= tmp;

			errno=0;
			iconv(_cd, const_cast<char**>(&from), &inleft, &to, &outleft);
			if(EILSEQ==errno && ++from && ++errs>=errs_lim)
			{
				return false;
			}
			t.append(tmp, to-tmp);
		}
		return true;
	}


	// -------------------------------------------------------------------
	template<typename String>
	Convertor<String>::~Convertor()
	{
		if((iconv_t)-1!=_cd)
			::iconv_close(_cd);
	}


	// -------------------------------------------------------------------
	template<typename String>
	String easy_conv(const conv_type type, const String& from) throw(bad_convert)
	{
		Convertor<String> cer(type);
		return cer.conv(from);
	}


	// -------------------------------------------------------------------
	template<typename String>
	String easy_conv(const conv_type type, const char* from, size_t size) throw(bad_convert)
	{
		Convertor<String> cer(type);
		return cer.conv(from, size);
	}


	// -------------------------------------------------------------------
	std::string easy_conv(const conv_type type, const char* from, size_t size) throw(bad_convert)
	{
		return easy_conv<std::string>(type, from, size);
	}


	// -------------------------------------------------------------------
	template<typename String>
	String easy_conv(const String& to_type, const String& from_type,
		const String& from) throw(bad_convert)
	{
		Convertor<String> cer(to_type, from_type);
		return cer.conv(from);
	}


	// -------------------------------------------------------------------
	template<typename String>
	String easy_conv(const String& to_type, const String& from_type,
		const char* from, size_t size) throw(bad_convert)
	{
		Convertor<String> cer(to_type, from_type);
		return cer.conv(from, size);
	}

}

namespace Iconv
{
	typedef Convertor<std::string> Conv;
}

#endif //M_iconv_hpp