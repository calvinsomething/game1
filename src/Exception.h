#pragma once

#include "pch.h"

class Exception: public std::exception {
	static char _what[];
public:
	Exception(const char* message, int code, const char* file, int line) noexcept;
	~Exception() {}

	const char* what() const noexcept override;
};

