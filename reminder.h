#ifndef REMINDERS__REMINDER_H_
#define REMINDERS__REMINDER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "files.h"

#define CACHE_FOLDER "/home/guy/.config/reminder_cache"
#define CACHE_FOLDER_SLASH CACHE_FOLDER "/"
#define COUNT_FILE_NAME "count"
#define COUNT_FILE_PATH CACHE_FOLDER_SLASH COUNT_FILE_NAME

#define INT_TO_STR(str, str_size, integer) \
char(str)[(str_size)] = { 0 };             \
snprintf((str), (str_size), "%d", (integer));

#define CACHE_FILE_NAME_PREFIX "reminder_"
#define CACHE_FILE_NAME_POSTFIX ".txt"

#define CACHE_FILE_NAME(var_name, index)                                       \
char(var_name)[1024] = { 0 };                                                   \
snprintf((var_name), 1024, "%s%d%s", CACHE_FOLDER_SLASH CACHE_FILE_NAME_PREFIX, \
	     (index), CACHE_FILE_NAME_POSTFIX);

#define HR_CACHE_COUNT (cache_count + 1)

// Returns:
//  0 => cache folder already exists;
//  1 => cache folder just created;
// -1 => error making cache folder.
int make_cache_dir(void);

// Returns:
// -1 => error reading cache count file.
int read_cache_count(void);

void write_cache_count(int cnt);

// Returns:
// NULL => index not found.
const char *read_reminder(int index);
void        add_reminder(const char *reminder);

void load_all_reminders(const char ***reminders, int *reminders_count);
void remove_all_reminders(void);
void print_all_reminders(void);
void remove_reminder(int index);

#endif // REMINDERS__REMINDER_H_
