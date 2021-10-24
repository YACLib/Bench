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
Benchmark results

<details>
<summary>
About system
</summary>

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
STLConstantFuture                      511 ns          510 ns      1312484
YACLibConstantFuture                  32.0 ns         31.9 ns     22096915
FollyConstantFuture                   28.3 ns         28.3 ns     25076414
STLPromiseAndFuture                    528 ns          528 ns      1309909
YACLibPromiseAndFuture                62.2 ns         62.1 ns     10973978
FollyPromiseAndFuture                 64.9 ns         64.9 ns     10741754
YACLibOneThen                          147 ns          147 ns      4785874
FollyOneThen                           172 ns          172 ns      4108779
YACLibTwoThen                          236 ns          236 ns      2990642
FollyTwoThen                           296 ns          296 ns      2349923
YACLibFourThen                         415 ns          415 ns      1693791
FollyFourThen                          558 ns          558 ns      1244561
YACLibHundredThen                     8725 ns         8709 ns        79019
FollyHundredThen                     12542 ns        12503 ns        56253
YACLibFourThenOnThread               27789 ns        18837 ns        37001
FollyFourThenOnThread                30961 ns        20014 ns        34970
YACLibFourThenOnThreadInline         27312 ns        18980 ns        37703
FollyFourThenOnThreadInline          34727 ns        22842 ns        34598
YACLibHundredThenOnThread            53120 ns        36885 ns        18914
FollyHundredThenOnThread             75488 ns        52666 ns        13471
YACLibHundredThenOnThreadInline      43156 ns        33789 ns        20653
FollyHundredThenOnThreadInline       54391 ns        34591 ns        20284
YACLibComplexUnit                    39182 ns        39157 ns        17977
FollyComplexUnit                     49353 ns        49318 ns        14191
YACLibComplexBlob4                   38641 ns        38621 ns        18098
FollyComplexBlob4                    48809 ns        48778 ns        14379
YACLibComplexBlob8                   38387 ns        38269 ns        17942
FollyComplexBlob8                    48119 ns        48092 ns        14557
YACLibComplexBlob64                  40176 ns        40153 ns        17654
FollyComplexBlob64                   42885 ns        42851 ns        17041
YACLibComplexBlob128                 41073 ns        41014 ns        17024
FollyComplexBlob128                  42016 ns        41978 ns        16553
YACLibNoContention                 1623865 ns       684637 ns         1027
FollyNoContention                  2917857 ns       899710 ns          775
YACLibContention                   3337525 ns       661014 ns         1107
FollyContention                    5953766 ns       956817 ns          732
```

</details>
