#!/bin/bash
#SO IS1 210B LAB08
#Daniel Brzezicki
#bd46477@zut.edu.pl

case $1 in
"-p");;
"-u");;
*)
echo "Bledne uzycie. Dostepne operatory -p -u"
exit 0
esac

for dir in `ls -d /proc/* | sort -V`
do
	if [ -d $dir ]
	then
		if [ -e /$dir/status ]
		then
			if [ $1 == "-p" ]
			then
			pid=`awk 'NR==6' $dir/status | cut -d: -d '	' -f2`
			ppid=`awk 'NR==7' $dir/status | cut -d: -d '	' -f2`
			uid=`awk 'NR==9' $dir/status | cut -d: -d '	' -f2`
			username=`getent passwd "$uid" | cut -d: -f1`
			pname=`awk 'NR==1' $dir/status | cut -d: -d '	' -f2`
			echo "$pid $ppid $uid ($username) $pname"
			elif [ $1 == "-u" ]
			then
				uid=`awk 'NR==9' $dir/status | cut -d: -d '	' -f2`
				username=`getent passwd "$uid" | cut -d: -f1`
				if [ $EUID -eq $uid ]
				then
				pid=`awk 'NR==6' $dir/status | cut -d: -d '	' -f2` 
				ppid=`awk 'NR==7' $dir/status | cut -d: -d '	' -f2`
				pname=`awk 'NR==1' $dir/status | cut -d: -d '	' -f2`
				if [ -e /$dir/cwd ]
				then
				kat=`readlink /$dir/cwd`
				fi
				echo "$pid $pname $kat"
				fi
			fi
		fi
	fi
done
