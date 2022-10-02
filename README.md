# Covert-Channel
Implementation of a cache covert channel that doesn't require threshold calibration.

This attack builds up on the observation that the latency of a `clflush` operation is higher than that of a `load` operation on a `cache-hit` and vice-versa on a `cache-miss`. A simple comparision of the latency of both operations by the receiver is enough to decode the bit sent by the sender.

## Build and run

`gcc sender.c util.c -o sender`

`gcc receiver.c util.c -o receiver`

`./sender 0(/1) && ./receiver`

