```
2022-03-03T14:37:59+02:00
Running ./build_clang_libcxx/future/future
Run on (24 X 3868.18 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 512 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.40, 0.62, 0.58
-----------------------------------------------------------------------------
Benchmark                                   Time             CPU   Iterations
-----------------------------------------------------------------------------
ConstantFuture(Std)/real_time            40.1 ns         40.1 ns     17311654
ConstantFuture(YACLib)/real_time         14.7 ns         14.7 ns     47576527
PromiseAndFuture(Std)/real_time          50.6 ns         50.5 ns     13722192
PromiseAndFuture(YACLib)/real_time       24.1 ns         24.0 ns     29130053
Then(YACLib)/0/0/real_time               53.4 ns         53.4 ns     13022811
Then(YACLib)/1/0/real_time                106 ns          106 ns      6630830
Then(YACLib)/2/0/real_time                157 ns          156 ns      4462874
Then(YACLib)/4/0/real_time                260 ns          259 ns      2697598
Then(YACLib)/8/0/real_time                468 ns          468 ns      1493153
Then(YACLib)/16/0/real_time               874 ns          873 ns       799576
Then(YACLib)/32/0/real_time              1685 ns         1684 ns       414559
Then(YACLib)/64/0/real_time              3306 ns         3303 ns       211406
Then(YACLib)/0/1/real_time               6277 ns         2939 ns       111903
Then(YACLib)/1/1/real_time               6404 ns         3018 ns       106708
Then(YACLib)/2/1/real_time               6520 ns         3130 ns       108367
Then(YACLib)/4/1/real_time               7018 ns         3456 ns       100018
Then(YACLib)/8/1/real_time               7499 ns         3914 ns        90044
Then(YACLib)/16/1/real_time              7434 ns         4704 ns       146120
Then(YACLib)/32/1/real_time              9331 ns         6286 ns        75205
Then(YACLib)/64/1/real_time             11649 ns        10074 ns        59201
Then(YACLib)/0/2/real_time               6119 ns         2926 ns       110322
Then(YACLib)/1/2/real_time               6476 ns         3242 ns       107495
Then(YACLib)/2/2/real_time               6651 ns         3405 ns       103714
Then(YACLib)/4/2/real_time               7064 ns         3782 ns        97820
Then(YACLib)/8/2/real_time               7810 ns         4426 ns        89725
Then(YACLib)/16/2/real_time              9693 ns         6143 ns       114959
Then(YACLib)/32/2/real_time             16717 ns        13125 ns        41626
Then(YACLib)/64/2/real_time             29783 ns        25353 ns        50140
ComplexBlob(YACLib)/0/real_time         11647 ns        11634 ns        61059
ComplexBlob(YACLib)/2/real_time          9941 ns         9930 ns        71457
ComplexBlob(YACLib)/4/real_time          9320 ns         9310 ns        75297
ComplexBlob(YACLib)/8/real_time          9518 ns         9507 ns        74014
ComplexBlob(YACLib)/16/real_time         8504 ns         8494 ns        84675
ComplexBlob(YACLib)/32/real_time        10292 ns        10281 ns        68065
ComplexBlob(YACLib)/64/real_time         9097 ns         9087 ns        76570
ComplexBlob(YACLib)/128/real_time        9216 ns         9206 ns        75929
ComplexBlob(YACLib)/256/real_time       11967 ns        11946 ns        57320
ComplexBlob(YACLib)/512/real_time       12335 ns        12324 ns        56389
ComplexBlob(YACLib)/1024/real_time      20265 ns        20242 ns        36187
ComplexBlob(YACLib)/2048/real_time      23781 ns        23755 ns        28852
ComplexBlob(YACLib)/4096/real_time      41707 ns        41659 ns        16775
ComplexBlob(YACLib)/8192/real_time     110379 ns       110226 ns         6330
NoContention(YACLib)/real_time         424548 ns       201957 ns         1645
Contention(YACLib)/real_time           680203 ns       150807 ns         1016
2022-03-03T14:38:40+02:00
Running ./build_clang_libstdcxx/future/future
Run on (24 X 3598.1 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 512 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.78, 0.69, 0.61
----------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations
----------------------------------------------------------------------------------
ConstantFuture(Std)/real_time                 94.8 ns         94.7 ns      7289575
ConstantFuture(YACLib)/real_time              14.6 ns         14.6 ns     48008978
ConstantFuture(Folly)/real_time               18.6 ns         18.6 ns     37068417
ConstantFuture(BoostThread)/real_time         76.1 ns         76.0 ns      9178531
PromiseAndFuture(Std)/real_time                100 ns         99.9 ns      6997605
PromiseAndFuture(YACLib)/real_time            22.5 ns         22.5 ns     30713481
PromiseAndFuture(Folly)/real_time             79.4 ns         79.4 ns      8790011
PromiseAndFuture(BoostThread)/real_time       83.8 ns         83.7 ns      8362422
Then(YACLib)/0/0/real_time                    57.9 ns         57.8 ns     12088320
Then(YACLib)/1/0/real_time                     112 ns          112 ns      6216822
Then(YACLib)/2/0/real_time                     166 ns          166 ns      4216832
Then(YACLib)/4/0/real_time                     273 ns          273 ns      2561500
Then(YACLib)/8/0/real_time                     490 ns          490 ns      1427283
Then(YACLib)/16/0/real_time                    911 ns          910 ns       764841
Then(YACLib)/32/0/real_time                   1754 ns         1753 ns       397373
Then(YACLib)/64/0/real_time                   3452 ns         3448 ns       203108
Then(YACLib)/0/1/real_time                    6324 ns         2995 ns       110462
Then(YACLib)/1/1/real_time                    6572 ns         3192 ns       165055
Then(YACLib)/2/1/real_time                    6728 ns         3322 ns       103941
Then(YACLib)/4/1/real_time                    6521 ns         3567 ns        99145
Then(YACLib)/8/1/real_time                    7483 ns         4008 ns        90127
Then(YACLib)/16/1/real_time                   8294 ns         5261 ns        85783
Then(YACLib)/32/1/real_time                   8895 ns         6780 ns       124396
Then(YACLib)/64/1/real_time                  11223 ns        10163 ns       105007
Then(YACLib)/0/2/real_time                    6405 ns         3025 ns       109334
Then(YACLib)/1/2/real_time                    6446 ns         3222 ns       105420
Then(YACLib)/2/2/real_time                    6607 ns         3407 ns       106989
Then(YACLib)/4/2/real_time                    6604 ns         3782 ns       103160
Then(YACLib)/8/2/real_time                    7730 ns         4478 ns        89513
Then(YACLib)/16/2/real_time                   9972 ns         6618 ns        70308
Then(YACLib)/32/2/real_time                  17020 ns        13391 ns        40931
Then(YACLib)/64/2/real_time                  29760 ns        25906 ns        23479
Then(Folly)/0/0/real_time                      179 ns          179 ns      3908223
Then(Folly)/1/0/real_time                      413 ns          413 ns      1701728
Then(Folly)/2/0/real_time                      648 ns          647 ns      1074107
Then(Folly)/4/0/real_time                     1121 ns         1119 ns       623630
Then(Folly)/8/0/real_time                     2052 ns         2050 ns       340695
Then(Folly)/16/0/real_time                    3916 ns         3912 ns       178702
Then(Folly)/32/0/real_time                    7652 ns         7644 ns        91443
Then(Folly)/64/0/real_time                   15103 ns        15087 ns        46222
Then(Folly)/0/1/real_time                     6249 ns         3380 ns       108878
Then(Folly)/1/1/real_time                     7343 ns         3827 ns        96113
Then(Folly)/2/1/real_time                     7575 ns         3975 ns        92117
Then(Folly)/4/1/real_time                     8301 ns         4630 ns        87557
Then(Folly)/8/1/real_time                     5937 ns         4343 ns        85018
Then(Folly)/16/1/real_time                    9282 ns         6057 ns        74975
Then(Folly)/32/1/real_time                   17459 ns        11518 ns        43919
Then(Folly)/64/1/real_time                   41056 ns        28552 ns        16921
Then(Folly)/0/2/real_time                     5949 ns         3271 ns       109750
Then(Folly)/1/2/real_time                     7510 ns         3865 ns        93263
Then(Folly)/2/2/real_time                     7632 ns         3898 ns        90324
Then(Folly)/4/2/real_time                     8318 ns         4703 ns        79862
Then(Folly)/8/2/real_time                    10282 ns         5551 ns        69748
Then(Folly)/16/2/real_time                   16126 ns         9601 ns        44366
Then(Folly)/32/2/real_time                   25691 ns        15335 ns        26046
Then(Folly)/64/2/real_time                   48206 ns        28849 ns        14649
Then(BoostThread)/0/0/real_time                279 ns          278 ns      2529229
Then(BoostThread)/1/0/real_time                633 ns          633 ns      1103563
Then(BoostThread)/2/0/real_time                990 ns          989 ns       711329
Then(BoostThread)/4/0/real_time               1704 ns         1702 ns       412080
Then(BoostThread)/8/0/real_time               3111 ns         3108 ns       224652
Then(BoostThread)/16/0/real_time              5923 ns         5916 ns       118004
Then(BoostThread)/32/0/real_time             11550 ns        11537 ns        60688
Then(BoostThread)/64/0/real_time             22883 ns        22858 ns        30821
Then(BoostThread)/0/1/real_time               7261 ns         3792 ns        96171
Then(BoostThread)/1/1/real_time               8224 ns         4689 ns        84855
Then(BoostThread)/2/1/real_time               8927 ns         5439 ns        77164
Then(BoostThread)/4/1/real_time               9715 ns         6061 ns        73629
Then(BoostThread)/8/1/real_time              11837 ns         8225 ns       101268
Then(BoostThread)/16/1/real_time             17411 ns        14982 ns        41907
Then(BoostThread)/32/1/real_time             30700 ns        28408 ns        22763
Then(BoostThread)/64/1/real_time             53791 ns        49683 ns        12850
Then(BoostThread)/0/2/real_time               7066 ns         3673 ns        96819
Then(BoostThread)/1/2/real_time               8981 ns         5151 ns        79059
Then(BoostThread)/2/2/real_time               9920 ns         6243 ns        69842
Then(BoostThread)/4/2/real_time              13902 ns         8825 ns        49613
Then(BoostThread)/8/2/real_time              21749 ns        13970 ns        67444
Then(BoostThread)/16/2/real_time             33978 ns        22060 ns        20347
Then(BoostThread)/32/2/real_time             55487 ns        36865 ns        12518
Then(BoostThread)/64/2/real_time            104351 ns        70975 ns        10000
ComplexBlob(YACLib)/0/real_time               9376 ns         9366 ns        74672
ComplexBlob(Folly)/0/real_time               32996 ns        32959 ns        21547
ComplexBlob(BoostThread)/0/real_time         68253 ns        62825 ns        10416
ComplexBlob(YACLib)/2/real_time               8023 ns         8015 ns        86948
ComplexBlob(Folly)/2/real_time               33131 ns        33095 ns        21424
ComplexBlob(BoostThread)/2/real_time         70439 ns        65058 ns        10032
ComplexBlob(YACLib)/4/real_time               9425 ns         9415 ns        74800
ComplexBlob(Folly)/4/real_time               32234 ns        32196 ns        21883
ComplexBlob(BoostThread)/4/real_time         69318 ns        63896 ns        10388
ComplexBlob(YACLib)/8/real_time               9942 ns         9931 ns        70418
ComplexBlob(Folly)/8/real_time               31619 ns        31585 ns        22190
ComplexBlob(BoostThread)/8/real_time         69704 ns        64181 ns        10269
ComplexBlob(YACLib)/16/real_time              8654 ns         8645 ns        80791
ComplexBlob(Folly)/16/real_time              31585 ns        31550 ns        22347
ComplexBlob(BoostThread)/16/real_time        70453 ns        65093 ns        10026
ComplexBlob(YACLib)/32/real_time             10008 ns         9995 ns        70235
ComplexBlob(Folly)/32/real_time              31418 ns        31383 ns        22384
ComplexBlob(BoostThread)/32/real_time        70395 ns        64943 ns         9981
ComplexBlob(YACLib)/64/real_time              9109 ns         9100 ns        76664
ComplexBlob(Folly)/64/real_time              32879 ns        32834 ns        21451
ComplexBlob(BoostThread)/64/real_time        70774 ns        65307 ns         9984
ComplexBlob(YACLib)/128/real_time             9605 ns         9594 ns        72544
ComplexBlob(Folly)/128/real_time             32657 ns        32621 ns        21521
ComplexBlob(BoostThread)/128/real_time       70049 ns        64558 ns        10061
ComplexBlob(YACLib)/256/real_time            12404 ns        12390 ns        56572
ComplexBlob(Folly)/256/real_time             33313 ns        33274 ns        20983
ComplexBlob(BoostThread)/256/real_time       70210 ns        64744 ns        10354
ComplexBlob(YACLib)/512/real_time            13165 ns        13149 ns        53006
ComplexBlob(Folly)/512/real_time             36408 ns        36366 ns        19436
ComplexBlob(BoostThread)/512/real_time       71748 ns        66276 ns         9876
ComplexBlob(YACLib)/1024/real_time           19598 ns        19577 ns        35169
ComplexBlob(Folly)/1024/real_time            40944 ns        40899 ns        17089
ComplexBlob(BoostThread)/1024/real_time      92668 ns        87109 ns         7652
ComplexBlob(YACLib)/2048/real_time           22880 ns        22856 ns        29964
ComplexBlob(Folly)/2048/real_time            45125 ns        45074 ns        15556
ComplexBlob(BoostThread)/2048/real_time      99397 ns        93899 ns         7138
ComplexBlob(YACLib)/4096/real_time           43866 ns        43819 ns        15937
ComplexBlob(Folly)/4096/real_time            66439 ns        66350 ns        10505
ComplexBlob(BoostThread)/4096/real_time     111444 ns       105770 ns         6328
ComplexBlob(YACLib)/8192/real_time          100408 ns       100269 ns         6933
ComplexBlob(Folly)/8192/real_time           120943 ns       120762 ns         5776
ComplexBlob(BoostThread)/8192/real_time     155583 ns       148833 ns         4576
NoContention(YACLib)/real_time              446234 ns       221493 ns         1564
NoContention(Folly)/real_time              2251579 ns       914427 ns          312
NoContention(BoostThread)/real_time        4801297 ns      3076796 ns          150
Contention(YACLib)/real_time                732738 ns       173684 ns          909
Contention(Folly)/real_time                2906086 ns       659158 ns          239
Contention(BoostThread)/real_time          4941652 ns      2094590 ns          144
2022-03-03T14:40:39+02:00
Running ./build_gcc_libstdcxx/future/future
Run on (24 X 4353.95 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 512 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.08, 0.84, 0.68
----------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations
----------------------------------------------------------------------------------
ConstantFuture(Std)/real_time                  153 ns          153 ns      4573470
ConstantFuture(YACLib)/real_time              14.5 ns         14.5 ns     48263026
ConstantFuture(Folly)/real_time               18.9 ns         18.9 ns     36987153
ConstantFuture(BoostThread)/real_time          103 ns          103 ns      6795005
PromiseAndFuture(Std)/real_time                151 ns          151 ns      4659410
PromiseAndFuture(YACLib)/real_time            19.9 ns         19.8 ns     33096214
PromiseAndFuture(Folly)/real_time             72.9 ns         72.8 ns      9536848
PromiseAndFuture(BoostThread)/real_time       96.7 ns         96.6 ns      7216746
Then(YACLib)/0/0/real_time                    48.1 ns         48.0 ns     14494563
Then(YACLib)/1/0/real_time                    95.4 ns         95.3 ns      7259261
Then(YACLib)/2/0/real_time                     143 ns          142 ns      4913824
Then(YACLib)/4/0/real_time                     238 ns          238 ns      2949050
Then(YACLib)/8/0/real_time                     437 ns          437 ns      1600924
Then(YACLib)/16/0/real_time                    814 ns          813 ns       857755
Then(YACLib)/32/0/real_time                   1564 ns         1561 ns       446888
Then(YACLib)/64/0/real_time                   3029 ns         3026 ns       231382
Then(YACLib)/0/1/real_time                    5356 ns         2616 ns       127549
Then(YACLib)/1/1/real_time                    6044 ns         2858 ns       114599
Then(YACLib)/2/1/real_time                    6250 ns         2979 ns       111559
Then(YACLib)/4/1/real_time                    6583 ns         3271 ns       103609
Then(YACLib)/8/1/real_time                    6890 ns         3557 ns        97155
Then(YACLib)/16/1/real_time                   8013 ns         4745 ns        91184
Then(YACLib)/32/1/real_time                   8938 ns         6070 ns        77319
Then(YACLib)/64/1/real_time                  11503 ns         9869 ns        61547
Then(YACLib)/0/2/real_time                    5566 ns         2661 ns       123557
Then(YACLib)/1/2/real_time                    5936 ns         3007 ns       117398
Then(YACLib)/2/2/real_time                    5698 ns         3080 ns       121676
Then(YACLib)/4/2/real_time                    6029 ns         3368 ns       100000
Then(YACLib)/8/2/real_time                    7066 ns         4223 ns        98653
Then(YACLib)/16/2/real_time                   9875 ns         6848 ns        71998
Then(YACLib)/32/2/real_time                  12591 ns         9878 ns        41695
Then(YACLib)/64/2/real_time                  29359 ns        25918 ns        23798
Then(Folly)/0/0/real_time                      156 ns          156 ns      4363444
Then(Folly)/1/0/real_time                      356 ns          356 ns      1961979
Then(Folly)/2/0/real_time                      556 ns          555 ns      1181008
Then(Folly)/4/0/real_time                      968 ns          967 ns       716186
Then(Folly)/8/0/real_time                     1795 ns         1793 ns       388848
Then(Folly)/16/0/real_time                    3459 ns         3456 ns       202269
Then(Folly)/32/0/real_time                    6748 ns         6741 ns       103498
Then(Folly)/64/0/real_time                   13322 ns        13308 ns        52462
Then(Folly)/0/1/real_time                     5781 ns         3181 ns       122218
Then(Folly)/1/1/real_time                     6882 ns         3651 ns       102618
Then(Folly)/2/1/real_time                     7352 ns         3823 ns        96385
Then(Folly)/4/1/real_time                     8167 ns         4343 ns        90811
Then(Folly)/8/1/real_time                     7662 ns         4517 ns        90453
Then(Folly)/16/1/real_time                    9071 ns         5656 ns       114475
Then(Folly)/32/1/real_time                   18756 ns        11788 ns        37738
Then(Folly)/64/1/real_time                   38157 ns        25999 ns        18778
Then(Folly)/0/2/real_time                     5904 ns         3206 ns       118422
Then(Folly)/1/2/real_time                     6965 ns         3627 ns        97159
Then(Folly)/2/2/real_time                     7646 ns         3870 ns       155519
Then(Folly)/4/2/real_time                     8704 ns         4515 ns        80679
Then(Folly)/8/2/real_time                     9976 ns         5413 ns       113480
Then(Folly)/16/2/real_time                   15912 ns         9137 ns        65181
Then(Folly)/32/2/real_time                   26894 ns        16996 ns        38943
Then(Folly)/64/2/real_time                   48777 ns        31944 ns        14981
Then(BoostThread)/0/0/real_time                333 ns          333 ns      2102979
Then(BoostThread)/1/0/real_time                739 ns          738 ns       962027
Then(BoostThread)/2/0/real_time               1108 ns         1107 ns       620911
Then(BoostThread)/4/0/real_time               1859 ns         1857 ns       376796
Then(BoostThread)/8/0/real_time               3384 ns         3380 ns       207638
Then(BoostThread)/16/0/real_time              6392 ns         6385 ns       108837
Then(BoostThread)/32/0/real_time             12381 ns        12366 ns        56401
Then(BoostThread)/64/0/real_time             24480 ns        24454 ns        28625
Then(BoostThread)/0/1/real_time               7167 ns         3683 ns       167609
Then(BoostThread)/1/1/real_time               8284 ns         4768 ns        84245
Then(BoostThread)/2/1/real_time               8445 ns         5093 ns        84918
Then(BoostThread)/4/1/real_time               9908 ns         6209 ns       122521
Then(BoostThread)/8/1/real_time              11256 ns         7903 ns        61475
Then(BoostThread)/16/1/real_time             17526 ns        15004 ns        64874
Then(BoostThread)/32/1/real_time             31184 ns        28723 ns        22099
Then(BoostThread)/64/1/real_time             55184 ns        52186 ns        12647
Then(BoostThread)/0/2/real_time               7395 ns         3828 ns        94156
Then(BoostThread)/1/2/real_time               8966 ns         5077 ns       100000
Then(BoostThread)/2/2/real_time              10085 ns         6068 ns       130043
Then(BoostThread)/4/2/real_time               7854 ns         5353 ns       101908
Then(BoostThread)/8/2/real_time              17735 ns        11294 ns        33899
Then(BoostThread)/16/2/real_time             32767 ns        20578 ns        21280
Then(BoostThread)/32/2/real_time             56248 ns        37213 ns        12395
Then(BoostThread)/64/2/real_time            103842 ns        70621 ns         6713
ComplexBlob(YACLib)/0/real_time              10822 ns        10811 ns        64589
ComplexBlob(Folly)/0/real_time               30960 ns        30929 ns        22691
ComplexBlob(BoostThread)/0/real_time         72361 ns        66871 ns         9719
ComplexBlob(YACLib)/2/real_time              10017 ns        10008 ns        69039
ComplexBlob(Folly)/2/real_time               30963 ns        30933 ns        22595
ComplexBlob(BoostThread)/2/real_time         71799 ns        66294 ns         9703
ComplexBlob(YACLib)/4/real_time              10510 ns        10500 ns        66216
ComplexBlob(Folly)/4/real_time               31732 ns        31702 ns        22044
ComplexBlob(BoostThread)/4/real_time         72333 ns        66655 ns         9661
ComplexBlob(YACLib)/8/real_time              10273 ns        10262 ns        68239
ComplexBlob(Folly)/8/real_time               30262 ns        30233 ns        23146
ComplexBlob(BoostThread)/8/real_time         71631 ns        66005 ns        10014
ComplexBlob(YACLib)/16/real_time             10505 ns        10496 ns        66131
ComplexBlob(Folly)/16/real_time              31410 ns        31380 ns        22322
ComplexBlob(BoostThread)/16/real_time        71096 ns        65421 ns         9867
ComplexBlob(YACLib)/32/real_time             10735 ns        10726 ns        64565
ComplexBlob(Folly)/32/real_time              31116 ns        31086 ns        22519
ComplexBlob(BoostThread)/32/real_time        72784 ns        67184 ns         9536
ComplexBlob(YACLib)/64/real_time             11034 ns        11021 ns        64459
ComplexBlob(Folly)/64/real_time              32091 ns        32049 ns        21890
ComplexBlob(BoostThread)/64/real_time        72536 ns        67067 ns         9957
ComplexBlob(YACLib)/128/real_time            12187 ns        12175 ns        57090
ComplexBlob(Folly)/128/real_time             32632 ns        32586 ns        21424
ComplexBlob(BoostThread)/128/real_time       74722 ns        69317 ns         9637
ComplexBlob(YACLib)/256/real_time            12863 ns        12849 ns        54375
ComplexBlob(Folly)/256/real_time             34423 ns        34384 ns        20424
ComplexBlob(BoostThread)/256/real_time       74054 ns        68643 ns         9595
ComplexBlob(YACLib)/512/real_time            18830 ns        18809 ns        37138
ComplexBlob(Folly)/512/real_time             38843 ns        38797 ns        18080
ComplexBlob(BoostThread)/512/real_time       78611 ns        73152 ns         9146
ComplexBlob(YACLib)/1024/real_time           27492 ns        27428 ns        25230
ComplexBlob(Folly)/1024/real_time            46090 ns        46042 ns        15224
ComplexBlob(BoostThread)/1024/real_time      95006 ns        89439 ns         7009
ComplexBlob(YACLib)/2048/real_time           31094 ns        31064 ns        22536
ComplexBlob(Folly)/2048/real_time            48533 ns        48483 ns        13276
ComplexBlob(BoostThread)/2048/real_time     100972 ns        95500 ns         7016
ComplexBlob(YACLib)/4096/real_time           47595 ns        47543 ns        14712
ComplexBlob(Folly)/4096/real_time            75624 ns        75527 ns         9234
ComplexBlob(BoostThread)/4096/real_time     113530 ns       107810 ns         6163
ComplexBlob(YACLib)/8192/real_time          101728 ns       101526 ns         6785
ComplexBlob(Folly)/8192/real_time           149324 ns       149027 ns         5012
ComplexBlob(BoostThread)/8192/real_time     155057 ns       148635 ns         4574
NoContention(YACLib)/real_time              398952 ns       222091 ns         1760
NoContention(Folly)/real_time              1565136 ns       727341 ns          446
NoContention(BoostThread)/real_time        4563109 ns      2828566 ns          153
Contention(YACLib)/real_time                670465 ns       154046 ns         1015
Contention(Folly)/real_time                2577796 ns       528689 ns          271
Contention(BoostThread)/real_time          4742608 ns      2055291 ns          134
```
