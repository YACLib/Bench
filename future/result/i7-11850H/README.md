### Configuration

<details>

```bash
OS: Arch Linux x86_64
Host: Latitude 5421
Kernel: 5.15.25-1-lts
Uptime: 2 mins
Packages: 659 (pacman)
Shell: zsh 5.8.1
Resolution: 1920x1080
DE: GNOME 41.4
WM: Mutter
WM Theme: Adwaita
Theme: Adwaita [GTK2/3]
Icons: Adwaita [GTK2/3]
Terminal: alacritty
CPU: 11th Gen Intel i7-11850H (16) @ 2.501GHz
GPU: Intel TigerLake-H GT1 [UHD Graphics]
Memory: 732MiB / 47912MiB
```

</details>

### GCC, libstdc++

<details>

##### Version

```bash
g++ (GCC) 11.2.0

mold 1.1 (89612b709638b90c8a044e2f96f47d28054ba789; compatible with GNU ld)
```

##### Configuration

```bash
cmake -GNinja                                       \
  -DCMAKE_BUILD_TYPE=Release                        \
  -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++   \
  -DSTD=ON -DYACLIB=main -DFOLLY=ON -DBOOST_THREAD=ON
```

##### Results

```bash
2022-02-28T02:46:46+03:00
Running ./build_gcc_libstdcxx/future/future
Run on (16 X 2514.53 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 1280 KiB (x8)
  L3 Unified 24576 KiB (x1)
Load Average: 0.22, 0.36, 0.17
----------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations
----------------------------------------------------------------------------------
ConstantFuture/Std/real_time                  129 ns          129 ns      5436771
ConstantFuture/YACLib/real_time              14.9 ns         14.9 ns     46948391
ConstantFuture/Folly/real_time               15.6 ns         15.6 ns     44933294
ConstantFuture/BoostThread/real_time          104 ns          104 ns      6739487

PromiseAndFuture/Std/real_time                132 ns          132 ns      5303394
PromiseAndFuture/YACLib/real_time            26.2 ns         26.2 ns     26741427
PromiseAndFuture/Folly/real_time             42.2 ns         42.0 ns     16574648
PromiseAndFuture/BoostThread/real_time        113 ns          113 ns      6203199


Then/YACLib/0/0/real_time                    59.3 ns         59.3 ns     11790715
Then/Folly/0/0/real_time                      111 ns          110 ns      6609518
Then/BoostThread/0/0/real_time                677 ns          675 ns      1027172

Then/YACLib/1/0/real_time                     123 ns          123 ns      5689354
Then/Folly/1/0/real_time                      244 ns          243 ns      2341937
Then/BoostThread/1/0/real_time               1469 ns         1466 ns       470493

Then/YACLib/2/0/real_time                     187 ns          187 ns      3741530
Then/Folly/2/0/real_time                      381 ns          379 ns      1836613
Then/BoostThread/2/0/real_time               2248 ns         2243 ns       313011

Then/YACLib/4/0/real_time                     329 ns          329 ns      2125063
Then/Folly/4/0/real_time                      673 ns          669 ns      1038724
Then/BoostThread/4/0/real_time               3793 ns         3785 ns       185715

Then/YACLib/8/0/real_time                     589 ns          589 ns      1187586
Then/Folly/8/0/real_time                     1228 ns         1222 ns       570623
Then/BoostThread/8/0/real_time               6804 ns         6790 ns       103395

Then/YACLib/16/0/real_time                   1103 ns         1102 ns       638875
Then/Folly/16/0/real_time                    2339 ns         2327 ns       300356
Then/BoostThread/16/0/real_time             12861 ns        12834 ns        54564

Then/YACLib/32/0/real_time                   2132 ns         2128 ns       329145
Then/Folly/32/0/real_time                    5389 ns         5375 ns       100000
Then/BoostThread/32/0/real_time             24923 ns        24868 ns        28227

Then/YACLib/64/0/real_time                   4214 ns         4195 ns       166677
Then/Folly/64/0/real_time                    9026 ns         8983 ns        77503
Then/BoostThread/64/0/real_time             49269 ns        49165 ns        14314

Then/YACLib/0/1/real_time                    5577 ns         3609 ns       127438
Then/Folly/0/1/real_time                     5615 ns         3865 ns       125794
Then/BoostThread/0/1/real_time               6674 ns         4647 ns       103925

Then/YACLib/1/1/real_time                    5761 ns         3771 ns       123879
Then/Folly/1/1/real_time                     5929 ns         4063 ns       117985
Then/BoostThread/1/1/real_time               7221 ns         5355 ns        95286

Then/YACLib/2/1/real_time                    5721 ns         3798 ns       120948
Then/Folly/2/1/real_time                     6434 ns         4416 ns       109074
Then/BoostThread/2/1/real_time               7537 ns         5798 ns        93137

Then/YACLib/4/1/real_time                    5932 ns         3985 ns       116606
Then/Folly/4/1/real_time                     6623 ns         4781 ns       104123
Then/BoostThread/4/1/real_time               8712 ns         7182 ns        80230

Then/YACLib/8/1/real_time                    6376 ns         4435 ns       109794
Then/Folly/8/1/real_time                     6959 ns         4936 ns       105988
Then/BoostThread/8/1/real_time              11134 ns         9958 ns        62541

Then/YACLib/16/1/real_time                   6911 ns         5198 ns       102453
Then/Folly/16/1/real_time                    8088 ns         6376 ns        85610
Then/BoostThread/16/1/real_time             19402 ns        18007 ns        36085

Then/YACLib/32/1/real_time                   7780 ns         6515 ns        89439
Then/Folly/32/1/real_time                   23715 ns        21178 ns        29800
Then/BoostThread/32/1/real_time             34418 ns        33001 ns        20105

Then/YACLib/64/1/real_time                   7900 ns         7859 ns        88609
Then/Folly/64/1/real_time                   46854 ns        41808 ns        14899
Then/BoostThread/64/1/real_time             61609 ns        60141 ns        11319

Then/YACLib/0/2/real_time                    5566 ns         3620 ns       127029
Then/Folly/0/2/real_time                     5758 ns         3926 ns       123716
Then/BoostThread/0/2/real_time               6828 ns         4813 ns       103466

Then/YACLib/1/2/real_time                    5878 ns         3790 ns       122339
Then/Folly/1/2/real_time                     6289 ns         4269 ns       109821
Then/BoostThread/1/2/real_time               7805 ns         5567 ns        88761

Then/YACLib/2/2/real_time                    5967 ns         3851 ns       116674
Then/Folly/2/2/real_time                     6740 ns         4527 ns       105427
Then/BoostThread/2/2/real_time               8884 ns         6519 ns        79282

Then/YACLib/4/2/real_time                    6336 ns         4093 ns       111494
Then/Folly/4/2/real_time                     7245 ns         4771 ns        94545
Then/BoostThread/4/2/real_time              11883 ns         8730 ns        58917

Then/YACLib/8/2/real_time                    7084 ns         4538 ns        98081
Then/Folly/8/2/real_time                     7875 ns         5142 ns        87621
Then/BoostThread/8/2/real_time              18978 ns        13130 ns        36631

Then/YACLib/16/2/real_time                   9076 ns         5933 ns        77800
Then/Folly/16/2/real_time                   10453 ns         6761 ns        66647
Then/BoostThread/16/2/real_time             30228 ns        20516 ns        23319

Then/YACLib/32/2/real_time                  14110 ns         9830 ns        49214
Then/Folly/32/2/real_time                   23486 ns        17718 ns        28886
Then/BoostThread/32/2/real_time             52712 ns        35036 ns        12242

Then/YACLib/64/2/real_time                  24624 ns        18005 ns        28337
Then/Folly/64/2/real_time                   51350 ns        42603 ns        13850
Then/BoostThread/64/2/real_time             99465 ns        68384 ns         7064


ComplexBlob/YACLib/0/real_time              13082 ns        13043 ns        53315
ComplexBlob/Folly/0/real_time               30684 ns        30588 ns        22680
ComplexBlob/BoostThread/0/real_time        108613 ns       105015 ns         6540

ComplexBlob/YACLib/2/real_time              12536 ns        12501 ns        56030
ComplexBlob/Folly/2/real_time               30113 ns        30028 ns        23100
ComplexBlob/BoostThread/2/real_time        107469 ns       103865 ns         6590

ComplexBlob/YACLib/4/real_time              12493 ns        12456 ns        55464
ComplexBlob/Folly/4/real_time               30122 ns        30042 ns        23219
ComplexBlob/BoostThread/4/real_time        107629 ns       104175 ns         6499

ComplexBlob/YACLib/8/real_time              12339 ns        12304 ns        56225
ComplexBlob/Folly/8/real_time               29650 ns        29568 ns        23557
ComplexBlob/BoostThread/8/real_time        106035 ns       102510 ns         6599

ComplexBlob/YACLib/16/real_time             13680 ns        13650 ns        51020
ComplexBlob/Folly/16/real_time              29600 ns        29531 ns        23719
ComplexBlob/BoostThread/16/real_time       106127 ns       102636 ns         6622

ComplexBlob/YACLib/32/real_time             13563 ns        13535 ns        51506
ComplexBlob/Folly/32/real_time              29962 ns        29894 ns        23199
ComplexBlob/BoostThread/32/real_time       105512 ns       101885 ns         6650

ComplexBlob/YACLib/64/real_time             12974 ns        12948 ns        53877
ComplexBlob/Folly/64/real_time              30491 ns        30417 ns        22937
ComplexBlob/BoostThread/64/real_time       105392 ns       101666 ns         6650

ComplexBlob/YACLib/128/real_time            14425 ns        14393 ns        48313
ComplexBlob/Folly/128/real_time             31428 ns        31360 ns        22310
ComplexBlob/BoostThread/128/real_time      106523 ns       102777 ns         6626

ComplexBlob/YACLib/256/real_time            14646 ns        14616 ns        47604
ComplexBlob/Folly/256/real_time             32274 ns        32209 ns        21744
ComplexBlob/BoostThread/256/real_time      107286 ns       103565 ns         6556

ComplexBlob/YACLib/512/real_time            21045 ns        21002 ns        32863
ComplexBlob/Folly/512/real_time             37927 ns        37846 ns        18466
ComplexBlob/BoostThread/512/real_time      118559 ns       114792 ns         5940

ComplexBlob/YACLib/1024/real_time           30208 ns        30151 ns        23064
ComplexBlob/Folly/1024/real_time            44751 ns        44658 ns        15656
ComplexBlob/BoostThread/1024/real_time     141096 ns       137544 ns         4946

ComplexBlob/YACLib/2048/real_time           34314 ns        34204 ns        20390
ComplexBlob/Folly/2048/real_time            48533 ns        48380 ns        14424
ComplexBlob/BoostThread/2048/real_time     155948 ns       152166 ns         4486

ComplexBlob/YACLib/4096/real_time           54259 ns        54010 ns        13015
ComplexBlob/Folly/4096/real_time            69187 ns        68992 ns        10057
ComplexBlob/BoostThread/4096/real_time     176848 ns       173475 ns         3871

ComplexBlob/YACLib/8192/real_time          127257 ns       127246 ns         5516
ComplexBlob/Folly/8192/real_time           135525 ns       135513 ns         5145
ComplexBlob/BoostThread/8192/real_time     245158 ns       241978 ns         2858


NoContention/YACLib/real_time              716841 ns       319033 ns          976
NoContention/Folly/real_time              1164090 ns       519442 ns          601
NoContention/BoostThread/real_time        3904441 ns      1904416 ns          179

Contention/YACLib/real_time               1117828 ns       301887 ns          629
Contention/Folly/real_time                1991801 ns       563274 ns          351
Contention/BoostThread/real_time          5988780 ns      1868434 ns          120
```

