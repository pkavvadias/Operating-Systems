#!/bin/bash
if [ ${#} -eq 0 ]; then
   echo "1054350-1054288"
   exit 1
fi

while [[ $# -gt 0 ]]; do
    key="$1"
    case "$key" in
        # Flag for surnames argument
        --firstnames)
	FIRSTNAMES=1
        ;;
        # Flag for last name argument
        --lastnames)
        LASTNAMES=1
        ;;
        # Pass filepath to FILE variable
        -f)
        shift # past the argument to get the value
        FILE="$1"
        ;;
        # Pass id to ID variable
        -id)
        shift  
        ID="$1"
        ;;
	# Pass born since date to BORN_SINCE variable
        --born-since)
        shift  
        BORN_SINCE="$1"
        ;;
	# Pass born until date to BORN_UNTIL variable
        --born-until)
        shift 
        BORN_UNTIL="$1"
        ;;
	# Flag for social media argument
	--socialmedia)
        SOCIALMEDIA=1
        ;;
	# Pass id of the user,column to be replaced and the value replacing it to their respectable variables
        --edit)
        shift 
        ID="$1"
#	shift # To get second value
	COLUMN="$2"
#	shift # To get third value
	VALUE="$3"
	EDIT=1
        ;;
        *)
    esac
    # After checking all cases shift to get next option
    shift
done


while read line ; do
	[[ $line = \#* ]] && continue # Ignore lines starting with #
	LINEARRAY+=("$line") # Insert every line into array
    
done <$FILE


	: '
        For every line processed the elements of each column go to the variable with the appropriate name(ids,lastnames etc)
	Then this variable is put in the appropriate array(IDARRAY,LASTNAMESARRAY etc)
	'
while IFS=$'|' read -r ids lastnames firstnames genders birthdays joindates ips browsersused socialmedias
do
	[[ $ids = \#* ]] && continue
	IDARRAY+=("$ids")
	LASTNAMESARRAY+=("$lastnames")
	FIRSTNAMESARRAY+=("$firstnames")
	GENDERSARRAY+=("$genders")
	BIRTHDAYSARRAY+=("$birthdays")
	JOINDATESARRAY+=("$joindates")
	IPSARRAY+=("$ips")
	BROWSERUSEDARRAY+=("$browserused")
	SOCIALMEDIAARRAY+=("$socialmedias")
done <$FILE

if [[ -z $ID ]] && [[ -z $FIRSTNAMES ]] && [[ -z $LASTNAMES ]] && [[ -z $BORN_SINCE ]] && [[ -z $BORN_UNTIL ]] && [[ -z $SOCIALMEDIA ]] # If no other arguments given then only print every user
then
	for each in "${LINEARRAY[@]}"
	do
  	echo "$each"
	done
#for ((index=0;index<${#IDARRAY[@]};++index));do
#	echo -e ${IDARRAY[index]}'\t'${LASTNAMESARRAY[index]}'\t'${FIRSTNAMESARRAY[index]}'\t'${GENDERSARRAY[index]}'\t'${BIRTHDAYSARRAY[index]}'\t'${JOINDATESARRAY[index]}'\t'${IPSARRAY[index]}'\t'${BROWSERUSEDARRAY[index]}'\t'${SOCIALMEDIAARRAY[index]}
#done

fi

if [[ $EDIT ]] && [[ -z $ID ]]
then
	for ((i=0;i< "${#IDARRAY[@]}";++i)); # Iterate through all IDs
	do
		if [[ $ID ==  ${IDARRAY[i]} ]] # If there is a match prints corresponding first name,last name and date of birth
		then
			echo -e ${FIRSTNAMESARRAY[i]}'\t'${LASTNAMESARRAY[i]}'\t'${BIRTHDAYSARRAY[i]}
		fi
	done
fi

if [[ $FIRSTNAMES ]]
then
	IFS=$'\n' sortedFirstnames=($(sort -u  <<<"${FIRSTNAMESARRAY[*]}")) # Create a new array with sorted firstnames
	for sortedfirstname in "${sortedFirstnames[@]}"
	do
		echo "$sortedfirstname"
	done
fi

if [[ $LASTNAMES ]]
then
	IFS=$'\n' sortedLastnames=($(sort -u  <<<"${LASTNAMESARRAY[*]}")) # Create a new array with sorted lastnames
	for sortedlastname in "${sortedLastnames[@]}"
	do
		echo "$sortedlastname" 
	done
fi


if [[ $BORN_SINCE ]] || [[ $BORN_UNTIL ]]
then
	if [[ -z $BORN_UNTIL ]]
	then
		BORN_UNTIL=$(date +%Y-%m-%d) # If no BORN_UNTIL argument given set current day as BORN_UNTIL
	fi
	if [[ -z $BORN_SINCE ]]
	then
		BORN_SINCE="1800-01-01" # If no BORN_SINCE argument given then set a date earlier than every other possible date(no social media users existed before 1800)
	fi
	

	for ((i=0;i< "${#BIRTHDAYSARRAY[@]}";++i)); # Equality is checked separately because inside [[ ]] operators ">=" and "<=" can't be used
	do	
		if [[  "${BIRTHDAYSARRAY[i]}" > $BORN_SINCE ]]  && [[  "${BIRTHDAYSARRAY[i]}" < $BORN_UNTIL ]]  || [[  "${BIRTHDAYSARRAY[i]}" ==  $BORN_SINCE ]] || [[  "${BIRTHDAYSARRAY[i]}" == $BORN_UNTIL ]] 
		then
			echo "${LINEARRAY[i]}"
		fi
	done

fi

if [[ $EDIT ]]
then
idcheck="$(grep -c $ID $FILE)"
if [[ $idcheck -eq 0 ]] || [[ $COLUMN -lt 2 ]] || [[ $COLUMN -gt 8 ]];then  # If given id doesn't exist or wrong column number exit
	echo "Wrong parametres"
	exit 0
else
	#For every line starting with the id replaces value of the desired column  with the new value and creates a backup of the original file called (original filename).bak
	sed -i.bak -e  "/^$ID|/s/[^|]*/$VALUE/$COLUMN" $FILE

fi
fi

