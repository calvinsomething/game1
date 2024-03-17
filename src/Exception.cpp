#include "Exception.h"

char Exception::_what[500];

Exception::Exception(const char* message, int code, const char* file, int line) noexcept
{
	memset(_what, 0, sizeof(_what));

	if (strcpy_s(_what, message)) return;

	int i = strlen(message);
	const int n = sizeof(_what) - 1;

	_what[i++] = '\n';
	if (strcpy_s(_what + i, n - i, "error code ")) return;
	i += sizeof("error code ");
	_itoa_s(code, _what + i - 1, n - i, 10);
	i += strlen(_what + i);

	memset(_what + i, '\n', 2);
	i += 2;

	if (strcpy_s(_what + i, n - i, "[FILE]: ")) return;
	i += sizeof("[FILE]: ");
	if (strcpy_s(_what + i - 1, n - i, file)) return;
	i += strlen(file);

	memset(_what + i - 1, '\n', 2);
	i++;

	if (strcpy_s(_what + i, n - i, "[LINE]: ")) return;
	i += sizeof("[LINE]: ");
	_itoa_s(line, _what + i - 1, n - i, 10);
}

const char* Exception::what() const noexcept
{
	return _what;
}

