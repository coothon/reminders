#include "files.h"

bool is_folder(const char *folder_path) {
	struct stat sb;
	return ((stat(folder_path, &sb) == 0) && S_ISDIR(sb.st_mode));
}

bool is_file(const char *file_path) {
	// Check if this file exists. A return value of 0 means yes, so we not it.
	return !access(file_path, F_OK);
}

void write_file(const char *file_path, const char *content) {
	FILE *file = fopen(file_path, "w");
	if (!file) return;

	fseek(file, 0UL, SEEK_SET);
	fwrite((void *)content, sizeof(char), strlen(content), file);
	fclose(file);
}
void append_file(const char *file_path, const char *content) {
	if (!is_file(file_path)) return;

	FILE *file = fopen(file_path, "a");
	if (!file) return;

	fseek(file, 0UL, SEEK_END);
	fwrite((void *)content, sizeof(char), strlen(content), file);
	fclose(file);
}

const char *read_entire_file(const char *file_path) {
	if (!is_file(file_path)) return NULL;
	FILE *file;

	file = fopen(file_path, "r");
	if (!file) return NULL;

	size_t file_size = size_file(file);

	void *file_contents = calloc(file_size + 1UL, sizeof(char));
	if (!file_contents) {
		fclose(file);
		return NULL;
	}

	fseek(file, 0L, SEEK_SET);
	fread(file_contents, sizeof(char), file_size, file);
	fclose(file);

	return (const char *)file_contents;
}

size_t size_file(FILE *file) {
	fseek(file, 0L, SEEK_END);
	return (size_t)ftell(file);
}

int count_files_in_dir(const char *dir_path) {
	DIR *dir = opendir(dir_path);
	if (!dir) return -1;

	int            file_count = 0;
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL)
		if (entry->d_type == DT_REG) ++file_count;

	closedir(dir);
	return file_count;
}
