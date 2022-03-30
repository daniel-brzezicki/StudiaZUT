// PS IS1 324 LAB02
// Daniel Brzezicki
// bd46477@zut.edu.pl  
#include <utmpx.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main(){
	struct utmpx *utmp = getutxent();

	while(utmp=getutxent()){
		if(utmp->ut_type==USER_PROCESS){
			struct passwd* pw = getpwnam(utmp->ut_user);

   			printf("login name: %s\nuser id: %d\n",
			pw->pw_name,
			pw->pw_uid
			);
		}
	}


	return 0;
}
