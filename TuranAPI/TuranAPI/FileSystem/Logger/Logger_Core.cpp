#include "Logger_Core.h"
using namespace TuranAPI::File_System;
#include <string>
//Please don't move the above classes anywhere! I just want to use them here, so don't need to worry about wrong usage


using namespace TuranAPI::File_System;
using namespace TuranAPI::Logging;

Logger* Logger::SELF = nullptr;
Logger::Logger(): MainLogFile_Path("C:/dev/TuranEngine/logs.txt", LASTUSEDALLOCATOR), WarningLogFile_Path("C:/dev/TuranEngine/warnings.txt", LASTUSEDALLOCATOR),
ErrorLogFile_Path("C:/dev/TuranEngine/errors.txt", LASTUSEDALLOCATOR), NotCodedLogFile_Path("C:/dev/TuranEngine/notcodedpaths.txt"), LOGs(LASTUSEDALLOCATOR, 100, 10000)
{
	TuranAPI::File_System::FileSystem::Write_TextFile("TuranAPI: Logging Started!", MainLogFile_Path, false);
	TuranAPI::File_System::FileSystem::Write_TextFile("TuranAPI: Logging Started!", WarningLogFile_Path, false);
	TuranAPI::File_System::FileSystem::Write_TextFile("TuranAPI: Logging Started!", ErrorLogFile_Path, false);
	TuranAPI::File_System::FileSystem::Write_TextFile("TuranAPI: Logging Started!", NotCodedLogFile_Path, false);
}


void Logger::Write_LOGs_toTextFiles() {
	if (LOGs.size() == 0) {
		return;
	}
	String MainLogFile_Text, ErrorLogFile_Text, WarningLogFile_Text, NotCodedLogFile_Text;

	for (size_t i = 0; i < LOGs.size(); i++) {
		LOG* log_data = &LOGs[i];
		switch (log_data->TYPE)
		{
		case LOG_TYPE::CRASHING_ERROR:
		case LOG_TYPE::ERROR:
			MainLogFile_Text.append(log_data->TEXT);
			ErrorLogFile_Text.append(log_data->TEXT);
			break;
		case LOG_TYPE::WARNING:
			MainLogFile_Text.append(log_data->TEXT);
			WarningLogFile_Text.append(log_data->TEXT);
			break;
		case LOG_TYPE::NOT_CODEDPATH:
			MainLogFile_Text.append(log_data->TEXT);
			ErrorLogFile_Text.append(log_data->TEXT);
			NotCodedLogFile_Text.append(log_data->TEXT);
			break;
		case LOG_TYPE::STATUS:
			MainLogFile_Text.append(log_data->TEXT);
			break;
		default:
			break;
		}
		delete log_data->TEXT;
		log_data->TEXT = nullptr;
	}
	LOGs.clear();

	TuranAPI::File_System::FileSystem::Write_TextFile(&MainLogFile_Text, SELF->MainLogFile_Path, true);
	TuranAPI::File_System::FileSystem::Write_TextFile(&ErrorLogFile_Text, SELF->ErrorLogFile_Path, true);
	TuranAPI::File_System::FileSystem::Write_TextFile(&WarningLogFile_Text, SELF->WarningLogFile_Path, true);
	TuranAPI::File_System::FileSystem::Write_TextFile(&NotCodedLogFile_Text, SELF->NotCodedLogFile_Path, true);
}

void Logger::Log_CrashingError(const char* log) {
	LOG log_data;
	unsigned int log_length = 0;
	while (log[log_length] != 0) {
		log_length++;
	}
	log_length += 1;
	log_data.TEXT = new char[log_length];
	for (unsigned int i = 0; i < log_length; i++) {
		log_data.TEXT[i] = log[i];
	}
	log_data.TYPE = LOG_TYPE::CRASHING_ERROR;
	LOGs.push_back(log_data);
	Write_LOGs_toTextFiles();
	TuranAPI::Breakpoint(log);
}

void Logger::Log_HandledError(const char* log) {
	LOG log_data;
	unsigned int log_length = 0;
	while (log[log_length] != 0) {
		log_length++;
	}
	log_length += 1;
	log_data.TEXT = new char[log_length];
	for (unsigned int i = 0; i < log_length; i++) {
		log_data.TEXT[i] = log[i];
	}
	log_data.TYPE = LOG_TYPE::ERROR;
	LOGs.push_back(log_data);

	std::cout << log_data.TEXT;
}

void Logger::Log_Warning(const char* log) {
	LOG log_data;
	unsigned int log_length = 0;
	while (log[log_length] != 0) {
		log_length++;
	}
	log_length += 1;
	log_data.TEXT = new char[log_length];
	for (unsigned int i = 0; i < log_length; i++) {
		log_data.TEXT[i] = log[i];
	}
	log_data.TYPE = LOG_TYPE::WARNING;
	LOGs.push_back(log_data);
	 
	std::cout << log_data.TEXT;
}

void Logger::Log_Status(const char* log) {
	LOG log_data;
	unsigned int log_length = 0;
	while (log[log_length] != 0) {
		log_length++;
	}
	log_length += 1;
	log_data.TEXT = new char[log_length];
	for (unsigned int i = 0; i < log_length; i++) {
		log_data.TEXT[i] = log[i];
	}
	log_data.TYPE = LOG_TYPE::STATUS;
	LOGs.push_back(log_data);
	std::cout << "Status: " << log_data.TEXT;
}

void Logger::Log_NotCodedPath(const char* log, bool stop_running) {
	if (stop_running) {
		Write_LOGs_toTextFiles();
	}
	LOG log_data;
	unsigned int log_length = 0;
	while (log[log_length] != 0) {
		log_length++;
	}
	log_length += 1;
	log_data.TEXT = new char[log_length];
	for (unsigned int i = 0; i < log_length; i++) {
		log_data.TEXT[i] = log[i];
	}
	log_data.TYPE = LOG_TYPE::NOT_CODEDPATH;
	LOGs.push_back(log_data);

	if (stop_running) {
		Write_LOGs_toTextFiles();
		TuranAPI::Breakpoint(log);
	}
}