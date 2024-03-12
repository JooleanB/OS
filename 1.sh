#!/bin/bash

users=$(cat who.fake | awk '{print $1}')
for user in $users
do
	echo "$user"
	grep -c "^$user" ps.fake
done
