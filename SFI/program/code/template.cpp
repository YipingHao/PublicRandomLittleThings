#include"template.h"
#include<string.h>
namespace TemplateSelf
{
	static inline bool _hx_sc_is_empty(const StringConst& s) {
		return s.length() == 0;
	}

	StringConst::StringConst(const char* str)
		: array<char>()
	{
		if (!str || *str == '\0') {
			// 空串：保持 Length=0, content=NULL
			return;
		}
		size_t len = ::strlen(str);
		// 直接分配 len+1（含 '\0'），绕过 array<char>::Malloc 以避免多余循环
		content = (char*)malloc(len + 1);
		if (!content) ::abort();
		memcpy(content, str, len + 1); // 包含终止符 '\0'
		Length = len + 1;
	}

	StringConst& StringConst::operator=(const char* str)
	{
		if (!str || *str == '\0') {
			// 目标为空串：释放为统一“空”表示
			this->Free();
			return *this;
		}
		size_t len = ::strlen(str);
		// 需要大小 = len+1
		if (Length != len + 1) {
			this->Free();
			this->Malloc(len + 1);
		}
		for (size_t i = 0; i < len; ++i) content[i] = str[i];
		content[len] = '\0';
		return *this;
	}
	bool StringConst::operator==(const StringConst& other) const
	{
		size_t L = length();
		size_t R = other.length();
		if (L != R) return false;
		if (L == 0) return true; // 都是空串（非唯一性）
		// 比较前 L 个字节（不含终止符），可改为含 '\0' 也一致
		return ::memcmp(content, other.content, L) == 0;
	}
	bool StringConst::operator!=(const StringConst& other) const
	{
		return !(*this == other);
	}
	bool StringConst::operator==(const char* other) const
	{
		if (!other || *other == '\0')
			return _hx_sc_is_empty(*this);
		size_t L = length();
		if (L == 0) return false;
		size_t R = ::strlen(other);
		if (L != R) return false;
		return ::memcmp(content, other, L) == 0;
	}
	bool StringConst::operator!=(const char* other) const
	{
		return !(*this == other);
	}
}
