#ifndef REMINDERS__FILES_H_
#define REMINDERS__FILES_H_

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

bool        is_folder(const char *folder_path);
bool        is_file(const char *file_path);
void        write_file(const char *file_path, const char *content);
void        append_file(const char *file_path, const char *content);
const char *read_entire_file(const char *file_path);
size_t      size_file(FILE *file);
int         count_files_in_dir(const char *dir);
#endif // REMINDERS__FILES_H_
