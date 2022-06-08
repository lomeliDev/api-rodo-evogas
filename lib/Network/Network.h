#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include "Globals.h"

void setupWIFI();
void setupAP();
void stopWIFI();
void create_json(char *type, bool status, char *message);
void setupRouting();
void getAction();

#endif