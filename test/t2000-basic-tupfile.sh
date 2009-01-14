#! /bin/sh -e

# Check a basic rule in a Tupfile

. ../tup.sh
cat > Tupfile << HERE
: foo.c |> echo gcc -c foo.c -o foo.o |> foo.o
HERE
tup touch foo.c Tupfile
tup upd
tup_object_exist . foo.c
tup_object_exist . "echo gcc -c foo.c -o foo.o"
