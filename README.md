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
------------------------------------------------------------------------------------
Benchmark                                          Time             CPU   Iterations
------------------------------------------------------------------------------------
STLConstantFuture/real_time                      568 ns          568 ns      1151694
YACLibConstantFuture/real_time                  32.3 ns         32.3 ns     20237516
FollyConstantFuture/real_time                   23.7 ns         23.7 ns     23097941

STLPromiseAndFuture/real_time                    474 ns          473 ns      1512769
YACLibPromiseAndFuture/real_time                64.3 ns         63.5 ns     11138296
FollyPromiseAndFuture/real_time                 60.1 ns         59.7 ns     11694852

YACLibOneThen/real_time                          127 ns          125 ns      5450958
FollyOneThen/real_time                           165 ns          163 ns      4249089

YACLibTwoThen/real_time                          206 ns          206 ns      3436010
FollyTwoThen/real_time                           278 ns          276 ns      2508035

YACLibFourThen/real_time                         366 ns          362 ns      1922748
FollyFourThen/real_time                          511 ns          510 ns      1362878

YACLibHundredThen/real_time                     7894 ns         7882 ns        89768
FollyHundredThen/real_time                     11413 ns        11309 ns        61696

YACLibFourThenOnThread/real_time               24786 ns        17157 ns        28718
FollyFourThenOnThread/real_time                26772 ns        17972 ns        24657

YACLibFourThenOnThreadInline/real_time         24045 ns        17080 ns        29164
FollyFourThenOnThreadInline/real_time          26799 ns        18188 ns        25839

YACLibHundredThenOnThread/real_time            39741 ns        28166 ns        17512
FollyHundredThenOnThread/real_time             59789 ns        44683 ns        12145

YACLibHundredThenOnThreadInline/real_time      31021 ns        25090 ns        23266
FollyHundredThenOnThreadInline/real_time       45353 ns        34057 ns        15884

YACLibComplexVoid/real_time                    28255 ns        28229 ns        24270
FollyComplexUnit/real_time                     37927 ns        37901 ns        18388

YACLibComplexBlob4/real_time                   26720 ns        26697 ns        26289
FollyComplexBlob4/real_time                    39877 ns        39859 ns        17977

YACLibComplexBlob8/real_time                   26650 ns        26639 ns        26136
FollyComplexBlob8/real_time                    37337 ns        37306 ns        18879

YACLibComplexBlob64/real_time                  28532 ns        28518 ns        24494
FollyComplexBlob64/real_time                   37713 ns        37698 ns        18631

YACLibComplexBlob128/real_time                 29172 ns        29160 ns        24009
FollyComplexBlob128/real_time                  38326 ns        38308 ns        18157

YACLibComplexBlob256/real_time                 31499 ns        31477 ns        22199
FollyComplexBlob256/real_time                  40587 ns        40560 ns        17373

YACLibComplexBlob512/real_time                 39858 ns        39817 ns        17565
FollyComplexBlob512/real_time                  46185 ns        46152 ns        14762

YACLibComplexBlob1024/real_time                60630 ns        60601 ns        11523
FollyComplexBlob1024/real_time                 60297 ns        60280 ns        11617

YACLibComplexBlob2048/real_time                76371 ns        76344 ns         9073
FollyComplexBlob2048/real_time                 70066 ns        70030 ns        10008

YACLibComplexBlob4096/real_time               112153 ns       112119 ns         6227
FollyComplexBlob4096/real_time                106537 ns       106467 ns         6550

YACLibNoContention/real_time                 1033378 ns       636226 ns          676
FollyNoContention/real_time                  1730145 ns       847328 ns          396

YACLibContention/real_time                   1876405 ns       595295 ns          377
FollyContention/real_time                    3240638 ns       875590 ns          215
```

</details>
