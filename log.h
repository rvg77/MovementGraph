#pragma once

#include <stdio.h>
#include <stdarg.h>


void printLog(const char* Achar, 
              bool        isPrintToStdOutput = true,
              bool        isPrintToFile      = true,
              const char* timeLog            = "",
              const char* logFilePath        = "log/log.log", 
              const char* fileName           = "", 
              int         numberLine         = 0, 
              ...) {

  FILE * log = fopen(logFilePath, "a");
  if (!log) return;

  va_list args;
  va_start(args, Achar);

  if (isPrintToFile) {
    fprintf(log, "Time: %s \n File: %s \n Line: %d \n Message: ", timeLog, fileName, numberLine);
    vfprintf(log, Achar, args);
    fprintf(log, "\n\n");
  }

  if (isPrintToStdOutput) {
    printf("Time: %s \n File: %s \n Line: %d \n Message: ", timeLog, fileName, numberLine);
    vprintf(Achar, args);
    printf("\n\n");
  }

  fclose(log);
  va_end(args);
}

#define Log(s) \
  printLog(true, true, asctime(localtime(&time(NULL))), "log/" + __FILE__ + ".log", __FILE__, __LINE__); \
  printLog(true, true, asctime(localtime(&time(NULL))), "log/log.log", __FILE__, __LINE__);