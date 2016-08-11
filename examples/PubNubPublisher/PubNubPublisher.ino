/*
  PubNub sample client

  This sample client will publish PubNub messages.

  This code is in the public domain.
  */

#include <PubNub.h>

char pubkey[] = "demo";
char subkey[] = "demo";
char channel[] = "hello_world";

void setup()
{
	Serial.begin(9600);
	Serial.println("Serial set up");

	PubNub.begin(pubkey, subkey);
	Serial.println("PubNub set up");
}

void loop()
{
	TCPClient *client;

	char msg[64] = "{\"analog\":[";
	for (int i = 0; i < 6; i++) {
		sprintf(msg + strlen(msg), "%d", i);
		if (i < 5)
			strcat(msg, ",");
	}
	strcat(msg, "]}");

	Serial.print("publishing message: ");
	Serial.println(msg);
	client = PubNub.publish(channel, msg);
	if (!client) {
		Serial.println("publishing error");
	} else {
		client->stop();
	}

	delay(5000);
}
