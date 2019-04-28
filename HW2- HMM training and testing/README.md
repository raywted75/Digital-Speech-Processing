# HMM Training and Testing

## Description
[Slide Link](https://drive.google.com/open?id=1laxJTNvlab2XJ1s10M9q9uxa4hjItW0O)

## How to Execute

0.  Download [HTK](https://drive.google.com/open?id=1SoaoG9jvkSLdc_f_K1PrqEcXLoTHxDfG), [Speech Data](https://drive.google.com/open?id=1Kc1hUXYR_TZ3G--_OwdFwqnBngkDcplI) and put them into the folder. <br>

0.  (Optional) If any parameter or file is changed, please remove all the previos files.
```
$ ./00_clean_all.sh
```

1.  Feature Extraction
```
$ ./01_run_HCopy.sh
```

2.  Model Initialization
```
$ ./02_run_HCompV.sh
```

3.  Training
```
$ ./03_training.sh
```

4.  Testing
```
$ ./04_testing.sh
```

## Experiment

1.  Number of states

| State | Accuracy |
| ----- | -------- |
| 5     | 74.34%   |
| 6     | 81.47%   |
| 7     | 87.80%   |
| 8     | 89.64%   |
| 9     | 90.91%   |
| 10    | 93.67%   |
| 11    | 94.25%   |
| 12    | 95.22%   |
| 13    | 95.57%   |
| 14    | 95.80%   |
| 15    | 95.91%   |

2.  Number of Gaussian mixtures

| Gaussian | Accuracy |
| -------- | -------- |
| 2        | 74.34%   |
| 3        | 74.05%   |
| 4        | 74.45%   |
| 5        | 76.52%   |
| 6        | 78.42%   |
| 7        | 78.37%   |
| 8        | 78.02%   |
| +2       | 74.86%   |
| +3       | 75.20%   |
| +4       | 76.24%   |
| +5       | 79.86%   |
| +6       | 79.86%   |
| +7       | 79.34%   |

3.  Number of iterations

| HERest Iteration | Accuracu |
| ---------------- | -------- |
| 3, 3, 6          | 74.34%   |
| 6, 6, 12         | 77.62%   |
| 12, 12, 24       | 75.89%   |

4.  Adjustment base on the results above

| State | Gaussian | Iteration   | Accuracy |
| ----- | -------- | ----------- | -------- |
| 5     | 2        | 3, 3, 6     | 74.34%   |
| 10    | 6        | 6, 6, 12    | 96.20%   |
| 10    | +6       | 6, 6, 12    | 95.80%   |
| 10    | 7        | 6, 6, 12    | 95.68%   |
| 11    | 6        | 6, 6, 12    | 96.49%   |
| 12    | 6        | 6, 6, 12    | 96.32%   |
| 12    | 6        | 9, 9, 18    | 96.72%   |
| 12    | 6        | 12, 12, 24  | 96.84%   |
| 12    | 6        | 24, 24, 36  | 96.95%   |
| 12    | 6        | 48, 48, 72  | 97.30%   |
| 12    | 6        | 96, 96, 144 | 97.47%   |
| 15    | 6        | 12, 12, 24  | 96.89%   |
| 15    | 6        | 96, 96, 144 | 96.95%   |
| 15    | 10       | 9, 9, 12    | 97.64%   |
| 15    | 20       | 9, 9, 12    | 97.81%   |
| 15    | 40       | 9, 9, 12    | 97.93%   |
| 17    | 40       | 9, 9, 12    | 97.41%   |
| 15    | 60       | 12, 12, 15  | 98.33%   |

5. Best result

| State | Gaussian (liN - jiou) (2 - 14) | Gaussian (sil) (2 - 4) | Iteration  | Accuracy |
| ----- | ------------------------------ | ---------------------- | ---------- | -------- |
| 15    | 60                             | 3                      | 12, 12, 15 | 98.33%   |

## Conclusion

The most influential factors to the model are the number of states, Gaussian mixtures, and iterations. Therefore, I changed one variable at a time to get the best value separately. Based on the best results separately,  I combined them and kept adjusting. The best result I got is 97.47%. <br>

In the process of experiment, I found that: <br>
1.  Increasing the number of states can improve the performance because the model can be described more precisely.
2.  Increasing the number of Gaussian mixtures can improve the performance because each state is a continuous probability distribution and thus the more number of Gaussian, the more similar they can form the probability distribution.
3.  With the number of states and Gaussian mixtures increasing, we need more iteration to train the model well. However, the number of states and the number of Gaussian mixtures are still the main factors to the performance.
