#ifndef DETECT_DATA_POOL_H_
#define DETECT_DATA_POOL_H_

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

namespace PDF_CHECK {

	struct Data {
		static const unsigned int kCacheSize = 10240; /* when file is smaller than 10KB, the data will be stored in _data (此时直接在栈_data中存储文档内容) */
		unsigned int _begin;
		unsigned int _end; /* position of '\0' */
		char _data[kCacheSize];
		Data() : _begin{ 0 }, _end{ 0 } {}
		void set_boader(unsigned int begin, unsigned int end) { /* 记录_data中存储的是文中的哪一部分数据：[_begin, _end) */
			_begin = begin;
			_end = end;
		}
	};

	class DataPool {
	private:
		static const unsigned int kCacheSize = Data::kCacheSize;
	public:
		explicit DataPool(const std::wstring& path);
		~DataPool();

		bool Read(const std::wstring& path);
		void Show() const;
		unsigned int Size() const { // 返回文件数据的字节数
			return _file_size;
		}
		std::vector<char> get_data(unsigned int begin, unsigned int end) const; /* 读取范围：[begin, end] 注意vector不要太长,数据太大时，做上层封装，而不是一次性读到一个vector中 */
		char next() const; /* 会修改_current_pos 指针 */
		char at(unsigned int) const;
		char operator[](unsigned int) const; /* 这是个假的operator[]，因为返回值不是引用，所以只能读不能修改 */
		unsigned int current_pos() const { return _current_pos; }

	protected:
		void set_pos(unsigned int pos = 0); /* 指定_current_pos的位置 */

	private:
		bool saved_in_stack() const; /* is data saved in _data ? */
		bool _read(const std::wstring& path);

	private:
		std::wstring _path;
		std::unique_ptr<std::ifstream> _file;
		std::filebuf* _pbuf{ nullptr };
		size_t _file_size{ 0 };
		mutable Data _cache;
		mutable unsigned int _current_pos{ 0 };
	};
}

#endif /* end of DETECT_DATA_POOL_H_ */