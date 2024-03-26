#!/bin/bash

check_exit_code() {
    if [ $? -ne 0 ]; then
        echo "Failed"
        exit 1
    fi
}

pushd build
make -j

for counter in {1..20}
do
	./tests
	check_exit_code
	echo
	echo $counter "iterations finished"
	echo
done

popd
