# CS201-Project
LRU Cache Implementation

By:
    Group No.: 10

Vijay Dwivedi     -   2020csb1140@iitrpr.ac.in
Vinay Kumar       -   2020csb1141@iitrpr.ac.in
Yadwinder Singh   -   2020csb1143@iitrpr.ac.in

Mentor:
Ravi Bhatt        -   2020aim1008@iitrpr.ac.in

Files:
1) LruCache.c 
2) random_url_generator.cpp
3) input.txt
4) output.txt
5) Report__pdf_Group_10.pdf

How to Input:
Program reads input from "input.txt"
  1) 1st line of "input.txt" is length of LRU cache (int).
  2) From 2nd line to second last line contains URLs (strings).
  3) Last line has to be "-1" indicating input has been completed.
User can create "input.txt" by thier own using above steps
              OR
We have created a cpp program for random URL generator. For this, user have to input length of cache and "input.txt" will be created.

How to run:
1) LruCache.c 
      User can run it directly or run it in terminal.
2) random_url_generator.cpp
      User can directly run or run it in terminal.

Output:
For every URL program reads from "input.txt" , it gives you the URLs in cache from least recently used at the top and
most recently used at the bottom.
At the end, it prints LRU (least recently used) URL as well as MRU (most recently used) URL.

Program gives a "output.txt" file in which all the results are present.

Debugging:
The program in output file gives you the elements of cache at every step, hence it show the whole process how the cache changes everytime you add a new string. It gives you an idea whether the program runs correctly or not.



      
