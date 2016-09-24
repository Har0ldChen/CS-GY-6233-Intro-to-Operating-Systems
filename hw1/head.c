#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void head(int fd, int num, char *name) {
	int l, i;
	int n = read(fd, buf, sizeof(buf));

	i = l = 0;

	while (i < n && l < num) {
		if (buf[i] == '\n') l++;
		i++;
		if (l < num) printf(1, "%c", buf[i]);
	}
}

int main(int argc, char *argv[]) {
	int fd, i, num;

	if (argc <= 1) {
		head(0, 10, "");
		exit();
	}

	if (argc == 2) {
		if ((fd = open(argv[1], 0)) < 0) {
			printf(1, "head: cannot open %s\n", argv[1]);
			exit();
		}
		head(fd, 10, argv[1]);
		close(fd);
		exit();
	}

	if (argv[1][0] == '-') argv[1][0] = '0';
	num = atoi(argv[1]);

	for (i = 2; i < argc; i++) {
		if ((fd = open(argv[i], 0)) < 0) {
			printf(1, "head: cannot open %s\n", argv[i]);
			exit();
		}
		head(fd, num, argv[i]);
		close(fd);
	}
	exit();
}