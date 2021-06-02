

#include <stdlib.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#include <grp.h>

#define MAXGROUPS 100

int
builtin_gid(int argc, char *argv[])
{
	int i = 0;
	int gid;
	int s_gid[MAXGROUPS];
	int n_gr = 0;
	struct group *grp;

	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return EXIT_FAILURE;
	}

	grp = getgrgid(getgid());

	printf("gid=%d(%s) ", grp->gr_gid, grp->gr_name);
	
	n_gr = getgroups(MAXGROUPS, s_gid);

	printf("groups=");
	for( i = 0; i < n_gr; i++ ){
		grp = getgrgid(s_gid[i]);
		printf("%d(%s)", grp->gr_gid, grp->gr_name);
		if( i+1 < n_gr ){
			printf(",");
		}
	}
	printf("\n");
	

	return EXIT_SUCCESS;
}
