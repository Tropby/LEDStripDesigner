#pragma once

bool initSD();

boolean openFile(const char *filename);

size_t readFile(char *buffer, size_t maxSize);

void readConfig(char * ssid, char * password);