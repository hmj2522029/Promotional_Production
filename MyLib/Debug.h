#pragma once
//#include <iostream>
#include <cstdio>

// デバッグ用のコンソール出力
class Debug
{
private:
	static FILE* m_stream;

public:
	static void Initialize();
	static void Finalize();

	template <typename ... Args>
	static void Log(const char* format, Args const & ... args)
	{
#ifdef _DEBUG
		std::printf(format, args...);
#endif
	}
};
