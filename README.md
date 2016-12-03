# schedule-generator
A schedule generation tool to help with the college class registration process

## How to build
Requires make and gcc, or an understanding of how to edit makefiles.
Obtain a copy of this repo in any way. Navigate to its root folder (contains README and LICENSE among other things) and run `make`

## How to run
Once built, the executable is located in the `bin` directory as `bin/schedule_generator`

## How to use
Run `bin/schedule_generator` and follow the directions on how to input each class

The schedule generator can also read a class list from a file. The format is exactly like what is inputted when done by hand: the first line is the number of courses, followed by a single class on every line, and ending with the word "done" on the last line.

## License information
This project is licensed under the MIT License. Be sure to check the `LICENSE` file for complete details.
