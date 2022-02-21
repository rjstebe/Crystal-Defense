#pragma once

#include "Manager.h"

namespace df {

const std::string LOGFILE_NAME = "dragonfly.log"; // File name to write logs to.

#define LM df::LogManager::getInstance() // Two-letter acronym.

class LogManager : public Manager {
private:
	LogManager();                      // Private (a singleton).
	LogManager(LogManager const&);     // No copying.
	void operator=(LogManager const&); // No assignment.
	std::string m_file_name = LOGFILE_NAME; // Determines the file to print messages to.
	int m_log_level = 1;                    // Determines verbosity of log messages.
	bool m_do_flush = false;                // True if fflush after each write.
	bool m_log_time_string = false;         // True if print time string before each write.
	bool m_log_step_count = false;          // True if print step count before each write.
	FILE* m_p_f = NULL;                     // Pointer to logfile structure.
public:
	// If logfile is open, close it.
	~LogManager();
	
	// Get the one and only instance of the LogManager.
	static LogManager& getInstance();

	// Start up the LogManager (open logfile "dragonfly.log").
	int startUp();

	// Shut down the LogManager (close logfile).
	void shutDown();

	// Set the file name to print logs to. (returns -1 and fails if LogManager is running).
	int setFileName(std::string filename);

	// Set the verbosity of the LogManager.
	void setLogLevel(int log_level);

	// Set flush of logfile after each write.
	void setFlush(bool do_flush = true);

	// Set print of time string before each write.
	void setTimeString(bool log_time_string = true);

	// Set print of step count before each write.
	void setStepCount(bool log_step_count = true);

	// Write to logfile.
	// Only write if indicated log level >= LogManager log level.
	// Supports printf() formatting.
	// Return number of bytes written (excluding pre-pends), -1 if error.
	int writeLog(int log_level, const char* fmt, ...) const;

	// Write to logfile.
	// Supports printf() formatting.
	// Return number of bytes written (excluding pre-pends), -1 if error.
	int writeLog(char const* fmt, ...) const;

	// Write to logfile.
	// Only write if indicated log level >= LogManager log level.
	// Supports printf() formatting via a va_list.
	// Return number of bytes written (excluding pre-pends), -1 if error.
	int writeLog(int log_level, const char* fmt, va_list args) const;
};

} // end of namespace df
