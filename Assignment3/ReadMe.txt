There are two files: withMutualExclusion.c and withoutMutualExclusion.c in this folder containing answer code.

Follow following steps to get the output:
1- download those files in folder and save them in a directry

2- open terminal to exicution, change the directry to the one in which you have saved the code files with command-
 'cd [directery name]' 
(I have used college linux id terminal to run this code)

3- comple the code with command- 
'gcc -lpthread withoutMutualExclusion.c -lm' 

4- for output use command- ' ./a.out'

 This code without mutual exclusion give wrong output.

5- comple the code with command- 
'gcc -lpthread withMutualExclusion.c -lm' 

6- for output use command- ' ./a.out'

 This code with mutual exclusion gives the desired output. 
