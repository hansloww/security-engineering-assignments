#!/bin/bash

# arguments handling
if [ "$#" -ne 2 ]; then
    echo "Error:Number of arguments does not match">&2
    exit 1
fi
# Format check
if [[ ! $2 =~ ^[0-9]+$ ]]; then
    echo "Error: '$2' is not a valid positive integer" >&2
    exit 2
fi

U=$1
N=$2
# Creates a text file to store the tans with the username
TAN_list="${U}_tans.txt"

for ((num=1; num<=N; num++));
do
	# Generates random key
	KEY=$(od -t x4 /dev/urandom | head -1 | cut -c 8-43 | sed -e "s/ //g")
	# HMAC(key, message)
	HMAC=$(openssl dgst -sha256 -mac HMAC -macopt hexkey:"$KEY" <(echo "$num") | sed -E "s/.*= //g")
	# Truncate 31-bit | mod 10^6
	TAN=$(( (0x$HMAC & 0x7FFFFFFF) % 1000000 ))
	echo "$TAN" >> "$TAN_list"
done









