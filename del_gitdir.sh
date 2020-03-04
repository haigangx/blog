#!/bin/bash
sub_dir=`ls`
for i in $sub_dir; do
	if [ -d $i ]; then
		cd $i;
		echo "in $i";
		if [ -e ".git" ]; then
			rm -fr .git;
			echo "del .git dir";
		fi
		cd ..;
		echo "leave $i";
	fi

done
