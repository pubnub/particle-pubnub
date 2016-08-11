/*
  PubNub sample subscribe client

  This sample client will subscribe to and handle raw PubNub messages
  (not doing any JSON decoding).  It does so with a randomly generated
  UUID.

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

	Serial.println("waiting for a message (subscribe)");
	client = PubNub.subscribe(channel);
	if (!client) {
		Serial.println("subscription error");
		delay(1000);
		return;
	}
	Serial.print("Received: ");
	while (client->wait_for_data()) {
		char c = client->read();
		Serial.print(c);
	}
	client->stop();
	Serial.println();

	delay(200);
}
