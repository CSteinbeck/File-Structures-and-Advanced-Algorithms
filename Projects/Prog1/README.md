The Binary Book Database: Part III Analysis and Design Discussion
Colton Steinbeck

Overview:
The purpose of this project is to gain experience inputting and outputting records from/to a binary file using indexed file organization. The goal of this project is to show the optimizations made when reading/writing files in binary vs. reading them in as traditional text. With Part III, the database portion is to process mutiples BookRec Structs (basic book information) from a master file alongside reading and processing new book files (transactions) and writing the changes to a new master file. 

There were strict parameters of what could modified to the new master file:
1) Adding
    -If the ISBN does not already exist, add a new record to the new master, containing all of the other information in the transaction, in the appropriate position. An add transaction may occur before other transactions for the same ISBN. This is legal and the changes/deletes should occur on the new record, before it goes into the new master file.


2) Deleting
    -If the ISBN exists, the record should not be added to the new master file. If the ISBN does not exist, print the appropiate error messages

3) Changing On Hand Amount
    -If the ISBN exists, change the Onhand field by adding the Onhand field of the transaction record to it. If this creates a negative count or non-existent ISBN, print the corresponding error messages.

4) Price Changing
    -If the ISBN exists, change the price accordingly. If non-existent, print corresponding error message.


Corresponding Files for update.cpp
    -library.out- This was the original master file used in Part II and serves as the "starting file" for Part III
    -transact.out- This file is where any changes to the original file are held. This includes adding books, deleting books, changing price and onhand for said books.
    -newMas.out - This is the new master file, holding all the changes done by the transact.out file done to the library.out file
    -copy.out - copy of the master file  to hold all changes done to library and master before writing it to the new master (newMas) file
    -ERROR-File to show all errors without outputing them directly to the console

    Algorithm Design:

    When designing this project, I wanted to accurately link ISBN to their corresponding byte offset. This allows me to accurately place their location on file and read/write more efficently. With that in mind, I implemented a map to achieve this and add or delete new elements based on the transaction file being processed in at that time. Through using fstreams, I was able to quickly open and read the copy.out file. While reading the files, the program would call methods to check for all potential changes and would add to the map if accepted. 
    When the file was finished, it would output the contents of the map to the new master file, showing any changes made.