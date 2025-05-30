## __Naudojimosi Instrukcija / Usage Manual__

Programa sukurta linux ir unix sistemoms, todėl jei naudojate Windows, reikės atsisiūsti wsl (Windows subsystem for linux), pagal instrukcijas apačioje.

The program was made specifically for linux/unix systems, so if you use Windows, you might need to download wsl (Windows subsystem for linux) via instructions below.

Lietuviškai:
1. Atsisiūsti repozitoriją arba ją klonuoti.
2. Atidaryti "installer.msi" ir atsisiųsti programą.
3. Nueiti į "C:\Program Files (x86)\VU\Vardenis-Pavardenis" - ten bus programa. (shortcutu dar nesukūriau)
4. Smagaus nuadojimo! :).


English:
1. Download or copy all source files from the repository (for example the .zip file from the 1.0.final realease).
2. Open the "installer.msi" file and install the program.
3. Navigate to "C:\Program Files (x86)\VU\Vardenis-Pavardenis" - the program will be installed there.
4. Happy using!

# __Release notes__

## __V3.0__

This is the final version of my program.  

I added an installer, which downloads the program automatically into the user's computer and prepares the program for use.  
However it still doesn't have any automatic shortcuts or .dll libraries. I will be adding those in an update soon.

In this version, I created my own Vector class with same methods and operators as the standart vector container.  
For comparison, I used unit testing methods to review the performance of __Vector__ vs __vector__.  
The first test was done by checking the push_back method speed of both containers.  
Here are the average results of 5 tests:  
| size        | vector   | Vector   |
| ----------- | -------- | -------- |
| 10,000      | 0.000194 | 0.000054 |
| 100,000     | 0.000612 | 0.00047  |
| 1,000,000   | 0.005074 | 0.00442  |
| 10,000,000  | 0.05567  | 0.05102  |
| 100,000,000 | 0.5109   | 0.395226 |

As you can see, my Vector had a faster time than the standart one with every entry size. WOW! I was honestly very surprised. :)  
This could be because my Vector's push_back compares size_>=capacity_ while the std::vector does it like this: size==capacity.  
But I'm not too sure. I also used resize instead of declaring a new_capacity.

## __V2.0__

This version focuses on testing and documentation.

__Unit Tests__  
I added unit tests to my program, to make testing not only easier, but also more efficient.  
The framework I used to create these tests was __Catch2__, so to compile and run these tests a user would need to download it.  
How to compile and run the tests:  
1. open the terminal
2. type "g++ -g test.cpp -o test_exec" //creates a runnable compiled program for testing
3. type "./test_exec" //execute the created program and test it!

