#!/bin/bash

# Architecture
arc=$(uname -a)

# CPU physical
pcpu=$(grep "physical id" /proc/cpuinfo | sort | uniq | wc -l)

# vCPU
vcpu=$(grep "^processor" /proc/cpuinfo | wc -l)

# Memory Usage
uram=$(free -m | awk '$1 == "Mem:" {print $3}')
tram=$(free -m | awk '$1 == "Mem:" {print $2}')
pram=$(free | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')

# Disk Usage
udisk=$(df -Bm | grep '^/dev/' | grep -v '/boot$' | awk '{ut += $3} END {print ut}')
tdisk=$(df -Bg | grep '^/dev/' | grep -v '/boot$' | awk '{ft += $2} END {print ft}')
pdisk=$(df -Bm | grep '^/dev/' | grep -v '/boot$' | awk '{ut += $3} {ft+= $2} END {printf("%d"), ut/ft*100}')

# CPU load
cpul=$(top -bn1 | grep '^%Cpu' | cut -c 9- | xargs | awk '{printf("%.1f%%"), $1 + $3}')

# Last boot
lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')

# LVM use
lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -eq 0 ]; then echo no; else echo yes; fi)

# Connections TCP
ctcp=$(ss -neopt state established | wc -l)

# User log
ulog=$(users | wc -w)

# Network
ip=$(hostname -I | awk '{print $1}')
mac=$(ip link show | awk '$1 == "link/ether" {print $2}')

# Sudo
cmds=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

wall "	#Architecture: $arc
	#CPU physical: $pcpu
	#vCPU: $vcpu
	#Memory Usage: $uram/${tram}MB ($pram%)
	#Disk Usage: $udisk/${tdisk}Gb ($pdisk%)
	#CPU load: $cpul
	#Last boot: $lb
	#LVM use: $lvmu
	#Connections TCP: $ctcp ESTABLISHED
	#User log: $ulog
	#Network: IP $ip ($mac)
	#Sudo: $cmds cmd"
