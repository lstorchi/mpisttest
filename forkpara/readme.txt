Parallel using a simple fork

[redo@banquo 11_summa]$ time ./summa  100000000
result = 5000000050000000.000000

real    0m0.292s
user    0m0.285s
sys     0m0.000s
[redo@banquo 11_summa]$ time ./forking  100000000
result = 5000000050000000.000000

real    0m0.182s
user    0m0.349s
sys     0m0.001s

