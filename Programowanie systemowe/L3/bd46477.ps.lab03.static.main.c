// PS IS1 324 LAB02
// Daniel Brzezicki
// bd46477@zut.edu.pl  
#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <limits.h>
#include <grp.h>
#include <stdbool.h> 

int main(int argc, char **argv){
	int c;
	struct utmpx *utmp = getutxent();

	int ngroups=0;

	char *IP;
	struct hostent *host_entry;
	
	bool sHosts=false;
	bool sGroups=false;

	while((c=getopt(argc,argv,"hg"))!=-1){
		switch(c){
			case 'h':
				sHosts=true;
				break;
			case 'g':
				sGroups=true;
				break;
		}

	}
	while(utmp=getutxent()){
		if(utmp->ut_type==USER_PROCESS){
			struct passwd* pw = getpwnam(utmp->ut_user);
			if(argc==1)
				printf("%s\n",pw->pw_name);

			if(sHosts)
				printf("%s (%s)\n",pw->pw_name,utmp->ut_host);
			
			if(sGroups)
				showGroups(pw->pw_name,pw->pw_gid);
		}
	}
	


	return 0;
}
