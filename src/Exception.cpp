#include "Exception.h"

#define ADD_HEADER(name) \
{\
	constexpr char header[] = "[" #name "]: ";\
	if (strcpy_s(_what + i, n - i, header)) return;\
	i += sizeof(header);\
}

char Exception::_what[1024];

Exception::Exception(const char* message, int error_code, const char* file, int line) noexcept
{
	memset(_what, 0, sizeof(_what));

	if (strcpy_s(_what, message)) return;

	unsigned i = strlen(message);
	const int n = sizeof(_what) - 1;

	memset(_what + i, '\n', 2);
	i += 2;

	ADD_HEADER(Error Code);
	_itoa_s(error_code, _what + i - 1, n - i, 10);
	i += strlen(_what + i);

	memset(_what + i, '\n', 2);
	i += 2;

	ADD_HEADER(File);
	if (strcpy_s(_what + i - 1, n - i, file)) return;
	i += strlen(file);

	memcpy(_what + i - 1, " : ", 3);
	_itoa_s(line, _what + i + 2, n - i, 10);
}

const char* Exception::what() const noexcept
{
	return _what;
}

