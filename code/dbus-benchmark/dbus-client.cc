#include <dbus/dbus.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#include "dbus-strings.h"
#include "dbus-util.h"

static void send_message (DBusConnection* conn, DBusError* error, size_t send_length = 1024)
{
    DBusMessage* message = dbus_message_new_method_call(
                ECHO_SERVICE_NAME,
                ECHO_SERVICE_PATH,
                ECHO_SERVICE_INTERFACE,
                ECHO_SERVICE_METHODNAME_ECHO);

    if (!message) {
        printf("Didn't allocate message\n");
        abort();
    }

    static bool inited = false;
    static char sent_string[2049];
    char* ptr_sent_string = &sent_string[0];

    if (!inited) {
        if (send_length > 2048)
        {
            send_length = 2048;
        }

        memset(sent_string, 'a', sizeof(sent_string) - 1);
        sent_string[sizeof(sent_string) - 1] = '\0';
        sent_string[send_length] = '\0';
        inited = true;
    }

    dbus_message_append_args(message, DBUS_TYPE_STRING, &ptr_sent_string, DBUS_TYPE_INVALID);

    DBusMessage* reply = dbus_connection_send_with_reply_and_block(conn, message, DBUS_TIMEOUT_INFINITE, error);
    enforce_error(error);

    dbus_message_unref(message);
    message = NULL;

    char const* replied_string;

    dbus_message_get_args(reply, error, DBUS_TYPE_STRING, &replied_string, DBUS_TYPE_INVALID);
    enforce_error(error);

    dbus_message_unref(reply);
    reply = NULL;
}

int main (int argc, char* argv[])
{
    DBusError error;
    int callCount = 500;
    int messageSize = 1024;
    int inputArg;
   
    printf("\narguments: { ");

    for (int i = 0; i < argc; ++i)
        printf("%s\"%s\"",
               (i == 0) ? "" : ", ",
               argv[i]);

    printf("}\n");

    if (argc > 1)
    {
        callCount = atoi(argv[1]);
        if (callCount < 10 || callCount > 20000)
        {
            exit(EXIT_FAILURE);
        }
    }

    if (argc > 2)
    {
        messageSize = atoi(argv[2]);
        if (messageSize < 1 || messageSize > 20000)
        {
            exit(EXIT_FAILURE);
        }
    }

    dbus_error_init(&error);

    #if defined(__QNX__)
        DBusConnection* conn = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
    #else
        DBusConnection* conn = dbus_bus_get(DBUS_BUS_SESSION, &error);
    #endif

    enforce_error(&error);

    // send message once to handle init
    send_message(conn, &error, messageSize);

    struct timeval before, after;
    gettimeofday(&before, NULL);

    for (unsigned int i = 0; i < callCount; ++i) {
        send_message(conn, &error);
    }

    gettimeofday(&after, NULL);

    double elapsed = after.tv_sec + (after.tv_usec / (double)1000000);
    elapsed -= before.tv_sec + (before.tv_usec / (double)1000000);

    printf("%d messages in %2.3f sec, %2.5f sec per message\n",
           callCount, elapsed, elapsed / callCount);

    return 0;
}
