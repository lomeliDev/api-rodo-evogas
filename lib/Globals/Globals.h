#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

/*DEBUG*/
extern bool debug;
extern void log(String data);
extern void logf(String data);

/*API*/
extern char *ssidAP;
extern char *pwdAP;
extern int timeout;
extern bool isAP;

/*WIFI*/
extern char *ssid;
extern char *pwd;

#endif