COMMAND='rm -rf grafmusl ; git clone https://www.github.com/cmgraff/grafmusl; cd grafmusl ; make test'

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