</details>

### Clang, libstdc++

<details>

##### Version

```bash
clang version 13.0.1
Target: x86_64-pc-linux-gnu
Thread model: posix

mold 1.1 (89612b709638b90c8a044e2f96f47d28054ba789; compatible with GNU ld)
```

##### Configuration

```bash
cmake -GNinja                                           \
  -DCMAKE_BUILD_TYPE=Release                            \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DSTD=ON -DYACLIB=main -DFOLLY=ON -DBOOST_THREAD=ON
```

##### Results

```bash
2022-02-28T02:48:55+03:00
Running ./build_clang_libstdcxx/future/future
Run on (16 X 2500.89 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 1280 KiB (x8)
  L3 Unified 24576 KiB (x1)
Load Average: 0.92, 0.62, 0.29
----------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations
----------------------------------------------------------------------------------
ConstantFuture/Std/real_time                  139 ns          139 ns      5137530
ConstantFuture/YACLib/real_time              15.4 ns         15.3 ns     45652617
ConstantFuture/Folly/real_time               16.3 ns         16.2 ns     42920633
ConstantFuture/BoostThread/real_time          107 ns          107 ns      6558398

PromiseAndFuture/Std/real_time                146 ns          145 ns      4781574
PromiseAndFuture/YACLib/real_time            30.9 ns         30.7 ns     22732174
PromiseAndFuture/Folly/real_time             53.1 ns         52.9 ns     13139125
PromiseAndFuture/BoostThread/real_time        115 ns          114 ns      5245917


Then/YACLib/0/0/real_time                    74.8 ns         74.5 ns      9608639
Then/Folly/0/0/real_time                      121 ns          121 ns      5704559
Then/BoostThread/0/0/real_time                641 ns          637 ns      1115940

Then/YACLib/1/0/real_time                     150 ns          149 ns      4685896
Then/Folly/1/0/real_time                      290 ns          289 ns      2427066
Then/BoostThread/1/0/real_time               1419 ns         1408 ns       497423

Then/YACLib/2/0/real_time                     228 ns          227 ns      3068577
Then/Folly/2/0/real_time                      458 ns          456 ns      1523096
Then/BoostThread/2/0/real_time               2158 ns         2142 ns       324954

Then/YACLib/4/0/real_time                     400 ns          398 ns      1768683
Then/Folly/4/0/real_time                      823 ns          820 ns       865793
Then/BoostThread/4/0/real_time               3636 ns         3609 ns       193201

Then/YACLib/8/0/real_time                     712 ns          709 ns       977221
Then/Folly/8/0/real_time                     1483 ns         1478 ns       469934
Then/BoostThread/8/0/real_time               6570 ns         6518 ns       106161

Then/YACLib/16/0/real_time                   1326 ns         1321 ns       527118
Then/Folly/16/0/real_time                    2839 ns         2828 ns       247090
Then/BoostThread/16/0/real_time             12654 ns        12560 ns        56093

Then/YACLib/32/0/real_time                   2561 ns         2550 ns       274199
Then/Folly/32/0/real_time                    5746 ns         5729 ns       127100
Then/BoostThread/32/0/real_time             24687 ns        24522 ns        28999

Then/YACLib/64/0/real_time                   5035 ns         5012 ns       139400
Then/Folly/64/0/real_time                   10886 ns        10846 ns        63989
Then/BoostThread/64/0/real_time             47888 ns        47532 ns        14574

Then/YACLib/0/1/real_time                    5913 ns         3909 ns       117565
Then/Folly/0/1/real_time                     5977 ns         4102 ns       135842
Then/BoostThread/0/1/real_time               6686 ns         4755 ns       105158

Then/YACLib/1/1/real_time                    5803 ns         3848 ns       120910
Then/Folly/1/1/real_time                     6531 ns         4575 ns       105819
Then/BoostThread/1/1/real_time               7450 ns         5593 ns        93807

Then/YACLib/2/1/real_time                    5945 ns         3991 ns       118416
Then/Folly/2/1/real_time                     6621 ns         4657 ns       105053
Then/BoostThread/2/1/real_time               8017 ns         6240 ns        87096

Then/YACLib/4/1/real_time                    6131 ns         4133 ns       113399
Then/Folly/4/1/real_time                     6769 ns         4984 ns       103009
Then/BoostThread/4/1/real_time               9283 ns         7624 ns        76395

Then/YACLib/8/1/real_time                    6523 ns         4534 ns       106687
Then/Folly/8/1/real_time                     7113 ns         4958 ns        98552
Then/BoostThread/8/1/real_time              11641 ns        10522 ns        60212

Then/YACLib/16/1/real_time                   7283 ns         5526 ns        95610
Then/Folly/16/1/real_time                    8483 ns         6344 ns        83075
Then/BoostThread/16/1/real_time             21068 ns        19702 ns        33158

Then/YACLib/32/1/real_time                   8324 ns         6938 ns        84260
Then/Folly/32/1/real_time                   22046 ns        18447 ns        30514
Then/BoostThread/32/1/real_time             33973 ns        32617 ns        20263

Then/YACLib/64/1/real_time                   8640 ns         8551 ns        80685
Then/Folly/64/1/real_time                   41652 ns        34634 ns        16955
Then/BoostThread/64/1/real_time             59942 ns        58679 ns        11841

Then/YACLib/0/2/real_time                    5788 ns         3843 ns       120072
Then/Folly/0/2/real_time                     6041 ns         4129 ns       115401
Then/BoostThread/0/2/real_time               6554 ns         4675 ns       106586

Then/YACLib/1/2/real_time                    5941 ns         3834 ns       115542
Then/Folly/1/2/real_time                     6439 ns         4352 ns       109226
Then/BoostThread/1/2/real_time               7678 ns         5608 ns        91625

Then/YACLib/2/2/real_time                    6193 ns         4053 ns       111555
Then/Folly/2/2/real_time                     6689 ns         4525 ns       103573
Then/BoostThread/2/2/real_time               8624 ns         6424 ns        81366

Then/YACLib/4/2/real_time                    6847 ns         4432 ns       104796
Then/Folly/4/2/real_time                     7288 ns         4901 ns        94625
Then/BoostThread/4/2/real_time              12340 ns         8866 ns        57748

Then/YACLib/8/2/real_time                    7709 ns         4908 ns        90696
Then/Folly/8/2/real_time                     8180 ns         5492 ns        87118
Then/BoostThread/8/2/real_time              18426 ns        12980 ns        37949

Then/YACLib/16/2/real_time                   9809 ns         6584 ns        72322
Then/Folly/16/2/real_time                   11302 ns         7347 ns        62623
Then/BoostThread/16/2/real_time             30710 ns        21123 ns        22801

Then/YACLib/32/2/real_time                  14923 ns        11094 ns        45749
Then/Folly/32/2/real_time                   26931 ns        20699 ns        29906
Then/BoostThread/32/2/real_time             55202 ns        38270 ns        12734

Then/YACLib/64/2/real_time                  26156 ns        21206 ns        27891
Then/Folly/64/2/real_time                   50322 ns        40277 ns        13515
Then/BoostThread/64/2/real_time            106081 ns        73730 ns         6576


ComplexBlob/YACLib/0/real_time              15346 ns        15293 ns        45441
ComplexBlob/Folly/0/real_time               32217 ns        32108 ns        21686
ComplexBlob/BoostThread/0/real_time        105486 ns       101879 ns         6674

ComplexBlob/YACLib/2/real_time              14194 ns        14147 ns        48952
ComplexBlob/Folly/2/real_time               32616 ns        32507 ns        21399
ComplexBlob/BoostThread/2/real_time        104805 ns       101347 ns         6718

ComplexBlob/YACLib/4/real_time              14335 ns        14283 ns        49268
ComplexBlob/Folly/4/real_time               32704 ns        32581 ns        21347
ComplexBlob/BoostThread/4/real_time        102990 ns        99724 ns         6744

ComplexBlob/YACLib/8/real_time              12941 ns        12904 ns        54593
ComplexBlob/Folly/8/real_time               30196 ns        30004 ns        23143
ComplexBlob/BoostThread/8/real_time         98775 ns        95798 ns         7089

ComplexBlob/YACLib/16/real_time             13992 ns        13963 ns        50115
ComplexBlob/Folly/16/real_time              29328 ns        29162 ns        23746
ComplexBlob/BoostThread/16/real_time        98273 ns        95366 ns         7121

ComplexBlob/YACLib/32/real_time             13898 ns        13868 ns        50482
ComplexBlob/Folly/32/real_time              29096 ns        28954 ns        24237
ComplexBlob/BoostThread/32/real_time        98355 ns        95451 ns         7111

ComplexBlob/YACLib/64/real_time             14379 ns        14318 ns        49373
ComplexBlob/Folly/64/real_time              31230 ns        31117 ns        22204
ComplexBlob/BoostThread/64/real_time       103823 ns       100309 ns         6779

ComplexBlob/YACLib/128/real_time            16263 ns        16199 ns        43716
ComplexBlob/Folly/128/real_time             31968 ns        31861 ns        21806
ComplexBlob/BoostThread/128/real_time      104064 ns       100281 ns         6759

ComplexBlob/YACLib/256/real_time            16082 ns        16007 ns        43301
ComplexBlob/Folly/256/real_time             33046 ns        32904 ns        21056
ComplexBlob/BoostThread/256/real_time      105271 ns       101535 ns         6686

ComplexBlob/YACLib/512/real_time            17442 ns        17381 ns        39884
ComplexBlob/Folly/512/real_time             34686 ns        34543 ns        20176
ComplexBlob/BoostThread/512/real_time      106351 ns       102546 ns         6618

ComplexBlob/YACLib/1024/real_time           27506 ns        27401 ns        25395
ComplexBlob/Folly/1024/real_time            42317 ns        42130 ns        16525
ComplexBlob/BoostThread/1024/real_time     124590 ns       121059 ns         5644

ComplexBlob/YACLib/2048/real_time           33180 ns        33059 ns        21088
ComplexBlob/Folly/2048/real_time            48386 ns        48215 ns        14447
ComplexBlob/BoostThread/2048/real_time     125508 ns       122316 ns         5403

ComplexBlob/YACLib/4096/real_time           42182 ns        42170 ns        16597
ComplexBlob/Folly/4096/real_time            59954 ns        59949 ns        11643
ComplexBlob/BoostThread/4096/real_time     132468 ns       129450 ns         5289

ComplexBlob/YACLib/8192/real_time          114877 ns       114869 ns         6086
ComplexBlob/Folly/8192/real_time           130345 ns       130336 ns         5364
ComplexBlob/BoostThread/8192/real_time     179593 ns       176434 ns         3895


NoContention/YACLib/real_time              750686 ns       314437 ns          928
NoContention/Folly/real_time              1225356 ns       505605 ns          571
NoContention/BoostThread/real_time        3862092 ns      1873659 ns          181

Contention/YACLib/real_time               1155390 ns       291587 ns          611
Contention/Folly/real_time                2117608 ns       560854 ns          330
Contention/BoostThread/real_time          5971219 ns      1824637 ns          119
```

