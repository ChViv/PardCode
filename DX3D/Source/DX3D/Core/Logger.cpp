#include <DX3D/Core/Logger.h>
#include <iostream>
dx3d::Logger::Logger(LogLevel loglevel) : m_logLevel(loglevel)
{
	std::clog << " Logger | Zivv Elomina | dx3d Engine | GDENG03 " << "\n";
	std::clog << "------------------------------------------------" << "\n";
}

dx3d::Logger::~Logger()
{
}

void dx3d::Logger::log(LogLevel level, const char* message)
{
	auto logLevelToString = [](LogLevel level)
		{
			switch (level)
			{
			case LogLevel::Info: return "Info";
			case LogLevel::Warning: return "Warning";
			case LogLevel::Error: return "Error";
			default: return "Unkown";
			}
		};

	if (level > m_logLevel) return;
	std::clog << "[DX3D " << logLevelToString(level) << "]: " << message << "\n";
}