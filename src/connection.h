#ifndef CONNECTION_H
#define CONNECTION_H

extern bool forceOffline;

void InitWifi(bool);
void checkWifi(bool);
void HandleOTA();
void InitOTA();

extern void disableBlynkTemporary();

#endif // CONNECTION_H
