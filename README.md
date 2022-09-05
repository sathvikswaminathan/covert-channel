# Covert-Channel
Implementation of a cache covert channel that doesn't require threshold calibration 

## Build and run

`gcc sender.c util.c -o sender`

`gcc receiver.c util.c -o receiver`

`./sender 0(/1) && ./receiver`