</details>

### Clang, libc++

<details>

##### Version

```bash
clang version 13.0.1
Target: x86_64-pc-linux-gnu
Thread model: posix

mold 1.1 (89612b709638b90c8a044e2f96f47d28054ba789; compatible with GNU ld)
```

##### Configuration

```bash
cmake -GNinja                                           \
  -DCMAKE_BUILD_TYPE=Release                            \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLIBCXX=ON                                           \
  -DSTD=ON -DYACLIB=main
```

##### Results

```bash
2022-02-28T03:10:34+03:00
Running ./build_clang_libcxx/future/future
Run on (16 X 2500 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 1280 KiB (x8)
  L3 Unified 24576 KiB (x1)
Load Average: 0.80, 0.81, 0.67
-----------------------------------------------------------------------------
Benchmark                                   Time             CPU   Iterations
-----------------------------------------------------------------------------
ConstantFuture/Std/real_time            41.1 ns         41.0 ns     17436305
ConstantFuture/YACLib/real_time         16.4 ns         16.3 ns     43327014

PromiseAndFuture/Std/real_time          49.8 ns         49.6 ns     14091817
PromiseAndFuture/YACLib/real_time       32.8 ns         32.7 ns     21429744


Then/YACLib/0/0/real_time               73.4 ns         73.2 ns      9485851

Then/YACLib/1/0/real_time                152 ns          152 ns      4410053

Then/YACLib/2/0/real_time                228 ns          228 ns      3093238

Then/YACLib/4/0/real_time                399 ns          398 ns      1787154

Then/YACLib/8/0/real_time                716 ns          715 ns       989649

Then/YACLib/16/0/real_time              1317 ns         1315 ns       530073

Then/YACLib/32/0/real_time              2539 ns         2533 ns       276433

Then/YACLib/64/0/real_time              4943 ns         4932 ns       141286

Then/YACLib/0/1/real_time               5878 ns         3852 ns       118884

Then/YACLib/1/1/real_time               6069 ns         4032 ns       116418

Then/YACLib/2/1/real_time               6024 ns         4056 ns       115451

Then/YACLib/4/1/real_time               6126 ns         4199 ns       112194

Then/YACLib/8/1/real_time               6689 ns         4691 ns       105765

Then/YACLib/16/1/real_time              7128 ns         5405 ns        97268

Then/YACLib/32/1/real_time              8147 ns         7084 ns        88009

Then/YACLib/64/1/real_time              8754 ns         8692 ns        79270

Then/YACLib/0/2/real_time               5779 ns         3798 ns       120670

Then/YACLib/1/2/real_time               5984 ns         3965 ns       117194

Then/YACLib/2/2/real_time               6314 ns         4136 ns       111981

Then/YACLib/4/2/real_time               6645 ns         4327 ns       105767

Then/YACLib/8/2/real_time               7312 ns         4756 ns        94191

Then/YACLib/16/2/real_time              9066 ns         5884 ns        77092

Then/YACLib/32/2/real_time             14429 ns         9621 ns        48712

Then/YACLib/64/2/real_time             24817 ns        16941 ns        28326


ComplexBlob/YACLib/0/real_time         15105 ns        15045 ns        49675

ComplexBlob/YACLib/2/real_time         13636 ns        13577 ns        53415

ComplexBlob/YACLib/4/real_time         13759 ns        13703 ns        53228

ComplexBlob/YACLib/8/real_time         13149 ns        13088 ns        52965

ComplexBlob/YACLib/16/real_time        16103 ns        16051 ns        47824

ComplexBlob/YACLib/32/real_time        14720 ns        14665 ns        47499

ComplexBlob/YACLib/64/real_time        13941 ns        13872 ns        50286

ComplexBlob/YACLib/128/real_time       14453 ns        14387 ns        48276

ComplexBlob/YACLib/256/real_time       15179 ns        15107 ns        46252

ComplexBlob/YACLib/512/real_time       16462 ns        16376 ns        42430

ComplexBlob/YACLib/1024/real_time      26172 ns        26043 ns        26664

ComplexBlob/YACLib/2048/real_time      30658 ns        30515 ns        22873

ComplexBlob/YACLib/4096/real_time      45413 ns        45353 ns        15430

ComplexBlob/YACLib/8192/real_time     130512 ns       130338 ns         5386


NoContention/YACLib/real_time         735608 ns       301239 ns          952

Contention/YACLib/real_time          1026614 ns       242974 ns          646
```

</details>
