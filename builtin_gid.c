#include "minish.h"

int builtin_gid(int argc, char *argv[]) {
	int i = 0;
	int gid;
	int s_gid[MAXGROUPS];
	int n_gr = 0;
	struct group *grp;

	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		errno = E2BIG;
		return errno;
	}

	grp = getgrgid(getgid());

	printf("gid=%d(%s) ", grp->gr_gid, grp->gr_name);
	
	n_gr = getgroups(MAXGROUPS, s_gid);

	printf("groups=");
	for( i = 0; i < n_gr-1; i++ ){
		grp = getgrgid(s_gid[i]);
		printf("%d(%s), ", grp->gr_gid, grp->gr_name);
	}
	grp = getgrgid(s_gid[i]);
	printf("%d(%s)\n", grp->gr_gid, grp->gr_name);
	
	return EXIT_SUCCESS;
}

