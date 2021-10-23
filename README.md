# Producer Consumer Problem
## Meta data
* Name: Kapil Chauhan
* Assignment: Producer Consumer problem
* Date: 10/21/21
## Overview
* The produccer produces items and stores it into buffer.
* The consumer consumes the items one by one from the buffer.
## Problems faced
* Having a shared buffer.
* Keeping track of items produced and consumed.
* Keeping up with production and or consumption (overflow/underflow).
## Solution
* The buffer is in the shared memory.
* We use in and out integer variable in the shared memory to keep track of production and consumption.
* We will be using a circular queue and in, out variables to store and wait for the other task to finish.
## How to use?
* Use these commands to start the two processes in a linux shell.
```
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
```
