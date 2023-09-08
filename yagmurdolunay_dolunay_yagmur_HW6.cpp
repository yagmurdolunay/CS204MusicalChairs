#include <iostream>
#include <iomanip> //for put_time
#include <thread>
#include <chrono> // for system_clock
#include <ctime>
#include "IntQueueHW6.h"
#include <mutex>
using namespace std;
/*taken and implemented from threads8.cpp: starts*/
void count1m(int id, struct tm* ptm, int* playersArray, IntQueueHW6& remainingPlayersQueue,
        IntQueueHW6& outsiderPlayersQueue, mutex& remainingMutex, mutex& outsiderMutex) {
    this_thread::sleep_until(chrono::system_clock::from_time_t(time(nullptr)));
    for (int i=0; i < 1000000; ++i)
    {} // to randomize the threads

    if (playersArray[id] != -1) { // if the player is still in the game
        if (remainingPlayersQueue.isFull()) { // if the  # of remaining players have reached the max size
            outsiderMutex.lock();
            outsiderPlayersQueue.enqueue(id); // enqueue the player to the outsiderplayersqueue that couldn't capture the chair
            outsiderMutex.unlock();
        } else {
            remainingMutex.lock();
            remainingPlayersQueue.enqueue(id); // enqueue the players to the remainingqueue
            remainingMutex.unlock();
        }
    }
}
/*taken and implemented from threads8.cpp: ends */

int main() {
    int numPlayers;

    cout << "Welcome to Musical Chairs game!" << endl;
    cout << "Enter the number of players in the game: " << endl;
    cin >> numPlayers;

    mutex remainingMutex;
    mutex outsiderMutex;

    cout << "Game Start!" << endl;
    int remainingPlayers = numPlayers; // formed to control the while loop
    int winner = -1; //initialized
    int* playersArray = new int[numPlayers]; //to keep track of the players
    for (int i = 0; i < numPlayers; i++) {
        playersArray[i] = i;
    }
    /*taken from threads8.cpp : starts */
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm* ptm = localtime(&tt);
    /*taken from threads8.cpp : ends */

    while (remainingPlayers > 1) { // while there exists only one player
        /*initalized the queue's */
        IntQueueHW6 remainingPlayersQueue(remainingPlayers - 1); //size is -1 bc. one player will  be out of the game at each round, and remainings will be numplayers-1
        IntQueueHW6 remainingPlayersQueue2(remainingPlayers - 1);//size is -1 bc. one player will  be out of the game at each round, and remainings will be numplayers-1
        IntQueueHW6 outsiderPlayersQueue(1); // at each round just one of them wouldn't capture a chair
        cout << endl;
        cout << "Time is now " << put_time(ptm, "%X") << endl;

        thread* playerThreads = new thread[remainingPlayers]; // create threads as remainingplayers
        int threadCount = 0;  // Number of threads created

        for (int i = 0; i < numPlayers; i++) { //start the threads
            if (playersArray[i] != -1) { //check if the player is still in the game
                playerThreads[threadCount] = thread(count1m, i, ptm, playersArray, ref(remainingPlayersQueue),
                                                    ref(outsiderPlayersQueue), ref(remainingMutex), ref(outsiderMutex));
                threadCount++;
            }
        }

        for (int i = 0; i < threadCount; i++) {
            playerThreads[i].join(); //end the threads
        }
        delete[] playerThreads; // delete the threads

        ptm->tm_sec += 2; /* to delay the time for 2 seconds*/
        mktime(ptm);

        while (!remainingPlayersQueue.isEmpty()) {
            int player;
            remainingPlayersQueue.dequeue(player); //make sure which player is this

            if (playersArray[player] != -1) { // to check if the player is still in the game
                if (remainingPlayersQueue.isEmpty()) {
                    remainingPlayersQueue2.enqueue(player); // add the player to the remainingplayersqueue2
                    winner = player; //if it is the last player in the remainingsqueue, in the last round, it will be winner

                } else {
                    remainingPlayersQueue2.enqueue(player);
                }

                cout << "Player " << player << " captured a chair at " << put_time(ptm, "%X") << endl;
            }
        }

        while (!outsiderPlayersQueue.isEmpty()) {
            int player;
            outsiderPlayersQueue.dequeue(player);
            playersArray[player] = -1;//make sure it is -1, that is not in the game anymore
            cout << "Player " << player << " couldn't capture a chair." << endl;
        }

        cout << "Remaining players are as follows: ";
        while (!remainingPlayersQueue2.isEmpty()) {
            int player;
            remainingPlayersQueue2.dequeue(player);
            remainingPlayersQueue.enqueue(player);
            cout << player << " ";
        }
        cout << endl;

        remainingPlayers--; //decrement the # of remainingPlayers
    }

    delete[] playersArray; //delete the array

    cout << endl;
    cout << "Game over!" << endl;
    cout << "Winner is Player " << winner << "!" << endl;
    return 0;
}
