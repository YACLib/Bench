```
2022-03-18T07:54:25+03:00
Running ./build_clang_libcxx/future/future
Run on (16 X 3639.3 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 512 KiB (x8)
  L3 Unified 16384 KiB (x2)
Load Average: 1.07, 1.30, 1.17
-----------------------------------------------------------------------------
Benchmark                                   Time             CPU   Iterations
-----------------------------------------------------------------------------
ConstantFuture(Std)/real_time            44.8 ns         44.8 ns     15533881
ConstantFuture(YACLib)/real_time         17.5 ns         17.5 ns     40625160
PromiseAndFuture(Std)/real_time          59.2 ns         59.2 ns     12050366
PromiseAndFuture(YACLib)/real_time       32.0 ns         32.0 ns     21816267
Then(YACLib)/0/0/real_time               78.0 ns         78.0 ns      9027304
Then(YACLib)/1/0/real_time                155 ns          155 ns      4472215
Then(YACLib)/2/0/real_time                216 ns          216 ns      3238783
Then(YACLib)/4/0/real_time                355 ns          355 ns      2034100
Then(YACLib)/8/0/real_time                589 ns          588 ns      1204618
Then(YACLib)/16/0/real_time              1085 ns         1084 ns       645818
Then(YACLib)/32/0/real_time              2101 ns         2101 ns       331824
Then(YACLib)/64/0/real_time              4043 ns         4042 ns       173625
Then(YACLib)/0/1/real_time               4735 ns         2471 ns       145393
Then(YACLib)/1/1/real_time               5050 ns         2694 ns       135617
Then(YACLib)/2/1/real_time               5113 ns         2697 ns       133318
Then(YACLib)/4/1/real_time               5553 ns         3022 ns       123605
Then(YACLib)/8/1/real_time               6193 ns         3426 ns       115690
Then(YACLib)/16/1/real_time              6985 ns         4507 ns       101195
Then(YACLib)/32/1/real_time              8259 ns         6305 ns        88376
Then(YACLib)/64/1/real_time             10268 ns         9957 ns        67456
Then(YACLib)/0/2/real_time               4790 ns         2412 ns       145883
Then(YACLib)/1/2/real_time               4858 ns         2555 ns       139508
Then(YACLib)/2/2/real_time               5207 ns         2821 ns       132816
Then(YACLib)/4/2/real_time               5631 ns         3255 ns       122536
Then(YACLib)/8/2/real_time               6728 ns         3933 ns       101760
Then(YACLib)/16/2/real_time             11226 ns         8013 ns        61267
Then(YACLib)/32/2/real_time             19799 ns        16203 ns        35272
Then(YACLib)/64/2/real_time             36742 ns        32605 ns        18998
ComplexBlob(YACLib)/0/real_time         12774 ns        12770 ns        54457
ComplexBlob(YACLib)/2/real_time         10207 ns        10204 ns        68393
ComplexBlob(YACLib)/4/real_time         10537 ns        10533 ns        65599
ComplexBlob(YACLib)/8/real_time         10292 ns        10290 ns        68379
ComplexBlob(YACLib)/16/real_time        11291 ns        11288 ns        62654
ComplexBlob(YACLib)/32/real_time        11027 ns        11024 ns        62924
ComplexBlob(YACLib)/64/real_time        11378 ns        11375 ns        61512
ComplexBlob(YACLib)/128/real_time       11878 ns        11875 ns        58876
ComplexBlob(YACLib)/256/real_time       13519 ns        13513 ns        51675
ComplexBlob(YACLib)/512/real_time       14632 ns        14628 ns        47870
ComplexBlob(YACLib)/1024/real_time      23971 ns        23962 ns        29222
ComplexBlob(YACLib)/2048/real_time      26923 ns        26913 ns        26060
ComplexBlob(YACLib)/4096/real_time      39610 ns        39596 ns        17695
ComplexBlob(YACLib)/8192/real_time      96408 ns        96357 ns         7278
NoContention(YACLib)/real_time         588388 ns       286316 ns         1187
Contention(YACLib)/real_time           893560 ns       184694 ns          781
2022-03-18T07:55:05+03:00
Running ./build_clang_libstdcxx/future/future
Run on (16 X 4017.63 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 512 KiB (x8)
  L3 Unified 16384 KiB (x2)
Load Average: 1.20, 1.31, 1.18
----------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations
----------------------------------------------------------------------------------
ConstantFuture(Std)/real_time                  112 ns          112 ns      6156156
ConstantFuture(YACLib)/real_time              16.8 ns         16.8 ns     40769431
ConstantFuture(Folly)/real_time               16.0 ns         16.0 ns     42784927
ConstantFuture(BoostThread)/real_time          106 ns          106 ns      6616728
PromiseAndFuture(Std)/real_time                121 ns          121 ns      5768659
PromiseAndFuture(YACLib)/real_time            30.5 ns         30.5 ns     22958531
PromiseAndFuture(Folly)/real_time             79.1 ns         79.0 ns      8869973
PromiseAndFuture(BoostThread)/real_time        124 ns          124 ns      5673709
Then(YACLib)/0/0/real_time                    76.2 ns         76.2 ns      9322278
Then(YACLib)/1/0/real_time                     159 ns          159 ns      4438494
Then(YACLib)/2/0/real_time                     223 ns          223 ns      3134230
Then(YACLib)/4/0/real_time                     362 ns          361 ns      1934567
Then(YACLib)/8/0/real_time                     611 ns          611 ns      1146791
Then(YACLib)/16/0/real_time                   1132 ns         1132 ns       626002
Then(YACLib)/32/0/real_time                   2170 ns         2169 ns       321704
Then(YACLib)/64/0/real_time                   4297 ns         4296 ns       162963
Then(YACLib)/0/1/real_time                    4889 ns         2458 ns       146076
Then(YACLib)/1/1/real_time                    5001 ns         2591 ns       141355
Then(YACLib)/2/1/real_time                    5040 ns         2661 ns       135228
Then(YACLib)/4/1/real_time                    5430 ns         2876 ns       126815
Then(YACLib)/8/1/real_time                    5931 ns         3417 ns       121361
Then(YACLib)/16/1/real_time                   7003 ns         4362 ns       102768
Then(YACLib)/32/1/real_time                   8168 ns         5937 ns        87266
Then(YACLib)/64/1/real_time                  10595 ns        10206 ns        65138
Then(YACLib)/0/2/real_time                    4906 ns         2518 ns       143021
Then(YACLib)/1/2/real_time                    5189 ns         2822 ns       139756
Then(YACLib)/2/2/real_time                    5367 ns         2968 ns       132758
Then(YACLib)/4/2/real_time                    5892 ns         3419 ns       118683
Then(YACLib)/8/2/real_time                    6791 ns         3989 ns       103045
Then(YACLib)/16/2/real_time                  11367 ns         8226 ns        61514
Then(YACLib)/32/2/real_time                  19872 ns        16417 ns        35307
Then(YACLib)/64/2/real_time                  36838 ns        33215 ns        18980
Then(Folly)/0/0/real_time                      160 ns          160 ns      4515628
Then(Folly)/1/0/real_time                      345 ns          345 ns      2040334
Then(Folly)/2/0/real_time                      546 ns          545 ns      1285813
Then(Folly)/4/0/real_time                      904 ns          904 ns       763026
Then(Folly)/8/0/real_time                     1637 ns         1637 ns       419971
Then(Folly)/16/0/real_time                    3158 ns         3157 ns       222842
Then(Folly)/32/0/real_time                    6129 ns         6128 ns       114114
Then(Folly)/64/0/real_time                   11779 ns        11776 ns        59576
Then(Folly)/0/1/real_time                     5209 ns         3085 ns       128739
Then(Folly)/1/1/real_time                     5689 ns         3409 ns       120162
Then(Folly)/2/1/real_time                     5917 ns         3650 ns       115761
Then(Folly)/4/1/real_time                     6472 ns         4238 ns       111942
Then(Folly)/8/1/real_time                     7362 ns         4778 ns        96171
Then(Folly)/16/1/real_time                    9524 ns         6231 ns        73282
Then(Folly)/32/1/real_time                   26083 ns        18668 ns        30455
Then(Folly)/64/1/real_time                   48460 ns        34269 ns        14928
Then(Folly)/0/2/real_time                     5188 ns         3096 ns       134677
Then(Folly)/1/2/real_time                     5670 ns         3304 ns       121458
Then(Folly)/2/2/real_time                     6387 ns         3594 ns       107939
Then(Folly)/4/2/real_time                     7446 ns         4351 ns        92059
Then(Folly)/8/2/real_time                     9169 ns         5466 ns        77669
Then(Folly)/16/2/real_time                   14705 ns         8866 ns        43150
Then(Folly)/32/2/real_time                   29602 ns        18615 ns        24910
Then(Folly)/64/2/real_time                   51512 ns        32078 ns        13532
Then(BoostThread)/0/0/real_time                547 ns          547 ns      1269871
Then(BoostThread)/1/0/real_time               1168 ns         1167 ns       600113
Then(BoostThread)/2/0/real_time               1790 ns         1790 ns       390425
Then(BoostThread)/4/0/real_time               3024 ns         3023 ns       232130
Then(BoostThread)/8/0/real_time               5567 ns         5566 ns       127031
Then(BoostThread)/16/0/real_time             10453 ns        10450 ns        66685
Then(BoostThread)/32/0/real_time             20653 ns        20647 ns        34209
Then(BoostThread)/64/0/real_time             39828 ns        39817 ns        17232
Then(BoostThread)/0/1/real_time               6038 ns         3508 ns       111657
Then(BoostThread)/1/1/real_time               7433 ns         4763 ns        97979
Then(BoostThread)/2/1/real_time               7962 ns         5419 ns        89739
Then(BoostThread)/4/1/real_time               9144 ns         7010 ns        76927
Then(BoostThread)/8/1/real_time              13940 ns        11857 ns        53387
Then(BoostThread)/16/1/real_time             26165 ns        24010 ns        26956
Then(BoostThread)/32/1/real_time             45001 ns        42894 ns        15659
Then(BoostThread)/64/1/real_time             78622 ns        76358 ns         8851
Then(BoostThread)/0/2/real_time               6402 ns         3785 ns       108115
Then(BoostThread)/1/2/real_time               8647 ns         5549 ns        80276
Then(BoostThread)/2/2/real_time               9988 ns         7001 ns        70126
Then(BoostThread)/4/2/real_time              15500 ns        10502 ns        45183
Then(BoostThread)/8/2/real_time              24307 ns        16841 ns        28858
Then(BoostThread)/16/2/real_time             40038 ns        27873 ns        17463
Then(BoostThread)/32/2/real_time             68656 ns        48551 ns        10208
Then(BoostThread)/64/2/real_time            131929 ns        93894 ns         5296
ComplexBlob(YACLib)/0/real_time              12579 ns        12576 ns        55663
ComplexBlob(Folly)/0/real_time               29952 ns        29943 ns        23440
ComplexBlob(BoostThread)/0/real_time         96649 ns        90064 ns         7256
ComplexBlob(YACLib)/2/real_time              10243 ns        10240 ns        67051
ComplexBlob(Folly)/2/real_time               30084 ns        30075 ns        23214
ComplexBlob(BoostThread)/2/real_time         96979 ns        90401 ns         7105
ComplexBlob(YACLib)/4/real_time              10093 ns        10091 ns        69127
ComplexBlob(Folly)/4/real_time               30999 ns        30992 ns        22469
ComplexBlob(BoostThread)/4/real_time         96912 ns        90310 ns         7301
ComplexBlob(YACLib)/8/real_time              10032 ns        10030 ns        68549
ComplexBlob(Folly)/8/real_time               30537 ns        30529 ns        22754
ComplexBlob(BoostThread)/8/real_time         97146 ns        90555 ns         7242
ComplexBlob(YACLib)/16/real_time             11098 ns        11096 ns        61687
ComplexBlob(Folly)/16/real_time              31709 ns        31702 ns        22036
ComplexBlob(BoostThread)/16/real_time        97708 ns        91110 ns         7103
ComplexBlob(YACLib)/32/real_time             10744 ns        10742 ns        64415
ComplexBlob(Folly)/32/real_time              29768 ns        29760 ns        23455
ComplexBlob(BoostThread)/32/real_time        98257 ns        91663 ns         7148
ComplexBlob(YACLib)/64/real_time             11491 ns        11489 ns        60041
ComplexBlob(Folly)/64/real_time              29966 ns        29959 ns        23259
ComplexBlob(BoostThread)/64/real_time        98138 ns        91246 ns         7105
ComplexBlob(YACLib)/128/real_time            13027 ns        13025 ns        53111
ComplexBlob(Folly)/128/real_time             31700 ns        31690 ns        22179
ComplexBlob(BoostThread)/128/real_time       98999 ns        92408 ns         7125
ComplexBlob(YACLib)/256/real_time            12748 ns        12745 ns        54186
ComplexBlob(Folly)/256/real_time             33469 ns        33461 ns        20980
ComplexBlob(BoostThread)/256/real_time      100017 ns        93181 ns         7046
ComplexBlob(YACLib)/512/real_time            14263 ns        14259 ns        48607
ComplexBlob(Folly)/512/real_time             34562 ns        34552 ns        20198
ComplexBlob(BoostThread)/512/real_time       99516 ns        92995 ns         6955
ComplexBlob(YACLib)/1024/real_time           24617 ns        24612 ns        28058
ComplexBlob(Folly)/1024/real_time            42147 ns        42134 ns        16575
ComplexBlob(BoostThread)/1024/real_time     124979 ns       118476 ns         5572
ComplexBlob(YACLib)/2048/real_time           27694 ns        27687 ns        25084
ComplexBlob(Folly)/2048/real_time            48106 ns        48093 ns        14454
ComplexBlob(BoostThread)/2048/real_time     126542 ns       119859 ns         5498
ComplexBlob(YACLib)/4096/real_time           39764 ns        39755 ns        17524
ComplexBlob(Folly)/4096/real_time            66162 ns        66136 ns        10524
ComplexBlob(BoostThread)/4096/real_time     138609 ns       132021 ns         4999
ComplexBlob(YACLib)/8192/real_time           89528 ns        89489 ns         7718
ComplexBlob(Folly)/8192/real_time           121505 ns       121444 ns         5750
ComplexBlob(BoostThread)/8192/real_time     181234 ns       174252 ns         3845
NoContention(YACLib)/real_time              622123 ns       282060 ns         1136
NoContention(Folly)/real_time              1935653 ns      1024220 ns          360
NoContention(BoostThread)/real_time        5898002 ns      3319338 ns          116
Contention(YACLib)/real_time                915654 ns       187521 ns          770
Contention(Folly)/real_time                2968518 ns       693210 ns          238
Contention(BoostThread)/real_time          6399099 ns      2288040 ns          112
2022-03-18T07:57:01+03:00
Running ./build_gcc_libstdcxx/future/future
Run on (16 X 3654.95 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 512 KiB (x8)
  L3 Unified 16384 KiB (x2)
Load Average: 1.42, 1.35, 1.21
----------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations
----------------------------------------------------------------------------------
ConstantFuture(Std)/real_time                  119 ns          119 ns      5894510
ConstantFuture(YACLib)/real_time              17.0 ns         17.0 ns     40305884
ConstantFuture(Folly)/real_time               18.2 ns         18.1 ns     38458845
ConstantFuture(BoostThread)/real_time          109 ns          109 ns      6463834
PromiseAndFuture(Std)/real_time                122 ns          122 ns      5747624
PromiseAndFuture(YACLib)/real_time            24.6 ns         24.6 ns     27925338
PromiseAndFuture(Folly)/real_time             70.1 ns         70.1 ns     10195437
PromiseAndFuture(BoostThread)/real_time        138 ns          138 ns      5158575
Then(YACLib)/0/0/real_time                    73.0 ns         73.0 ns      9604960
Then(YACLib)/1/0/real_time                     156 ns          156 ns      4457361
Then(YACLib)/2/0/real_time                     232 ns          232 ns      3006679
Then(YACLib)/4/0/real_time                     391 ns          391 ns      1795859
Then(YACLib)/8/0/real_time                     686 ns          686 ns      1017590
Then(YACLib)/16/0/real_time                   1284 ns         1284 ns       547692
Then(YACLib)/32/0/real_time                   2458 ns         2458 ns       285686
Then(YACLib)/64/0/real_time                   4872 ns         4871 ns       143530
Then(YACLib)/0/1/real_time                    4833 ns         2465 ns       146525
Then(YACLib)/1/1/real_time                    5116 ns         2665 ns       100000
Then(YACLib)/2/1/real_time                    5004 ns         2613 ns       139007
Then(YACLib)/4/1/real_time                    5317 ns         2887 ns       128477
Then(YACLib)/8/1/real_time                    6082 ns         3516 ns       117792
Then(YACLib)/16/1/real_time                   6783 ns         4358 ns       100354
Then(YACLib)/32/1/real_time                   8211 ns         6038 ns        84307
Then(YACLib)/64/1/real_time                  11074 ns        10705 ns        62509
Then(YACLib)/0/2/real_time                    4814 ns         2463 ns       145464
Then(YACLib)/1/2/real_time                    4946 ns         2661 ns       140922
Then(YACLib)/2/2/real_time                    5244 ns         2930 ns       131021
Then(YACLib)/4/2/real_time                    5732 ns         3277 ns       119791
Then(YACLib)/8/2/real_time                    6883 ns         4006 ns       101738
Then(YACLib)/16/2/real_time                  11266 ns         8038 ns        62957
Then(YACLib)/32/2/real_time                  19494 ns        15869 ns        35893
Then(YACLib)/64/2/real_time                  37440 ns        33933 ns        18800
Then(Folly)/0/0/real_time                      144 ns          144 ns      4776681
Then(Folly)/1/0/real_time                      308 ns          308 ns      2259576
Then(Folly)/2/0/real_time                      494 ns          494 ns      1400855
Then(Folly)/4/0/real_time                      821 ns          821 ns       845165
Then(Folly)/8/0/real_time                     1494 ns         1494 ns       460560
Then(Folly)/16/0/real_time                    2851 ns         2850 ns       244362
Then(Folly)/32/0/real_time                    5546 ns         5544 ns       125787
Then(Folly)/64/0/real_time                   10908 ns        10905 ns        65550
Then(Folly)/0/1/real_time                     5149 ns         2972 ns       135879
Then(Folly)/1/1/real_time                     5618 ns         3243 ns       124886
Then(Folly)/2/1/real_time                     5632 ns         3477 ns       124859
Then(Folly)/4/1/real_time                     6066 ns         3937 ns       114517
Then(Folly)/8/1/real_time                     6522 ns         4112 ns       107643
Then(Folly)/16/1/real_time                    8340 ns         5973 ns        83652
Then(Folly)/32/1/real_time                   23435 ns        17166 ns        29451
Then(Folly)/64/1/real_time                   46441 ns        33982 ns        15255
Then(Folly)/0/2/real_time                     4982 ns         2950 ns       134919
Then(Folly)/1/2/real_time                     5783 ns         3267 ns       118787
Then(Folly)/2/2/real_time                     6505 ns         3625 ns       106015
Then(Folly)/4/2/real_time                     8193 ns         4404 ns        85413
Then(Folly)/8/2/real_time                    10242 ns         5612 ns        71074
Then(Folly)/16/2/real_time                   17767 ns         9441 ns        39503
Then(Folly)/32/2/real_time                   30080 ns        17249 ns        22032
Then(Folly)/64/2/real_time                   56798 ns        32621 ns        12481
Then(BoostThread)/0/0/real_time                556 ns          555 ns      1245226
Then(BoostThread)/1/0/real_time               1187 ns         1187 ns       590052
Then(BoostThread)/2/0/real_time               1824 ns         1823 ns       383706
Then(BoostThread)/4/0/real_time               3077 ns         3076 ns       227665
Then(BoostThread)/8/0/real_time               5595 ns         5590 ns       125550
Then(BoostThread)/16/0/real_time             10635 ns        10632 ns        65850
Then(BoostThread)/32/0/real_time             20643 ns        20627 ns        33838
Then(BoostThread)/64/0/real_time             40624 ns        40610 ns        17181
Then(BoostThread)/0/1/real_time               6222 ns         3711 ns       112102
Then(BoostThread)/1/1/real_time               7296 ns         4677 ns       100751
Then(BoostThread)/2/1/real_time               7759 ns         5436 ns        89949
Then(BoostThread)/4/1/real_time               9155 ns         6879 ns        74880
Then(BoostThread)/8/1/real_time              13233 ns        10797 ns        54681
Then(BoostThread)/16/1/real_time             25598 ns        23510 ns        27716
Then(BoostThread)/32/1/real_time             43678 ns        41564 ns        16044
Then(BoostThread)/64/1/real_time             77199 ns        74989 ns         9219
Then(BoostThread)/0/2/real_time               6362 ns         3801 ns       110915
Then(BoostThread)/1/2/real_time               8415 ns         5279 ns        83560
Then(BoostThread)/2/2/real_time               9828 ns         6765 ns        71315
Then(BoostThread)/4/2/real_time              15130 ns        10275 ns        46437
Then(BoostThread)/8/2/real_time              23938 ns        16504 ns        29340
Then(BoostThread)/16/2/real_time             39916 ns        27892 ns        17556
Then(BoostThread)/32/2/real_time             69197 ns        48924 ns        14886
Then(BoostThread)/64/2/real_time            136685 ns        98972 ns         5109
ComplexBlob(YACLib)/0/real_time              12519 ns        12516 ns        56668
ComplexBlob(Folly)/0/real_time               33217 ns        33207 ns        20994
ComplexBlob(BoostThread)/0/real_time         98388 ns        91866 ns         7095
ComplexBlob(YACLib)/2/real_time              11938 ns        11934 ns        57446
ComplexBlob(Folly)/2/real_time               33478 ns        33469 ns        20703
ComplexBlob(BoostThread)/2/real_time         98479 ns        91859 ns         7044
ComplexBlob(YACLib)/4/real_time              11054 ns        11051 ns        61572
ComplexBlob(Folly)/4/real_time               33888 ns        33878 ns        20531
ComplexBlob(BoostThread)/4/real_time         98606 ns        92032 ns         7062
ComplexBlob(YACLib)/8/real_time              10712 ns        10709 ns        64510
ComplexBlob(Folly)/8/real_time               33671 ns        33647 ns        20826
ComplexBlob(BoostThread)/8/real_time         98838 ns        92107 ns         7109
ComplexBlob(YACLib)/16/real_time             11385 ns        11381 ns        60270
ComplexBlob(Folly)/16/real_time              33703 ns        33690 ns        20615
ComplexBlob(BoostThread)/16/real_time        98359 ns        91475 ns         7095
ComplexBlob(YACLib)/32/real_time             11481 ns        11478 ns        60345
ComplexBlob(Folly)/32/real_time              33635 ns        33625 ns        20811
ComplexBlob(BoostThread)/32/real_time        99484 ns        92760 ns         6868
ComplexBlob(YACLib)/64/real_time             12244 ns        12241 ns        57938
ComplexBlob(Folly)/64/real_time              33233 ns        33222 ns        21215
ComplexBlob(BoostThread)/64/real_time        99383 ns        92604 ns         6983
ComplexBlob(YACLib)/128/real_time            14026 ns        14023 ns        49703
ComplexBlob(Folly)/128/real_time             35297 ns        35288 ns        19739
ComplexBlob(BoostThread)/128/real_time       99154 ns        92405 ns         6874
ComplexBlob(YACLib)/256/real_time            13538 ns        13534 ns        51392
ComplexBlob(Folly)/256/real_time             35927 ns        35917 ns        19471
ComplexBlob(BoostThread)/256/real_time       99650 ns        92748 ns         6909
ComplexBlob(YACLib)/512/real_time            20331 ns        20325 ns        34097
ComplexBlob(Folly)/512/real_time             45661 ns        45646 ns        15347
ComplexBlob(BoostThread)/512/real_time      104918 ns        98320 ns         6592
ComplexBlob(YACLib)/1024/real_time           30972 ns        30964 ns        22571
ComplexBlob(Folly)/1024/real_time            52078 ns        52061 ns        13422
ComplexBlob(BoostThread)/1024/real_time     128506 ns       121194 ns         5449
ComplexBlob(YACLib)/2048/real_time           33421 ns        33411 ns        20933
ComplexBlob(Folly)/2048/real_time            57463 ns        57446 ns        12201
ComplexBlob(BoostThread)/2048/real_time     132999 ns       126415 ns         5157
ComplexBlob(YACLib)/4096/real_time           43310 ns        43298 ns        16183
ComplexBlob(Folly)/4096/real_time            90423 ns        90386 ns         7747
ComplexBlob(BoostThread)/4096/real_time     145929 ns       138628 ns         4703
ComplexBlob(YACLib)/8192/real_time           98164 ns        98118 ns         7079
ComplexBlob(Folly)/8192/real_time           175384 ns       175292 ns         3990
ComplexBlob(BoostThread)/8192/real_time     189308 ns       182120 ns         3693
NoContention(YACLib)/real_time              553765 ns       273098 ns         1253
NoContention(Folly)/real_time              1234327 ns       565901 ns          569
NoContention(BoostThread)/real_time        6389211 ns      3720666 ns          109
Contention(YACLib)/real_time                880683 ns       189365 ns          806
Contention(Folly)/real_time                3039814 ns       645325 ns          227
Contention(BoostThread)/real_time          6182179 ns      2240055 ns          115
```
