#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "fstream"
#include "sstream"
#include "string"

typedef std::vector<std::vector<std::string>> Array2D;

std::unordered_map<std::string, int> class_counts(const Array2D& rows);

std::vector<std::string> unique_vals(const Array2D& rows, int col);

std::vector<std::vector<std::string> > CSV2Vector (const char* file_name);

extern std::vector<std::string> header;
extern long long totalDuration;

class Timer {
private: 
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;

public:
	Timer() {
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		Stop();
	}

	void Stop() const{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
		
		auto duration = end - start;
		std::cout << duration << "us (" << duration * 0.001 << "ms)\n";
	}
};