# Benchmark YACLib

## Results

Future benchmark [results](future/result/RESULTS.md).

## How to add your own results

**The most important** benchmarks now only work on Linux

Need to install:
```
cmake
ninja
gcc
g++
clang
```

And if you want enable Folly or BoostThread or libc++:
```
folly
boost_thread
libc++
```

If you install all these dependencies, you can run:
```bash
./script/build.sh
./script/run.sh --proc="Your proc name without space"
```

At this point, new benchmark results will be in `:/future/result/<Your proc name without space>`

Then commit and make PR, thanks!

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

