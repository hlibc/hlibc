COMMAND='rm -rf hlibc ; git clone https://git.zv.io/me/hlibc/ ; cd hlibc ; make gcctest'
MIPSCOMMAND='rm -rf hlibc-mips ; git clone https://git.zv.io/me/hlibc/ hlibc-mips ; cd hlibc-mips ; make gcctest'

test_i386()
{
	ssh cgraff1@gcc45.fsffrance.org -f "$COMMAND"
}
test_i386 > test_i386_log 2>&1

test_x86_64()
{
	ssh cgraff1@gcc75.fsffrance.org -f "$COMMAND"
}
test_x86_64 > test_x86_64_log 2>&1

test_arm()
{
	ssh cgraff1@arm.zv.io -f "$COMMAND"
}
test_arm > test_arm_log 2>&1

test_mips()
{
	ssh cgraff1@gcc22.fsffrance.org -f "$MIPSCOMMAND"
}
test_mips > test_mips_log 2>&1


LLVMCOMMAND='rm -rf clanghlibc ; git clone https://git.zv.io/me/hlibc/ clanghlibc; cd clanghlibc ; make clangtest'

test_x86_64_clang()
{
	ssh cgraff1@gcc75.fsffrance.org -f "$LLVMCOMMAND"
}
test_x86_64_clang > test_x86_64_clang_log 2>&1
