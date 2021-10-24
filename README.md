# Benchmark YACLib

<details>
<summary>
If you have this warning:

```bash
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
```

</summary>
Before run:

```bash
sudo cpupower frequency-set --governor performance
```

After run:

```bash
sudo cpupower frequency-set --governor powersave
```

</details>

<details open>

<summary> 
About system
<details>

```bash
OS: Arch Linux x86_64
Host: 20KN001NRT ThinkPad E480
Kernel: 5.10.75-1-lts
Uptime: 10 mins
CPU: Intel i7-8550U (8) @ 4.000GHz
GPU: AMD ATI Radeon 540/540X/550/550X / RX 540
GPU: Intel UHD Graphics 620
Memory: 5173MiB / 15773MiB

Run on (8 X 3711.38 MHz CPU s)
CPU Caches:
L1 Data 32 KiB (x4)
L1 Instruction 32 KiB (x4)
L2 Unified 256 KiB (x4)
L3 Unified 8192 KiB (x1)
Load Average: 2.24, 1.56, 0.76
```

</details>
</summary>

```bash
--------------------------------------------------------------------------
Benchmark                                Time             CPU   Iterations
--------------------------------------------------------------------------
STLConstantFuture                      665 ns          664 ns      1102341
YACLibConstantFuture                  39.5 ns         39.5 ns     17759137
FollyConstantFuture                   28.2 ns         28.1 ns     25026422
STLPromiseAndFuture                    495 ns          494 ns      1381178
YACLibPromiseAndFuture                60.5 ns         60.5 ns     11498653
FollyPromiseAndFuture                 64.0 ns         64.0 ns     10812138
YACLibOneThen                          141 ns          141 ns      5034779
FollyOneThen                           167 ns          167 ns      4199227
YACLibTwoThen                          225 ns          225 ns      3111868
FollyTwoThen                           288 ns          287 ns      2409535
YACLibFourThen                         392 ns          392 ns      1791787
FollyFourThen                          536 ns          536 ns      1338499
YACLibHundredThen                     9724 ns         9715 ns        84571
FollyHundredThen                     12444 ns        12435 ns        56576
YACLibFourThenOnThread               24139 ns        17061 ns        40884
FollyFourThenOnThread                28743 ns        19254 ns        39393
YACLibFourThenOnThreadInline         27274 ns        19789 ns        35370
FollyFourThenOnThreadInline          30633 ns        20840 ns        33243
YACLibHundredThenOnThread            45219 ns        32662 ns        21173
FollyHundredThenOnThread             73015 ns        51052 ns        10000
YACLibHundredThenOnThreadInline      38174 ns        31567 ns        19745
FollyHundredThenOnThreadInline       47598 ns        30737 ns        22118
```

</details>
