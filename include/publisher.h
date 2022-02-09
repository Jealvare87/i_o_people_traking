#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <mosquitto.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>

/**
 * This module comes from code by a coworker of this thesis. Those methods applies libmosquitto to publish messages.
 * @author Victor T. Carrascal
 * @date 02/06/2021
 * @version v0.0.2
**/

/**
 * Convert integer to char pointer.
 * 
 * @param {num} integer for num entry
 * @param {resul} char pointer for extract the number converted
 * 
 * @return size of this char
 * 
**/
int convertIntToChar(int num, char *resul);

/**
 * Get current date time.
 * 
 * @return current date as a string
 * 
**/
std::string currentDateTime();

/**
 * Warns that this topic wants to disconnect its linkage 
 * 
 * @param {name} char pointer specifies the name of topic that wants to finish publishing
 * 
**/
void finishPublisher(char *name);

/**
 * Starts a conection between, with a created class from mosquitto libs, publisher and broker
 * setting params. 
 * 
 * If an error has ocurred, it will notify by message
 * 
**/
void initPublisher();

/**
 * Publish people whoe have entered and who have left with its topic.
 * 
 * @param {pIN} integer for people in
 * @param {pOut} integer for people out
 * @param {name} name of its topic in this way "<<zone>>/<<branch>>/..."
 * 
**/
void publicar(int pIN, int pOut, char *name);
#endif // PUBLISHER_H