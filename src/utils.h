#pragma once

#include "pch.h"

class RFG
{
	std::mt19937 engine;
	std::unordered_map<long long, std::uniform_real_distribution<float>> distributions;

	RFG() : engine(std::random_device{}()) {}

	long long make_key(float a, float b);

public:
	RFG(const RFG&) = delete;
	RFG operator=(const RFG&) = delete;

	static const RFG& Get();

	void Load(float min, float max);

	float operator()(float min, float max);

	float RunLoaded();
};

