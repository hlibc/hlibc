mkdir -p control

for i in tests/*.c
do	ln $i control/$(basename $i)
done
