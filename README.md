# sylvestinator

## Resources

The [ENPH 253/480 Playlists](https://www.youtube.com/playlist?list=PLfCQFn-5zQea-hT0bXkBX_ccUr0g87iYa) provide some guidance on PlatformIO.

The robot embedded system is done on VS Code's PlatformIO with the Arduino framework. You can find [more libraries](https://platformio.org/lib) in the PlatformIO website.

For C++ coding help, refer to [C++ documentation](https://devdocs.io/cpp/), the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html), or this [Java to C++ basics](https://horstmann.com/ccj2/ccjapp3.html)

For C++ specific to STM32 development, refer to the [Arduino STM32 wiki](https://github.com/stm32duino/wiki/wiki).

## Structure

* `labs`: Code used for weekly ENPH 480 labs (## indicates which week)
* `robot`: Code for the actual robot
* `tools`: Dependencies/other tools we use
* `files`: Useful pdfs/files to reference while coding

When uploading robot code, make sure you upload the _entire_ project folder of your PlatformIO code (do not upload only `./src`) if there are significant differences.

If changes are minor, feel free to only upload the `main.cpp` code provided you name it properly as detailed in the next section.

## File Naming
Be __specific__ about the names of your projects/files and save them in the corresponding folders. Suffixes should be added to the end of each file to indicate whose code it is.
For example, if __John Doe__ was trying to upload a project folder named 'foo', it should be named
> foo_jd

To be more specific, add descriptions about what it was for. ie. for lab 1, name it:
> foo_l1_jd

You can choose to only upload to a personal branch or master if proper naming conventions are followed.

## To be continued...
