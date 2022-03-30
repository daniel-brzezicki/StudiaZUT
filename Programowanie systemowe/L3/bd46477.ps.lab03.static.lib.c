// PS IS1 324 LAB03
// Daniel Brzezicki
// bd46477@zut.edu.pl  
#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <grp.h>

void showGroups(char *name,int ngroups){
	//int ngroups=pw->pw_gid;
 	struct group *gr;
	gid_t *groups = malloc(sizeof(*groups) * ngroups);
						

	if (getgrouplist(name, ngroups, groups, &ngroups) == -1) {
		fprintf(stderr, "getgrouplist() returned -1; ngroups = %d\n", ngroups);
		return 0;
    }
						
	printf("%s [",name);

    for (int j = 0; j < ngroups; j++) {
    	gr = getgrgid(groups[j]);
        if (gr != NULL)
        	printf(" %s ", gr->gr_name);
	}
	printf("]\n");
}