An example of how my Unit testing realisation works:
![Screenshot 2025-05-30 010151](https://github.com/user-attachments/assets/495ffb86-b2ac-448e-86b5-222a46abac76)


__Documentation__  
First of all, I generated a documentation using doxygen. It is simple and doesn't use any templates.  
To generate one yourself, you would need these tools:  
doxygen  
texlive  
graphviz  
cmake  
(all of which I downloaded and used in WSL terminal)

To generate the documentation, you will have to:
1. type "doxygen Doxyfile"  //this loads the config and reads the file
2. cd Documentation/latex   //navigate to where the analyzed data is
3. type "make pdf"  //this will generate a .pdf file inside latex


## __V1.5__

This version introduces a parent class "Zmogus", which holds the student name and surname.  
It is an abstract class, so I created methods in "stud" class to access data inside it.  
The tests run correctly, everything is essentially the same as in the previous version, except that the data is a little safer.

## __V1.2__

This version introduces higher level of class operators (rule of 5 + reading and writing).

For the destructor, I didn't create a specified one, as I thought the default one works well enough.  
Therefore it only has an output line to confirm the destruction.  
![image](https://github.com/user-attachments/assets/ecad8fc3-da74-417d-9f7d-feba10e314a2)


I have designed 4 different operators for overriden methods (perdengti metodai):

1. copy operator = : (with a constructor)  
    Works by accessing an existing object of stud class. It copies it's values without doing anything to the object in itself (more similar to reading it).
   
    Usage example:
   
    "stud a,b; //constructing 2 objects without any primary values  
    cin>>a; //entering student data by hand  
    b=a;" //copying all values from student a to student b. Now the objects have the same values

Constructor:
    ![image](https://github.com/user-attachments/assets/9d799f00-fa30-400e-92cd-fb3fa0d718a9)
   
Operator:  
   ![image](https://github.com/user-attachments/assets/4b324409-7e53-468e-a7a3-f3447c62415d)

   
2. move operator = : (with a separate constructor)  
    Works by accessing an existing object of stud class. It moves it's values to a selected object.
    That means that the primary object loses its data.
    This operator sets simple values, which aren't removed automatically after moving to 0.
   
    Usage example:
   
    "stud a,b; //same as in the previous example  
    cin>>a;  
    b=move(a); //moving the values from stud a to stud b  
    cout<< b; //now b displays the data of stud a  
    cout<< a;" //stud a displays nothing or 0

Constructor:  
 ![image](https://github.com/user-attachments/assets/d540a3bd-58fb-49cf-ac86-77dbafa78f25) 

Operator:  
 ![image](https://github.com/user-attachments/assets/3f52a557-5328-4206-9234-6e7271e1ddc6)
    
3. read operator >> :  
    Works by reading input from files or by hand. However the inputs have to be of certain formulation ("name surname homework1 2 3 <...> exam")  
    It automatically calculates the end result of each object
   
    Usage example:
   
    "stud a;  
    cin>>a;"  
   
    Or:  
    "stud a;  
    ifstream in("filename.txt");  
    in>>a;  
    in.close();"

   ![image](https://github.com/user-attachments/assets/7f3a401e-3656-40bf-a699-fa79a892bd9e)

   
4. write operator << :  
    Works by directly outputting data from the stud class. It has special structure, designed as a standart for all functions.  
    Overall the design is very simple.
   
    Usage example:  
    "stud a;  
    cin>>a;  
    cout<< a;" //outputs student's name, surname, end results
   
    This method also works with files:  
    "stud a;  
    cin>>a;  
    ofstream out("filename.txt");  
    out<< a; //uses the same logic for outputting data into files  
    out.close();"

   ![image](https://github.com/user-attachments/assets/54d6c3a5-e92c-48cc-ae43-f52c234e4bc5)


### All operators, getters, setters and destructors were tested and work properly.
While destructor's work can't be seen in these tests, I did it beforehand and it certainly works.  
The problem is that the destructor is called without a specifiedd call after the function.  
That means that our called destructor works, but the one called by default tries to "destroy" an object, which is already destroyed.  
This ends the program prematurely, therefore it isn't included (is commented) in the testing function.
![image](https://github.com/user-attachments/assets/9bd22a2c-ab47-406a-84c8-44544193294f)

The testing function:  
![image](https://github.com/user-attachments/assets/9ebb8eed-c400-4906-b985-b19c34a313e7)



## __V1.1__

This version totally changed the main data structure. I am slowly moving towards a total OOP approach.

When moving from struct to a class, I needed to check the performance of my program. This time the experiment was done on the performance of the main loop with different compiler flags (O1, O2 and O3). I also included the default compiling method in the table for comparison.

I discovered that bigger file processing lasts for a really long time, however I didn't change it because of the previous version. I wanted to compare how my solution works in the new scenario without making any changes. Perhaps that was my mistake, therefore I will most likely fix this issue in both repositories with the next version (v1.2).

Here are the test results with different optimisation flags:

struct program (v1.0):
| compiler flag            | 1,000,000 | 10,000,000 |
| -------------------- | ---------- | --------- |
| g                    | 183.2385 | 2068.5155 |
| o1                   | 194.009 | 2151.2211 |
| o2                   | 244.7038 | 2131.2762 |
| o3                   | 281.5756 | _1838.5983_ |

class program (v1.1):
| compiler flag           | 1,000,000 | 10,000,000 |
| -------------------- | ---------- | --------- |
| g                   | 211.92563 | 2100.8763 |
| o1                  | _178.18559_ | 2052.4107 |
| o2                  | 191.08189 | 2029.7401 |
| o3                  | 228.712 | 2196.6803 |

With flags O1 and O2, the class oriented project worked faster than the struct realisation, however the struct realisation with O3 flag had the best overall time compared to others.

## __V1.0.final__

In this version I tested different strategies for data splitting.

The first strategy was: Bendro studentai konteinerio (vector, list ir deque tipų) skaidymas (rūšiavimas) į du naujus to paties tipo konteinerius: "vargšiukų" ir "kietiakų". Tokiu būdu tas pats studentas yra dvejuose konteineriuose: bendrame studentai ir viename iš suskaidytų (vargšiukai arba kietiakai). 
This strategy turned out to be the best performance wise. Best for vector or deque containers.

The second strategy was: Bendro studentų konteinerio (vector, list ir deque) skaidymas (rūšiavimas) panaudojant tik vieną naują konteinerį: "vargšiukai". Tokiu būdu, jei studentas yra vargšiukas, jį turime įkelti į naująjį "vargšiukų" konteinerį ir ištrinti iš bendro studentai konteinerio. Po šio žingsnio studentai konteineryje liks vien tik kietiakai.
This strategy took a hard toll on performance, therefore It wasn't even tested with bigger capacity files. Best with list type containers.

The third strategy was: upgrading the best strategy (the first one in my case) to make vector containers work as fast as possible. The method i found to be the fastest, was by using partition. With partition, it outperformed the first strategy, however it was sometimes mixing the order of entries, which was determined before splitting data. To counter this, I used stable_partition method instead. That made the third strategy slower, so I concluded, that the first strategy was the fastest even without any fancy "updates".

Performance test results:

The results will be displayed in different tables for different container types.

__Vector:__
| size       | 1str.    | 2str.    | 3str.    |
| ---------- | -------- | -------- | -------- |
| 1,000      | _0.00043_  | 0.011452 | 0.008038 |
| 10,000     | _0.00185_  | 0.961286 | 0.002136 |
| 100,000    | 0.020136 | 96.87775 | _0.017612_ |
| 1,000,000  | _0.170872_ | \-       | 0.18118  |
| 10,000,000 | _1.848834_ | \-       | 2.13107  |

__Deque:__
| size       | 1str.    | 2str.    | 3str.    |
| ---------- | -------- | -------- | -------- |
| 1,000      | _0.000246_ | 0.00392  | 0.000342 |
| 10,000     | _0.001418_ | 0.41902  | 0.002016 |
| 100,000    | _0.011860_  | 39.32599 | 0.018832 |
| 1,000,000  | _0.169566_ | \-       | 0.22355  |
| 10,000,000 | _1.794734_ | \-       | 2.53863  |

__List:__
| size       | 1str.    | 2str.    | 3str.    |
| ---------- | -------- | -------- | -------- |
| 1,000      | 0.000136 | _0.000102_ | 0.000258 |
| 10,000     | 0.001146 | _0.000778_ | 0.002296 |
| 100,000    | 0.009326 | _0.007676_ | 0.024492 |
| 1,000,000  | \-       | \-       | \-       |
| 10,000,000 | \-       | \-       | \-       |

## __V1.0.pradinis__

Performance tests:

Laptop specs used to perform the tests:
| Part       | specifics   |
| ---------- | -------- |
| CPU       | 13th Gen Intel(R) Core(TM) i7-13700H   2.40 GHz    |
| RAM       | DDR5 32GB  |
| SSD       | 1TB  |
| OS        | Windows 11 Home  |

Tests were performed in WSL, with gnu gcc compiler.

The presented tables are an average representation of 5 tests.

In this code, I tested how different container types work with 3 different categories of the program: reading from a file, sorting the entries, splitting entried data based on 1 criteria.

Numbers in italics represent the best average values from each testing category.

Overall average performance:
| size       | vector   | deque    | list     |
| ---------- | -------- | -------- | -------- |
| 1,000      | 0.03076  | *0.012428* | 0.016372 |
| 10,000     | 0.117736 | *0.115878* | 0.424666 |
| 100,000    | 1.144202 | *1.261344* | 27.46817 |
| 1,000,000  | 12.31542 | *10.98947* |          |
| 10,000,000 | 107.6915 | *102.1495* |          |

Performance of file reading:
| size       | vector   | deque    | list     |
| ---------- | -------- | -------- | -------- |
| 1,000      | 0.030188 | *0.011774* | 0.01608  |
| 10,000     | 0.1112   | *0.10869*  | 0.421896 |
| 100,000    | *1.058244* | 1.165262 | 27.41412 |
| 1,000,000  | 11.22911 | *9.769698* |          |
| 10,000,000 | 94.44985 | *86.97129* |          |

Performance of entry sorting:
| size       | vector   | deque    | list     |
| ---------- | -------- | -------- | -------- |
| 1,000      | 0.00042  | 0.000528 | *0.00017*  |
| 10,000     | 0.00485  | 0.00573  | *0.001794* |
| 100,000    | 0.064236 | 0.078698 | *0.036834* |
| 1,000,000  | *0.821712* | 0.974098 |          |
| 10,000,000 | *10.39225* | 12.32084 |          |

Performance of data splitting:
| size       | vector   | deque    | list     |
| ---------- | -------- | -------- | -------- |
| 1,000      | 0.000152 | 0.000126 | *0.000122* |
| 10,000     | 0.001686 | 0.001458 | *0.000976* |
| 100,000    | 0.021722 | 0.017384 | *0.017214* |
| 1,000,000  | 0.264606 | *0.245676* |          |
| 10,000,000 | *2.84937*  | 2.857383 |          |




## __V0.4__

Performance tests:

Time was calculated as an average measurement from 5 tests.

Size is in student entries (generated lines).
Each test generated 15 marks for each student.

Performance of file generation: 
|    size    |  time, s  |
|:-----------|:----------|
| 1,000      | 0.14999   |
| 10,000     | 0.78290   |
| 100,000    | 9.27199   |
| 1,000,000  | 87.97203  |
| 10,000,000 | 913.54749 |

Performance of file reading, splitting and generating the output:
|    size    |  time, s   |
|:-----------|:-----------|
| 1,000      | 0.38349    |
| 10,000     | 1.19842    |
| 100,000    | 12.44007   |
| 1,000,000  | 148.85819  |
| 10,000,000 | 1135.89981 |

Example of testing 100,000 entry file reading, splitting and outputting performance:
![image](https://github.com/user-attachments/assets/40a07b1b-ba23-4f44-9dc3-b79ecd0d13d8)
