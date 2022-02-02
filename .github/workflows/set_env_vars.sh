#!/bin/bash
if [ "$1" = "shared" ]; then
	echo "PNINEXUS_SHARED=True" >> $GITHUB_ENV
else
	echo "PNINEXUS_SHARED=False" >> $GITHUB_ENV
fi
if [ "$2" = "mpi" ]; then
	echo "PNINEXUS_WITH_MPI=True" >> $GITHUB_ENV
else
	echo "PNINEXUS_WITH_MPI=False" >> $GITHUB_ENV
fi
