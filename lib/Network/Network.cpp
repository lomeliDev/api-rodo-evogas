#include <Arduino.h>
#include <FS.h>
#include "SPIFFS.h"
#include "Esp.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "Globals.h"
#include "Network.h"

WebServer server(80);

StaticJsonDocument<2048> jsonDocument;
char buffer[2048];

void setupWIFI()
{

    log("Setting WIFI…");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);

    delay(1000);

    log("");
    log("[Wifi]: Connecting");
    log("");

    int countWifi = 0;
    WiFi.begin(ssid, pwd);

    while (WiFi.status() != WL_CONNECTED)
    {
        if (countWifi >= 50)
        {
            log("");
            log("");
            log("wifi no connected Reset ESP32");
            log("");
            log("");
            ESP.restart();
            delay(3000);
        }
        logf(".");
        delay(100);
        delay(100);
        countWifi++;
    }
    log("");
    log("wifi ok");

    log("");
    log("WiFi connected");
    log("");
    logf("IP address: ");
    log(String(WiFi.localIP().toString().c_str()));
    log("");
    logf("Gateway: ");
    log(String(WiFi.gatewayIP().toString().c_str()));
    log("");
    logf("Mask: ");
    log(String(WiFi.subnetMask().toString().c_str()));
    log("");
    logf("DNS: ");
    log(String(WiFi.dnsIP().toString().c_str()));
    log("");

    setupRouting();
}

void setupAP()
{

    log("Setting AP (Access Point)…");

    WiFi.softAP(ssidAP, pwdAP);

    delay(1000);

    IPAddress IP = WiFi.softAPIP();
    logf("AP IP address: ");
    log(String(IP));

    log("");
    log("WiFi connected");
    log("");
    logf("IP address: ");
    log(String(WiFi.localIP().toString().c_str()));
    log("");
    logf("Gateway: ");
    log(String(WiFi.gatewayIP().toString().c_str()));
    log("");
    logf("Mask: ");
    log(String(WiFi.subnetMask().toString().c_str()));
    log("");
    logf("DNS: ");
    log(String(WiFi.dnsIP().toString().c_str()));
    log("");

    setupRouting();
}

void stopWIFI()
{
    WiFi.disconnect();
    WiFi.disconnect(true);
    WiFi.disconnect();
}

void create_json(char *type, bool status, char *message)
{
    jsonDocument.clear();
    jsonDocument["type"] = type;
    jsonDocument["status"] = status;
    jsonDocument["message"] = message;
    serializeJson(jsonDocument, buffer);
}

void setupRouting()
{
    server.on("/data", HTTP_POST, getAction);

    server.begin();
}

void getAction()
{
    log("getAction");

    int codeResponse = 200;

    if (server.hasArg("data") == false)
    {
        log("no data");
        server.send(500, "application/json", "{}");
    }

    String response = server.arg("data");

    jsonDocument.clear();
    DeserializationError error = deserializeJson(jsonDocument, response);

    if (error)
    {
        log("error en data");
        server.send(500, "application/json", "{}");
    }

    String typeData = jsonDocument["type"];

    if (typeData == "SincronizarVentas")
    {
        create_json("SincronizarVentas", true, "Ventas sincronizadas");
    }
    else if (typeData == "IniciarVenta")
    {
        create_json("IniciarVenta", true, "Venta Iniciada");
    }
    else if (typeData == "UltimaVenta")
    {
        create_json("UltimaVenta", true, "Ultima venta");
    }
    else if (typeData == "AjustarRTC")
    {
        create_json("AjustarRTC", true, "RTC OK");
    }
    else if (typeData == "WriteConfigParams")
    {
        create_json("WriteConfigParams", true, "Configs guardadas");
    }
    else if (typeData == "ReadConfigParams")
    {
        create_json("ReadConfigParams", true, "Data Configs");
    }
    else if (typeData == "ReporteTotal")
    {
        create_json("ReporteTotal", true, "Reporte OK");
    }
    else if (typeData == "ReporteParcial")
    {
        create_json("ReporteParcial", true, "Reporte OK");
    }
    else if (typeData == "ActivarAP")
    {
        create_json("ActivarAP", true, "AP activado");
    }
    else if (typeData == "ActivarWIFI")
    {
        create_json("ActivarWIFI", true, "Wifi Activado");
    }

    server.send(200, "application/json", buffer);

    if (typeData == "ActivarAP")
    {
        stopWIFI();
        setupAP();
    }
    else if (typeData == "ActivarWIFI")
    {
        stopWIFI();
        setupWIFI();
    }

}
