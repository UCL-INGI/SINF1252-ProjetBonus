void initRW();
void *readerAllow(int key, void *(*reader)(int key));
void writerAllow(int key, int value, void *(*writer)(int key, int value));
