// PS IS1 324 LAB03
// Daniel Brzezicki
// bd46477@zut.edu.pl  
#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <grp.h>

void show(char *name,int gid){
	int ngroups=0;			
	getgrouplist(name,gid,NULL,&ngroups);
 	struct group *gr;
	gid_t *groups = malloc(sizeof(*groups) * ngroups);

	if (getgrouplist(name, gid, groups, &ngroups) == -1) {
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
