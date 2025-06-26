#!/bin/bash


# Trap signals to prevent interruption(Ctrl+C)
trap '' SIGINT

while true;
do
	echo -n "Enter username: "
	read username

	tan_file="${username}_tans.txt"

	# Check if TAN file exists
    	if [ ! -f "$tan_file" ]; then
        	echo "No TAN list found for {username}">&2
        	continue
    	fi

	echo -n "Enter TAN: "
    	read entered_tan

	# Verify TAN format(max 6 digits)
    	if ! [[ "$entered_tan" =~ ^[0-9]{6}$ ]]; then
        	echo "Invalid TAN ">&2
        	continue
    	fi

	# Check TAN list(checks if file exists and not empty)
    	if [ ! -s "$tan_file" ]; then
        	echo "Zugriff verweigert: die TAN-Liste des Users ist aufgebraucht"
        	continue
    	fi

	# Check if TAN exists in file
	# -F fixed string not regex
	# -x matches whole lines only not just part of it
	# -q quiet mode(match without printing to the terminal)
    	if grep -F -x -q "$entered_tan" "$tan_file"; then
        	echo "Zugriff erlaubt"
        	# Remove the used TAN
		# -i apply changes to file directly
        	sed -i "/^${entered_tan}$/d" "$tan_file"
    	else
        	echo "Access denied: Invalid TAN or already used"
   	 fi

done

