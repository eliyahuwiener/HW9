#!/bin/bash
cat /dev/stdin > packets_list.txt
if [ -s packets_list.txt ]; then
	while read -r line ; do
		cat packets_list.txt > packets_tmp.txt
		line=$(echo "$line" | sed -e 's/ //' | sed -e 's/#.*//')
		if [[ "$line" == "" ]]; then
			continue
		fi
		IFS=',' read -r -a rules_line <<< "$line"
		for one_rule in "${rules_line[@]}" ; do
			if [[ "$one_rule" == "" ]]; then
				continue
			fi
			cat packets_tmp.txt | ./firewall.exe "$one_rule" > rules_line_match.txt
			cat rules_line_match.txt > packets_tmp.txt
		done
		cat packets_tmp.txt >>pckts_match_fin.txt
	done <$1
	echo -e "$(<pckts_match_fin.txt)" | sed '/^$/d' | sort | uniq | tr -d ' ' | sort
	rm pckts_match_fin.txt rules_line_match.txt packets_tmp.txt packets_list.txt
else
	rm packets_list.txt
fi