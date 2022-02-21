#include <stdarg.h>

#include "utility.h"
#include "LogManager.h"
#include "GameManager.h"

// Called only by getInstance().
df::LogManager::LogManager() {}

// If logfile is open, close it.
df::LogManager::~LogManager() {
	if (m_p_f != NULL) {
		fclose(m_p_f);
	}
}

// Get the one and only instance of the LogManager.
df::LogManager& df::LogManager::getInstance() {
	static df::LogManager& instance = *new LogManager();
	return instance;
}

// Start up the LogManager (open the target logfile).
int df::LogManager::startUp() {
	m_p_f = fopen(m_file_name.c_str(), "w");
	if (m_p_f == NULL) {
		return -1;
	}
	setType("LogManager");
	return Manager::startUp();
}

// Shut down the LogManager (close logfile).
void df::LogManager::shutDown() {
	Manager::shutDown();
	m_file_name = LOGFILE_NAME;
	m_log_level = 1;
	m_do_flush = false;
	m_log_time_string = false;
	m_log_step_count = false;
	fclose(m_p_f);
}

// Set the file name to print logs to. (returns -1 and fails if LogManager is running).
int df::LogManager::setFileName(std::string filename) {
	if (isStarted()) {
		return -1;
	}
	m_file_name = filename;
	return 0;
}

// Set the verbosity of the LogManager.
void df::LogManager::setLogLevel(int log_level) {
	m_log_level = log_level;
}

// Set flush of logfile after each write.
void df::LogManager::setFlush(bool do_flush) {
	m_do_flush = do_flush;
}

// Set print of time string before each write.
void df::LogManager::setTimeString(bool log_time_string) {
	m_log_time_string = log_time_string;
}

// Set print of step count before each write.
void df::LogManager::setStepCount(bool log_step_count) {
	m_log_step_count = log_step_count;
}

// Write to logfile.
// Only write if indicated log level >= LogManager log level.
// Supports printf() formatting.
// Return number of bytes written (excluding pre-pends), -1 if error.
int df::LogManager::writeLog(int log_level, const char* fmt, ...) const {
	va_list args;
	va_start(args, fmt);
	int returnVal = writeLog(log_level, fmt, args);
	va_end(args);
	return returnVal;
}

// Write to logfile.
// Supports printf() formatting.
// Return number of bytes written (excluding pre-pends), -1 if error.
int df::LogManager::writeLog(const char* fmt, ...) const {
	va_list args;
	va_start(args, fmt);
	int returnVal = writeLog(INT_MAX, fmt, args);
	va_end(args);
	return returnVal;
}

// Write to logfile.
// Only write if indicated log level >= LogManager log level.
// Supports printf() formatting via a va_list.
// Return number of bytes written (excluding pre-pends), -1 if error.
int df::LogManager::writeLog(int log_level, const char* fmt, va_list args) const {
	// Only print if LogManager was set up correctly
	if (!isStarted()) {
		return -1;
	}

	// Only print message when verbosity level high enough
	if (log_level < m_log_level) {
		return 0;
	}

	// Print out pre-pends
	if (m_log_time_string) {
		fprintf(m_p_f, "%s ", df::getTimeString());
	}
	if (m_log_step_count) {
		fprintf(m_p_f, "(%d) ", GM.getGameLoopCount());
	}
	fprintf(m_p_f, "- ");

	// Print out fmt with args
	int bytes = vfprintf(m_p_f, fmt, args);

	// Append newline character
	fprintf(m_p_f, "\n");
	// Flush file buffer if option is enabled
	if (m_do_flush) {
		fflush(m_p_f);
	}
	return bytes;
}
