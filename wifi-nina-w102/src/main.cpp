#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "secrets.h"

// #define BOT1_TOKEN "XXXXXXXX:XXXXXXXXX"  // your Bot Token (Get from Botfather)
// #define CHAT_ID "XXXXXXX"

// const char* ssid = "******";
// const char* password = "******";


WiFiClientSecure client;
UniversalTelegramBot bot(BOT1_TOKEN, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages)
{
  // Serial.println("handleNewMessages");
  // Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)
  {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID)
    {
      //bot.sendMessage(chat_id, "Unauthorized user", "");
      //continue;
    }

    // Print the received message
    
    String text = bot.messages[i].text;
    // Serial.println(bot.messages[i].chat_id);
    // Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text.startsWith("/running"))
    {
      Serial.println("running");
    }
    if (text.startsWith("/passing"))
    {
      Serial.println("passing");
    }
    if (text.startsWith("/failing"))
    {
      Serial.println("failing");
    }
    if (text.startsWith("/cancelled"))
    {
      Serial.println("cancelled");
    }
  }
}

void setup()
{
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("connecting");
  }
  
  Serial.println("connected");
}

void loop()
{
  if (millis() > lastTimeBotRan + botRequestDelay)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      // Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}