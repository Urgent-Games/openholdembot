//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose: Debug-DLL for OpenHoldem
//
//******************************************************************************

#define DEBUG_DLL_EXPORTS

#ifdef _DEBUG
// visual leak detector in debug-mode
// https://vld.codeplex.com/
// needs to be included at the very beginning
// http://www.maxinmontreal.com/forums/viewtopic.php?f=338&t=22351
#include <vld.h>			
#endif _DEBUG

#include "debug.h"
#include "afxwin.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "..\Files_DLL\Files.h"
#include "..\..\Shared\CCritSec\CCritSec.h"
#include "..\..\Shared\MagicNumbers\MagicNumbers.h"

FILE *log_fp = NULL;
int session_ID = kUndefined;
CCritSec log_critsec;  // Used to ensure only one thread at a time writes to log file
bool footer_needs_to_be_written = false;
const char *footer = "********************************************************************************\n";

void write_footer_if_necessary() {
  if (footer_needs_to_be_written == false) {
    return;
  }
  // First set footer_needs_to_be_written = false
  // otherwise we get an endless recursion
  footer_needs_to_be_written = false;
  write_log_nostamp(true, footer);
}

char *get_time(char * timebuf) {
  // returns current system time in WH format
  time_t	ltime;
  char tmptime[30];
  time(&ltime);
  ctime_s(tmptime, 26, &ltime);
  tmptime[24] = '\0';
  memcpy(timebuf, tmptime + 20, 4); //yyyy
  *(timebuf + 4) = '-';
  // mm
  if (memcmp(tmptime + 4, "Jan", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '1';
  }
  else if (memcmp(tmptime + 4, "Feb", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '2';
  }
  else if (memcmp(tmptime + 4, "Mar", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '3';
  }
  else if (memcmp(tmptime + 4, "Apr", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '4';
  }
  else if (memcmp(tmptime + 4, "May", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '5';
  }
  else if (memcmp(tmptime + 4, "Jun", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '6';
  }
  else if (memcmp(tmptime + 4, "Jul", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '7';
  }
  else if (memcmp(tmptime + 4, "Aug", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '8';
  }
  else if (memcmp(tmptime + 4, "Sep", 3) == 0) {
    *(timebuf + 5) = '0';
    *(timebuf + 6) = '9';
  }
  else if (memcmp(tmptime + 4, "Oct", 3) == 0) {
    *(timebuf + 5) = '1';
    *(timebuf + 6) = '0';
  }
  else if (memcmp(tmptime + 4, "Nov", 3) == 0) {
    *(timebuf + 5) = '1';
    *(timebuf + 6) = '1';
  }
  else if (memcmp(tmptime + 4, "Dec", 3) == 0) {
    *(timebuf + 5) = '1';
    *(timebuf + 6) = '2';
  }
  *(timebuf + 7) = '-';
  memcpy(timebuf + 8, tmptime + 8, 2); //dd
  *(timebuf + 10) = ' ';
  memcpy(timebuf + 11, tmptime + 11, 8); //HH:mm:ss
  *(timebuf + 19) = '\0';
  return timebuf;
}

char *get_now_time(char * timebuf) {
  // returns current system time as a UNIX style string
  time_t	ltime;
  time(&ltime);
  ctime_s(timebuf, 26, &ltime);
  timebuf[24] = '\0';
  return timebuf;
}

void delete_log() {
  assert(session_ID >= 0);
  // Precondition: log file must not be open
  remove(LogFilePath(session_ID).GetString());
}

void clear_log() {
  stop_log();
  assert(session_ID > 0);
  start_log(session_ID, true);
}

void start_log(int current_session_iD, bool delete_old_log) {

}

void write_log_vl(bool debug_settings_for_this_message, const char* fmt, va_list vl) {

}

void write_log(bool debug_settings_for_this_message, const char* fmt, ...) {

}

void write_log_nostamp(bool debug_settings_for_this_message, const char* fmt, ...) {

}

void stop_log(void) {
  write_footer_if_necessary();
  if (log_fp == NULL) return;
  write_log_separator(k_always_log_basic_information, "LOG FILE CLOSED");
  fclose(log_fp);
  log_fp = NULL;
}

void write_log_separator(bool debug_settings_for_this_message, const char* header_message) {

}