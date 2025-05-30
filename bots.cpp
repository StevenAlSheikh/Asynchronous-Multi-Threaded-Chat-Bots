// Course: CS 480
// Professor Guy Leonard
// Year: 2024
// Programming Assignment #1
// Group members:
// Name: Steven Al-Sheikh
// RedID: 826493311
//  Edoras account: cssc4457
// Name: Moe Jawadi
// RedID: 130102437
// Edoras account: cssc4444

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include "bots.h"
#include <string>
using namespace std;
// We have created a stream object that is going to be used to store the name of our file.
ofstream fileQuote;
// Here we have created a semaphore and we will call it FLAG.
sem_t FLAG;

// We have created this function to get the quote that will be printed
// When the number of the thread is an even number, it shall return one quote. If it is not, then it will return a different one.

string getQuote(int thread_id){
    string quoteofBot;
    // this if else statement will check for an even thread.
    if(thread_id %2 == 0){
        quoteofBot = "Controlling complexity is the essence of computer programming.--Brian Kernigan\n";
        //The Quote (followed by a Carriage Return and Newline) 
    }
    else{
        quoteofBot = "Controlling complexity is the essence of computer programming.--Brian Kernigan\n";
    }
    return quoteofBot;

}
// The gettheInterval function will receive a thread_id, this will check if it is even or odd.
// if the id is even then it will return a 2, if it is odd then it will return a 3.
int getTheInterval(int thread_id){
    // if the thread is even then it will reutn a 2
    if (thread_id % 2 == 0) {
        return 2;  
    }

    // if it is not even then it is odd, which will return a 3.
    else {
        return 3;  
    }
}
// In this function, we will be execuring the threads. This function will call gettheInterval(int thread_id).
    void* executeThreads(void* args){
     int thread_id = *((int*)args);

    //declare an int variable and use that to call the getInterval() function
    int thread_interval = getTheInterval(thread_id);

    for (int count = 0; count < 8; count++) {
        sem_wait(&FLAG); //point 6. Block/wait for all seven threads to complete their work.

        //get the quote
        string quote = getQuote(thread_id);
        ////Open the file QUOTE.txt 
        fileQuote.open("QUOTE.txt", std::ios::app);
        // we will be writting the thread id followed by thr quote 
        // then the carriage return is added to the quote 
       fileQuote << "Thread " << thread_id << quote;

        // this will close the file
        fileQuote.close();

        // we will use this to write to the console to print the thread followed by thread id, is running followed by a newline.
        cout << "Thread " << thread_id << ": " << quote;

        // this sem will release the FLAG
        sem_post(&FLAG);
 
        sleep(thread_interval);
    }
    pthread_exit(NULL); // we will use this to exit the thread
}

// The createTheQuoteFile will write the pid to the file
// Here are the steps that were given on canvas:
//When your program starts, it shall do the following:
//Create a file, named QUOTE.txt, in the current directory (cwd).
//Have your running process write it’s pid (Process ID) followed by a Carriage Return and Newline into the file.
////Close the file QUOTE.txt
void createTheQuoteFile() {

    //create the file
    std::ofstream quoteFile("QUOTE.txt");
    if (quoteFile.is_open()) {
        //write the pid and new line 
        quoteFile << getpid() << "\n";
        //then close the file
        quoteFile.close();
    }

    else {
        std::cerr << "Sorry failed to create the file" << endl;
    }
}

int main() {
    // create quote file and other steps
    createTheQuoteFile();

    // Initialize flag
    sem_init(&FLAG, 0, 1);

    // create array of 7 threads
    pthread_t threads[7];
    int array_thread_id[7]; // array to hold the thread ID's for each thread

    // for loop to create the threads
    for (int i = 0; i < 7; i++)
    {
        array_thread_id[i] = i + 1;
        //create the thread and pass the worker function
        int threadCreate = pthread_create(&threads[i], NULL, executeThreads, &array_thread_id[i]);
        //if failed to create, print an error
        if (threadCreate != 0) {
            std::cerr << "Failed to create" << endl;
            return 1;
        }
    }


    // Wait for all threads to complete
    //Once all threads are done, destroy the semaphore,
    for (int i = 0; i < 7; i++) {

        if (pthread_join(threads[i], NULL) != 0)
        {
            std::cerr << "Failed to create" << endl;
            return 1;
        }
    }

    // destroying semaphore here
    sem_destroy(&FLAG);

    // then exit gracefully, printing a friendly message to the console
    cout << "Yay! All the threads are working!" << endl;

    return 0;
}