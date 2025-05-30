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

#pragma once
#ifndef BOTS_H_
#define BOTS_H_
#include <string>
using namespace std;

//function definition from Bots.cpp
string getQuote(int thread_id);
int getTheInterval(int thread_id);
void* executeThreads(void* args);
void createTheQuoteFile();

#endif