#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <SD.h>

#include "https.h"
#include "sdreader.h"

char ssid[64] = "Tropby";
char password[64] = "a25kj69s";

String fileList;

WebServer server(80);

void initWiFi()
{
    WiFi.disconnect(true);

    delay(100);

    WiFi.onEvent(WiFiEvent);

    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname("ESP32_LED");

    WiFi.begin(ssid, password);

    server.on("/", handle_OnConnect);
    server.on("/GetRSSI", handle_GetRSSI);

    server.on("/fileList", handle_readDirectory);
    server.on("/openFile", HTTP_GET, handle_openFile);

    
    File dir = SD.open("/");
    while (File entry = dir.openNextFile())
    {
        String filename = String(entry.name());
        filename.toLowerCase();
        if (filename.endsWith(".alc"))
        {
            filename = String(entry.name());
            fileList += "<a href='/openFile?filename=" + filename + "'>" + filename + "</ a><br />";
        }
        entry.close();
    }

    server.onNotFound(handle_NotFound);
    server.begin();
    Serial.println("HTTP server started");

    Serial.println();
    Serial.println();
    Serial.println("Wait for WiFi... ");
}

void WiFiEvent(WiFiEvent_t event)
{
    Serial.printf("[WiFi-event] event: %d\n", event);
    switch (event)
    {
    case SYSTEM_EVENT_WIFI_READY:
        Serial.println("WiFi interface ready");
        break;
    case SYSTEM_EVENT_SCAN_DONE:
        Serial.println("Completed scan for access points");
        break;
    case SYSTEM_EVENT_STA_START:
        Serial.println("WiFi client started");
        break;
    case SYSTEM_EVENT_STA_STOP:
        Serial.println("WiFi clients stopped");
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        Serial.println("Connected to access point");
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("Disconnected from WiFi access point");

        WiFi.disconnect();
        WiFi.reconnect();

        break;
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
        Serial.println("Authentication mode of access point has changed");
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.print("Obtained IP address: ");
        Serial.println(WiFi.localIP());
        break;
    case SYSTEM_EVENT_STA_LOST_IP:
        Serial.println("Lost IP address and IP address is reset to 0");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
        Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
        Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
        Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
        Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
        break;
    case SYSTEM_EVENT_AP_START:
        Serial.println("WiFi access point started");
        break;
    case SYSTEM_EVENT_AP_STOP:
        Serial.println("WiFi access point  stopped");
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        Serial.println("Client connected");
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        Serial.println("Client disconnected");
        break;
    case SYSTEM_EVENT_AP_STAIPASSIGNED:
        Serial.println("Assigned IP address to client");
        break;
    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        Serial.println("Received probe request");
        break;
    case SYSTEM_EVENT_GOT_IP6:
        Serial.println("IPv6 is preferred");
        break;
    case SYSTEM_EVENT_ETH_START:
        Serial.println("Ethernet started");
        break;
    case SYSTEM_EVENT_ETH_STOP:
        Serial.println("Ethernet stopped");
        break;
    case SYSTEM_EVENT_ETH_CONNECTED:
        Serial.println("Ethernet connected");
        break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
        Serial.println("Ethernet disconnected");
        break;
    case SYSTEM_EVENT_ETH_GOT_IP:
        Serial.println("Obtained IP address");
        break;
    default:
        break;
    }
}

String SendHTML()
{
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<title>LED Strip Animator</title>\n";
    ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
    ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
    ptr += "</style>\n";
    ptr += "</head>\n";
    ptr += "<body>\n";
    ptr += "<div id=\"webpage\">\n";
    ptr += "<h1>LED Strip Animator</h1>\n";
    ptr += fileList;
    ptr += "</div>\n";
    ptr += "</body>\n";
    ptr += "</html>\n";
    return ptr;
}

void handle_GetRSSI()
{
    int8_t rssi = WiFi.RSSI();

    DynamicJsonDocument doc(1024);
    doc["hello"] = "world";
    doc["rssi"] = rssi;

    char buffer[400];
    serializeJson(doc, buffer);
    server.send(200, "text/html", buffer);
}

void handle_OnConnect()
{
    Serial.println("Event!");
    server.send(200, "text/html", SendHTML());
}

void handle_NotFound()
{
    server.send(404, "text/plain", "Not found");
}

void handleHTTPS()
{
    server.handleClient();
}

void handle_openFile()
{
    if (server.hasArg("filename"))
    {
        if( openFile(server.arg("filename").c_str()) )
        {
            server.send(200, "text/html", "<meta http-equiv='refresh' content='0; URL=/'>");
        }
        else
        {
            server.send(200, "text/html", "{\"code\":\"error\", \"message\":\"can not open file!\"}");
        }
    }
    else
    {
        server.send(200, "text/html", "{\"code\":\"error\", \"message\":\"no filename provided!\"}");
    }
}

void handle_readDirectory()
{
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.createNestedArray("files");

    File dir = SD.open("/");
    while (File entry = dir.openNextFile())
    {
        array.add(String(entry.name()));
        entry.close();
    }

    char buffer[1024];
    serializeJson(doc, buffer);
    server.send(200, "text/html", buffer);
}

void scanNetworks()
{
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            delay(10);
        }
    }
    Serial.println("");
}