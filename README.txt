0.compile
g++ main.cpp   MadgwickAHRS.c -o main

1.run
  0)calculate quaternion:
	./main  input.txt  output.txt 
  0)calculate euler angle:
	./main  input.txt  output.txt  euler
