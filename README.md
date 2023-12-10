# p1

## Description
This is a C-program which is capable of selecting and ranking airplane and train routes in Germany.
The program is a representation of how a real world application could work which is why it retrieves its data from at fixed dataset.

## How to run program

Assuming you have already downloaded the program folder and navigated to it in your terminal run the following command. 

`make clean && make`

Then

`./main`

If you want to skip a step run:

`make clean && make && ./main`

And if you want to test the program with predefined input run:

`make clean && make && ./main < temp.txt`

## How to access you content in all files
To access you function in main, or any other file, you need to add it to the `functions.h` file.
You can watch the file for an example. 

## Additional
You can add more data to the `.csv` files if you want, just add it in the same format as the other lines.