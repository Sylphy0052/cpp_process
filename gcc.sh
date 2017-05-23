#!/bin/bash

gcc capfork.c -o capfork
gcc capfork2.c -o capfork2
gcc capthread.c -o capthread -lpthread
gcc pipe.c -o pipe
gcc tcount.c -o tcount -lpthread
gcc pcount.c -o pcount