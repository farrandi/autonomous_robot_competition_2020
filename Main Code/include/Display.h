#ifndef Display_h
#define Display_h
#endif

#include <INIT.h>


class Display{
    public:
        // Constructors
        Display();
<<<<<<< HEAD

        // Sets up the displays
=======
        
        // Sets up the display
>>>>>>> 7c132714873f53004ef8de7d758466cb71f25058
        void setup();

        // Clears the display
        void clear();

        // Writes on the display and enters a new line
        void println(const char *s);
        void println(int num);
        void println(double num);

        // Writes on the display
        void print(const char *s);
        void print(int num);
        void print(double num);

        //Write a value on the display with a tag
<<<<<<< HEAD
        void taggedValue(const char *tag, int value);
=======
        void taggedValue(const char *tag, int value);\

>>>>>>> 7c132714873f53004ef8de7d758466cb71f25058

};