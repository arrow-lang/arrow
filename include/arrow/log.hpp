// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#pragma once

#include <string>
#include <unordered_map>

#include "cppformat/format.h"

#include "arrow/span.hpp"

namespace arrow {

enum LogLevel {
  LOG_TRACE = 1,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR
};

class Log {
 public:
  static Log& get() noexcept;

  Log(const Log& other) = delete;
  Log(Log&& other) = delete;
  Log& operator=(const Log& other) = delete;
  Log& operator=(Log&& other) = delete;

  /// Count the number of messages of the passed level.
  unsigned count(LogLevel level);

  // General (no location)
  // -------------------------------------------------------------------------|

  /// Log a message at the passed level.
  void log(LogLevel level, const char* format, fmt::ArgList args);

  FMT_VARIADIC(void, log, LogLevel, const char *)

  /// Log a message the error level.
  void error(const char* format, fmt::ArgList args) {
    log(LOG_ERROR, format, args);
  }

  FMT_VARIADIC(void, error, const char *)

  /// Log a message the warn level.
  void warn(const char* format, fmt::ArgList args) {
    log(LOG_WARN, format, args);
  }

  FMT_VARIADIC(void, warn, const char *)

  /// Log a message the info level.
  void info(const char* format, fmt::ArgList args) {
    log(LOG_INFO, format, args);
  }

  FMT_VARIADIC(void, info, const char *)

  /// Log a message the debug level.
  void debug(const char* format, fmt::ArgList args) {
    log(LOG_DEBUG, format, args);
  }

  FMT_VARIADIC(void, debug, const char *)

  /// Log a message the trace level.
  void trace(const char* format, fmt::ArgList args) {
    log(LOG_TRACE, format, args);
  }

  FMT_VARIADIC(void, trace, const char *)

  // File/Row/Column specific
  // -------------------------------------------------------------------------|

  /// Log a message at the passed level.
  void log(LogLevel level, Span span, const char* format, fmt::ArgList args);

  FMT_VARIADIC(void, log, LogLevel, Span, const char *)

  /// Log a message the error level.
  void error(Span span, const char* format, fmt::ArgList args) {
    log(LOG_ERROR, span, format, args);
  }

  FMT_VARIADIC(void, error, Span, const char *)

  /// Log a message the warn level.
  void warn(Span span, const char* format, fmt::ArgList args) {
    log(LOG_WARN, span, format, args);
  }

  FMT_VARIADIC(void, warn, Span, const char *)

  /// Log a message the info level.
  void info(Span span, const char* format, fmt::ArgList args) {
    log(LOG_INFO, span, format, args);
  }

  FMT_VARIADIC(void, info, Span, const char *)

  /// Log a message the debug level.
  void debug(Span span, const char* format, fmt::ArgList args) {
    log(LOG_DEBUG, span, format, args);
  }

  FMT_VARIADIC(void, debug, Span, const char *)

  /// Log a message the trace level.
  void trace(Span span, const char* format, fmt::ArgList args) {
    log(LOG_TRACE, span, format, args);
  }

  FMT_VARIADIC(void, trace, Span, const char *)

 private:
  Log();

  std::unordered_map<int, unsigned> _counters;
};

}  // namespace arrow
