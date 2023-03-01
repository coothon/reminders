#include "reminder.h"

extern int cache_count;

int make_cache_dir(void) {
	if (is_folder(CACHE_FOLDER)) return 0;
	return !mkdir(CACHE_FOLDER, 0777) ? 1 : -1;
}

int read_cache_count(void) {
	if (!is_file(COUNT_FILE_PATH)) return -1;

	const char *count = read_entire_file(COUNT_FILE_PATH);

	int count_int = atoi(count);
	if (count_int < 0) return -1;

	free((void *)count);
	return count_int;
}

void write_cache_count(int cnt) {
	INT_TO_STR(buf, 32, cnt)
	write_file(COUNT_FILE_PATH, buf);
}

const char *read_reminder(int index) {
	if (index < 1 || index > HR_CACHE_COUNT) return NULL;
	CACHE_FILE_NAME(reminder_path, index)
	return read_entire_file(reminder_path);
}

void add_reminder(const char *reminder) {
	++cache_count;
	CACHE_FILE_NAME(reminder_path, cache_count)
	write_file(reminder_path, reminder);
	write_cache_count(cache_count);
}

void load_all_reminders(const char ***reminders, int *reminders_count) {
	int total_count = count_files_in_dir(CACHE_FOLDER) - 1;
	if (total_count < 1) { // If there are no reminders.
		*reminders       = NULL;
		*reminders_count = 0;
		return;
	}

	*reminders_count = 0;
	*reminders       = (const char **)calloc(total_count, sizeof(intptr_t));

	for (int i = 0; (i + 1) <= total_count; ++i) {
		(*reminders)[i] = read_reminder(i + 1);
		++(*reminders_count);
	}
}

void remove_all_reminders(void) {
	int rem_count = count_files_in_dir(CACHE_FOLDER) - 1;
	if (rem_count < 1) return;

	for (int i = 0; (i + 1) <= rem_count; ++i) {
		CACHE_FILE_NAME(reminder_i, (i + 1))

		remove(reminder_i);
	}

	cache_count = 0;
	write_cache_count(cache_count);
}

void print_all_reminders(void) {
	const char **reminders = NULL;
	int          count     = 0;
	load_all_reminders(&reminders, &count);
	if (count < 1) return;

	for (int i = 0; (i + 1) <= count; ++i) {
		const char *str = reminders[i];
		printf("[%d] %s\n", i + 1, str);
		free((void *)str);
	}

	free((void *)reminders);
}

void remove_reminder(int index) {
	const char **reminders = NULL;
	int          count     = 0;
	load_all_reminders(&reminders, &count);
	if (count < 1 || index < 1 || index > count) return;

	remove_all_reminders();

	free((void *)(reminders[--index]));
	reminders[index] = NULL;

	int real_i = 0;
	for (int i = 0; (i + 1) <= count; ++i, ++real_i) {
		if (i == index) {
			--real_i;
			continue;
		}

		CACHE_FILE_NAME(reminder_i, (real_i + 1))

		write_file(reminder_i, reminders[i]);
		free((void *)reminders[i]);
		reminders[i] = NULL;
	}
	free((void *)reminders);
	reminders = NULL;

	cache_count = real_i;
	write_cache_count(cache_count);
}
