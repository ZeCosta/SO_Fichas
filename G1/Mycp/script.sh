#!/bin/bash
echo script running

make mycp

time cp 1char a
echo
ls -l 1char a

echo ------------

time ./mycp 1char b
echo
ls -l 1char b

echo -------------//---------------

#time cp clientes c
#echo
#ls -l clientes c

#echo ------------

dd if=/dev/zero of=bigfile count=2M  #em vez de count posso usar bs=1G que é tamanho absoluto

time ./mycp bigfile d
echo
ls -l bigfile d
