#include <stdio.h>
#include <string.h>

#include "reminder.h"

int cache_count = 0;

void print_help(void) {
	puts("\033[1mUsage:");
	puts("  $ reminders [option] <option arguments>\n");
	puts("Options:");
	puts("  add      Add a reminder.");
	puts("  remove   Remove reminder from a list.");
	puts("  clear    Remove all reminders.");
	puts("  help     Show help.");
	puts("  list     Show reminders.");
	puts("  rem      Shorthand for remove.\n");
	puts("  any      Are there any reminders?\n");
	puts("When no argument is given, behaviour defaults to `list.'\033(B\033[m");
}

int main(int argc, char **argv) {
	make_cache_dir();
	cache_count = read_cache_count();
	if (cache_count == -1) {
		cache_count = 0;
		write_cache_count(cache_count);
	}

	if (argc == 2) {
		if (strcmp(argv[1], "help") == 0) {
			print_help();
		} else if (strcmp(argv[1], "list") == 0) {
			if (cache_count < 1) {
				fprintf(stderr, "[ERROR]: No reminders to list.\n");
				return 1;
			}
			print_all_reminders();
		} else if (strcmp(argv[1], "any") == 0) {
			return cache_count < 1;
		} else if (strcmp(argv[1], "add") == 0) {
			puts("What shall I remember for you?");
			char buf[2048] = { 0 };
			scanf("%s", buf);
			add_reminder(buf);
		} else if (strcmp(argv[1], "remove") == 0 ||
		           strcmp(argv[1], "rem") == 0) {
			if (cache_count < 1) {
				fprintf(stderr, "[ERROR]: No reminders to remove.\n");
				return 1;
			}
			int rem = 0;
			print_all_reminders();
			printf("\nThe number of the reminder to remove: ");
			scanf("%d", &rem);
			if (rem < 1 || rem > cache_count) {
				fprintf(stderr, "[ERROR]: Number must be one listed above.\n");
				return 1;
			}
			remove_reminder(rem);
		} else if (strcmp(argv[1], "clear") == 0) {
			if (cache_count < 1) {
				fprintf(stderr, "[ERROR]: No reminders to remove.\n");
				return 1;
			}
			remove_all_reminders();
			puts("Reminders cleared.");
		} else {
			fprintf(stderr, "[ERROR]: Unknown argument `%s.'\n", argv[1]);
			return 1;
		}
		return 0;
	} else if (argc > 2) {
		if (strcmp(argv[1], "add") == 0) {
			char buf[2048] = { 0 };
			strcat(buf, argv[2]);
			for (int i = 3; i < argc; ++i) {
				strcat(buf, " ");
				strcat(buf, argv[i]);
			}
			add_reminder(buf);
		} else {
			fprintf(stderr, "[ERROR]: Invalid number of arguments.\n");
		}
	} else {
		if (cache_count < 1) {
			fprintf(stderr, "[ERROR]: No reminders to list.\n");
			return 1;
		}
		print_all_reminders();
	}

	return 0;
}
