// PS IS1 324 LAB04
// Daniel Brzezicki
// bd46477@zut.edu.pl
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include <stdbool.h>


int main(int argc, char **argv){
  int times=1;

  int c;
  bool show=false;
	bool customTimes=false;

	while((c=getopt(argc,argv,"+vt:"))!=-1){
		switch(c){
			case 'v':
				show=true;
				break;
			case 't':
				customTimes=true;
        times=atoi(optarg);
        printf("%d",times);

				break;
		}
	}

  char command[] = " ";

  int commandPlace = 0;
  if(show && customTimes)
    commandPlace=4;
  else if(!show && customTimes)
    commandPlace=3;
  else if(show && !customTimes)
    commandPlace=2;
  else
    commandPlace=1;


  for(int i=commandPlace;i<argc;i++){
    strcat(command,argv[i]);
    strcat(command," ");
}

if(command==" "){
  return 0;
}
  char rest[] = " > /dev/null 2>&1";
  if(!show)
    strcat(command, rest);

  //printf("%s\n\n",command);

  int i;
  pid_t pPid = getpid();
  pid_t cPid=-1;
  struct rusage _rusage;
  int status;

  double sumTime=0;
  double sumUserTime=0;
  double sumSysTime=0;

  for(int i=0;i<times;i++){
    if(getpid()==pPid)
      cPid=fork();

      if(cPid==0){
        system(command);
        exit(0);
      }
      else{
        clock_t start = clock();
        wait4(cPid,&status,0,&_rusage);
        clock_t end = clock();

        printf("---------- wykonanie: %d\n", i+1);

        double t = ((double) (end-start)) /CLOCKS_PER_SEC;
        printf("realTime: %f s.\n",t);
        sumTime+=t;

        long int sec=_rusage.ru_utime.tv_sec;
        long int secMs=_rusage.ru_utime.tv_usec;
        double userTime = sec + (secMs/1000000.0);
        //printf("%f\n",userTime);
        printf("userTime: %ld.%06ld s.\n", sec, secMs);
        sumUserTime+=userTime;


        sec = _rusage.ru_stime.tv_sec;
        secMs = _rusage.ru_stime.tv_usec;
        double sysTime = sec + (secMs/1000000.0);
        //printf("%f\n",sysTime);
        printf("sysTime: %ld.%06ld s. \n", _rusage.ru_stime.tv_sec, _rusage.ru_stime.tv_usec);
        //printf("process %ld\n", (long)cPid);
        sumSysTime+=sysTime;

      }
  }
  if(times>1)
    printf("\n=============\nAvg realTime: %fs.\nAvg userTime: %fs.\nAvg sysTime: %fs.\n", sumTime/times, sumUserTime/times, sumSysTime/times );


	return 0;
}
