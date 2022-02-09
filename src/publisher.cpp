#include "publisher.h"

struct mosquitto *mosq;

int convertIntToChar(int num, char *resul)
{
    std::string str = std::to_string(num);
    std::strcpy(resul, str.c_str());
    return str.length() + 1;
}

std::string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);

    // Structed string time
    std::strftime(buf, sizeof(buf), "%Y-%m-%d.%H:%M:%S", &tstruct);

    return buf;
}

//Finish publisher
void finishPublisher(char *name)
{
    printf("Disconnected!\n");
    std::string times = currentDateTime();
    char aux[80];
    std::strcpy(aux, times.c_str());

    // Create end topic
    char msg[3 + times.length()];
    std::sprintf(msg, "%s %s", "end", aux);

    mosquitto_publish(mosq, NULL, name, 3 + times.length(), msg, 0, false);

    // Disconnecting
    mosquitto_disconnect(mosq);
    mosquitto_loop_stop(mosq, false);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

void initPublisher()
{
    mosquitto_lib_init();

    mosq = mosquitto_new("publisher_cpp", false, NULL);

    int rc, aut;

    aut = mosquitto_username_pw_set(mosq, "admin", "admin");

    if (aut != MOSQ_ERR_SUCCESS)
    {
        printf("INVALID PASSWORD!! \n");
        exit(1);
    }

    rc = mosquitto_connect(mosq, "broker.emqx.io", 1883, 60); // Public broker
    //rc = mosquitto_connect(mosq, "", 1883, 60);

    while (rc != MOSQ_ERR_SUCCESS)
    {
        printf("Client could not connect to broker! Error Code: %d\n", rc);
        rc = mosquitto_reconnect(mosq); // Try to reconnect for each 5 secs
        sleep(5);
    }

    printf("MQTT connect: %s \n", mosquitto_connack_string(rc));

    int lp = mosquitto_loop_start(mosq);

    mosquitto_reconnect_delay_set(mosq, 2, 10, false); // We set the reconnection delay if the connection fails in the middle of the loop
    if (lp != MOSQ_ERR_SUCCESS)
    {
        printf("Loop error\n");
    }
}

void publicar(int pIN, int pOut, char *name)
{

    //Create people in message
    char inStr[10];
    int inLen = convertIntToChar(pIN, inStr);

    //Create people out message
    char outStr[10];
    int outLen = convertIntToChar(pOut, outStr);

    //Create time message
    std::string times = currentDateTime();
    char aux[80];
    strcpy(aux, times.c_str());

    //Create entire structure
    char msg[outLen + inLen + times.length()];
    sprintf(msg, "%s %s %s", aux, inStr, outStr);

    mosquitto_publish(mosq, NULL, name, outLen + inLen + times.length(), msg, 0, false);
}
