# Benchmark YACLib

If you have this warning:

```
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
```

Before run:

```bash
sudo cpupower frequency-set --governor performance
```

After run:

```bash
sudo cpupower frequency-set --governor powersave
```
