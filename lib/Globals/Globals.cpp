#include <Arduino.h>
#include "Globals.h"

/*DEBUG*/
bool debug = true;

/*API*/
char *ssidAP = "Evogas";
char *pwdAP = "holacomoestas";
int timeout = 15000;
bool isAP = true;

/*WIFI*/
char *ssid = "Dayis";
char *pwd = "holacomoestas";

void log(String data)
{
    Serial.println(data);
}

void logf(String data)
{
    Serial.print(data);
}