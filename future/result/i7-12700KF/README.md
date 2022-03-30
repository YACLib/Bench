```2022-03-30T16:54:44+03:00
Running ./build_clang_libcxx/future/future
Run on (20 X 3609.6 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 25600 KiB (x1)
Load Average: 0.73, 1.49, 1.20
-----------------------------------------------------------------------------
Benchmark                                   Time             CPU   Iterations
-----------------------------------------------------------------------------
ConstantFuture(Std)/real_time            31.8 ns         31.8 ns     22190553
ConstantFuture(YACLib)/real_time         12.9 ns         12.9 ns     54425219
PromiseAndFuture(Std)/real_time          42.0 ns         42.0 ns     16666191
PromiseAndFuture(YACLib)/real_time       23.6 ns         23.6 ns     29757066
Then(YACLib)/0/0/real_time               51.6 ns         51.6 ns     13814340
Then(YACLib)/1/0/real_time                108 ns          108 ns      6449491
Then(YACLib)/2/0/real_time                163 ns          163 ns      4338925
Then(YACLib)/4/0/real_time                276 ns          276 ns      2537790
Then(YACLib)/8/0/real_time                498 ns          498 ns      1404833
Then(YACLib)/16/0/real_time               941 ns          941 ns       740001
Then(YACLib)/32/0/real_time              1813 ns         1813 ns       385745
Then(YACLib)/64/0/real_time              3581 ns         3581 ns       195741
Then(YACLib)/0/1/real_time              22629 ns        17947 ns        31719
Then(YACLib)/1/1/real_time              22633 ns        18097 ns        31213
Then(YACLib)/2/1/real_time              22817 ns        18246 ns        24594
Then(YACLib)/4/1/real_time              23345 ns        18675 ns        28679
Then(YACLib)/8/1/real_time              26533 ns        20614 ns        27884
Then(YACLib)/16/1/real_time             24612 ns        19967 ns        27022
Then(YACLib)/32/1/real_time             27010 ns        21976 ns        27467
Then(YACLib)/64/1/real_time             26491 ns        23182 ns        25875
Then(YACLib)/0/2/real_time              24122 ns        18788 ns        30608
Then(YACLib)/1/2/real_time              23173 ns        18220 ns        29999
Then(YACLib)/2/2/real_time              25244 ns        19339 ns        29579
Then(YACLib)/4/2/real_time              24043 ns        18557 ns        29058
Then(YACLib)/8/2/real_time              26520 ns        19993 ns        29613
Then(YACLib)/16/2/real_time             25730 ns        19769 ns        27449
Then(YACLib)/32/2/real_time             30315 ns        22259 ns        25301
Then(YACLib)/64/2/real_time             31999 ns        23949 ns        21286
ComplexBlob(YACLib)/0/real_time         10374 ns        10374 ns        67308
ComplexBlob(YACLib)/2/real_time          9801 ns         9801 ns        71469
ComplexBlob(YACLib)/4/real_time          9827 ns         9827 ns        71541
ComplexBlob(YACLib)/8/real_time          9805 ns         9805 ns        71593
ComplexBlob(YACLib)/16/real_time        11154 ns        11154 ns        62962
ComplexBlob(YACLib)/32/real_time        11125 ns        11125 ns        62780
ComplexBlob(YACLib)/64/real_time        10069 ns        10069 ns        69875
ComplexBlob(YACLib)/128/real_time       10646 ns        10646 ns        65945
ComplexBlob(YACLib)/256/real_time       11458 ns        11458 ns        60897
ComplexBlob(YACLib)/512/real_time       11793 ns        11793 ns        58843
ComplexBlob(YACLib)/1024/real_time      19296 ns        19296 ns        36463
ComplexBlob(YACLib)/2048/real_time      22367 ns        22367 ns        31275
ComplexBlob(YACLib)/4096/real_time      32531 ns        32531 ns        21726
ComplexBlob(YACLib)/8192/real_time     127390 ns       127390 ns         5476
NoContention(YACLib)/real_time         601443 ns       302777 ns         1076
Contention(YACLib)/real_time           757511 ns       214086 ns          937
2022-03-30T16:55:25+03:00
Running ./build_clang_libstdcxx/future/future
Run on (20 X 3609.6 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 25600 KiB (x1)
Load Average: 0.79, 1.40, 1.18
----------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations
----------------------------------------------------------------------------------
ConstantFuture(Std)/real_time                 91.3 ns         91.3 ns      7526855
ConstantFuture(YACLib)/real_time              12.7 ns         12.7 ns     54310592
ConstantFuture(Folly)/real_time               12.4 ns         12.4 ns     57598706
ConstantFuture(BoostThread)/real_time         88.2 ns         88.2 ns      7986037
PromiseAndFuture(Std)/real_time               96.3 ns         96.3 ns      7013497
PromiseAndFuture(YACLib)/real_time            22.4 ns         22.4 ns     30838971
PromiseAndFuture(Folly)/real_time             49.0 ns         49.0 ns     14279965
PromiseAndFuture(BoostThread)/real_time       92.3 ns         92.3 ns      7542843
Then(YACLib)/0/0/real_time                    54.9 ns         54.9 ns     12825362
Then(YACLib)/1/0/real_time                     111 ns          111 ns      6207085
Then(YACLib)/2/0/real_time                     168 ns          168 ns      4195324
Then(YACLib)/4/0/real_time                     284 ns          284 ns      2479942
Then(YACLib)/8/0/real_time                     510 ns          510 ns      1360601
Then(YACLib)/16/0/real_time                    961 ns          961 ns       710419
Then(YACLib)/32/0/real_time                   1868 ns         1868 ns       376092
Then(YACLib)/64/0/real_time                   3646 ns         3646 ns       192112
Then(YACLib)/0/1/real_time                   23072 ns        18173 ns        30602
Then(YACLib)/1/1/real_time                   22938 ns        18229 ns        28529
Then(YACLib)/2/1/real_time                   22915 ns        18264 ns        24189
Then(YACLib)/4/1/real_time                   23306 ns        18642 ns        30023
Then(YACLib)/8/1/real_time                   25767 ns        20203 ns        29130
Then(YACLib)/16/1/real_time                  24621 ns        20051 ns        28781
Then(YACLib)/32/1/real_time                  27187 ns        22144 ns        27410
Then(YACLib)/64/1/real_time                  27358 ns        23541 ns        26298
Then(YACLib)/0/2/real_time                   24657 ns        19039 ns        31663
Then(YACLib)/1/2/real_time                   23234 ns        18163 ns        28119
Then(YACLib)/2/2/real_time                   25039 ns        19298 ns        28815
Then(YACLib)/4/2/real_time                   24177 ns        18656 ns        29070
Then(YACLib)/8/2/real_time                   26075 ns        19834 ns        28303
Then(YACLib)/16/2/real_time                  26422 ns        19965 ns        27358
Then(YACLib)/32/2/real_time                  27420 ns        20722 ns        25907
Then(YACLib)/64/2/real_time                  32485 ns        24018 ns        20179
Then(Folly)/0/0/real_time                     97.0 ns         97.0 ns      7167378
Then(Folly)/1/0/real_time                      217 ns          217 ns      3212924
Then(Folly)/2/0/real_time                      350 ns          350 ns      2041123
Then(Folly)/4/0/real_time                      605 ns          605 ns      1149099
Then(Folly)/8/0/real_time                     1112 ns         1112 ns       628177
Then(Folly)/16/0/real_time                    2131 ns         2131 ns       330572
Then(Folly)/32/0/real_time                    4143 ns         4143 ns       169298
Then(Folly)/64/0/real_time                    8150 ns         8150 ns        85466
Then(Folly)/0/1/real_time                    23274 ns        18630 ns        29867
Then(Folly)/1/1/real_time                    23506 ns        18910 ns        30455
Then(Folly)/2/1/real_time                    23569 ns        19020 ns        24018
Then(Folly)/4/1/real_time                    24055 ns        19416 ns        29448
Then(Folly)/8/1/real_time                    26283 ns        20832 ns        28412
Then(Folly)/16/1/real_time                   26407 ns        21235 ns        27855
Then(Folly)/32/1/real_time                   29041 ns        23486 ns        25592
Then(Folly)/64/1/real_time                   37692 ns        30733 ns        18611
Then(Folly)/0/2/real_time                    24609 ns        19572 ns        30817
Then(Folly)/1/2/real_time                    23683 ns        18936 ns        30235
Then(Folly)/2/2/real_time                    24902 ns        19593 ns        29723
Then(Folly)/4/2/real_time                    24541 ns        19271 ns        29215
Then(Folly)/8/2/real_time                    28168 ns        21146 ns        27971
Then(Folly)/16/2/real_time                   28015 ns        20788 ns        25662
Then(Folly)/32/2/real_time                   33851 ns        23676 ns        22577
Then(Folly)/64/2/real_time                   47032 ns        34137 ns        14646
Then(BoostThread)/0/0/real_time                556 ns          556 ns      1268525
Then(BoostThread)/1/0/real_time               1202 ns         1202 ns       582523
Then(BoostThread)/2/0/real_time               1831 ns         1831 ns       382391
Then(BoostThread)/4/0/real_time               3078 ns         3078 ns       227256
Then(BoostThread)/8/0/real_time               5575 ns         5575 ns       125889
Then(BoostThread)/16/0/real_time             10568 ns        10568 ns        66568
Then(BoostThread)/32/0/real_time             20556 ns        20556 ns        34086
Then(BoostThread)/64/0/real_time             40419 ns        40419 ns        17289
Then(BoostThread)/0/1/real_time              23649 ns        19064 ns        29746
Then(BoostThread)/1/1/real_time              26033 ns        20764 ns        28260
Then(BoostThread)/2/1/real_time              24743 ns        20492 ns        26444
Then(BoostThread)/4/1/real_time              28977 ns        23428 ns        26203
Then(BoostThread)/8/1/real_time              28835 ns        24649 ns        23762
Then(BoostThread)/16/1/real_time             35420 ns        30485 ns        20764
Then(BoostThread)/32/1/real_time             42184 ns        39244 ns        15579
Then(BoostThread)/64/1/real_time             62011 ns        58879 ns         9817
Then(BoostThread)/0/2/real_time              22804 ns        18540 ns        23752
Then(BoostThread)/1/2/real_time              24603 ns        19469 ns        28101
Then(BoostThread)/2/2/real_time              27617 ns        21262 ns        27164
Then(BoostThread)/4/2/real_time              27392 ns        21404 ns        25431
Then(BoostThread)/8/2/real_time              31255 ns        24553 ns        21881
Then(BoostThread)/16/2/real_time             40047 ns        30260 ns        16978
Then(BoostThread)/32/2/real_time             60102 ns        42451 ns        12287
Then(BoostThread)/64/2/real_time             95847 ns        67205 ns         5980
ComplexBlob(YACLib)/0/real_time              10438 ns        10438 ns        67453
ComplexBlob(Folly)/0/real_time               21264 ns        21264 ns        32935
ComplexBlob(BoostThread)/0/real_time        110336 ns       105043 ns         5947
ComplexBlob(YACLib)/2/real_time               9433 ns         9433 ns        74691
ComplexBlob(Folly)/2/real_time               21227 ns        21227 ns        32749
ComplexBlob(BoostThread)/2/real_time        142007 ns       123412 ns         4863
ComplexBlob(YACLib)/4/real_time               9611 ns         9611 ns        72343
ComplexBlob(Folly)/4/real_time               22262 ns        22262 ns        32056
ComplexBlob(BoostThread)/4/real_time        116186 ns       109158 ns         6344
ComplexBlob(YACLib)/8/real_time               9430 ns         9430 ns        74025
ComplexBlob(Folly)/8/real_time               21548 ns        21548 ns        32699
ComplexBlob(BoostThread)/8/real_time        110599 ns       105153 ns         6055
ComplexBlob(YACLib)/16/real_time             10799 ns        10799 ns        64225
ComplexBlob(Folly)/16/real_time              21471 ns        21471 ns        32880
ComplexBlob(BoostThread)/16/real_time       110121 ns       104643 ns         6396
ComplexBlob(YACLib)/32/real_time             10889 ns        10889 ns        64492
ComplexBlob(Folly)/32/real_time              21314 ns        21314 ns        32919
ComplexBlob(BoostThread)/32/real_time       141307 ns       122780 ns         4945
ComplexBlob(YACLib)/64/real_time             10057 ns        10057 ns        68993
ComplexBlob(Folly)/64/real_time              21389 ns        21389 ns        32829
ComplexBlob(BoostThread)/64/real_time       116505 ns       109359 ns         6337
ComplexBlob(YACLib)/128/real_time            10871 ns        10871 ns        64530
ComplexBlob(Folly)/128/real_time             21683 ns        21683 ns        32066
ComplexBlob(BoostThread)/128/real_time      115472 ns       108746 ns         6221
ComplexBlob(YACLib)/256/real_time            11054 ns        11054 ns        63596
ComplexBlob(Folly)/256/real_time             22712 ns        22712 ns        30662
ComplexBlob(BoostThread)/256/real_time      111918 ns       106382 ns         6314
ComplexBlob(YACLib)/512/real_time            11673 ns        11673 ns        59016
ComplexBlob(Folly)/512/real_time             23243 ns        23243 ns        30082
ComplexBlob(BoostThread)/512/real_time      112342 ns       106982 ns         6184
ComplexBlob(YACLib)/1024/real_time           19900 ns        19900 ns        35651
ComplexBlob(Folly)/1024/real_time            29935 ns        29935 ns        23513
ComplexBlob(BoostThread)/1024/real_time     131994 ns       125513 ns         5551
ComplexBlob(YACLib)/2048/real_time           22301 ns        22301 ns        30860
ComplexBlob(Folly)/2048/real_time            34580 ns        34579 ns        20406
ComplexBlob(BoostThread)/2048/real_time     131183 ns       125555 ns         5350
ComplexBlob(YACLib)/4096/real_time           32902 ns        32902 ns        21254
ComplexBlob(Folly)/4096/real_time            53338 ns        53338 ns        12004
ComplexBlob(BoostThread)/4096/real_time     140791 ns       135281 ns         4959
ComplexBlob(YACLib)/8192/real_time          107595 ns       107594 ns         6541
ComplexBlob(Folly)/8192/real_time           124842 ns       124841 ns         5606
ComplexBlob(BoostThread)/8192/real_time     196978 ns       189541 ns         3614
NoContention(YACLib)/real_time              593623 ns       289040 ns         1175
NoContention(Folly)/real_time              1021784 ns       432992 ns          685
NoContention(BoostThread)/real_time        3453957 ns      1723409 ns          201
Contention(YACLib)/real_time                756586 ns       217519 ns          931
Contention(Folly)/real_time                1694969 ns       500656 ns          412
Contention(BoostThread)/real_time          5449775 ns      1717421 ns          131
2022-03-30T16:57:27+03:00
Running ./build_gcc_libstdcxx/future/future
Run on (20 X 3609.6 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 25600 KiB (x1)
Load Average: 0.80, 1.21, 1.14
----------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations
----------------------------------------------------------------------------------
ConstantFuture(Std)/real_time                 90.7 ns         90.7 ns      7503359
ConstantFuture(YACLib)/real_time              14.2 ns         14.2 ns     49706168
ConstantFuture(Folly)/real_time               12.5 ns         12.5 ns     56565539
ConstantFuture(BoostThread)/real_time         93.9 ns         93.9 ns      7414307
PromiseAndFuture(Std)/real_time               96.6 ns         96.6 ns      7293234
PromiseAndFuture(YACLib)/real_time            21.5 ns         21.5 ns     32570108
PromiseAndFuture(Folly)/real_time             45.1 ns         45.1 ns     15249675
PromiseAndFuture(BoostThread)/real_time        100 ns          100 ns      6897154
Then(YACLib)/0/0/real_time                    51.9 ns         51.9 ns     13602421
Then(YACLib)/1/0/real_time                     108 ns          108 ns      6472077
Then(YACLib)/2/0/real_time                     165 ns          165 ns      4282840
Then(YACLib)/4/0/real_time                     280 ns          280 ns      2518463
Then(YACLib)/8/0/real_time                     508 ns          508 ns      1370937
Then(YACLib)/16/0/real_time                    968 ns          968 ns       713683
Then(YACLib)/32/0/real_time                   1874 ns         1874 ns       374649
Then(YACLib)/64/0/real_time                   3673 ns         3673 ns       188754
Then(YACLib)/0/1/real_time                   24263 ns        18802 ns        30236
Then(YACLib)/1/1/real_time                   22821 ns        18186 ns        30521
Then(YACLib)/2/1/real_time                   25491 ns        19691 ns        30541
Then(YACLib)/4/1/real_time                   23095 ns        18489 ns        29607
Then(YACLib)/8/1/real_time                   25427 ns        20046 ns        29528
Then(YACLib)/16/1/real_time                  24549 ns        19907 ns        28661
Then(YACLib)/32/1/real_time                  25389 ns        21011 ns        27449
Then(YACLib)/64/1/real_time                  26678 ns        23363 ns        22885
Then(YACLib)/0/2/real_time                   22325 ns        17795 ns        30872
Then(YACLib)/1/2/real_time                   24460 ns        18890 ns        27057
Then(YACLib)/2/2/real_time                   23494 ns        18333 ns        29538
Then(YACLib)/4/2/real_time                   25406 ns        19276 ns        29069
Then(YACLib)/8/2/real_time                   23882 ns        18604 ns        28507
Then(YACLib)/16/2/real_time                  27142 ns        20662 ns        27920
Then(YACLib)/32/2/real_time                  27026 ns        20645 ns        25466
Then(YACLib)/64/2/real_time                  34960 ns        27127 ns        20507
Then(Folly)/0/0/real_time                     98.0 ns         98.0 ns      7143331
Then(Folly)/1/0/real_time                      213 ns          213 ns      3283409
Then(Folly)/2/0/real_time                      326 ns          326 ns      2155036
Then(Folly)/4/0/real_time                      564 ns          564 ns      1241127
Then(Folly)/8/0/real_time                     1021 ns         1021 ns       682203
Then(Folly)/16/0/real_time                    1936 ns         1936 ns       359192
Then(Folly)/32/0/real_time                    3766 ns         3766 ns       184719
Then(Folly)/64/0/real_time                    7432 ns         7432 ns        94865
Then(Folly)/0/1/real_time                    24573 ns        19513 ns        30339
Then(Folly)/1/1/real_time                    23239 ns        18833 ns        30059
Then(Folly)/2/1/real_time                    23300 ns        18882 ns        29808
Then(Folly)/4/1/real_time                    23204 ns        18996 ns        25386
Then(Folly)/8/1/real_time                    24516 ns        19983 ns        27914
Then(Folly)/16/1/real_time                   25144 ns        20656 ns        23857
Then(Folly)/32/1/real_time                   27605 ns        22607 ns        25477
Then(Folly)/64/1/real_time                   37133 ns        30393 ns        19311
Then(Folly)/0/2/real_time                    22725 ns        18499 ns        30175
Then(Folly)/1/2/real_time                    25233 ns        19646 ns        29819
Then(Folly)/2/2/real_time                    23747 ns        18958 ns        28752
Then(Folly)/4/2/real_time                    26162 ns        20137 ns        28644
Then(Folly)/8/2/real_time                    25465 ns        19692 ns        26806
Then(Folly)/16/2/real_time                   29647 ns        21724 ns        25117
Then(Folly)/32/2/real_time                   32171 ns        22845 ns        22048
Then(Folly)/64/2/real_time                   46493 ns        33299 ns        13858
Then(BoostThread)/0/0/real_time                572 ns          572 ns      1226472
Then(BoostThread)/1/0/real_time               1244 ns         1244 ns       562579
Then(BoostThread)/2/0/real_time               1896 ns         1896 ns       369270
Then(BoostThread)/4/0/real_time               3171 ns         3171 ns       219968
Then(BoostThread)/8/0/real_time               5763 ns         5763 ns       122146
Then(BoostThread)/16/0/real_time             10928 ns        10927 ns        63346
Then(BoostThread)/32/0/real_time             21180 ns        21180 ns        32996
Then(BoostThread)/64/0/real_time             41770 ns        41770 ns        16774
Then(BoostThread)/0/1/real_time              23019 ns        18718 ns        28933
Then(BoostThread)/1/1/real_time              26352 ns        21036 ns        27034
Then(BoostThread)/2/1/real_time              25388 ns        20857 ns        27427
Then(BoostThread)/4/1/real_time              29042 ns        23461 ns        26027
Then(BoostThread)/8/1/real_time              29095 ns        24841 ns        23354
Then(BoostThread)/16/1/real_time             36062 ns        31020 ns        20699
Then(BoostThread)/32/1/real_time             42810 ns        39968 ns        16221
Then(BoostThread)/64/1/real_time             65775 ns        61021 ns        10320
Then(BoostThread)/0/2/real_time              23079 ns        18635 ns        29307
Then(BoostThread)/1/2/real_time              26522 ns        20522 ns        27721
Then(BoostThread)/2/2/real_time              25322 ns        20059 ns        26542
Then(BoostThread)/4/2/real_time              30037 ns        22791 ns        24995
Then(BoostThread)/8/2/real_time              30486 ns        23979 ns        22100
Then(BoostThread)/16/2/real_time             43855 ns        31934 ns        17039
Then(BoostThread)/32/2/real_time             58038 ns        41808 ns        10086
Then(BoostThread)/64/2/real_time             98519 ns        67969 ns         6393
ComplexBlob(YACLib)/0/real_time               9733 ns         9733 ns        72095
ComplexBlob(Folly)/0/real_time               22361 ns        22361 ns        31670
ComplexBlob(BoostThread)/0/real_time        119684 ns       114095 ns         5024
ComplexBlob(YACLib)/2/real_time               9348 ns         9348 ns        74566
ComplexBlob(Folly)/2/real_time               21978 ns        21978 ns        31901
ComplexBlob(BoostThread)/2/real_time        114843 ns       109580 ns         6013
ComplexBlob(YACLib)/4/real_time               9318 ns         9318 ns        75369
ComplexBlob(Folly)/4/real_time               22100 ns        22100 ns        31362
ComplexBlob(BoostThread)/4/real_time        113046 ns       107550 ns         6166
ComplexBlob(YACLib)/8/real_time               9333 ns         9333 ns        74654
ComplexBlob(Folly)/8/real_time               22047 ns        22047 ns        31799
ComplexBlob(BoostThread)/8/real_time        112400 ns       107077 ns         6047
ComplexBlob(YACLib)/16/real_time             10624 ns        10624 ns        66432
ComplexBlob(Folly)/16/real_time              22101 ns        22101 ns        31982
ComplexBlob(BoostThread)/16/real_time       112436 ns       106910 ns         6234
ComplexBlob(YACLib)/32/real_time             10697 ns        10697 ns        65432
ComplexBlob(Folly)/32/real_time              22000 ns        22000 ns        31833
ComplexBlob(BoostThread)/32/real_time       118145 ns       111063 ns         6282
ComplexBlob(YACLib)/64/real_time              9900 ns         9900 ns        71195
ComplexBlob(Folly)/64/real_time              22563 ns        22563 ns        30840
ComplexBlob(BoostThread)/64/real_time       115245 ns       109009 ns         4933
ComplexBlob(YACLib)/128/real_time            10910 ns        10910 ns        63752
ComplexBlob(Folly)/128/real_time             23357 ns        23357 ns        30520
ComplexBlob(BoostThread)/128/real_time      116660 ns       110161 ns         5686
ComplexBlob(YACLib)/256/real_time            10555 ns        10555 ns        66911
ComplexBlob(Folly)/256/real_time             24114 ns        24114 ns        28953
ComplexBlob(BoostThread)/256/real_time      114419 ns       108725 ns         6161
ComplexBlob(YACLib)/512/real_time            14074 ns        14074 ns        49433
ComplexBlob(Folly)/512/real_time             28397 ns        28397 ns        24697
ComplexBlob(BoostThread)/512/real_time      130115 ns       123198 ns         5666
ComplexBlob(YACLib)/1024/real_time           21134 ns        21134 ns        32936
ComplexBlob(Folly)/1024/real_time            33142 ns        33143 ns        21140
ComplexBlob(BoostThread)/1024/real_time     144840 ns       139380 ns         4582
ComplexBlob(YACLib)/2048/real_time           23561 ns        23561 ns        29808
ComplexBlob(Folly)/2048/real_time            37955 ns        37955 ns        18016
ComplexBlob(BoostThread)/2048/real_time     156078 ns       150336 ns         4548
ComplexBlob(YACLib)/4096/real_time           32694 ns        32694 ns        21286
ComplexBlob(Folly)/4096/real_time            58421 ns        58421 ns        12155
ComplexBlob(BoostThread)/4096/real_time     184223 ns       176978 ns         3970
ComplexBlob(YACLib)/8192/real_time          105882 ns       105882 ns         6546
ComplexBlob(Folly)/8192/real_time           132458 ns       132458 ns         5296
ComplexBlob(BoostThread)/8192/real_time     252571 ns       245334 ns         2595
NoContention(YACLib)/real_time              572227 ns       288557 ns         1224
NoContention(Folly)/real_time               973385 ns       437487 ns          722
NoContention(BoostThread)/real_time        3516074 ns      1765353 ns          197
Contention(YACLib)/real_time                738195 ns       216684 ns          908
Contention(Folly)/real_time                1651140 ns       501430 ns          421
Contention(BoostThread)/real_time          5550196 ns      1724216 ns          128```