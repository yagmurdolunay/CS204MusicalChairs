# CS204MusicalChairs
multithreaded C++ program that simulates the universal  game called musical chairs
# Table of Contents
* Introduction
* Features
* Program Overview
* Details of the Program
# Introduction
This project aims to create a multithreaded C++ program that simulates the classic game of musical chairs using a queue data structure. The game starts by taking the number of players as input and then simulates each round of the game via several threads, one for each player. It will print relevant information about the game's progress and outcomes.

In the game of musical chairs, players move around a circle of chairs while music plays. When the music stops, the players must quickly find a chair to sit in. One chair is removed in each round, and the game continues until only one player is left standing.

This simulation program is designed to provide a fun and educational way to understand multithreading concepts in C++ while playing a popular party game.

# Features
The header and the cpp files of the "IntQueueHW6 class" are provided.

# Program Overview
The game starts by taking the number of players as input.
Each player is assigned a unique ID starting from 0.
The number of chairs is one less than the number of players.
Each round begins with displaying the current time.
Players start hunting for a chair 2 seconds after the current time to ensure fairness.
Threads (one for each player) are synchronized using std::this_thread::sleep_until to start at the same time.
Players try to enqueue their ID to a common queue to capture a chair.
A mutex is used to synchronize access to the queue to avoid conflicts.
After each round, the threads are joined properly.
The IDs of players who captured a chair in the capturing order are displayed.
One player is eliminated each round, and the number of chairs decreases by one.
The game continues until only one player remains as the winner.

# Details of the Program
The program uses the iomanip, thread, chrono, ctime, and mutex libraries.
The program includes a void function to randomize the threads, and to enqueue the random gotten ID to the related queue.
It begins by declaring an integer variable numPlayers to store the number of players in the game.

The program prompts the user to enter the number of players and stores it in the numPlayers variable.

Two mutexes, remainingMutex and outsiderMutex, are declared. These mutexes will be used to synchronize access to shared resources.

The game starts with a welcoming message and initializes some variables:

remainingPlayers: Initially set to numPlayers, used to control the main game loop.
winner: Initialized to -1, which will hold the ID of the winning player.
playersArray: A dynamically allocated array of integers to keep track of the players' statuses.
The program retrieves the current time and stores it in the tt variable, which is then converted to a readable time format and stored in ptm.

The main game loop runs while remainingPlayers is greater than 1, which means there is more than one player left in the game.

Inside the loop, three queues are initialized:

remainingPlayersQueue: A queue to hold the players who are still in the game.
remainingPlayersQueue2: Another queue to help manage the remaining players after each round.
outsiderPlayersQueue: A queue to hold the player who couldn't capture a chair in the current round.
The program displays the current time.

An array of player threads, playerThreads, is dynamically allocated to match the number of players. threadCount keeps track of how many threads have been created.

A loop iterates through all players to create and start threads. It checks if the player is still in the game (not eliminated). For each active player, a thread is created and passed various parameters, including player ID, time information, queues, and mutexes.

After all player threads have been created, there's a loop to join (wait for) all the threads to complete their tasks.

The playerThreads array is then deleted to free up memory.

The program increments the time by 2 seconds to simulate a delay.

The next loop dequeues players from remainingPlayersQueue and checks if they are still in the game. It adds players to remainingPlayersQueue2 and records the winner if they are the last player.

Another loop dequeues players from outsiderPlayersQueue and marks them as -1 in the playersArray to indicate they are no longer in the game.

The program prints the remaining players in remainingPlayersQueue2, updates remainingPlayers, and continues to the next round.

The main game loop repeats until there is only one player left.

Finally, the playersArray is deleted, and the program prints the winner of the game.




