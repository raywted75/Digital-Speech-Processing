# Discrete Hidden Markov Model

## Environment

System: Ubuntu 16.04.6 LTS <br>
Compiler: gcc 5.4.0 <br>

## How to Execute

0.  (Optional) You can change the value of the variable “var” in Makefile to customize the iterations you want(default value is 1000).

1. First, you need to compile the three C programs(train.c, test.c, and acc.c). 
- Compile
```
$ make
```
2. Second, you can choose to run all the three programs or part of them.
- Run All(including train, test, and acc)
    > make run
- Run Train
    > make run_train 
- Run Test
    > make run_test
- Run Acc
    > make run_acc
3. Finally, you may want to clean the programs.
- Clean
    > make clean

## Experiment
1. I tried different iterations and find that when the iteration increases, the accuracy will decrease at the first; then, it will keep increasing and finally fluctuate around 0.87.
 iteration | accuracy 
 --------- | -------- 
 1         | 0.766000 
 10        | 0.540800 
 100       | 0.810000 
 500       | 0.856000 
 1000      | 0.869600 
 1200      | 0.868400 
 1500      | 0.870000 
 1800      | 0.869600 

2. Out of curiosity, I tried different initial probability(set iteration = 100) and find that the different initial probability does impact the accuracy given the same iteration. However, because this experiment is very rough, we do not know whether they will converge to the different accuracy and which one will have the best performance.
| initial probability                                        | accuracy |
| ---------------------------------------------------------- | -------- |
| 0.2        0.1        0.2        0.2        0.2        0.1 | 0.810000 |
| 0.2        0.2        0.2        0.1        0.1        0.2 | 0.864400 |
| 0.5        0.1        0.1        0.1        0.1        0.1 | 0.857600 |
