CC="$1" ./configure --prefix="${2}" --enable-gcc-wrapper --disable-shared

CC="$1" make

make install

git clone https://git.hlibc.xyz/lab/hlibc-test.git

./hlibc-test/build.sh $1 ${2}/bin/${1}-wrap

exit

wget https://ftp.gnu.org/gnu/bc/bc-1.03.tar.gz

tar -xf bc-1.03.tar.gz

cd bc-1.03

CC=${2}/bin/${1}-wrap make

echo "1234567*1234567" | ./bc -l


