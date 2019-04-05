var = 1000

all:
	gcc -o train train.c
	gcc -o test test.c
	gcc -o acc acc.c

run: run_train run_test run_acc

run_train:
	./train $(var) model_init.txt seq_model_01.txt model_01.txt
	./train $(var) model_init.txt seq_model_02.txt model_02.txt
	./train $(var) model_init.txt seq_model_03.txt model_03.txt
	./train $(var) model_init.txt seq_model_04.txt model_04.txt
	./train $(var) model_init.txt seq_model_05.txt model_05.txt

run_train_continue:
	./train $(var) model_01.txt seq_model_01.txt model_01.txt
	./train $(var) model_02.txt seq_model_02.txt model_02.txt
	./train $(var) model_03.txt seq_model_03.txt model_03.txt
	./train $(var) model_04.txt seq_model_04.txt model_04.txt
	./train $(var) model_05.txt seq_model_05.txt model_05.txt

run_test:
	./test modellist.txt testing_data1.txt result1.txt
	./test modellist.txt testing_data2.txt result2.txt

run_acc:
	./acc

clean:
	rm ./train
	rm ./test
	rm ./acc
