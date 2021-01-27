#ifndef _BOT_H
#define _BOT_H

void szukaj_sciany(char* argv, char buffer[2048]);

dynamiczna *info_bot(char *test, char buffer[2048]);

void start_bot(char* test, char buffer[2048]);

dynamiczna *krecenie(char* test, char buffer[2048], int x, int y);

dynamiczna *krecenie2(char* test, char buffer[2048]);

void move_bot(char* test, char buffer[2048]);

dynamiczna *explore_bot(char* test, char buffer[2048]);

#endif

