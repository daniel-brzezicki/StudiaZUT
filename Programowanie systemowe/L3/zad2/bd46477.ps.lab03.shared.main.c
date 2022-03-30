// PS IS1 324 LAB03
// Daniel Brzezicki
// bd46477@zut.edu.pl  
  
#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <grp.h>
#include <dlfcn.h>
#include <stdbool.h> 

int main(int argc, char **argv){
	int c;
	struct utmpx *utmp = getutxent();
	int ngroups=0;

	void *uchwyt = dlopen("./zad2_lib.so",RTLD_LAZY);

	bool loaded=true;
	void (*pokaz) (char*, int);
	if(uchwyt==NULL){
		loaded=false;
		perror("dlopen");
	}
	else{
		pokaz = dlsym(uchwyt, "show");
		if (!pokaz)
		{
			loaded=false;
			printf("Nieudane: %s\n",dlerror());
	   	  	return 2;
    		}
		
	}

	


	char *IP;
	struct hostent *host_entry;

	bool sHosts=false;
	bool sGroups=false;
	if(loaded){
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
}


	while(utmp=getutxent()){
		if(utmp->ut_type==USER_PROCESS){
			struct passwd* pw = getpwnam(utmp->ut_user);
			if(!sHosts&&!sGroups)
				printf("%s\n",pw->pw_name);
			
			if(sHosts)
				printf("%s (%s)\n",pw->pw_name,utmp->ut_host);
			
			if(sGroups)
				pokaz(pw->pw_name,pw->pw_gid);

		}
	}
	if(uchwyt!=NULL)
		dlclose(uchwyt);
	return 0;
}
